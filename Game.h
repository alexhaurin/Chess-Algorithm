#pragma once
#include "Entity.h"
#include "Piece.h"
#include "board.h"
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

	std::shared_ptr<Board> CreateBoard(float in_size);
	std::shared_ptr<Piece> CreatePiece(sf::Texture& in_texture, const sf::Vector2i in_position, float in_size);

	double GetFramerate() const { return dt; }
	sf::Vector2f GetDimensions() const { return m_dimensions; }

	void SetFramerate(int in_framerate) { m_targetTime = std::chrono::milliseconds(1000 / in_framerate); }
	void SetWindowSize(const sf::Vector2u& in_size) { m_window->setSize(in_size); }
private:
	std::shared_ptr<sf::RenderWindow> m_window;
	std::chrono::milliseconds m_targetTime;
	sf::Vector2f m_dimensions;
	double dt = 1.0;

	sf::Vector2i m_mousePosition;

	std::shared_ptr<Piece> m_grabbed;
	std::shared_ptr<Piece> m_piece;
	sf::Texture m_pieceTexture;

	std::vector<std::shared_ptr<Entity>> m_entityList;
	std::vector<std::shared_ptr<Piece>> m_pieceList;

	std::shared_ptr<Board> m_board;
	float m_boardSize = 750;


	Input m_inputState;
	bool m_inputBool;
};