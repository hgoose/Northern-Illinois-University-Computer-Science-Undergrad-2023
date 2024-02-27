#ifndef SHAPES_H
#define SHAPES_H

struct point
{
    int x = 0;
    int y = 0;

    point() = default;

    point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

struct rectangle
{
    point origin;
    int width = 0;
    int height = 0;

    rectangle() = default;

    rectangle(point origin, int width, int height)
    {
        this->origin = origin;
        this->width = width;
        this->height = height;
    }
};

#endif
