#include "TestComponent.h"
#include <glm\gtc\matrix_transform.hpp>
#include <stddef.h>



namespace Engine
{
	RDEFINE_CLASS(TestComponent, "")

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

		Stream stream;
		BinaryFormatter formatter;

		std::string value = "hello world. This is a crazy sentence";
		std::string result = "";

		formatter.Serialize(value, stream);
		formatter.Deserialize(result, stream);
    
        

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

			//Get the renderer type information.
            Type type = m_Renderer->GetType();
			//Get the members from the type.
            Array<Reflection::MemberInfo> members = type.GetMembers();

			//Create two pointer objects.
            Pointer<Material> * material = nullptr;
            Pointer<Mesh> * mesh = nullptr;

			//Iterate through all of the members and 
            for (int i = 0; i < members.GetCount(); i++)
            {
                Reflection::MemberInfo member = members[i];

				DEBUG_LOG("==Member==\nName: %s\nType Name: %s\nOffset %u", member.GetMemberName(), member.GetMemberTypename(), member.GetOffset());

                if (member.GetMemberName() == "m_Mesh")
                {
                    mesh = (Pointer<Mesh>*)member.GetOffsetPointer(m_Renderer);

					if (mesh != nullptr)
					{
						DEBUG_LOG("Changing Mesh Values.\nPrevious Name: %s",m_Renderer->GetMesh()->GetName().c_str());
						(*mesh)->SetName("New Mesh Name");
						DEBUG_LOG("After Name: %s", m_Renderer->GetMesh()->GetName().c_str());
					}
                }
                else if (member.GetMemberName() == "m_Material")
                {
                    material = (Pointer<Material>*)member.GetOffsetPointer(m_Renderer);
					if (material != nullptr)
					{
						DEBUG_LOG("Changing Material Values.\nPrevious Name: %s", m_Renderer->GetMaterial()->GetName().c_str());
						(*material)->SetName("New Material Name");
						DEBUG_LOG("After Name: %s", m_Renderer->GetMaterial()->GetName().c_str());
					}
                }
            }
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