#ifndef _CP_AUDIO_H_
#define _CP_AUDIO_H_


#include <AsyncTimer.h>

#define CP_BEEP_GPIO 25

class CPAudio {
public:
  CPAudio();
  void init();
  void beep();
private:
  AsyncTimer t;
};
#endif