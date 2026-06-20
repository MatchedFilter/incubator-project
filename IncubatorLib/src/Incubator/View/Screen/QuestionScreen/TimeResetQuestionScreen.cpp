#include "Incubator/View/Screen/QuestionScreen/TimeResetQuestionScreen.h"

#include "bsp_config.h"

namespace Incubator
{

TimeResetQuestionScreen::TimeResetQuestionScreen()
    : AQuestionScreen{SCREEN_TYPE_QUESTION_TIME_RESET}, m_ChangedTimeInformationData{nullptr}
{
}

TimeResetQuestionScreen::~TimeResetQuestionScreen()
{
}

void TimeResetQuestionScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("G");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_U);
  m_Lcd->Print("ncel zaman");
  m_Lcd->MoveCursor(1U, 0U);
  m_Lcd->Print("s");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("f");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("rlans");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("n m");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_I);
  m_Lcd->Print("?");
  AQuestionScreen::OnInitial();
}

void TimeResetQuestionScreen::Initialize(Lcd2004 *tc2004Lcd,
                                         DataChangedEventHandlers *eventHandlers,
                                         TimeInformationData *changedTimeInformationData)
{
  AQuestionScreen::Initialize(tc2004Lcd, eventHandlers);
  m_ChangedTimeInformationData = changedTimeInformationData;

  bsp_assert(nullptr != m_ChangedTimeInformationData);
}

void TimeResetQuestionScreen::NotifyChangedData()
{
  m_DataChangedEventHandlers->m_TimeInformationDataChangedEventHandler->OnUpdate(
    *m_ChangedTimeInformationData);
}

} // namespace Incubator
