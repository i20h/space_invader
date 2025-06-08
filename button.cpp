#include "button.h"

#include <iostream>

Button::Button(const nsGraphics::Vec2D& pos, const nsGraphics::Vec2D& size,
           const std::string& label, const std::function<void()>& onClick,
           nsGui::GlutFont::GlutFonts font)
    : label(label), onClick(onClick), font(font)
{
    int textHeight = size.getY() - 2;
    this->pos = pos - nsGraphics::Vec2D(1, textHeight + 1);
    this->size = nsGraphics::Vec2D(size.getX() + 2, textHeight + 2);
}

void Button::draw(MinGL& window) const{
    int textHeight = size.getY() - 2;

    nsGraphics::Vec2D rectPos = pos - nsGraphics::Vec2D(1, textHeight + 1);
    nsGraphics::Vec2D rectSize = nsGraphics::Vec2D(size.getX() + 2, textHeight + 2);

    nsGraphics::Vec2D textPos = pos;

    window << nsShape::Rectangle(rectPos, rectPos + rectSize, isHovered ? hoverBg : normalBg);
    window << nsGui::Text(textPos, label, nsGraphics::KWhite, this->font);
}

bool Button::isMouseOver(const nsGraphics::Vec2D& mouse) const{
    int textHeight = size.getY() - 2;
    nsGraphics::Vec2D rectPos = pos - nsGraphics::Vec2D(1, textHeight + 1);
    nsGraphics::Vec2D rectSize = nsGraphics::Vec2D(size.getX() + 2, textHeight + 2);

    return mouse.getX() >= rectPos.getX() && mouse.getX() <= rectPos.getX() + rectSize.getX() &&
           mouse.getY() >= rectPos.getY() && mouse.getY() <= rectPos.getY() + rectSize.getY();
}

void Button::tryClick(const nsGraphics::Vec2D& mouse, bool mousePressed) {
    if (mousePressed && isMouseOver(mouse)) {
        onClick();
    }
}
