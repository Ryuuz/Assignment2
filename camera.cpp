#include "camera.h"
#include <QMatrix4x4>
#include <QVector4D>


Camera::Camera()
{
    mViewMatrix = new QMatrix4x4;
    mPerspectiveMatrix = new QMatrix4x4;

    mViewMatrix->setToIdentity();
    mPerspectiveMatrix->setToIdentity();
}


Camera::~Camera()
{
    delete mViewMatrix;
    delete mPerspectiveMatrix;
}


void Camera::setViewMatrix(GLfloat x, GLfloat y, GLfloat z)
{
    mViewMatrix->lookAt(QVector3D(x, y, z), QVector3D(0.f, 0.f, 0.f), QVector3D(0.f, 1.f, 0.f));
}


void Camera::setPerspectiveMatrix()
{
    mPerspectiveMatrix->perspective(45.f, 1.3f, 0.1, 1000.f);
}



