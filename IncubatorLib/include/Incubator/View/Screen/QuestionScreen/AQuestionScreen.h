#ifndef INCUBATOR_AQUESTIONSCREEN_H
#define INCUBATOR_AQUESTIONSCREEN_H
#include "EnumQuestionSelection.h"
#include "Incubator/Lcd2004.h"
#include "Incubator/View/DataChangedEventHandler/DataChangedEventHandlers.h"
#include "Incubator/View/Screen/AScreen.h"
#include "Incubator/View/Screen/EnumScreenType.h"

namespace Incubator
{
class AQuestionScreen : public AScreen
{
public:
  AQuestionScreen(const EnumScreenType screenType);
  ~AQuestionScreen();

  void OnInitial() override;

  virtual void Reset() override final;
  virtual void Run() override final;
  void OnUserAction(const JoystickEvent &event) override final;

protected:
  void Initialize(Lcd2004 *tc2004Lcd, DataChangedEventHandlers *eventHandlers);
  virtual void NotifyChangedData() = 0;
  virtual EnumScreenType GetNextScreenWhenYesSelected() const;

protected:
  Lcd2004 *m_Lcd;
  EnumQuestionSelection m_QuestionSelection;
  DataChangedEventHandlers *m_DataChangedEventHandlers;

private:
};
} // namespace Incubator

#endif // INCUBATOR_AQUESTIONSCREEN_H
