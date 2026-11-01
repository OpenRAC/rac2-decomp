#include "include_asm.h"

typedef unsigned char u8;
typedef struct {
    char pad0[0x1B8];
    int frame;
    char pad1bc[0x1220 - 0x1BC];
    int state;
    char pad1224[0x1248 - 0x1224];
    int index;
    char pad124c[0x2290 - 0x124C];
    void *owner;
    int mode;
} FlashResidentFields;
extern FlashResidentFields D_00189E20_2;
extern unsigned char D_00139568[];
extern char D_L00_00262570[];
extern void func_002A04B8(void *owner, int *a1, int *a2, int *a3);
extern void func_002A0488(void *owner, int a1, int a2, int a3);
extern void func_L00_002A7070(void);
extern void func_L00_002A70F0(int first, void *second);

void func_PAL_L00_002A7390(void)
{
    int r, g, b;
    int active = 0;
    if (D_00189E20_2.mode == 125 || D_00189E20_2.mode == 127)
        active = D_00189E20_2.frame < 25;
    if (active) {
        func_002A04B8(D_00189E20_2.owner, &r, &g, &b);

        if (D_00189E20_2.frame % 4 < 3) {
            r = 0;
            g = 0;
            b = 0;
        } else {
            r = 0x90;
            g = 0x90;
            b = 0xF0;
        }

        func_002A0488(D_00189E20_2.owner, r, g, b);
        func_L00_002A7070();
    }

    if (D_00189E20_2.index >= 0) {
        unsigned char index = D_00139568[D_00189E20_2.index];
        char *record = D_L00_00262570 + index * 0xE0;

        if (*(u8 *)(record + 4) != 0) {
            int state = D_00189E20_2.state;

            if (state != 0)
                func_L00_002A70F0(state, D_00189E20_2.owner);
        }
    }
}
