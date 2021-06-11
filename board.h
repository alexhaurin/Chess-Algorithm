#pragma once
#include "Piece.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Board : public Entity
{
public:
	Board();
	~Board();
	void Initialize();
	void Destroy();

	virtual void Update(double in_dt) override;
	virtual void Draw(std::shared_ptr<sf::RenderWindow> window) override;

	void ClearData();

	std::vector<std::vector<std::shared_ptr<Piece>>> GetData() const { return m_boardData; }

	void SetSize(int in_size) { m_size = in_size; }
	void SetSpots(int in_spots) { m_spots = in_spots; }
	void SetData(sf::Vector2i in_spot, std::shared_ptr<Piece> in_piece) { m_boardData[in_spot.x][in_spot.y] = in_piece; }

private:
	std::vector<std::vector<std::shared_ptr<Piece>>> m_boardData = {
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
	};

	int m_spots;
	int m_size;
};

////////////////////////////// Spot ///////////////////////////////////////

class Spot
{
public:
	Spot(sf::Vector2i in_pos, std::shared_ptr<Entity> in_piece);
	~Spot();

private:
	sf::Vector2i m_pos;
	std::shared_ptr<Entity> m_piece;
};