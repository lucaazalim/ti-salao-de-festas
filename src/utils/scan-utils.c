#include <stdio.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removeNewLine(char *string) {
    string[strcspn(string, "\n")] = 0;
}

void scanText(char *destination, int destinationLength) {
    fgets(destination, destinationLength, stdin);
    removeNewLine(destination);
}

int getch() {
    clearInputBuffer();
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}