#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

//////////////////////////////////////////////////////
// define's the button's pins
#define BUTTON_TOPLEFT D6
#define BUTTON_TOPRIGHT D4
#define BUTTON_BOTTOMLEFT D5
#define BUTTON_BOTTOMRIGHT D3
#define BUTTON_SNOOZE D2


#define LAST_PRESSED_LENGTH 10


#define CLEAR       100
#define TOPLEFT     101
#define TOPRIGHT    102
#define BOTTOMLEFT  103
#define BOTTOMRIGHT 104
#define TOP         105
#define BOTTOM      106
#define X           107

//////////////////////////////////////////////////////
// Section used exclusively by Simon
#define DODISPLAY 1
#define DOBUTTONS 2
#define DOCHECKS 3
#define PASSED 4
#define FAILED 5
#define R 5 // r for rounds

#define SIMONTOPLEFT 1
#define SIMONTOPRIGHT 2
#define SIMONBOTTOMLEFT 3
#define SIMONBOTTOMRIGHT 4

#define SIMONBUTTON_TOPLEFT 6
#define SIMONBUTTON_TOPRIGHT 4
#define SIMONBUTTON_BOTTOMLEFT 5
#define SIMONBUTTON_BOTTOMRIGHT 3
#define SIMONBUTTON_SNOOZE 2

//////////////////////////////////////////////////////
//  Section for Alarm state definitions
#define ALARM_NORMAL 0
#define ALARM_FLASH 1
#define ALARM_TRIGGER 2

#define ALARM_FLASH_COUNT 4
#define ALARM_TRIGGER_COUNT 60



#endif
