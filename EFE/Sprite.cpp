#include "Sprite.h"
#include "Vertex.h"
#include <cstddef>
#include "ResourceManager.h"

namespace efe
{

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

	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(texturePath);


		if (_vboID == 0)
		{
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6] = {};

		// first triangle
		vertexData[0].setPosition(_x + _width, _y + _height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(_x, _y + _height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(_x, _y);
		vertexData[2].setUV(0.0f, 0.0f);

		//Second Triangle
		vertexData[3].setPosition(_x, _y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(_x + _width, _y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(_x + _width, _y + _height);
		vertexData[5].setUV(1.0f, 1.0f);


		//for (int i = 0; i < 6; i++)
		//{
		//	vertexData[i].setColor(255, 222, 225, 255);
		//
		//}

		//vertexData[1].setColor(0, 0, 225, 255);
		//vertexData[4].setColor(0, 255, 225, 255);

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{

		glBindTexture(GL_TEXTURE_2D, _texture.id);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

}