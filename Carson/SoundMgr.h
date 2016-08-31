#ifndef SOUND_MGR
#define SOUND_MGR

#include <ESP8266WiFi.h>

enum Sounds {GOOD = 0, BAD, READ};

class SoundMgr
{
public:
	SoundMgr();
	void playSound(Sounds sound, char* snd = NULL);
 
};

#endif
