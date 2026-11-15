#include "include_asm.h"
#include "names.h"

/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
/* Reads a value from the object's private data. */
void *moby_get_vars_word_18(unsigned int object)
{
    unsigned int vars;
    unsigned int result;

    vars = *(unsigned int *)(object + 0x68);
    result = *(unsigned int *)(vars + 0x18);
    return result;
}




/* func_L00_0032CF60 is in L00_0032CF60-g8.c (-G8 -g). */

/* Writes a value to the given memory address if it is not null. */
void mem_store_word_at_address(int value, long address) {
    int *target = (int *)(int)address;
    if (target != 0)
        *target = value;
}

typedef struct { char pad[0x17a0]; unsigned int handles[4]; } ResidentState;
extern ResidentState g_sound_state;
typedef struct { char pad[0x529c]; int base; char gap[0x40]; int entries[3][2]; } AddressBank;
extern AddressBank g_copy_setup_data;
extern void snd_send_cmd6(int handle);
extern void snd_clear_flag_and_update(void);
extern int snd_Pump(void);
extern void func_00132828(void);
extern int snd_BankLoadByLoc(int address, int mode);
void ReloadSoundBank(int index)
{
    int i;
    int address;
    for (i = 0; i < 3; i++) {
        ResidentState *rs = &g_sound_state;
        unsigned int *handle = &rs->handles[i + 1];
        if (*handle != 0) {
            snd_send_cmd6(*handle);
            *handle = 0;
        }
    }
    snd_clear_flag_and_update();
    while (snd_Pump() != 0) { }
    func_00132828();
    while (snd_Pump() != 0) { }
    address = g_copy_setup_data.entries[index][0];
    if (address != 0) {
        address += g_copy_setup_data.base;
        g_sound_state.handles[index + 1] = -1;
        g_sound_state.handles[index + 1] = snd_BankLoadByLoc(address, 0);
    }
    func_00132828();
}

