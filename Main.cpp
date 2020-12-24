#include <memory>
#include "game.h"

int main() {

	auto game = Object::SpawnRoot<Game>();

	game->Run();
}