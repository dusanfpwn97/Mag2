#include "Boid.h"
#include <EFE/ResourceManager.h>
#include <iostream>
#include "BoidManager.h"
#include <cmath>


Boid::Boid(glm::vec2 pos, glm::vec2 dir, float speed, BoidManager& boidManager, int id) :
	_speed(0.f),
	_vel(0.f),
	_position(0.f),
	_id(-1)
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

// Crtanje boida
void Boid::draw(efe::SpriteBatch& spriteBatch)
{
	// Setovanje UV koordinata
	glm::vec4 uv(0, 0, 1, 1);
	// Setovanje pozicije i skale
	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 15.f, 15.f);
	// Setovanje teksture
	static efe::GLTexture texture = efe::ResourceManager::getTexture("textures/boid.png");
	// Setovanje boje. Bela boja znači da se uzima prava boja teksture
	efe::Color color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;
	
	// Crtanje
	spriteBatch.draw(posAndSize, uv, texture.id, color, 0);
}

// Ažuriranje boida
void Boid::update()
{
	// Dobijanje svih boida blizu ovog boida
	_nearbyBoids = _boidManager->getNearbyBoids(*this, 400.f);
	// Računanje brzine
	calculateVelocity();
	// Kretanje
	move();

}

// Kretanje
void Boid::move()
{
	_position += _vel * _speed;
}

// Računanje brzine
void Boid::calculateVelocity()
{
	// Izbegavanje obližnjih boida - Razdvajanje
	avoidOtherBoids();
	// Letenje ka centru mase obližnjih boida - Kohezija
	flyTowardsCenter();
	// Korigovati brzinu prema obližnjim boidima - Poravnanje
	matchVelocity();
	// Ograničavanje brzine
	limitSpeed();
}

// Izbegavanje obližnjih boida - Razdvajanje
void Boid::avoidOtherBoids()
{
	// Koliko će se snažno odvajati
	const static float avoidAmount = 0.1f;

	glm::vec2 dt = {0.f, 0.f};

	// Zbir razlike brzina ovog boida i bliznjih
	for (int i = 0; i < _nearbyBoids.size(); i++)
	{
		dt += _vel - _nearbyBoids[i]->getVel();
	}
	// Rezultat se dodaje u velocity
	_vel += dt * avoidAmount;
}

// Ograničavanje brzine
void Boid::limitSpeed()
{
	const float speed = sqrt(_vel.x * _vel.x + _vel.y * _vel.y);

	if (speed > _speed)
	{
		_vel.x = (_vel.x / speed) * _speed;
		_vel.y = (_vel.y / speed) * _speed;
	}

}

// Letenje ka centru mase obližnjih boida - Kohezija
void Boid::flyTowardsCenter()
{
	if (_nearbyBoids.size() == 0) return;

	const static float centerAmount = 0.003f;
	
	glm::vec2 center = { 0.f, 0.f };
	
	// Zbir svih pozicija
	for (int i = 0; i < _nearbyBoids.size(); i++)
	{
		center += _nearbyBoids[i]->getPos();
	}
	// srednja vrednost svih pozicija
	center /= (float)_nearbyBoids.size();
	
	_vel += (center - _position) * centerAmount;
}

// Korigovati brzinu prema obližnjim boidima - Poravnanje
void Boid::matchVelocity()
{
	if (_nearbyBoids.size() == 0) return;

	const static float amount = 0.06f;

	glm::vec2 avgVel = { 0.f, 0.f };

	// Zbir svih brzina
	for (int i = 0; i < _nearbyBoids.size(); i++)
	{
		avgVel += _nearbyBoids[i]->getVel();
	}
	// Srednja brzina
	avgVel /= _nearbyBoids.size();

	_vel += (avgVel - _vel) * amount;
}


