#include "board.h"

Board::Board()
{
	std::cout << "Board created" << std::endl;
}

Board::~Board()
{
	std::cout << "Board destroyed" << std::endl;
}

void Board::Initialize() {

	Entity::Initialize();
}

void Board::Destroy() {

	Entity::Destroy();
}

void Board::Update(double in_dt) {
	ClearData();
}

void Board::Draw(std::shared_ptr<sf::RenderWindow> in_window)
{
	std::shared_ptr<sf::RectangleShape> line = std::make_shared<sf::RectangleShape>(sf::Vector2f(2, m_size));
	line->setFillColor(sf::Color(100, 0, 100));
	for (int i = 0; i < m_spots + 1; i++) {
		line->setPosition((i * (m_size / m_spots)), 0);
		in_window->draw(*line);
	}

	line->setSize(sf::Vector2f(m_size, 1));
	for (int i = 0; i < m_spots + 1; i++) {
		line->setPosition(0, i * (m_size / m_spots));
		in_window->draw(*line);
	}
}

void Board::ClearData() {
	for (int i = 0; i < m_spots; i++) {
		for (int j = 0; j < m_spots; j++) {
			m_boardData[i][j] = nullptr;
		}
	}
}


/////////////////////////// Spot //////////////////////////////

Spot::Spot(sf::Vector2i in_pos, std::shared_ptr<Entity> in_piece) {
	m_pos = in_pos;
	m_piece = in_piece;
}

Spot::~Spot() {

}