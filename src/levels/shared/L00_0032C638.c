#include "include_asm.h"
#include "names.h"

/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
/* Reads a value from the object's private data. */
unsigned int func_L00_0032C638(unsigned int object)
{
    unsigned int vars;
    unsigned int result;

    vars = *(unsigned int *)(object + 0x68);
    result = *(unsigned int *)(vars + 0x18);
    return result;
}




/* func_L00_0032CF60 is in L00_0032CF60-g8.c (-G8 -g). */

/* Writes a value to the given memory address if it is not null. */
void func_L00_0032D100(int value, long address) {
    int *target = (int *)(int)address;
    if (target != 0)
        *target = value;
}

typedef struct { char pad[0x17a0]; unsigned int handles[4]; } ResidentState;
extern ResidentState D_00188660;
typedef struct { char pad[0x529c]; int base; char gap[0x40]; int entries[3][2]; } AddressBank;
extern AddressBank D_0014B540;
extern void func_00132858(int handle);
extern void func_00133230(void);
extern int func_00132028(void);
extern void func_00132828(void);
extern int func_00132318(int address, int mode);
void func_L00_0032D208(int index)
{
    int i;
    int address;
    for (i = 0; i < 3; i++) {
        ResidentState *rs = &gSoundState;
        unsigned int *handle = &rs->handles[i + 1];
        if (*handle != 0) {
            SendSoundCommand6(*handle);
            *handle = 0;
        }
    }
    ClearSoundFlagAndUpdate();
    while (snd_Pump() != 0) { }
    func_00132828();
    while (snd_Pump() != 0) { }
    address = gCopySetupData.entries[index][0];
    if (address != 0) {
        address += gCopySetupData.base;
        gSoundState.handles[index + 1] = -1;
        gSoundState.handles[index + 1] = snd_BankLoadByLoc(address, 0);
    }
    func_00132828();
}

