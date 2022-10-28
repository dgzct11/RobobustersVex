#pragma once

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

		Vector2(double x = 0.0, double y = 0.0){
			this->x = x;
			this->y = y;
		}

		Vector2 operator+(Vector2 vec){
			return {x + vec.x, y + vec.y};
		}

		Vector2 operator-(Vector2 vec){
			return {x - vec.x, y - vec.y};
		}

		Vector2 operator*(Vector2 vec){
			return {x * vec.x, y * vec.y};
		}

		Vector2 operator/(Vector2 vec){
			return {x / vec.x, y / vec.y};
		}
};
