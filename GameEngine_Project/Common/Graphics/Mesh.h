#ifndef GAME_ENGINE_MESH_H
#define GAME_ENGINE_MESH_H

#include <GL\glew.h>
#include "../BasicTypes.h"
#include "../Math/Math.h"
#include "../Utilities/Utilities.h"
#include "Color.h"




namespace Engine
{
    ///A class used to represent mesh data for rendering. 
    //Contains VertexAttributes (Position, Normal, Color, TexCoords)
    class Mesh : public Object
    {
        CLASS_HEADER(Mesh)
    public:
        //Initializes the mesh values to 0.
        Mesh();
        //Releases any resources held within the meshes. (The vertex attribute arrays/GPU memory)
        ~Mesh();
        //Loads a mesh from a file. (This does not upload to OpenGL refer to Upload for that function)
        bool LoadFile(const std::string &aFileName);
        //Uploads a mesh to the OpenGL state machine
        bool Upload();
        //Releases resources from the CPU (if true) and OpenGL if IsUploaded
        bool Release(bool aReleaseCPU = false);

        // -- Setters for Vertex Attributes
		// These will create a copy of the array
        void SetPositions(Array<Vector3> & aPositions);
        void SetNormals(Array<Vector3> & aNormals);
        void SetTexCoords(Array<Vector2> & aTexCoords);
        void SetColors(Array<Color> & aColors);
        void SetIndices(Array<UInt16> & aIndicies);
        
        // -- Getters for Vertex Attributes
		// These return a reference to the array
        Array<Vector3> GetPositions();
        Array<Vector3> GetNormals();
        Array<Vector2> GetTexCoords();
        Array<Color> GetColors();
        Array<UInt16> GetIndicies();

        // -- Returns true if the Mesh has been uploaded to the OpenGL state machine
        bool IsUploaded();
        // -- Returns the VBO handle. Refrain from using OpenGL functions externally.
        GLuint GetVBO();
        // -- Returns a copy of the IBO handle. Refrain from using OpenGL Functions externally.
        GLuint GetIBO();
        // -- Returns how many attributes were made when the file was uploaded to OpenGL
        UInt32 GetAttributeCount();
        // -- Returns how many indicies were made when thefile was uploaded to OpenGL
        UInt32 GetIndexCount();

        
    private:
        Array<Vector3> m_Positions;
        Array<Vector3> m_Normals;
        Array<Vector2> m_TexCoords;
        Array<Color> m_Colors;
        Array<UInt16> m_Indices;


        bool m_Uploaded;
        GLuint m_VBO;
        GLuint m_IBO;
        UInt32 m_AttributeCount;
        UInt32 m_IndexCount;


    };

    TYPE_DEFINE(Mesh)
    TYPE_DEFINE_PTR(Mesh*, "Mesh Ptr")

}

#endif