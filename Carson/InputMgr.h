#ifndef INPUT_MGR
#define INPUT_MGR

#include <ESP8266WiFi.h>
#include <vector>
#include "Button.h"

class InputMgr
{
public:
	InputMgr();   
 	bool CheckAllButtons();
 	bool CheckButton(Button *button);

 	void AddButton(Button *button);

 	std::vector<Button*> m_buttons;
};

#endif
