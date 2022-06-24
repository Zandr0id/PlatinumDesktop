#pragma once
#include "libgfx.hpp"

typedef enum EventType
{
    CREATE_WINDOW,
    MOUSE_MOVE,
    MOUSE_BUTTON
} EventType;

typedef struct CreateWindowEventData
{
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
    CreateWindowEventData(unsigned int new_x, unsigned int new_y, unsigned int new_w, unsigned int new_h)
    {
        x = new_x;
        y = new_y;
        w = new_w;
        h = new_h;
    }
} CreateWindowEventData;

typedef struct MouseMoveEvent
{
    unsigned int x;
    unsigned int y;
    MouseMoveEvent(unsigned int new_x, unsigned int new_y)
    {
        x = new_x;
        y = new_y;
    }
} MouseMoveEvent;

typedef struct MouseButtonEvent
{
    bool left_down;
    bool right_down;
    MouseButtonEvent(bool left, bool right)
    {
        left_down = left;
        right_down = right;
    }
} MouseButtonEvent;

typedef union EventData
{
    CreateWindowEventData create_window_event;
    MouseMoveEvent mouse_move_event;
    MouseButtonEvent mouse_button_event;
    EventData(){};
} EventData;

typedef struct Event
{
    EventType type;
    EventData data;
    Event(){};
} Event;