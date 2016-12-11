#include "debug.h"

void debugButton(int pin) {
    std::string s;
    switch(pin) {
        case D3:
        s = "D3";
        break;
        case D4:
        s = "D4";
        break;
        case D5:
        s = "D5";
        break;
        case D6:
        s = "D6";
        break;
        case D7:
        s = "D7";
        break;
    }

    std::stringstream ss;
    ss << s << " button pressed";
    s = ss.str();
    Serial.print(s.c_str());
    Serial.print("\n");
}

void debug(std::stringstream *ss) {
    (*ss) << "\n\r";
    std::string s;
    s = ss->str();
    Serial.print(s.c_str());
}
