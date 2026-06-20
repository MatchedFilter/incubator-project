#include "Incubator/Controller/HumidityController.h"

#include "bsp_config.h"

namespace Incubator
{

HumidityController::HumidityController()
    : m_bIsHumidityValid(false), m_UpperThresholdInPercentage(0), m_LowerThresholdInPercentage(0),
      m_OnTimeInMillisecond(0), m_OffTimeInMillisecond(0), m_StartTimeInMillisecond(0),
      m_LastState(STATE_OFF)
{
}

HumidityController::~HumidityController()
{
}

void HumidityController::SetHumidityThresholds(const uint8_t upperThresholdInPercentage,
                                               const uint8_t lowerThresholdInPercentage)
{
  m_UpperThresholdInPercentage = upperThresholdInPercentage;
  m_LowerThresholdInPercentage = lowerThresholdInPercentage;
}

EnumState HumidityController::Control(const uint8_t &humidityInPercentage)
{
  EnumState state = STATE_OFF;
  if (m_bIsHumidityValid)
  {
    if (humidityInPercentage < m_LowerThresholdInPercentage)
    {

      const uint64_t currentTimeStampInMillisecond = bsp_get_time_in_ms();
      m_OffTimeInMillisecond =
        static_cast<uint32_t>(currentTimeStampInMillisecond - m_StartTimeInMillisecond);
      m_StartTimeInMillisecond = currentTimeStampInMillisecond;
      state                    = STATE_ON;
    }
    else if (humidityInPercentage > m_UpperThresholdInPercentage)
    {
      const uint64_t currentTimeStampInMillisecond = bsp_get_time_in_ms();
      m_OnTimeInMillisecond =
        static_cast<uint32_t>(currentTimeStampInMillisecond - m_StartTimeInMillisecond);
      m_StartTimeInMillisecond = currentTimeStampInMillisecond;
      state                    = STATE_OFF;
    }
    else
    {
      state = m_LastState;
    }
    m_LastState = state;
  }
  else
  {
    const uint64_t currentTimeStampInMillisecond = bsp_get_time_in_ms();
    const uint32_t timeDifferenceInMillisecond =
      static_cast<uint32_t>(currentTimeStampInMillisecond - m_StartTimeInMillisecond);
    if (STATE_ON == m_LastState)
    {
      if (timeDifferenceInMillisecond > m_OnTimeInMillisecond)
      {
        state                    = STATE_OFF;
        m_StartTimeInMillisecond = currentTimeStampInMillisecond;
        m_LastState              = state;
      }
    }
    else
    {
      if (timeDifferenceInMillisecond > m_OffTimeInMillisecond)
      {
        state                    = STATE_ON;
        m_StartTimeInMillisecond = currentTimeStampInMillisecond;
        m_LastState              = state;
      }
    }
  }
  return state;
}

void HumidityController::UpdateHumidityFailStatus(const bool bIsFailed)
{
  if (false == bIsFailed)
  {
    m_bIsHumidityValid = true;
  }
  else
  {
    m_bIsHumidityValid = false;
  }
}

} // namespace Incubator
