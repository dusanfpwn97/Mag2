#pragma once
#include <GL/glew.h>
#include "GLTexture.h"

#include <string>
namespace efe
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();


		void init(float x, float y, float width, float height, std::string texturePath);

		void draw();


	private:
		float _x = 0;
		float _y = 0;
		float _width = 0;
		float _height = 0;
		GLint _vboID = 0;
		GLTexture _texture;

	};

}