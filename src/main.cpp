#include <iostream>
#include "../include/cpu.h"
#include "../include/cart.h"


using namespace std;

int main(int argc, char* argv[]) {
    const char* cart_path = "roms\\tetris.gb";
    if (cart_load(cart_path))
        cart_print_info();
    cpu_init();
    cpu_fetch();
    return 0;
}