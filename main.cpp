#include <iostream>
#include "Board.h"
int main() {
    Board b;
    b.setStartPosition();
    std::cout << b.printBoard();
    return 0;
}
