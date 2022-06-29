

#pragma once
#include <vector>
#include "libgfx.hpp"

namespace gui
{
    class Widget
    {
    public:
        Widget(){};
        ~Widget(){};
        shapes::Rect Bounds() { return m_bounds; };
        shapes::Point RelativeLocation() { return m_relative_location; };
        unsigned int Width() { return m_width; };
        unsigned int Height() { return m_height; };

        void SetRelativeLocation(shapes::Point new_location)
        {
            m_relative_location = new_location;
        };
        void AddChild(Widget *child)
        {
            m_children.push_back(child);
        };

        std::vector<Widget *> Children() { return m_children; };
        virtual void Hovered(shapes::Point mouse) = 0;
        virtual void Clicked(shapes::Point mouse) = 0;

    protected:
        // size and collision info
        shapes::Point m_relative_location;
        shapes::Rect m_bounds;
        unsigned int m_width;
        unsigned int m_height;
        // any child widgets
        std::vector<Widget *> m_children;
    };

} // namespace gui