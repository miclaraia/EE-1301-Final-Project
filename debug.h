#ifndef DEBUG_H_
#define DEBUG_H_
#include "application.h"
#include "definitions.h"
#include "objects.h"
#include <string>

void debugButton(int pin);
void debug(std::string *str);
void debugArray(int *list, int length);

#endif