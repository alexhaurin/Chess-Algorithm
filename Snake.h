#pragma once

#include "board.h"

#include <iostream>
#include <SFML/Graphics.hpp>

struct Part {
	Part(sf::Vector2i in_offset)
		: m_offset(in_offset) {}
	~Part() {}

	sf::Vector2i m_offset;
};

class Snake {
public:
	Snake();
	~Snake();

	void Initialize();
	void Destory();

	void Update(double in_dt);
	void Draw(std::shared_ptr<sf::RenderWindow> in_window);

private:
	std::vector<Part> m_pieces;
	sf::Vector2i m_position;
};