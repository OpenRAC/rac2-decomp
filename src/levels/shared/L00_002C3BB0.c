#include "include_asm.h"
#include "names.h"
typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x80]; float position[4];
    unsigned char pad1[8]; float heading;
    unsigned char pad2[0x64C - 0x9C]; float alternate_heading;
    unsigned char pad3[0xAA4 - 0x650]; void *selected_aa4; int ready_aa8;
    unsigned char pad4[12]; int value_ab8;
    unsigned char pad5[4]; int value_ac0; float score_ac4;
    unsigned char pad6[8]; void *selected_ad0;
    unsigned char pad7[4]; float score_ad8;
    unsigned char pad8[2]; short ready_ade;
    unsigned char pad9[0xB10 - 0xAE0]; void *selected_b10; int ready_b14;
    unsigned char pad10[0x2294 - 0xB18]; int mode, field_2298, state;
} HeroSelectionState;
extern HeroSelectionState D_00189E20;

extern unsigned char *D_L00_001B1EA8 __attribute__((sda));
extern float func_L00_002AE388(void *, int *, float, float, float, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_002ACBC8(void *, int);
extern int func_002761F8(void *, void *, int, void *, int);

/* Finds the nearest Swingshot Node in front of the hero and notes whether the hero can grab it. */
void func_L00_002C3BB0(void)
{
    unsigned char *node = D_L00_001B1EA8;
    unsigned char *best = 0;
    float closest = 100000000.0f;
    float first[4], second[4];
    int blocked[4];
    gHeroState.ready_ade = 0;
    for (; node; node = *(unsigned char **)(node + 0x28)) {
        char *data;
        float horizontal, vertical, range, score, heading;
        if (*(short *)(node + 0xAA) != 0x323 /* Swingshot Node */) continue;
        data = *(char **)(node + 0x68);
        if (*(unsigned short *)(node + 0x34) & 1) continue;
        if (3.0f < gHeroState.position[2] - *(float *)(node + 0x18)) continue;
        if (*(float *)(data + 0x20) != 0.0f &&
            *(float *)(data + 0x20) < fast_vec_dist(gHeroState.position, node + 0x10)) continue;
        horizontal = 0.785398244857788086f;
        if (gHeroState.mode == 0x2C) horizontal = 1.221730589866638184f;
        vertical = 0.785398244857788086f;
        if (gHeroState.mode == 0x2C) vertical = 1.134464144706726074f;
        if (gHeroState.mode == 1 || gHeroState.mode == 0x1D)
            horizontal = vertical = 0.087266474962234497f;
        heading = gHeroState.heading;
        range = 16.0f;
        if (*(float *)(data + 0x20) != 0.0f) range = *(float *)(data + 0x20);
        score = ScoreTargetByHeading(node, blocked, heading, range, horizontal, vertical);
        if (blocked[0] != 0) continue;
        if ((unsigned char)node[0x31] == 0) score += 10.0f;
        if (*(int *)(data + 0x1C) >= 0 && IsPointInCuboid(gHeroState.position, *(int *)(data + 0x1C))) continue;
        if (score < closest) { closest = score; best = node; }
    }
    gHeroState.selected_ad0 = best;
    if (best) {
        *(Vector *)first = *(Vector *)gHeroState.position;
        first[2] += 0.5f;
        *(Vector *)second = *(Vector *)(best + 0x10);
        if (!CollLine(first, second, 2, 0, 0)) {
            gHeroState.ready_ade = 1;
            gHeroState.score_ad8 = closest;
        }
    }
}
