#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QVector3D>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QDebug>

#include "shader.h"
#include "mainwindow.h"
#include "objectinstance.h"
#include "sceneobject.h"
#include "physicsobject.h"
#include "camera.h"
#include "plane.h"
#include "sphere.h"
#include "axis.h"
#include "cube.h"
#include "boundingvolume.h"
#include "triggervolume.h"
#include "collision.h"
#include "transform.h"
#include "texture.h"


RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext{0}, mInitialized{false}, mMainWindow{mainWindow}
{
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    mContext = new QOpenGLContext(this);
    mContext->setFormat(requestedFormat());
    if (!mContext->create())
    {
        delete mContext;
        mContext = 0;
    }
}


RenderWindow::~RenderWindow()
{
    mCurrentCamera = nullptr;
    delete mCamera1;
    delete mCamera2;

    delete mShaderProgram;
    mPlayerBall = nullptr;

    for(auto element : mStaticObjects)
    {
        delete element;
    }

    for(auto element : mDynamicObjects)
    {
        delete element;
    }

    delete mPlane;
    delete mSphere;
    delete mAxis;
    delete mCube;
}


void RenderWindow::init()
{
    if (!mContext->makeCurrent(this)) {
        emit error(tr("makeCurrent() failed"));
        return;
    }

    if (!mInitialized)
    {
        mInitialized = true;
    }

    initializeOpenGLFunctions();

    startOpenGLDebugger();

    mCamera1 = new Camera;
    mCamera2 = new Camera;

    //Set the perspective and view matrices
    mCamera1->setPerspectiveMatrix();
    mCamera1->setViewMatrix(1.f, 4.f, 4.f);
    mCamera2->setPerspectiveMatrix();
    mCamera2->setViewMatrix(0.f, 4.f, 4.f);

    mCurrentCamera = mCamera1;

    mCollision = new Collision;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    //Compile shaders:
    mShaderProgram = new Shader("vertexshader.vert", "fragmentshader.frag");
    mTextureShader = new Shader("textureshader.vert", "textureshader.frag");

    mTexture = new Texture("../Assignment2/Bricks.bmp");
    mTextureUniform = glGetUniformLocation(mTextureShader->getProgram(), "textureSampler");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture->id());

    //enable the matrixUniform
    mMatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "matrix" ); // enable in shader and in render() function also to use matrix

    //Load assets
    mPlane = new Plane;
    glBindVertexArray(0);

    mSphere = new Sphere(3);
    glBindVertexArray(0);

    mCube = new Cube;
    glBindVertexArray(0);

    mAxis = new Axis;
    glBindVertexArray(0);

    //Create and place objects
    createObjects();

    emit ready();   //tell the mainWindow that init is finished
}


