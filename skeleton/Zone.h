#pragma once
#include "core.hpp"

class Zone
{
private:
	std::pair<Vector3, Vector3> _zone;

public:
	Zone(Vector3 a, Vector3 b) {
		_zone = { a, b };
	}

	bool isOut(Vector3 p);
};

