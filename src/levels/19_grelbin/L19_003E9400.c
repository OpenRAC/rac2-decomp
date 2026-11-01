#include "include_asm.h"
#include "common.h"

/* func_L19_003E9400 is defined in L19_003E9400-controller.c. */

/* func_L19_00411890 is defined in L19_00411890-g8.c. */

/* func_L19_00411EF0 is defined in L19_00411EF0-g8.c. */

INCLUDE_ASM("asm/levels", func_L19_00412140);

/* func_L19_004160A0 is defined in L19_004160A0-g8.c. */

/* func_L19_004170D8 is defined in L19_004170D8-g8.c. */

extern void func_2EB590();

extern void func_2EB5C0();

extern float func_3183D8(float, float);

extern float func_2EBF18(float);

extern float func_2EBF30(float);

void func_L19_00417A00(char *a0)
{
    int obj = *(int *)(a0 + 0x68);

    func_2EB590(obj + 0x218);
    func_2EB5C0(obj + 0x21C);
    if (*(unsigned short *)(a0 + 0x96) < 0xFFFF) {
        *(unsigned short *)(a0 + 0x96) += 1;
    }
}

/* func_L19_00417A58 is defined in L19_00417A58.c. */


/* func_L19_00417CA0 is defined in L19_003E9400-effects-g8.c. */

INCLUDE_ASM("asm/levels", func_L19_00417F88);

/* func_L19_0041B078 is defined in L19_0041B078-g8.c. */

/* func_L19_0041BFD0 is defined in L19_0041BFD0-g8.c. */

INCLUDE_ASM("asm/levels", func_L19_0041C328);


/* func_L19_0041E5B0 is defined in L19_003E9400-lift-g8.c. */

/* func_L19_0041EE60 is defined in L19_0041EE60.c. */

INCLUDE_ASM("asm/levels", func_L19_004203F0);

extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7750(void *, int, int);
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern char D_00188660[];
extern float D_L19_001A8F20[] MACRO_ADDR;
extern void func_002AA458(void *, void *, void *, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern float func_00282E48(void *, void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L19_00420B48(void *);
extern void func_002A8C00(float, void *, void *, int, void *);
extern int func_002761F8(void *, void *, int, void *, void *);

/* Moves the object between two points. State 0 records its home position and builds the far
   point (along the axis at 0xC0, raised by the first state word); state 1 waits for its trigger
   flag or for its linked entity to leave state 0; states 2 and 3 move it out and back, keeping
   its looping sound alive, and then cast a collision line along the axis at 0xE0. */
void func_L19_00420818(char *obj)
{
    char *data = *(char **)(obj + 0x68);
    float offset[4] __attribute__((aligned(16)));
    char query[0x30] __attribute__((aligned(16)));
    char *sound;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        func_00282F20(offset, obj + 0xC0, *(float *)(data + 4));
        func_00282CC0(data + 0x30, offset, obj + 0x10);
        *(float *)(data + 0x38) += *(float *)data;
        qcopy(data + 0x20, obj + 0x10);
        *(int *)(data + 0x40) = -1;
    case 1:
        if ((*(u8 *)(obj + 0xB0) != 0xFF && (D_0019B2E8[*(u8 *)(obj + 0xB0) + (D_001A79F0 << 4)] & 0x80)) ||
            (*(int *)(data + 0x1C) != -1 &&
             *(u8 *)((char *)((*(int *)(data + 0x1C) << 8) + (int)D_L19_001B2A1C[0]) + 0x20) != 0))
            func_002A7750(obj, 2, -1);
        break;
    case 2:
        func_002AA458(obj + 0x10, data + 0x30, data + 0x14, *(float *)(data + 8) * 0.00027777778f,
                      *(float *)(data + 8) * 0.00027777778f, *(float *)(data + 8) * 0.016666668f);
        sound = D_00188660 + *(int *)(data + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != obj || !*(u8 *)(sound + 0x74))
            *(int *)(data + 0x40) = func_002E5CF8(0, 4, obj);
        if (func_00282E48(obj + 0x10, data + 0x30) < *(float *)(data + 8) * 0.016666668f)
            func_002A7750(obj, 3, -1);
        break;
    case 3:
        sound = D_00188660 + *(int *)(data + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != obj || !*(u8 *)(sound + 0x74))
            *(int *)(data + 0x40) = func_002E5CF8(0, 4, obj);
        func_002AA458(obj + 0x10, data + 0x20, data + 0x14, *(float *)(data + 8) * 0.00027777778f,
                      *(float *)(data + 8) * 0.00027777778f, *(float *)(data + 8) * 0.016666668f);
        if (func_00282E48(obj + 0x10, data + 0x20) < *(float *)(data + 8) * 0.016666668f)
            func_002A7750(obj, 2, -1);
        break;
    }
    if (*(u8 *)(obj + 0x20) >= 2) {
        func_L00_002E6CF0(func_L19_00420B48, obj);
        func_002A8C00(4.0f, query, obj, 1, D_L19_001A8F20);
        *(u16 *)(query + 0x1A) = *(u16 *)(obj + 0xAA);
        func_00282F20(offset, obj + 0xE0, *(float *)(data + 0xC));
        func_00282CC0(offset, obj + 0x10, offset);
        func_002761F8(obj + 0x10, offset, 0, obj, query);
    }
}


extern int D_L19_001C9FC0[];
extern void func_L00_00323448(char *, char *, int, int, int, int, int, int);
extern void func_L00_00323958(char *, char *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);

/* Arms the rig object once its data arrives, then, when the level word matches the rig's tag, applies the stored rotations to the object and to every joint record. */
void func_L19_00420EF0(char *obj)
{
    char *rig = *(char **)(obj + 0x68);
    float turn[4] __attribute__((aligned(16)));
    char mat[0x30] __attribute__((aligned(16)));
    char *joint;
    int tag;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (*(long *)rig != -1) {
            { u8 a = 0xFF; *(u8 *)(obj + 0x30) = a; }
            func_L00_00323448(obj, rig + 0x30, 0x32, *(s32 *)(rig + 4), *(s32 *)rig, *(s32 *)(rig + 8), 7, 0);
            if (*(u8 *)(rig + 0x7A) == 0) {
                func_0029F338((u8 *)obj);
            } else {
                *(u8 *)(rig + 0x7D) = 1;
                *(u16 *)(obj + 0x34) |= 0x104;
                func_002833F0(obj + 0xC0, obj + 0xF0);
                *(u8 *)(obj + 0x20) = 1;
            }
        }
        return;
    case 1:
        if (D_L19_001C9FC0[0] == *(s32 *)(rig + 0xC)) {
            turn[0] = *(float *)(rig + 0x10) * 0.00029088825f;
            turn[1] = *(float *)(rig + 0x14) * 0.00029088825f;
            turn[2] = *(float *)(rig + 0x18) * 0.00029088825f;
            func_002833F0(mat, turn);
            func_00283738(obj + 0xC0, obj + 0xC0, mat);
            joint = rig + 0x30;
            do {
                turn[0] = *(float *)(rig + 0x1C) * 0.00029088825f;
                turn[1] = *(float *)(rig + 0x20) * 0.00029088825f;
                turn[2] = *(float *)(rig + 0x24) * 0.00029088825f;
                func_002833F0(mat, turn);
                func_00283738(joint, joint, mat);
                tag = *(u8 *)(joint + 0x4A);
                joint += 0x50;
            } while (tag != 1);
            func_L00_00323958(obj, rig + 0x30);
        }
        break;
    }
}

