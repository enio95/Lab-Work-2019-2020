#ifndef ERROR
#define ERROR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"

void errorMessageMem(char *str);
void errorMessageOut(char *str);
void errorMessageMap(char *str);
void errorMessagePointer(char *str);
void errorMessageIllegalSize(char *str);

#endif
