#include "Incubator/Presenter/DataChangedEventHandlers/TimeInformationDataChangedEventHandler.h"

#include "TimeUtils/TimeSettings.h"

namespace Incubator
{
TimeInformationDataChangedEventHandler::TimeInformationDataChangedEventHandler()
    : m_Model{nullptr}, m_View{nullptr}
{
}

TimeInformationDataChangedEventHandler::~TimeInformationDataChangedEventHandler()
{
}

void TimeInformationDataChangedEventHandler::OnUpdate(const TimeInformationData &data)
{
  TimeUtils::TimeSettings::SetIncubatorTimeInSeconds(data.m_CurrentTimestampInSecond);
  if (nullptr != m_Model)
  {
    m_Model->Update(data);
  }
  if (nullptr != m_View)
  {
    m_View->UpdateTimeInformationData(data);
  }
}
} // namespace Incubator
