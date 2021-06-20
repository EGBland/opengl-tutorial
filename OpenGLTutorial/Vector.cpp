#include "Vector.h"

Vector::Vector() {
	return Vector(0.0f, 0.0f, 0.0f);
}

Vector::Vector(float vx, float vy, float vz) {
	this->coords = new float[] {vx, vy, vz};
}