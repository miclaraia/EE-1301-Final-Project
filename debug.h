#ifndef DEBUG_H_
#define DEBUG_H_
#include "application.h"
#include <sstream>
#include <string>
#include "definitions.h"
#include "objects.h"

void debugButton(int pin);
void debug(std::stringstream *ss);
void debugArray(int *list, int length);

#endif