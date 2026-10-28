/* func_00325158 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G0 -ffunction-sections.
 * Measured in src/game/00325158.c: 448/456 bytes.
 * US: 0/7 local places; PAL: ABSENT; US2: 0/7 local places.
 * No strict linked build was run because no local placement matched.
 * The effect pointer live ranges, saved registers and frame differ; the 0.01745329424738884f word is retained. Callees were checked against current source or retail. Reopen with effect-pointer lifetime evidence.
 */

#include "common.h"

extern float func_00283B98(float, float);
extern void func_00325C50(float, char *, char **, int, void *);
extern void func_002AB8C0(void *, unsigned char *);
extern int func_00282978(void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_0027CFD0(void (*)(int), int);
extern void func_00325430(int);
extern void func_00325DA0(void *, void *);
extern void func_002B0990(void *, float *, float, int, int);
extern char ref_L00_003DA068_00[];

void func_00325158(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *effect;
    float angle;
    float step;
    float blend;
    if (*(unsigned char *)(object + 0x95) && *(unsigned char *)(object + 0x20) != 3) {
        angle = *(float *)(state + 0x2AC);
        if (*(unsigned char *)(object + 0x95) != 5 && !*(int *)(state + 0x2C4)) {
            angle = func_00283B98(angle, *(float *)(state + 0x2E8) * 0.01745329424738884f);
            *(float *)(state + 0x2AC) = angle;
            func_00325C50(angle, object, (char **)(state + 0x2A0), 1, ref_L00_003DA068_00);
            goto update;
        }
    }
    func_00325C50(*(float *)(state + 0x2AC), object, (char **)(state + 0x2A0), 0, ref_L00_003DA068_00);
update:
    func_002AB8C0(object, (unsigned char *)state + 0x50);
    step = 0.03f;
    blend = 0.3f;
    func_00282978(state + 0x270);
    effect = state + 0x530;
    func_00282978(state + 0x272);
    func_00282978(state + 0x26);
    func_002AEC48(object, effect, 7, step, blend);
    func_002AEC48(object, state + 0x5B0, 8, step, blend);
    if (*(unsigned short *)(object + 0x96) < 0xFFFFu) ++*(unsigned short *)(object + 0x96);
    if ((unsigned int)(*(unsigned char *)(object + 0x20) - 4) < 2 || *(unsigned char *)(object + 0x95) == 2 || *(unsigned char *)(object + 0x20) == 10)
        func_0027CFD0(func_00325430, (int)object);
    func_00325DA0(object, state + 0x2FC);
    func_002B0990(object, (float *)effect, 2.5f, 7, 1);
}