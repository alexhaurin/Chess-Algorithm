#pragma once

#include "board.h"
#include "Snake.h"

#include <SFML/Audio.hpp>
#include <cstdarg>
#include <chrono>
#include <thread>

class Input {
public:
	void CheckKeyboardInputs();
	void CheckMouseInputs();
	void ClearKeyboardInputs();
	void ClearMouseInputs();

	bool keyRightPressed = false;
	bool keyLeftPressed = false;
	bool keyUpPressed = false;
	bool keyDownPressed = false;
	bool keySpacePressed = false;

	bool mouseLeftPressed = false;
	bool mouseRightPressed = false;
	bool mouseLeftReleased = false;
	bool mouseRightReleased = false;
};

class Sound {
public:
	Sound();
	~Sound();
	void Initialize();

	void PlayPieceSound();

private:
	sf::SoundBuffer soundBuffer1;
	sf::SoundBuffer soundBuffer2;
	sf::SoundBuffer soundBuffer3;

	std::vector<sf::Sound> pieceSounds = { sf::Sound(), sf::Sound(), sf::Sound() };
};

class Game : public Object {
public:
	Game();
	~Game();
	void Initialize();
	void Destroy();

	void Run();
	void HandleEvents();
	void Update(double in_dt);
	void Draw();

	void PopulateBoard();

	std::shared_ptr<Board> CreateBoard(int in_size, int m_boardSpots);
	std::shared_ptr<Piece> CreatePiece(sf::Texture& in_texture, const sf::Vector2i in_boardPos, int in_color, float in_size);
	std::shared_ptr<Pawn> CreatePawn(sf::Texture& in_texture, const sf::Vector2i in_boardPos, int in_color, float in_size);

	double GetFramerate() const { return dt; }
	sf::Vector2i GetDimensions() const { return m_dimensions; }
	sf::Vector2i GetMouseBoardPosition() {
		auto pos = sf::Vector2i(m_mousePosI.x / (m_boardSize / m_boardSpots), m_mousePosI.y / (m_boardSize / m_boardSpots));
		
		pos.x = std::max(0, pos.x);
		pos.x = std::min(7, pos.x);
		pos.y = std::max(0, pos.y);
		pos.y = std::min(7, pos.y);

		return pos;
	}

	void SetFramerate(int in_framerate) { m_targetTime = std::chrono::milliseconds(1000 / in_framerate); }
	void SetWindowSize(const sf::Vector2u& in_size) { m_window->setSize(in_size); }

protected:
	std::shared_ptr<Board> m_board;
	int m_boardSize = 800;
	int m_boardSpots = 8;

private:
	std::shared_ptr<sf::RenderWindow> m_window;
	std::chrono::milliseconds m_targetTime;
	sf::Vector2i m_dimensions;
	double dt = 1.0;

	Sound Sound;

	sf::Vector2f m_mousePos;
	sf::Vector2i m_mousePosI;
	sf::Vector2i m_mouseBoardPos;

	std::shared_ptr<Piece> m_grabbed;
	std::shared_ptr<Piece> m_piece;
	sf::Texture m_pieceTexture;

	std::vector<std::shared_ptr<Entity>> m_entityList;
	std::vector<std::shared_ptr<Piece>> m_pieceList;

	Input m_inputState;
	bool m_inputBool;

	////////////////////////////// SNAKEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE /////////////////////////////////////////////////////
	std::shared_ptr<Snake> m_snake = std::make_shared<Snake>();
};