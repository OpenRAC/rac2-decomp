#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(char *, char *, char *);
extern void make_hit_descriptor(char *, int, int, void *, float);
extern int CollLine(void *, void *, int, int, void *);
extern int math_fast_float_d(void *);
extern void snd_play_from_class_bank(int, int, void *, int);
extern void gfx_add_draw_callback_third(void *, int);
extern void func_PAL_L20_0039F518(char *);
extern void func_PAL_L20_0039F810(char *, int, int);
extern void gfx_draw_projectile_trail(void);
extern void moby_mark_spawned(int);
extern char D_L20_001C0420[];

void func_PAL_L20_0039F390(char *arg0) {
    char *s0 = arg0 + 0x10;
    char *s3 = *(char **)(arg0 + 0x68);
    char *s1;
    char buf[0x30];

    *(TI128 *)s3 = *(TI128 *)s0;
    s1 = s3 + 0x10;
    FastVecAdd(s0, s0, s1);
    make_hit_descriptor(buf, (int)arg0, 0x10001, s1, *(float *)(s3 + 0x2C));
    if (CollLine(s3, s0, 0, *(int *)(arg0 + 0xB8), buf) != 0
        || math_fast_float_d(s3 + 0x20) != 0) {
        func_PAL_L20_0039F810(D_L20_001C0420, 0x14, 1);
        snd_play_from_class_bank(2, 0, arg0, 0x12EF);
        moby_mark_spawned((int)arg0);
    } else {
        func_PAL_L20_0039F518(arg0);
        gfx_add_draw_callback_third(gfx_draw_projectile_trail, (int)arg0);
    }
}

extern char *CreateMoby(int);

/* Spawns an object of type 0x12F2 and fills its position and its sub-record vector. */
char *func_PAL_L20_0039F488(char *arg0, char *arg1, char *arg2, float f12) {
    char *v;
    char *o = CreateMoby(0x12F2);

    if (o != 0) {
        *(int *)(o + 0xB8) = (int)arg0;
        *(TI128 *)(o + 0x10) = *(TI128 *)arg1;
        v = *(char **)(o + 0x68);
        *(unsigned char *)(o + 0x30) = 0xFF;
        *(TI128 *)(v + 0x10) = *(TI128 *)arg2;
        *(float *)(v + 0x2C) = f12;
        *(int *)(v + 0x20) = 0xFA;
    }
    return o;
}
