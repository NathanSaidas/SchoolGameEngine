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



    CLASS_CPP(Graphics, object)

    Graphics * Graphics::s_Instance = nullptr;
    Graphics::Graphics()
    {
        InitializePrimitiveBuffers();
		m_ShadowMapTexture = MEM_POOL_ALLOC_T(RenderTexture);
		m_DefaultShader = MEM_POOL_ALLOC_T(Shader);
		m_ShadowMapShader = MEM_POOL_ALLOC_T(Shader);
		m_DepthShader = MEM_POOL_ALLOC_T(Shader);
		m_FrameBufferMesh = Geometry::CreatePlane(0.5f, 0.5f, Color::White(), AllocatorType::Pool);

		m_DefaultShader->Load("CustomTest.glsl");
		m_ShadowMapShader->Load("ShadowMap.glsl");
		m_DepthShader->Load("DepthShader.glsl");
		m_ShadowMapTexture->Create(1024, 1024);

		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);



    }

    Graphics::~Graphics()
    {
        
		m_DefaultShader->Release();
		m_ShadowMapShader->Release();
		m_ShadowMapTexture->Release();
		m_DepthShader->Release();
		MEM_POOL_DEALLOC_T(m_DefaultShader, Shader);
		MEM_POOL_DEALLOC_T(m_ShadowMapShader, Shader);
		MEM_POOL_DEALLOC_T(m_DepthShader, Shader);
		MEM_POOL_DEALLOC_T(m_ShadowMapTexture, RenderTexture);
		MEM_POOL_DEALLOC_T(m_FrameBufferMesh, Mesh);
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

    void Graphics::DrawPoint(const Vector3 & aPosition, const bool & aImmediate, GLsizeiptr aAttributeCount, GLvoid * aAttributes, GLsizeiptr aIndiciesCount, GLvoid * aIndicies)
    {
        //TODO: Initialize variables

        float deltaTime = 0.0f;
        float time = 0.0f;

        Matrix4x4 model;
        Matrix4x4 view;
        Matrix4x4 projection;

        Matrix4x4 mvp = model * view * projection;

        //Bind Material (Textures / Shaders )


        //Bind Shader
        Shader shader; //Get the shader from the material.

        if (!shader.UseShader())
        {
            DEBUG_LOG("Failed to bind shader %s. Shader was not initialized.", shader.GetName());
            return;
        }

        //Bind VBO / IBO (Primitive Shape Buffer)
        m_PointsBuffer->BindData(aAttributeCount, aAttributes, aIndiciesCount, aIndicies);
        BindBuffer(BufferTarget::Array, m_PointsBuffer->GetVBO());
        BindBuffer(BufferTarget::ElementArray, m_PointsBuffer->GetIBO());


        //Get Shader Attributes
        GLint a_Position = shader.GetAttributeLocation("a_Position");
        GLint a_TextureCoordinate = shader.GetAttributeLocation("a_TexCoords");
        GLint a_Normal = shader.GetAttributeLocation("a_Normal");
        GLint a_Color = shader.GetAttributeLocation("a_Color");

        //Get Shader Uniforms
        GLint u_MVP = shader.GetUniformLocation("u_MVP");
        GLint u_Model = shader.GetUniformLocation("u_Model");
        GLint u_ObjectSpace = shader.GetUniformLocation("u_ObjectSpace");
        GLint u_Time = shader.GetUniformLocation("u_Time");
        GLint u_DeltaTime = shader.GetUniformLocation("u_DeltaTime");
		GLint u_DirectionalLight = shader.GetUniformLocation("u_DirectionalLight");


        //Bind Textures
        


        //Bind Position Attributes
        if (a_Position != -1)
        {
            glVertexAttribPointer(a_Position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, position));
            glEnableVertexAttribArray(a_Position);
        }
        //Bind Texture Coordinate Attributes
        if (a_TextureCoordinate != -1)
        {
            glVertexAttribPointer(a_TextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, texCoord));
            glEnableVertexAttribArray(a_TextureCoordinate);
        }
        //Bind Normal Attributes
        if (a_Normal != -1)
        {
            glVertexAttribPointer(a_Normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, normal));
            glEnableVertexAttribArray(a_Normal);
        }
        //Bind Color Attributes
        if (a_Color != -1)
        {
            glVertexAttribPointer(a_Color, 4, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, color));
            glEnableVertexAttribArray(a_Color);
        }

        //Bind MVP Matrix Uniform
        if (u_MVP != -1)
        {
            glUniformMatrix4fv(u_MVP, 1, GL_FALSE, (GLfloat*)&mvp.Raw()[0][0]);
        }
        //Bind Model Matrix Uniform
        if (u_Model != -1)
        {
            glUniformMatrix4fv(u_Model, 1, GL_FALSE, (GLfloat*)&model.Raw()[0][0]);
        }
        //Bind Object_Space Matrix Uniform
        if (u_ObjectSpace != -1)
        {
            Matrix4x4 objectSpace = model * view;
            glUniformMatrix4fv(u_ObjectSpace, 1, GL_FALSE, (GLfloat*)&objectSpace.Raw()[0][0]);
        }
        //Bind Time Uniform
        if (u_Time != -1)
        {
            glUniform1f(u_Time, time);
        }
        //Bind Delta Time Uniform
        if (u_DeltaTime != -1)
        {
            glUniform1f(u_DeltaTime, deltaTime);
        }

		//glLineWidth(2.0f);
        //Make Draw Call
        //glDrawElements((GLenum)PrimitiveMode::Triangles, aIndiciesCount, GL_UNSIGNED_SHORT, 0);
		glDrawElements((GLenum)PrimitiveMode::Lines, aIndiciesCount, GL_UNSIGNED_SHORT, 0);

        //Unbind Color Attributes
        if (a_Color != -1)
        {
            glDisableVertexAttribArray(a_Color);
        }
        //Unbind Normal Attributes
        if (a_Normal != -1)
        {
            glDisableVertexAttribArray(a_Normal);
        }
        //Unbind Texture Attributes
        if (a_TextureCoordinate != -1)
        {
            glDisableVertexAttribArray(a_TextureCoordinate);
        }
        //Unbind Position Attributes
        if (a_Position != -1)
        {
            glDisableVertexAttribArray(a_Position);
        }
        //Unbind Textures

        //Unbind VBO/IBO
        BindBuffer(BufferTarget::Array, 0);
        BindBuffer(BufferTarget::ElementArray, 0);

        //Unbind Material
        glUseProgram(0);

    }

    void Graphics::DrawPolygon(const PrimitiveMode & aMode, Float32 * aVertices, SInt32 aVertexSize, SInt32 aVertexCount, Float32 * aColors, SInt32 aColorSize)
    {
        

    }
	void Graphics::DrawPrimitive(const PrimitiveShape & aShape, const Vector3 & aPosition, const Quaternion & aRotation, const Vector3 & aScale)
	{

	}
	void Graphics::DrawMesh(const DrawCall & aDrawCall)
	{
		if (s_Instance != nullptr)
		{
			s_Instance->m_DrawCalls.push_back(aDrawCall);
		}
	}

	void Graphics::DrawMesh(const Matrix4x4 & aModel, const Matrix4x4 & aView, const Matrix4x4 & aProjection, Mesh * aMesh, Material * aMaterial)
	{
		if (aMaterial == nullptr || 
			aMesh == nullptr ||
			aMaterial->GetShader() == nullptr)
		{
			return;
		}

		Float32 deltaTime = Time::GetDeltaTime();
		Float32 time = Time::GetTime();

		Matrix4x4 view = aView;
		Matrix4x4 mvp = aProjection * view * aModel;
		Matrix4x4 objectSpace = aModel * view;

		RenderTexture * shadowMap = s_Instance->m_ShadowMapTexture;
		Shader * shader = aMaterial->GetShader();
		Texture * texture = aMaterial->GetTexture();

		if (texture == nullptr)
		{
			shader = s_Instance->m_DepthShader;
		}

		if (!shader->UseShader())
		{
			DEBUG_LOG("Failed to bind shader %s. Shader was not initialized.", shader->GetName());
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
		GLint u_ObjectSpace = shader->GetUniformLocation("u_ObjectSpace");
		GLint u_Time = shader->GetUniformLocation("u_Time");
		GLint u_DeltaTime = shader->GetUniformLocation("u_DeltaTime");

		//Shadow Map & Default Shader
		GLint u_Texture = shader->GetUniformLocation("u_Texture");

		//Default Shader
		GLint u_ShadowMap = shader->GetUniformLocation("u_ShadowMap");
		GLint u_DirectionalLight = shader->GetUniformLocation("u_DirectionalLight");



		//Bind Position Attributes
		if (a_Position != -1)
		{
			glVertexAttribPointer(a_Position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, position));
			glEnableVertexAttribArray(a_Position);
		}
		//Bind Texture Coordinate Attributes
		if (a_TextureCoordinate != -1)
		{
			glVertexAttribPointer(a_TextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, texCoord));
			glEnableVertexAttribArray(a_TextureCoordinate);
		}
		//Bind Normal Attributes
		if (a_Normal != -1)
		{
			glVertexAttribPointer(a_Normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, normal));
			glEnableVertexAttribArray(a_Normal);
		}
		//Bind Color Attributes
		if (a_Color != -1)
		{
			glVertexAttribPointer(a_Color, 4, GL_FLOAT, GL_FALSE, sizeof(VertexAttribute), (void*)offsetof(VertexAttribute, color));
			glEnableVertexAttribArray(a_Color);
		}

		//Bind MVP Matrix Uniform
		if (u_MVP != -1)
		{
			glUniformMatrix4fv(u_MVP, 1, GL_FALSE, &mvp[0][0]);
		}
		//Bind Model Matrix Uniform
		if (u_Model != -1)
		{
			glUniformMatrix4fv(u_Model, 1, GL_FALSE, (GLfloat*)&aModel.Raw()[0][0]);
		}
		//Bind Object_Space Matrix Uniform
		if (u_ObjectSpace != -1)
		{
			glUniformMatrix4fv(u_ObjectSpace, 1, GL_FALSE, (GLfloat*)&objectSpace.Raw()[0][0]);
		}
		//Bind Time Uniform
		if (u_Time != -1)
		{
			glUniform1f(u_Time, time);
		}
		//Bind Delta Time Uniform
		if (u_DeltaTime != -1)
		{
			glUniform1f(u_DeltaTime, deltaTime);
		}
		if (u_Texture != -1)
		{
			if (texture == nullptr)
			{
				 
				 glActiveTexture(GL_TEXTURE0);
				 glBindTexture(GL_TEXTURE_2D, s_Instance->m_ShadowMapTexture->GetDepthHandle());
				 glUniform1i(u_Texture, 0);
			}
			else
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
				glUniform1i(u_Texture, 0);
			}
			
		}

		if (u_DirectionalLight != -1)
		{
			Matrix4x4 dirLightView = view; 
			Matrix4x4 dirLightMVP = aProjection * dirLightView * aModel;
			glUniformMatrix4fv(u_DirectionalLight, 1, GL_FALSE, &dirLightMVP[0][0]);
		}

		if (u_ShadowMap != -1)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, shadowMap->GetDepthHandle());
			glUniform1i(u_ShadowMap, 1);
		}


		//Make Draw Call
		glDrawElements((GLenum)PrimitiveMode::Triangles, aMesh->GetIndexCount(), GL_UNSIGNED_SHORT, 0);
		//Unbind Color Attributes
		if (a_Color != -1)
		{
			glDisableVertexAttribArray(a_Color);
		}
		//Unbind Normal Attributes
		if (a_Normal != -1)
		{
			glDisableVertexAttribArray(a_Normal);
		}
		//Unbind Texture Attributes
		if (a_TextureCoordinate != -1)
		{
			glDisableVertexAttribArray(a_TextureCoordinate);
		}
		//Unbind Position Attributes
		if (a_Position != -1)
		{
			glDisableVertexAttribArray(a_Position);
		}

		if (u_Texture != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if (u_ShadowMap != -1)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

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
        if (count != normals.GetCount()     || 
            count != texCoords.GetCount()   || 
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
        glBufferData((GLenum)BufferTarget::Array, sizeof(VertexAttribute) * count, attributes.GetElements(), (GLenum)BufferMode::StaticDraw);
        glBindBuffer((GLenum)BufferTarget::Array, 0);

        glGenBuffers(1, &aIBO);
        glBindBuffer((GLenum)BufferTarget::ElementArray, aIBO);
        glBufferData((GLenum)BufferTarget::ElementArray, sizeof(GLshort) * indices.GetCount(), indices.GetElements(), (GLenum)BufferMode::StaticDraw);
        glBindBuffer((GLenum)BufferTarget::ElementArray, 0);

        return true;
    }

	void Graphics::Render()
	{
		OpenGLWindow * currentWindow = Application::GetInstance()->GetCurrentWindow();
		RenderTexture * shadowMap = s_Instance->m_ShadowMapTexture;

		glBindFramebuffer(GL_FRAMEBUFFER, shadowMap->GetFBOHandle());
		glViewport(0, 0, shadowMap->GetWidth(), shadowMap->GetHeight());

		Clear();
		
		Material material;
		material.SetShader(s_Instance->m_ShadowMapShader);


		//Specify the ViewPort
		for (std::vector<DrawCall>::iterator it = s_Instance->m_DrawCalls.begin(); it != s_Instance->m_DrawCalls.end(); it++)
		{
			DrawCall call = *it;
			material.SetTexture(call.material->GetTexture());
			DrawMesh(call.model, call.view, call.projection, call.mesh, &material);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		material.SetShader(s_Instance->m_DefaultShader);
		glViewport(0, 0, currentWindow->GetWidth(), currentWindow->GetHeight());

		for (std::vector<DrawCall>::iterator it = s_Instance->m_DrawCalls.begin(); it != s_Instance->m_DrawCalls.end(); it++)
		{
			DrawCall call = *it;
			material.SetTexture(call.material->GetTexture());
			DrawMesh(call.model, call.view, call.projection, call.mesh, &material);
		}

		
		s_Instance->m_DrawCalls.clear();

		Matrix4x4 model;
		model.SetIdentity();
		model.Scale(Vector3(0.5f,0.65f, 1.0f));
		model.Rotate(Vector3(90.0f, 0.0f, 0.0f));

		model[3][0] = -0.75f;
		model[3][1] = 0.75f;
		model[3][2] = 0.0;

		
		
		Matrix4x4 identity;
		identity.SetIdentity();

		material.SetTexture(nullptr);


		DrawMesh(model, identity, identity, s_Instance->m_FrameBufferMesh, &material);
		CheckForGLErrors(__FILE__, __LINE__);

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
}