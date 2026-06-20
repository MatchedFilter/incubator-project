#ifndef INCUBATOR_ASCREEN_H
#define INCUBATOR_ASCREEN_H
#include "EnumScreenType.h"
#include "Incubator/View/JoystickEvent.h"
namespace Incubator
{
class AScreen
{
public:
  inline AScreen(const EnumScreenType screenType)
      : m_ScreenType{screenType}, m_NextScreen{screenType}
  {
  }
  inline virtual ~AScreen()
  {
  }
  inline EnumScreenType GetScreenType() const
  {
    return m_ScreenType;
  }
  virtual void OnInitial()                              = 0;
  virtual void OnUserAction(const JoystickEvent &event) = 0;
  virtual EnumScreenType GetNextScreen()
  {
    return m_NextScreen;
  };
  inline EnumScreenType GetPreviousScreen() const
  {
    return m_PreviousScreen;
  }
  inline void SetPreviousScreen(const EnumScreenType previousScreen)
  {
    m_PreviousScreen = previousScreen;
  }
  inline virtual void Reset()
  {
    m_NextScreen = m_ScreenType;
  }
  virtual void Run() = 0;

protected:
  inline void SetNextScreen(const EnumScreenType nextScreen)
  {
    m_NextScreen = nextScreen;
  }

private:
  const EnumScreenType m_ScreenType;
  EnumScreenType m_NextScreen;
  EnumScreenType m_PreviousScreen;
};
} // namespace Incubator

#endif // INCUBATOR_ASCREEN_H
