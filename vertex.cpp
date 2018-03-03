#include "vertex.h"


Vertex::Vertex()
{

}


Vertex::Vertex(QVector3D pos, QVector3D col, QVector2D uv) : mPosition(pos), mColor(col), mUV(uv)
{

}


//Sets the 3D position the vertex will hold
void Vertex::setPosition(const QVector3D &pos)
{
    mPosition = pos;
}


void Vertex::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    mPosition.setX(x);
    mPosition.setY(y);
    mPosition.setZ(z);
}


//Sets the color the vertex should have
void Vertex::setColor(const QVector3D &col)
{
    mColor = col;
}


void Vertex::setColor(GLfloat r, GLfloat g, GLfloat b)
{
    mColor.setX(r);
    mColor.setY(g);
    mColor.setZ(b);
}


void Vertex::setUV(const QVector2D &uv)
{
    mUV = uv;
}


void Vertex::setUV(GLfloat u, GLfloat v)
{
    mUV.setX(u);
    mUV.setY(v);
}
