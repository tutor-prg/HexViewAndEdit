#include "my-tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool fileExists(const char* fileName){
    FILE* f = fopen(fileName, "r");
    if (f){
        fclose(f);
        return true;
    }
    return false;
}

bool isStrShowsHex(const char* s){
    int n = strlen(s);
    if (n > 10) return false;
    if (n < 2) return false;
    if (s[0] != '0') return false;
    if (s[1] != 'x' && s[2] != 'X') return false;
    for (int i=2; i<n; i++){
        char c = s[i];
        bool ok1 = '0' <= c && c <= '9';
        bool ok2 = 'a' <= c && c <= 'f';
        bool ok3 = 'A' <= c && c <= 'F';
        bool ok = ok1 || ok2 || ok3;
        if (!ok) return false;
    }
    return true;
}

void clearScreen(){
    #ifdef _WIN32
        system("CLS");
    #else
        system("clear");
    #endif
}

long fileSize(const char* fileName){
    FILE* f = fopen(fileName, "r");
    if (f){
        fseek(f, 0, SEEK_END);
        long pos = ftell(f);
        fclose(f);
        return pos;
    }
    return 0;
}






