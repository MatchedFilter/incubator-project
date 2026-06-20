#include "Incubator/IncubatorApp.h"

#include "Data/UsbData.h"
#include "Incubator/IncubatorData/EnumSensorStatus.h"
#include "TimeUtils/TimerManager.h"
#include "Utils/CacheManager.h"
#include "bsp_config.h"

#include <cstring>

namespace Incubator
{

auto IncubatorApp::ReadSensors(void)
{
  bool bme_sensor_is_ok = true;
  if (m_SensorReadingTimer->IsFinished())
  {
    m_SensorReadingTimer->Start();
    bsp_bme280_process_run();
  }

  uint8_t humidityInPercentage = 0U;
  if (bsp_bme280_read_humidity(&humidityInPercentage))
  {
    m_Presenter.UpdateHumidity(humidityInPercentage);
  }
  else
  {
    bme_sensor_is_ok = false;
    m_Presenter.OnHumidityFailure();
  }

  int32_t temperatureInMillidegree = 0;
  if (bsp_bme280_read_temperature(&temperatureInMillidegree))
  {
    m_Presenter.UpdateTemperature(temperatureInMillidegree);
  }
  else
  {
    bme_sensor_is_ok = false;
    m_Presenter.OnTemperatureFailure();
  }
  if (!bme_sensor_is_ok)
  {
    m_SensorsStatusData.m_Bme280Status = SENSOR_STATUS_ERROR;
  }
  else
  {
    m_SensorsStatusData.m_Bme280Status = SENSOR_STATUS_NO_ERROR;
  }
  m_Presenter.UpdateSensorsStatus(m_SensorsStatusData);
}

auto IncubatorApp::Initialize(void) -> void
{
  Data::UsbData usbData;
  usbData.m_TransmissionPeriodicity = 1000U;
  Utils::CacheManager::Write(usbData);

  m_Timer = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_Timer->SetDuration(250U);
  m_Timer->Start();

  m_SensorReadingTimer = TimeUtils::TimerManager::CreateMillisecondTimer();
  m_SensorReadingTimer->SetDuration(250U);
  m_SensorReadingTimer->Start();

  m_UsbTransmissionHandler.Initialize();

  m_Presenter.Initialize(&m_Lcd2004View, &m_InternalFlashModel);
}

auto IncubatorApp::Run(void) -> void
{
  if (m_Timer->IsFinished())
  {
    bsp_internal_led_toggle();
    m_Timer->Start();
  }
  m_UsbCommandHandler.Run();
  m_UsbTransmissionHandler.Run();

  m_Presenter.Run();
  m_Lcd2004View.Run();
}
} // namespace Incubator
