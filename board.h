#pragma once
#include "Entity.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Board : public Entity
{
public:
	Board();
	~Board();
	void Initialize();
	void Destroy();

	void Update();
	void Draw(std::shared_ptr<sf::RenderWindow> window);

	void SetSize(float in_size) { m_size = in_size; }

	std::shared_ptr<sf::RenderWindow> window;
	int m_spots = 9;
	float m_size = 100.0;
};