#include "include_asm.h"
#include "common.h"

extern int ref_L00_00312060_01;

extern unsigned char ref_L00_00312060_00[];

void func_002A0430(unsigned int index)
{
    if (index != 255u)
        ref_L00_00312060_00[index + (unsigned int)ref_L00_00312060_01 * 16u] |= 0x80u;
}

void func_002A0468(unsigned long long *command_words, unsigned long long upper_field, unsigned long long middle_field, unsigned long long low_field, unsigned long long tail_field);

/* rac1-decomp src/game/mobyfunc.c: func_0020E340 */
/* Adapted from Lombyte (MIT) for PAL by OpenRAC's tools/port.py: src/rendering/commands/pack_render_command_fields.c, PackRenderCommandFields. */
void func_002A0468(unsigned long long *command_words, unsigned long long upper_field,
                             unsigned long long middle_field, unsigned long long low_field, unsigned long long tail_field) {
    int command_word_index;
    if (middle_field) {
        upper_field <<= 32;
        low_field <<= 8;
        tail_field <<= 16;
    } else {
        upper_field <<= 32;
        low_field <<= 8;
        tail_field <<= 16;
    }
    {
        register unsigned long long packed_command;
        packed_command = upper_field | middle_field;
        packed_command |= low_field;
        packed_command |= tail_field;
        command_word_index = 7;
        command_words[command_word_index] = packed_command;
    }
}

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251328. */
ASM_FUNC("asm/game", func_002A0488);

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251358. */
ASM_FUNC("asm/game", func_002A04B8);

ASM_FUNC("asm/game", func_002A04E8);

/* Original assembly: RAC1 overlays/shared/moby_frame_packet.c, func_L00_00251468. */
ASM_FUNC("asm/game", func_002A0558);

/* Original assembly: 29 trapping add/addi/sub/dsub, $at as a working register, and two cvt.w.s
   words in an encoding the compiler never emits. */
ASM_FUNC("asm/game", func_002A05A8);

INCLUDE_ASM("asm/game", func_002A08A0);

INCLUDE_ASM("asm/game", func_002A0A28);

ASM_FUNC("asm/game", func_002A0B88);

ASM_FUNC("asm/game", func_002A0BE8);

ASM_FUNC("asm/game", func_002A0C68);

/* Original assembly: VU0 macro instructions (lqc2/sqc2, vmula/vmadd, vcallms, qmtc2/qmfc2),
   trapping addi/add and $at as a working register. */
ASM_FUNC("asm/game", func_002A0F48);

INCLUDE_ASM("asm/game", func_002A10E8);

INCLUDE_ASM("asm/game", func_002A1130);

INCLUDE_ASM("asm/game", func_002A1378);

/* Original assembly: 32 trapping add/addi/sub, $at as a working register, and no return:
   it leaves by jumps, like func_002A1130. */
ASM_FUNC("asm/game", func_002A1490);

ASM_FUNC("asm/game", func_002A1738);

ASM_FUNC("asm/game", func_002A2450);

ASM_FUNC("asm/game", func_002A3110);

ASM_FUNC("asm/game", func_002A3DB8);

ASM_FUNC("asm/game", func_002A3F10);

ASM_FUNC("asm/game", func_002A4078);

ASM_FUNC("asm/game", func_002A4AD8);

ASM_FUNC("asm/game", func_002A4D88);

ASM_FUNC("asm/game", func_002A4E68);

ASM_FUNC("asm/game", func_002A6640);

INCLUDE_ASM("asm/game", func_002A677C);



typedef struct {
    unsigned char pad00[0x46];
    short kind;
} RewardClass;
typedef struct {
    unsigned char pad00[0x10];
    float position[4];
    unsigned char pad20[4];
    RewardClass *mclass;
    unsigned char pad28[0x57];
    unsigned char kills;
    unsigned char pad80[0x30];
    unsigned char owner, flags;
    short id, bolts;
    unsigned short count;
} RewardMoby;
extern int D_001A9E70 __attribute__((sda));
extern int D_001A79F0;
extern short D_001A86E6 __attribute__((sda));
extern RewardMoby *D_001B1D30[2];
typedef struct { unsigned char pad[0x80]; float position[4]; unsigned char pad90[0x2204]; int state; unsigned char pad2298[0x1C]; unsigned char mode; unsigned char pad22B5[13]; unsigned char option; } PlayerReward;
extern PlayerReward D_00189E20;
typedef struct { unsigned char pad[12]; int earned, reserve, extra; unsigned char pad18[26]; unsigned char multiplier; } RewardState;
extern RewardState D_001A7A00 MACRO_ADDR;
extern int D_00188610[];
extern short D_001A86C0[] MACRO_ADDR, D_001A8698[] MACRO_ADDR;
extern unsigned char D_0019B4A8[];
extern char D_001A9E78[];
extern char D_001A8690[] MACRO_ADDR, D_001A8688[] MACRO_ADDR, D_001A8680[] MACRO_ADDR, D_001A8678[] MACRO_ADDR;
extern int D_001F1B78[][56], D_00139868[];
extern short D_001A86E8;
typedef struct { u8 prefix[0x464]; u8 collected[0]; } BoltCollectionTable;
extern BoltCollectionTable D_00210D40, D_002119B0;
extern unsigned char D_001B19A0[] MACRO_ADDR, D_0019B2E8[] MACRO_ADDR;
extern int D_001B1A80;
extern void func_002A6AE0(RewardMoby *, int);
extern int func_0026FEB8(char *, int, int, int);
extern int func_00279B70(char *, int, int);
extern char *func_002AB1F0(RewardMoby *);
extern void func_0029B720(int);
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern void func_002ADB78(RewardMoby *, int, int, int, int, int, float);

