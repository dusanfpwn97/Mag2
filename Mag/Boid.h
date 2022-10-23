#pragma once
#include <glm/glm.hpp>
#include <EFE/SpriteBatch.h>
class BoidManager;

class Boid
{

public:
	Boid(glm::vec2 pos, glm::vec2 dir, float speed, BoidManager &boidManager, int id);
	~Boid();

	void updateBounds(const int x, const int y) { _boundX = x; _boundY = y; };

	void draw(efe::SpriteBatch& spriteBatch);
	void update();
	glm::vec2 getPos() const { return _position; }
	glm::vec2 getVel() const { return _vel; }
	int		  getId() const { return _id; }


private:
	void move();
	void calculateVelocity();
	void keepWithinBounds();
	void avoidOtherBoids();
	void limitSpeed();
	void flyTowardsCenter();
	void matchVelocity();

	BoidManager* _boidManager;
	float _speed;
	glm::vec2 _vel;
	glm::vec2 _position;

	int _boundX;
	int _boundY;
	int _id;
	std::vector<Boid*> _nearbyBoids;
	//glm::vec2 _velocity;
};

