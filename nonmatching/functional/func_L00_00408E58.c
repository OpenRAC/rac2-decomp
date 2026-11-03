/* functional: medium. Read against retail end to end; same calls, arguments, loads and stores in retail's order. Two retail quirks kept or noted: `base` is never written before func_00282CC0 adds the moby position to it (retail reads its own stack there too, lesson 16), and when func_002AB1F0 returns 0 retail still reads the byte at address 0xE and, if it is 2, runs the hit path and stores 2 there; this C skips a null record instead. Fixed from the draft: the 0x310440 callee is level 00's copy of func_0029F338, the callback hook is func_L00_002E6EF8. */
/*
 * func_L00_00408E58 (1476 bytes): a charged gadget's state machine (moby
 * state byte +0x20). 1: on the fire button (D_00138324), when allowed, play
 * the charge sound (D_L00_0029FBE0), arm the timer from D_L00_001B0F90 and go
 * to 2, else play 4; set the cooldown from the weapon table. 2: count down,
 * at 10 play the release animation and sound, then 4. 4: spawn the effect
 * once (func_L00_00416F68) ahead of the camera, then 5. 5: hold for the
 * timer at +8 (hooking func_L00_00409480 each frame), then 3. 3: gather up to
 * 32 mobys in a half-sphere (func_002AF580), lift their effect point by 1.5x
 * their height, flag classes 0xA8D/0xA8E/0x1002, hit those whose health is
 * at most 100 (drain 20 from the rest), then at the end of the timer play
 * the hit/miss sound and go back to 0.
 */
typedef struct { int w[4]; } __attribute__((aligned(16))) Quad_8E58;

extern struct {
    char pad0[0x1230];
    int mask;
    char pad1234[0xC];
    int level;
    char pad1244[0x104C];
    char *object;
    int state;
    char pad2298[0x24];
    unsigned char disabled;
} D_00189E20;
extern int D_L00_001A8F00;
extern int D_00138324;
extern int D_L00_001B0F90;
extern unsigned char D_00139593;
extern char D_L00_00262570[];
extern float D_L00_0025C64C;
extern char D_L00_0029FBE0[];
extern Quad_8E58 D_L00_001B8FF0;

