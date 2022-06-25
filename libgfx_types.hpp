#ifndef GFX_TYPES_HPP
#define GFX_TYPES_HPP
#include <stdint.h>
#include <iostream>
#include "libshapes.hpp"

namespace gfx
{
    // the Pixel class holds r, g, b and alpha data for one single pixel
    class Pixel
    {
    public:
        Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha)
        {
            m_red = r;
            m_green = g;
            m_blue = b;
            m_alpha = alpha;
        }
        Pixel()
        {
            m_red = 0;
            m_green = 0;
            m_blue = 0;
            m_alpha = 0;
        }
        Pixel(Pixel *p)
        {
            m_red = p->red();
            m_blue = p->blue();
            m_green = p->green();
            m_alpha = p->alpha();
        }
        ~Pixel()
        {
        }

        uint8_t red()
        {
            return m_red;
        }

        uint8_t green()
        {
            return m_green;
        }

        uint8_t blue()
        {
            return m_blue;
        }

        uint8_t alpha()
        {
            return m_alpha;
        }

        uint32_t rgb()
        {
            return (m_red << 24) + (m_green << 16) + (m_blue << 8);
        }

        uint32_t rgba()
        {
            return (m_red << 24) + (m_green << 16) + (m_blue << 8) + m_alpha;
        }

        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            m_red = r;
            m_green = g;
            m_blue = b;
            m_alpha = a;
        }

        void operator=(const Pixel &c)
        {
            m_red = c.m_red;
            m_green = c.m_green;
            m_blue = c.m_blue;
            m_alpha = c.m_alpha;
        }

    private:
        uint8_t m_red;
        uint8_t m_green;
        uint8_t m_blue;
        uint8_t m_alpha;
    };

    // the Bitmap is a 2D array of pixels
    class Bitmap
    {

    public:
        Bitmap(uint32_t width, uint32_t height, Pixel color)
        {
            Pixel *tmp_array = new Pixel[width * height]; // easier to keep it 1D and transform to 2D as needed

            for (int i = 0; i < (width * height); i++)
            {
                tmp_array[i] = color;
            }

            m_data = tmp_array;
            m_width = width;
            m_height = height;
        }

        Bitmap(uint32_t width, uint32_t height)
        {
            Pixel *tmp_array = new Pixel[width * height]; // easier to keep it 1D and transform to 2D as needed

            for (int i = 0; i < (width * height); i++)
            {
                // tmp_array[i].set(0, 0, 0, 0);
                tmp_array[i] = Pixel(0, 0, 0, 0);
            }

            m_data = tmp_array;
            m_width = width;
            m_height = height;
        }

        ~Bitmap()
        {
            delete[] m_data;
        }

        Pixel pixel_at(int x, int y)
        {
            Pixel ret = m_data[(m_width * y) + x];
            return ret;
        }

        void set_pixel(Pixel p, int x, int y)
        {
            if ((x >= 0) && (x < m_width) && (y >= 0) && (y < m_height))
            {
                Pixel background = pixel_at(x, y);

                uint8_t new_r = (p.alpha() * (background.red() - p.red()) + background.red());
                uint8_t new_g = (p.alpha() * (background.green() - p.green()) + background.green());
                uint8_t new_b = (p.alpha() * (background.blue() - p.blue()) + background.blue());
                p.set(new_r, new_g, new_b, p.alpha());

                m_data[(m_width * y) + x] = p;
            }
        }

        void set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a, int x, int y)
        {
            Pixel tmp(r, g, b, a);
            set_pixel(tmp.red(), tmp.green(), tmp.blue(), tmp.alpha(), x, y);
            m_data[(m_width * y) + x] = tmp;
        }

        unsigned int width()
        {
            return m_width;
        }

        unsigned int height()
        {
            return m_height;
        }

        void stamp_with(gfx::Bitmap &src, shapes::Point location)
        {
            unsigned int src_h = src.height();
            unsigned int src_w = src.width();

            gfx::Pixel tmp;
            for (int dx = 0; dx < src_w; dx++)
            {
                for (int dy = 0; dy < src_h; dy++)
                {
                    if ((location.x + dx < m_width) && (location.y + dy < m_height))
                    {
                        set_pixel(src.pixel_at(dx, dy), location.x + dx, location.y + dy);
                    }
                }
            }
        }
        Pixel *m_data; // TODO: THIS SHOULD BE PRIVATE, but no better way to get it into SDL_interface for now
    private:
        int m_width;
        int m_height;
    };

}
#endif // GFX_TYPES_HPP