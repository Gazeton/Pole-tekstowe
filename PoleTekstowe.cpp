#include <windows.h>
#include <conio.h>
#include <stdio.h>

void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    const int inputFieldWidth = 10;
    const int startX = 5;
    const int startY = 2;
    char input[inputFieldWidth + 1] = { 0 };
    int cursorPosition = 0;

    SetCursorPosition(startX, startY);
    SetColor(7); 

    while (1) {
        if (_kbhit()) {
            char key = _getch();
            if (key == -32) { 
                key = _getch(); 
                if (key == 75 && cursorPosition > 0) { 
                    cursorPosition--;
                }
                else if (key == 77 && cursorPosition < strlen(input)) { 
                    cursorPosition++;
                }
            }
            else if (key == '\r') {
                break; 
            }
            else if (key == '\b') { 
                if (cursorPosition > 0) {
                    memmove(&input[cursorPosition - 1], &input[cursorPosition], strlen(input) - cursorPosition + 1);
                    cursorPosition--;
                }
            }
            else if (isprint(key) && strlen(input) < inputFieldWidth) { 
                memmove(&input[cursorPosition + 1], &input[cursorPosition], strlen(input) - cursorPosition + 1);
                input[cursorPosition++] = key;
            }

            SetCursorPosition(startX, startY);
            printf("%-*s", inputFieldWidth, input);
            SetCursorPosition(startX + cursorPosition, startY); 
        }
    }

    return 0;
}
