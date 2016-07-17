#include "Automaton.hpp"

#include <iostream>

#include <micron/ap/ap_load.h>
#include <micron/ap/ap_reload.h>
#include <micron/ap/sys/platform.h>
#if defined(LINUX32) || defined(LINUX64)
#include <fcntl.h>
#include <unistd.h>
#endif


namespace ap {

Automaton::Automaton(
) : m_automaton(0) 
{
}

Automaton::Automaton(
  const ap_automaton_t& automaton
) : m_automaton(automaton)
{
}

Automaton::Automaton(
  const std::string& fileName
) : m_automaton(0)
{
  file_descriptor_t fd;
#if defined(LINUX32) || defined(LINUX64)
	fd = open(fileName.c_str(),O_RDONLY, S_IRUSR);
#else
	//fd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#endif
  AP_Restore(&m_automaton, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  //CloseHandle(fd);
#endif
}

Automaton::Automaton(
  Automaton&& that
) : m_automaton(that.m_automaton)
{
  that.m_automaton = 0;
}

void
Automaton::setSymbol(
  ElementMap& elementMap, 
  SymbolChange& changes
)
{
  AP_SetSymbol(m_automaton, *elementMap, *changes, changes.count());
}

void
Automaton::save(
  const std::string& fileName
) const
{
  file_descriptor_t fd;
#if defined(LINUX32) || defined(LINUX64)
	fd = open(fileName.c_str(),O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR);
#else
	fd = CreateFileA(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
#endif
  AP_Save(m_automaton, fd);
#if defined(LINUX32) || defined(LINUX64)
  close(fd);
#else
  CloseHandle(fd);
#endif
}

void
Automaton::printInfo(
) const
{
  struct ap_automaton_info info;
  AP_GetInfo(m_automaton, &info, 0); 
  std::cout << "blocks_rect = " << info.blocks_rect<< std::endl;
  std::cout << "blocks_used = " << info.blocks_used<< std::endl;
  std::cout << "ste_count = " << info.ste_count<< std::endl;
  std::cout << "ste_grp_used = " << info.ste_grp_used << std::endl;
  std::cout << "counter_used = " << info.counter_used << std::endl;
  std::cout << "bool_used = " << info.bool_used << std::endl;
  std::cout << "match_res = " << info.match_res<< std::endl;
  std::cout << "clock_divisor = " << info.clock_divisor << std::endl;
}

Automaton::~Automaton(
)
{
  if (m_automaton != 0) {
    AP_Destroy(m_automaton);
    m_automaton = 0;
  }
}

} // namespace ap
