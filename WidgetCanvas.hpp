/*
This widget will own a bit map on which to draw its
children widgets.
*/

#pragma once

#include "Widget.hpp"
#include "ErrorOr.hpp"

namespace gui
{
    class WidgetCanvas : public Widget
    {
    public:
        WidgetCanvas(unsigned int w, unsigned int h, shapes::Point location);
        ~WidgetCanvas();

        virtual void Hovered(shapes::Point mouse);
        virtual void Clicked(shapes::Point mouse);

        ErrorOr<bool> CopyOut(gfx::Bitmap *dest, shapes::Point location);

    private:
        gfx::Bitmap *m_bitmap;
    };

} // namespace gui