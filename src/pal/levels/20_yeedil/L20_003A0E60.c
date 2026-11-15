#include "include_asm.h"

#include "common.h"
extern int trooper_spawn_parts(char *, int);
extern void *func_00325040(int);
extern void func_0033E708(char *, char *);
extern char *func_00338198(char *);
extern void func_00326528(char *, int, char *);
extern f32 func_00303270(f32, f32);
extern void func_00327AD0(void *);
extern void func_003381E0(void *, void *);
extern void func_00338830(void *, u32, int, int);
extern void func_0032F2D0(void *, int, int, int);
extern f32 vec_distance_xy(void *, void *);

int func_PAL_L20_003A0E60(char *arg0, int arg1) {
    char *s0;
    char *s1;
    char *s2 = arg0;
    char *s3;
    char *s4;
    int cnt;
    char *p2;
    int six;
    int v;

    s3 = *(char **)(s2 + 0x68);
    if (arg1 != 0) {
        if (*(char **)(s3 + 0x254) == 0) {
            s0 = (char *)func_00325040(0xD0E);
            if (s0 == 0) {
                v = 0;
                goto out;
            }
            func_0033E708(s0, s2);
            *(u16 *)(s0 + 0x7C) = 0x3FF;
            *(char **)(s3 + 0x254) = s0;
        }
        s4 = 0;
        s1 = s3 + 0x258;
        while ((int)s4 < 2) {
            if (*(u32 *)s1 == 0) {
                s0 = (char *)func_00325040(0xD66);
                if (s0 == 0) {
                    v = 0;
                    goto out;
                }
                func_0033E708(s0, s2);
                *(u32 *)s1 = (u32)s0;
            }
            s4++;
            s1 += 4;
        }
    }
    s4 = (char *)func_00338198(s2);
    if (*(char **)(s3 + 0x254) != 0) {
        func_00326528(s2, 0, *(char **)(s3 + 0x254) + 0x10);
        *(f32 *)(*(char **)(s3 + 0x254) + 0xF8) = func_00303270(*(f32 *)(s2 + 0xF8), *(f32 *)(s3 + 0x288));
        func_00327AD0(*(char **)(s3 + 0x254));
        func_003381E0(*(char **)(s3 + 0x254), s4);
        if (*(u8 *)(*(char **)(s3 + 0x254) + 0x43) != *(u8 *)(s2 + 0x43)) {
            func_0032F2D0(*(char **)(s3 + 0x254), *(u8 *)(s2 + 0x43), *(u8 *)(s2 + 0x41), 0x8);
        }
    }
    cnt = 0;
    six = 6;
    p2 = s3 + 0x258;
    while (cnt < 2) {
        if (*(u32 *)p2 != 0) {
            func_00338830(*(char **)(s3 + 0x254), *(u32 *)p2, cnt, (cnt == 1) ? six : 0);
            func_003381E0(*(u32 *)p2, s4);
        }
        cnt++;
        p2 += 4;
    }
    v = 1;
out:
    return v;
}

