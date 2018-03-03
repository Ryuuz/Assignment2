#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QBasicTimer>
#include <QTime>
#include <vector>

class QOpenGLContext;
class Shader;
class MainWindow;
class ObjectInstance;
class Camera;
class PhysicsObject;
class Plane;
class Sphere;
class Axis;
class Cube;
class Collision;
class TriggerVolume;
class Texture;


class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT

    public:
        RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
        ~RenderWindow();
        QOpenGLContext *context() { return mContext; }
        void exposeEvent(QExposeEvent *) override;

    signals:
        void ready();
        void error(const QString &msg);

    private slots:
        void render();
        void update();
        void swapCamera();

    private:
        void init();
        void createObjects();
        void startOpenGLDebugger();

        QOpenGLContext *mContext;
        bool mInitialized;

        Shader *mShaderProgram;
        Shader *mTextureShader;
        Texture *mTexture;
        GLuint mTextureUniform;
        GLint mMatrixUniform;

        Collision *mCollision;

        Camera *mCurrentCamera;
        Camera *mCamera1;
        Camera *mCamera2;

        Plane *mPlane;
        Sphere *mSphere;
        Cube *mCube;
        Axis *mAxis;

        std::vector<ObjectInstance*> mStaticObjects;
        std::vector<PhysicsObject*> mDynamicObjects;
        std::vector<TriggerVolume*> mTriggerVolumes;
        PhysicsObject *mPlayerBall;

        QBasicTimer mTimer;     //timer that drives the gameloop
        QTime mTimeStart;       //time variable that reads the actual FPS

        MainWindow *mMainWindow;
        bool yeah = false;

        class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};

        void checkForGLerrors();

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        void timerEvent(QTimerEvent *) override;
};

#endif // RENDERWINDOW_H
