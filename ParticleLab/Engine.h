#pragma once
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include "Particle2.h"
using namespace std;

class Engine
{
private:
	// A regular RenderWindow
	RenderWindow m_Window;

	//vector for Particles
	vector<Particle> m_particles;
	vector<Particle2> m_particles2;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();
	Sound WOW;
	Sound POP;

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};

#endif