#include "Engine.h"

int main()
{
	srand(time(0));
	// Declare an instance of Engine
	Engine engine;
	// Start the engine
	engine.run();
	// Quit in the usual way when the engine is stopped
	return 0;
}

//void Particle::update(float dt)
//{
//    float G2 = rand() % 2501 + (-1000);
//    m_ttl = m_ttl - dt;
//    rotate(dt * m_radiansPerSec);
//    scale(SCALE);
//    float dx = m_vx * dt;
//    //m_vy = m_vy - (G * dt);
//    m_vy = m_vy - (G2 * dt);
//    float dy = m_vy * dt;
//    translate(dx, dy);
//}