extern void func_L00_00409420(char *);
extern void func_L00_002C42E0(int, int);
extern void func_002A75E0(char *, int, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002829D8(void *);
extern void func_00282A88(void *, int);
extern int func_00282948(void *);
extern int func_L00_002D4040(int);
extern void func_L00_002AF568(void);
extern int func_L00_002D6998(void *);
extern int func_002E5CF8(int, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_00416F68(void *, int, char *);
extern void func_L00_002E6EF8(void (*)(char *), char *);
extern void func_L00_00409480(char *);
extern void func_L00_0037E000(void *);
extern void func_002AF580(void *, void *, int *, void *, int, int, float, float, float, float, float, int, int);
extern char *func_002AB1F0(char *);
extern void func_002A6C58(char *, int, int);
extern void func_0029F338(char *);
extern int func_L00_002D3F30(int, int);

#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define B(p, n) (*(unsigned char *)((char *)(p) + (n)))
#define H(p, n) (*(short *)((char *)(p) + (n)))

void func_L00_00408E58(char *o)
{
    char *q = *(char **)(o + 0x68);
    Quad_8E58 base;     /* never written before use, as in retail */
    Quad_8E58 v, out;
    char *list[32];
    int count;
    int i;

    func_L00_00409420(o);
    if (D_00189E20.state == 1)
        func_L00_002C42E0(29, 1);
    if (B(o, 0x31))
        D_L00_0025C64C = 0.1f;
    if (B(o, 0x42) == B(o, 0x43) && (B(o, 0x60) & 2))
        func_002A75E0(o, 1, 0, 2, 0);
    func_00282CC0(&base, &base, o + 0x10);
    func_002829D8(q);

    if (B(o, 0x20) == 1) {
        if (D_L00_001A8F00 != 0 || D_00189E20.disabled != 0 ||
            (D_00138324 & D_00189E20.mask) == 0 || D_00189E20.level < 23)
            return;
        if (func_L00_002D4040(-1)) {
            func_L00_002AF568();
            I(q, 0x18) = func_L00_002D6998(D_L00_0029FBE0);
            B(o, 0x20) = 2;
            I(q, 4) = D_L00_001B0F90;
        } else {
            func_002E5CF8(4, 0, o);
        }
        F(q, 0) = 1.0f / F(D_L00_00262570 + D_00139593 * 0xE0, 0x54);
    } else if (B(o, 0x20) == 2) {
        if (func_00282948(q + 0x10)) {
            B(o, 0x20) = 4;
            I(q, 0x10) = 30;
            I(q, 0x14) = 0;
        }
        if (I(q, 0x10) == 10) {
            func_002A75E0(o, 2, 0, 3, 0);
            func_002E5CF8(1, 0, o);
        }
    } else if (B(o, 0x20) == 4) {
        if (func_00282948(q + 0x10)) {
            B(o, 0x20) = 5;
            I(q, 0x14) = 0;
            I(q, 0x10) = 30;
            func_002A75E0(o, 3, 0, 3, 0);
        } else if (I(q, 0x14) == 0) {
            v = *(Quad_8E58 *)(D_00189E20.object + 0xC0);
            func_00282F20(&v, &v, 1.0f);
            func_00282CC0(&out, &base, &v);
            func_L00_00416F68(&out, 1, o);
            I(q, 0x14) = 1;
        }
    } else if (B(o, 0x20) == 5) {
        if (func_00282948(q + 8)) {
            B(o, 0x20) = 3;
            I(q, 8) = 64;
            func_002A75E0(o, 4, 0, 3, 0);
        } else {
            func_L00_002E6EF8(func_L00_00409480, o);
        }
    } else if (B(o, 0x20) == 3) {
        int *timer = (int *)(q + 4);

        v = D_L00_001B8FF0;
        func_00282A88(list, 128);
        func_L00_0037E000(o);
        func_002AF580(o + 0x10, &v, &count, list, 32, 0,
                      3.1415929794311523f, 1.047197699546814f, 40.0f, 0.0f, 0.0f, 0, 0);
        for (i = 0; i < count; i++) {
            char *p;
            int active = 1;

            out = *(Quad_8E58 *)(list[i] + 0x10);
            p = func_002AB1F0(list[i]);
            if (p != 0) {
                F(&out, 8) = F(&out, 8) + F(p, 16) * 1.5f;
                if (100.0f < F(p, 0))
                    active = 0;
            }
            if (list[i] != 0 && B(list[i], 0x20) != 254 && B(list[i], 0x20) != 253) {
                if (H(list[i], 0xAA) == 0xA8D)
                    B(list[i], 0x95) = 9;
                if (H(list[i], 0xAA) == 0xA8E)
                    B(list[i], 0x95) = 7;
                if (H(list[i], 0xAA) == 0x1002)
                    B(list[i], 0x20) = 7;
            }
            if (active) {
                if (p != 0 && (B(p, 14) == 1 || B(p, 14) == 2)) {
                    func_L00_00416F68(&out, 0, 0);
                    I(q, 0x1C) = I(q, 0x1C) + 1;
                    func_002A6C58(list[i], 0, 3);
                    B(p, 14) = 2;
                } else if (p != 0 && B(p, 14) != 3) {
                    func_L00_00416F68(&out, 0, 0);
                    I(q, 0x1C) = I(q, 0x1C) + 1;
                    func_002A6C58(list[i], 0, 3);
                    func_0029F338(list[i]);
                }
            } else {
                F(p, 0) = F(p, 0) - 20.0f;
                if (F(p, 0) < 0.0f)
                    F(p, 0) = 0.0f;
            }
        }
        if (func_00282948(timer)) {
            if (I(q, 0x1C) != 0)
                func_002E5CF8(2, 0, o);
            else
                func_002E5CF8(3, 0, o);
            I(q, 0x1C) = 0;
            B(o, 0x20) = 0;
            func_L00_002D3F30(-1, 1);
        }
    }
}
