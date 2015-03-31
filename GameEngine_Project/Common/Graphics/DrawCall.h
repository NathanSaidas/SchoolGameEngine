#ifndef GAME_ENGINE_DRAW_CALL_H
#define GAME_ENGINE_DRAW_CALL_H

#include "../Math/Matrix4x4.h"
#include "../Math/Vector3.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "../Memory/Memory.h"

namespace Engine
{
	struct DrawCall
	{
		DrawCall(Matrix4x4 aModel, Pointer<Mesh> aMesh, Pointer<Material> aMaterial);


		Matrix4x4 model;
		Pointer<Mesh> mesh;
		Pointer<Material> material;
	};
}

#endif