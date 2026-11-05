#include "include_asm.h"
#include "common.h"

/* func_L02_003DB310 is defined in L02_003DB310-reinit-g8.c. */

extern void func_002A7750(char *, int, int);

extern void func_002E59F8(int);

extern void func_002A7470(char *, int, int, int);

extern void func_002A05A8(char *);

extern void func_0029F338(char *);

extern void func_0029F9F0(char *, char *);

extern char D_00188660[];

extern char *D_L02_001B359C __attribute__((sda));

/* An entity record (0x100 bytes, in the table at D_L02_001B359C). Both flag updates below go
   through this struct: a struct member store neither orders the next load of the table's base
   after it nor makes the compiler reload that base, which is how retail's loads are placed. */
typedef struct {
    char pad0[0x34];
    unsigned short flags;
} Entity003DB6D8;

/* The record of the table that the actor's state names at +0x244. */
#define CHILD003DB6D8 (D_L02_001B359C + *(int *)(*(char **)(arg0 + 0x68) + 0x244) * 0x100)

/* Switches the actor off: stops the effect that the state's slot at +0x26C indexes in the table at
   D_00188660 (0x70-byte records) when that record's owner (+0x88) is this actor and its live byte
   (+0x74) is set, clears the actor's own flags, and clears its child entity's state (the child
   is the table record that the state names at +0x244); the child is then handed to func_0029F9F0
   with each of the three sub-objects of the state whose byte at +0x171, +0x1B1, +0x1F1 is set. */
void func_L02_003DB6D8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int slot;
    char *rec;

    func_002A7750(arg0, 1, 0);
    slot = *(int *)(state + 0x26C);
    if (slot != -1) {
        rec = D_00188660 + slot * 0x70;
        if (*(char **)(rec + 0x88) == arg0 && *(unsigned char *)(rec + 0x74) != 0)
            func_002E59F8(slot);
    }
    *(int *)(state + 0x26C) = -1;
    func_002A7470(arg0, 0, 0, 3);
    func_002A05A8(arg0);
    *(unsigned char *)(arg0 + 0x31) = 0;
    *(int *)(arg0 + 0x98) = 0;
    ((Entity003DB6D8 *)arg0)->flags = (((Entity003DB6D8 *)arg0)->flags & 0xEFFF) | 3;
    ((Entity003DB6D8 *)CHILD003DB6D8)->flags |= 1;
    *(unsigned char *)(CHILD003DB6D8 + 0x31) = 0;
    *(int *)(CHILD003DB6D8 + 0x98) = 0;
    if (*(char **)(*(char **)(arg0 + 0x68) + 0x260) != 0)
        func_0029F338(*(char **)(*(char **)(arg0 + 0x68) + 0x260));
    if (*(unsigned char *)(state + 0x171) != 0)
        func_0029F9F0(CHILD003DB6D8, state + 0x170);
    if (*(unsigned char *)(state + 0x1B1) != 0)
        func_0029F9F0(CHILD003DB6D8, state + 0x1B0);
    if (*(unsigned char *)(state + 0x1F1) != 0)
        func_0029F9F0(CHILD003DB6D8, state + 0x1F0);
}

#undef CHILD003DB6D8

void func_L02_003DB870(char *arg0, int arg1) {
    *(int *)(*(char **)(arg0 + 0x68) + 0x264) = arg1;
}

/* Same body as func_L02_003D4990, with this function's own callees. */
void func_L02_003DB880(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(short *)(state + 0x280) != 0)
        return;
    (*(short *)(state + 0x282))++;
    while (*(float *)(state + 0x20) <
           (float)*(short *)(state + 0x24) * (3.0f - (float)*(short *)(state + 0x282)) * 0.33333334f)
        (*(short *)(state + 0x282))++;
    *(short *)(state + 0x280) = 1;
}

void func_L02_003DB938(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(short *)(state + 0x280) != 0)
        *(short *)(state + 0x280) = 0;
}

extern void func_002A7750();

