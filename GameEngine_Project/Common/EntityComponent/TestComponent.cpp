#include "TestComponent.h"
#include <glm\gtc\matrix_transform.hpp>
#include <stddef.h>
#include <Windows.h>




namespace Engine
{
	RDEFINE_CLASS(TestComponent, "")

	TestComponent::TestComponent() : Component()
	{

	}
	TestComponent::~TestComponent()
	{
		ResourceDatabase::UnloadResource("TestMesh");
	}

	void TestComponent::OnRegister()
	{
		DEBUG_LOG("\n\n");
		DEBUG_LOG("Registered %s", GetType().GetName().c_str());
	
		Pointer<Shader> shader = m_Material->GetShader();
		shader->SetName("Default Shader");
		shader->Load("DefaultShader.glsl");

		Pointer<ImageTexture> texture;
		texture->SetName("Wall");
		texture->Load("Wall.png");
		texture->Upload();

		m_Material->SetTexture(texture.Cast<Texture>());

		//m_Mesh.MakeUnique(Geometry::CreateCube(2.0f, 2.0f, 2.0f, Color::Crimson(), Memory::AllocatorType::Pool));
		m_Mesh.MakeUnique(Geometry::CreatePlane(1.0f, 1.0f, Color::Crimson(), Memory::AllocatorType::Pool));


		m_Material->SetName("Default Diffuse");

		

		//Directory dir = Directory::GetCurrent();
		//dir.Back(2);
		//if (dir.Change("Resources\\"))
		//{
		//	DEBUG_LOG("Resource Directory: %s", dir.GetPath().c_str());
		//}
		//else
		//{
		//	DEBUG_LOG("Failed to set resource directory.\nCurrent Directory: %s", dir.GetPath().c_str());
		//}

		//m_TestTexture = ResourceDatabase::LoadTexture("Wall3.png");
		m_TestMesh = ResourceDatabase::LoadMesh("TestMesh.obj");
		
	}
	
	void TestComponent::OnInitialize()
	{
		DEBUG_LOG("Initialized %s", GetType().GetName().c_str());
		Input * input = Input::Instance();
		input->CreateAxis("Vertical", AxisCode::W, AxisCode::S);
		input->CreateAxis("Horizontal", AxisCode::D, AxisCode::A);

		Stream stream;
		BinaryFormatter formatter;

		std::string value = "hello world. This is a crazy sentence";
		std::string result = "";

		formatter.Serialize(value, stream);
		formatter.Deserialize(result, stream);
    
        
		
		bool isAlive = m_TestMesh.IsAlive();
		if (isAlive)
		{
			DEBUG_LOG("Test Mesh is alive");
		}
		else
		{
			DEBUG_LOG("Test Mesh is dead");
		}
	}
	void TestComponent::OnLateInitialize()
	{
		DEBUG_LOG("Late Initialization %s", GetType().GetName().c_str());

		m_Camera = GetComponentInChildren<Camera>();
		m_Renderer = GetComponentInChildren<Renderer>();
		
		if (m_Camera != nullptr)
		{
			m_Camera->SetFieldOfView(45.0f);
			GameObject * gameObject = m_Camera->GetGameObject();
			gameObject->SetPosition(Vector3(0.0f, 1.0f, -3.0f));
			gameObject->LookAt(Vector3::Zero());
		}

		if (m_Renderer != nullptr)
		{
			m_Renderer->SetMaterial(m_Material);
			m_Renderer->SetMesh(m_Mesh);
			GameObject * gameObject = m_Renderer->GetGameObject();
			float scale = 1.0f / 10.0f;
			gameObject->SetScale(Vector3(scale, scale, scale));
		}
        

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
		
		float v = input->GetAxis("Vertical");
		float h = input->GetAxis("Horizontal");

		if (m_Renderer != nullptr)
		{
			GameObject * renderer = m_Renderer->GetGameObject();
			Vector3 rendererPosition = renderer->GetPosition();

			rendererPosition.x += h * Time::GetDeltaTime();
			rendererPosition.z += v * Time::GetDeltaTime();

			renderer->SetPosition(rendererPosition);

			//Quaternion rotation = renderer->GetRotation();
			//rotation *= Quaternion::Euler(Vector3(0.0f, 35.0f * Time::GetDeltaTime(), 0.0f));
			//renderer->SetRotation(rotation);
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
		
	}
	void TestComponent::OnRender()
	{
	
	}
	void TestComponent::OnPostRender()
	{
	
	}
}