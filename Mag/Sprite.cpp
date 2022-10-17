#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>

Sprite::Sprite()
{
	_vboID = 0;
}

Sprite::~Sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6] = {};

	// first triangle
	vertexData[0].SetPosition(_x + _width, _y + _height);
	vertexData[0].setUV(1.0f, 1.0f);

	vertexData[1].SetPosition(_x, _y + _height);
	vertexData[1].setUV(0.0f, 1.0f);

	vertexData[2].SetPosition(_x, _y);
	vertexData[2].setUV(0.0f, 0.0f);

	//Second Triangle
	vertexData[3].SetPosition(_x, _y);
	vertexData[3].setUV(0.0f, 0.0f);

	vertexData[4].SetPosition(_x + _width, _y);
	vertexData[4].setUV(1.0f, 0.0f);

	vertexData[5].SetPosition(_x + _width, _y + _height);
	vertexData[5].setUV(1.0f, 1.0f);


	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 0, 225, 255);

	}

	vertexData[1].setColor(0, 0, 225, 255);
	vertexData[4].setColor(0, 255, 225, 255);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,		   sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));



	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
