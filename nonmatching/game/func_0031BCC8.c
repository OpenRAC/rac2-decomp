/* opus-1 (Claude Opus 5.5, xhigh) near miss, USA v1.01, -O2 -G8.
 * Best check.py result: 1992 / 1996 bytes, 0 of 2 places (boot and level 00).
 * Needs its own -G8 unit (for example src/game/003173B0-group-g8.c): retail
 * reads D_001B1B5C absolutely, but 003173B0-g8.c declares it sda, so it cannot
 * sit next to func_0031C720. Uses the declarations below.
 * Group loops: the 0x9B4 exit must be a `break` and the later exits a goto
 * past the loop, so expand_end_loop rotates only the first test and
 * duplicate_loop_exit_test copies it. Use a separate `if` for 0x9B5 (not
 * `else if`) to get the out-of-line 0x264 block and its nop. Reading
 * D_001B1B5C every iteration gives retail's a0 load and t0 copy.
 * Remaining: one missing insn, `daddu s5,s0,zero`. Retail keeps data+0x350
 * in s0 for the call arguments and a copy in s5 for both qcopy targets; an
 * expression-or-variable split before or after the first call did not keep
 * the copy. Saved registers are shifted (retail self=s3, data=s2; here
 * s2/s1). sched reorders the initializer stores; retail keeps source order.
 * Small slot differences in the 0xAA2 and state==5 blocks.
 */
#include "include_asm.h"
#include "common.h"

/* -G8 unit for func_0031BCC8, which reads D_001B1B5C absolutely
   (003173B0-g8.c declares it sda). */