int func_L02_003DB950(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *other = *(char **)(state + 0x264);
    unsigned char kind;
    int result = 0;

    if (other == 0)
        goto done;
    kind = *(unsigned char *)(other + 0x20);
    if (kind == 0xFE)
        goto done;
    if (kind == 0xFD)
        goto done;
    if (kind < 3)
        goto done;
    if (*(float *)(state + 0x20) <
        (float)*(short *)(state + 0x24) *
            (3.0f - (float)*(short *)(state + 0x282)) * 0.33333334f)
        result = 1;
done:
    return result;
}

/* func_L02_003DBA70 is matched in L02_003DBA70-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-por). */

/* func_L02_003DBB70 is matched in L02_003DBB70.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

extern char D_L02_001BA500;

extern float func_00282E48();

extern void func_002A93B0();

void func_L02_003DBE60(char *arg0) {
    if (*(unsigned char *)(arg0 + 0x31) != 0) {
        if (func_00282E48(arg0 + 0x10, &D_L02_001BA500) < 64.0f) {
            func_002A93B0(arg0);
            *(unsigned char *)(arg0 + 0x6F) = 60;
        }
    }
}

/* func_L02_003DBF40 is defined in L02_003DB310-g8.c (with -G8, its flag load is one assembler macro, which builds the address in $v1 as retail does). */

/* func_L02_003DBFD8 is defined in L02_003DB310-g8.c (it reads D_L02_001B0530 through $gp). */


/* func_L02_003E6D70 is defined in L02_003E6D70-g8.c. */

/* func_L02_003E7370 is defined in L02_003E7370-g8.c. */

extern int func_002B3868(char *);
extern int func_00282948(int *);
extern int func_00283CF0(float);
extern int D_L02_002A53B0[3][9];

/* The actor's state, as far as this function goes: three tracks of nine positions each. */
typedef struct {
    char pad0[0x60];
    float pos[3];
    int timer[3];
    int mode[3];
    float speed[3];
    int want[3];
} State003E75A8;

/* Advances the actor's three tracks (position +0x60, countdown +0x6C, mode +0x78, speed +0x84,
   wanted table entry +0x90), each position kept in [0, 9). The first time func_002B3868 agrees the
   countdowns are set (100 for the middle track, 50 and 180 for the others, swapped when bit 15 of
   +0x34 is set) and every mode becomes 1. Mode 1 moves the position back by its speed and becomes
   mode 2 when func_00282948 says its countdown is over. Mode 2 moves it the same way until the
   entry D_L02_002A53B0[track][(int)(position + 9) % 9] is the wanted one and the position is less
   than 0.2 above a whole number: the mode is then 0. Once all three modes are 0 the actor changes
   state (func_002A7750 with 4). */
void func_L02_003E75A8(char *arg0) {
    State003E75A8 *st = *(State003E75A8 **)(arg0 + 0x68);
    int i;

    if (func_002B3868(arg0)) {
        st->timer[1] = 100;
        st->timer[0] = 50;
        st->timer[2] = 180;
        if (*(u16 *)(arg0 + 0x34) & 0x8000) {
            st->timer[0] = 180;
            st->timer[2] = 50;
        }
        st->mode[0] = 1;
        st->mode[1] = 1;
        st->mode[2] = 1;
    }
    for (i = 0; i < 3; i++) {
        switch (st->mode[i]) {
        case 0:
            break;
        case 1:
            st->pos[i] = st->pos[i] - st->speed[i];
            if (st->pos[i] < 0.0f)
                st->pos[i] += 9.0f;
            if (func_00282948(&st->timer[i]))
                st->mode[i] = 2;
            break;
        case 2:
            st->pos[i] = st->pos[i] - st->speed[i];
            if (st->pos[i] < 0.0f)
                st->pos[i] += 9.0f;
            if (D_L02_002A53B0[i][func_00283CF0(st->pos[i] + 9.0f) % 9] == st->want[i]) {
                if (st->pos[i] - (float)func_00283CF0(st->pos[i]) < 0.2f)
                    st->mode[i] = 0;
            }
            break;
        }
        if (st->mode[0] == 0 && st->mode[1] == 0 && st->mode[2] == 0)
            func_002A7750(arg0, 4, -1);
    }
}

