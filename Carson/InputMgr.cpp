#include "InputMgr.h"

InputMgr::InputMgr()
{
}

bool InputMgr::CheckAllButtons()
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if(m_buttons[i]->CheckPressed())
			return true;
	}
 return false;
}

bool InputMgr::CheckButton(Button *button)
{
	if(button->CheckPressed())
		return true;
  return false;	
}

void InputMgr::AddButton(Button *button)
{
	m_buttons.push_back(button);
}
