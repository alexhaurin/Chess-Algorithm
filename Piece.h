#pragma once

#include "Entity.h"
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class Board;

class Piece : public Entity {
public:
	Piece();
	~Piece();
	void Initialize() override;
	void Destroy() override;

	void Update(double in_dt);
	void Draw(std::shared_ptr<sf::RenderWindow> window);

	void MoveTo(sf::Vector2i in_pos);
	bool CanMove(std::shared_ptr<Board> in_board, sf::Vector2i in_spot);

	virtual std::vector<sf::Vector2i> GetAvailableSpots(std::shared_ptr<Board>& in_board);
	virtual std::vector<sf::Vector2i> GetAvailableAttacks(std::shared_ptr<Board>& in_board);
	sf::Vector2i GetBoardPosition() { return m_boardPos; }

	void SetBoardPosition(sf::Vector2i in_pos) {
		m_boardPos = in_pos;
		m_sprite.setPosition(sf::Vector2f(m_boardPos.x * 800.0 / 8.0, m_boardPos.y * 800.0 / 8.0));
	}
	void SetColor(int in_color) { m_color = in_color; }
	void SetMoved(bool in_moved) { m_moved = in_moved; }

protected:
	sf::Vector2i m_boardPos;
	bool m_moved = false;

	int m_color;
};

class Pawn : public Piece {
public:
	Pawn();
	~Pawn();

	std::vector<sf::Vector2i> GetAvailableSpots(std::shared_ptr<Board>& in_board) override;
	std::vector<sf::Vector2i> GetAvailableAttacks(std::shared_ptr<Board>& in_board) override;

};