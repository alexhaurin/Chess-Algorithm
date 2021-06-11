#include "Snake.h"

Snake::Snake() {

};

Snake::~Snake() {

};

void Snake::Initialize() {
	Entity::Initialize();

	Part p(sf::Vector2i(0, 0));
	m_pieces.push_back(p);
};

void Snake::Destory() {

	Entity::Destroy();
};

void Snake::Update(double in_dt) {

};

void Snake::Draw(std::shared_ptr<sf::RenderWindow> in_window) {
	sf::RectangleShape shape(sf::Vector2f(10, 10));
	for (auto piece : m_pieces) {
		shape.setPosition(sf::Vector2f(piece.m_offset));
		in_window->draw(shape);
	}
};