#ifndef BUTTON_H
#define BUTTON_H

#include "mingl/graphics/vec2d.h"
#include "mingl/graphics/rgbacolor.h"
#include "mingl/shape/rectangle.h"
#include "mingl/gui/text.h"
#include <functional>

class Button {
public:
    Button(const nsGraphics::Vec2D& pos, const nsGraphics::Vec2D& size,
           const std::string& label, const std::function<void()>& onClick,
           nsGui::GlutFont::GlutFonts font);

    void draw(MinGL& window) const;

    bool isMouseOver(const nsGraphics::Vec2D& mouse) const;
    void setHovered(bool hovered) { isHovered = hovered; }
    void setHoverBg(const nsGraphics::RGBAcolor& color) { hoverBg = color; }
    void tryClick(const nsGraphics::Vec2D& mouse, bool mousePressed);
    void setHover(bool hover) { isHovered = hover; }
        
private:
    std::string label;
    bool isHovered = false;
    nsGraphics::Vec2D pos, size;
    nsGui::GlutFont::GlutFonts font;
    nsGraphics::RGBAcolor hoverBg = nsGraphics::KGray;
    nsGraphics::RGBAcolor normalBg = nsGraphics::KTransparent;
    std::function<void()> onClick;
};

#endif // BUTTON_H
