#include "Incubator/View/Screen/DataSetScreen/APidDataSetScreen.h"

#include "Utils/StringUtils.h"

namespace Incubator
{

APidDataSetScreen::APidDataSetScreen(const EnumScreenType screenType) : ADataSetScreen(screenType)
{
}

APidDataSetScreen::~APidDataSetScreen()
{
}

static auto GetPidValueString(const int32_t value, char (&chrArr)[11]);

static auto GetPidValueString(const int32_t value, char (&chrArr)[11])
{
  const int32_t positiveValue = (value < 0) ? -value : value;
  uint32_t index              = 0U;
  if (value < 0)
  {
    chrArr[index++] = '-';
  }
  index += Utils::StringUtils::ToCharArray(positiveValue, chrArr, index);
  for (uint32_t i = index; i < 16U; i++)
  {
    chrArr[i] = ' ';
  }
}

void APidDataSetScreen::PrintCurrentData() const
{
  char valueString[11] = {0U};
  GetPidValueString(GetCurrentValue(), valueString);
  m_Lcd->Print(valueString);
}

void APidDataSetScreen::PrintNewData() const
{

  char valueString[11] = {0U};
  GetPidValueString(GetChangedValue(), valueString);
  m_Lcd->Print(valueString);
}

void APidDataSetScreen::OnIncrementHighEvent()
{
  const int32_t nextValue = GetChangedValue() + HIGH_INCREMENT_CONSTANT;
  int32_t resultValue     = MAX_ALLOWED_CONSTANT;
  if (nextValue < MAX_ALLOWED_CONSTANT)
  {
    resultValue = nextValue;
  }
  SetChangedValue(resultValue);
}

void APidDataSetScreen::OnIncrementLowEvent()
{
  const int32_t nextValue = GetChangedValue() + LOW_INCREMENT_CONSTANT;
  int32_t resultValue     = MAX_ALLOWED_CONSTANT;
  if (nextValue < MAX_ALLOWED_CONSTANT)
  {
    resultValue = nextValue;
  }
  SetChangedValue(resultValue);
}

void APidDataSetScreen::OnDecrementHighEvent()
{
  const int32_t changedValue = GetChangedValue();
  int32_t resultValue        = MIN_ALLOWED_CONSTANT;
  const int32_t nextValue    = changedValue - HIGH_INCREMENT_CONSTANT;
  if (nextValue > MIN_ALLOWED_CONSTANT)
  {
    resultValue = nextValue;
  }
  SetChangedValue(resultValue);
}

void APidDataSetScreen::OnDecrementLowEvent()
{
  const int32_t changedValue = GetChangedValue();
  int32_t resultValue        = MIN_ALLOWED_CONSTANT;
  const int32_t nextValue    = changedValue - LOW_INCREMENT_CONSTANT;
  if (nextValue > MIN_ALLOWED_CONSTANT)
  {
    resultValue = nextValue;
  }

  SetChangedValue(resultValue);
}

void APidDataSetScreen::NotifyChangedData()
{
  m_DataChangedEventHandlers->m_AdminDataChangedEventHandler->OnUpdate(
    m_ChangedIncubatorInformationData->m_AdminData);
}

EnumScreenType APidDataSetScreen::GetNextScreenForYesSelection() const
{
  return SCREEN_TYPE_TEMPERATURE_PID;
}

EnumScreenType APidDataSetScreen::GetNextScreenForNoSelection() const
{
  return SCREEN_TYPE_TEMPERATURE_PID;
}

} // namespace Incubator
