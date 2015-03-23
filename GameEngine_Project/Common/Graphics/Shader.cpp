#include "Shader.h"
#include <fstream>
#include "Graphics.h"
#include "../Utilities/Utilities.h"

namespace Engine
{
    CLASS_CPP(Shader,Object)
    Shader::Shader()
    {
        m_FragmentShader = 0;
        m_FragmentShaderLoaded = false;
        m_FragmentShaderSource = "";

        m_VertexShader = 0;
        m_VertexShaderLoaded = false;
        m_VertexShaderSource = "";

        m_GeometryShader = 0;
        m_GeometryShaderLoaded = false;
        m_GeometryShaderSource = "";

        m_ShaderHandle = 0;
        m_ShaderHandleLoaded = false;
    }
    Shader::~Shader()
    {
        Release();
    }

    //Loads the shader file
    void Shader::LoadFile(const std::string & aFilename)
    {
        std::ifstream fileStream;
        fileStream.open(aFilename);
        if (!fileStream.is_open())
        {
            DEBUG_LOG("Failed to load in file %s", aFilename.c_str());
            return;
        }
        string shaderSource;
        string line; 
        ShaderType shaderType;
        bool buildingShaderSource = false;
        std::vector<string> words;
        while (std::getline(fileStream, line))
        {
            if (line.size() == 0)
            {
                continue;
            }
            words.clear();
            GetWords(line, words);
            if (words.size() > 0)
            {
                if (words[0] == "#implement" && words.size() > 1)
                {
                    if (buildingShaderSource)
                    {
                        switch (shaderType)
                        {
                            case ShaderType::Vertex:
                                m_VertexShaderSource = shaderSource;
                                break;
                            case ShaderType::Fragment:
                                m_FragmentShaderSource = shaderSource;
                                break;
                            case ShaderType::Geometry:
                                m_GeometryShaderSource = shaderSource;
                                break;
                        }
                        buildingShaderSource = false;
                        shaderSource.clear();
                    }
                    if (words[1] == "vertex")
                    {
                        shaderType = ShaderType::Vertex;
                        buildingShaderSource = true;
                    }
                    else if (words[1] == "fragment")
                    {
                        shaderType = ShaderType::Fragment;
                        buildingShaderSource = true;
                    }
                    else if (words[1] == "geometry")
                    {
                        shaderType = ShaderType::Geometry;
                        buildingShaderSource = true;
                    }
                }
                else if (words[0] == "#end")
                {
                    if (buildingShaderSource)
                    {
                        switch (shaderType)
                        {
                        case ShaderType::Vertex:
                            m_VertexShaderSource = shaderSource;
                            break;
                        case ShaderType::Fragment:
                            m_FragmentShaderSource = shaderSource;
                            break;
                        case ShaderType::Geometry:
                            m_GeometryShaderSource = shaderSource;
                            break;
                        }
                        buildingShaderSource = false;
                        shaderSource.clear();
                    }
                }
                else
                {
                    shaderSource.append(line).append("\n");
                }
            }
        }

        fileStream.close();

    }
    //Loads the loaded shader source into opengl/direct3D
    void Shader::LoadProgram()
    {
        ReleaseProgram();

        if (m_VertexShaderSource.size() != 0)
        {
            m_VertexShaderLoaded = Graphics::CompileShader(m_VertexShader, ShaderType::Vertex, m_VertexShaderSource);
        }
        if (m_FragmentShaderSource.size() != 0)
        {
            m_FragmentShaderLoaded = Graphics::CompileShader(m_FragmentShader, ShaderType::Fragment, m_FragmentShaderSource);
        }
        if (m_GeometryShaderSource.size() != 0)
        {
            m_GeometryShaderLoaded = Graphics::CompileShader(m_GeometryShader, ShaderType::Geometry, m_GeometryShaderSource);
        }

        GLuint shaders[] = { m_VertexShader, m_FragmentShader, m_GeometryShader };
        bool shadersLoaded[] = { m_VertexShaderLoaded, m_FragmentShaderLoaded, m_GeometryShaderLoaded };

        if (!Graphics::LinkShaderProgram(m_ShaderHandle, shaders, shadersLoaded))
        {
            ReleaseProgram();
        }
		else
		{
			m_ShaderHandleLoaded = true;
		}
        //Else Successful Shader Compile

		


        
    } 
    //Loads the shader file then loads the shader source into opengl/direct3D
    void Shader::Load(const std::string & aFilename)
    {
        LoadFile(aFilename);
        LoadProgram();
    }

    void Shader::ReleaseFile()
    {
        m_VertexShaderSource.clear();
        m_FragmentShaderSource.clear();
        m_GeometryShaderSource.clear();
    }
    void Shader::ReleaseProgram()
    {
        //Clean Up
        if (m_VertexShaderLoaded)
        {
            if (m_ShaderHandleLoaded)
            {
                Graphics::DetatchShader(m_ShaderHandle, m_VertexShader);
            }
            Graphics::DeleteShader(m_VertexShader);
            m_VertexShaderLoaded = false;
            m_VertexShader = 0;
        }
        if (m_FragmentShaderLoaded)
        {
            if (m_ShaderHandleLoaded)
            {
                Graphics::DetatchShader(m_ShaderHandle, m_FragmentShader);
            }
            Graphics::DeleteShader(m_FragmentShader);
            m_FragmentShaderLoaded = false;
            m_FragmentShader = 0;
        }
        if (m_GeometryShaderLoaded)
        {
            if (m_ShaderHandleLoaded)
            {
                Graphics::DetatchShader(m_ShaderHandle, m_GeometryShader);
            }
            Graphics::DeleteShader(m_GeometryShader);
            m_GeometryShaderLoaded = false;
            m_GeometryShader = 0;
        }
        if (m_ShaderHandleLoaded)
        {
            Graphics::DeleteProgram(m_ShaderHandle);
            m_ShaderHandleLoaded = false;
            m_ShaderHandle = 0;
        }
    }
    void Shader::Release()
    {
        ReleaseFile();
        ReleaseProgram();
    }

    bool Shader::UseShader()
    {
        if (m_ShaderHandleLoaded)
        {
            Graphics::UseShader(m_ShaderHandle);
            return true;
        }
        return false;
    }

    GLint Shader::GetAttributeLocation(const std::string & aName)
    {
        return glGetAttribLocation(m_ShaderHandle, aName.c_str());
    }
    GLint Shader::GetUniformLocation(const std::string & aName)
    {
        return glGetUniformLocation(m_ShaderHandle, aName.c_str());
    }
}