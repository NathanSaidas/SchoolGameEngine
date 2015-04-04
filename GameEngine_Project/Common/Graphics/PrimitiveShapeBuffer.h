#ifndef GAME_ENGINE_PRIMITIVE_SHAPE_BUFFER_H
#define GAME_ENGINE_PRIMITIVE_SHAPE_BUFFER_H

#include <GL\glew.h>
#include "../BasicTypes.h"

namespace Engine
{
    //This is a VBO used for drawing basic primitives. Data is reallocated each time a primitive makes a draw call.
    //Use Mesh for increased performance.
    class PrimitiveShapeBuffer : public object
    {
		RDECLARE_CLASS(PrimitiveShapeBuffer)
    public:
        // -- Initializes the PrimitiveShapeBuffer to default values
        PrimitiveShapeBuffer();
        // -- Releases existing memory from the PrimitiveShapeBuffer
        ~PrimitiveShapeBuffer();

        // -- Creates the PrimitiveShapeBuffer objects
        void Create();
        // -- Release the PrimitiveShapeBuffer objects
        void Release();
        // -- Returns true if the PrimitiveShapeBuffer is allocated
        bool IsAllocated();
        // -- Marshals data into the buffer. 
        void BindData(GLsizeiptr aAttributeCount, GLvoid * aAttributes, GLsizeiptr aIndicesSize, GLvoid * aIndices);
        // -- Returns the VBO handle
        GLuint GetVBO();
        // -- Returns the IBO handle
        GLuint GetIBO();

    private:
        GLuint m_VBO;
        GLuint m_IBO;
        bool m_Allocated;
    };

	TYPE_DEFINE(PrimitiveShapeBuffer)
}

#endif