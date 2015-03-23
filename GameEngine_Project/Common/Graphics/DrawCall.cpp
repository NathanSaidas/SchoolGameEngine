#include "DrawCall.h"


namespace Engine
{
	DrawCall DrawCall::Create(Matrix4x4 aModel, Vector3 aCameraPosition, Vector3 aCameraTarget, Matrix4x4 aProjection, Mesh * aMesh, Material * aShader)
	{
		DrawCall drawCall;
		drawCall.model = aModel;
		drawCall.view = Matrix4x4::LookAt(aCameraPosition, aCameraTarget, Vector3::Up());
		drawCall.projection = aProjection;
		drawCall.mesh = aMesh;
		drawCall.material = aShader;
		return drawCall;
	}
}