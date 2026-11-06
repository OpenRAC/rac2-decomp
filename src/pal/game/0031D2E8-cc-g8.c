/* func_PAL_0031D2E8, the PAL copy of func_0031BCC8: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50. */
#include "common.h"

/* -G8 unit for func_PAL_0031D2E8, which reads D_001B1B5C absolutely
   (003173B0-g8.c declares it sda). */

/* Notes for this match (USA v1.01 and v2.00, boot and level 00):
   - The tuning stores are written so sched1 keeps retail's order: stores whose
     constant dies issue first, so the shared-constant uses that must come later
     (0x84, 0x9C, 0xCC..0xD2, 0x118) are written before their last use, and
     0x77 = 24 is written last among the bytes so it gets $v1.
   - Retail keeps a copy of data + 0x350 for both qcopy targets: written as an
     expression each time, gcse's reaching register survives because cse does
     not rewrite the qcopy asm inputs.
   - oldpos/origin/route are set before the event code; written as expressions,
     gcse would insert them on the group loop's entry edges, and loop.c would no
     longer move the 0x264 exit block out of the loop.
   - The child's 0x38 field is stored as an array element (an in-struct store),
     so the sda scalar D_001AFAF8 is read ahead of it. */

extern void func_0031C720(char *);
extern unsigned short *D_001EE5A0[];
extern char *D_001B1B5C;
extern void func_002B60B0(char *, float, float, float, float);
extern void func_0029FCC0(char *, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern char D_001BAFA0[];
extern float func_002A89A8(void *, int, float);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern char *D_001B1C4C;
extern char *func_0029EFD0(int);
extern float D_001AFAF8 __attribute__((sda));
extern void func_002A0F48(void *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_0029FC20(void *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern int D_001B1B78 __attribute__((sda));
extern int func_002A8508(int, int);
extern int func_002B3670(void *, int *, int, int, void *, float, float);

void func_PAL_0031D2E8(unsigned char *self)
{
    char local[0x40] __attribute__((aligned(16)));
    char *data = *(char **)(self + 0x68);
    char *position;
    char *oldpos;
    int *route;
    char *origin;
    int state;
    unsigned short *member;
    char *other;
    char *otherdata;
    if ((unsigned char)self[0x20] == 0) {
        *(char **)(data + 0x18) = data + 0x110;
        *(int *)(data + 0x290) = 1;
        *(int *)(data + 0x27C) = 0;
        *(int *)(data + 0x28C) = 0;
        *(float *)(data + 0x254) *= 0.01745329424738884f;
        {
            char *spawn = data + 0x5A0;
            position = self + 0x10;
            qcopy(spawn, position);
        }
        *(int *)(data + 0x294) = 0;
        *(int *)(data + 0x298) = 0;
        *(float *)(data + 0x90) = 0.5f;
        *(float *)(data + 0x94) = 0.5f;
        *(float *)(data + 0x114) = 0.5f;
        *(float *)(data + 0x84) = 0.006f;
        *(float *)(data + 0x9C) = 0.4000000059604645f;
        *(char *)(data + 0xCC) = -1;
        *(char *)(data + 0xCD) = -1;
        *(char *)(data + 0xCE) = -1;
        *(char *)(data + 0xCF) = -1;
        *(char *)(data + 0xD2) = -1;
        *(float *)(data + 0x118) = 0.4000000059604645f;
        *(char *)(data + 0x70) = 15;
        *(int *)(data + 0xA8) = 5;
        *(char *)(data + 0x71) = 19;
        *(char *)(data + 0x72) = 21;
        *(char *)(data + 0x76) = 23;
        *(char *)(data + 0x77) = 24;
        *(float *)(data + 0x7C) = 0.120000005f;
        *(float *)(data + 0x80) = 0.080000006f;
        *(float *)(data + 0x88) = 0.012f;
        *(float *)(data + 0x8C) = 0.006f;
        *(char *)(data + 0xD3) = -1;
        *(float *)(data + 0x110) = 0.800000011920929f;
        *(float *)(data + 0x11C) = 0.4000000059604645f;
        *(float *)(data + 0x120) = 1.134464144706726f;
        *(float *)(data + 0x140) = 0.523598849773407f;
        *(float *)(data + 0x13C) = 0.008f;
        func_002B60B0(self, 0.0064000003f, 0.16000001f, 0.0016755164f, 0.12566373f);
        qcopy(data + 0x200, position);
        *(int *)(data + 0x250) = 0;
        *(float *)(data + 0x210) = 1.0f;
        *(float *)(data + 0x21C) = 5.0f;
        *(float *)(data + 0x220) = 10.0f;
        data[0x28] = 3;
        func_0029FCC0(self, 3, data + 0x350);
        *(float *)(data + 0x358) += 20.0f;
        func_0029FCC0(self, 3, data + 0x360);
        if (func_002761F8(data + 0x360, data + 0x350, 0, self, 0))
            qcopy(data + 0x350, D_001BAFA0);
        if (*(int *)(data + 0x24C) == 0 && *(int *)(data + 0x258) == -1) {
            *(float *)(self + 0x18) = func_002A89A8(position, 0, 0.5f);
            func_002A7750(self, 1, 0);
            if ((unsigned char)self[0x43] != 0) func_PAL_002A7E68(self, 0, 0, 0);
        } else {
            func_002A7750(self, 3, 2);
            if ((unsigned char)self[0x43] != 12) func_PAL_002A7E68(self, 12, 0, 0);
        }
        if (*(int *)(data + 0x258) != -1) {
            func_002A7750(self, 2, 0);
            qcopy(data + 0x350, D_001B1C4C + (*(int *)(data + 0x258) << 7) + 0x30);
            *(unsigned char *)(self + 0x30) = 0x80;
        }
        *(char **)(data + 0x270) = func_0029EFD0(0xAA2);
        (*(char **)(data + 0x270))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x270) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x270))[0x31] = 1;
        ((long long *)*(char **)(data + 0x270))[7] = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x270) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x270));
        func_002AF1D0(self, *(char **)(data + 0x270), 0, 0);
        *(char **)(data + 0x274) = func_0029EFD0(0xAA2);
        (*(char **)(data + 0x274))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x274) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x274))[0x31] = 1;
        ((long long *)*(char **)(data + 0x274))[7] = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x274) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x274));
        func_002AF1D0(self, *(char **)(data + 0x274), 1, 0);
        *(char **)(data + 0x278) = func_0029EFD0(0xAA2);
        (*(char **)(data + 0x278))[0x30] = self[0x30];
        *(short *)(*(char **)(data + 0x278) + 0x32) = *(short *)(self + 0x32);
        (*(char **)(data + 0x278))[0x31] = 1;
        ((long long *)*(char **)(data + 0x278))[7] = *(long long *)(self + 0x38);
        *(float *)(*(char **)(data + 0x278) + 0x2C) *= D_001AFAF8;
        func_002A0F48(*(char **)(data + 0x278));
        func_002AF1D0(self, *(char **)(data + 0x278), 2, 0);
    }
    oldpos = data + 0x5A0;
    origin = self + 0x10;
    route = (int *)(data + 0x248);
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
    state = func_PAL_002B1A50(self, data + 0x60, 0);
    if (state) {
        if (state == 5) {
            *(int *)(data + 0xF0) = 0;
            *(float *)(data + 0xF4) = 1.0053098f;
        }
        func_0031C720(self);
        if ((unsigned)(state - 4) < 2 && D_001B1B78 >= (unsigned char)self[0x21] && func_002A8508((unsigned char)self[0x21], -1) >= 2) {
            member = D_001EE5A0[(unsigned char)self[0x21]];
            for (;;) {
                other = D_001B1B5C + ((*member & 0x7FFF) << 8);
                if (*(short *)(other + 0xAA) == 0x9B4) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x2A4) == 0) {
                        *(int *)(otherdata + 0x2A4) = 1;
                        break;
                    }
                } else if (*(short *)(other + 0xAA) == 0x9B5) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x264) == 0) {
                        *(int *)(otherdata + 0x264) = 1;
                        goto group_done_0;
                    }
                }
                if (*(short *)member++ < 0) goto group_done_0;
            }
        group_done_0:;
        }
    }
    if (*(float *)(self + 0x18) - func_002A89A8(origin, 0, 0.5f) > 20.0f && D_001B1B78 >= (unsigned char)self[0x21] && !*(int *)(data + 0x298)) {
        *(int *)(data + 0x298) = 1;
        if (func_002A8508((unsigned char)self[0x21], -1) >= 2) {
            member = D_001EE5A0[(unsigned char)self[0x21]];
            for (;;) {
                other = D_001B1B5C + ((*member & 0x7FFF) << 8);
                if (*(short *)(other + 0xAA) == 0x9B4) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x2A4) == 0) {
                        *(int *)(otherdata + 0x2A4) = 1;
                        break;
                    }
                } else if (*(short *)(other + 0xAA) == 0x9B5) {
                    otherdata = *(char **)(other + 0x68);
                    if (*(int *)(otherdata + 0x264) == 0) {
                        *(int *)(otherdata + 0x264) = 1;
                        goto group_done_1;
                    }
                }
                if (*(short *)member++ < 0) goto group_done_1;
            }
        group_done_1:;
        }
    }
    *(short *)(data + 0x244) = func_002B3670(self, route, *(int *)(data + 0x230), *(int *)(data + 0x234), oldpos, *(float *)(data + 0x238), *(float *)(data + 0x23C));
}
