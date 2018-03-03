#ifndef CAMERA_H
#define CAMERA_H

#include <QtGui/qopengl.h>
#include <QVector3D>

class QMatrix4x4;

class Camera
{
    public:
        Camera();
        ~Camera();

        void setViewMatrix(GLfloat x, GLfloat y, GLfloat z);
        void setPerspectiveMatrix();


        QMatrix4x4* getViewMatrix() const {return mViewMatrix;}
        QMatrix4x4* getPerspectiveMatrix() const {return mPerspectiveMatrix;}

    private:
        QMatrix4x4 *mViewMatrix;
        QMatrix4x4 *mPerspectiveMatrix;
};

#endif // CAMERA_H
