#include "Incubator/View/Screen/DataSetScreen/PDataSetScreen.h"

namespace Incubator
{

PDataSetScreen::PDataSetScreen() : APidDataSetScreen(SCREEN_TYPE_DATA_SET_P)
{
}

PDataSetScreen::~PDataSetScreen()
{
}

int32_t PDataSetScreen::GetCurrentValue() const
{
  return m_CurrentIncubatorInformationData->m_AdminData.m_P;
}

int32_t PDataSetScreen::GetChangedValue() const
{
  return m_ChangedIncubatorInformationData->m_AdminData.m_P;
}

void PDataSetScreen::SetChangedValue(const int32_t value)
{
  m_ChangedIncubatorInformationData->m_AdminData.m_P = value;
}

} // namespace Incubator
