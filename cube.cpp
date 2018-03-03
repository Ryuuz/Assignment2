#include "cube.h"
#include "vertex.h"
#include <QVector3D>


Cube::Cube()
{
    mNumberOfVertices = 36;

    //The vertices used for drawing the object
    mVertices = new Vertex[mNumberOfVertices]
    {
        //Back
        {QVector3D{-0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 0.f}},
        {QVector3D{0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},

        {QVector3D{0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{-0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},
        {QVector3D{-0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 1.f}},

        //Right side
        {QVector3D{0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 0.f}},
        {QVector3D{0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},

        {QVector3D{0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},
        {QVector3D{0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 1.f}},

        //Left side
        {QVector3D{-0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{-0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 0.f}},
        {QVector3D{-0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},

        {QVector3D{-0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{-0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},
        {QVector3D{-0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 1.f}},

        //Bottom
        {QVector3D{-0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{-0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 0.f}},
        {QVector3D{0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},

        {QVector3D{-0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{0.5f, -0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},
        {QVector3D{0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 1.f}},

        //Top
        {QVector3D{-0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{-0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 0.f}},
        {QVector3D{0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},

        {QVector3D{-0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},
        {QVector3D{0.5f, 0.5f, -0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 1.f}},

        //Front
        {QVector3D{-0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{-0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 0.f}},
        {QVector3D{0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},

        {QVector3D{-0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{0.f, 1.f}},
        {QVector3D{0.5f, -0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.f, 0.f}},
        {QVector3D{0.5f, 0.5f, 0.5f}, QVector3D{0.9f, 0.9f, 0.9f}, QVector2D{1.0f, 1.f}}
    };

    findMaxVertex();
    findMinVertex();

    init();
}


Cube::~Cube()
{
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}


//Initiate everything needed for rendering
void Cube::init()
{
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    //Sets up and fills the VBO
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mNumberOfVertices*sizeof(Vertex), mVertices, GL_STATIC_DRAW);

    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    mDrawType = GL_TRIANGLES;

    delete[] mVertices;
}
