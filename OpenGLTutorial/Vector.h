#pragma once

class Vector {
private:
	float* coords;
public:
	Vector();
	Vector(float vx, float vy, float vz);
	void setCoords(float vx, float vy, float vz);
	float* getCoords();
};