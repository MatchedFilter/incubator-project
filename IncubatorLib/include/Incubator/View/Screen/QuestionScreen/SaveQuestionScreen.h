#ifndef INCUBATOR_SAVEQUESTIONSCREEN_H
#define INCUBATOR_SAVEQUESTIONSCREEN_H
#include "AQuestionScreen.h"
#include "Incubator/IncubatorData/SettingsData.h"
namespace Incubator
{
class SaveQuestionScreen : public AQuestionScreen
{
public:
  SaveQuestionScreen();
  ~SaveQuestionScreen();

  void OnInitial();

  void Initialize(Lcd2004 *tc2004Lcd, DataChangedEventHandlers *eventHandlers,
                  SettingsData *changedSettingsData);

protected:
  virtual void NotifyChangedData() override;

private:
  SettingsData *m_ChangedSettingsData;
};
} // namespace Incubator

#endif // INCUBATOR_SAVEQUESTIONSCREEN_H
