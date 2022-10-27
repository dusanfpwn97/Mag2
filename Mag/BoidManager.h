#pragma once
#include <EFE/SpriteBatch.h>
#include "Boid.h"
#include <vector>


class BoidManager
{

public:
	BoidManager();
	~BoidManager();

	// Postavljanje granica u kojima će se stvoriti boidi
	void updateBounds(const int x, const int y);
	// Stvaranje boida 
	void spawnBoids(int num, glm::vec2 pos);
	// Crtanje boida
	void drawBoids(efe::SpriteBatch &spriteBatch);
	// Ažuriranje boida
	void updateBoids();

	// Dobijanje svih boida stvorenih ovom instancom
	std::vector<Boid> getAllBoids() const { return _boids; }
	// Dobijanje svih boida blizu datog boida
	std::vector<Boid*> getNearbyBoids(const Boid &boid, float range);

private:
	// Vektor boida
	std::vector<Boid> _boids;

	// Granice stvaranja
	int _boundX;
	int _boundY;
};

