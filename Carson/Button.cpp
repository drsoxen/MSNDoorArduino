#include "Button.h"

Button::Button(int btnPin, std::function<void(void)> fn)
{
	m_btnPin = btnPin;
	m_callback = fn;
}

bool Button::CheckPressed()
{
	if(/*pressed*/true)
	{
		m_callback();
		return true;
	}
	return false;
}