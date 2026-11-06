/* func_PAL_L15_00436870, the PAL copy of func_L15_00430C80: the same C, which also deletes the two tracked mobys. */
#include "common.h"

typedef struct {
    u8 pad00[0xAA];
    s16 uid;
} Moby430C80;

extern s32 D_L15_001B1534 __attribute__((sda));
extern char *D_L15_001B1584 __attribute__((sda));
extern char *D_L15_001B1588 __attribute__((sda));
extern s32 D_L15_00221E10[];
extern u8 *D_L15_001B2714[] __attribute__((sda));
extern s32 D_L15_001B2148[] __attribute__((sda));

extern void func_0029F338(void *);
extern void func_002B7320(void);
extern s32 func_L00_004272A0(void);
extern Moby430C80 **func_L05_00379EB8(void);
extern int func_L05_00379ED0(int arg);
extern void func_L05_00379F18(int);
extern void func_L05_0037B210(void);
extern void func_PAL_L05_0037D9D0(void *object, int handler);
extern void *func_PAL_L05_0037DB90(int, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern int func_L15_00381CF0(int);
extern void func_PAL_L15_00436118(void *, int);
extern void func_PAL_L15_0043BB70(void *);
extern void func_PAL_L15_0043BD80(void *);

void func_PAL_L15_00436870(void *self) {
    Moby430C80 **list;
    void *obj;
    s32 n;
    s32 i;

    if (D_L15_001B1534 == 0) {
        D_L15_001B1534 = 1;
        D_L15_00221E10[0x2C / 4] = 0;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        list = func_L05_00379EB8();
        n = func_L00_004272A0();
        for (i = 0; i < n; i++) {
            if (list[i]->uid == 0x957) {
                func_PAL_L05_0037D9D0(list[i], 1);
                func_L05_0037CEE0(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
                func_L05_0037D608(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
            }
        }
        obj = func_PAL_L05_0037DB90(0x1211, 1);
        if (obj != 0) {
            func_PAL_L15_0043BB70(obj);
            func_PAL_L15_0043BD80(obj);
        }
        if (D_L15_001B1584 != 0) {
            func_0029F338(D_L15_001B1584);
            D_L15_001B1584 = 0;
        }
        if (D_L15_001B1588 != 0) {
            func_0029F338(D_L15_001B1588);
            D_L15_001B1588 = 0;
        }
    }
    if (func_L15_00381CF0(func_L05_00379ED0(0x1211)) == 0 && D_L15_001B2148[0] >= 6) {
        func_PAL_L15_00436118(self, 2);
    }
}
