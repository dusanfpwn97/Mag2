#pragma once
#include <EFE/SpriteBatch.h>
#include "Boid.h"
#include <vector>


class BoidManager
{

public:
	BoidManager();
	~BoidManager();

	void updateBounds(const int x, const int y);

	void spawnBoids(int num);
	void drawBoids(efe::SpriteBatch &spriteBatch);
	void updateBoids();

	std::vector<Boid> getAllBoids() const { return _boids; }
	std::vector<Boid*> getNearbyBoids(const Boid &boid, float range);


private:
	std::vector<Boid> _boids;


};

