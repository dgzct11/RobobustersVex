#include "Constants.cpp"

enum Drive{
	tank,
	split_arcade,
	left,
	right,
};

struct Vector2{
public:
	double x;
	double y;

	Vector2(double x, double y){
				this->x = x;
				this->y = y;
	}

	Vector2 operator+(Vector2 otherVector){
		return {x + otherVector.x, y + otherVector.y};
	}

	Vector2 operator-(Vector2 otherVector){
		return {x - otherVector.x, y - otherVector.y};
	}

	Vector2 operator*(Vector2 otherVector){
		return {x * otherVector.x, y * otherVector.y};
	}

	Vector2 operator/(Vector2 otherVector){
		return {x / otherVector.x, y / otherVector.y};
	}
};
