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

		m_Mesh.MakeUnique(Geometry::CreateCube(2.0f, 2.0f, 2.0f, Color::Crimson(), Memory::AllocatorType::Pool));
		//m_Mesh.MakeUnique(Geometry::CreatePlane(1.0f, 1.0f, Color::Crimson(), Memory::AllocatorType::Pool));


		m_Material->SetName("Default Diffuse");

	}
	
	void TestComponent::OnInitialize()
	{
		DEBUG_LOG("Initialized %s", GetType().GetName().c_str());
		Input * input = Input::Instance();
		input->CreateAxis("Vertical", AxisCode::W, AxisCode::S);
		input->CreateAxis("Horizontal", AxisCode::A, AxisCode::D);

	}
	void TestComponent::OnLateInitialize()
	{
		DEBUG_LOG("Late Initialization %s", GetType().GetName().c_str());

		m_Camera = GetComponentInChildren<Camera>();
		m_Renderer = GetComponentInChildren<Renderer>();

		IniFileStream fileStream;
		fileStream.SetPath("Log.ini");

		fileStream.AddSection("Default");
		fileStream.BindSection("Default");
		
		Matrix4x4 identity = Matrix4x4::Identity();
		fileStream.AddVector4("Identity[0]", Vector4(identity[0]));
		fileStream.AddVector4("Identity[1]", Vector4(identity[1]));
		fileStream.AddVector4("Identity[2]", Vector4(identity[2]));
		fileStream.AddVector4("Identity[3]", Vector4(identity[3]));

		
		if (m_Camera != nullptr)
		{
			m_Camera->SetFieldOfView(45.0f);
			GameObject * gameObject = m_Camera->GetGameObject();
			gameObject->SetPosition(Vector3(0.0f, 3.0f, -3.0f));
			gameObject->LookAt(Vector3::Zero());


			Matrix4x4 view = m_Camera->GetViewMatrix();
			Matrix4x4 projection = m_Camera->GetProjectionMatrix();



			fileStream.AddSection("Camera");
			fileStream.BindSection("Camera");
			fileStream.AddVector3("Position", gameObject->GetPosition());
			fileStream.AddVector4("View[0]", Vector4(view[0]));
			fileStream.AddVector4("View[1]", Vector4(view[1]));
			fileStream.AddVector4("View[2]", Vector4(view[2]));
			fileStream.AddVector4("View[3]", Vector4(view[3]));
			fileStream.AddVector4("Projection[0]", Vector4(projection[0]));
			fileStream.AddVector4("Projection[1]", Vector4(projection[1]));
			fileStream.AddVector4("Projection[2]", Vector4(projection[2]));
			fileStream.AddVector4("Projection[3]", Vector4(projection[3]));
		}

		if (m_Renderer != nullptr)
		{
			m_Renderer->SetMaterial(m_Material);
			m_Renderer->SetMesh(m_Mesh);

			GameObject * gameObject = m_Renderer->GetGameObject();
			
			Matrix4x4 model = gameObject->GetLocalToWorldMatrix();

			fileStream.AddSection("Renderer");
			fileStream.BindSection("Renderer");
			fileStream.AddVector3("Position", gameObject->GetPosition());
			fileStream.AddVector4("Model[0]", Vector4(model[0]));
			fileStream.AddVector4("Model[1]", Vector4(model[1]));
			fileStream.AddVector4("Model[2]", Vector4(model[2]));
			fileStream.AddVector4("Model[3]", Vector4(model[3]));

		}

		fileStream.Save();

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