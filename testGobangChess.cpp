#include <cstdio>
#include "goBangChess.h"

void paint(GoBangChess a) { // should be done by interactor
    GoBangChess::Board b;
    a.copyBoardTo(&b);

    const char hint[16] = "123456789ABCDEF"; // auto fill \0
    printf("  %s\n\n", hint);
    for (int i = 0; i < 16; ++ i) {
        printf("%c ", hint[i]);
        for (int j = 0; j < 16; ++ j){
            if (b[i][j] == b.NONE) printf(" ");
            if (b[i][j] == 0) printf(".");
            if (b[i][j] == 1) printf("*");
        }
        printf("\n");
    }
};

int main() {
    GoBangChess c;
    while (1) {
        paint(c);

    }
}