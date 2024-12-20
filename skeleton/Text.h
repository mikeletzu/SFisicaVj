#pragma once

using Vector2 = physx::PxVec2;
using Vector4 = physx::PxVec4;

class Text {
private:
	Vector2 pos;
	std::string text;
	Vector4 color;
	bool show = true;

public:
	Text(std::string tx, Vector2 pos, Vector4 col) : text(tx), pos(pos), color(col) {}
	Vector2 getPos() const { return pos; }
	std::string getText() const { return text; }
	Vector4 getColor() const { return color; }
	bool getShow() const { return show; }
	void setPos(Vector2 pos) { this->pos = pos; }
	void setText(std::string text) { this->text = text; }
	void setColor(Vector4 color) { this->color = color; }
	void setShow(bool s) { show = s; }
};

