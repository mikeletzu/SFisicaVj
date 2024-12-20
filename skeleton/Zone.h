#pragma once
#include "core.hpp"

class Zone
{
private:
	std::pair<Vector3, Vector3> _zone;
	bool active = true;

public:
	Zone(Vector3 a, Vector3 b) {
		if (a == b) {
			active = false;
		}
		_zone = { a, b };
	}

	bool isOut(Vector3 p);
};

