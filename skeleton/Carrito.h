#pragma once
#include "core.hpp"
#include "Text.h"

class Carrito
{
public:
    Carrito(Text* txt) : _capopsTXT(txt){}
    void update(Vector3 pos);
    void addPop();

private:
    Vector3 _anchor;
    int _capturedPops = 0;
    Text* _capopsTXT;
};

