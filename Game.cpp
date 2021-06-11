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
	Sound.Initialize();

	m_dimensions = sf::Vector2i(1500, 1500);
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_dimensions.x, m_dimensions.y), "Engine2");
	//m_board = CreateBoard(m_boardSize, m_boardSpots);

	//PopulateBoard();

	//////////////////////////// SNAKEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ////////////////////////////////////////////////
	m_snake->Initialize();

}

void Game::Destroy() {

	Object::Destroy();

	std::cout << "Game destroyed" << std::endl;

}

void Game::Run() {

	SetFramerate(1000);
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
			m_window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
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
	//m_mousePosI = sf::Mouse::getPosition(*m_window);
	//m_mousePos = sf::Vector2f(m_mousePosI);
	//m_mouseBoardPos = GetMouseBoardPosition();
	//
	//for (auto& entity : m_entityList) {
	//	entity->Update(dt);
	//}
	//
	//for (auto& piece : m_pieceList) {
	//	m_board->SetData(piece->GetBoardPosition(), piece);
	//}
	//
	//if (m_inputState.mouseLeftPressed) {
	//	if (m_board->GetData()[m_mouseBoardPos.x][m_mouseBoardPos.y] != nullptr) {
	//		if (m_grabbed == nullptr) {
	//			m_grabbed = m_board->GetData()[m_mouseBoardPos.x][m_mouseBoardPos.y];
	//		}
	//	}
	//}
	//
	////Grab piece
	//if (m_grabbed != nullptr) {
	//	if (m_inputState.mouseLeftPressed) {
	//		m_grabbed->SetPosition(sf::Vector2f(m_mousePos.x - m_grabbed->GetDimensions().x/2, m_mousePos.y - m_grabbed->GetDimensions().y/2));
	//	}
	//	else {
	//		sf::Vector2i pos = m_mouseBoardPos;
	//
	//		if (m_grabbed->CanMove(m_board, pos)) {
	//			m_grabbed->MoveTo(pos);
	//			Sound.PlayPieceSound();
	//		} else {
	//			m_grabbed->SetBoardPosition(m_grabbed->GetBoardPosition());
	//		}
	//
	//		m_grabbed = nullptr;
	//	}
	//}
	//
	////Destroy Invalid Entitys
	//auto EraseInvalid = [](auto& entityList) {
	//	entityList.erase(std::remove_if(entityList.begin(), entityList.end(), [](auto entity) {
	//		return !IsValid(&*entity);
	//	}), entityList.end());
	//};

	///////////////////////////////////////////////// SNAKEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ///////////////////////////////////////////////////////////

	

	if (m_inputState.keyUpPressed) {

	}
}

void Game::Draw()
{
	//m_window->clear();
	//
	//for (auto& entity : m_entityList) {
	//	entity->Draw(m_window);
	//}
	//
	//m_window->display();

	///////////////////////////////////////////// SNAKEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ////////////////////////////////////////////////////

	m_window->clear();
	
	
	
	m_window->display();
}

void Game::PopulateBoard() {
	if (!m_pieceTexture.loadFromFile("Images/Queen.jpg")) {
		std::cout << "can't load queen" << std::endl;
	}
	int color = 1;

	std::vector<int> rows = { 1, 6 };
	for (auto& place : rows) {
		for (int i = 0; i < m_boardSpots; i++) {
			auto piece = CreatePawn(m_pieceTexture, sf::Vector2i(i, place), color, m_boardSize / m_boardSpots);
			m_pieceList.push_back(piece);
			m_entityList.push_back(piece);
		}
		color *= -1;
	}
}

std::shared_ptr<Board> Game::CreateBoard(int in_size, int in_spots) {
	auto board = SpawnWithSetup<Board>(shared_from_this(), [this, in_size, in_spots](Board* in_board) {
		in_board->SetSize(in_size);
		in_board->SetSpots(in_spots);
	});
	m_entityList.push_back(board);
	return board;
}

std::shared_ptr<Piece> Game::CreatePiece(sf::Texture& in_texture, const sf::Vector2i in_boardPos, int in_color, float in_size) {
	auto piece = SpawnWithSetup<Piece>(shared_from_this(), [this, in_texture, in_boardPos, in_color, in_size](Piece* in_piece) {
		in_piece->SetTexture(in_texture);
		in_piece->SetBoardPosition(in_boardPos);
		in_piece->SetColor(in_color);
		in_piece->SetDimensions(sf::Vector2f(in_size, in_size));;
	});
	return piece;
}

std::shared_ptr<Pawn> Game::CreatePawn(sf::Texture& in_texture, const sf::Vector2i in_boardPos, int in_color, float in_size) {
	auto pawn = SpawnWithSetup<Pawn>(shared_from_this(), [this, in_texture, in_boardPos, in_color, in_size](Pawn* in_pawn) {
		in_pawn->SetTexture(in_texture);
		in_pawn->SetBoardPosition(in_boardPos);
		in_pawn->SetColor(in_color);
		in_pawn->SetDimensions(sf::Vector2f(in_size, in_size));;
	});
	return pawn;
}

/////////////////////////////// Input Class //////////////////////////////////////
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
/////////////////////////////////////// Sound ////////////////////////////////////////////

Sound::Sound() {

}

Sound::~Sound() {

}

void Sound::Initialize() {

	if (!soundBuffer1.loadFromFile("Sounds/chessSound1.wav")) {
		std::cout << "Sound1 not loaded" << std::endl;
	}
	pieceSounds[0].setBuffer(soundBuffer1);

	if (!soundBuffer2.loadFromFile("Sounds/chessSound2.wav")) {
		std::cout << "Sound1 not loaded" << std::endl;
	}
	pieceSounds[1].setBuffer(soundBuffer2);

	if (!soundBuffer3.loadFromFile("Sounds/chessSound3.wav")) {
		std::cout << "Sound1 not loaded" << std::endl;
	}
	pieceSounds[2].setBuffer(soundBuffer3);
}

void Sound::PlayPieceSound() {
	int random = rand() % 3;

	pieceSounds[random].play();
}

