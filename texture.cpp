#include <QDebug>
#include <QImage>
#include <QBuffer>
#include <QByteArray>

#include <iostream>
#include <fstream>
#include <string>

#include "texture.h"
#include "constants.h"

//Quick fix to get rid of windows.h which contains
//BITMAPINFOHEADER and BITMAPFILEHEADER.
typedef unsigned short int OWORD;    //should be 16 bit
typedef unsigned int ODWORD;         //should be 32 bit
typedef int OLONG;                   //should be 32 bit

struct OBITMAPINFOHEADER {
    ODWORD biSize;
    OLONG  biWidth;
    OLONG  biHeight;
    OWORD  biPlanes;
    OWORD  biBitCount;
    ODWORD biCompression;
    ODWORD biSizeImage;
    OLONG  biXPelsPerMeter;
    OLONG  biYPelsPerMeter;
    ODWORD biClrUsed;
    ODWORD biClrImportant;
};

struct OBITMAPFILEHEADER {
    OWORD  bfType;
    ODWORD bfSize;
    OWORD  bfReserved1;
    OWORD  bfReserved2;
    ODWORD bfOffBits;
};

Texture::Texture() : QOpenGLFunctions_4_1_Core()
{
    //small dummy texture
    for (int i=0; i<11; i++)
        pixels[i] = 0;
    pixels[0] = 255;
    pixels[4] = 255;
    pixels[8] = 255;
    pixels[9] = 255;
    pixels[10] = 255;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    qDebug() << "Texture::Texture() id = " << mId;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, reinterpret_cast<const GLvoid*>(pixels));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

//!
//! \brief Texture::Texture() Read a bitmap file and create a texture with standard parameters
//! \param filename The name of the bmp file containing a texture
//! First one 2D texture is generated from
//! - glGenTextures()
//! Then the OpenGL functions
//! - glBindTexture()
//! - glTexParameteri()
//! - glTexImage2D()
//! are used. The texture can be retrieved later by using the function id()
Texture::Texture(const std::string &filename): QOpenGLFunctions_4_1_Core()
{
    initializeOpenGLFunctions();
    readBitmap(filename);
    setTexture();
}

//!
//! \brief Texture::id() Return the id of a previously generated texture object
//! \return The id of a previously generated texture object
//!
GLuint Texture::id() const
{
    return mId;
}

void Texture::readBitmap(const std::string &filename)
{
    OBITMAPFILEHEADER bmFileHeader;
    OBITMAPINFOHEADER bmInfoHeader;

    std::ifstream file;
    file.open ((gsl::assetFilePath + filename).c_str(), std::ifstream::in | std::ifstream::binary);
    if (file.is_open())
    {
        file.read((char *) &bmFileHeader, 14);

        file.read((char *) &bmInfoHeader, sizeof(OBITMAPINFOHEADER));
        mColumns = bmInfoHeader.biWidth;
        mRows = bmInfoHeader.biHeight;
        mnByte = bmInfoHeader.biBitCount / 8;

        mBitmap = new unsigned char[mColumns * mRows * mnByte];
        file.read((char *) mBitmap, mColumns * mRows * mnByte);
        file.close();
    }
    else
    {
        qDebug() << "Can not read " << QString((gsl::assetFilePath + filename).c_str());
    }
    unsigned char tmp;
    // switch red and blue
    for (int k = 0; k < mColumns * mRows * mnByte; k += mnByte) {
        tmp = mBitmap[k];
        mBitmap[k] = mBitmap[k + 2];
        mBitmap[k + 2] = tmp;
    }
}

void Texture::setTexture()
{
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mColumns, mRows, 0, GL_RGB, GL_UNSIGNED_BYTE, mBitmap);
}
