#include "include_asm.h"

#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;

extern u8 *D_L04_001FB1E0[];
extern u8 *D_L04_001B24DC __attribute__((sda));

extern void func_00282CF0(char *a0, char *a1, char *a2);
extern float func_00282DB0(char *a0, char *a1);
extern void func_L00_00323F70(void *input, int *out_x, int *out_y);
extern int func_L00_002EA668(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, f32 *a6);
extern s32 D_001A7340 __attribute__((sda));
extern s32 D_001A7344;
extern f32 D_L04_001B31EC __attribute__((sda));
extern char D_L04_001B9680[];

/* Projects the object into the screen, and while its position is inside the
   view asks the level's cursor helper to follow it. */

typedef int TI128 __attribute__((mode(TI)));

extern u16 **D_L04_001A9014;
extern u8 *D_L04_001B2B54;
extern u8 D_L04_001B17E0[8] __attribute__((sda));
extern u8 D_L04_001B17D8[8] __attribute__((sda));
extern u8 D_L04_001B17D0[8] __attribute__((sda));
extern s32 D_L04_001B1800 __attribute__((sda));

extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern void *func_002A9640(void *a0, s32 a1, s32 a2);
extern void func_L00_0032A530(void *a0, void *a1, void *a2, void *a3, s32 a4, s32 a5, s32 a6,
                              s32 a7, s32 a8, s32 a9, s32 a10);
extern void func_L00_00326110(void *a0, s32 a1, f32 f12);
extern void func_L00_00324F18(void *a0, void *a1, f32 f12, f32 f13, f32 f14);
/* Integer and float arguments take separate registers, so the interleaving below changes no
   register, only the order the caller loads them in; this is the measured order. */
extern void func_002ABBB8(void *o, void *a, void *b, f32 f0, f32 f1, s32 i0, s32 i1, s32 i2,
                          f32 f2, f32 f3, f32 f4, f32 f5, s32 i3, f32 f6, s32 i4, s32 i5, s32 i6,
                          s32 i7, s32 i8);
extern void func_0029F338(void *a0);

extern s32 D_L04_001A8F00;
extern u8 D_001A7A40;
extern u8 D_L04_001B1DE0;
extern u8 D_L04_001B1DE1;
extern f32 D_L04_001B1E00;
extern f32 D_L04_001B1E04;
extern f32 D_L04_001B1E08;
extern void func_3325E0(void *a0, void *a1, void *a2);

/* func_L04_004389C0 reads D_001A79F0 through $gp; it is in
   src/levels/04_barlow/L04_004389C0-g8.c. */

/* The level's list of live objects: the count is at +0x44 and the entries at +0x18C. */
typedef struct {
    u8 pad00[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    u32 *entries[16];
} L04Base004;

extern L04Base004 D_L04_001BD380;

/* Walks the level's list of objects and, for the one with the object's own id, asks the
   level's helper to clear it and sets the level's three timers. */
/* Same body as func_L04_00439870, with this function's own callees. */
void func_L04_00434AD0(u8 *moby) {
    u32 *elem;
    s32 i;

    if (D_L04_001A8F00 == 2) {
        if (D_001A7A40 != 0) {
            for (i = 0; i < D_L04_001BD380.count; i++) {
                elem = D_L04_001BD380.entries[i];
                if (*(s16 *)((u8 *)elem + 0xAA) == *(s16 *)(moby + 0xAA)) {
                    if (D_L04_001B1DE1 == 0) {
                        func_3325E0(elem, 0, &D_L04_001B1DE0);
                        D_L04_001B1E00 = 2.75f;
                        D_L04_001B1E04 = 2.75f;
                        D_L04_001B1E08 = 2.75f;
                    }
                }
            }
        }
    }
}
