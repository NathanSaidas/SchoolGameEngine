#include "DrawCall.h"


namespace Engine
{
	DrawCall::DrawCall(Matrix4x4 aModel, Pointer<Mesh> aMesh, Pointer<Material> aMaterial)
	{
		model = aModel;
		mesh = aMesh;
		material = aMaterial;
	}
}