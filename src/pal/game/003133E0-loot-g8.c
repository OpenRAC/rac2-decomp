#include "include_asm.h"

#include "common.h"
extern int func_002A77E0(int);
extern int D_001AF0FC __attribute__((sda));
extern void func_PAL_002A7650(void *, int, int);
extern int func_002A68A8(void *, int *);
extern void func_PAL_00321958(void *, int, int, int);

/* Selects the object's drop kind, emits the requested count, and resets its
 * halfword at +0xB4 before handing it to the state helper. */
void func_PAL_003133E0(unsigned char *self)
{
    unsigned char *data = *(unsigned char **)(self + 0x68);
    int item = *(short *)(data + 0xC6) == 0;
    int n, i;

    if (*(short *)(self + 0xAA) == 0x1F5 || *(short *)(self + 0xAA) == 0x200)
        item = 0;
    if (item) {
        if (D_001AF0FC >= 21)
            i = 0;
        else if (D_001AF0FC >= 11)
            i = 1;
        else
            i = 2;
        func_PAL_002A7650(self, 256, func_002A77E0(2) + i);
    } else {
        if (*(short *)(self + 0xAA) != 0x1F5 && *(short *)(self + 0xAA) != 0x200) {
            {
                int kind = data[0xCB];
                if (kind == 4)
                    goto kind4;
                if (kind < 5)
                    goto none;
                if (kind == 8)
                    goto kind8;
                if (kind == 9)
                    goto kind9;
                goto none;
            kind8:
                item = 14;
                goto selected;
            kind4:
                item = 15;
                goto selected;
            kind9:
                item = 17;
                goto selected;
            none:
                item = -1;
            selected:
                ;
            }
            n = func_002A68A8(self, &item);
            if (n > 0) {
                i = n;
                do {
                    func_PAL_00321958(self + 0x10, item, -1, 0);
                    --i;
                } while (i);
            }
        }
        if (*(short *)(self + 0xB4))
            *(short *)(self + 0xB4) = 0;
        func_PAL_002A7650(self, 256, 0);
    }
}
