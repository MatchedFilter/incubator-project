#ifndef INCUBATOR_INCUBATORDATA_TIMEINFORMATIONDATA_H
#define INCUBATOR_INCUBATORDATA_TIMEINFORMATIONDATA_H
#include "MF/ByteStreamReader.h"
#include "MF/ByteStreamWriter.h"
namespace Incubator
{
struct TimeInformationData
{
public:
  uint32_t m_CurrentTimestampInSecond;

  static constexpr uint32_t DATA_SIZE = static_cast<uint32_t>(sizeof(m_CurrentTimestampInSecond));

public:
  void Reset();
  void Copy(const TimeInformationData &other);
  template <uint32_t TSIZE>
  bool Serialize(MF::ByteStreamWriter<TSIZE> &writer) const;
  template <uint32_t TSIZE>
  bool Deserialize(MF::ByteStreamReader<TSIZE> &reader);
};

template <uint32_t TSIZE>
bool TimeInformationData::Serialize(MF::ByteStreamWriter<TSIZE> &writer) const
{
  bool bResult = false;
  if (writer.GetRemainingSize() >= DATA_SIZE)
  {
    bResult = true;
    (void) writer.Write4Bytes(m_CurrentTimestampInSecond, MF::ENDIAN_TYPE_BIG);
  }
  return bResult;
}

template <uint32_t TSIZE>
bool TimeInformationData::Deserialize(MF::ByteStreamReader<TSIZE> &reader)
{
  bool bResult = false;
  if (reader.GetRemainingSize() >= DATA_SIZE)
  {
    bResult = true;
    (void) reader.Read4Bytes(m_CurrentTimestampInSecond, MF::ENDIAN_TYPE_BIG);
  }
  return bResult;
}

} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_TIMEINFORMATIONDATA_H
