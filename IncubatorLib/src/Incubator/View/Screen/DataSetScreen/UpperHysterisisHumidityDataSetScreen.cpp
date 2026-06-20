#include "Incubator/View/Screen/DataSetScreen/UpperHysterisisHumidityDataSetScreen.h"

namespace Incubator
{
UpperHysterisisHumidityDataSetScreen::UpperHysterisisHumidityDataSetScreen()
    : AHysterisisHumidityDataSetScreen(SCREEN_TYPE_DATA_SET_UPPER_HYSTERISIS)
{
}

UpperHysterisisHumidityDataSetScreen::~UpperHysterisisHumidityDataSetScreen()
{
}

uint8_t UpperHysterisisHumidityDataSetScreen::GetCurrentDifference() const
{
  return m_CurrentIncubatorInformationData->m_AdminData.m_UpperHumidityDifference;
}

uint8_t UpperHysterisisHumidityDataSetScreen::GetChangedDifference() const
{
  return m_ChangedIncubatorInformationData->m_AdminData.m_UpperHumidityDifference;
}

void UpperHysterisisHumidityDataSetScreen::SetChangedDifference(const uint8_t &difference)
{
  m_ChangedIncubatorInformationData->m_AdminData.m_UpperHumidityDifference = difference;
}

} // namespace Incubator
