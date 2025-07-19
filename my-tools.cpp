#include "my-tools.h"
#include <stdio.h>

bool fileExists(const char* fileName){
    FILE* f = fopen(fileName, "r");
    if (f){
        fclose(f);
        return true;
    }
    return false;
}