extern void func_00282CC0(void *, void *, void *);
extern void func_L02_0031E9E8(float *, float);
extern void func_L01_0031A278(char *, float *, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_00321878(char *, int, int, int, int, int, float);
extern int func_002A68A8(char *, int *);
extern char *func_003202E8(float *, int, int, int);
extern void func_00282D30(char *, char *, float);
extern void func_L02_003A8770(float *, int);
extern void func_0026FEB8(const char *, ...);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_002B0A18(int, int);
extern char D_L02_001B09C8[];
extern int D_L02_001AEC78 __attribute__((sda));
extern int D_L02_001A903C __attribute__((sda));
extern int D_001A79F8 __attribute__((sda));
extern void *D_L02_002A52D0[5];

/* The actor's state, as far as this function goes. */
typedef struct {
    char pad0[0xA4];
    int flag;
} State003E77E0;

/* The global at D_001A7A00: the byte at +0x79 is a one-shot flag. */
typedef struct {
    char pad0[0x79];
    u8 once;
} Global001A7A00;
extern Global001A7A00 D_001A7A00 __attribute__((sda));

/* Re-arms the actor (func_002A7750 with 1), builds a random point near it (a, from
   func_L01_0031A278, plus the offset b from func_L02_0031E9E8) and acts on the mode at +0x5C of
   its state (the one func_L02_003E79F8 rolls), through the level's own jump table. Mode 1 starts
   an effect (func_L00_00321878). Mode 2 sets the word at +0xA4, decrements D_L02_001AEC78 and
   changes the actor's state to 5. Mode 3 scales by 0.35 the state of the object func_003202E8
   makes at the point. Mode 4 calls func_L02_003A8770 and prints D_L02_001B09C8. Mode 5 runs a
   one-shot (the flag at D_001A7A00 + 0x79, func_002E5E58, func_002B0A18 and D_L02_001A903C) and
   adds 300 to D_001A79F8. Modes 1, 3, 4 and 5 call func_002E5CF8 with 2 first, any other mode
   with 3. */
void func_L02_003E77E0(char *arg0) {
    static void *tab[] = { &&c1, &&c2, &&c3, &&c4, &&c5 };
    char *state = *(char **)(arg0 + 0x68);
    float a[4];
    float b[4];
    int out;
    char *p;
    unsigned int sel;

    func_002A7750(arg0, 1, -1);
    func_L02_0031E9E8(b, 1.0f);
    func_L01_0031A278(arg0, a, 3.0f, 0.0f, 2.0f);
    func_00282CC0(a, b, a);
    sel = *(int *)(state + 0x5C) - 1;
    if (sel < 5)
        goto *D_L02_002A52D0[sel];
    goto other;
c1:
    func_002E5CF8(2, 0x20, arg0);
    func_L00_00321878(arg0, 0xF, 0x41, 3, -1, 4, 0.0f);
    goto done;
c2:
    ((State003E77E0 *)state)->flag = 1;
    D_L02_001AEC78--;
    func_002A7750(arg0, 5, -1);
    goto done;
c3:
    func_002E5CF8(2, 0x20, arg0);
    func_002A68A8(arg0, &out);
    p = *(char **)(func_003202E8(a, out, -1, 0) + 0x68);
    func_00282D30(p, p, 0.35f);
    goto done;
c4:
    func_002E5CF8(2, 0x20, arg0);
    func_L02_003A8770(a, 0);
    func_0026FEB8(D_L02_001B09C8);
    goto done;
c5:
    func_002E5CF8(2, 0x20, arg0);
    if (D_001A7A00.once == 0) {
        D_001A7A00.once = 1;
        func_002E5E58(1, 0, 0);
        func_002B0A18(0x1233, -1);
        D_L02_001A903C = 1;
    }
    D_001A79F8 += 300;
    goto done;
other:
    func_002E5CF8(3, 0x20, arg0);
done:
    return;
}

/* func_L02_003E79F8 is defined in L02_003DB310-g8.c (it reads its weights through $gp). */

INCLUDE_ASM("asm/levels", func_L02_003E7B58);

/* func_L02_003E7F28 is defined in L02_003DB310-g8.c (it reads D_L02_001B0A60 through $gp). */

INCLUDE_ASM("asm/levels", func_L02_003E80F8);

/* func_L02_003E87D8 is defined in L02_003E87D8-g8.c. */

/* func_L02_003E8CE8 is matched in L02_003E8CE8-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -g). */

/* func_L02_003E8E90 is matched in L02_003E8E90-g8.c (built with -frac2-qcopy). */

/* func_L02_003E9040 is matched in L02_003E9040-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003E91F0 is in L02_003E91F0-g8.c. */

/* func_L02_003E98A8 is in L02_003E98A8-g8.c. */


/* func_L02_003EA180 is in L02_003EA180-g8.c. */

extern void func_31E6A0(char *, int, int);

/* Re-arms the actor's sub-object and clears the low bits of its flags. */
void func_L02_003EA488(char *arg0) {
    char *p = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) != 0)
        return;
    *(int *)(p + 0x5C) |= 4;
    func_31E6A0(arg0, 1, -1);
    *(int *)(arg0 + 0x98) = 0;
    *(unsigned short *)(arg0 + 0x34) =
        (*(unsigned short *)(arg0 + 0x34) & 0xEFFF) | 0x43;
}


