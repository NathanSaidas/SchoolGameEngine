#include "Graphics.h"
#include <new>
#include "../Engine.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

using namespace Engine::Memory;

namespace Engine
{

	//Describes the attributes of a vertex.
	struct VertexAttribute
	{
		float position[3];
		float normal[3];
		float texCoord[2];
		float color[4];
	};


#ifndef VERTEX_ATTRIB
#define VERTEX_ATTRIB(MEMBER) (void*)offsetof(Engine::VertexAttribute,MEMBER)
#endif 




	RDEFINE_CLASS(Graphics, object)

	Graphics * Graphics::s_Instance = nullptr;
	Graphics::Graphics()
	{

		InitializePrimitiveBuffers();

#ifdef CONFIG_GRAPHICS_SHADOWMAPPING

        Array<Vector3> positions(4);
        positions[0] = Vector3(-1.0f,  1.0f, -0.5f);
        positions[1] = Vector3( 1.0f,  1.0f, -0.5f);
        positions[2] = Vector3( 1.0f, -1.0f, -0.5f);
        positions[3] = Vector3(-1.0f, -1.0f, -0.5f);

        Array<Color> colors(4);
        colors[0] = colors[1] = colors[2] = colors[3] = Color::White();

        Array<Vector2> texCoords(4);
        texCoords[0] = Vector2(1.0f, 1.0f); //top left
        texCoords[1] = Vector2(0.0f, 1.0f); //top right
        texCoords[2] = Vector2(0.0f, 0.0f);
        texCoords[3] = Vector2(1.0f, 0.0f);

        Array<Vector3> normals(4);
        normals[0] = normals[1] = normals[2] = normals[3] = Vector3::Back();


        Array<UInt16> indicies(6);
        indicies[0] = 0;
        indicies[1] = 2;
        indicies[3] = 3;
        indicies[4] = 0;
        indicies[5] = 1;
        indicies[6] = 2;
        

        m_Screen->SetPositions(positions);
        m_Screen->SetColors(colors);
        m_Screen->SetTexCoords(texCoords);
        m_Screen->SetNormals(normals);
        m_Screen->SetIndices(indicies);
        m_Screen->Upload();

        //Pointer<ImageTexture> texture;
        Pointer<Shader> shader;

        shader->Load("DefaultTextureShader.glsl");

        //texture->Load("Wall3.png");
        //texture->Upload();


        m_ScreenMaterial->SetShader(shader);
        //m_ScreenMaterial->SetTexture(texture.Cast<Texture>());

        OpenGLWindow * window = Application::GetDefaultWindow();

        CheckForGLErrors(__FILE__, __LINE__);

		m_ScreenRenderTexture->SetName("Shadow Map");
		m_ScreenRenderTexture->SetFilterMode(FilterMode::Nearest);
		m_ScreenRenderTexture->SetWrapMode(WrapMode::Clamp);
        m_ScreenRenderTexture->Create(window->GetWidth(), window->GetHeight());

        CheckForGLErrors(__FILE__, __LINE__);
#else
        DEBUG_LOG("ShadowMapping is turned off. Check OpenGL version");
#endif
	}

	Graphics::~Graphics()
	{
		ReleasePrimitiveBuffers();
	}

