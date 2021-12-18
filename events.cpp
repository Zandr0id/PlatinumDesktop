#include "events.hpp"

Event::Event(const EventType type, const EventData data)
{
    m_type = type;
    m_data = data;
}
