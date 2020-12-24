#include "game.h"
#include "VectorMath.h"

Game::Game() {

	std::cout << "Game created" << std::endl;
}

Game::~Game() {

	std::cout << "Game deleted" << std::endl;
}

void Game::Initialize() {

	Object::Initialize();

	m_dimensions = sf::Vector2f(1200.0, 800.0);
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_dimensions.x, m_dimensions.y), "Engine2");
	m_board = CreateBoard(m_boardSize);

	//Load
	if (!m_pieceTexture.loadFromFile("Images/Queen.jpg")) {
		std::cout << "can't load queen" << std::endl;
	}
	
	//Spawn
	m_piece = CreatePiece(m_pieceTexture, sf::Vector2i(0, 0), m_boardSize/9);
	m_pieceList.push_back(m_piece);
	m_entityList.push_back(m_piece);
}

void Game::Destroy() {

	Object::Destroy();

	std::cout << "Game destroyed" << std::endl;

}

void Game::Run() {

	SetFramerate(60);
	while (m_window->isOpen()) {
		auto startTime = std::chrono::high_resolution_clock::now();
		HandleEvents();
		Update(dt);
		Draw();
		auto endTime = std::chrono::high_resolution_clock::now();
		auto deltaTime = startTime - endTime;

		if (deltaTime < m_targetTime) {
			auto remainingTime = m_targetTime - deltaTime - std::chrono::milliseconds(5);
			if (remainingTime > std::chrono::milliseconds(0)) {
				std::this_thread::sleep_for(remainingTime);

				while ((std::chrono::high_resolution_clock::now() - startTime) < m_targetTime) {}
			}
		}
		dt = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - startTime).count();
		//std::cout << dt << std::endl;
	}
}

void Game::HandleEvents() {

	sf::Event event;

	while (m_window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			m_window->close();
			Destroy();
			break;
		case sf::Event::Resized:
			break;
		case sf::Event::KeyPressed:
			m_inputBool = true;
			m_inputState.CheckKeyboardInputs();
		case sf::Event::KeyReleased:
			m_inputState.CheckKeyboardInputs();
		case sf::Event::MouseButtonPressed:
			m_inputState.CheckMouseInputs();
		case sf::Event::MouseButtonReleased:
			m_inputState.CheckMouseInputs();
		}
	}
}

void Game::Update(double in_dt)
{
	m_mousePosition = sf::Mouse::getPosition(*m_window);
	sf::Vector2f m_mousePositionF = sf::Vector2f(m_mousePosition);

	//Update Pieces
	for (auto piece : m_pieceList) {
		piece->Update(in_dt);

		if (m_grabbed == nullptr) {
			if (Math::CheckCircleCollisions(piece->GetPosition(), piece->GetDimensions().x / 2, m_mousePositionF, 10.0) && m_inputState.mouseLeftPressed) {
				m_grabbed = piece;
			}
		}
	}

	//Grab piece
	if (m_grabbed != nullptr) {
		if (m_inputState.mouseLeftPressed) {
			m_grabbed->SetPosition(m_mousePositionF);
		}
		else {
			m_grabbed->SetBoardPosition(m_grabbed->GetBoardPosition());
		}
	}



	//Destroy Invalid Entitys
	auto EraseInvalid = [](auto& entityList) {
		entityList.erase(std::remove_if(entityList.begin(), entityList.end(), [](auto entity) {
			return !IsValid(&*entity);
		}), entityList.end());
	};
}

void Game::Draw()
{
	m_window->clear();

	//Entities
	for (auto entity : m_entityList) {
		entity->Draw(m_window);
	}

	m_board->Draw(m_window);

	m_window->display();
}

std::shared_ptr<Piece> Game::CreatePiece(sf::Texture& in_texture, const sf::Vector2i in_boardPos, float in_size) {
	auto piece = SpawnWithSetup<Piece>(shared_from_this(), [this, in_texture, in_boardPos, in_size](Piece* in_player) {
		in_player->SetTexture(in_texture);
		in_player->SetBoardPosition(in_boardPos);
		in_player->SetDimensions(sf::Vector2f(in_size, in_size));;
	});
	return piece;
}

std::shared_ptr<Board> Game::CreateBoard(float in_size) {
	auto board = SpawnWithSetup<Board>(shared_from_this(), [this, in_size](Board* in_board) {
		in_board->SetSize(in_size);
	});
	return board;
}

////////////////////Input Class///////////////////
void Input::ClearKeyboardInputs() {

	keyUpPressed = false;
	keyLeftPressed = false;
	keyDownPressed = false;
	keyRightPressed = false;
	keySpacePressed = false;
}

void Input::ClearMouseInputs() {

	mouseLeftPressed = false;
	mouseRightPressed = false;
	mouseLeftReleased = false;
	mouseRightReleased = false;
}

void Input::CheckKeyboardInputs() {

	ClearKeyboardInputs();

	keyUpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	keyLeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	keyDownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	keyRightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	keySpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

void Input::CheckMouseInputs() {
	bool leftWasPressed = false;
	bool rightWasPressed = false;

	if (mouseLeftPressed) { leftWasPressed = true; }
	if (mouseRightPressed) { rightWasPressed = true; }

	ClearMouseInputs();
	
	mouseLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	mouseRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	//Test to see if mouse buttons were released
	if (leftWasPressed && !mouseLeftPressed) {
		mouseLeftReleased = true;
	}
	if (rightWasPressed && !mouseRightPressed) {
		mouseLeftReleased = true;
	}
}