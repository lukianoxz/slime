#include "slmsys.h"
#include <libc.h>

static uint8_t slime_logo[8 * 8] = {
     0,  0, 10, 10,  0,  0,  0,  0,
     0, 10,  0, 10, 10,  0,  0,  0,
     0,  0,  0, 10, 10,  2,  0,  0,
     0,  0, 10, 10, 10,  2,  2,  0,
     0, 10, 10,  2,  2,  2,  2,  0,
    10, 10,  2,  2,  2,  2,  2,  2,
    10, 10,  2,  2,  2,  2,  2,  2,
     0, 10, 10,  2,  2,  2,  0,  0
};

static uint8_t correct_logo[8 * 8] = {
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 0, 2, 0,
    2, 0, 0, 0, 0, 2, 0, 0,
    0, 2, 0, 0, 2, 0, 0, 0,
    0, 0, 2, 0, 2, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
};

struct slmsys_process_data {
    uint16_t sp;
    uint16_t segment;
    uint8_t status;
};

#define slmsys_max_processes 4
struct slmsys_process_data slmsys_processes[slmsys_max_processes];
uint16_t *slmsys_current_process_sp;
uint8_t current_pid;

void slmsys_schelduler();
void slmsys_app_setup(uint8_t pid, uint16_t segment);
void slmsys_poke_world(uint16_t segment, uint16_t offset, uint16_t value);

void slm_kernel_entry() {
    slmsys_current_process_sp = &slmsys_processes[0].sp;
    current_pid = 0;
    uint8_t dest = 0;
    uint8_t src = 2;

    slmsys_init_video();
    slmsys_draw_image(6, 6, 8, 8, slime_logo, 0, true);

    memcpy(&dest, &src, 1);

    if (dest == src) {
        slmsys_draw_image(20, 20, 8, 8, correct_logo, 0, true);
    }
}

void slmsys_schelduler() {
    for (int i = 0; i < slmsys_max_processes; i++) {
        current_pid = (current_pid + 1) % slmsys_max_processes;
        
        if (slmsys_processes[current_pid].status == (uint8_t)1) {
            slmsys_current_process_sp = &slmsys_processes[current_pid].sp;
            return;
        }
    }
}

void slmsys_app_setup(uint8_t pid, uint16_t segment) {
    uint16_t stack = (uint16_t)0xFFFF;

    slmsys_poke_world(segment, stack -= 2, (uint16_t)0x0202); // interruption flag on
    slmsys_poke_world(segment, stack -= 2, segment);
    slmsys_poke_world(segment, stack -= 2, (uint16_t)0x0000); // entry point (main)

    for (int i = 0; i < 9; i++) {
        slmsys_poke_world(segment, stack -= 2, (uint16_t)0);
    }

    slmsys_processes[pid].sp = (uint16_t)stack;
    slmsys_processes[pid].segment = segment;
    slmsys_processes[pid].status = 1;
}

void slmsys_poke_world(uint16_t segment, uint16_t offset, uint16_t value) {
    __asm__ volatile (
        "movw %0, %%es\n\t" // mov segment to es
        "movw %2, %%es:(%1)" // mov value to offset
        :
        : "r"(segment), "b"(offset), "r"(value)
        : "memory"
    );
}