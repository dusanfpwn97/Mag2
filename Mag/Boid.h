#pragma once
#include <glm/glm.hpp>
#include <EFE/SpriteBatch.h>
class BoidManager;

class Boid
{

public:
	Boid(glm::vec2 pos, glm::vec2 dir, float speed, BoidManager &boidManager);
	~Boid();

	void updateBounds(const int x, const int y) { _boundX = x; _boundY = y; };

	void draw(efe::SpriteBatch& spriteBatch);
	void update();
	glm::vec2 getPos() const { return _position; }


private:
	void move();
	void calculateDirection();
	void keepWithinBounds();

	BoidManager* _boidManager;
	float _speed;
	glm::vec2 _direction;
	glm::vec2 _position;
	int _boundX;
	int _boundY;
	//glm::vec2 _velocity;
};