/* func_L19_00421E80 is defined in L19_00421E80-g8.c. */

/* func_L19_00422238 is defined in L19_00422238.c. */

extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_0019B4A8[];

extern s32 func_002B38B8(u8 *);
extern void func_0029F338(u8 *);
extern void func_L02_0031F858(s32, s32);

/* The part of the object's state this function reads: the id of its first entity, three group
   words, four mark words (-1 means none). */
typedef struct {
    s32 first;
    s32 groups[3];
    u8 pad[0x10];
    s32 marks[4];
} GrelbinState;

/* Leaves at once when byte 0xBC is clear, func_002B38B8 returns zero, the entity of state word 0
   is in neither state 0xFE nor 0xFD and the table byte of the object lacks bit 7; otherwise hands
   every entity of the three groups to func_0029F338, releases the four marks, counts one nibble of
   the table byte at 0xB2 up (saturating at 7) and releases the object. */
void func_L19_00422810(u8 *a0)
{
    GrelbinState *state = *(GrelbinState **)(a0 + 0x68);
    u16 *p;
    u8 *e;
    u8 *first;
    s32 i;
    s32 k;
    u16 f;

    if (a0[0xBC] == 0) {
        if (func_002B38B8(a0) == 0) {
            if (state->first != -1) {
                first = (u8 *)((state->first << 8) + (int)D_L19_001B2A1C[0]);
                if (first[0x20] != 0xFE) {
                    if (first[0x20] != 0xFD) {
                        if ((D_0019B2E8[a0[0xB0] + D_001A79F0 * 16] & 0x80) == 0)
                            return;
                    }
                }
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (state->groups[i] == -1)
            continue;
        for (p = D_L19_001FB5A0[state->groups[i]];
             (state->groups[i] & 0xFF) != 0xFF && state->groups[i] <= D_L19_001B2A38[0] &&
             p != 0 && ((s16)p[-1] >= 0 || p == D_L19_001FB5A0[state->groups[i]]);
             p++) {
            e = D_L19_001B2A1C[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            func_0029F338(e);
        }
    }
    for (k = 0; k < 4; k++) {
        if (state->marks[k] != -1)
            func_L02_0031F858(state->marks[k], 1);
    }
    f = *(u16 *)(a0 + 0xB2);
    if (f & 1) {
        u8 *q = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *q;

        if (((c >> 4) & 7) != 7)
            *q = c + 0x10;
    } else {
        u8 *q = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *q;

        if ((c & 7) != 7)
            *q = c + 1;
    }
    func_0029F338(a0);
}

/* func_L19_00422A98 is defined in L19_00422A98-g8.c. */

extern char D_L19_001B9A40[];
extern float D_L19_001B1ECC[] SDATA(D_L19_001B1ECC);
extern float D_L19_001B1ED0[] SDATA(D_L19_001B1ED0);
extern float D_L19_001B1ED4[] SDATA(D_L19_001B1ED4);
extern float D_L19_001B1ED8[] SDATA(D_L19_001B1ED8);
extern u8 D_L19_001B1EDC[] SDATA(D_L19_001B1EDC);
extern int D_L19_001B1EE0[] SDATA(D_L19_001B1EE0);
extern int D_L19_001B1EE4[] SDATA(D_L19_001B1EE4);
extern float D_L19_001B1EE8[] SDATA(D_L19_001B1EE8);
extern float D_L19_001B1EEC[] SDATA(D_L19_001B1EEC);
extern u32 D_L19_001B1EF0[] SDATA(D_L19_001B1EF0);
extern u32 D_L19_001B1EF4[] SDATA(D_L19_001B1EF4);
extern int D_L19_001B1EFC[] SDATA(D_L19_001B1EFC);
extern int D_L19_001B1F00[] SDATA(D_L19_001B1F00);
extern int D_L19_001B2508[] __attribute__((sda));
extern int func_002A77E0(int);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7A00(float *, float, float);
extern void *func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(unsigned int, unsigned int, float);
extern unsigned char *func_002C2FD8(void *, int, unsigned char, int, int, int, int, float);

/* Emits the glow of this object. Its origin is 1.5 units along the axis at 0xE0 for class
   0x11C7 and joint 0 otherwise. On one call in four it bursts four anchored particles whose
   velocities drift by random steps; every call it spawns four sprites in a line leading from
   the origin away from the point D_L19_001B9A40, coloured and faded by the counter at
   D_L19_001B2508 and scaled by the object's size. */
void func_L19_00423270(char *obj)
{
    float origin[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float jitter[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    int i, color, alpha, spriteAlpha;
    float inv255, half, three;

    if (*(short *)(obj + 0xAA) == 0x11C7) {
        func_00282F20(point, obj + 0xE0, 1.5f);
        func_00282CC0(origin, obj + 0x10, point);
    } else {
        func_0029FCC0(obj, 0, origin);
    }
    if (!func_002A77E0(4)) {
        func_002A7A00(velocity, D_L19_001B1ECC[0] * 0.016666668f, D_L19_001B1ED0[0] * 0.016666668f);
        {
            int glowAlpha = D_L19_001B1EDC[0];
            func_002C3150(origin, velocity, D_L19_001B1EE0[0], glowAlpha, func_002A77E0(255), 0,
                          D_L19_001B1EE8[0]);
        }
        for (i = 2; i >= 0; i--) {
            func_002A7A00(jitter, D_L19_001B1ED4[0] * 0.016666668f, D_L19_001B1ED8[0] * 0.016666668f);
            func_00282CC0(velocity, velocity, jitter);
            {
                int glowAlpha = D_L19_001B1EDC[0];
                func_002C3150(origin, velocity, D_L19_001B1EE4[0], glowAlpha, func_002A77E0(255), 0,
                              D_L19_001B1EEC[0]);
            }
        }
    }
    inv255 = 1.0f / 255.0f;
    half = 0.5f;
    three = 3.0f;
    func_00282CF0(point, D_L19_001B9A40, origin);
    func_00282F20(point, point, -0.3f);
    func_00282F20(step, point, 0.1f);
    func_00282CC0(point, point, origin);
    for (i = 0; i < 4; i++) {
        color = func_00283D38(D_L19_001B1EF0[0], D_L19_001B1EF4[0],
                              func_00282C48(half - func_00283CE0(255 - ((D_L19_001B2508[0] + i * 20) & 255)) * inv255));
        alpha = *(u8 *)D_L19_001B2508;
        if (i & 2)
            alpha *= 2;
        if (i & 1)
            alpha = 255 - alpha;
        spriteAlpha = (u8)alpha;
        func_002C2FD8(point, color, spriteAlpha, D_L19_001B1F00[0], D_L19_001B1EFC[0], 2, 0,
                      (func_00283CE0(i) + three) * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        func_00282CC0(point, point, step);
    }
}

INCLUDE_ASM("asm/levels", func_L19_00423548);

/* func_L19_00423A98 is in L19_003E9400-g8.c. */

/* func_L19_00423CC0 is defined in L19_00423CC0.c. */

INCLUDE_ASM("asm/levels", func_L19_00423EC0);
