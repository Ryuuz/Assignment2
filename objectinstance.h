#ifndef OBJECTINSTANCE_H
#define OBJECTINSTANCE_H

#include <QOpenGLFunctions_4_1_Core>
#include "boundingvolume.h"

class SceneObject;
class QVector3D;
class QMatrix4x4;
class Shader;
class Camera;
class Transform;


class ObjectInstance : protected QOpenGLFunctions_4_1_Core
{
    public:
        ObjectInstance(SceneObject *a = nullptr, Shader *s = nullptr, GLuint t = 999);
        ~ObjectInstance();
        void draw(GLuint m, Camera *camera);

        void setShader(Shader *s) {mShader = s;}
        void setBoundingObject(BoundType type);
        void setBoundingObject(QVector3D max, QVector3D min, BoundType type);

        Shader* getShader() const {return mShader;}
        BoundingVolume* getBounds() const {return mBoundingObject;}
        Transform* getTransform() const {return mTransform;}
        QMatrix4x4* getModelMatrix();

    protected:
        SceneObject *mModel;
        QMatrix4x4 *mModelMatrix;
        Shader *mShader;
        BoundingVolume *mBoundingObject;
        Transform *mTransform;
        GLuint mTexUniform;
};

#endif // OBJECTINSTANCE_H
