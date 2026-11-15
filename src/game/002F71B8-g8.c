#include "include_asm.h"
#include "names.h"

/* Rebuilds the list of the slots after the current one that are unlocked (the bit in
   the save byte, or the fallback check), each with its id and table value. */

typedef struct {
    int value[5];
} Func002F71B8Table;

typedef struct {
    int id;
    int value;
    int slot;
} Func002F71B8Entry;

typedef struct {
    char pad[0x140];
    Func002F71B8Entry entry[0x80];
    int count;
} Func002F71B8List;

extern int D_001AD1C0 __attribute__((sda));
extern int D_001AD1B8 __attribute__((sda));
extern Func002F71B8Table D_001AD268;
extern unsigned char D_001395B8[];
extern Func002F71B8List D_0021F240;
extern int func_00288D58(void);

void func_002F71B8(void)
{
    Func002F71B8Table values = D_001AD268;
    int i;

    gVendorMenuState.count = 0;
    D_001AD1B8 = 0;
    for (i = D_001AD1C0 != 0 ? D_001AD1C0 + 1 : 1; i < 5; i++) {
        if ((unsigned int)i >= 8 ||
            ((D_001395B8[0x8D] >> i) & 1) == 0) {
            if (IsFlagByteSet() == 0)
                continue;
        }
        gVendorMenuState.entry[gVendorMenuState.count].slot = i;
        gVendorMenuState.entry[gVendorMenuState.count].value = values.value[i];
        gVendorMenuState.entry[gVendorMenuState.count].id = i + 0xEA92;
        gVendorMenuState.count = gVendorMenuState.count + 1;
    }
}
