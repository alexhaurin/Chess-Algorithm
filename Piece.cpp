#include "Piece.h"

Piece::Piece() {
}

Piece::~Piece() {

}

void Piece::Initialize() {

	m_sprite.setScale(sf::Vector2f((m_dimensions.x) / m_texture.getSize().x, (m_dimensions.x) / m_texture.getSize().x));
	m_sprite.setTexture(m_texture);

	m_dimensions.x = m_texture.getSize().x * m_sprite.getScale().x;
	m_dimensions.y = m_texture.getSize().y * m_sprite.getScale().y;

	std::cout << "initialized" << std::endl;
}

void Piece::Destroy() {

}

void Piece::Update(double in_dt) {

}

void Piece::Draw(std::shared_ptr<sf::RenderWindow> in_window) {
	in_window->draw(m_sprite);
}