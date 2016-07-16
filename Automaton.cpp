#include "Automaton.hpp"

#include <iostream>

#include <micron/ap/ap_load.h>
#include <micron/ap/ap_element_map.h>
#include <micron/ap/ap_reload.h>
#include <micron/ap/sys/platform.h>
#if defined(LINUX32) || defined(LINUX64)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace ap {

Automaton::Automaton(
) : m_automaton(0),
    m_elementMap(0)
{
}

Automaton::Automaton(
  const ap_automaton_t& automaton,
  const ap_element_map_t& elementMap
) : m_automaton(automaton),
    m_elementMap(elementMap)
{
}

Automaton::Automaton(
  Automaton&& that
) : m_automaton(that.m_automaton),
    m_elementMap(that.m_elementMap)
{
  that.m_automaton = 0;
  that.m_elementMap = 0;
}

ElementRef
Automaton::getElementRef(
  const std::string& elementId
) const
{
  ap_anml_element_ref_t elementRef;
  AP_GetElementRefFromElementId(m_elementMap, &elementRef, elementId.c_str());
  return ElementRef(elementRef);
}

void
Automaton::setSymbol(
  SymbolChange& changes
)
{
  AP_SetSymbol(m_automaton, m_elementMap, *changes, changes.count());
}

void
Automaton::save(
  const std::string& fileName
) const
{
  file_descriptor_t fd;
#if defined(LINUX32) || defined(LINUX64)
	fd = open(fileName.c_str(),O_CREAT|O_RDWR, 0644);
#else
	fd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#endif
  AP_Save(m_automaton, fd);
}

void
Automaton::printInfo(
) const
{
  struct ap_automaton_info info;
  AP_GetInfo(m_automaton, &info, 0); 
  std::cout << "ste_grp_used = " << info.ste_grp_used << std::endl;
  std::cout << "ste_count = " << info.ste_count<< std::endl;
  std::cout << "match_res = " << info.match_res<< std::endl;
  std::cout << "blocks_used = " << info.blocks_used<< std::endl;
  std::cout << "blocks_rect = " << info.blocks_rect<< std::endl;

}

Automaton::~Automaton(
)
{
  if (m_automaton != 0) {
    AP_Destroy(m_automaton);
    m_automaton = 0;
  }
  if (m_elementMap != 0) {
    AP_DestroyElementMap(m_elementMap);
    m_elementMap = 0;
  }
}

} // namespace ap