void func_002A6C58(RewardMoby *p, int flags, int arg)
{
    int multiplier;
    int slot, bonus, reward, extra, i, j, total;
    unsigned short count;
    char *info;
    float bolts;
    int dropflags;
    if (p->id < 0 || (p->flags & 0x80)) return;
    p->kills++;
    multiplier = 1;
    if (p->mclass && p->mclass->kind == 5) {
        if (D_001A7A00.multiplier) multiplier = D_001A7A00.multiplier;
        func_002A6AE0(p, 0);
    }
    count = p->count;
    for (slot = 1; slot >= 0; slot--) if (p == D_001B1D30[slot]) break;
    if ((count || D_001A9E70 != -1) && (unsigned)(D_00189E20.mode - 1) >= 2) {
        bonus = (D_001A7A00.reserve + 49) / 50;
        if (D_001A9E70 != -1 && slot < 0) {
            unsigned short base = D_001A86C0[D_001A9E70];
            reward = (short)base;
            if (D_00188610[D_001A9E70] * 2 > D_001A8698[D_001A9E70])
                reward = (short)base * D_001A8698[D_001A9E70] / (D_00188610[D_001A9E70] * 2);
            if (!reward) reward = 1;
            func_0026FEB8(D_001A9E78, D_001A9E70, (short)base, reward);
        } else {
            int n = D_0019B4A8[(p->id >> 1) + (D_001A79F0 << 10)];
            if (((unsigned short)p->id & 1) ? (n >> 4) & 8 : n & 8) reward = func_00279B70(D_001A8690, (short)count, p->id);
            else reward = func_00279B70(D_001A8688, (short)count, p->id);
        }
        info = func_002AB1F0(p);
        if (info && (unsigned char)info[0x17] != 255) {
            if (slot >= 0) {
                total = 0;
                for (i = 0; i < 56; i++) total += D_001F1B78[slot][i];
                if (total) {
                    for (j = 0; j < 56; j++) D_00139868[j] += D_001F1B78[slot][j] * (reward + bonus) / total;
                }
                D_001B1D30[slot] = 0;
            } else D_00139868[(unsigned char)info[0x17]] += reward + bonus;
        }
        D_001A7A00.reserve -= bonus;
        D_001A7A00.earned += reward + bonus;
        func_0029B720(720);
    }
    extra = (D_001A7A00.extra + 49) / 50;
    D_001A7A00.extra -= extra;
    if (D_001A9E70 != -1) {
        int base;
        if (D_001A79F0 == 2) base = D_001A86E8;
        else base = D_001A86E6;
        bolts = base;
        if (slot >= 0) bolts *= 10.0f;
    } else {
        int n = D_0019B4A8[(p->id >> 1) + (D_001A79F0 << 10)];
        if (((unsigned short)p->id & 1) ? (n >> 4) & 8 : n & 8) bolts = func_00279B70(D_001A8680, p->bolts, p->id);
        else bolts = func_00279B70(D_001A8678, p->bolts, p->id);
    }
    if (p->id >= 0 && !(p->flags & 0x80)) {
        unsigned short id;
        if (D_001A9E70 != -1) D_00188610[D_001A9E70]++;
        id = (unsigned short)p->id;
        if (id & 1) {
            unsigned char *bits = D_0019B4A8 + (((short)id >> 1) + (D_001A79F0 << 10));
            if (((*bits >> 4) & 7) != 7) *bits += 16;
        } else {
            unsigned char *bits = D_0019B4A8 + (((short)id >> 1) + (D_001A79F0 << 10));
            if ((*bits & 7) != 7) *bits += 1;
        }
        D_00210D40.collected[p->id] = p->owner + 2;
        {
            int k = p->owner;
            if (k == 255 || (!(D_001B19A0[k & 0xFF] & 0x80) && (D_0019B2E8[(k & 0xFF) + (D_001A79F0 << 4)] & 0x80)))
                D_002119B0.collected[p->id] = k + 2;
        }
    }
    if (D_001A9E70 == -1) bolts *= multiplier;
    bolts += extra;
    dropflags = flags & 0x100 ? 5 : 1;
    if (D_00189E20.option || (flags & 0x200)) dropflags |= 2;
    if (D_00189E20.state == 16 && func_00282E48(D_00189E20.position, p->position) < 4.0f) dropflags |= 2;
    if (flags & 0x400) dropflags |= 0x10;
    dropflags |= 8;
    if (D_001B1A80 <= 99) dropflags |= 2;
    if (bolts < 0.0f) bolts = 0.0f;
    if (bolts > 0.0f) {
        int spread = 0;
        if (bolts >= 8.0f) spread = func_00283CF0(bolts * 0.25f);
        else if (bolts >= 2.0f) spread = 1;
        {
            int n = func_00283CF0(bolts);
            int hi = n + spread;
            n -= spread;
            func_002ADB78(p, n, hi, dropflags, -1, arg, 0.0f);
        }
    }
}


