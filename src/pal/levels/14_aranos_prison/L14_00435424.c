#include "include_asm.h"


#include "common.h"
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern char D_00189EA0[];
extern char D_L14_001A8F20[] __attribute__((sda));
extern char *D_L14_001B259C_gp SDATA(D_L14_001B259C);
extern char *D_L14_001B259C_direct __asm__("D_L14_001B259C") __attribute__((sda));
extern int func_002A8508(int, int);
extern float func_00282E80(void *, void *);
extern int func_002B38B8(void *);
extern int func_002ACBC8(void *, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_00277258(void *, float, int, void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_0029F338(void *);
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern u8 D_0019B2E8[];
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_00189EA0[];
extern u8 D_00189E20[];
extern u8 D_001395E1;
extern int func_002ACBC8(void *, int);
extern void func_0029F338(void *);
extern float func_00283198(float);
extern unsigned char *D_L14_001FB060[];
typedef struct {
    int linked[4];
    int f10;
    int f14;
    int f18;
    int group;
} PrisonGateState;
typedef struct {
    char pad00[0x10];
    float pos[4];
    u8 mode;
    char pad21[3];
    int *next;
    char pad28[0xC];
    u16 flags;
    char pad36[0xD];
    u8 anim;
    char pad44[0x1C];
    u8 animFlags;
    char pad61[7];
    PrisonGateState *state;
    char pad6C[0xC];
    int f78;
    char pad7C[0x19];
    u8 f95;
    char pad96[2];
    int f98;
    char pad9C[0x5C];
    float angle;
    char padFC[4];
} PrisonEntity;

/* Gate logic: opens when the player nears, is hit open by linked objects, and
   hands off to the next object when it slides clear. */
void func_PAL_L14_004356C0(PrisonEntity *self)
{
    float temp[4] __attribute__((aligned(16)));
    float front[4] __attribute__((aligned(16)));
    float left[4] __attribute__((aligned(16)));
    float right[4] __attribute__((aligned(16)));
    /* Passed unwritten to the left/right additions below, as retail does; the matching code needs that. */
    float offset1[4] __attribute__((aligned(16)));
    float offset2[4] __attribute__((aligned(16)));
    PrisonGateState *state = self->state;
    int i;
    int entry;
    int group;
    PrisonEntity *other;
    char *base;

    if (self->mode == 0) {
        /* Mark the group's members busy. */
        if (D_L14_001FB060[group = state->group] && func_002A8508(group, -1) >= 2) {
            unsigned short *list;

            list = (unsigned short *)D_L14_001FB060[state->group];
            base = D_L14_001B259C_direct;
            do {
                entry = *list;
                other = (PrisonEntity *)(base + ((entry & 0x7FFF) << 8));
                other->flags |= 0x43;
            } while ((group = (short)*list++) >= 0);
        }

        if (func_00282E80(&self->pos, D_00189EA0) < 6.0f && func_002B38B8(self) &&
            !func_002ACBC8(D_00189EA0, state->f14) &&
            !func_002ACBC8(D_00189EA0, state->f18)) {
            self->mode = 1;
            self->f78 = 0x24C102;
            if (self->anim != 1)
                func_PAL_002A7E68(self, 1, 0, 0);
            self->f98 = 0;

            /* Release the group's members. */
            if (D_L14_001FB060[group = state->group] && func_002A8508(group, -1) >= 2) {
                unsigned short *list;

                list = (unsigned short *)D_L14_001FB060[state->group];
                base = D_L14_001B259C_direct;
                do {
                    entry = *list;
                    other = (PrisonEntity *)(base + ((entry & 0x7FFF) << 8));
                    other->flags &= 0xFFBC;
                } while ((group = (short)*list++) >= 0);
            }
        } else if (func_002ACBC8(D_00189EA0, state->f14)) {
            self->mode = 5;
        }

        for (i = 0; i < 4; i++) {
            int id = state->linked[i];

            if (id != -1) {
                other = (PrisonEntity *)(D_L14_001B259C_gp + (id << 8));
                if (other->f95 || (s8)other->mode < 0) {
                    if (state->f10) {
                        self->mode = 2;
                        qcopy(temp, self->pos);
                        temp[2] += 1.0f;
                        prisonStartSound(2, 0, self);
                        func_PAL_002AC718(self, D_L14_001A8F20, temp, 0.0f, 0.0f, 10, 3, 16,
                            4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
                        return;
                    }
                    self->mode = 1;
                    if (self->anim != 1)
                        func_PAL_002A7E68(self, 1, 0, 0);
                    self->f98 = 0;
                }
            }
        }
    }

    if (self->mode == 1 && (self->animFlags & 2)) {
        self->mode = 3;
        self->f78 = 0x224C1;
        if (self->anim != 2)
            func_PAL_002A7E68(self, 2, 0, 0);
    }

    if (self->mode == 2) {
        temp[0] = func_00283180(self->angle - 1.57079649f) * 0.36f;
        temp[1] = func_00283198(self->angle - 1.57079649f) * 0.36f;
        temp[2] = 0;
        func_00282CC0(self->pos, self->pos, temp);
        qcopy(front, self->pos);
        qcopy(left, self->pos);
        qcopy(right, self->pos);
        front[2] += 0.75f;
        left[2] += 0.75f;
        right[2] += 0.75f;
        temp[0] = func_00283180(self->angle) * 0.8f;
        temp[1] = func_00283198(self->angle) * 0.8f;
        temp[2] = 0;
        temp[0] = func_00283180(self->angle + 3.14159298f) * 0.8f;
        temp[1] = func_00283198(self->angle + 3.14159298f) * 0.8f;
        temp[2] = 0;
        func_00282CC0(left, left, offset1);
        func_00282CC0(right, right, offset2);
        if (func_00277258(front, 0.6f, 0, self) || func_00277258(left, 0.68f, 0, self) || func_00277258(right, 0.68f, 0, self)) {
            prisonStartSound(2, 0, self);
            func_PAL_002AC718(self, D_L14_001A8F20, front, 0.0f, 0.0f, 10, 3, 16,
                4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
            func_0029F338(self);
            return;
        }
    }

    if (self->mode == 3 && func_002ACBC8(D_00189EA0, state->f14)) {
        self->mode = 4;
        if (self->anim != 3)
            func_PAL_002A7E68(self, 3, 0, 0);
    }

    if (self->mode == 4 && (self->animFlags & 2)) {
        self->mode = 5;
        self->f98 = self->next[4];
        if (self->anim)
            func_PAL_002A7E68(self, 0, 0, 0);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L14_00435D28);
