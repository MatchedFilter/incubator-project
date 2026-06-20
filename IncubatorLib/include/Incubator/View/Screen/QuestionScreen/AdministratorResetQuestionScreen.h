#ifndef INCUBATOR_AdministratorResetQuestionScreen_H
#define INCUBATOR_AdministratorResetQuestionScreen_H
#include "AQuestionScreen.h"
#include "Incubator/IncubatorData/AdminData.h"
namespace Incubator
{
class AdministratorResetQuestionScreen : public AQuestionScreen
{
public:
  AdministratorResetQuestionScreen();
  ~AdministratorResetQuestionScreen();

  void OnInitial();

  void Initialize(Lcd2004 *tc2004Lcd, DataChangedEventHandlers *eventHandlers,
                  AdminData *changedAdminData);

protected:
  virtual void NotifyChangedData() override;
  virtual EnumScreenType GetNextScreenWhenYesSelected() const;

private:
  AdminData *m_AdminData;
};
} // namespace Incubator

#endif // INCUBATOR_AdministratorResetQuestionScreen_H