void RenderWindow::createObjects()
{
    ObjectInstance *obj;
    TriggerVolume *triggObj;
    PhysicsObject *physObj;

    //Axis
    obj = new ObjectInstance(mAxis, mShaderProgram);
    mStaticObjects.push_back(obj);

    //Ground plane
    obj = new ObjectInstance(mPlane, mShaderProgram);
    obj->getTransform()->setRotation(-90.f, 0.f, 0.f);
    obj->getTransform()->setScale(3.f, 3.f, 3.f);
    mStaticObjects.push_back(obj);

    //Walls
    obj = new ObjectInstance(mCube, mTextureShader, mTextureUniform);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(0.f, 0.2f, -1.5f);
    obj->getTransform()->setScale(3.1f, 0.4f, 0.1f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mTextureShader, mTextureUniform);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(0.f, 0.2f, 1.5f);
    obj->getTransform()->setScale(3.1f, 0.4f, 0.1f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mTextureShader, mTextureUniform);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(-1.5f, 0.2f, 0.f);
    obj->getTransform()->setScale(0.1f, 0.4f, 3.f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mTextureShader, mTextureUniform);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(1.5f, 0.2f, 0.f);
    obj->getTransform()->setScale(0.1f, 0.4f, 3.f);
    mStaticObjects.push_back(obj);

    //House
    obj = new ObjectInstance(mCube, mShaderProgram);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(0.75f, 0.5f, -1.3f);
    obj->getTransform()->setScale(1.2f, 1.f, 0.1f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mShaderProgram);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(1.4f, 0.5f, -0.75f);
    obj->getTransform()->setScale(0.1f, 1.f, 1.2f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mShaderProgram);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(0.1f, 0.5f, -0.75f);
    obj->getTransform()->setScale(0.1f, 1.f, 1.2f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mShaderProgram);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(1.2f, 0.5f, -0.1f);
    obj->getTransform()->setScale(0.5f, 1.f, 0.1f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mShaderProgram);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(0.3f, 0.5f, -0.1f);
    obj->getTransform()->setScale(0.5f, 1.f, 0.1f);
    mStaticObjects.push_back(obj);

    obj = new ObjectInstance(mCube, mShaderProgram);
    obj->setBoundingObject(BoundType::box);
    obj->getTransform()->setPosition(0.75f, 1.05f, -0.75f);
    obj->getTransform()->setScale(1.4f, 0.1f, 1.4f);
    mStaticObjects.push_back(obj);

    //Trigger volume
    triggObj = new TriggerVolume;
    triggObj->setBoundingObject(QVector3D(0.5f, 1.f, 0.5f), QVector3D(-0.5f, 0.f, -0.5f), BoundType::trigger);
    triggObj->getTransform()->setScale(1.3f, 1.f, 1.2f);
    triggObj->getTransform()->setPosition(0.75f, 0.f, -0.75f);
    connect(triggObj, &TriggerVolume::entered, this, &RenderWindow::swapCamera);
    connect(triggObj, &TriggerVolume::exited, this, &RenderWindow::swapCamera);
    mTriggerVolumes.push_back(triggObj);

    //Ball
    physObj = new PhysicsObject(mSphere, mShaderProgram);
    physObj->setBoundingObject(BoundType::sphere);
    physObj->getTransform()->setPosition(0.2f, 0.15f, 0.5f);
    physObj->getTransform()->setScale(0.15f, 0.15f, 0.15f);
    mDynamicObjects.push_back(physObj);

    physObj = new PhysicsObject(mSphere, mShaderProgram);
    physObj->setBoundingObject(BoundType::sphere);
    physObj->getTransform()->setPosition(-0.6f, 0.15f, -1.f);
    physObj->getTransform()->setScale(0.15f, 0.15f, 0.15f);
    mDynamicObjects.push_back(physObj);

    mPlayerBall = mDynamicObjects.at(0);

    obj = nullptr;
    triggObj = nullptr;
    physObj = nullptr;
}


void RenderWindow::render()
{
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)

    initializeOpenGLFunctions();

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Draw the models
    for(auto object : mStaticObjects)
    {
        object->draw(mMatrixUniform, mCurrentCamera);
        checkForGLerrors();
    }

    for(auto object : mDynamicObjects)
    {
        object->draw(mMatrixUniform, mCurrentCamera);
        checkForGLerrors();
    }

    glBindVertexArray(0);
    mContext->swapBuffers(this);
}


void RenderWindow::update()
{
    for(auto object : mDynamicObjects)
    {
        for(auto item : mStaticObjects)
        {
            if(object->getBounds() && item->getBounds())
            {
                if(mCollision->collisionDetection(object->getBounds(), item->getBounds(), object->getVelocity()))
                {
                    mCollision->collisionHandling(object);
                }
            }
        }

        for(auto item : mDynamicObjects)
        {
            if(item != object && item->getBounds() && object->getBounds())
            {
                if(mCollision->collisionDetection(object->getBounds(), item->getBounds(), object->getVelocity()))
                {
                    mCollision->collisionHandling(object, item);
                }
            }
        }

        object->physicsUpdate();
    }

    for(auto item : mTriggerVolumes)
    {
        if(mPlayerBall->getBounds() && item->getBounds())
        {
            if(mCollision->collisionDetection(mPlayerBall->getBounds(), item->getBounds(), mPlayerBall->getVelocity()))
            {
                item->onEnter();
            }
            else
            {
                item->onExit();
            }
        }
    }
}


void RenderWindow::swapCamera()
{
    if(mCurrentCamera == mCamera1)
    {
        mCurrentCamera = mCamera2;
    }
    else
    {
        mCurrentCamera = mCamera1;
    }
}


void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        qDebug() << "Can this system run QOpenGLDebugLogger? :" << format.testOption(QSurfaceFormat::DebugContext);

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            qDebug() << "System can log OpenGL errors!";
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
            {
                qDebug() << "Started OpenGL debug logger!";
            }
        }
    }
}


void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
            qDebug() << message;
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << "glGetError returns " << err;
        }
    }
}


//This function is called from Qt when window is exposed / shown
void RenderWindow::exposeEvent(QExposeEvent *)
{
    if (!mInitialized)
    {
       init();
    }

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    if (isExposed())
    {
        mTimer.start(16, this);
        mTimeStart.start();
    }
}


void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
            mMainWindow->close();
    }
    else
    {
        mPlayerBall->setVelocity(event);
    }
}


void RenderWindow::timerEvent(QTimerEvent *)
{
    update();
    render();
}
