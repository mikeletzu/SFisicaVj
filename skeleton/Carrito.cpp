#include "Carrito.h"

void Carrito::update(Vector3 pos)
{

}

void Carrito::addPop()
{ 
	++_capturedPops;
	_capopsTXT->setText("Particulas capturadas: " + std::to_string(_capturedPops));
}