typedef int TI128_002A7470 __attribute__((mode(TI)));

typedef struct {
    char pad[0x48];
    unsigned char *anims[1];
} Model_002A7470;

extern void func_002A7398(unsigned char *, int, int);
extern int func_0029FA88(void *);
extern void func_002A2450(void *, int);
extern void func_0029F390(void *);
extern float func_00283CE0(int);
extern TI128_002A7470 ref_L00_002A7470_00[];

void func_002A7470(unsigned char *object, int animation, int frame, int rate)
{
    int count;
    int slot;
    float reciprocal;

    count = (*(Model_002A7470 **)(object + 0x24))->anims[animation][0x10];
    if (frame >= count)
        frame = count - 1;

    if (rate <= 0) {
        func_002A7398(object, animation, frame);
        return;
    }

    if (0.025f < *(float *)(object + 0x44) ||
        *(unsigned int *)(object + 0x50) != 0 ||
        *(unsigned int *)(object + 0x54) != 0) {
        slot = func_0029FA88(object);
        if (slot >= 0) {
            func_002A2450(object, slot | 0x300);
            qcopy(&ref_L00_002A7470_00[slot], object + 0x80);
            if (object[0x42] != 0xFF)
                object[0xA9] = object[0x42];
            object[0x42] = 0xFF;
            object[0x40] = slot;
        }
    }

    object[0x41] = frame;
    object[0x43] = animation;
    func_0029F390(object);
    *(float *)(object + 0x48) = 1.0f;
    reciprocal = 1.0f / func_00283CE0(rate);
    *(unsigned int *)(object + 0x44) = 0;
    object[0x60] &= 0xFD;
    *(float *)(object + 0x4C) = reciprocal;
    object[0x6C] = (*(Model_002A7470 **)(object + 0x24))->anims[animation][0x11];
}

typedef struct {
    unsigned char pad0[0x8E];
    unsigned short count;
    unsigned char pad90[0x50];
} Class_2A68A8;

extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_00139568[];
extern int D_00139688[];
extern Class_2A68A8 D_00239BA0[];
extern int func_002A77E0(int);

int func_002A68A8(int unused, int *out)
{
    int i;
    int j;
    int k;
    int sum = 0;
    int total = 0;
    int pick;
    Class_2A68A8 *cls;

    for (i = 0; i < 0x38; i++) {
        if (D_001A7AF8[i] != 0) {
            cls = &D_00239BA0[D_00139568[i]];
            if (cls->count != 0 && i != 0x1F && i != 0x3D && i != 0x2D && i != 0x4D) {
                total++;
                if (D_00139688[i] < cls->count)
                    sum++;
            }
        }
    }
    if (sum != 0) {
        pick = func_002A77E0(sum);
        for (j = 0; j < 0x38; j++) {
            if (D_001A7AF8[j] != 0) {
                cls = &D_00239BA0[D_00139568[j]];
                if (cls->count != 0 && D_00139688[j] < cls->count && j != 0x1F && j != 0x3D) {
                    if (pick == 0) {
                        *out = j;
                        break;
                    }
                    pick--;
                }
            }
        }
    } else {
        pick = func_002A77E0(total);
        for (k = 0; k < 0x38; k++) {
            if (D_001A7AF8[k] != 0) {
                cls = &D_00239BA0[D_00139568[k]];
                if (cls->count != 0 && k != 0x1F && k != 0x3D && k != 0x2D && k != 0x4D) {
                    if (pick == 0) {
                        *out = k;
                        break;
                    }
                    pick--;
                }
            }
        }
    }
    {
        int roll = func_002A77E0(5);
        int one;
        int result = 2;
        one = 1;
        if (roll != 0) result = one;
        return result;
    }
}
