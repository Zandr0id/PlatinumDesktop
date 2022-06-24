#include "EventQueue.hpp"

EventQueue::EventQueue()
{
}

EventQueue::~EventQueue()
{
}

Event EventQueue::PopNextEvent()
{
    Event ret = m_event_queue.front();
    m_event_queue.pop();
    return ret;
}

void EventQueue::PushEvent(Event e)
{
    m_event_queue.push(e);
}

bool EventQueue::IsEmpty()
{
    return m_event_queue.empty();
}