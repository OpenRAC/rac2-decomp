#include "names.h"
extern char g_sound_state[];
extern int g_copy_setup_data[];
extern void load_store_callback_result(int, long);
extern void snd_start_bank_read(void *, int, void (*)(int, long), unsigned long);

/* Starts loading the first sound bank and stores the result in its status slot when done. */
void snd_load_first_bank(void) {
    char *statusBase = g_sound_state;
    int *soundTable = g_copy_setup_data;
    *(unsigned int *)(statusBase + 0x17A0) = 0xFFFFFFFFu;
    snd_start_bank_read((void *)(soundTable[0x14AC] + soundTable[0x14A7]), 0, load_store_callback_result,
                  (unsigned long)(unsigned int)(statusBase + 0x17A0));
}
