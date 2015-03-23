#include "TestComponent.h"
#include <glm\gtc\matrix_transform.hpp>



namespace Engine
{
	CLASS_CPP(TestComponent,"")

	TestComponent::TestComponent() : Component()
	{

	}
	TestComponent::~TestComponent()
	{
		Shader * shader = m_Material->GetShader();
		Texture * texture = m_Material->GetTexture();

		texture->Free();
		MEM_POOL_DEALLOC_T(texture, Texture);
		shader->Release();
		MEM_POOL_DEALLOC_T(shader, Shader);
		MEM_POOL_DEALLOC_T(m_Material, Material);
		m_Cube->Release(true);
		MEM_POOL_DEALLOC_T(m_Cube, Mesh);
		m_Plane->Release(true);
		MEM_POOL_DEALLOC_T(m_Plane, Mesh);

		MEM_POOL_DEALLOC_T(m_File, IniFileStream);
	}

	void TestComponent::OnRegister()
	{
		DEBUG_LOG("\n\n");
		DEBUG_LOG("Registered %s", GetType().GetName().c_str());
	}
	
	void TestComponent::OnInitialize()
	{
		DEBUG_LOG("Initialized %s", GetType().GetName().c_str());
		m_Material = MEM_POOL_ALLOC_T(Material);

		Shader * shader = MEM_POOL_ALLOC_T(Shader);
		shader->SetName("Default Shader");
		shader->Load("DefaultShader.glsl");
		shader->ReleaseFile();
		shader->UseShader();


		Texture * texture = MEM_POOL_ALLOC_T(Texture);
		texture->SetName("Wall");
		texture->Load("Wall4.png");
		texture->Upload(true);


		m_Material->SetName("TestComponent");
		m_Material->SetShader(shader);
		m_Material->SetTexture(texture);



		//m_Mesh = Geometry::CreatePlane(10.0f, 10.0f, Color::White(), Memory::AllocatorType::Pool);
		m_Cube = Geometry::CreateCube(1.0f, 1.0f, 1.0f, Color::Crimson(), Memory::AllocatorType::Pool);
		m_Plane = Geometry::CreatePlane(10.0f, 10.0f, Color::White(),Memory::AllocatorType::Pool);


		m_File = MEM_POOL_ALLOC_T(IniFileStream);
		m_File->SetPath("Settings.ini");
		m_File->Read();

		if (!m_File->BindSection("TestComponent"))
		{
			m_File->AddSection("TestComponent");
			m_File->BindSection("TestComponent");
			float defaultPos = 0.0f;

			m_File->AddFloat("xPos", defaultPos);
			m_File->AddFloat("yPos", defaultPos);
			m_File->AddFloat("zPos", defaultPos);

			m_File->AddFloat("xRot", defaultPos);
			m_File->AddFloat("yRot", defaultPos);
			m_File->AddFloat("zRot", defaultPos);

			m_File->Save();
		}

		if (!m_File->BindSection("Color"))
		{
			m_File->AddSection("Color");
			m_File->BindSection("Color");

			Color color = Color(1.0f, 0.5f, 0.25f, 1.0f);

			m_File->AddFloat("red", color.r);
			m_File->AddFloat("green", color.g);
			m_File->AddFloat("blue", color.b);
			m_File->Save();
		}

	}
	void TestComponent::OnLateInitialize()
	{
		DEBUG_LOG("Late Initialization %s", GetType().GetName().c_str());
	}
	
	void TestComponent::OnDestroy()
	{
	
	}
	void TestComponent::OnLateDestroy()
	{
	
	}
	
	void TestComponent::Update()
	{
		Input * input = Input::Instance();
		if (input->GetKeyDown(KeyCode::T))
		{
			OpenGLWindow * currentWindow = Application::GetInstance()->GetCurrentWindow();
			DEBUG_LOG("Aspect Ratio: %f", currentWindow->GetWidth() / currentWindow->GetHeight());
		}

	}
	void TestComponent::LateUpdate()
	{
	
	}
	void TestComponent::FixedUpdate()
	{
	
	}
	
	void TestComponent::OnPreRender()
	{
		m_File->Read();

		Vector3 position = Vector3::Zero();
		Vector3 rotation = Vector3::Zero();
		Color color = Color(0.0f, 0.0f, 0.0f, 1.0f);

		if (m_File->BindSection("TestComponent"))
		{
			position.x = m_File->GetFloat("xPos").GetValue();
			position.y = m_File->GetFloat("yPos").GetValue();
			position.z = m_File->GetFloat("zPos").GetValue();

			rotation.x = m_File->GetFloat("xRot").GetValue();
			rotation.y = m_File->GetFloat("yRot").GetValue();
			rotation.z = m_File->GetFloat("zRot").GetValue();


		}

		if (m_File->BindSection("Color"))
		{
			color.r = m_File->GetFloat("red").GetValue();
			color.g = m_File->GetFloat("green").GetValue();
			color.b = m_File->GetFloat("blue").GetValue();
		}

		Matrix4x4 model;
		Matrix4x4 view;
		Matrix4x4 projection;

		//glFrontFace(GL_CW);

		Graphics::SetBackgroundColor(color);
		//Graphics::DrawMesh(model,view, projection, m_Cube, m_Shader);


		//projection = Matrix4x4::Perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
		projection = Matrix4x4::Perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		view = Matrix4x4::LookAt(Vector3(0.0f, 15, -15), Vector3(0.0f, 0.0f, 0.0f), Vector3::Up());

		model.SetIdentity();
		model.Scale(Vector3::One() * 2.0f);
		model.Translate(Vector3(2.0f,2.0f,-1.0f));
		//Graphics::DrawMesh(model, view, projection, m_Cube, m_Shader);
		DrawCall cubeOne = DrawCall::Create(model, Vector3(0.0f, 15, -15), Vector3(0.0f, 0.0f, 0.0f), projection, m_Cube, m_Material);

		model.SetIdentity();
		model.Scale(Vector3::One() * 2.0f);
		model.Translate(Vector3(-2.0f, 2.0f, -1.0f));
		//Graphics::DrawMesh(model, view, projection, m_Cube, m_Shader);
		DrawCall cubeTwo = DrawCall::Create(model, Vector3(0.0f, 15, -15), Vector3(0.0f, 0.0f, 0.0f), projection, m_Cube, m_Material);

		model.SetIdentity();
		model.Scale(Vector3::One() * 2.0f);
		model.Translate(Vector3(0.0f, 4.0f, 0.0f));
		//Graphics::DrawMesh(model, view, projection, m_Cube, m_Shader);
		DrawCall cubeThree = DrawCall::Create(model, Vector3(0.0f, 15, -15), Vector3(0.0f, 0.0f, 0.0f), projection, m_Cube, m_Material);

		model.SetIdentity();
		model.Scale(Vector3::One() * 1.0f);
		model.Translate(Vector3(0.0f, 0.0f, 0.0f));
		//Graphics::DrawMesh(model, view, projection, m_Plane, m_Shader);
		DrawCall plane = DrawCall::Create(model, Vector3(0.0f, 15, -15), Vector3(0.0f, 0.0f, 0.0f), projection, m_Plane, m_Material);

		Graphics::DrawMesh(cubeOne);
		Graphics::DrawMesh(cubeTwo);
		Graphics::DrawMesh(cubeThree);
		Graphics::DrawMesh(plane);
	}
	void TestComponent::OnRender()
	{
	
	}
	void TestComponent::OnPostRender()
	{
	
	}
}