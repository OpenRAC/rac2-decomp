/* func_US2_L15_004329F0, the USA v2.00 copy of func_L15_00430C80: the same C, where the
 * first-time setup also releases the two path markers still held from an earlier state. */
#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0xAA];
    s16 uid;
} Moby430C80;

extern s32 D_L15_001B1534 __attribute__((sda));
extern s32 D_L15_00221E10[];
extern u8 *D_L15_001B2714[] __attribute__((sda));
extern s32 D_L15_001B2148[] __attribute__((sda));

extern void func_002B7320(void);
extern s32 func_L00_004272A0(void);
extern Moby430C80 **func_L05_00379EB8(void);
extern int func_L05_00379ED0(int arg);
extern void func_L05_00379F18(int);
extern void func_L05_0037B210(void);
extern void func_L05_0037B280(void *object, int handler);
extern void *func_L05_0037B440(int, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern int func_L15_00381CF0(int);
extern void func_US2_L15_00432238(void *, int);
extern void func_L15_00435E80(void *);
extern void func_L15_00436090(void *);
extern void func_0029F338(void *);

typedef struct {
    u8 pad00[0x34];
    u16 flags;
} Marker;

extern Marker *D_L15_001B1584 __attribute__((sda));
extern Marker *D_L15_001B1588 __attribute__((sda));

void func_US2_L15_004329F0(void *self) {
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
                func_L05_0037B280(list[i], 1);
                func_L05_0037CEE0(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
                func_L05_0037D608(list[i], D_L15_001B2714[0] + D_L15_00221E10[0] * 128 + 0x30, 64.0f);
            }
        }
        obj = func_L05_0037B440(0x1211, 1);
        if (obj != 0) {
            func_L15_00435E80(obj);
            func_L15_00436090(obj);
        }
        if (D_L15_001B1584 != 0 && D_L15_001B1584->flags != 0) {
            func_0029F338(D_L15_001B1584);
            D_L15_001B1584 = 0;
        }
        if (D_L15_001B1588 != 0 && D_L15_001B1588->flags != 0) {
            func_0029F338(D_L15_001B1588);
            D_L15_001B1588 = 0;
        }
    }
    if (func_L15_00381CF0(func_L05_00379ED0(0x1211)) == 0 && D_L15_001B2148[0] >= 6) {
        func_US2_L15_00432238(self, 2);
    }
}
