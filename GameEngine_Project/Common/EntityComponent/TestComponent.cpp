#include "TestComponent.h"
#include <Windows.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <stddef.h>



/// -- This component will setup a camera and the ground plane and provide a light source and target to demonstrate shadows.
/// -- Move the camera with the WASD keys
/// -- Move the light with the TFGH keys
/// -- Move the light target with the arrow keys.
/// -- This program was tested on a AMD Radeon HD 7700 graphics card with OpenGL version 4.4
/// -- Program setup can be configured with setting.ini file found inside the projects folder.


namespace Engine
{
	//Helper functions to create a cube and Plane object
	GameObject * CreateCube(Vector3 aPosition, Pointer<Material> & aMaterial, float aSize);
	GameObject * CreateCube(Vector3 aPosition, Pointer<Material> & aMaterial, float aSize, Color aColor);
	GameObject * CreatePlane(Vector3 aPosition, Pointer<Material> & aMaterial, float aSize);

	
	GameObject * CreateCube(Vector3 aPosition, Pointer<Material> & aMaterial, float aSize)
	{
		return CreateCube(aPosition, aMaterial, aSize, Color::CornflowerBlue());
	}

	GameObject * CreateCube(Vector3 aPosition, Pointer<Material> & aMaterial, float aSize, Color aColor)
	{
		Pointer<Mesh> mesh;
		mesh.MakeUnique(Geometry::CreateCube(
			aSize, aSize, aSize,
			aColor,
			Memory::AllocatorType::Pool));
		GameObject * cube = NEW_POOL(GameObject)("Cube");
		Renderer * renderer = cube->AddComponent<Renderer>();
		renderer->SetMaterial(aMaterial);
		renderer->SetMesh(mesh);
		cube->SetPosition(aPosition);

		return cube;
	}

	GameObject * CreatePlane(Vector3 aPosition, Pointer<Material> & aMaterial, float aSize)
	{
		Pointer<Mesh> mesh;
		mesh.MakeUnique(Geometry::CreatePlane(
			aSize, aSize,
			Color::CornflowerBlue(),
			Memory::AllocatorType::Pool));
		GameObject * cube = NEW_POOL(GameObject)("Plane");
		Renderer * renderer = cube->AddComponent<Renderer>();
		renderer->SetMaterial(aMaterial);
		renderer->SetMesh(mesh);
		cube->SetPosition(aPosition);

		return cube;
	}

    RDEFINE_CLASS(TestComponent, "")

        void MathTest();

	TestComponent::TestComponent() : Component()
	{
        MathTest();
	}
	TestComponent::~TestComponent()
	{

	}

	void TestComponent::OnRegister()
	{
		DEBUG_LOG("Registered %s", GetType().GetName().c_str());

	}
	
	void TestComponent::OnInitialize()
	{
		DEBUG_LOG("Initialized %s", GetType().GetName().c_str());
		//Setup Input Axis.
		Input * input = Input::Instance();
		input->CreateAxis("Vertical", AxisCode::W, AxisCode::S);
		input->CreateAxis("Horizontal", AxisCode::A, AxisCode::D);

		input->CreateAxis("Light V", AxisCode::T, AxisCode::G);
		input->CreateAxis("Light H", AxisCode::F, AxisCode::H);
		input->CreateAxis("Light Y", AxisCode::Y, AxisCode::R);

		input->CreateAxis("Target V", AxisCode::Up, AxisCode::Down);
		input->CreateAxis("Target H", AxisCode::Left, AxisCode::Right);

		//Get the camera and renderer to setup
		m_Camera = GetComponentInChildren<Camera>();
		m_Renderer = GetComponentInChildren<Renderer>();
		
		//Create the ground plane.
		m_Mesh.MakeUnique(Geometry::CreatePlane(25.0f, 25.0f, Color::Crimson(), Memory::AllocatorType::Pool));

		//Load texture and shader.
		Pointer<ImageTexture> texture = ResourceDatabase::LoadTexture("Wall3.png");
		Pointer<Shader> shader = ResourceDatabase::LoadShader("Shaders\\Built-In\\DefaultShader.glsl");

		//Setup the material.
		if (!texture.IsAlive())
		{
			DEBUG_LOG("Missing Wall3.png");
		}
		else
		{
			m_Material->SetTexture(texture.Cast<Texture>());
		}
		if (!shader.IsAlive())
		{
			DEBUG_LOG("Missing Built-in DefaultShader.glsl");
		}
		else
		{
			m_Material->SetShader(shader);
		}

		//Setup the camera
		if (m_Camera != nullptr)
		{
			m_FieldOfView = 60.0f;
			m_Camera->SetFieldOfView(m_FieldOfView);
			GameObject * gameObject = m_Camera->GetGameObject();
			gameObject->SetPosition(Vector3(0.0f, 3.0f, -3.0f));
			gameObject->LookAt(Vector3(0.0f,3.5f,0.0f));
		}

		//Setup the renderer
		if (m_Renderer != nullptr)
		{
			m_Renderer->SetMaterial(m_Material);
			m_Renderer->SetMesh(m_Mesh);
			GameObject * gameObject = m_Renderer->GetGameObject();
		}

	}

	

