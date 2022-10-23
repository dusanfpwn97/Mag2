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
	for (int i = 0; i < _boids.size(); i++)
	{
		_boids[i].updateBounds(x, y);
	}
}

void BoidManager::spawnBoids(int num)
{
	srand(time(NULL));
	const float randMax = static_cast<float>(RAND_MAX);
	const float halfRandMax = randMax / 2;
	for (int i = 0; i < num; i++)
	{
		glm::vec2 direction;
		direction.x = (rand() - halfRandMax) / randMax;
		direction.y = (rand() - halfRandMax) / randMax;
		glm::normalize(direction);

		glm::vec2 pos;
		pos.x = rand() / randMax * 600 - 256;
		pos.y = rand() / randMax * 600 - 256;

		_boids.emplace_back(pos, direction, 2.5f, *this);
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
		if (glm::distance(APos, _boids[i].getPos()) <= range)
		{
			boids.push_back(&_boids[i]);
		}

	}

	return boids;
}