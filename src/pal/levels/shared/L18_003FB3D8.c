#include "include_asm.h"

#include "common.h"

/* Tells if the object has run out of time or steps. */
int protopet_is_action_finished_pal(void *object) {
    int finished;
    void *state;

    finished = 0;
    state = *(void **)((unsigned char *)object + 0x68);
    if (((unsigned short) (*(unsigned short *)((unsigned char *)object + 0x96)) >= 0xC9U) || ((*(short *)((unsigned char *)state + 0x294)) >= (*(short *)((unsigned char *)state + 0x2A4)))) {
        finished = 1;
    }
    return finished;
}

