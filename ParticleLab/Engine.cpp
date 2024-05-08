#include "Engine.h"
#include <cstdlib> 
#include <time.h> 
#include <vector>
#include "Particle.h"

//using namespace Particle;

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particle", Style::Default);
}
void Engine::run()
{
	Clock clock;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		Time time = clock.restart();
		input();
		update(time.asSeconds());
		draw();
	}

}
void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed) m_Window.close();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
		if (event.mouseButton.button == Mouse::Left && event.type == Event::MouseButtonPressed)
		{
			int num = ((rand() % (80 - 60 + 1)) + 60);
			for (int i = 0; i < 5; i++)
			{
				Particle particle(m_Window, num, Mouse::getPosition(m_Window));
				m_particles.push_back(particle);
			}
		}
	}

}
void Engine::update(float dtAsSeconds)
{
	vector<Particle>::iterator itr;
	for (itr = m_particles.begin(); itr != m_particles.end();)
	{
		if (itr->getTTL() > 0.0)
		{
			itr->update(dtAsSeconds);
			++itr;
		}
		else
		{
			itr = m_particles.erase(itr);
		}
	}
}
void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();
}