extern void func_0031C720(char *);
extern unsigned short *D_001EE5A0[];
extern char *D_001B1B5C;
extern void func_002B60B0(char *, float, float, float, float);
extern void func_0029FCC0(char *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern char D_001BAFA0[];
extern float func_002A89A8(void *, float, int);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern char *D_001B1C4C;
extern char *func_0029EFD0(int);
extern float D_001AFAF8 __attribute__((sda));
extern void func_002A0F48(void *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_0029FC20(void *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002B0ED8(void *, void *, int);
extern int D_001B1B78 __attribute__((sda));
extern int func_002A8508(int, int);
extern int func_002B3670(void *, void *, int, int, float, float, void *);

void func_0031BCC8(unsigned char *self)
{
    char local[0x40] __attribute__((aligned(16)));
    char *data = *(char **)(self + 0x68);
    char *position;
    char *normal;
    char *oldpos;
    int state;
    int classid;
    unsigned short *member;
    char *other;
    char *otherdata;
    if ((unsigned char)self[0x20] == 0) {
        *(float *)(data + 0x254) *= 0.01745329424738884f;
        *(char **)(data + 0x18) = data + 0x110;
        *(int *)(data + 0x290) = 1;
        *(int *)(data + 0x27C) = 0;
        *(int *)(data + 0x28C) = 0;
        position = self + 0x10;
        qcopy_nc(data + 0x5A0, position);
        *(int *)(data + 0x294) = 0;
        *(int *)(data + 0x298) = 0;
        *(float *)(data + 0x90) = 0.5f;
        *(float *)(data + 0x94) = 0.5f;
        *(float *)(data + 0x114) = 0.5f;
        *(char *)(data + 0x77) = 24;
        *(char *)(data + 0x70) = 15;
        *(int *)(data + 0xA8) = 5;
        *(char *)(data + 0x71) = 19;
        *(char *)(data + 0x72) = 21;
        *(char *)(data + 0x76) = 23;
        *(float *)(data + 0x7C) = 0.10000000894069672f;
        *(float *)(data + 0x80) = 0.06666667014360428f;
        *(float *)(data + 0x88) = 0.008333333767950535f;
        *(float *)(data + 0x8C) = 0.004166666883975267f;
        *(char *)(data + 0xD3) = -1;
        *(float *)(data + 0x110) = 0.800000011920929f;
        *(float *)(data + 0x11C) = 0.4000000059604645f;
        *(float *)(data + 0x120) = 1.134464144706726f;
        *(float *)(data + 0x140) = 0.523598849773407f;
        *(float *)(data + 0x13C) = 0.0055555556900799274f;
        *(float *)(data + 0x84) = 0.004166666883975267f;
        *(float *)(data + 0x9C) = 0.4000000059604645f;
        *(char *)(data + 0xCC) = -1;
        *(char *)(data + 0xCD) = -1;
        *(char *)(data + 0xCE) = -1;
        *(char *)(data + 0xCF) = -1;
        *(char *)(data + 0xD2) = -1;
        *(float *)(data + 0x118) = 0.4000000059604645f;
        func_002B60B0(self, 0.004444444552063942f, 0.13333334028720856f, 0.0011635529808700085f, 0.10471977293491364f);
        qcopy_nc(data + 0x200, position);
        *(int *)(data + 0x250) = 0;
        *(float *)(data + 0x210) = 1.0f;
        *(float *)(data + 0x21C) = 5.0f;
        *(float *)(data + 0x220) = 10.0f;
        data[0x28] = 3;
        normal = data + 0x350;
        func_0029FCC0(self, 3, normal);
        *(float *)(data + 0x358) += 20.0f;
        func_0029FCC0(self, 3, data + 0x360);
        if (func_002761F8(data + 0x360, data + 0x350, 0, self, 0))
            qcopy_nc(normal, D_001BAFA0);
        if (*(int *)(data + 0x24C) == 0 && *(int *)(data + 0x258) == -1) {
            *(float *)(self + 0x18) = func_002A89A8(position, 0.5f, 0);
            func_002A7750(self, 1, 0);
            if ((unsigned char)self[0x43] != 0) func_002A7470(self, 0, 0, 0);
        } else {
            func_002A7750(self, 3, 2);
            if ((unsigned char)self[0x43] != 12) func_002A7470(self, 12, 0, 0);
        }
        if (*(int *)(data + 0x258) != -1) {
            func_002A7750(self, 2, 0);
            qcopy_nc(normal, D_001B1C4C + (*(int *)(data + 0x258) << 7) + 0x30);
            *(unsigned char *)(self + 0x30) = 0x80;
        }
        *(char **)(data + 0x270) = func_0029EFD0(0xAA2);
        (*(char **)(data + 0x270))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x270) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x270))[0x31] = 1;
        *(long long *)(*(char **)(data + 0x270) + 0x38) = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x270) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x270));
        func_002AF1D0(self, *(char **)(data + 0x270), 0, 0);
        *(char **)(data + 0x274) = func_0029EFD0(0xAA2);
        (*(char **)(data + 0x274))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x274) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x274))[0x31] = 1;
        *(long long *)(*(char **)(data + 0x274) + 0x38) = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x274) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x274));
        func_002AF1D0(self, *(char **)(data + 0x274), 1, 0);
        *(char **)(data + 0x278) = func_0029EFD0(0xAA2);
        (*(char **)(data + 0x278))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x278) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x278))[0x31] = 1;
        *(long long *)(*(char **)(data + 0x278) + 0x38) = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x278) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x278));
        func_002AF1D0(self, *(char **)(data + 0x278), 2, 0);
    }
    oldpos = data + 0x5A0;
    position = self + 0x10;
    func_0029FCC0(self, 3, data + 0x360);
    func_0029FCC0(self, 4, data + 0x370);
    func_0029FCC0(self, 5, data + 0x380);
    func_0029FC20(self, 6, local);
    func_00282C88(data + 0x390);
    *(int *)(data + 0x398) = 0;
    *(float *)(data + 0x390) = 0.25f;
    func_002830C0(data + 0x390, data + 0x390, local);
    func_00282CC0(data + 0x390, data + 0x390, local + 0x30);
    func_002AF1D0(self, *(char **)(data + 0x270), 0, 0);
    func_002AF1D0(self, *(char **)(data + 0x274), 1, 0);
    func_002AF1D0(self, *(char **)(data + 0x278), 2, 0);
    state = func_002B0ED8(self, data + 0x60, 0);
    if (state) {
        if (state == 5) {
            *(int *)(data + 0xF0) = 0;
            *(float *)(data + 0xF4) = 0.8377581834793091f;
            func_0031C720(self);
        }
        if ((unsigned)(state - 4) < 2 && D_001B1B78 >= (unsigned char)self[0x21] && func_002A8508((unsigned char)self[0x21], -1) >= 2) {
            member = D_001EE5A0[(unsigned char)self[0x21]];
            for (;;) {
                other = D_001B1B5C + ((*member & 0x7FFF) << 8);
                classid = *(short *)(other + 0xAA);
                if (classid == 0x9B4) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x2A4) == 0) {
                        *(int *)(otherdata + 0x2A4) = 1;
                        break;
                    }
                }
                if (classid == 0x9B5) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x264) == 0) {
                        *(int *)(otherdata + 0x264) = 1;
                        goto group_done_0;
                    }
                }
                if (*(short *)member < 0) goto group_done_0;
                ++member;
            }
        group_done_0:;
        }
    }
    if (*(float *)(self + 0x18) - func_002A89A8(position, 0.5f, 0) > 20.0f && D_001B1B78 >= (unsigned char)self[0x21] && !*(int *)(data + 0x298)) {
        *(int *)(data + 0x298) = 1;
        if (func_002A8508((unsigned char)self[0x21], -1) >= 2) {
            member = D_001EE5A0[(unsigned char)self[0x21]];
            for (;;) {
                other = D_001B1B5C + ((*member & 0x7FFF) << 8);
                classid = *(short *)(other + 0xAA);
                if (classid == 0x9B4) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x2A4) == 0) {
                        *(int *)(otherdata + 0x2A4) = 1;
                        break;
                    }
                }
                if (classid == 0x9B5) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x264) == 0) {
                        *(int *)(otherdata + 0x264) = 1;
                        goto group_done_1;
                    }
                }
                if (*(short *)member < 0) goto group_done_1;
                ++member;
            }
        group_done_1:;
        }
    }
    *(short *)(data + 0x244) = func_002B3670(self, data + 0x248, *(int *)(data + 0x230), *(int *)(data + 0x234), *(float *)(data + 0x238), *(float *)(data + 0x23C), oldpos);
}