/* func_L02_003EAA68 is matched in L02_003EAA68.c (built with -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-barrier). */

/* func_L02_003EAE10 is matched in L02_003EAE10-g8.c (built with -frac2-zero-ti-barrier). */

/* func_L02_003EB098 is defined in L02_003DB310-g8.c (it reads D_L02_001B35B8 through $gp). */

/* func_L02_003EB138 is defined in L02_003DB310-g8.c (it reads D_L02_001B35B8 through $gp). */

INCLUDE_ASM("asm/levels", func_L02_003EB258);

/* func_L02_003EB648 is matched in L02_003EB648-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003EE938 is matched in L02_003EE938.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003EEAD8 is matched in L02_003EEAD8.c (built with -g). */

typedef struct {
    float x, y, z, w;
} V4;

typedef struct {
    int count;
    int pad[3];
    V4 pts[1];
} Entry;

typedef struct {
    int id;
    char pad04[0x2C];
    int idx;
    float t;
} State;

extern char *D_L02_001FF1C0[];
extern char D_00189EA0[];
extern float func_00282E80(char *, char *);

float func_L02_003EEC58(char *arg0) {
    State *state = *(State **)(arg0 + 0x68);
    Entry *entry = (Entry *)D_L02_001FF1C0[state->id];
    float cur = func_00282E80(D_00189EA0, (char *)&entry->pts[state->idx]);
    float d;

    if (state->idx < entry->count - 1) {
        d = func_00282E80(D_00189EA0, (char *)&entry->pts[state->idx + 1]);
        if (d < cur) {
            state->t += entry->pts[state->idx].w;
            if (state->t > 14.0f)
                state->t = 14.0f;
            state->idx += 1;
            return d;
        }
    }
    if (state->idx > 0) {
        d = func_00282E80(D_00189EA0, (char *)&entry->pts[state->idx - 1]);
        if (d < cur) {
            state->t -= entry->pts[state->idx].w;
            if (state->t < 0.0f)
                state->t = 0.0f;
            state->idx -= 1;
            return d;
        }
    }
    return cur;
}

extern float func_00282C48(float);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_002AAC80(void *, float, float, float, float);
extern void func_L00_00424B48(int);
extern void func_L00_00424C28(void);
extern float D_L02_001B0E90 __attribute__((sda));
extern char *D_L02_001FF1C0[];

