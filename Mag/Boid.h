#pragma once
#include <glm/glm.hpp>
#include <EFE/SpriteBatch.h>
class BoidManager;

class Boid
{
public:
	// Konstruktor sa pozicijom, smerom, brzinom,
	// referencom na Boid Manager instancu i id boida
	Boid(glm::vec2 pos, glm::vec2 dir, float speed, BoidManager &boidManager, int id);
	~Boid();

	// Crtanje boida
	void draw(efe::SpriteBatch& spriteBatch);
	// Ažuriranje boida
	void update();
	// Dobijanje pozicije
	glm::vec2 getPos() const { return _position; }
	// Dobijanje brzine
	glm::vec2 getVel() const { return _vel; }
	// Dobijanje id-a
	int		  getId() const { return _id; }


private:
	// Kretanje boida
	void move();
	// Računanje brzine
	void calculateVelocity();
	// Izbegavanje drugih boida
	void avoidOtherBoids();
	// Ograničavanje brzine
	void limitSpeed();
	// Letenje ka centru mase drugih boida (kohezija)
	void flyTowardsCenter();
	// korigovati brzinu prema drugim boidima
	void matchVelocity();

	// Pointer na BoidManager instancu koja je stvorila ovaj boid
	BoidManager* _boidManager;
	// maksimalna brzina
	float _speed;
	// trenutna brzina (i smer)
	glm::vec2 _vel;
	// trenutna poticija
	glm::vec2 _position;
	
	int _id;
	// Vektor pokazivača na trenutne obližnje boide
	std::vector<Boid*> _nearbyBoids;
};

