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
extern int g_copy_setup_data[];
extern void snd_start_bank_read(void *, int, void (*)(int, long), unsigned long);
extern char g_sound_state[];
extern void load_store_callback_result(int, long);

/* Load a table entry and write its completion result to the next bank status slot. */
void snd_load_bank_entry(int index)
{
    int *d = g_copy_setup_data;
    int offset = ((BankLoadTable *)d)->entries[index].offset;
    BankStatuses *b;

    if (offset) {
        unsigned int out;

        b = (BankStatuses *)g_sound_state;
        b->status[index + 1] = -1;
        out = (unsigned int)((unsigned long)(unsigned int)((BankCallbackStatuses *)b)->status
                             + index * 4);
        snd_start_bank_read((void *)(offset + d[0x14a7]), 0, load_store_callback_result,
                      (unsigned long)(unsigned int)out);
    } else {
        ((BankStatuses *)g_sound_state)->status[index + 1] = 0;
    }
}
