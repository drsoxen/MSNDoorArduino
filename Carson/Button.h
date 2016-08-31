#ifndef BUTTON
#define BUTTON

#include <ESP8266WiFi.h>

class Button
{
public:
	Button(int btnPin, std::function<void(void)> fn);
	bool CheckPressed();

private:
	std::function<void(void)> m_callback;
 	int m_btnPin;
};

#endif
