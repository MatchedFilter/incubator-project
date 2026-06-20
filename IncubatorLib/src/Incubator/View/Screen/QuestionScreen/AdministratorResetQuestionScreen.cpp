#include "Incubator/View/Screen/QuestionScreen/AdministratorResetQuestionScreen.h"

#include "bsp_config.h"

namespace Incubator
{

AdministratorResetQuestionScreen::AdministratorResetQuestionScreen()
    : AQuestionScreen{SCREEN_TYPE_QUESTION_ADMIN_RESET}, m_AdminData{nullptr}
{
}

AdministratorResetQuestionScreen::~AdministratorResetQuestionScreen()
{
}

void AdministratorResetQuestionScreen::OnInitial()
{
  Reset();
  m_Lcd->Clear();
  m_Lcd->MoveCursor(0U, 0U);
  m_Lcd->Print("Y");
  m_Lcd->Print(BSP_LCD_2004_CHAR_LOWER_O);
  m_Lcd->Print("netici ayarlar");
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

void AdministratorResetQuestionScreen::Initialize(Lcd2004 *tc2004Lcd,
                                                  DataChangedEventHandlers *eventHandlers,
                                                  AdminData *changedAdminData)
{
  AQuestionScreen::Initialize(tc2004Lcd, eventHandlers);
  m_AdminData = changedAdminData;

  bsp_assert(nullptr != m_AdminData);
}

void AdministratorResetQuestionScreen::NotifyChangedData()
{
  m_AdminData->Reset();
  m_DataChangedEventHandlers->m_AdminDataChangedEventHandler->OnUpdate(*m_AdminData);
}

EnumScreenType AdministratorResetQuestionScreen::GetNextScreenWhenYesSelected() const
{
  return SCREEN_TYPE_ADMINISTRATOR_SETTINGS;
}

} // namespace Incubator
