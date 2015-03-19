#ifndef GAME_ENGINE_SHADER_H
#define GAME_ENGINE_SHADER_H

#include <GL\glew.h>
#include "../BasicTypes.h"


namespace Engine
{
    class Shader : public Object
    {
        CLASS_HEADER(Shader)
    public:
        ///Sets the shader to default values.
        Shader();
        ~Shader();

        //Loads the shader file
        void LoadFile(const std::string & aFilename);
        //Loads the loaded shader source into opengl/direct3D
        void LoadProgram();
        //Loads the shader file then loads the shader source into opengl/direct3D
        void Load(const std::string & aFilename);
        //Release the shader file from memory
        void ReleaseFile();
        //Release the shader program from memory
        void ReleaseProgram();
        //Releases the shader file and program from memory
        void Release();
           
        //Tells OpenGL to use this shader
        bool UseShader();
        //Retrieve an attributes location from the shader. Call UseShader before calling this.
        GLint GetAttributeLocation(const std::string & aName);
        //Retrieve a uniforms location from the shader. Call UseShader before calling this.
        GLint GetUniformLocation(const std::string & aName);

    private:
        std::string m_VertexShaderSource;
        std::string m_FragmentShaderSource;
        std::string m_GeometryShaderSource;

        bool m_VertexShaderLoaded;
        bool m_FragmentShaderLoaded;
        bool m_GeometryShaderLoaded;
        bool m_ShaderHandleLoaded;

        GLuint m_VertexShader;
        GLuint m_FragmentShader;
        GLuint m_GeometryShader;
        GLuint m_ShaderHandle;

    };

}

#endif