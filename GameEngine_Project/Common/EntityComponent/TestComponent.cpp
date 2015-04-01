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

	}

	void TestComponent::OnRegister()
	{
		DEBUG_LOG("\n\n");
		DEBUG_LOG("Registered %s", GetType().GetName().c_str());
	
		Pointer<Shader> shader = m_Material->GetShader();
		shader->SetName("Default Shader");
		shader->Load("DefaultShader.glsl");

		Pointer<Texture> texture = m_Material->GetTexture();
		texture->SetName("Wall");
		texture->Load("Wall.png");
		texture->Upload();

		//m_Mesh.MakeUnique(Geometry::CreateCube(2.0f, 2.0f, 2.0f, Color::Crimson(), Memory::AllocatorType::Pool));
		m_Mesh.MakeUnique(Geometry::CreatePlane(1.0f, 1.0f, Color::Crimson(), Memory::AllocatorType::Pool));


		m_Material->SetName("Default Diffuse");

	}
	
	void TestComponent::OnInitialize()
	{
		DEBUG_LOG("Initialized %s", GetType().GetName().c_str());
		Input * input = Input::Instance();
		input->CreateAxis("Vertical", AxisCode::W, AxisCode::S);
		input->CreateAxis("Horizontal", AxisCode::D, AxisCode::A);

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

		if (m_Camera != nullptr)
		{
			GameObject * renderer = m_Renderer->GetGameObject();
			Vector3 rendererPosition = renderer->GetPosition();

			rendererPosition.x += h * Time::GetDeltaTime();
			rendererPosition.z += v * Time::GetDeltaTime();

			renderer->SetPosition(rendererPosition);
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