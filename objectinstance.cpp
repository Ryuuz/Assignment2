#include "objectinstance.h"
#include "sceneobject.h"
#include "shader.h"
#include "camera.h"
#include "transform.h"
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <QQuaternion>


ObjectInstance::ObjectInstance(SceneObject *a, Shader *s, GLuint t) : mModel(a), mShader(s), mTexUniform(t)
{
    mModelMatrix = new QMatrix4x4;
    mModelMatrix->setToIdentity();
    mBoundingObject = nullptr;
    mTransform = new Transform;
}


ObjectInstance::~ObjectInstance()
{
    delete mModelMatrix;
    delete mBoundingObject;
    delete mTransform;
    mModel = nullptr;
    mShader = nullptr;
}


//Calculates the MVP matrix and draws the object using the given 'mDrawType'
void ObjectInstance::draw(GLuint m, Camera *camera)
{
    if(mModel)
    {
        initializeOpenGLFunctions();

        glUseProgram(mShader->getProgram());
        glBindVertexArray(mModel->getVao());

        if(mTexUniform != 999)
        {
            glUniform1i(mTexUniform, 0);
        }

        QMatrix4x4 mvp = (*camera->getPerspectiveMatrix())*(*camera->getViewMatrix())*(*getModelMatrix());
        glUniformMatrix4fv(m, 1, GL_FALSE, mvp.constData());
        glDrawArrays(mModel->mDrawType, 0, mModel->getVertexNumber());
    }
}


//Creates bounding volume of given type based on the model
void ObjectInstance::setBoundingObject(BoundType type)
{
    if(mModel)
    {
        mBoundingObject = new BoundingVolume(mModel->getMaxVertex(), mModel->getMinVertex(), type, this);
    }
}


//Creates a bounding volume with the given values
void ObjectInstance::setBoundingObject(QVector3D max, QVector3D min, BoundType type)
{
    mBoundingObject = new BoundingVolume(max, min, type, this);
}


//Performs all transformations on the model matrix and returns it
QMatrix4x4* ObjectInstance::getModelMatrix()
{
    mModelMatrix->setToIdentity();
    mModelMatrix->translate(mTransform->getTranslation());
    mModelMatrix->rotate(QQuaternion::fromEulerAngles(mTransform->getRotation()));
    mModelMatrix->scale(mTransform->getScale());

    return mModelMatrix;
}
