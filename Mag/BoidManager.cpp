#include "BoidManager.h"
#include <random>
#include <ctime>
#include <glm/glm.hpp>


BoidManager::BoidManager()
{
}

BoidManager::~BoidManager()
{
}


void BoidManager::updateBounds(const int x, const int y)
{
	_boundX = x;
	_boundY = y;

	for (int i = 0; i < _boids.size(); i++)
	{
		_boids[i].updateBounds(_boundX, _boundX);
	}
}

void BoidManager::spawnBoids(int num, glm::vec2 pos)
{
	if (pos.x < 0.1f && pos.y < 0.1f && pos.x > -0.1f && pos.y > -0.1f)
	{
		srand(time(NULL));
		const float randMax = static_cast<float>(RAND_MAX);
		const float halfRandMax = randMax / 2;
		for (int i = 0; i < num; i++)
		{
			glm::vec2 vel;
			vel.x = (rand() - halfRandMax) / randMax;
			vel.y = (rand() - halfRandMax) / randMax;
			vel = glm::normalize(vel);

			glm::vec2 randPos;
			randPos.x = (rand() - halfRandMax) / randMax * _boundX * 1.75f;
			randPos.y = (rand() - halfRandMax) / randMax * _boundY * 1.75f;

			_boids.emplace_back(randPos, vel, 1.5f, *this, _boids.size());

			_boids[_boids.size() - 1].updateBounds(_boundX, _boundY);
		}
	}
	else
	{
		_boids.emplace_back(pos, glm::vec2(0.f,0.f), 1.5f, *this, _boids.size());

		_boids[_boids.size() - 1].updateBounds(_boundX, _boundY);
	}
	

}

void BoidManager::drawBoids(efe::SpriteBatch& spriteBatch)
{

	for (int i = 0; i < _boids.size(); i++)
	{
		_boids[i].draw(spriteBatch);
	}
}

void BoidManager::updateBoids()
{
	for (int i = 0; i < _boids.size(); i++)
	{
		_boids[i].update();
	}
}

std::vector<Boid*> BoidManager::getNearbyBoids(const Boid& boid, float range)
{
	std::vector<Boid*> boids;
	const glm::vec2 APos = boid.getPos();

	for (int i = 0; i < _boids.size(); i++)
	{
		if ((glm::distance(APos, _boids[i].getPos()) <= range) && boid.getId() != _boids[i].getId())
		{
			boids.push_back(&_boids[i]);
		}

	}

	return boids;
}