	Graphics * Graphics::GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new Graphics();
		}
		return s_Instance;
	}
	void Graphics::Initialize()
	{
		GetInstance();
	}

	void Graphics::Terminate()
	{
		if (s_Instance != nullptr)
		{
			delete s_Instance;
			s_Instance = nullptr;
		}
	}

	void Graphics::InitializePrimitiveBuffers()
	{
		m_PointsBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();
		m_LinesBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();
		m_TriangleBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();
		m_CircleBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();
		m_RectangleBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();
		m_PlaneBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();
		m_CubeBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();
		m_SphereBuffer = new(MEM_POOL_ALLOC(sizeof(PrimitiveShapeBuffer), __alignof(PrimitiveShapeBuffer)))PrimitiveShapeBuffer();

		m_CurrentPrimitiveBuffer = nullptr;
	}
	void Graphics::ReleasePrimitiveBuffers()
	{
		m_PointsBuffer->~PrimitiveShapeBuffer();
		m_LinesBuffer->~PrimitiveShapeBuffer();
		m_TriangleBuffer->~PrimitiveShapeBuffer();
		m_CircleBuffer->~PrimitiveShapeBuffer();
		m_RectangleBuffer->~PrimitiveShapeBuffer();
		m_PlaneBuffer->~PrimitiveShapeBuffer();
		m_CubeBuffer->~PrimitiveShapeBuffer();
		m_SphereBuffer->~PrimitiveShapeBuffer();

		m_PointsBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_PointsBuffer, sizeof(PrimitiveShapeBuffer));
		m_LinesBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_LinesBuffer, sizeof(PrimitiveShapeBuffer));
		m_TriangleBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_TriangleBuffer, sizeof(PrimitiveShapeBuffer));
		m_CircleBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_CircleBuffer, sizeof(PrimitiveShapeBuffer));
		m_RectangleBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_RectangleBuffer, sizeof(PrimitiveShapeBuffer));
		m_PlaneBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_PlaneBuffer, sizeof(PrimitiveShapeBuffer));
		m_CubeBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_CubeBuffer, sizeof(PrimitiveShapeBuffer));
		m_SphereBuffer = (PrimitiveShapeBuffer*)MEM_POOL_DEALLOC(m_SphereBuffer, sizeof(PrimitiveShapeBuffer));
	}


	void Graphics::Render(Matrix4x4 & aModel, Pointer<Mesh> aMesh, Pointer<Material> aMaterial)
	{
		if (s_Instance != nullptr)
		{
			s_Instance->m_DrawCalls.push_back(DrawCall(aModel, aMesh, aMaterial));
		}
	}

	void Graphics::Render(const Matrix4x4 & aModel, const Matrix4x4 & aView, const Matrix4x4 & aProjection, Mesh * aMesh, Material * aMaterial)
	{
		//TODO(Nathan): Make a draw call with this information for later.

		if (s_Instance != nullptr)
		{
			//s_Instance->m_DrawCalls.push_back(DrawCall::Create(aModel,);
		}


	}
	void Graphics::RenderImmediate(const Matrix4x4 & aModel, const Matrix4x4 & aView, const Matrix4x4 & aProjection, const Pointer<Mesh> & aMesh, const Pointer<Material> & aMaterial)
	{
		//TODO(Nathan): Write the code to draw model.

		if (!aMesh.IsAlive() || !aMaterial.IsAlive())
		{
			return;
		}

		Float32 deltaTime = Time::GetDeltaTime();
		Float32 time = Time::GetTime();

		Matrix4x4 mvp =  aProjection * aView * aModel;

		

		Pointer<Shader> shader = aMaterial->GetShader();
		Pointer<Texture> texture = aMaterial->GetTexture();

		if (!shader.IsAlive())
		{
			return;
		}


		//Check for pre-existing errors
		//CheckForGLErrors(__FILE__, __LINE__);

		if (!aMesh->IsUploaded() || !shader->UseShader())
		{
			return;
		}

		BindBuffer(BufferTarget::Array, aMesh->GetVBO());
		BindBuffer(BufferTarget::ElementArray, aMesh->GetIBO());

		GLint a_Position = shader->GetAttributeLocation("a_Position");
		GLint a_TextureCoordinate = shader->GetAttributeLocation("a_TexCoords");
		GLint a_Normal = shader->GetAttributeLocation("a_Normal");
		GLint a_Color = shader->GetAttributeLocation("a_Color");

		GLint u_MVP = shader->GetUniformLocation("u_MVP");
		GLint u_Model = shader->GetUniformLocation("u_Model");
		GLint u_View = shader->GetUniformLocation("u_View");
		GLint u_Projection = shader->GetUniformLocation("u_Projection");
		GLint u_Time = shader->GetUniformLocation("u_Time");
		GLint u_DeltaTime = shader->GetUniformLocation("u_DeltaTime");
        GLint u_Texture = shader->GetUniformLocation("u_Texture");

		EnableVertexAttrib(a_Position, 3, VERTEX_ATTRIB(position));
		EnableVertexAttrib(a_TextureCoordinate, 2, VERTEX_ATTRIB(texCoord));
		EnableVertexAttrib(a_Normal, 3, VERTEX_ATTRIB(normal));
		EnableVertexAttrib(a_Color, 4, VERTEX_ATTRIB(color));

		SetMatrix(u_MVP, mvp);
		SetMatrix(u_Model, aModel);
		SetMatrix(u_View, aView);
		SetMatrix(u_Projection, aProjection);
		SetFloat(u_Time, time);
		SetFloat(u_DeltaTime, deltaTime);
        SetTexture(u_Texture, 0, texture);

		glDrawElements((GLenum)PrimitiveMode::Triangles, aMesh->GetIndexCount(), GL_UNSIGNED_SHORT, 0);

		DisableVertexAttrib(a_Position);
		DisableVertexAttrib(a_TextureCoordinate);
		DisableVertexAttrib(a_Normal);
		DisableVertexAttrib(a_Color);

		BindBuffer(BufferTarget::Array, 0);
		BindBuffer(BufferTarget::ElementArray, 0);
		glUseProgram(0);

	}

	void Graphics::UseShader(GLuint & aProgramID)
	{
		glUseProgram(aProgramID);
	}
	void Graphics::DetatchShader(GLuint aProgramID, GLuint aShaderID)
	{
		glDetachShader(aProgramID, aShaderID);
	}
	void Graphics::DeleteShader(GLuint aShaderID)
	{
		glDeleteShader(aShaderID);
	}
	void Graphics::DeleteProgram(GLuint aProgramID)
	{
		glDeleteProgram(aProgramID);
	}

	void Graphics::BindBuffer(BufferTarget aTarget, GLuint aBuffer)
	{
		GetInstance()->m_CurrentBoundTarget = aTarget;
		GetInstance()->m_CurrentBoundBuffer = aBuffer;
		glBindBuffer((GLenum)aTarget, aBuffer);
	}

	void Graphics::BufferData(BufferTarget aTarget, GLsizeiptr aSize, GLvoid * aData, BufferMode aMode)
	{
		glBufferData((GLenum)aTarget, aSize, aData, (GLenum)aMode);
	}

	bool Graphics::CompileShader(GLuint & aHandle, const ShaderType & aShaderType, const std::string & aSource)
	{
		std::string shaderTypename;
		switch (aShaderType)
		{
		case ShaderType::Vertex:
			shaderTypename = "Vertex";
			break;
		case ShaderType::Fragment:
			shaderTypename = "Fragment";
			break;
		case ShaderType::Geometry:
			shaderTypename = "Geometry";
			break;
		default:
			DEBUG_LOG("Unsupported shader type %u", (unsigned int)aShaderType);
			return false;
		}


		aHandle = glCreateShader((GLenum)aShaderType);
		char * src = (char *)aSource.c_str();
		glShaderSource(aHandle, 1, (const char **)&src, NULL);
		glCompileShader(aHandle);



		//DEBUG_LOG("Attempting to compile shader %s.\nSource:\n%s", shaderTypename.c_str(), aSource.c_str());

		int status = 0;
		glGetShaderiv(aHandle, GL_COMPILE_STATUS, &status);
		if (status == 0)
		{
			int logLength = 0;
			glGetShaderiv(aHandle, GL_INFO_LOG_LENGTH, &logLength);
			char * infobuffer = new char[logLength + 1];
			glGetShaderInfoLog(aHandle, logLength + 1, 0, infobuffer);
			DEBUG_LOG("Shader Error: %s", infobuffer);
			delete infobuffer;
			glDeleteShader(aHandle);
			aHandle = 0;
			return false;
		}
		return true;
	}
	bool Graphics::LinkShaderProgram(GLuint & aProgram, const GLuint aShaders[], const bool aShadersEnabled[])
	{
		aProgram = glCreateProgram();

		if (aShadersEnabled[0])
		{
			glAttachShader(aProgram, aShaders[0]);
		}
		if (aShadersEnabled[1])
		{
			glAttachShader(aProgram, aShaders[1]);
		}
		if (aShadersEnabled[2])
		{
			glAttachShader(aProgram, aShaders[2]);
		}

		glLinkProgram(aProgram);

		int status = 0;
		glGetProgramiv(aProgram, GL_LINK_STATUS, &status);
		if (status == 0)
		{
			int logLength = 0;
			glGetProgramiv(aProgram, GL_INFO_LOG_LENGTH, &logLength);
			char * infobuffer = new char[logLength + 1];
			glGetProgramInfoLog(aProgram, logLength + 1, 0, infobuffer);
			DEBUG_LOG("Shader Program Error: %s", infobuffer);
			delete infobuffer;
			return false;
		}
		return true;
	}
	BufferTarget Graphics::GetCurrentBoundTarget()
	{
		return GetInstance()->m_CurrentBoundTarget;
	}
	GLuint Graphics::GetCurrentBoundBuffer()
	{
		return GetInstance()->m_CurrentBoundBuffer;
	}
	void Graphics::Clear()
	{

		Color color;
		if (s_Instance != nullptr)
		{
			color = s_Instance->m_BackgroundColor;
		}
		glClearColor(color.r, color.g, color.b, color.a);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	void Graphics::SetBackgroundColor(const Color & aColor)
	{
		if (s_Instance != nullptr)
		{
			s_Instance->m_BackgroundColor = aColor;
		}
	}

	bool Graphics::LoadMesh(Mesh * aMesh, GLuint & aVBO, GLuint & aIBO)
	{
		//TODO: Load the mesh data into OpenGL
		if (aMesh == nullptr)
		{
			return false;
		}

		if (aMesh->IsUploaded())
		{
			DEBUG_LOG("Cannot upload the mesh. It's already uploaded. Release the resources before attempting to upload.");
			return false;
		}

		Array<Vector3> positions = aMesh->GetPositions();
		Array<Vector3> normals = aMesh->GetNormals();
		Array<Vector2> texCoords = aMesh->GetTexCoords();
		Array<Color> colors = aMesh->GetColors();
		Array<UInt16> indices = aMesh->GetIndicies();

		UInt32 count = positions.GetCount();
		if (count != normals.GetCount() ||
			count != texCoords.GetCount() ||
			count != colors.GetCount()
			)
		{
			DEBUG_LOG("There is a different number of attributes in this mesh %s", aMesh->GetName().c_str());
			return false;
		}

		Array<VertexAttribute> attributes;
		attributes.Allocate(count);

		for (unsigned int i = 0; i < count; i++)
		{
			//Position
			attributes[i].position[0] = positions[i].x;
			attributes[i].position[1] = positions[i].y;
			attributes[i].position[2] = positions[i].z;

			//Normals
			attributes[i].normal[0] = normals[i].x;
			attributes[i].normal[1] = normals[i].y;
			attributes[i].normal[2] = normals[i].z;

			//Tex Coords
			attributes[i].texCoord[0] = texCoords[i].x;
			attributes[i].texCoord[1] = texCoords[i].y;

			//Colors
			attributes[i].color[0] = colors[i].r;
			attributes[i].color[1] = colors[i].g;
			attributes[i].color[2] = colors[i].b;
			attributes[i].color[3] = colors[i].a;
		}

		//Send to OpenGL
		glGenBuffers(1, &aVBO);
		glBindBuffer((GLenum)BufferTarget::Array, aVBO);
		glBufferData((GLenum)BufferTarget::Array, sizeof(VertexAttribute)* count, attributes.GetElements(), (GLenum)BufferMode::StaticDraw);
		glBindBuffer((GLenum)BufferTarget::Array, 0);

		glGenBuffers(1, &aIBO);
		glBindBuffer((GLenum)BufferTarget::ElementArray, aIBO);
		glBufferData((GLenum)BufferTarget::ElementArray, sizeof(GLshort)* indices.GetCount(), indices.GetElements(), (GLenum)BufferMode::StaticDraw);
		glBindBuffer((GLenum)BufferTarget::ElementArray, 0);

		return true;
	}

	void Graphics::Render(Scene * aScene)
	{
		if (s_Instance != nullptr)
		{
			s_Instance->RenderScene(aScene);
		}
		return;
	}

	bool Graphics::CheckForGLErrors(const char* file, int line)
	{
		GLenum errorID = GL_NO_ERROR;
		char* errorStr;
		int errorCount = 0;

		while ((errorID = glGetError()) != GL_NO_ERROR)
		{
			errorCount++;

			switch (errorID)
			{
			case GL_INVALID_ENUM:
				errorStr = "GL_INVALID_ENUM";
				break;

			case GL_INVALID_VALUE:
				errorStr = "GL_INVALID_VALUE";
				break;

			case GL_INVALID_OPERATION:
				errorStr = "GL_INVALID_OPERATION";
				break;

			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;

			case GL_OUT_OF_MEMORY:
				errorStr = "GL_OUT_OF_MEMORY";
				break;

			default:
				errorStr = "Unknown GL message type.";
				break;
			}

			DEBUG_LOG("GLError -> %d - %s - %d - %s(%d)\n", errorID, errorStr, errorCount, file, line);
		}

		return(errorCount > 0 ? true : false);
	}


	void Graphics::RegisterCamera(Camera * aCamera)
	{
		if (s_Instance != nullptr && aCamera != nullptr && !aCamera->IsRegistered())
		{
			s_Instance->m_RenderCameras.push_back(aCamera);
		}
	}
	void Graphics::UnregisterCamera(Camera * aCamera)
	{
		if (s_Instance != nullptr)
		{
			Utilities::Remove<Camera*>(s_Instance->m_RenderCameras, aCamera);
		}
	}

	void Graphics::RenderScene(Scene * aScene)
	{
		if (aScene == nullptr)
		{
			//Nothing to render.
			return;
		}
		//Gather Geometry / Drawcalls

        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);

#ifdef CONFIG_GRAPHICS_SHADOWMAPPING
        glBindFramebuffer(GL_FRAMEBUFFER, m_ScreenRenderTexture->GetFBOHandle());
#endif
        Clear();

		aScene->PreRender();
		for (std::vector<Camera*>::iterator it = m_RenderCameras.begin(); it != m_RenderCameras.end(); it++)
		{
			RenderCamera(aScene, *it);
		}
#ifdef CONFIG_GRAPHICS_SHADOWMAPPING
        glBindFramebuffer(GL_FRAMEBUFFER, 0); 
#endif
       

		aScene->Render();
		m_RenderCameras.clear();
		m_DrawCalls.clear();
		
#ifdef CONFIG_GRAPHICS_SHADOWMAPPING
        Clear();
        RenderScreen();
#endif
        
        aScene->PostRender();


	}

	void Graphics::RenderCamera(Scene * aScene, Camera * aCamera)
	{
		Matrix4x4 viewMatrix = aCamera->GetViewMatrix();
		Matrix4x4 projectionMatrix = aCamera->GetProjectionMatrix();

		Float32 x, y, w, h;

		aCamera->GetViewport(x, y, w, h);

		glViewport((GLint)x, (GLint)y, (GLint)w, (GLint)h);

		for (std::vector<DrawCall>::iterator it = m_DrawCalls.begin(); it != m_DrawCalls.end(); it++)
		{
			DrawCall & drawCall = *it;
			RenderImmediate(drawCall.model, viewMatrix, projectionMatrix, drawCall.mesh, drawCall.material);
		}


	}

	void Graphics::EnableVertexAttrib(GLint aLocation, GLint aSize, const GLvoid * aOffset)
	{
		if (aLocation != -1)
		{
			glVertexAttribPointer(aLocation, aSize, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), aOffset);
			glEnableVertexAttribArray(aLocation);
		}
	}
	void Graphics::DisableVertexAttrib(GLint aLocation)
	{
		if (aLocation != -1)
		{
			glDisableVertexAttribArray(aLocation);
		}
	}

	void Graphics::SetMatrix(GLint aLocation, const Matrix4x4 & aMatrix)
	{
		if (aLocation != -1)
		{
			glUniformMatrix4fv(aLocation, 1, GL_FALSE, &(aMatrix.Raw())[0][0]);
		}
	}
	void Graphics::SetFloat(GLint aLocation, Float32 aFloat)
	{
		if (aLocation != -1)
		{
			glUniform1f(aLocation, aFloat);
		}
	}
	void Graphics::SetTexture(GLint aLocation, GLenum aUnit, Pointer<Texture> aTexture)
	{
		if (aLocation != -1)
		{
            if (aTexture.IsAlive() && aTexture->IsUploaded())
            {
                glActiveTexture(GL_TEXTURE0 + aUnit);
                glBindTexture(GL_TEXTURE_2D, aTexture->GetHandle());
                glUniform1i(aLocation, aUnit);
            }
		}
	}

    void Graphics::SetTexture(GLint aLocation, GLenum aUnit, Pointer<RenderTexture> aTexture)
    {
        if (aLocation != -1)
        {
            if (aTexture.IsAlive() && aTexture->IsUploaded())
            {
                glActiveTexture(GL_TEXTURE0 + aUnit);
                glBindTexture(GL_TEXTURE_2D, aTexture->GetDepthHandle());
                glUniform1i(aLocation, aUnit);
            }
        }
    }

    void Graphics::RenderScreen()
    {
        Matrix4x4 identity = Matrix4x4::Identity();

        BindBuffer(BufferTarget::Array, m_Screen->GetVBO());
        BindBuffer(BufferTarget::ElementArray, m_Screen->GetIBO());

        Pointer<Shader> shader = m_ScreenMaterial->GetShader();
        Pointer<Texture> texture = m_ScreenMaterial->GetTexture();

        if (!shader.IsAlive())
        {
            return;
        }

        if (!m_Screen->IsUploaded() || !shader->UseShader())
        {
            return;
        }

        GLint a_Position = shader->GetAttributeLocation("a_Position");
        GLint a_TextureCoordinate = shader->GetAttributeLocation("a_TexCoords");
        GLint a_Normal = shader->GetAttributeLocation("a_Normal");
        GLint a_Color = shader->GetAttributeLocation("a_Color");

        GLint u_MVP = shader->GetUniformLocation("u_MVP");
        GLint u_Model = shader->GetUniformLocation("u_Model");
        GLint u_View = shader->GetUniformLocation("u_View");
        GLint u_Projection = shader->GetUniformLocation("u_Projection");
        GLint u_Time = shader->GetUniformLocation("u_Time");
        GLint u_DeltaTime = shader->GetUniformLocation("u_DeltaTime");
        GLint u_Texture = shader->GetUniformLocation("u_Texture");

        EnableVertexAttrib(a_Position, 3, VERTEX_ATTRIB(position));
        EnableVertexAttrib(a_TextureCoordinate, 2, VERTEX_ATTRIB(texCoord));
        EnableVertexAttrib(a_Normal, 3, VERTEX_ATTRIB(normal));
        EnableVertexAttrib(a_Color, 4, VERTEX_ATTRIB(color));

        SetMatrix(u_MVP, identity);
        SetMatrix(u_Model, identity);
        SetMatrix(u_View, identity);
        SetMatrix(u_Projection, identity);
        SetFloat(u_Time, Time::GetTime());
        SetFloat(u_DeltaTime, Time::GetDeltaTime());
        SetTexture(u_Texture, 0, m_ScreenRenderTexture);
        //SetTexture(u_Texture,0, texture);

        //glDrawElements((GLenum)PrimitiveMode::TriangleFans, m_Screen->GetIndexCount(), GL_UNSIGNED_SHORT, 0);

        glDrawArrays((GLenum)PrimitiveMode::TriangleFans, 0, 4);

        DisableVertexAttrib(a_Position);
        DisableVertexAttrib(a_TextureCoordinate);
        DisableVertexAttrib(a_Normal);
        DisableVertexAttrib(a_Color);

        BindBuffer(BufferTarget::Array, 0);
        BindBuffer(BufferTarget::ElementArray, 0);
        glUseProgram(0);

    }
}