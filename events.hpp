#pragma once
#include "libgfx.hpp"

typedef enum EventType
{
    CREATE_WINDOW
} EventType;

typedef struct CreateWindowEventData
{
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
} CreateWindowEventData;

typedef union EventData
{
    CreateWindowEventData create_window_event;
} EventData;

typedef struct Event
{
    EventType m_type;
    EventData m_data;
    Event(const EventType type, const EventData data);
} Event;