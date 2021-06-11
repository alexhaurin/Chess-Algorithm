#include "Piece.h"
#include "board.h"

Piece::Piece() {
}

Piece::~Piece() {

}

void Piece::Initialize() {

	m_sprite.setScale(sf::Vector2f((m_dimensions.x) / m_texture.getSize().x, (m_dimensions.x) / m_texture.getSize().x));
	m_sprite.setTexture(m_texture);

	m_dimensions.x = m_texture.getSize().x * m_sprite.getScale().x;
	m_dimensions.y = m_texture.getSize().y * m_sprite.getScale().y;

	std::cout << "Piece initialized" << std::endl;
}

void Piece::Destroy() {

	std::cout << "Piece destroyed" << std::endl;
}

void Piece::Update(double in_dt) {

}

void Piece::Draw(std::shared_ptr<sf::RenderWindow> in_window) {
	in_window->draw(m_sprite);
}

void Piece::MoveTo(sf::Vector2i in_pos) {
	SetBoardPosition(in_pos);

	m_moved = true;
}

bool Piece::CanMove(std::shared_ptr<Board> in_board, sf::Vector2i in_spot) {
	auto spots = GetAvailableSpots(in_board);
	auto attack = GetAvailableAttacks(in_board);
	spots.insert(spots.end(), attack.begin(), attack.end());

	for (auto& spot : spots) {
		if (in_spot == spot) {
			return true;
		}
	}

	return false;
}

std::vector<sf::Vector2i> Piece::GetAvailableSpots(std::shared_ptr<Board>& in_board) {
	auto board = in_board->GetData();
	std::vector<sf::Vector2i> spots;

	if (board[m_boardPos.x][m_boardPos.y + m_color] == nullptr) {
		spots.push_back(sf::Vector2i(m_boardPos.x, m_boardPos.y + m_color));
	}

	return spots;
}

std::vector<sf::Vector2i> Piece::GetAvailableAttacks(std::shared_ptr<Board>& in_board) {
	auto board = in_board->GetData();
	std::vector<sf::Vector2i> spots;

	for (int i = 1; i < 3; i++) {
		if (board[m_boardPos.x + i][m_boardPos.y + m_color] != nullptr) {
			spots.push_back(sf::Vector2i(m_boardPos.x, m_boardPos.y + m_color));
		}
	}

	std::cout << spots[0].x << ", " << spots[0].y << std::endl;
	return spots;
}

////////////////////////////// Pawn //////////////////////////////

Pawn::Pawn() {

}

Pawn::~Pawn() {

}

std::vector<sf::Vector2i> Pawn::GetAvailableSpots(std::shared_ptr<Board>& in_board) {
	auto board = in_board->GetData();
	std::vector<sf::Vector2i> spots;

	if (!m_moved) {
		spots.push_back(sf::Vector2i(m_boardPos.x, m_boardPos.y + (2 * m_color)));
	}
	if (board[m_boardPos.x][m_boardPos.y + m_color] == nullptr) {
		spots.push_back(sf::Vector2i(m_boardPos.x, m_boardPos.y + m_color));
	}

	return spots;
}

std::vector<sf::Vector2i> Pawn::GetAvailableAttacks(std::shared_ptr<Board>& in_board) {
	auto board = in_board->GetData();
	std::vector<sf::Vector2i> spots;

	for (int i = 1; i < 3; i++) {
		auto spot = sf::Vector2i(m_boardPos.x + i, m_boardPos.y + m_color);

		if (spot.x > 7) { spot.x = 6; }
		if (spot.x < 0) { spot.x = 1; }

		if (board[spot.x][spot.y] != nullptr) {
			spots.push_back(spot);
		}
	}

	if (spots.size()) {
		std::cout << spots[0].x << ", " << spots[0].y << std::endl;
	}
	return spots;
}