/* Updates the heading (float at +0x38 of the actor's state) from the path D_L02_001FF1C0[*state]:
   its first word is the point count and its 16-byte points start at +0x10. The segment runs from
   point i (the index at +0x30, one back when it is the last point) to point j (i plus the
   lookahead at +0x3C, at most the last point). The segment's angle (func_00283248) minus the
   angle of the hero's direction vector (floats at +0x160 of its state, the pointer at +0x70 of the
   object at D_L02_001BA500 + 0x50) turned by pi, wrapped by func_00283B98 and func_00283BE0, clears
   the heading when it is under about a tenth of a degree; otherwise func_002AAC80 eases the
   heading towards it, weighted by the progress (+0x34, minus 6, over 8, at least 0). The heading
   is then copied into the hero's state at +0x1D4, +0x1DC gets 1.0 and, from a progress of 0.9, the
   two shared calls run. Nothing happens while the hero's halfword at +0x86 is not 0. */
void func_L02_003EEDD0(char *arg0) {
    char *hero = *(char **)(&D_L02_001BA500 + 0x50);
    char *state;
    char *hs;
    char *cam;
    float *dir;
    char *path;
    float scale;
    float a1;
    float a2;
    float t;
    int last;
    int i;
    int j;

    if (*(short *)(hero + 0x86) != 0)
        return;
    state = *(char **)(arg0 + 0x68);
    hs = *(char **)(hero + 0x70);
    cam = hs + 0x1C0;
    dir = (float *)(hs + 0x160);
    path = D_L02_001FF1C0[*(int *)state];
    scale = (*(float *)(state + 0x34) - 6.0f) * 0.125f;
    if (scale < 0.0f)
        scale = 0.0f;
    last = *(int *)path - 1;
    i = *(int *)(state + 0x30);
    if (i == last)
        i--;
    j = i + *(int *)(state + 0x3C);
    if (j > last)
        j = last;
    {
        char *p0 = path + i * 16;
        char *p1 = path + j * 16;

        a1 = func_00283248(*(float *)(p1 + 0x10) - *(float *)(p0 + 0x10),
                           *(float *)(p1 + 0x14) - *(float *)(p0 + 0x14));
    }
    a2 = func_00283248(dir[0], dir[1]);
    a2 = func_00283B98(a2, 3.1415927f);
    a1 = func_00283BE0(a1, a2);
    if (func_00282C48(a1) < 0.0017453294713050127f) {
        *(float *)(state + 0x38) = 0.0f;
    } else {
        t = scale * D_L02_001B0E90;
        func_002AAC80(state + 0x38, a1, (t + 0.5f) * 0.00027777778450399637f,
                      (t + 0.5f) * 0.00027777778450399637f, t * 0.01666666753590107f);
    }
    *(float *)(cam + 0x1C) = 1.0f;
    *(float *)(cam + 0x14) = *(float *)(state + 0x38);
    if (scale >= 0.9f) {
        func_L00_00424B48(0);
        func_L00_00424C28();
    }
}

typedef int TI128 __attribute__((mode(TI)));
extern char *D_L02_001FF1C0[];
extern char D_00189EA0[];
extern int func_L02_00348420(void *, char *);

/* True when D_00189EA0 is within the radius at +0x2C of the actor's position (+0x20) and also
   of one of the 16-byte points of the actor's table entry (taking every +0x40 of them); the
   point is then copied to a local vector that goes to func_L02_00348420 with the entry. */
int func_L02_003EEFB8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *entry = D_L02_001FF1C0[*(int *)state];
    TI128 buf;
    int i;

    if (*(float *)(state + 0x2C) < func_00282E48(D_00189EA0, state + 0x20))
        return 0;
    for (i = 0; i < *(int *)entry; i += *(int *)(state + 0x40)) {
        if (func_00282E48(D_00189EA0, entry + (i * 16 + 0x10)) < *(float *)(state + 0x2C)) {
            buf = *(TI128 *)D_00189EA0;
            *(int *)(state + 0x30) = func_L02_00348420(&buf, entry);
            return 1;
        }
    }
    return 0;
}


extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern void func_00325B70(void *, void *, int, int);
extern void func_00325C50(float, void *, void *, int, void *);
extern void func_00325DA0(void *, void *);
extern void *func_002A9640(void *, int, int);
extern int func_002B0ED8(void *, void *, int);
extern void func_L02_003F18E8(char *);
extern void func_L02_003F16F0(char *);
extern char D_L02_001A8F20[] __attribute__((sda));

/* The actor's state: only the words this function touches are named. */
typedef struct {
    u8 pad0[0x18];
    char *p18;
    u8 pad1c[0xC];
    u8 b28;
    u8 pad29[5];
    u8 b2E;
    u8 pad2f[0x19];
    u8 b48;
    u8 pad49;
    u8 b4A;
    u8 pad4b[0x15];
    u8 x60[0x10];
    u8 b70;
    u8 pad71[0x1F];
    float f90;
    float f94;
    u8 pad98[4];
    float f9C;
    u8 pada0[8];
    int fA8;
    u8 padac[0x44];
    int fF0;
    float fF4;
    u8 padf8[0x18];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    u8 pad124[0x18];
    float f13C;
    float f140;
    u8 pad144[0x370];
    float f4B4;
    u8 pad4b8[4];
    float f4BC;
    u8 x4C0[0xC];
    float f4CC;
    u8 pad4d0[0xC];
    u8 x4DC[0xE];
    short s4EA;
} St003F1298;

/* Update with a lazy start: the first call (state byte +0x20 still 0) sets the actor up (a random
   sway angle of 15 to 40 degrees, either sign, two random bytes from 15 and 12, its speed and
   timing words), registers it and runs func_L02_003F18E8; every call then fires func_002A93B0 when
   the player is within 24 units, turns the angle by the rate at +0x4CC, updates the effect,
   and for a visible actor of state 3 or more looks for the object of class 0xA03 / 0xB89 that
   it is attached to and releases it. */
void func_L02_003F1298(char *arg0) {
    St003F1298 *s = *(St003F1298 **)(arg0 + 0x68);
    float f;

    if (*(u8 *)(arg0 + 0x20) == 0) {
        s->p18 = (char *)&s->f110;
        f = func_002A7878(15.0f, 40.0f) * 0.017453294f;
        s->f4B4 = (func_002A77E0(2) != 0) ? -f : f;
        s->b48 = func_00283CF0(15.0f);
        s->b4A = func_00283CF0(12.0f);
        if (func_002A77E0(2) == 1)
            *(u16 *)(arg0 + 0x34) |= 0x8000;
        s->f4CC = 8.0f;
        s->f90 = 0.8f;
        s->b70 = 10;
        s->fA8 = 5;
        s->f94 = 0.8f;
        s->f9C = 0.4f;
        s->f118 = 0.4f;
        s->f110 = 0.6f;
        s->f114 = 0.2f;
        s->f11C = 0.4f;
        s->f4BC = 0.0f;
        s->f120 = 1.5707965f;
        s->f140 = 0.52359885f;
        s->f13C = 0.0055555557f;
        s->b28 = 3;
        s->b2E = 1;
        func_00325B70(arg0, s->x4C0, 0, 1);
        s->s4EA = 0;
        func_L02_003F18E8(arg0);
    }
    if (*(u8 *)(arg0 + 0x31) != 0) {
        if (func_00282E48(arg0 + 0x10, &D_L02_001BA500) < 24.0f) {
            func_002A93B0(arg0);
            *(u8 *)(arg0 + 0x6F) = 0x16;
        }
    }
    s->f4BC = func_00283B98(s->f4BC, s->f4CC * 0.017453294f);
    func_00325C50(s->f4BC, arg0, s->x4C0, 1, D_L02_001A8F20);
    func_00325DA0(arg0, s->x4DC);
    if (*(u8 *)(arg0 + 0x31) != 0 && *(u8 *)(arg0 + 0x20) >= 3) {
        char *t = func_002A9640(arg0, 0x10000, 1);

        if (t != 0 && *(char **)(t + 0x20) != 0 && *(u8 *)(arg0 + 0x31) == 0 &&
            (*(short *)(*(char **)(t + 0x20) + 0xAA) == 0xA03 ||
             *(short *)(*(char **)(t + 0x20) + 0xAA) == 0xB89))
            *(int *)(t + 0x2C) = 0;
        if (func_002B0ED8(arg0, s->x60, 0) == 5) {
            s->fF0 = 0;
            s->fF4 = 0.8377582f;
        }
        if (*(u8 *)(arg0 + 0x20) >= 2 && s->b2E == 2)
            func_L02_003F18E8(arg0);
        func_L02_003F16F0(arg0);
    }
}

