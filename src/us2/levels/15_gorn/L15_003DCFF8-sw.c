#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
struct L02NearObject;
struct L02GroupObject;
extern char D_00189E20[] NOT_SDA;
typedef struct { char pad[0x18]; char *hit; int count; } L02Collision;
extern L02Collision D_L15_001BFC00;
extern char *D_L15_001FE480[];
extern int D_L15_001B2148[] __attribute__((sda));
extern int func_L02_003CC7B0(char *), func_L02_003CCFE8(char *, void *);
extern void func_L02_003CCCC8(char *), func_L02_003CCEA0(char *), func_L02_003CD1E8(char *, void *), func_L02_003CD758(char *);
extern void func_L02_003CD298(struct L02NearObject *), func_L02_003CD4A8(struct L02GroupObject *), func_L02_003CED70(char *, void *, void *);
extern u8 *func_L02_003CEBB8(int);
extern void func_0029F338(void *), func_002A7750(u8 *, int, int), func_002A7470(char *, int, int, int), func_US2_002A7AA8(char *, void *, int);
extern int func_002B3868(u8 *), func_002B3890(u8 *), func_002A77E0(int), func_002A7820(int, int), func_00282978(short *);
extern void *func_002B60B0(u8 *, float, float, float, float);
extern int func_002B1C20(void *, void *);
extern void func_L01_003E9CF8(char *, int, void (*)(char *));
extern int func_L01_00321178(char *, char *), func_L01_00322288(int, float), func_L02_00331440(void *, void *, int, float, float, float), func_L02_00332630(char *, void *);
extern float func_00283248(float, float), func_00283C80(float, float), func_00282E48(void *, void *), func_00282E80(void *, void *), func_00282C48(float), func_00282DB0(void *, void *), func_0029F530(char *);
extern int func_002761F8(void *, void *, int, char *, void *), func_002ABB78(char *), func_US2_002AF9C8(char *, float), func_002ACBC8(void *, int), func_002B6120(char *, char *), func_002B6318(u8 *);
extern int func_002A8D70(float, float, float, void *, void *, int, int, int, int);
extern void func_0029FC20(char *, int, char *), func_0029FCC0(char *, int, char *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00282D30(void *, void *, float);
extern void *func_L02_00401530(void *, void *, void *, float, float, float, int, int, int);
typedef struct {
    u8 prefix[0x80]; Vector position_80; u8 gap_90[0x40]; Vector target_d0;
    u8 gap_e0[0x21B0]; char *pointer_2290; u8 gap_2294[8]; int mode_229c;
    u8 gap_22a0[0x1FC]; char *pointer_249c;
} L02_ResidentCombatPrefix;

void func_US2_L15_003DCFF8(char *self) {
    /* One frame area, two layouts: the aiming states and the case-21 hand-off. */
    union {
        struct { Vector muzzle, velocity, acceleration, transform[4]; } aim;
        struct { Vector frame[4], direction, origin; } relay;
    } work;
    char *state = *(char **)(self + 0x68), *path, *other;
    L02Collision *col;
    int flags;
    float angle, time, power;

    int choice, animation, collision, contact;
    if (func_L02_003CC7B0(self)) { func_0029F338(self); return; }
    switch (((u8 *)self)[0x95]) {
    case 0:
        if (func_002B3890((u8 *)self)) func_002B60B0((u8 *)self, 0.0011111111380159855f, 0.050000004f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(state + 0x204) == 1) {
            if (*(int *)(state + 0x33C)) { *(int *)(state + 0x33C) = 0; func_002A7750((u8 *)self, 8, 2); }
            else func_002A7750((u8 *)self, 10, 2);
        } else if (*(short *)(state + 0x382)) {
            func_002A7750((u8 *)self, 3, 1); *(short *)(state + 0x382) = 0; *(short *)(state + 0x374) = func_002A7820(480, 600);
        }
        break;
    case 1:
        if (func_002B3890((u8 *)self)) func_002B60B0((u8 *)self, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(state + 0x204) == 1) func_002A7750((u8 *)self, 10, 2);
        else if (!*(short *)(state + 0x374)) {
            if (func_00282E80(self + 0x10, &((L02_ResidentCombatPrefix *)D_00189E20)->position_80) > 26) func_002A7750((u8 *)self, 1, 0);
            else *(short *)(state + 0x374) = 120;
        }
        break;
    case 2:
        if (func_002B3890((u8 *)self)) {
            func_L02_003CD298((struct L02NearObject *)self);
            func_002B60B0((u8 *)self, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        }
        if (*(int *)(state + 0x204) != 1 && (((u8 *)self)[0x60] & 2) && ((u8 *)self)[0x20] != 11) {
            if (func_00282E48(self + 0x10, state + 0x340) > 4) func_002A7750((u8 *)self, 6, -1);
            else {
                switch (func_002A77E0(4)) {
                case 0: func_002A7750((u8 *)self, 3, 1); break;
                case 1: func_002A7750((u8 *)self, 4, 1); break;
                case 2: func_002A7750((u8 *)self, 5, 1); break;
                case 3: func_002A7750((u8 *)self, 7, 1); break;
                }
            }
            *(short *)(state + 0x374) = func_002A7820(580, 600);
        }
        break;
    case 3:
        flags = func_002B1C20(self, state + 0x50);
        if (flags & 1) {
            *(u16 *)(*(char **)(state + 0x370) + 0x34) |= 0x41; *(u16 *)(*(char **)(state + 0x370) + 0x34) &= 0xEFFF; *(int *)(*(char **)(state + 0x370) + 0x98) = 0;
            func_US2_002A7AA8(self, 0, 3); func_L01_003E9CF8(self, 0, func_L02_003CD758); return;
        }
        if (flags & 2) {
            *(int *)(state + 0x33C) = 0;
            if (*(int *)(state + 0x320) != -1) func_002A7750((u8 *)self, 18, 4);
            else if (*(int *)(state + 0x204) == 1) func_002A7750((u8 *)self, 10, 2);
            else { func_002A7750((u8 *)self, 3, 1); *(short *)(state + 0x374) = func_002A7820(580, 600); }

        }
        break;
    case 4:
        if (func_002B3890((u8 *)self)) {
            func_002B60B0((u8 *)self, 0.0033333334140479565f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f); *(float *)(state + 0x134) = 0.25f;
        }
        break;
    }
    switch (((u8 *)self)[0x20]) {
    case 1:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43]) func_002A7470(self, 0, 0, 20);
        if (!(((u8 *)self)[0x60] & 2)) break;
        if (!func_002A77E0(4)) { func_002A7750((u8 *)self, 5, -1); break; }
        else if (!*(int *)(state + 0x33C)) { func_002A7750((u8 *)self, 2, -1); break; }
        break;
    case 2:
        if (func_002B3868((u8 *)self)) {
            if (((u8 *)self)[0x43] != 5) func_002A7470(self, 5, 0, 20); func_L02_003CD1E8(self, state + 0x350);
        }
        if ((func_L01_00321178(self, state + 0x350) & 0x80) || *(u16 *)(self + 0x96) >= 181 || *(int *)(state + 0x180) >= 21) { func_002A7750((u8 *)self, 5, -1); break; }
        break;
    case 3:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 9) func_002A7470(self, 9, 0, 20);
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (func_00283C80(*(float *)(self + 0xF8), angle) > 0.26179942f) { func_002A7750((u8 *)self, 9, -1); break; }
        else if ((((u8 *)self)[0x60] & 2) && func_002A77E0(2)) {
            switch (func_002A77E0(3)) {
            case 0: func_002A7750((u8 *)self, 4, -1); break;
            case 1: func_002A7750((u8 *)self, 5, -1); break;
            case 2: func_002A7750((u8 *)self, 7, -1); break;
            }

        }
        break;
    case 4:
        if (func_002B3868((u8 *)self)) {
            animation = func_L02_003CCFE8(self, state + 0x350) ? 18 : 17;
            if (*(u16 *)(self + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)self)[0x43] != animation) func_002A7470(self, animation, 0, 10);
        }
        angle = func_00283248(*(float *)(state + 0x350) - *(float *)(self + 0x10), *(float *)(state + 0x354) - *(float *)(self + 0x14));
        if ((func_L02_00331440(self, state + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(self + 0x96) >= 121) { func_002A7750((u8 *)self, 3, -1); break; }
        break;
    case 5:
        if (func_002B3868((u8 *)self)) {
            if (((u8 *)self)[0x95]) { if (((u8 *)self)[0x95] == 1 && ((u8 *)self)[0x43] != func_002A77E0(2) + 3) func_002A7470(self, func_002A77E0(2) + 3, 0, 20); }
            else if (((u8 *)self)[0x43] != 1) func_002A7470(self, 1, 0, 20);
        }
        if (((u8 *)self)[0x60] & 2) { if (((u8 *)self)[0x95]) { if (((u8 *)self)[0x95] == 1) { func_002A7750((u8 *)self, 3, -1); break; } } else { func_002A7750((u8 *)self, 1, -1); break; } }

        break;
    case 7:
        if (func_002B3868((u8 *)self)) { animation = func_002A77E0(2) ? 20 : 21; if (((u8 *)self)[0x43] != animation) func_002A7470(self, animation, 0, 15); }
        if (((u8 *)self)[0x60] & 2) { func_002A7750((u8 *)self, 3, -1); break; }
        break;
    case 6:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 6) func_002A7470(self, 6, 0, 15);
        if ((func_L01_00321178(self, state + 0x340) & 0x80) || *(u16 *)(self + 0x96) >= 241) { func_002A7750((u8 *)self, 3, -1); break; }
        break;
    case 9:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 5) func_002A7470(self, 5, 0, 10);
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        func_L01_00322288((int)self, angle); func_L02_003CCEA0(self);
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (func_00283C80(*(float *)(self + 0xF8), angle) < 0.087266475f) {
            switch (((u8 *)self)[0x95]) {
            case 2: func_002A7750((u8 *)self, 10, -1); break;
            case 1: func_002A7750((u8 *)self, 3, -1); break;
            }

        }

        break;
    case 8:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 2) func_002A7470(self, 2, 0, 10);
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        func_L01_00322288((int)self, angle); func_L02_003CCEA0(self); if (((u8 *)self)[0x60] & 2) { func_002A7750((u8 *)self, 10, -1); break; }
        break;
    case 10:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 9) func_002A7470(self, 9, 0, 20);
        func_L02_003CCEA0(self);
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (func_00283C80(*(float *)(self + 0xF8), angle) > 0.52359885f) { { func_002A7750((u8 *)self, 9, -1); break; } break; }
        if (!*(short *)(state + 0x378) && *(u16 *)(self + 0x96) > 15) {
            func_0029FCC0(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
            contact = func_002761F8(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)D_00189E20)->target_d0, 16, self, 0);
            if (contact && D_L15_001BFC00.hit && *(short *)(D_L15_001BFC00.hit + 0xAA) == 0xC1B) { { func_002A7750((u8 *)self, 13, -1); break; } break; }
            if (contact && (col = &D_L15_001BFC00)->hit != ((L02_ResidentCombatPrefix *)D_00189E20)->pointer_2290 && !*(short *)(state + 0x386)) {
                if (!col->hit || (!func_002ABB78(col->hit) && (!*(char **)(col->hit + 0x24) || *(short *)(*(char **)(col->hit + 0x24) + 0x46) != 22))) break;
            }
            { func_002A7750((u8 *)self, 11, -1); break; }
        } else {
            if (func_00282E80(self + 0x10, &((L02_ResidentCombatPrefix *)D_00189E20)->position_80) < 3 && func_00282C48(*(float *)(self + 0x18) - ((L02_ResidentCombatPrefix *)D_00189E20)->position_80.f[2]) < 0.5f) { { func_002A7750((u8 *)self, 14, -1); break; } break; }
            if ((((u8 *)self)[0x60] & 2) && !func_002A77E0(2)) { func_002A7750((u8 *)self, 13, -1); break; }
        }
        break;
    case 13:
        if (func_002B3868((u8 *)self)) {
            animation = func_L02_003CCFE8(self, state + 0x350) ? 18 : 17;
            if (*(u16 *)(self + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)self)[0x43] != animation) func_002A7470(self, animation, 0, 10);
        }
        angle = func_00283248(*(float *)(state + 0x350) - *(float *)(self + 0x10), *(float *)(state + 0x354) - *(float *)(self + 0x14));
        if ((func_L02_00331440(self, state + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(self + 0x96) > 120 || *(int *)(state + 0x180) >= 21) { func_002A7750((u8 *)self, 10, -1); break; }
        break;
    case 11:
        if (func_002B3868((u8 *)self)) {
            if (((u8 *)self)[0x43] != 10) func_002A7470(self, 10, 0, 10);
            *(short *)(state + 0x380) = func_002A7820(3, 5); func_L02_003CD4A8((struct L02GroupObject *)self);
            qcopy(state + 0x360,state + 0x1F0); *(float *)(state + 0x368) += 0.5f;
        }
        func_L02_003CCEA0(self);
        if ((D_L15_001B2148[0] & 15) == (((int)self >> 8) & 15))
 func_L02_003CD4A8((struct L02GroupObject *)self);
        if (func_US2_002AF9C8(self, 5)) {
            func_0029FCC0(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
            func_00282CF0(&work.aim.velocity, state + 0x360, &work.aim.muzzle); func_00282F20(&work.aim.velocity, &work.aim.velocity, 0.23333334922790527f);
            func_00282D30(&work.aim.acceleration, &work.aim.velocity, 0.25f);
            power = (float)(u8)state[0x34];
            if (*(short *)(state + 0x380) >= 2)
                func_L02_00401530(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, power, power, 0.0055555556900799274f, 10, 30, 1);
            else
                func_L02_00401530(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, power, power, 0.0055555556900799274f, 30, 80, 1);
            break;
        }
        if (!(((u8 *)self)[0x60] & 2)) break;
        func_0029FCC0(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
        collision = func_002761F8(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)D_00189E20)->target_d0, 0, self, 0);
        if (func_00282978((short *)(state + 0x380)) || (collision && D_L15_001BFC00.hit != ((L02_ResidentCombatPrefix *)D_00189E20)->pointer_2290)) {
            *(short *)(state + 0x378) += 15; { if (!func_002A77E0(3)) func_002A7750((u8 *)self, 12, -1); else func_002A7750((u8 *)self, 13, -1); break; }
        } else {
            angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
            if (func_00283C80(*(float *)(self + 0xF8), angle) > 0.52359885f) { func_002A7750((u8 *)self, 9, -1); break; }
            else if (((L02_ResidentCombatPrefix *)D_00189E20)->mode_229c == 7 && ((L02_ResidentCombatPrefix *)D_00189E20)->pointer_249c && *(short *)(((L02_ResidentCombatPrefix *)D_00189E20)->pointer_249c + 0xAA) == 0xB5A) { func_002A7750((u8 *)self, 12, -1); break; }
        }
        break;
    case 14:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 13) func_002A7470(self, 13, 0, 10);
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        func_L01_00322288((int)self, angle); time = func_0029F530(self);
        if (time >= 11 && time < 12.5f) func_002A8D70(0.6f, (float)(u8)state[0x35], 3.0f, self, (void *)3, 1, 0, 1, 0);
        if (((u8 *)self)[0x60] & 2) { func_002A7750((u8 *)self, 15, -1); break; }
        break;
    case 15:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 11) func_002A7470(self, 11, 10, 10);
        func_L02_003CCEA0(self); if (!(((u8 *)self)[0x60] & 2)) break;
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (func_00283C80(*(float *)(self + 0xF8), angle) > 0.52359885f) func_002A7750((u8 *)self, 9, -1); else func_002A7750((u8 *)self, 11, -1);
        break;
    case 12:
        if (func_002B3868((u8 *)self)) {
            if (((L02_ResidentCombatPrefix *)D_00189E20)->mode_229c == 7) { if (((u8 *)self)[0x43] != 12) func_002A7470(self, 12, 0, 20); }
            else if (((u8 *)self)[0x43] != 11) func_002A7470(self, 11, 0, 20);
        }

        func_L02_003CCEA0(self); if (((u8 *)self)[0x60] & 2) { func_002A7750((u8 *)self, 10, -1); break; }
        break;
    case 16:
        if (!(*(float *)(state + 0x20) > 0)) {

            if (func_002B3868((u8 *)self)) { *(short *)(state + 0x378) = func_002A7820(10, 15); *(short *)(state + 0x384) = func_002A77E0(3) == 0; }
            if (*(short *)(state + 0x384) && func_00282978((short *)(state + 0x378))) {
                func_0029FC20(*(char **)(state + 0x370), 0, (char *)work.aim.transform);
                func_00282F20(&work.aim.muzzle, work.aim.transform, 0.23333334922790527f);
                func_00282CF0(&work.aim.velocity, D_00189E20 + 0xE0, &work.aim.transform[3]); func_00282F20(&work.aim.velocity, &work.aim.velocity, 1);
                if (func_00282DB0(&work.aim.velocity, work.aim.transform) < 0.2f) {
                func_L02_00401530(&work.aim.transform[3], &work.aim.muzzle, &work.aim.muzzle, 1.0f, 0.0f, 1.0f, 30, 80, 1);
                    *(short *)(state + 0x378) = func_002A7820(15, 30);
                }
            }
        }
        break;
    case 17:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43]) func_002A7470(self, 0, 0, 20);
        if (func_002ACBC8(&((L02_ResidentCombatPrefix *)D_00189E20)->position_80, *(int *)(state + 0x324)) || *(int *)(state + 0x204) == 1) { func_002A7750((u8 *)self, 18, -1); break; }
        break;
    case 18:
        path = D_L15_001FE480[*(int *)(state + 0x320)];
        if (func_002B3868((u8 *)self)) { if (((u8 *)self)[0x43] != 6) func_002A7470(self, 6, 0, 20); func_002B6318((u8 *)self); }
        if (!(func_00282E80(self + 0x10, path + *(int *)path * 16) < *(float *)(state + 0x134)) && !func_002B6120(self, path)) break;

        if (((u8 *)self)[0x43] != 2) {
            angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
            if (func_00283C80(*(float *)(self + 0xF8), angle > 0.3490659f ? 1.0f : 0.0f) != 0 && ((u8 *)self)[0x43] != 2) func_002A7470(self, 2, 5, 10);
        }
        func_L02_00332630(self, state + 0x1F0);
        angle = func_00283248(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (func_00283C80(*(float *)(self + 0xF8), angle) < 0.087266475f && (((u8 *)self)[0x43] != 2 || (((u8 *)self)[0x60] & 2))) {
            *(int *)(state + 0x320) = -1; qcopy(state + 0x340,self + 0x10);
            if (*(int *)(state + 0x328) != -1) func_002A7750((u8 *)self, 19, 4); else func_002A7750((u8 *)self, 1, 0);

        }
        break;
    case 22:
        if (func_002B3868((u8 *)self)) { if (((u8 *)self)[0x43] != 6) func_002A7470(self, 6, 0, 20); func_002B6318((u8 *)self); }
        if (func_L01_00321178(self, state + 0x340) & 0x80) { func_002A7750((u8 *)self, 1, 0); qcopy(state + 0x340,self + 0x10); }
        break;
    case 19:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43]) func_002A7470(self, 0, 0, 20);
        if (*(int *)(state + 0x32C) == -1 || func_002ACBC8(&((L02_ResidentCombatPrefix *)D_00189E20)->position_80, *(int *)(state + 0x32C)) || *(int *)(state + 0x204) == 1) { func_002A7750((u8 *)self, 20, -1); break; }
        break;
    case 20:
        if (func_002B3868((u8 *)self)) {
            if (((u8 *)self)[0x43] != 9) func_002A7470(self, 9, 0, 20);
            if (*(float *)(state + 0x37C) == 0) *(float *)(state + 0x37C) = func_002A77E0(2) ? 0.3490659f : -0.3490659f;
            else *(float *)(state + 0x37C) = -*(float *)(state + 0x37C);
        }
        *(float *)(state + 0x278) = *(float *)(state + 0x37C);
        if (*(u16 *)(self + 0x96) < 11) break;
        if (func_L02_003CEBB8(*(int *)(state + 0x328))) func_002A7750((u8 *)self, 21, -1); else func_002A7750((u8 *)self, 3, 1);
        break;
    case 21:
        if (func_002B3868((u8 *)self) && ((u8 *)self)[0x43] != 10) func_002A7470(self, 10, 0, 10);
        *(float *)(state + 0x278) = *(float *)(state + 0x37C);
        if (func_US2_002AF9C8(self, 5)) {
            if ((other = (char *)func_L02_003CEBB8(*(int *)(state + 0x328))) != 0) {
                func_0029FC20(*(char **)(state + 0x370), 0, (char *)work.relay.frame);
                func_00282F20(&work.relay.direction, work.relay.frame, 0.23333334922790527f);
                {
                    Quad q = *(Quad *)&work.relay.frame[3];
                    *(Quad *)&work.relay.origin = q;
                }
                func_L02_003CED70(other, &work.relay.origin, &work.relay.direction);
            }
        } else if (((u8 *)self)[0x60] & 2) func_002A7750((u8 *)self, 20, -1);

        break;
    }
    func_L02_003CCCC8(self);
}
