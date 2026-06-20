#ifndef INCUBATOR_TIMERESETQUESTIONSCREEN_H
#define INCUBATOR_TIMERESETQUESTIONSCREEN_H
#include "AQuestionScreen.h"
#include "Incubator/IncubatorData/TimeInformationData.h"
namespace Incubator
{
class TimeResetQuestionScreen : public AQuestionScreen
{
public:
  TimeResetQuestionScreen();
  ~TimeResetQuestionScreen();

  void OnInitial();

  void Initialize(Lcd2004 *tc2004Lcd, DataChangedEventHandlers *eventHandlers,
                  TimeInformationData *changedTimeInformationData);

protected:
  virtual void NotifyChangedData() override;

private:
  TimeInformationData *m_ChangedTimeInformationData;
};
} // namespace Incubator

#endif // INCUBATOR_TIMERESETQUESTIONSCREEN_H
