#include "Automaton.hpp"

#include <cstdio>

#include <micron/ap/ap_load.h>
#include <micron/ap/ap_element_map.h>
#include <micron/ap/ap_reload.h>


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

void
Automaton::getElementRef(
  const std::string& elementId
) const
{
  ap_anml_element_ref_t* elementRef = 0;
  AP_GetElementRefFromElementId(*m_elementMap, elementRef, elementId.c_str());
}

void
Automaton::setSymbol(
)
{
  AP_SetSymbol(*m_automaton, *m_elementMap, 0, 0);
}

void
Automaton::save(
  const std::string& fileName
) const
{
  FILE* f = fopen(fileName.c_str(), "wb");
  int pos = ftell(f);
  AP_Save(*m_automaton, pos); 
  fclose(f);
}


Automaton::~Automaton(
)
{
  AP_Destroy(*m_automaton);
  AP_DestroyElementMap(*m_elementMap);
  m_automaton = 0;
  m_elementMap = 0;
}

} // namespace ap