extern void func_002B0990(char *, char *, float, int, int);

extern void func_002A8C28(char *, char *, int, float, float, float, int, int, int);

void func_L02_003F1578(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned short *)(arg0 + 0x96) < 0xFFFF)
        (*(unsigned short *)(arg0 + 0x96))++;
    func_002B0990(arg0, state + 0x220, 2.5f, 7, 1);
    func_002A8C28(arg0, arg0 + 0x10, 0x4000000, 1.3f, 1.0f, 1.0f, 0, 1, 0);
}

extern void func_002A91F0(char *, char *);

/* func_L02_003F1608 is defined in L02_003F1608.c. */

/* func_L02_003F16A8 is defined in L02_003DB310-g8.c (this unit has no $gp access for it). */

extern int func_L02_003FC0D0(int, short);

extern int func_002B3BA8(char *, int, float, float, int, int);

void func_L02_003F16F0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) < 4) {
        *(int *)(state + 0x4B0) = 0;
        goto done;
    }

    if (*(short *)(state + 0x4EA) == 1) {
        *(short *)(state + 0x4E8) =
            func_002B3BA8(arg0, *(int *)(state + 0x4E4), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x4B0) = *(int *)(state + 0x210);
    } else {
        if (func_L02_003FC0D0(*(int *)(arg0 + 0xB8), *(short *)(arg0 + 0xAA)) == 0)
            goto done;
        *(short *)(state + 0x4EA) = 1;
        *(short *)(state + 0x4E8) =
            func_002B3BA8(arg0, *(int *)(state + 0x4E4), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x4B0) = *(int *)(state + 0x210);
    }
    return;

done:
    *(short *)(state + 0x4EA) = 0;
}

extern void func_002B60B0(u8 *, float, float, float, float);

extern void func_002A0488(void *, u8, u8, u8);

/* Sets the actor up: re-registers its sub-objects and arms its effects. */
void func_L02_003F17B0(char *arg0, int arg1) {
    char *state = *(char **)(arg0 + 0x68);
    int i;

    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(u16 *)(state + 0x98) = 0;
    func_002B60B0((u8 *)arg0, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    func_002A7750(arg0, 3, 0);
    *(int *)(arg0 + 0x98) = *(int *)(*(char **)(arg0 + 0x24) + 0x10);
    *(u8 *)(state + 0x7A) = 0;
    *(u8 *)(arg0 + 0x31) = 1;
    *(u8 *)(arg0 + 0x7F) = 0;
    *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0x34) | 0x1000) & 0xFFB8;
    {
        char **slot = (char **)(state + 0x4C0);

        for (i = 1; i >= 0; i--) {
            if (*slot != 0) {
                *(u16 *)(*slot + 0x34) &= 0xFFFE;
                *(u8 *)(*slot + 0x31) = 1;
                *(int *)(*slot + 0x98) = *(int *)(*(int *)(*slot + 0x24) + 0x10);
            }
            slot++;
        }
    }
    {
        short flag = *(short *)(state + 0x60);

        *(u16 *)(state + 0x4F0) = arg1;
        *(u16 *)(state + 0x4EA) = 0;
        if (flag != 0) {
            *(short *)(state + 0x60) = 0;
            func_002A0488(arg0, *(u8 *)(state + 0x64), *(u8 *)(state + 0x65),
                          *(u8 *)(state + 0x66));
            *(short *)(state + 0x62) = 1;
        }
    }
}

