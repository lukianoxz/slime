#ifndef SLMLAND_H
#define SLMLAND_H

#include "../shared/slm.h"
#include "slmland_window.h"

inline void slmland_yield() {
    __asm__ volatile ("int $0x81" :::);
}

inline void slmland_quit() {
    __asm__ volatile ("int $0x82" :::);
}

#endif