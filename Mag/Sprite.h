#pragma once
#include <GL/glew.h>


class Sprite
{
public:
	Sprite();
	~Sprite();


	void init(float x, float y, float width, float height);

	void draw();
	

private:
	float _x = 0;
	float _y = 0;
	float _width = 0;
	float _height = 0;
	GLuint _vboID = 0;


};

