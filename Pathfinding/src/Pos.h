#pragma once


#include <SFML/Graphics.hpp>

struct Pos {
	Pos() : x(0), y(0) {}
	Pos(int x, int y) : x(x), y(y) {}
	int x;
	int y;

	// Define the comparison operator
	bool operator<(const Pos& other) const {
		if (x != other.x) {
			return x < other.x;
		}
		return y < other.y;
	}

    bool operator==(const Pos& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Pos& other) const {
        return ! (*this == other);
    }
};