extern void func_31E3C0(char *, int, int, int);

extern void func_316220(char *);

extern void func_31EA58(char *, float, float);

extern void func_32B068(char *, int, char *, float, float, float, float, int);

extern void func_2F1F70(void *, void *, void *);

extern void func_3FC1B0(int, int);

extern void func_41F230(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);

extern void func_366BD8(int, int, char *, int);

/* Tears the actor down: stops its effect, clears its sub-objects, resets flags. */
void func_L02_003F18E8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char buffer[0x10];
    int i;

    if (*(short *)(state + 0x4EA) == 1)
        func_3FC1B0(*(int *)(arg0 + 0xB8), 0xB22);
    *(short *)(state + 0x4EA) = 0;
    *(int *)(state + 0x4B0) = 0;
    *(unsigned char *)(state + 0x7A) = 0;
    *(unsigned char *)(state + 0x2E) = 1;
    if (*(unsigned char *)(arg0 + 0x31) != 0) {
        func_41F230(arg0 + 0x10, 0, 0x1E, 5, 5, 5, 0x2D, 1, 0.5f, 0.0f, 1, 0, 0, 0);
        func_366BD8(0, 0, arg0, 0xC3E);
        func_31EA58(buffer, 0.033333335071802139f, 0.083333335816860199f);
        func_2F1F70(buffer, buffer, state + 0xE0);
        func_32B068(arg0, 0x7F, buffer, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    {
        char **slot = (char **)(state + 0x4C0);

        for (i = 1; i >= 0; i--) {
            if (*slot != 0) {
                *(unsigned short *)(*slot + 0x34) |= 1;
                *(unsigned char *)(*slot + 0x31) = 0;
                *(int *)(*slot + 0x98) = 0;
            }
            slot++;
        }
    }
    func_31E3C0(arg0, 0, 0, 3);
    func_316220(arg0);
    func_31E6A0(arg0, 1, 0);
    *(unsigned char *)(arg0 + 0x31) = 0;
    *(int *)(arg0 + 0x98) = 0;
    *(unsigned short *)(arg0 + 0x34) =
        (*(unsigned short *)(arg0 + 0x34) & 0xEFFF) | 0x47;
}

/* func_L02_003F1A88 is defined in L02_003F1A88.c. */

void func_L02_003F1B70(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    *(short *)(state + 0x4EC) = *(unsigned char *)(arg0 + 0x20);
    *(short *)(state + 0x4EE) = *(unsigned char *)(arg0 + 0x95);
    func_002A7750(arg0, 6, 4);
}

/* func_L02_003F52B0 is defined in L02_003F52B0.c. */

extern char *D_L02_001B3AF8 __attribute__((sda));
extern char *D_L02_001B3AFC __attribute__((sda));
extern u8 D_L02_00220730;

/* Appends to the actor's list of 16-bit indices (at +0x40, count at +0x80, at most 0x20) the
   index of every 0x20-byte record of the table whose byte at +0x1A equals the current key. */
void func_L02_003F5390(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    s16 *tbl = (s16 *)(state + 0x40);
    u8 key = D_L02_00220730;
    char *end = D_L02_001B3AFC;
    int i = 0;
    char *p;

    for (p = D_L02_001B3AF8; p < end; p += 0x20, i++) {
        if (*(u8 *)(p + 0x1A) == key) {
            s16 *q = tbl + *(int *)(state + 0x80);

            *q = i;
            if (++*(int *)(state + 0x80) >= 0x20)
                break;
        }
    }
}
