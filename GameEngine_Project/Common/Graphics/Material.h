#ifndef GAME_ENGINE_MATERIAL_H
#define GAME_ENGINE_MATERIAL_H

#pragma region CHANGE LOG
/// --	April	9, 2015 - Nathan Hanlan - Added rendering states.
#pragma endregion

#include "../BasicTypes.h"
#include "Shader.h"
#include "Texture.h"
#include "../Memory/Memory.h"

namespace Engine
{
	class Shader;
	class Texture;

	class Material : public Resource
	{
		RDECLARE_CLASS(Material)
	public:
		Material();
		~Material();

		void SetShader(Pointer<Shader> & aShader);
		Pointer<Shader> GetShader();

		void SetTexture(Pointer<Texture> & aTexture);
		Pointer<Texture> GetTexture();
		/**
		* Sets the default state of the graphics pipeline.
		*/
		void SetDefaultState();
		/**
		* Sets the faces to cull.
		* @param aCullFace The face to cull
		*/
		void SetCullFace(CullFace aCullFace);
		/**
		* Sets the winding order for face culling
		* @param aCullMode The winding order for face culling.
		*/
		void SetCullMode(CullMode aCullMode);
		/**
		* Sets the depth func for depth testing.
		* @param aDepthFunc The function to use for depth testing
		*/
		void SetDepthFunc(DepthFunc aDepthFunc);
		/**
		* Sets the blend equation for fragment blending
		* @param aSource The source factor for blending
		* @param aDestination The destination factor for blending
		*/
		void SetBlendFunc(BlendFunc aSource, BlendFunc aDestination);
		/**
		* Enables a rendering state. (Depth Testing, Blending, Culling etc)
		* @param aState The state to enable
		*/
		void EnableState(GraphicsState aState);
		/**
		* Disables a rendering state. (Depth Testing, Blending, Culling etc)
		* @param aState The state to disable.
		*/
		void DisableState(GraphicsState aState);
		/**
		* Gets the current state specified.
		* @param aState The state to check
		* @return Returns the current state specified.
		*/
		bool GetState(GraphicsState aState);
		/**
		* Gets the current cull mode
		* @return Returns the cull mode.
		*/
		CullMode GetCullMode();
		/**
		* Gets the current winding.
		* @return Returns the current winding.
		*/
		CullFace GetCullFace();
		/**
		* Gets the depth function to use.
		* @return Returns the DepthFunc.
		*/
		DepthFunc GetDepthFunc();
		/**
		* Gets the blend source function
		* @return Returns the blend source function
		*/
		BlendFunc GetBlendSource();
		/**
		* Gets the blend destination
		* @return Returns the blend destination.
		*/
		BlendFunc GetBlendDestination();
	private:
		Pointer<Shader> m_Shader;
		Pointer<Texture> m_Texture;

		bool m_Cull;
		bool m_Blend;
		bool m_DepthTest;
		CullMode m_CullMode;
		CullFace m_CullFace;
		DepthFunc m_DepthFunc;
		BlendFunc m_BlendSource;
		BlendFunc m_BlendDestination;
	};

	TYPE_DEFINE(Material)
}

#endif