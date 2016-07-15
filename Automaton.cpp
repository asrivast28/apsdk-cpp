#include "Automaton.hpp"

#include <micron/ap/ap_load.h>
#include <micron/ap/ap_element_map.h>

namespace ap {

Automaton::Automaton(
  ap_automaton_t* automaton,
  ap_element_map_t* elementMap
) : m_automaton(automaton),
    m_elementMap(elementMap)
{
}

Automaton::Automaton(
  const Automaton&& other
)
{
  m_automaton = other.m_automaton;
  m_elementMap = other.m_elementMap;
}


Automaton::~Automaton(
)
{
  AP_Destroy(*m_automaton);
  AP_DestroyElementMap(*m_elementMap);
  m_automaton = nullptr;
  m_elementMap = nullptr;
}

} // namespace ap
