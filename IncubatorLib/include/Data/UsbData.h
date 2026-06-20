#ifndef DATA_USBDATA_H
#define DATA_USBDATA_H
#include <cstdint>
namespace Data
{
struct UsbData
{
  std::uint32_t m_TransmissionPeriodicity = 0U;
  bool m_HelpRequested                    = false;
  uint8_t m_LH                            = 0U;
  uint8_t m_UH                            = 0U;
  uint8_t m_H                             = 0U;
};
} // namespace Data
#endif // DATA_USBDATA_H
