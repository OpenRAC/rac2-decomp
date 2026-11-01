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

INCLUDE_ASM("asm/game", func_002A0488);

INCLUDE_ASM("asm/game", func_002A04B8);

ASM_FUNC("asm/game", func_002A04E8);

INCLUDE_ASM("asm/game", func_002A0558);

INCLUDE_ASM("asm/game", func_002A05A8);

INCLUDE_ASM("asm/game", func_002A08A0);

INCLUDE_ASM("asm/game", func_002A0A28);

ASM_FUNC("asm/game", func_002A0B88);

ASM_FUNC("asm/game", func_002A0BE8);

ASM_FUNC("asm/game", func_002A0C68);

INCLUDE_ASM("asm/game", func_002A0F48);

INCLUDE_ASM("asm/game", func_002A10E8);

INCLUDE_ASM("asm/game", func_002A1130);

INCLUDE_ASM("asm/game", func_002A1378);

INCLUDE_ASM("asm/game", func_002A1490);

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



INCLUDE_ASM("asm/game", func_002A6C58);


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
