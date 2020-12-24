#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Vector {
	template<typename tItemType>
	std::vector<tItemType> EraseItemValue(std::vector<tItemType>& in_vector, tItemType& in_value);

	template<typename tItemType>
	int GetItemIndex(std::vector<tItemType>& in_vector, tItemType& in_value);
}

namespace Math {
	float GetMagnitude(sf::Vector2f& vector);

	float GetDot(sf::Vector2f& vect1, sf::Vector2f& vect2);

	sf::Vector2f Normalize(sf::Vector2f& vector);

	bool CheckCircleCollisions(const sf::Vector2f& pos1, const float& radius1, const sf::Vector2f& pos2, const float& radius2);

	bool CheckRectCollisions(const sf::Vector2f& pos1, const sf::Vector2f& dim1, const sf::Vector2f& pos2, const sf::Vector2f& dim2);

	bool CheckRectPointCollisions(const sf::Vector2f& pos1, const sf::Vector2f& dim1, const sf::Vector2f& pos2);
}