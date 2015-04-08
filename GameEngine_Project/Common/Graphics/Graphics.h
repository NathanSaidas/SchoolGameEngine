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
#include "Geometry.h"
#include "DrawCall.h"
#include "RenderTexture.h"
#include "Texture.h"
#include "ImageTexture.h"
#include "Material.h"

#define CONFIG_GRAPHICS_SHADOWMAPPING



namespace Engine
{
	class Camera;
	class Scene;

    ///This is the manager of graphics operations.
    class Graphics : public object
    {
		RDECLARE_CLASS(Graphics)
    public:
        // -- Creates / Gets the instance of Graphics
        static Graphics * GetInstance();
        // -- Initializes the Graphics system
        static void Initialize();
        // -- Terminates the Graphics system.
        static void Terminate();


		static void Render(Matrix4x4 & aModel, Pointer<Mesh> aMesh, Pointer<Material> aMaterial);
		static void Render(const Matrix4x4 & aModel, const Matrix4x4 & aView, const Matrix4x4 & aProjection, Mesh * aMesh, Material * aMaterial);
		static void RenderImmediate(const Matrix4x4 & aModel, const Matrix4x4 & aView, const Matrix4x4 & aProjection, const Pointer<Mesh> & aMesh, const Pointer<Material> & aMaterial);

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
		// -- Links a shader program.
		static bool LinkShaderProgram(GLuint & aProgram, const GLuint aShaders[], const bool aShadersEnabled[]);
        // -- Links a shader program with the given shaders. (Vertex, Fragment, Geometry) in 
        static BufferTarget GetCurrentBoundTarget();
        // -- Retrieves the current buffer bound.
        static GLuint GetCurrentBoundBuffer();

		static void Clear();
		static void SetBackgroundColor(const Color & aColor);

        // -- Uploads a mesh to OpenGL, use Mesh.Upload instead.
        static bool LoadMesh(Mesh * aMesh, GLuint & aVBO, GLuint & aIBO);

		static void Render(Scene * aScene);
		static bool CheckForGLErrors(const char* file = __FILE__, int line = __LINE__);
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

		// -- Draw Call Stuffs
		std::vector<DrawCall> m_DrawCalls;

		
		static void RegisterCamera(Camera * aCamera);
		static void UnregisterCamera(Camera * aCamera);
		std::vector<Camera*> m_RenderCameras;

		void RenderScene(Scene * aScene);
		void RenderCamera(Scene * aScene, Camera * aCamera);

		static void EnableVertexAttrib(GLint aLocation, GLint aSize, const GLvoid * aOffset);
		static void DisableVertexAttrib(GLint aLocation);
		static void SetMatrix(GLint aLocation, const Matrix4x4 & aMatrix);
		static void SetFloat(GLint aLocation, Float32 aFloat);
		static void SetTexture(GLint aLocation, GLenum aUnit, Pointer<Texture> aTexture);
        static void SetTexture(GLint aLocation, GLenum aUnit, Pointer<RenderTexture> aTexture);

		friend Camera;


        //-1, 1----1, 1
        //  |       |
        //  |       |
        //-1,-1----1,-1

        //0.0
        //0.0
        Pointer<Mesh> m_Screen;
        Pointer<Material> m_ScreenMaterial;
        Pointer<RenderTexture> m_ScreenRenderTexture;

        void RenderScreen();
    };

	TYPE_DEFINE(Graphics)
}

#endif