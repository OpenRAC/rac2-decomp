#include "common.h"

typedef struct {
    u32 value;
    u8 pad[0x14];
    u32 id;
} Entry_0028BCE8;

typedef struct {
    u8 pad[0x3C];
    u16 value;
    u8 pad3E[0xA2];
} Rec_0028BCE8;

extern u32 D_001B18D0;
extern u32 D_001B18D4;
extern u32 D_001A8DD0 __attribute__((sda));
extern u32 D_001A8D48 __attribute__((sda));
extern u32 D_001A73B8[] MACRO_ADDR;
extern u8 D_00139568[];
extern Rec_0028BCE8 D_00239BA0[];
extern Entry_0028BCE8 D_00255170[];

/* Initialises the eight displayed records from the class table and the stored ids. */
void func_0028BCE8(void)
{
    int i;
    u32 v;
    Rec_0028BCE8 *rec;

    D_001B18D0 = 8;
    D_001B18D4 = (u32)&D_001A8DD0;
    D_001A8D48 = 0;
    for (i = 0; i < 8; i++) {
        v = D_001A73B8[i];
        rec = &D_00239BA0[D_00139568[v]];
        D_00255170[i].id = v;
        D_00255170[i].value = rec->value;
    }
}
