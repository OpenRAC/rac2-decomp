#include "include_asm.h"

/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
unsigned int func_L00_0032C638(unsigned int param_1)
{
    unsigned int inner_ptr;
    unsigned int result;

    inner_ptr = *(unsigned int *)(param_1 + 0x68);
    result = *(unsigned int *)(inner_ptr + 0x18);
    return result;
}




INCLUDE_ASM("asm/levels", func_L00_0032CF60);

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
        ResidentState *rs = &D_00188660;
        unsigned int *handle = &rs->handles[i + 1];
        if (*handle != 0) {
            func_00132858(*handle);
            *handle = 0;
        }
    }
    func_00133230();
    while (func_00132028() != 0) { }
    func_00132828();
    while (func_00132028() != 0) { }
    address = D_0014B540.entries[index][0];
    if (address != 0) {
        address += D_0014B540.base;
        D_00188660.handles[index + 1] = -1;
        D_00188660.handles[index + 1] = func_00132318(address, 0);
    }
    func_00132828();
}

