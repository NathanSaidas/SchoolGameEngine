#ifndef GAME_ENGINE_TEST_COMPONENT_H
#define GAME_ENGINE_TEST_COMPONENT_H

#include "Component.h"
#include "../Engine.h"

namespace Engine
{
	class TestComponent : public Component
	{
		CLASS_HEADER(TestComponent)
	public:
		TestComponent();
		~TestComponent();
	protected:
		void OnRegister();
		void OnInitialize();
		void OnLateInitialize();
		
		void OnDestroy();
		void OnLateDestroy();
		
		void Update();
		void LateUpdate();
		void FixedUpdate();
		
		void OnPreRender();
		void OnRender();
		void OnPostRender();

	private:
		Mesh * m_Cube;
		Mesh * m_Plane;
		Material * m_Material;
		IniFileStream * m_File;
	};


	TYPE_DEFINE(TestComponent)
	TYPE_DEFINE_PTR(TestComponent*, "TestComponent Ptr")

}

#endif