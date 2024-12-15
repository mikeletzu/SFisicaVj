#include "Zone.h"
#include <iostream>

bool Zone::isOut(Vector3 p){

	return (p.x < _zone.first.x || p.x > _zone.second.x || p.y < _zone.first.y || p.y > _zone.second.y || p.z < _zone.first.z || p.z > _zone.second.z);
}
