#ifndef INCUBATOR_INCUBATORDATA_SETTINGSDATA_H
#define INCUBATOR_INCUBATORDATA_SETTINGSDATA_H
#include "MF/ByteStreamReader.h"
#include "MF/ByteStreamWriter.h"
namespace Incubator
{
struct SettingsData
{
public:
  uint32_t m_TemperatureInMilliCelcius;
  uint32_t m_LastDaysTemperatureInMilliCelcius;
  uint8_t m_HumidityInPercentage;
  uint8_t m_LastDaysHumidityInPercentage;
  uint8_t m_TotalIncubationDayCount;
  uint8_t m_LastDaysCount;

  static constexpr uint32_t DATA_SIZE = static_cast<uint32_t>(
    sizeof(m_TemperatureInMilliCelcius) + sizeof(m_LastDaysTemperatureInMilliCelcius) +
    sizeof(m_HumidityInPercentage) + sizeof(m_LastDaysHumidityInPercentage) +
    sizeof(m_TotalIncubationDayCount) + sizeof(m_LastDaysCount));

public:
  void Reset();
  void Copy(const SettingsData &other);
  template <uint32_t TSIZE>
  bool Serialize(MF::ByteStreamWriter<TSIZE> &writer) const;
  template <uint32_t TSIZE>
  bool Deserialize(MF::ByteStreamReader<TSIZE> &reader);
};

template <uint32_t TSIZE>
bool SettingsData::Serialize(MF::ByteStreamWriter<TSIZE> &writer) const
{
  bool bResult = false;

  if (writer.GetRemainingSize() >= DATA_SIZE)
  {
    bResult = true;
    (void) writer.Write4Bytes(m_TemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
    (void) writer.Write4Bytes(m_LastDaysTemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
    (void) writer.WriteByte(m_HumidityInPercentage);
    (void) writer.WriteByte(m_LastDaysHumidityInPercentage);
    (void) writer.WriteByte(m_TotalIncubationDayCount);
    (void) writer.WriteByte(m_LastDaysCount);
  }
  return bResult;
}

template <uint32_t TSIZE>
bool SettingsData::Deserialize(MF::ByteStreamReader<TSIZE> &reader)
{
  bool bResult = false;
  if (reader.GetRemainingSize() >= DATA_SIZE)
  {
    bResult = true;
    (void) reader.Read4Bytes(m_TemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
    (void) reader.Read4Bytes(m_LastDaysTemperatureInMilliCelcius, MF::ENDIAN_TYPE_BIG);
    (void) reader.ReadByte(m_HumidityInPercentage);
    (void) reader.ReadByte(m_LastDaysHumidityInPercentage);
    (void) reader.ReadByte(m_TotalIncubationDayCount);
    (void) reader.ReadByte(m_LastDaysCount);
  }
  return bResult;
}

} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_SETTINGSDATA_H
