#include <slmland.h>

void main() {
    slmland_yield(); // exit temporary for others process
    slmland_quit(); // end this process
}

char heap[2000]; // your process heap