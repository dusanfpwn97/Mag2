#include "Boid.h"
#include <EFE/ResourceManager.h>
#include <iostream>
#include "BoidManager.h"


Boid::Boid(glm::vec2 pos, glm::vec2 dir, float speed, BoidManager &boidManager) :
	_speed(0.f),
	_direction(0.f),
	_position(0.f)
	//_velocity(0.f)
	
{
	_speed = speed;
	_direction = dir;
	_position = pos;
	_boidManager = &boidManager;
}

Boid::~Boid()
{
}


void Boid::draw(efe::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0, 0, 1, 1);
	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30.f, 30.f);

	static efe::GLTexture texture = efe::ResourceManager::getTexture("textures/birb3.png");

	efe::Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;

	
	spriteBatch.draw(posAndSize, uv, texture.id, color, 0);
}

void Boid::update()
{
	calculateDirection();
	move();

}

void Boid::move()
{
	_position += _direction * _speed;
}

void Boid::calculateDirection()
{

	//std::vector<Boid*> nearbyBoids = _boidManager->getNearbyBoids(*this, 50.f);


	//for (int i = 0; i < nearbyBoids.size(); i++)
	//{
	//
	//}

	keepWithinBounds();

	
}

void Boid::keepWithinBounds()
{
	if (_position.x <= -_boundX)
	{
		_direction.x *= -1.f;
	}
	if (_position.x >= _boundX - 25.f)
	{
		_direction.x *= -1.f;
	}
	if (_position.y <= -_boundY)
	{
		_direction.y *= -1.f;
	}
	if (_position.y >= _boundY - 22.f)
	{
		_direction.y *= -1.f;
	}
}


