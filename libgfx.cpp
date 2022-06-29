#include "libgfx.hpp"
#include "libshapes.hpp"
#include <math.h>
#include <iostream>
#include <fstream>

// Circles
void gfx::draw_circle(Bitmap &bitmap, const int x0, const int y0, const unsigned int r)
{
    shapes::Circle circle = shapes::calculate_circle(x0, y0, r);

    for (int i = 0; i < circle.parimeter.size(); i++)
    {
        int x = circle.parimeter[i].x;
        int y = circle.parimeter[i].y;
        bitmap.set_pixel(gfx::draw_color, x, y);
    }
}

void gfx::fill_circle(Bitmap &bitmap, const int x0, const int y0, const unsigned int r)
{
    shapes::Circle circle = shapes::calculate_circle(x0, y0, r);

    for (int i = 0; i < circle.parimeter.size(); i++)
    {
        int x = circle.parimeter[i].x;
        int y = circle.parimeter[i].y;
        draw_line(bitmap, x, y, x0, y);
    }
}

// Ellipses
void gfx::draw_ellipse(Bitmap &bitmap, const int x, const int y, const unsigned int r_w, const unsigned int r_h)
{
    shapes::Ellipse ellipse = shapes::calculate_ellipse(x, y, r_w, r_h);
    for (int i = 0; i < ellipse.parimeter.size(); i++)
    {
        // draw_color.set(0, ((float)i / float(ellipse.parimeter.size())) * 255, 0, 255);
        int x = ellipse.parimeter[i].x;
        int y = ellipse.parimeter[i].y;
        bitmap.set_pixel(gfx::draw_color, x, y);
    }
}

// Arcs
void gfx::draw_arc(Bitmap &bitmap, const int x, const int y, const unsigned int r, const unsigned short theta_1, const unsigned short theta_2)
{
    shapes::Arc arc = shapes::calculate_arc(x, y, r, theta_1, theta_2);
    for (int i = 0; i < arc.parimeter.size(); i++)
    {
        int x = arc.parimeter[i].x;
        int y = arc.parimeter[i].y;
        bitmap.set_pixel(gfx::draw_color, x, y);
    }
}

// Lines
void gfx::draw_line(Bitmap &bitmap, const int x0, const int y0, const int x1, const int y1)
{
    shapes::Line line = shapes::calculate_line(x0, y0, x1, y1);

    for (int i = 0; i < line.points.size(); i++)
    {
        bitmap.set_pixel(gfx::draw_color, line.points[i].x, line.points[i].y);
    }
}

void gfx::draw_line(Bitmap &bitmap, const shapes::Point a, const shapes::Point b)
{
    draw_line(bitmap, a.x, a.y, b.x, b.y);
}

void gfx::draw_line(Bitmap &bitmap, shapes::Line line)
{
    draw_line(bitmap, line.a.x, line.a.y, line.b.x, line.b.y);
}

// Rectangles
void gfx::draw_rect(Bitmap &bitmap, const int x, const int y, const unsigned int h, const unsigned int w)
{
    shapes::Rect rect = shapes::calculate_rect(x, y, w, h);
    draw_line(bitmap, rect.sides.a);
    draw_line(bitmap, rect.sides.b);
    draw_line(bitmap, rect.sides.c);
    draw_line(bitmap, rect.sides.d);
}

void gfx::draw_rect(Bitmap &bitmap, const shapes::Point origin, const unsigned int h, const unsigned int w)
{
    draw_rect(bitmap, origin.x, origin.y, h, w);
}

void gfx::fill_rect(Bitmap &bitmap, const int x, const int y, const unsigned int h, const unsigned int w)
{
    shapes::Rect rect = shapes::calculate_rect(x, y, w + 1, h + 1);
    for (int i = 0; i < rect.sides.a.points.size(); i++)
    {
        draw_line(bitmap, rect.sides.a.points[i], rect.sides.c.points[i]);
    }
}

void gfx::fill_rect(Bitmap &bitmap, const shapes::Point origin, const unsigned int h, const unsigned int w)
{
    fill_rect(bitmap, origin.x, origin.y, h, w);
}

int gfx::load_bitmap(gfx::Bitmap *dest, std::string file)
{
    BMP_FileHeader fh;
    BMP_InfoHeader ih;
    BMP_ColorHeader ch;
    std::ifstream in_file{file.c_str(), std::ios_base::binary};
    if (in_file)
    {
        in_file.read((char *)&fh, sizeof(fh));
        if (fh.file_type != 0x4D42)
        {
            return -1;
        }
        in_file.read((char *)&ih, sizeof(ih));

        if (ih.bit_count == 32)
        {
            // Check if the file has bit mask color information
            if (ih.size >= (sizeof(BMP_InfoHeader) + sizeof(BMP_ColorHeader)))
            {
                in_file.read((char *)&ch, sizeof(ch));
                // Check if the pixel data is stored as BGRA and if the color space type is sRGB
                BMP_ColorHeader expected_color_header;
                if (expected_color_header.red_mask != ch.red_mask ||
                    expected_color_header.blue_mask != ch.blue_mask ||
                    expected_color_header.green_mask != ch.green_mask ||
                    expected_color_header.alpha_mask != ch.alpha_mask)
                {
                    return -2;
                }
                if (expected_color_header.color_space_type != ch.color_space_type)
                {
                    return -3;
                }
            }
            else
            {
                return -4;
            }
        }

        in_file.seekg(fh.offset_data, in_file.beg);

        if (ih.bit_count == 32) // Only 32 bit uses a color header
        {
            ih.size = sizeof(BMP_InfoHeader) + sizeof(BMP_ColorHeader);
            fh.offset_data = sizeof(BMP_InfoHeader) + sizeof(BMP_ColorHeader) + sizeof(BMP_FileHeader);
        }
        else
        {
            ih.size = sizeof(BMP_InfoHeader);
            fh.offset_data = sizeof(BMP_InfoHeader) + sizeof(BMP_FileHeader);
        }
        fh.file_size = fh.offset_data;

        Bitmap *ret = new Bitmap(ih.width, ih.height); // make the new bitmap

        if (0 == (ih.width % 4)) // no need for padding?
        {
            for (int i = 0; i < ih.width; i++)
            {
                for (int j = 0; j < ih.height; j++)
                {
                    Pixel p;
                    p.set(in_file.get(), in_file.get(), in_file.get(), in_file.get());
                    ret->set_pixel(p, i, j);
                }
            }
            dest = ret;
        }
        else
        {
            return -5;
        }
        return 1;
    }
    else
    {
        return -6;
    }
}