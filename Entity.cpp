#include "Entity.h"
#include "VectorMath.h"

Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::Initialize() {

	Object::Initialize();
}

void Entity::Destroy() {

	std::cout << "Destroying entity" << std::endl;

	Object::Destroy();
}

void Entity::Update(double in_dt) {

	m_position = GetPosition();
}

void Entity::Draw(std::shared_ptr<sf::RenderWindow> window) {

	window->draw(m_sprite);
}