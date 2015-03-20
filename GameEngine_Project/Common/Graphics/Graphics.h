#ifndef GAME_ENGINE_GRAPHICS_H
#define GAME_ENGINE_GRAPHICS_H

#include <GL\glew.h>
#include "../BasicTypes.h"
#include "../Math/Math.h"
#include "Color.h"
#include "GraphicEnums.h"
#include "Mesh.h"
#include "PrimitiveShapeBuffer.h"
#include "Shader.h"




namespace Engine
{

    ///This is the manager of graphics operations.
    class Graphics : public object
    {
        CLASS_HEADER(Graphics)
    public:
        // -- Creates / Gets the instance of Graphics
        static Graphics * GetInstance();
        // -- Initializes the Graphics system
        static void Initialize();
        // -- Terminates the Graphics system.
        static void Terminate();

        // -- An example of a draw function for a primitive
        static void DrawPrimitive(const PrimitiveShape & aShape, const Vector3 & aPosition, const Quaternion & aRotation, const Vector3 & aScale);

        // -- Wrapper around OpenGL glUseShader
        static void UseShader(GLuint & aProgramID);
        // -- Wrapped around OpenGL glDetatchShader
        static void DetatchShader(GLuint aProgramID, GLuint aShaderID);
        // -- Wrapper around OpenGL glDeleteShader
        static void DeleteShader(GLuint aShaderID);
        // -- Wrapper around OpenGL glDeleteProgram
        static void DeleteProgram(GLuint aProgramID);
        // -- Wrapper around OpenGL glBindBuffer
        static void BindBuffer(BufferTarget aTarget, GLuint aBuffer);
        // -- Wrapper around OpenGL glBufferData
        static void BufferData(BufferTarget aTarget, GLsizeiptr aSize, GLvoid * aData, BufferMode aMode);
        // -- Creates a shader based on the shader type with the given source. The result is a valid shader handle. Returns false if failed to create shader.
        static bool CompileShader(GLuint & aHandle, const ShaderType & aShaderType, const std::string & aSource);
        // -- Links a shader program with the given shaders. (Vertex, Fragment, Geometry) in that order.
        static bool LinkShaderProgram(GLuint & aProgram, const GLuint aShaders[], const bool aShadersEnabled[]);
        // -- Retrieves the current buffer target bound.
        static BufferTarget GetCurrentBoundTarget();
        // -- Retrieves the current buffer bound.
        static GLuint GetCurrentBoundBuffer();



        // -- Uploads a mesh to OpenGL, use Mesh.Upload instead.
        static bool LoadMesh(Mesh * aMesh, GLuint & aVBO, GLuint & aIBO);

    private:
        // -- Instance of the Graphics singleton
        static Graphics * s_Instance;

        Graphics();
        ~Graphics();
        friend class Engine::Reflection::MetaObject < Graphics > ;

        Color m_BackgroundColor;
        Color m_ForeGroundColor;

        // -- OpenGL
        BufferTarget m_CurrentBoundTarget;
        GLuint m_CurrentBoundBuffer;

        // -- Primitive Buffer Targets
        PrimitiveShapeBuffer * m_PointsBuffer;
        PrimitiveShapeBuffer * m_LinesBuffer;
        PrimitiveShapeBuffer * m_TriangleBuffer;
        PrimitiveShapeBuffer * m_CircleBuffer;
        PrimitiveShapeBuffer * m_RectangleBuffer;
        PrimitiveShapeBuffer * m_PlaneBuffer;
        PrimitiveShapeBuffer * m_CubeBuffer;
        PrimitiveShapeBuffer * m_SphereBuffer;

        PrimitiveShapeBuffer * m_CurrentPrimitiveBuffer;
        void InitializePrimitiveBuffers();
        void ReleasePrimitiveBuffers();
        
        // -- Primitive Buffer Targets End.

        //DrawMesh(Mesh, Material(Shaders/Textures), Position, Rotation, Scale)

        void DrawPoint(const Vector3 & aPosition, const bool & aImmediate, GLsizeiptr aAttributeCount, GLvoid * aAttributes, GLsizeiptr aIndiciesCount, GLvoid * aIndicies);
        
        void DrawPolygon(const PrimitiveMode & aMode, Float32 * aVertices, SInt32 aVertexSize, SInt32 aVertexCount, Float32 * aColors, SInt32 aColorSize);



    };
}

#endif