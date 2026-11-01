#include "include_asm.h"

typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef float f32;
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern f32 D_L02_001B1258 __attribute__((sda));
extern f32 D_L02_001B125C __attribute__((sda));
extern s32 func_00312B58(char *);
extern s32 func_L02_00416800(char *);
extern s32 func_002A77E0(s32);
extern s32 func_L02_003D77B8(char *);
extern s32 func_L02_003FD000(char *);
extern f32 func_00282E80(char *, char *);
extern unsigned char D_001395B8[0x100];
extern int func_L02_003F9B70(int);
extern int func_L02_00400650(char *, int);
extern s32 D_L02_001B30C8;
extern s32 func_002A7820(s32, s32);
extern s32 D_0018C2EC __attribute__((nosda));
extern s32 func_L02_00400650(char *, s32);
extern s32 D_0018C0B4 __attribute__((nosda));
extern u8 D_001395B8[];
extern u8 D_00139568[];
extern s32 func_L00_0032EF10(s32, s32, s32 *);
extern s32 func_L02_003F9B70(s32);
extern s32 func_00288D58(void);
extern const s32 D_L02_001B1524 __attribute__((sda));
extern s32 D_L02_001B1530 __attribute__((sda));
extern s32 D_001A7A00;
extern s32 func_00282948(void *);
extern void *func_PAL_L00_002D7850(s32);
extern void func_L00_002D7140(void *);
extern f32 D_L02_001B1234 __attribute__((sda));
extern f32 D_L02_001B1238 __attribute__((sda));
extern f32 D_L02_001B123C __attribute__((sda));
extern f32 D_L02_001B1240 __attribute__((sda));
extern f32 D_L02_001B1244 __attribute__((sda));
extern f32 D_L02_001B1248 __attribute__((sda));
extern f32 D_L02_001B124C __attribute__((sda));
extern f32 D_L02_001B1250 __attribute__((sda));
extern f32 D_L02_001B1254 __attribute__((sda));
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} L02_003FC9C0_Vec3;

/* In state 8 the actor's 0xC0 object is created through func_PAL_L00_002D7850(5) when missing,
   otherwise it gets one of three float triples: by the class (+0xAA, 0x9F8 or 0xA44) of the
   0xD0 object, or the default one when there is none. In any other state the object is
   released through func_L00_002D7140 and the slot cleared.
   Each branch writes its own triple; the y and z stores (re-reading 0xC0) come out as one tail
   through cross-jumping after reload, which is why z keeps its own register ($f2). The stores
   are struct fields so the sda loads are not ordered behind them. */
void func_PAL_L02_00401118(u8 *a0) {
    u8 *s0 = *(u8 **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x20) == 8) {
        L02_003FC9C0_Vec3 *obj = *(L02_003FC9C0_Vec3 **)(s0 + 0xC0);

        if (obj == 0) {
            *(L02_003FC9C0_Vec3 **)(s0 + 0xC0) = func_PAL_L00_002D7850(5);
        } else {
            u8 *src = *(u8 **)(s0 + 0xD0);

            if (src != 0) {
                if (*(s16 *)(src + 0xAA) == 0x9F8) {
                    obj->x = D_L02_001B1240;
                    (*(L02_003FC9C0_Vec3 **)(s0 + 0xC0))->y = D_L02_001B1244;
                    (*(L02_003FC9C0_Vec3 **)(s0 + 0xC0))->z = D_L02_001B1248;
                } else if (*(s16 *)(src + 0xAA) == 0xA44) {
                    obj->x = D_L02_001B124C;
                    (*(L02_003FC9C0_Vec3 **)(s0 + 0xC0))->y = D_L02_001B1250;
                    (*(L02_003FC9C0_Vec3 **)(s0 + 0xC0))->z = D_L02_001B1254;
                }
            } else {
                obj->x = D_L02_001B1234;
                (*(L02_003FC9C0_Vec3 **)(s0 + 0xC0))->y = D_L02_001B1238;
                (*(L02_003FC9C0_Vec3 **)(s0 + 0xC0))->z = D_L02_001B123C;
            }
        }
    } else {
        func_L00_002D7140(*(L02_003FC9C0_Vec3 **)(s0 + 0xC0));
        *(L02_003FC9C0_Vec3 **)(s0 + 0xC0) = 0;
    }
}
