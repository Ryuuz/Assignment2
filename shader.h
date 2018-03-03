#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <QOpenGLFunctions_4_1_Core>

//This class is pretty much a copy of the shader class at
//https://github.com/SonarSystems/Modern-OpenGL-Tutorials/blob/master/%5BLIGHTING%5D/%5B8%5D%20Basic%20Lighting/Shader.h

class Shader : protected QOpenGLFunctions_4_1_Core
{
    public:
        // Constructor generates the shader on the fly
        Shader( const std::string &vertexPath, const std::string &fragmentPath );
        // Uses the current shader
        void Use();

        GLuint getProgram() const;

    private:
        GLuint program;
};

#endif