	void TestComponent::OnLateInitialize()
	{
		DEBUG_LOG("Late Initialization %s", GetType().GetName().c_str());
		
		//Create the light and its target for visual representation.
		m_LightTarget = CreateCube(Vector3(3.0f, 1.0f, 0.0f), m_Material, 2.0f,Color::Yellow());
		m_Light =  CreateCube(Vector3(-2.0f, 3.0f, 5.0f), m_Material, 1.0f, Color::MidnightBlue());
	
		//Create additional shadow casters and other objects..
        CreateCube(Vector3(4.0f, 1.0f, 0.0f), m_Material, 3.0f);

        // Quaternion a = Quaternion::Euler(Vector3(0.0f, 0.0f, 25.0f));
        // Quaternion b = Quaternion::Euler(Vector3(0.0f, 0.0f, 45.0f));
        // Float32 dotR = Quaternion::Dot(a, b);
        // Quaternion lerp = Quaternion::Lerp(a, b, 0.75f);
        // Quaternion cross = Quaternion::Cross(a, b);
        // Quaternion slerp = Quaternion::Slerp(a, b, 0.75f);
        // 
        // 
        // Matrix4x4 orthoMatrix = Matrix4x4::Ortho(0.0f, 640.0f, 0.0f, 640.0f, 1.0f, 0.1f);
        // Matrix4x4 model = Matrix4x4::Identity();
        // model.Translate(Vector3(0.0f, 0.0f, 0.2f));
        // model.Rotate(0.0f, 0.0f, Vector3::Zero());
        // model.Scale(Vector3(100.0f, 100.0f, 30.0f));
        // 
        // Matrix4x4 mulRes = orthoMatrix * model;
        // 
        // Vector3 result = mulRes * Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
        // 
        glm::vec2 position(0.0f,0.0f);
        glm::vec2 size(10.0f, 10.0f);


        glm::mat4 model;
        model = glm::translate(model, glm::vec3(position, 0.0f));

        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        model = glm::scale(model, glm::vec3(size, 1.0f));

        glm::mat4 ortho = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);

        glm::vec4 positions[] =
        {
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
        };

