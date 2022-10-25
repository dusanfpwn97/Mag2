#include "Boid.h"
#include <EFE/ResourceManager.h>
#include <iostream>
#include "BoidManager.h"
#include <cmath>


Boid::Boid(glm::vec2 pos, glm::vec2 dir, float speed, BoidManager& boidManager, int id) :
	_speed(0.f),
	_vel(0.f),
	_position(0.f),
	_id(-1),
	_boundX(0),
	_boundY(0)
	//_velocity(0.f)
	
{
	_speed = speed;
	_vel = dir;
	_position = pos;
	_boidManager = &boidManager;
	_id = id;
}

Boid::~Boid()
{
}


void Boid::draw(efe::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0, 0, 1, 1);
	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 15.f, 15.f);

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
	_nearbyBoids = _boidManager->getNearbyBoids(*this, 400.f);
	calculateVelocity();
	move();

}

void Boid::move()
{
	_position += _vel * _speed;
}

void Boid::calculateVelocity()
{

	avoidOtherBoids();
	flyTowardsCenter();
	//keepWithinBounds();
	matchVelocity();

	limitSpeed();

	
}

void Boid::keepWithinBounds()
{
	if (_position.x <= -_boundX)
	{
		_vel.x *= -1.f;
	}
	if (_position.x >= _boundX - 25.f)
	{
		_vel.x *= -1.f;
	}
	if (_position.y <= -_boundY)
	{
		_vel.y *= -1.f;
	}
	if (_position.y >= _boundY - 22.f)
	{
		_vel.y *= -1.f;
	}
}

void Boid::avoidOtherBoids()
{
	const static float avoidAmount = 0.06f;

	glm::vec2 dt = {0.f, 0.f};

	for (int i = 0; i < _nearbyBoids.size(); i++)
	{
		dt += _vel - _nearbyBoids[i]->getVel();
	}

	_vel += dt * avoidAmount;

	//_vel = glm::normalize(_vel);
}

void Boid::limitSpeed()
{
	const float speed = sqrt(_vel.x * _vel.x + _vel.y * _vel.y);

	if (speed > _speed)
	{
		_vel.x = (_vel.x / speed) * _speed;
		_vel.y = (_vel.y / speed) * _speed;
	}

}

void Boid::flyTowardsCenter()
{
	if (_nearbyBoids.size() == 0) return;

	const static float centerAmount = 0.0035f;
	
	glm::vec2 center = { 0.f, 0.f };
	
	for (int i = 0; i < _nearbyBoids.size(); i++)
	{
		center += _nearbyBoids[i]->getPos();
	}
	
	center /= (float)_nearbyBoids.size();
	
	_vel += (center - _position) * centerAmount;
}

void Boid::matchVelocity()
{
	if (_nearbyBoids.size() == 0) return;

	const static float amount = 0.1f;

	glm::vec2 avgVel = { 0.f, 0.f };

	for (int i = 0; i < _nearbyBoids.size(); i++)
	{
		avgVel += _nearbyBoids[i]->getVel();
	}
	avgVel /= _nearbyBoids.size();

	_vel += avgVel - _vel * amount;
}


