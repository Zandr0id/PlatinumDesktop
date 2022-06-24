/*
    Event queues will probably be used lots of places, so this is just a formal
    wrapper for a queue to make it easier to use
*/
#pragma once

#include <queue>
#include "event_types.hpp"

class EventQueue
{
public:
    EventQueue();
    ~EventQueue();
    Event PopNextEvent();
    void PushEvent(Event e);
    bool IsEmpty();

private:
    std::queue<Event> m_event_queue;
};