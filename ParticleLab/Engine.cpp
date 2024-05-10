#include "Engine.h"
#include <cstdlib> 
#include <time.h> 
#include <vector>
#include "Particle.h"
#include "Particle2.h"
#include <SFML/Audio.hpp>

//using namespace Particle;

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particle", Style::Default);
}
void Engine::run()
{
	Clock clock;
	/*cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;*/

	SoundBuffer buffer;
	SoundBuffer buffer2;
	buffer.loadFromFile("AnimeWOW.wav");
	buffer2.loadFromFile("AnimePOP.wav");
	WOW.setBuffer(buffer);
	POP.setBuffer(buffer2);

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
			WOW.play();
			int num = ((rand() % (200 - 100 + 1)) + 100);
			for (int i = 0; i < 25; i++)
			{
				Particle particle(m_Window, num, Mouse::getPosition(m_Window));
				m_particles.push_back(particle);
			}
		}
		if (event.mouseButton.button == Mouse::Right && event.type == Event::MouseButtonPressed)
		{
			int num = ((rand() % (200 - 100 + 1)) + 100);
			for (int i = 0; i < 25; i++)
			{
				Particle2 particle2(m_Window, num, Mouse::getPosition(m_Window));
				m_particles2.push_back(particle2);
			}
			POP.play();
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
	vector<Particle2>::iterator itr2;
	for (itr2 = m_particles2.begin(); itr2 != m_particles2.end();)
	{
		if (itr2->getTTL() > 0.0)
		{
			itr2->update(dtAsSeconds);
			++itr2;
		}
		else
		{
			itr2 = m_particles2.erase(itr2);
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
	for (int i = 0; i < m_particles2.size(); i++)
	{
		m_Window.draw(m_particles2[i]);
	}
	m_Window.display();
}