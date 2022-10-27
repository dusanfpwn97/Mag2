#include "BoidManager.h"
#include <random>
#include <ctime>
#include <glm/glm.hpp>
#include <iostream>

BoidManager::BoidManager() :
	_boundX(0.0f),
	_boundY(0.0f)
{
}

BoidManager::~BoidManager()
{
}

// Ažuriranje granica stvaranja
void BoidManager::updateBounds(const int x, const int y)
{
	srand(time(NULL));

	_boundX = x;
	_boundY = y;
}

// Stvaranje boida 
void BoidManager::spawnBoids(int num, glm::vec2 pos)
{
	// Keširanje maximuma random floata
	static const float randMax = static_cast<float>(RAND_MAX);
	// Keširanje maximuma random floata
	static const float halfRandMax = randMax / 2;

	// Postavljanje random smera
	glm::vec2 vel;
	vel.x = (rand() - halfRandMax) / randMax;
	vel.y = (rand() - halfRandMax) / randMax;
	vel = glm::normalize(vel);

	// Ako je početna pozicija nula
	if (pos.x < 0.01f && pos.y < 0.01f && pos.x > -0.01f && pos.y > -0.01f)
	{
		
		for (int i = 0; i < num; i++)
		{
			// Postavljanje random pozicije u granicama
			glm::vec2 randPos;
			randPos.x = (rand() - halfRandMax) / randMax * _boundX;
			randPos.y = (rand() - halfRandMax) / randMax * _boundY;

			// Stvaranje boida sa parametrima u konstruktoru
			_boids.emplace_back(randPos, vel, 1.5f, *this, _boids.size());
		}
	}
	// Ako je data tačna pozicija
	else
	{
		for (int i = 0; i < num; i++)
		{
			// Stvaranje boida sa parametrima u konstruktoru
			_boids.emplace_back(pos, vel, 1.5f, *this, _boids.size());
		}
	}
	

}

// Crtanje svih boida
void BoidManager::drawBoids(efe::SpriteBatch& spriteBatch)
{
	for (int i = 0; i < _boids.size(); i++)
	{
		_boids[i].draw(spriteBatch);
	}
}

// Ažuriranje boida
void BoidManager::updateBoids()
{
	for (int i = 0; i < _boids.size(); i++)
	{
		_boids[i].update();
	}
}

// Dobijanje svih boida blizu datog boida
std::vector<Boid*> BoidManager::getNearbyBoids(const Boid& boid, float range)
{
	std::vector<Boid*> boids;
	// setovanje pozicije trenutnog boida jer se ne menja
	const glm::vec2 APos = boid.getPos();

	for (int i = 0; i < _boids.size(); i++)
	{
		// Ako je distance trenutnog boida manja od raspona,
		// dodamo boid u vektor boida
		if ((glm::distance(APos, _boids[i].getPos()) <= range) &&
			 boid.getId() != _boids[i].getId())
		{
			boids.push_back(&_boids[i]);
		}
	}

	return boids;
}