        for (int i = 0; i < 3; ++i)
        {
            glm::vec4 result = ortho * model * positions[i];
            DEBUG_LOG("%f %f %f", result.x, result.y, result.y);
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
		//Additional settings for speed
		float speed = 3.0f;
		float fovSpeed = 5.0f;
		Input * input = Input::Instance();
		
		//Get input.
		float v = input->GetAxis("Vertical");
		float h = input->GetAxis("Horizontal");
		float lightV = input->GetAxis("Light V");
		float lightH = input->GetAxis("Light H");
		float lightY = input->GetAxis("Light Y");
		float targetV = input->GetAxis("Target V");
		float targetH = input->GetAxis("Target H");

		

		if (m_Renderer != nullptr && m_Camera != nullptr)
		{
			//Move the camera with the 
			GameObject * gameObject = m_Camera->GetGameObject();
			Vector3 position = gameObject->GetPosition();

			//Move the camera
			position.x += h * Time::GetDeltaTime() * speed;
			position.z += v * Time::GetDeltaTime() * speed;

			gameObject->SetPosition(position);

			//Adjust the FOV of the camera.
			if (input->GetKey(KeyCode::Alpha0))
			{
				m_FieldOfView = Math::Clamp(m_FieldOfView + Time::GetDeltaTime() * fovSpeed, 10.0f, 90.0f);
			}
			else if (input->GetKey(KeyCode::Alpha9))
			{
				m_FieldOfView = Math::Clamp(m_FieldOfView - Time::GetDeltaTime() * fovSpeed, 10.0f, 90.0f);
			}

			//Log out some information to the console. With the ~ key.
			if (input->GetKeyDown(KeyCode::GraveAccent))
			{
				DEBUG_LOG("FOV: %f", m_FieldOfView);
				DEBUG_LOG("Pos: %f %f %f", Graphics::DEBUG_POSITION.x, Graphics::DEBUG_POSITION.y, Graphics::DEBUG_POSITION.z);
				DEBUG_LOG("Dir: %f %f %f", Graphics::DEBUG_DIRECTION.x, Graphics::DEBUG_DIRECTION.y, Graphics::DEBUG_DIRECTION.z);
			}

			m_Camera->SetFieldOfView(m_FieldOfView);
		}

		
		if (m_Light != nullptr && m_LightTarget != nullptr)
		{
			//Adjust the light positions.
			Vector3 position = m_Light->GetPosition();
			position.x += lightH * Time::GetDeltaTime() * speed;
			position.z += lightV * Time::GetDeltaTime() * speed;
			position.y += lightY * Time::GetDeltaTime() * speed;
			m_Light->SetPosition(position);

			//Adjust the light target positions
			position = m_LightTarget->GetPosition();
			position.x += targetH * Time::GetDeltaTime() * speed;
			position.z += targetV * Time::GetDeltaTime() * speed;
			m_LightTarget->SetPosition(position);

			
			//Toggle light / light target on and off.
			if (input->GetKeyDown(KeyCode::B))
			{
				if (m_Light->IsActive())
				{
					m_Light->SetActive(false);
				}
				else
				{
					m_Light->SetActive(true);
				}
				if (m_LightTarget->IsActive())
				{
					m_LightTarget->SetActive(false);
				}
				else
				{
					m_LightTarget->SetActive(true);
				}
			}
			
			//Reset the light and light target.
			if (input->GetKeyDown(KeyCode::Alpha1))
			{
				m_Light->SetPosition(Vector3(10.0f, 5.0f, 10.0f));
				m_LightTarget->SetPosition(Vector3(-5.0f, 0.0f, 0.0f));
			}

			Vector3 direction = m_LightTarget->GetPosition() - m_Light->GetPosition();
			Graphics::DEBUG_POSITION = m_Light->GetPosition();
			Graphics::DEBUG_DIRECTION = (direction.Normalized());
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
    
    float Deg2Rad(float v)
    {
        return 3.14159265359f / 180.0f * v;
    }

    float Rad2Deg(float v)
    {
        return v * 180.0f / 3.14159265359f;
    }

    void Vector2Test()
    {
        Vector2 a = Vector2(0.5f, 0.2f);
        Vector2 b = Vector2(0.4f, 0.3f);
        float angle = Vector2::Angle(a, b);

        Vector2 clampMag = Vector2::ClampMagnitude(a, 0.1f);

        float dot = Vector2::Dot(a, b);
        float mag = a.GetMagnitude();
        float magSqr = a.GetSqrMagnitude();

        Vector2 normalized = Vector2(34.243f, -84.123f);
        Vector2 otherNormalized = normalized.Normalized();
        normalized.Normalize();

        float dist = Vector2::Distance(a, b);

        Vector2 lerp = Vector2::Lerp(a, b, 0.35f);



        Vector2 reflect = Vector2::Reflect(a, b);
        Vector2 refract = Vector2::Refract(a, b, Deg2Rad(5.0f));
        Vector2 faceforward = Vector2::FaceForward(a, b, a);

        Vector2 rotated = Vector2::Rotate(a, Deg2Rad(45.0f));
    }

    void Vector3Test()
    {
        Vector3 a = Vector3(0.5f, 0.2f,0.3f);
        Vector3 b = Vector3(0.4f, 0.3f,0.95f);
        float angle = Vector3::Angle(a, b);

        Vector3 clampMag = Vector3::ClampMagnitude(a, 0.1f);

        float dot = Vector3::Dot(a, b);
        Vector3 cross = Vector3::Cross(a, b);
        float mag = a.GetMagnitude();
        float magSqr = a.GetSqrMagnitude();

        Vector3 normalized = Vector3(34.243f, -84.123f,12.453f);
        Vector3 otherNormalized = normalized.Normalized();
        normalized.Normalize();

        float dist = Vector3::Distance(a, b);

        Vector3 lerp = Vector3::Lerp(a, b, 0.35f);



        Vector3 reflect = Vector3::Reflect(a, b);
        Vector3 refract = Vector3::Refract(a, b, Deg2Rad(5.0f));
        Vector3 faceforward = Vector3::FaceForward(a, b, a);

        Vector3 rotateX = Vector3::RotateX(a, Deg2Rad(45.0f));
        Vector3 rotateY = Vector3::RotateY(a, Deg2Rad(45.0f));
        Vector3 rotateZ = Vector3::RotateZ(a, Deg2Rad(45.0f));

    }

    void MathTest()
    {
        Vector2Test();
        Vector3Test();


    }
}