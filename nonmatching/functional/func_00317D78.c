/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* sol-high v0883 retained attempt, USA v1.01, default game compiler profile.
 * Recompiled on upstream pinned compiler: 1132/1128 bytes, 0/2 places.
 * Qualified native TI qcopy/barrier and -fno-gcse retain the same s4 lifetime.
 * Disabling CSE jump/skip following reached 1128 bytes but changed allocation
 * throughout the body. Disabling jump following alone reached 1124 bytes.
 * Reordered ordinary initializers did not close FP/store scheduling.
 * Next: a source shape that rematerializes the real self+0x10 pointer after
 * the copy, rather than preserving it until the later distance call.
 * closer D successor, 1 November 2026: retail materialises both addresses for the copy
 * (addiu a0,s2,0x200; addiu v1,s3,0x10) and recomputes self+0x10 for the distance call. Flags
 * alone: -fno-gcse 71, -fno-cse-follow-jumps 78 (1124), both cse switches off 153 (1128).
 * Earlier sol-low measurements follow (still applicable):
 * Best check: 1132 bytes versus 1128; 0 of 2 places match.
 * The qcopy address self+0x10 is retained in s4 across calls, adding a save
 * and restore; retail recomputes it. Initialization constant allocation and
 * store scheduling also differ. Three qcopy/qcopy_nc/address-view forms tied.
 * Native TI assignment avoids s4 but emits direct-offset loads/stores and
 * shrinks to 1112 bytes, so it does not reproduce the retail copy either.
 * Needs common.h, D_001B5200 (state with float pos[3] at +0x140),
 * D_001EE5A0 (short *array), D_001B1B5C (char *), and func_00282E48.
 * The init flag bytes are observed at the exact offsets below. No name is
 * proposed because the object's identity is not established.
 */
#include "common.h"
typedef struct { char pad[0x140]; float pos[3]; } B0512State;
extern B0512State D_001B5200;
extern short *D_001EE5A0[];
extern char *D_001B1B5C __attribute__((sda));
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern void func_002B60B0(char *, float, float, float, float);
extern int func_002A77E0(int);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern void func_002A93B0(char *);
extern int func_002B0ED8(char *, char *, int);
extern int D_001B1B78;
extern int func_002A8508(int, int);
extern int func_002B3BA8(char *, int, float, float, int, int);
extern void func_003181E0(void *);
extern void func_003182C0(void *);
int func_00317D78(unsigned char *self)
{
    char *data = *(char **)(self + 0x68);
    int result, dead;
    short *p;
    char *other;
    if ((unsigned char)self[0x20] == 0) {
        self[0x7E] |= 1;
        *(char **)(data + 0x18) = data + 0x110;
        *(float *)(data + 0x28C) = *(float *)(self + 0x18);
        *(float *)(self + 0x2C) *= 0.75f;
        *(int *)(data + 0x2A8) = -1;
        data[0x48] = func_00283CF0(10.0f);
        data[0x4A] = func_00283CF0(8.0f);
        if (*(float *)(data + 0x290) == -1.0f)
            *(float *)(data + 0x290) = 0.01745329424738884f * func_002A78D8(25.0f, 100.0f);
        else
            *(float *)(data + 0x290) *= 0.01745329424738884f;
        self[0x30] = 48;
        *(float *)(data + 0x1C0) = *(float *)(data + 0x29C) * 0.01666666753590107f;
        data[0xD2] = data[0xCF] = data[0xCE] = data[0xCD] = data[0xCC] = data[0xD3] = -1;
        data[0x70] = 11;
        *(float *)(data + 0x7C) = 0.10000000894069672f;
        *(float *)(data + 0x88) = 0.008333333767950535f;
        
        *(float *)(data + 0x9C) = 0.4f;
        *(float *)(data + 0x110) = 0.85f;
        *(float *)(data + 0x118) = 0.75f;
        *(float *)(data + 0x120) = 1.134464144706726f;
        *(float *)(data + 0x140) = 25.13274383544922f;
        *(float *)(data + 0x80) = 0.06666667014360428f;
        *(float *)(data + 0x84) = *(float *)(data + 0x8C) = 0.004166666883975267f;
        *(int *)(data + 0x298) = 1;
        *(int *)(data + 0xA8) = 3;
        data[0x71] = 0; data[0x72] = 0; data[0x76] = 0; data[0x77] = 0;
        *(float *)(data + 0x90) = 0.5f; *(float *)(data + 0x94) = 0.5f;
        data[0xD6] = 1;
        *(int *)(data + 0x114) = 0;
        *(float *)(data + 0x11C) = 0.5f;
        *(int *)(data + 0x13C) = 0;
        *(int *)(data + 0x148) |= 0x10;
        func_002B60B0(self, 0.006666666828095913f, 0.06666667014360428f, 0.8377581834793091f, 0.8377581834793091f);
        qcopy(data + 0x200, self + 0x10);
        data[0x28] = 3; data[0x2E] = 1;
        *(float *)(data + 0x210) = 1.0f;
        *(float *)(data + 0x21C) = 5.0f;
        *(float *)(data + 0x220) = 10.0f;
        *(float *)(data + 0x2B0) = (unsigned char)data[0x34];
        *(float *)(data + 0x30) -= 0.5f;
        *(short *)(data + 0x272) = func_002A77E0(10);
        func_002A7750(self, 2, 0);
        if ((unsigned char)self[0x43]) func_002A7470(self, 0, 0, 0);
    }
    if ((unsigned char)self[0x31] && func_00282E48(self + 0x10, D_001B5200.pos) < 48.0f) {
        func_002A93B0(self); self[0x6F] = 45;
    }
    dead = (unsigned char)data[0x2E] == 2;
    result = func_002B0ED8(self, data + 0x60, 0);
    if (result || dead) {
        func_003182C0(self);
        if ((unsigned int)(result - 4) < 2 || dead) {
            if ((unsigned char)self[0x21] <= D_001B1B78 && func_002A8508((unsigned char)self[0x21], -1) >= 2) {
                p = D_001EE5A0[(unsigned char)self[0x21]];
                do {
                    other = D_001B1B5C + ((*p & 0x7FFF) << 8);
                    if (*(short *)(other + 0xAA) == 0x99C) {
                        char *otherData = *(char **)(other + 0x68);
                        if (!*(int *)(otherData + 0x2AC)) {
                            *(int *)(otherData + 0x2AC) = 1;
                            break;
                        }
                    }
                } while (*p++ >= 0);
            }
        }
    }
    if (dead) { func_003181E0(self); return 1; }
    *(int *)(data + 0x258) = func_002B3BA8(self, *(int *)(data + 0x250), *(float *)(data + 0x268), 10.0f, 0, 0);
    *(int *)(data + 0x25C) = func_002B3BA8(self, *(int *)(data + 0x254), *(float *)(data + 0x26C), 10.0f, 0, 0);
    return 0;
}


