#ifndef APSDK_DEVICE_HPP_
#define APSDK_DEVICE_HPP_

#include "Automaton.hpp"

#include <limits>
#include <string>

#include <micron/ap/ap_anml.h>

namespace ap {

/**
 * @brief  Wrapper class for ap_device_t and ap_rto_t functionality.
 */
class Device {
public:
  Device(const std::string&, const int = -1);

  // Do NOT allow copying of this object.
  // The underlying instance is not "shareable".
  Device(const Device&) = delete;

  void
  load(Automaton&&, const unsigned = 0);

  std::vector<std::pair<ElementRef, size_t> >
  search(std::vector<unsigned char>&, const size_t = std::numeric_limits<size_t>::max());

  void
  unload();

  ~Device();

private:
  // ap_device_t instance that this object refers to.
  ap_device_t m_device;
  // ap_rto_t instance that this object refers to.
  ap_rto_t m_runtimeObject;
}; // class Device

} // namespace ap

#endif // APSDK_DEVICE_HPP_
