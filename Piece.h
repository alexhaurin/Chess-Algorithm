#pragma once

#include "Entity.h"
#include "board.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Piece : public Entity {
public:
	Piece();
	~Piece();
	virtual void Initialize() override;
	virtual void Destroy() override;

	virtual void Update(double in_dt);
	virtual void Draw(std::shared_ptr<sf::RenderWindow> window);

	sf::Vector2i GetBoardPosition() { return m_boardPos; }

	void SetBoardPosition(sf::Vector2i in_pos) {
		m_sprite.setPosition(sf::Vector2f(in_pos.x * 750 / 9, in_pos.y * 750 / 9));
	}

protected:

private:
	sf::Vector2i m_boardPos;
};