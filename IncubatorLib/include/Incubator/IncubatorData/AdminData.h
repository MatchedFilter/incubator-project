#ifndef INCUBATOR_INCUBATORDATA_ADMINDATA_H
#define INCUBATOR_INCUBATORDATA_ADMINDATA_H
#include "MF/ByteStreamReader.h"
#include "MF/ByteStreamWriter.h"
namespace Incubator
{
struct AdminData
{
public:
  int32_t m_P;
  int32_t m_I;
  int32_t m_D;
  uint8_t m_UpperHumidityDifference;
  uint8_t m_LowerHumidityDifference;

  static constexpr uint32_t DATA_SIZE =
    static_cast<uint32_t>(sizeof(m_P)) + static_cast<uint32_t>(sizeof(m_I)) +
    static_cast<uint32_t>(sizeof(m_D)) + static_cast<uint32_t>(sizeof(m_UpperHumidityDifference)) +
    static_cast<uint32_t>(sizeof(m_LowerHumidityDifference));

public:
  void Reset();
  void Copy(const AdminData &other);

  template <uint32_t TSIZE>
  bool Serialize(MF::ByteStreamWriter<TSIZE> &writer) const;
  template <uint32_t TSIZE>
  bool Deserialize(MF::ByteStreamReader<TSIZE> &reader);
};

template <uint32_t TSIZE>
bool AdminData::Serialize(MF::ByteStreamWriter<TSIZE> &writer) const
{
  bool bResult = false;
  if (writer.GetRemainingSize() >= DATA_SIZE)
  {
    bResult = true;
    (void) writer.Write4Bytes(m_P, MF::ENDIAN_TYPE_BIG);
    (void) writer.Write4Bytes(m_I, MF::ENDIAN_TYPE_BIG);
    (void) writer.Write4Bytes(m_D, MF::ENDIAN_TYPE_BIG);
    (void) writer.WriteByte(m_UpperHumidityDifference);
    (void) writer.WriteByte(m_LowerHumidityDifference);
  }
  return bResult;
}
template <uint32_t TSIZE>
bool AdminData::Deserialize(MF::ByteStreamReader<TSIZE> &reader)
{
  bool bResult = false;
  if (reader.GetRemainingSize() >= DATA_SIZE)
  {
    bResult = true;
    (void) reader.Read4Bytes(m_P, MF::ENDIAN_TYPE_BIG);
    (void) reader.Read4Bytes(m_I, MF::ENDIAN_TYPE_BIG);
    (void) reader.Read4Bytes(m_D, MF::ENDIAN_TYPE_BIG);
    (void) reader.ReadByte(m_UpperHumidityDifference);
    (void) reader.ReadByte(m_LowerHumidityDifference);
  }
  return bResult;
}

} // namespace Incubator

#endif // INCUBATOR_INCUBATORDATA_ADMINDATA_H
