#include <cstdio>
#include "extension/chess/goBangChess.h"

void paint(GoBangChess *a) { // should be done by interactor
    GoBangChess::Board b;
    a->copyBoard(&b);

    const char hint[16] = "123456789ABCDEF"; // auto fill \0
    printf(" %s\n", hint);
    for (int i = 0; i < 15; ++ i) {
        printf("%c", hint[i]);
        for (int j = 0; j < 15; ++ j){
            if (b[i][j] == b.NONE) printf(" ");
            if (b[i][j] == 0) printf(".");
            if (b[i][j] == 1) printf("*");
        }
        printf("\n");
    }
};

int main() {
    GoBangChess c;
    c.clear();
    while (c.winner() == -1) {
        paint(&c);
        printf("CurrentPlayer: %d\n", c.currentPlayer());
        char m[5]; // be careful of memory leak
        do {
            printf("Input Move: ");
            scanf("%s", m);
        } while (!c.move(GoBangChess::Move(m)));
    }
    printf("Winner: %d\n", c.winner());
    return 0;
}