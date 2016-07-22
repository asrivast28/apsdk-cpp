#include "Device.hpp"

#include "APCall.hpp"

#include <cstring>

#include <micron/ap/ap_load.h>


namespace ap {

/**
 * @brief  Constructor for creating the object for a given device name.
 *
 * @param deviceName  Name of the device to be opened.
 * @param svReserve   Number of state vectors to be reserved.
 *                    Defaults to -1, which reserves all the vectors.
 */
Device::Device(
  const std::string& deviceName,
  const int svReserve
) : m_device(0),
    m_runtimeObject(0)
{
  // Reserve all the state vectors.
  APCALL_CHECK(AP_OpenDevice)(&m_device, deviceName.c_str(), svReserve);
}

/**
 * @brief  Loads the given automaton into the given load region on the device.
 *
 * @param automaton   The automaton to be loaded on the device.
 * @param loadRegion  The load region to be used. Defaults to 0.
 */
void
Device::load(
  Automaton&& automaton,
  const unsigned loadRegion
)
{
  APCALL_CHECK(AP_Load)(m_device, &m_runtimeObject, loadRegion, *automaton, static_cast<void*>(0), static_cast<const char*>(0));
  // Invalidate the underlying ap_automaton_t pointer so that AP_Destroy is not called on it.
  automaton.m_automaton = 0;
}

/**
 * @brief  Searches the automaton using the given data.
 *
 * @param data  The data to be streamed to the device.
 */
std::vector<std::pair<ElementRef, size_t> >
Device::search(
  void* const data,
  const unsigned dataSize
)
{
  ap_flow_t flow;
  APCALL_CHECK(AP_OpenFlow)(m_device, &flow, m_runtimeObject, static_cast<void*>(0));

  struct ap_flow_chunk flowChunk;
  memset(&flowChunk, 0, sizeof(flowChunk));
  flowChunk.data = data;
  flowChunk.length = dataSize;

  struct ap_flow_data flowData;
  memset(&flowData, 0, sizeof(flowData));
  flowData.flow = flow;
  flowData.chunks = &flowChunk;
  flowData.chunk_count = 1;

  struct ap_completion complete;
  APCALL_CHECK(AP_ScanFlows)(m_device, &flowData, 1, &complete);
  APCALL_CHECK(AP_Wait)(m_device, &complete, 0);

  struct ap_match_result result;

  std::vector<std::pair<ElementRef, size_t> > allResults;
  while (APCALL_CHECK(AP_GetMatches)(m_device, &result, 1) > 0) {
    size_t byteOffset = result.byte_offset;
    ap_anml_element_ref_t elementRef = result.report_alias.elementRef;
    allResults.push_back(std::make_pair(ElementRef(elementRef), byteOffset));
  }

  APCALL_CHECK(AP_CloseFlow)(m_device, flow);
  return allResults;
}

/**
 * @brief  Unload the currently loaded runtime object from the device.
 */
void
Device::unload(
)
{
  if (m_runtimeObject != 0) {
    APCALL_CHECK(AP_Unload)(m_device, m_runtimeObject);
    m_runtimeObject = 0;
  }
}

/**
 * @brief  Default destructor.
 */
Device::~Device(
)
{
  if (m_device != 0) {
    APCALL_CHECK(AP_CloseDevice)(m_device);
    m_device = 0;
  }
}

} // namespace ap
