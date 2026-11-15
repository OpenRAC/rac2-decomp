#include "names.h"
typedef struct { char pad[0x17a0]; unsigned int status[1]; } BankStatuses;
typedef struct { int offset, size; } SoundEntry;
typedef struct {
    char pad[0x529c];
    int base;
    char gap[0x40];
    SoundEntry entries[1];
} BankLoadTable;
typedef struct { char pad[0x17a4]; unsigned int status[1]; } BankCallbackStatuses;
extern int D_0014B540[];
extern void func_00132498(void *, int, void (*)(int, long), unsigned long);
extern char D_00188660[];
extern void func_002B6770(int, long);

/* Load a table entry and write its completion result to the next bank status slot. */
void func_002B6828(int index)
{
    int *d = gCopySetupData;
    int offset = ((BankLoadTable *)d)->entries[index].offset;
    BankStatuses *b;

    if (offset) {
        unsigned int out;

        b = (BankStatuses *)gSoundState;
        b->status[index + 1] = -1;
        out = (unsigned int)((unsigned long)(unsigned int)((BankCallbackStatuses *)b)->status
                             + index * 4);
        StartSoundBankRead((void *)(offset + d[0x14a7]), 0, StoreCallbackResult,
                      (unsigned long)(unsigned int)out);
    } else {
        ((BankStatuses *)gSoundState)->status[index + 1] = 0;
    }
}
