#include "my-tools.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <iomanip>

#define _WIN32 //Треба закоментувати цей рядок на Linux

#ifdef _WIN32
    #include <windows.h>
#endif

void parseParameters(int nParams, char** params);
void normalizeBoundaries();
void showDamp();

using namespace std;

char fileName[500];
unsigned int loAddr, hiAddr;  //Нижня межа ВКЛЮЧНО і верхня межа НЕ ВКЛЮЧНО

int main(int nParams, char** params)
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
   // system("chcp 65001 >> nul");
#endif

    parseParameters(nParams, params);
//  Контрольна точка - перевірка як і які параметри ми проситали
//    cout << fileName << endl;
//    cout <<hex<< loAddr << endl;
//    cout <<hex<< hiAddr << endl;


    //Нижню  адресу зменшуємо  до найближчої кратної 16
    //Верхню адресу збільшуємо до найближчої кратної 16
    normalizeBoundaries();
//  Контрольна точка - перевірка нормалізованих адрес
//    cout <<hex<< loAddr << endl;
//    cout <<hex<< hiAddr << endl;

    showDamp();

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

    //Нижня межа за умовчанням
    loAddr = 0;
    if (nParams >= 3){
        if (!isStrShowsHex(params[2])){
            printf("Не вдалося зчитати/зрозуміти hex-значення для нижньої адреси: %s\n", params[2]);
            exit(3);
        }
        sscanf(params[2], "%x", &loAddr);
    }

    //Верхня межа за умовчанням
    hiAddr = fileSize(fileName);
    if (nParams >= 4){
        if (!isStrShowsHex(params[3])){
            printf("Не вдалося зчитати/зрозуміти hex-значення для нижньої адреси: %s\n", params[3]);
            exit(4);
        }
        sscanf(params[3], "%x", &hiAddr);
    }
}


void normalizeBoundaries(){
    //Нижню  адресу зменшуємо  до найближчої кратної 16
    //Верхню адресу збільшуємо до найближчої кратної 16
    while (loAddr % 16 != 0) loAddr--;
    while (hiAddr % 16 != 0) hiAddr++;
}


void showDamp(){
    int buf_size = hiAddr - loAddr;
    char* buf = new char[buf_size];

    FILE* f = fopen(fileName, "rb");
    fseek(f, loAddr, SEEK_SET);
    int bytes_read = fread(buf, sizeof(char), buf_size, f);
    fclose(f);

    clearScreen();

    int addr1 = 0;
    int addr2 = addr1;
    while (addr1 < buf_size){
        cout << hex << setw(8) << setfill('0') << addr1 << "  ";
        for (int i=0; i<16; i++){
            if (addr1 < bytes_read){
                    // (int)buf[addr]      int(buf[addr])      static_cast<int>(buf[addr])
                //cout << " " << hex << uppercase << setw(2) << setfill('0') << (int)buf[addr1];
                printf("%02X ", buf[addr1]);
            }
            else {
                cout << "   ";
            }
            if (i==7) cout << " | ";
            addr1++;
        }

        cout << "  ";
        // Вивід ASCII
        for (size_t i = 0; i < 16; i++) {
            if (addr2 < bytes_read){
                unsigned char c = buf[addr2];
                printf("%c", isprint(c) ? c : '.');
            }
            else {
                cout << " ";
            }
            addr2++;
        }

        cout << endl;
    }

    delete [] buf;
}

