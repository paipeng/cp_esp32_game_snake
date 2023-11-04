#ifndef _CP_AUDIO_H_
#define _CP_AUDIO_H_


#define CP_BEEP_GPIO 34

class CPAudio {
public:
  CPAudio();
  void init();
  void beep();

};
#endif