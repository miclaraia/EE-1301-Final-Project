#include "application.h"
#include <sstream>
#include <string>
#include "objects.h"

using std::string;
using std::stringstream;

void addPin(int pin, stringstream *ss);

void debugButton(int pin) {
    string s;
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

    stringstream ss;
    ss << s << " button pressed";
    s = ss.str();
    Serial.print(s.c_str());
    Serial.print("\n");
}

void debug(stringstream *ss) {
    (*ss) << "\n\r";
    string s;
    s = ss->str();
    Serial.print(s.c_str());
}

void debugArray(int *list, int length) {
    stringstream ss;
    ss << "List of presses: ";
    for (int i = 0; i < length; i++) {
        addPin(*list, &ss);
        ss << ", ";

        list++;
    }

    debug(&ss);
}

void addPin(int pin, stringstream *ss) {
    string s;
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
        default:
        s = "unknown";
    }

    (*ss) << s;
}