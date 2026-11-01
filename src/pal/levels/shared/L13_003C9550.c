#include "include_asm.h"

#include "common.h"
extern char D_00189E20[];
extern unsigned char D_001A7A40[] __attribute__((sda));
extern int func_00283CF0(float);
extern float func_00283198(float);
extern void func_002A7750(char *, int, int);
extern int func_002ACBC8(void *, int);
extern int func_002B3868(char *);
extern void func_L00_00429020(int);
extern int func_002B0CE0(int, int, int);
extern int func_PAL_L13_002CF0A0(int, int);
extern float func_00283B98(float, float);

/* State 0 opens the trigger; state 1 reacts to the hero being on the object, or being in state
 * 0x82 inside its cuboid. Then pulses the object's colour, in the channel the flag selects. */
void func_PAL_L13_003C9550(char *obj)
{
    char *rig = *(char **)(obj + 0x68);
    char *hero, *other;
    int word, level, glow;
    float turn, pulse;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(unsigned short *)(obj + 0x34) |= 0x10;
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (func_002B3868(obj) != 0) {
            word = *(int *)rig;
            if (word != -1) {
                func_L00_00429020(word);
                *(int *)rig = -1;
            }
        }
        hero = D_00189E20;
        if (*(char **)(hero + 0x33C) == obj && *(int *)(hero + 0x340) != 0) {
            if (D_001A7A40[0xC0] != 0) {
                func_002B0CE0(0xC, 0x1349, 1);
                *(short *)(hero + 0x1F2) = 0x8;
                turn = *(float *)(rig + 0xC);
                if (turn != 0.0f)
                    *(float *)(hero + 0x5B8) = turn;
            }
        } else {
            other = D_00189E20;
            if (*(int *)(other + 0x2294) == 0x82) {
                level = *(int *)(rig + 8);
                if (level >= 0 && func_002ACBC8(other + 0x80, level) != 0)
                    func_PAL_L13_002CF0A0(6, 1);
            }
        }
        break;
    }
    if (*(unsigned char *)(obj + 0x31) != 0) {
        pulse = func_00283B98(*(float *)(rig + 4), 0.12566373f);
        *(float *)(rig + 4) = pulse;
        glow = func_00283CF0(func_00283198(pulse) * 128.0f);
        if (glow > 0x80)
            glow = 0x80;
        else if (glow < 0x20)
            glow = 0x20;
        if (D_001A7A40[0xC0] != 0)
            *(int *)(obj + 0x78) = (glow << 8) | 0x80000000;
        else
            *(int *)(obj + 0x78) = glow | 0x80000000;
    }
}

