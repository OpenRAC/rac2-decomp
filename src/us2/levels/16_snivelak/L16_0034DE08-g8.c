#include "include_asm.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry12;
extern int D_00139948[];
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry12;
extern SourceEntry12 D_L00_0028B620[];
extern char D_L00_002870C0[];
extern InitEntry12 D_L00_0021CEF0[];
extern int * volatile D_L00_001AA830 __attribute__((sda));
extern struct { char pad[0x230]; int selected; } D_L00_001C93A0;

int func_US2_L16_0034DE08(char *obj) {
    int i, entry;
    int *list;
    for (i = 0; i < 28 && D_00139948[i]; i++) {
        D_L00_0021CEF0[i].kind = 3;
        D_L00_0021CEF0[i].callback = D_L00_002870C0;
        D_L00_0021CEF0[i].id = D_L00_0028B620[D_00139948[i]].id;
        D_L00_0021CEF0[i].value = D_L00_0028B620[D_00139948[i]].value;
    }
    list = D_L00_001AA830;
    D_L00_0021CEF0[i].id = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned int *)(obj + 0x30) |= 0x8000;
    for (i = 0, entry = list[0]; entry; entry = D_L00_001AA830[++i]) {
        if (D_L00_001C93A0.selected == entry) {
            *(int *)(obj + 0x40) = i;
            break;
        }
    }
    return 0;
}
