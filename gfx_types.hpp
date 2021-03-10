#ifndef GFX_TYPES_HPP
#define GFX_TYPES_HPP
#include <stdint.h>
#include <iostream>

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

private:
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
    uint8_t m_alpha;
};

//the Bitmap is a 2D array of pixels
class Bitmap
{
public:
    Bitmap(uint32_t width, uint32_t height)
    {
        Pixel *tmp_array = new Pixel[width * height]; //easier to keep it 1D and transform to 2D as needed

        for (int i = 0; i < (width * height); i++)
        {
            tmp_array[i].set(0, 0, 0, 0);
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

    void set_pixel(Pixel p, unsigned int x, unsigned int y)
    {
        m_data[(m_width * y) + x] = p;
    }

    void set_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a, unsigned int x, unsigned int y)
    {
        Pixel tmp(r, g, b, a);
        m_data[(m_width * y) + x] = tmp;
    }

    void width(int *width)
    {
        *width = m_width;
    }

    void height(int *height)
    {
        *height = m_height;
    }

private:
    Pixel *m_data;
    int m_width;
    int m_height;
};

#endif //GFX_TYPES_HPP