#include "Incubator/View/Screen/DataSetScreen/DDataSetScreen.h"

namespace Incubator
{

DDataSetScreen::DDataSetScreen() : APidDataSetScreen(SCREEN_TYPE_DATA_SET_D)
{
}

DDataSetScreen::~DDataSetScreen()
{
}

int32_t DDataSetScreen::GetCurrentValue() const
{
  return m_CurrentIncubatorInformationData->m_AdminData.m_D;
}

int32_t DDataSetScreen::GetChangedValue() const
{
  return m_ChangedIncubatorInformationData->m_AdminData.m_D;
}

void DDataSetScreen::SetChangedValue(const int32_t value)
{
  m_ChangedIncubatorInformationData->m_AdminData.m_D = value;
}

} // namespace Incubator
