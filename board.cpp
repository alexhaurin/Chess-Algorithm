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

void Board::Update()
{

}

void Board::Draw(std::shared_ptr<sf::RenderWindow> window)
{
	std::shared_ptr<sf::RectangleShape> line = std::make_shared<sf::RectangleShape>(sf::Vector2f(1, m_size));
	for (int i = 0; i < m_spots + 1; i++)
	{
		line->setPosition((i * (m_size / m_spots)), 0);
		window->draw(*line);
	}

	line->setSize(sf::Vector2f(m_size, 1));
	for (int i = 0; i < m_spots + 1; i++)
	{
		line->setPosition(0, i * (m_size / m_spots));
		window->draw(*line);
	}
}