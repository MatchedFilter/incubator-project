#include "Incubator/View/Screen/SensorsStatusScreen.h"

#include "TimeUtils/TimerManager.h"

namespace Incubator
{

void SensorsStatusScreen::PrintSensorStatus(const EnumSensorStatus &sensorStatus)
{
  if (SENSOR_STATUS_NO_ERROR == sensorStatus)
  {
    m_Lcd->Print("YOK");
  }
  else
  {
    m_Lcd->Print("VAR");
  }
}

SensorsStatusScreen::SensorsStatusScreen()
    : AScreen{SCREEN_TYPE_SENSORS_STATUS}, m_Lcd{nullptr},
      m_SelectedLine{SENSOR_STATUS_SCREEN_LINE_SHT31}, m_SensorStatusScreenUpdateTimerTask{nullptr}
{
}

SensorsStatusScreen::~SensorsStatusScreen()
{
}

void SensorsStatusScreen::Initialize(Lcd2004 *tc2004Lcd)
{
  m_Lcd = tc2004Lcd;
  m_SensorsStatusData.Reset();
  m_SensorStatusScreenUpdateTimerTask = TimeUtils::TimerManager::CreateMillisecondTimer();
  constexpr uint32_t SENSOR_STATUS_SCREEN_UPDATE_TIME_IN_MILLISECOND = static_cast<uint32_t>(200UL);
  m_SensorStatusScreenUpdateTimerTask->SetDuration(SENSOR_STATUS_SCREEN_UPDATE_TIME_IN_MILLISECOND);
}

void SensorsStatusScreen::OnInitial()
{
  Reset();

  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("[Sens");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_O);
  m_Lcd->Print("r Durumlar");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("]");
  m_Lcd->MoveCursor(1U, 0U);
  m_Lcd->Print("BME280: HATA ...");
  m_SensorStatusScreenUpdateTimerTask->Start();
}

void SensorsStatusScreen::Run()
{
  if (m_SensorStatusScreenUpdateTimerTask->IsFinished())
  {
    m_SensorStatusScreenUpdateTimerTask->Start();
    m_Lcd->MoveCursor(1U, 12U);
    PrintSensorStatus(m_SensorsStatusData.m_Bme280Status);
  }
}

void SensorsStatusScreen::OnUserAction(const JoystickEvent &event)
{
  if (event.bIsLeftPressed)
  {
    m_SensorStatusScreenUpdateTimerTask->Stop();
    SetNextScreen(SCREEN_TYPE_MENU);
  }
}

void SensorsStatusScreen::UpdateSensorsStatus(const SensorsStatusData &data)
{
  m_SensorsStatusData.Copy(data);
}

} // namespace Incubator
