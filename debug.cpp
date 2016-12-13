#include "application.h"
#include "module.h"
#include <string>

using std::string;

void addPin(int pin, string *str);

void debug(string *str) {
    (*str) += "\n\r";
    Serial.print(str->c_str());
}

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

    s = s + " button pressed";
    debug(&s);
}

void debugArray(int *list, int length) {
    string str;
    char buffer[10];
    itoa(length, buffer, 10);
    string l(buffer);

    str = "Count: " + l + " List of presses: ";
    for (int i = 0; i < length; i++) {
        addPin(*list, &str);
        str += ", ";

        list++;
    }

    debug(&str);
}

void addPin(int pin, string *str) {
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

    (*str) += s;
}