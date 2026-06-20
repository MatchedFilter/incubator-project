#include "Incubator/View/Screen/QuestionScreen/AQuestionScreen.h"

#include "bsp_config.h"

namespace Incubator
{

AQuestionScreen::AQuestionScreen(const EnumScreenType screenType)
    : AScreen{screenType}, m_Lcd{nullptr}, m_QuestionSelection{QUESTION_SELECTION_NO},
      m_DataChangedEventHandlers{nullptr}
{
}

AQuestionScreen::~AQuestionScreen()
{
}

void AQuestionScreen::Initialize(Lcd2004 *tc2004Lcd, DataChangedEventHandlers *eventHandlers)
{
  m_Lcd                      = tc2004Lcd;
  m_DataChangedEventHandlers = eventHandlers;

  bsp_assert(nullptr != m_DataChangedEventHandlers);
}

void AQuestionScreen::OnInitial()
{
  Reset();
  m_Lcd->MoveCursor(3U, 0U);
  if (QUESTION_SELECTION_NO == m_QuestionSelection)
  {
    m_Lcd->Print(" Evet        [Hay");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("r]");
  }
  else if (QUESTION_SELECTION_YES == m_QuestionSelection)
  {
    m_Lcd->Print("[Evet]        Hay");
    m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
    m_Lcd->Print("r ");
  }
  else
  {
    // intentionally left blank
  }
}

void AQuestionScreen::Reset()
{
  AScreen::Reset();
  m_QuestionSelection = QUESTION_SELECTION_NO;
}

void AQuestionScreen::Run()
{
  // intentionally left blank
}

void AQuestionScreen::OnUserAction(const JoystickEvent &event)
{
  if (event.bIsButtonPressed)
  {
    if (QUESTION_SELECTION_YES == m_QuestionSelection)
    {
      SetNextScreen(GetNextScreenWhenYesSelected());
      NotifyChangedData();
    }
    else
    {
      SetNextScreen(GetPreviousScreen());
    }
  }
  else
  {
    if (QUESTION_SELECTION_NO == m_QuestionSelection)
    {
      if (event.bIsLeftPressed)
      {
        m_QuestionSelection = QUESTION_SELECTION_YES;
        m_Lcd->MoveCursor(3U, 0U);
        m_Lcd->Print("[");
        m_Lcd->MoveCursor(3U, 5U);
        m_Lcd->Print("]");
        m_Lcd->MoveCursor(3U, 13U);
        m_Lcd->Print(" ");
        m_Lcd->MoveCursor(3U, 19U);
        m_Lcd->Print(" ");
      }
    }
    else
    {
      if (event.bIsRightPressed)
      {
        m_QuestionSelection = QUESTION_SELECTION_NO;
        m_Lcd->MoveCursor(3U, 0U);
        m_Lcd->Print(" ");
        m_Lcd->MoveCursor(3U, 5U);
        m_Lcd->Print(" ");
        m_Lcd->MoveCursor(3U, 13U);
        m_Lcd->Print("[");
        m_Lcd->MoveCursor(3U, 19U);
        m_Lcd->Print("]");
      }
    }
  }
}

EnumScreenType AQuestionScreen::GetNextScreenWhenYesSelected() const
{
  return SCREEN_TYPE_MAIN;
}

} // namespace Incubator
