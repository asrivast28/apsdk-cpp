#include "Anml.hpp"

#include "AnmlMacro.hpp"
#include "AnmlNetwork.hpp"


namespace ap {

Anml::Anml(
)
{
  m_anml = AP_CreateAnml();
}

Anml::Anml(
  const Anml&& other
)
{
  m_anml = other.m_anml;
}

AnmlMacro
Anml::loadMacro(
  const std::string& fileName
)
{
  ap_macro_def_t* macro = nullptr;
  AP_LoadAnmlMacro(m_anml, macro, nullptr, fileName.c_str(), nullptr, AP_OPT_DEFAULT, nullptr);
  return AnmlMacro(macro);
}


AnmlNetwork
Anml::createWorkspace(
  const std::string& anmlId
)
{
  ap_anml_network_t* network = nullptr;
  AP_CreateAutomataNetwork(m_anml, network, anmlId.c_str());
  return AnmlNetwork(network);
}

Automaton
Anml::compile(
)
{
  ap_automaton_t* automaton = nullptr;
  ap_element_map_t* elementMap = nullptr;
  AP_CompileAnml(m_anml, automaton, elementMap, nullptr, nullptr, AP_OPT_DEFAULT, 0);
  return Automaton(automaton, elementMap);
}

Anml::~Anml(
)
{
  AP_DestroyAnml(m_anml);
}

} // namespace ap
