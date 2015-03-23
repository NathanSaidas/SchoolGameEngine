#ifndef GAME_ENGINE_DRAW_CALL_H
#define GAME_ENGINE_DRAW_CALL_H

#include "../Math/Matrix4x4.h"
#include "../Math/Vector3.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

namespace Engine
{
	struct DrawCall
	{
		Matrix4x4 model;
		Matrix4x4 projection;
		Matrix4x4 view;
		Mesh * mesh;
		Material * material;

		static DrawCall Create(Matrix4x4 aModel, Vector3 aCameraPosition, Vector3 aCameraTarget, Matrix4x4 aProjection, Mesh * aMesh, Material * aShader);
	};
}

#endif