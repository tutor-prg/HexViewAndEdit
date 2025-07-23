#include "my-tools.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

#define _WIN32

#ifdef _WIN32
    #include <windows.h>
#endif

void parseParameters(int nParams, char** params);

using namespace std;

char fileName[500];
unsigned int loAddr, hiAddr;

int main(int nParams, char** params)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
   // system("chcp 65001 >> nul");
#endif

    parseParameters(nParams, params);

//  Контрольна точка - перевірка як і які параметри ми проситали
    cout << fileName << endl;
    cout <<hex<< loAddr << endl;
    cout <<hex<< hiAddr << endl;


    return 0;
}

void parseParameters(int nParams, char** params){
    // Єдиний нульовий параметр - назва самої програми (зі шляхом)
    if (nParams == 1){
        cout << "***********" << endl;
        cout << "* Довідка *" << endl;
        cout << "***********" << endl;
        cout << "Без параметрів - читати цю довідку" << endl;
        cout << "Перший параметр - назва файла, який ми хочемо попазати/редагувати" << endl;
        cout << "Другий параметр - адреса всередині файла, звідки почати (hex-число: наприклад: 0xA25FFBD8)" << endl;
        cout << "                  Якщо не вказано, то - з початку файла" << endl;
        cout << "Тратій параметр - адреса всередині файла, де закінчити  (hex-число: наприклад: 0xA25FFBD8)" << endl;
        cout << "                  Якщо не вказано, то - до кінця файла" << endl;

        exit(1);
    }

    // Нульовий параметр - назва самої програми (зі шляхом)
    // Пеший параметр - назва файла, який ми хочемо попазати/редагувати
    if (nParams >= 2){
        strcpy(fileName, params[1]);
        if (!fileExists(fileName)){
            cout << " File not exists: " << fileName << endl;
            exit(2);
        }
    }

    if (nParams >= 3){
        if (!isStrShowsHex(params[2])){
            printf("Не вдалося зчитати/зрозуміти hex-значення для нижньої адреси: %s\n", params[2]);
            exit(3);
        }
        sscanf(params[2], "%x", &loAddr);
    }

    if (nParams >= 4){
        if (!isStrShowsHex(params[3])){
            printf("Не вдалося зчитати/зрозуміти hex-значення для нижньої адреси: %s\n", params[3]);
            exit(4);
        }
        sscanf(params[3], "%x", &hiAddr);
    }
}




