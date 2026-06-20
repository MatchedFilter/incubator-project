#include "Incubator/Model/InternalFlashModel.h"

#include "MF/MFBuffer.h"
#include "bsp_config.h"

namespace Incubator
{
static constexpr uint32_t WORD_SIZE_IN_BYTES = 4U;

static constexpr uint32_t SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET = 0U;
static constexpr uint32_t TIME_INFORMATION_DATA_START_MEMORY_ADDRESS_OFFSET =
  SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET + 32U;
static constexpr uint32_t PID_DATA_START_MEMORY_ADDRESS_OFFSET =
  TIME_INFORMATION_DATA_START_MEMORY_ADDRESS_OFFSET + 32U;
;

InternalFlashModel::InternalFlashModel()
{
}

InternalFlashModel::~InternalFlashModel()
{
}

bool InternalFlashModel::Update(const AdminData &data)
{
  bool result = false;
  static constexpr uint32_t ADMIN_DATA_WORD_SIZE =
    (AdminData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) +
    ((AdminData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));

  static constexpr uint32_t ADMIN_DATA_BUFFER_SIZE = WORD_SIZE_IN_BYTES * ADMIN_DATA_WORD_SIZE;
  MF::MFBuffer<ADMIN_DATA_BUFFER_SIZE> buffer;

  for (uint32_t i = static_cast<uint32_t>(0UL); i < ADMIN_DATA_BUFFER_SIZE; i++)
  {
    buffer.m_Buffer[i] = 0x00U;
  }
  buffer.m_Size = AdminData::DATA_SIZE;
  MF::ByteStreamWriter<ADMIN_DATA_BUFFER_SIZE> writer(buffer);
  if (data.Serialize(writer))
  {
    if (bsp_flash_write(m_FlashBaseAddress, PID_DATA_START_MEMORY_ADDRESS_OFFSET,
                        reinterpret_cast<const uint32_t *>(&buffer.m_Buffer[0]),
                        ADMIN_DATA_WORD_SIZE))
    {
      result = true;
    }
  }
  return result;
}

bool InternalFlashModel::Update(const SettingsData &data)
{
  bool result = false;
  static constexpr uint32_t SETTINGS_DATA_WORD_SIZE =
    (SettingsData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) +
    ((SettingsData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));

  static constexpr uint32_t SETTINGS_DATA_BUFFER_SIZE =
    WORD_SIZE_IN_BYTES * SETTINGS_DATA_WORD_SIZE;
  MF::MFBuffer<SETTINGS_DATA_BUFFER_SIZE> buffer;

  for (uint32_t i = static_cast<uint32_t>(0UL); i < SETTINGS_DATA_BUFFER_SIZE; i++)
  {
    buffer.m_Buffer[i] = 0x00U;
  }

  buffer.m_Size = SettingsData::DATA_SIZE;
  MF::ByteStreamWriter<SETTINGS_DATA_BUFFER_SIZE> writer(buffer);
  if (data.Serialize(writer))
  {
    if (bsp_flash_write(m_FlashBaseAddress, SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET,
                        reinterpret_cast<const uint32_t *>(&buffer.m_Buffer[0]),
                        SETTINGS_DATA_WORD_SIZE))
    {
      result = true;
    }
  }
  return result;
}

bool InternalFlashModel::Update(const TimeInformationData &data)
{
  bool result = false;
  static constexpr uint32_t TIME_INFORMATION_DATA_WORD_SIZE =
    (TimeInformationData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) +
    ((TimeInformationData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));

  static constexpr uint32_t TIME_INFORMATION_DATA_BUFFER_SIZE =
    WORD_SIZE_IN_BYTES * TIME_INFORMATION_DATA_WORD_SIZE;
  MF::MFBuffer<TIME_INFORMATION_DATA_BUFFER_SIZE> buffer;

  for (uint32_t i = static_cast<uint32_t>(0UL); i < TIME_INFORMATION_DATA_BUFFER_SIZE; i++)
  {
    buffer.m_Buffer[i] = 0x00U;
  }
  buffer.m_Size = TimeInformationData::DATA_SIZE;
  MF::ByteStreamWriter<TIME_INFORMATION_DATA_BUFFER_SIZE> writer(buffer);
  if (data.Serialize(writer))
  {
    if (bsp_flash_write(m_FlashBaseAddress, TIME_INFORMATION_DATA_START_MEMORY_ADDRESS_OFFSET,
                        reinterpret_cast<const uint32_t *>(&buffer.m_Buffer[0]),
                        TIME_INFORMATION_DATA_WORD_SIZE))
    {
      result = true;
    }
  }
  return result;
}

bool InternalFlashModel::Get(AdminData &data)
{
  bool result = false;
  static constexpr uint32_t ADMIN_DATA_WORD_SIZE =
    (AdminData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) +
    ((AdminData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));

  static constexpr uint32_t ADMIN_DATA_BUFFER_SIZE = WORD_SIZE_IN_BYTES * ADMIN_DATA_WORD_SIZE;
  MF::MFBuffer<ADMIN_DATA_BUFFER_SIZE> buffer;
  buffer.Reset();

  bsp_flash_read(m_FlashBaseAddress, PID_DATA_START_MEMORY_ADDRESS_OFFSET,
                 reinterpret_cast<uint32_t *>(&buffer.m_Buffer[0]), ADMIN_DATA_WORD_SIZE);
  buffer.m_Size = AdminData::DATA_SIZE;

  MF::ByteStreamReader<ADMIN_DATA_BUFFER_SIZE> reader(buffer);
  if (data.Deserialize(reader))
  {
    result = true;
  }

  return result;
}

bool InternalFlashModel::Get(SettingsData &data)
{
  bool result = false;
  static constexpr uint32_t SETTINGS_DATA_WORD_SIZE =
    (SettingsData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) +
    ((SettingsData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));

  static constexpr uint32_t SETTINGS_DATA_BUFFER_SIZE =
    WORD_SIZE_IN_BYTES * SETTINGS_DATA_WORD_SIZE;
  MF::MFBuffer<SETTINGS_DATA_BUFFER_SIZE> buffer;
  buffer.Reset();

  bsp_flash_read(m_FlashBaseAddress, SETTINGS_DATA_START_MEMORY_ADDRESS_OFFSET,
                 reinterpret_cast<uint32_t *>(&buffer.m_Buffer[0]), SETTINGS_DATA_WORD_SIZE);
  buffer.m_Size = SettingsData::DATA_SIZE;

  MF::ByteStreamReader<SETTINGS_DATA_BUFFER_SIZE> reader(buffer);
  if (data.Deserialize(reader))
  {
    result = true;
  }

  return result;
}

bool InternalFlashModel::Get(TimeInformationData &data)
{
  bool result = false;
  static constexpr uint32_t TIME_INFORMATION_DATA_WORD_SIZE =
    (TimeInformationData::DATA_SIZE / static_cast<uint32_t>(sizeof(uint32_t))) +
    ((TimeInformationData::DATA_SIZE % static_cast<uint32_t>(4UL)) != static_cast<uint32_t>(0UL));

  static constexpr uint32_t TIME_INFORMATION_DATA_BUFFER_SIZE =
    WORD_SIZE_IN_BYTES * TIME_INFORMATION_DATA_WORD_SIZE;
  MF::MFBuffer<TIME_INFORMATION_DATA_BUFFER_SIZE> buffer;
  buffer.Reset();

  bsp_flash_read(m_FlashBaseAddress, TIME_INFORMATION_DATA_START_MEMORY_ADDRESS_OFFSET,
                 reinterpret_cast<uint32_t *>(&buffer.m_Buffer[0]),
                 TIME_INFORMATION_DATA_WORD_SIZE);
  buffer.m_Size = TimeInformationData::DATA_SIZE;

  MF::ByteStreamReader<TIME_INFORMATION_DATA_BUFFER_SIZE> reader(buffer);
  if (data.Deserialize(reader))
  {
    result = true;
  }

  return result;
}

} // namespace Incubator
