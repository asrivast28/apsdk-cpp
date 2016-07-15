#ifndef APSDK_ANMLMACRO_HPP_
#define APSDK_ANMLMACRO_HPP_

#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

class AnmlMacro {
public:
  AnmlMacro(ap_macro_def_t*);

  AnmlMacro(const AnmlMacro&);

  void 
  getParamFromName(const std::string&) const;

  ~AnmlMacro();

private:
  ap_macro_def_t* m_macro;
}; // class AnmlMacro

} // namespace ap

#endif // APSDK_ANMLMACRO_HPP_
