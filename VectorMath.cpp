#include "VectorMath.h"

//////////////////////////// Vector //////////////////////////////
//Returns vector with first item of a given value erased
template<typename tItemType>
std::vector<tItemType> Vector::EraseItemValue(std::vector<tItemType>& in_vector, tItemType& in_value) {
	int index;
	for (int i = 0; i < in_vector.size(); i++) {
		if (in_vector[i] = in_value)
		{
			index = i;
			break;
		}
	}
	return in_vector.erase(in_vector.begin() + index);
}

//Returns index of first item with given value
template<typename tItemType>
int Vector::GetItemIndex(std::vector<tItemType>& in_vector, tItemType& in_value) {
	for (int i = 0; i < in_vector.size(); i++) {
		if (in_vector[i] = in_value) {
			return i;
		}
	}
}


////////////////////////////// Math //////////////////////////////////
float Math::GetMagnitude(sf::Vector2f& vector) {
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

float Math::GetDot(sf::Vector2f& vect1, sf::Vector2f& vect2) {
	return (vect1.x*vect2.x) + (vect1.y*vect2.y);
}

sf::Vector2f Math::Normalize(sf::Vector2f& vector) {

	auto magnitude = GetMagnitude(vector);
	if (magnitude == 0) {
		return vector;
	}

	sf::Vector2f normalized(vector.x / magnitude, vector.y / magnitude);
	return normalized;
}

bool Math::CheckCircleCollisions(const sf::Vector2f& pos1, const float& radius1, const sf::Vector2f& pos2, const float& radius2) {
	sf::Vector2f vector(pos1.x - pos2.x, pos1.y - pos2.y);

	float distance = GetMagnitude(vector);

	return (distance <= (radius1 + radius2));
}

bool Math::CheckRectCollisions(const sf::Vector2f& pos1, const sf::Vector2f& dim1, const sf::Vector2f& pos2, const sf::Vector2f& dim2) {
	if ((pos1.y - dim1.y / 2 >= pos2.y - dim2.y / 2 && pos1.y - dim1.y / 2 <= pos2.y + dim2.y / 2) || \
		(pos1.y + dim1.y / 2 <= pos2.y + dim2.y / 2 && pos1.y + dim1.y / 2 >= pos2.y - dim2.y / 2)) {
		if ((pos1.x + dim1.x / 2 <= pos2.x + dim2.x / 2 && pos1.x + dim1.x / 2 >= pos2.x - dim2.x / 2) || \
			(pos1.x - dim1.x / 2 >= pos2.x - dim2.x / 2 && pos1.x - dim1.x / 2 <= pos2.x + dim2.x / 2)) {
			return true;
		}
	}
	return false;
}

bool Math::CheckRectPointCollisions(const sf::Vector2f& pos1, const sf::Vector2f& dim1, const sf::Vector2f& pos2) {
	if ((pos1.y - dim1.y / 2 >= pos2.y && pos1.y - dim1.y / 2 <= pos2.y) || \
		(pos1.y + dim1.y / 2 <= pos2.y && pos1.y + dim1.y / 2 >= pos2.y)) {
		if ((pos1.x + dim1.x / 2 <= pos2.x && pos1.x + dim1.x / 2 >= pos2.x) || \
			(pos1.x - dim1.x / 2 >= pos2.x && pos1.x - dim1.x / 2 <= pos2.x)) {
			return true;
		}
	}

	return false;
}