#include "common.h"

/* func_L20_0043F318 defined in L20_0043F318-g8.c. */

/* func_L20_0043F460 is defined in L20_0043ECB0-g8.c (it reaches a global through $gp). */

/* func_L20_0043F570 is defined in L20_0043F570-g8.c. */

/* func_L20_0043FC70 is defined in L20_0043F570-g8.c (it reaches data through $gp). */

/* func_L20_0043FFF0 is defined in L20_0043F570-g8.c (it reaches globals through $gp). */

/* func_L20_00440198 is defined in L20_00440198.c (its slot-table and func_002A7750 declarations conflict with this unit's). */

extern char *D_L20_001FBB20[];

extern int D_L20_001B2FB8 __attribute__((sda));

extern unsigned int D_L20_001B2F9C __attribute__((sda));

/* Counts the objects of a group whose state byte (object + 0x20) is neither 6 nor negative.
   D_L20_001FBB20 holds a list of 16-bit object ids per group; the low 15 bits of an id index
   the 0x100-byte object records at D_L20_001B2F9C, and the last id of a list has its top bit
   set. The guards on the group and its list come before the walk and again after each record,
   as in func_L20_0039E0A0. The bound D_L20_001B2FB8 does not change in the loop, so cc1 hoists
   its repeated test into a register known to be zero, which the loop still tests (retail's
   `daddu $t0,$zero,$zero` and `bnez $t0`). */
int func_L20_00440398(int group) {
    unsigned short *rec = (unsigned short *)D_L20_001FBB20[group];
    int count = 0;

    if ((group & 0xFF) == 0xFF) {
        goto end;
    }
    if (D_L20_001B2FB8 < group) {
        goto end;
    }
    if (rec == 0) {
        goto end;
    }
    for (;;) {
        char *object = (char *)D_L20_001B2F9C + ((*rec & 0x7FFF) << 8);

        if (object == 0) {
            goto end;
        }
        if (*(unsigned char *)(object + 0x20) != 6 && *(signed char *)(object + 0x20) >= 0) {
            count++;
        }
        rec++;
        if ((group & 0xFF) == 0xFF) {
            goto end;
        }
        if (D_L20_001B2FB8 < group) {
            goto end;
        }
        if (rec == 0) {
            goto end;
        }
        if (*(short *)(rec - 1) >= 0) {
            continue;
        }
        if (rec == (unsigned short *)D_L20_001FBB20[group]) {
            continue;
        }
        break;
    }
end:
    return count;
}

extern void func_002A7750(int, int, int);

void func_L20_00440460(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    *(unsigned short *)(state + 0x178) = 0;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(int *)(arg0 + 0x98) = 0;
    *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
    func_002A7750(arg0, 6, 3);
}
extern void func_00282CC0(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);
extern int func_00282948(char *);
extern void func_0029F338(char *);

void func_L20_004404B8(char *arg0) {
    char *q = arg0 + 0x10;
    char *state = *(char **)(arg0 + 0x68);

    func_00282CC0(q, q, state);
    *(float *)(state + 8) = *(float *)(state + 8) - *(float *)(state + 0x14);
    func_00282D30(state, state, *(float *)(state + 0x10));
    func_002A8C28(*(char **)(arg0 + 0xB8), q, 0x10001, 0,
                  *(float *)(state + 0x18), 3.0f, 1.0f, 1, 0);
    if (func_00282948(state + 0x1C) != 0) {
        func_0029F338(arg0);
    }
}

extern void func_0027DDC0(int, int, int, int);

void func_L20_00440570(void) {
    func_0027DDC0(0, 0, 0, 0x80);
}

/* func_L20_00440598 is defined in L20_00440598-g8.c (it reaches data through $gp and needs -frac2-hazard-labels). */

/* func_L20_00441CB8 is defined in L20_00441CB8-g8.c. */

/* func_L20_004421A8 is defined in L20_004421A8-g8.c. */

/* func_L20_004424A0 is defined in L20_004424A0-helpers-g8.c. */
/* func_L20_004424A0 reads four constants through $gp: its near miss is in
   nonmatching/levels/func_L20_004424A0.c and belongs in the -G8 sibling. */

/* func_L20_00442550 is defined in L20_00442550-g8.c. */

extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);

extern float func_00282E80(char *, char *);

extern void func_002B50E0(char *, char *, float);

extern void func_L01_00321178(char *, char *);

void func_L20_004427C8(char *arg0, char *arg1, float f) {
    char *state = *(char **)(arg0 + 0x68);

    func_002A8C28(arg0, arg0 + 0x10, 0x04010000, 0,
                  *(float *)(state + 0x50) + 0.5f, 50.0f, 1.0f, 1, 0);
    if (func_00282E80(arg0 + 0x10, arg1) <= *(float *)(state + 0x84)) {
        func_002B50E0(arg0, arg1, f);
    } else {
        func_L01_00321178(arg0, arg1);
    }
}


/* func_L20_004429F0 is defined in L20_004429F0-g8.c. */

extern int func_002A7820(int, int);

extern int func_L20_004433B0(char *);

extern int func_002A77E0(int);

void func_L20_00442C10(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int v = *(int *)(state + 0x17F4);
    int r;

    if (v == 2) goto other;
    if (v >= 3) goto other;
    if (v != 1) goto other;
    r = func_L20_004433B0(arg0);
    *(int *)(state + 0x17FC) = r;
    if (r == 0) {
        func_002A7750(arg0, 0xC, 4);
    } else {
        func_002A7750(arg0, 4, 2);
    }
    goto done;
other:
    r = func_002A77E0(2) + 2;
    *(int *)(state + 0x17F8) = r;
    *(int *)(state + 0x1810) = func_002A7820(0xB4, 0x168);
    func_002A7750(arg0, 3, 1);
done:
    *(int *)(state + 0x17F4) = *(unsigned char *)(arg0 + 0x95);
}

/* func_L20_00442CD8 is defined in L20_00442CD8-g8.c. */

INCLUDE_ASM("asm/levels", func_L20_00442E68);

extern int func_002ABB78(char *);

extern void func_L02_003A6F78(char *);

extern void func_L20_00449A78(char *);

void func_L20_00442F30(char *arg0) {
    if (func_002ABB78(arg0) != 0) {
        func_L02_003A6F78(arg0);
    } else if (*(short *)(arg0 + 0xAA) == 0x12D3) {
        func_L20_00449A78(arg0);
    }
}

/* func_L20_00442F80 is defined in L20_00442F80-g8.c. */

/* func_L20_004431E0 is defined in L20_004431E0-g8.c (it reads D_L20_001B2FB8 through $gp and needs -frac2-keep-block-order). */
/* func_L20_004431E0 reads a global through $gp: its near miss is in
   nonmatching/levels/func_L20_004431E0.c and belongs in the -G8 sibling. */

extern unsigned int D_L20_001B2F9C __attribute__((sda));
extern int func_L03_003CA138(char *);
/* func_L20_004499E8 is defined in L20_004499E8-g8.c. */
extern int func_L20_00449AC8(char *);

extern void func_0039BDF0(char *, char *, int, int);

char *func_L20_00443328(char *arg0, char *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    unsigned int p = D_L20_001B2F9C + (*(int *)(state + 0x238) << 8);

    if (func_L20_00449AC8((char *)p) != 0) {
        func_L20_004499E8((char *)p, arg0, arg1);
        func_0039BDF0((char *)p, (char *)(p + 0x10), 0x168, 0);
        return (char *)p;
    }
    return 0;
}
/* func_L20_004433B0 is defined in L20_004433B0-g8.c (it reaches a global through $gp). */

extern int func_0033E808(char *, int);

extern int func_003BA3F8(char *);

extern int func_L20_00449AD8(char *);

int func_L20_00443508(char *arg0, char *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    short v;

    if (func_0033E808(arg1 + 0x10, *(int *)(state + 0x220)) == 0) {
        goto ret0;
    }
    v = *(short *)(arg1 + 0xAA);
    if (v < 0x1FF) {
        goto ret0;
    }
    if (v < 0x201) {
        goto other;
    }
    if (v != 0x12D3) {
        goto ret0;
    }
    if (func_L20_00449AC8(arg1) != 0) {
        goto ret0;
    }
    if (func_L20_00449AD8(arg1) != 0) {
        goto ret0;
    }
    return 1;
other:
    return func_003BA3F8(arg1) == 0;
ret0:
    return 0;
}

/* func_L20_004435A0 is in L20_004435A0-g8.c. */

/* func_L20_00443790 is defined in L20_00443790-helpers-g8.c. */

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;

extern void func_00283098(void *, void *, void *);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);

void func_L20_00443908(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    Vec4 v[6];

    func_00282CC0(arg0 + 0x10, arg0 + 0x10, state);
    *(float *)(state + 8) = *(float *)(state + 8) - *(float *)(state + 0x20);
    v[2].q = 0;
    v[2].f[2] = 0.5f;
    func_00283098(&v[0], &v[2], arg0 + 0xC0);
    func_00283958(state + 0x10, &v[3]);
    func_00283738(arg0 + 0xC0, &v[3], arg0 + 0xC0);
    func_00283098(&v[1], &v[2], arg0 + 0xC0);
    func_00282CF0(&v[2], &v[0], &v[1]);
    func_00282CC0(arg0 + 0x10, arg0 + 0x10, (char *)&v[2]);
    if (func_00282948(state + 0x24) != 0) {
        func_0029F338(arg0);
    }
}

/* func_L20_00443A10 lives in L20_00443A10-g8.c. */

/* func_L20_00443B60 is defined in L20_00443B60-helpers.c. */

INCLUDE_ASM("asm/levels", func_L20_00443CF0);
/* func_L20_00443CF0 is one word pair away: its near miss is in
   nonmatching/levels/func_L20_00443CF0.c. */

INCLUDE_ASM("asm/levels", func_L20_00443D58);

INCLUDE_ASM("asm/levels", func_L20_00443DF0);

/* func_L20_00444018 is defined in L20_00444088-g8.c (it needs this unit's -fno-schedule-insns). */

/* func_L20_00444088 is defined in L20_00444088-g8.c (it reaches a global through
   $gp and needs its own -fno-schedule-insns). */


/* func_L20_00444138 is defined in L20_00444138-g8.c (it reads a global through $gp and
   needs its own -mno-split-addresses). */

INCLUDE_ASM("asm/levels", func_L20_004441D8);

/* func_L20_004448A8 is defined in L20_004448A8-g8.c (it needs the -G8 profile with split addresses). */

extern float func_00283248(float, float);

extern float func_00283BE0(float, float);

void func_L20_00444AA8(char *arg0, float *arg1) {
    char *state = *(char **)(arg0 + 0x68);
    float f;

    f = func_00283248(arg1[0] - *(float *)(arg0 + 0x10),
                      arg1[1] - *(float *)(arg0 + 0x14));
    f = func_00283BE0(f, *(float *)(arg0 + 0xF8));
    if (f > 1.0471977f) {
        f = 1.0471977f;
    } else if (f < -1.0471977f) {
        f = -1.0471977f;
    }
    *(float *)(state + 0x2B8) = f;
}

/* func_L20_00444B48 is defined in L20_00444B48-g8.c. */

extern void func_L00_002E6EF8(void (*)(void), int);

void func_L20_00444C68(int arg0) {
    func_002A7750(arg0, 0x12, -1);
    func_L00_002E6EF8(func_L20_00440570, arg0);
}

/* func_L20_00444CA8 is defined in L20_00444CA8.c. */

INCLUDE_ASM("asm/levels", func_L20_004450D8);
/* func_L20_004450D8 reads a global through $gp: its near miss is in
   nonmatching/levels/func_L20_004450D8.c and belongs in the -G8 sibling. */

/* func_L20_004451C0 is defined in L20_004451C0-g16.c (it reaches two 16-byte vectors through $gp). */

/* The level's own jump table (the label of the data blob at 0x002B5960). */
extern void *jtbl_002B5960[];

extern int func_002B3868(char *);

extern int func_002B38B8(char *);

extern void func_002AA548(char *, char *, float, float, float, float);

extern int func_002E5CF8(int, int, char *);

extern unsigned char D_0019B2E8[];

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
void func_L20_00445738(char *arg0) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(arg0 + 0x20);
    state = *(char **)(arg0 + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5960[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(arg0 + 0x10);
    func_002A7750(arg0, 1, -1);
    goto out;
c1:
    if ((D_0019B2E8[((unsigned char *)arg0)[0xB0] + *(int *)0x001A79F0 * 16] & 0x80) == 0) {
        goto end;
    }
    func_002A7750(arg0, 2, -1);
    goto out;
c2:
    if (func_002B3868(arg0) != 0) {
        *(int *)(state + 0x14) = 0;
        func_002E5CF8(0, 0, arg0);
    }
    func_002AA548(arg0 + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (func_002B38B8(arg0) == 0) {
        goto end;
    }
    func_002A7750(arg0, 4, -1);
    goto out;
c4:
    if (func_002B3868(arg0) != 0) {
        func_002E5CF8(0, 0, arg0);
        *(int *)(state + 0x14) = 0;
    }
    func_002AA548(arg0 + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

/* func_L20_00445890 is defined in L20_00445890-g8.c. */

/* The level's own jump table (the label of the data blob at 0x002B5980). */
extern void *jtbl_002B5980[];

extern int func_002B3868(char *);

extern int func_002B38B8(char *);

extern void func_002AA548(char *, char *, float, float, float, float);

extern unsigned char D_0019B2E8[];

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
void func_L20_00446E70(char *arg0) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(arg0 + 0x20);
    state = *(char **)(arg0 + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5980[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(arg0 + 0x10);
    func_002A7750(arg0, 1, -1);
    goto out;
c1:
    if ((D_0019B2E8[((unsigned char *)arg0)[0xB0] + *(int *)0x001A79F0 * 16] & 0x80) == 0) {
        goto end;
    }
    func_002A7750(arg0, 2, -1);
    goto out;
c2:
    if (func_002B3868(arg0) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    func_002AA548(arg0 + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (func_002B38B8(arg0) == 0) {
        goto end;
    }
    func_002A7750(arg0, 4, -1);
    goto out;
c4:
    if (func_002B3868(arg0) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    func_002AA548(arg0 + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

extern int func_L00_00324120(char *);
extern float func_00282C48(float);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L14_003DE908(char *);
extern void func_002AD6F0(void *, void *, void *, void *);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot D_00188660[];
extern float D_00189EA4;

void func_L20_00446FA8(char *arg0) {
    Vec4 pos, rot, delta;
    char *state = *(char **)(arg0 + 0x68);
    qcopy(&pos, arg0+0x10);
    qcopy(&rot, arg0+0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        *(int *)(state+0x5C) |= 1;
        {
            float target=*(float *)(state+0x60);
            float start=*(float *)(arg0+0x14);
            *(float *)(state+0x6C) = 0.0011666667f;
            *(float *)(state+0x64) = start;
            *(float *)(state+0x70) = (start+target)*0.5f;
        }
        if (*(int *)(state+0x78) == 0) *(int *)(state+0x74)=0;
        else *(int *)(state+0x74)=1;
        func_002A7750(arg0,1,-1);
        break;
    case 1:
        if (func_002B38B8(arg0)) {
            if (func_L00_00324120(arg0) || (*(float *)(arg0+0x14)-*(float *)(state+0x70))*(D_00189EA4-*(float *)(state+0x70)) < 0.0f) {
                if (*(int *)(state+0x74)==0) func_002A7750(arg0,2,-1);
                else func_002A7750(arg0,3,-1);
                if (!func_002E59B0(arg0,*(int *)(state+0x7C))) *(int *)(state+0x7C)=func_002E5CF8(0,4,arg0);
            }
        }
        break;
    case 2:
        if (func_002B3868(arg0)) *(int *)(state+0x68)=0;
        if (func_00282C48(*(float *)(state+0x60)-*(float *)(arg0+0x14)) < 0.03f) {
            int i=*(int *)(state+0x7C);
            if (i != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)D_00188660+i*0x70);
                if (slot->owner==arg0 && slot->active) func_002E59F8(i);
            }
            *(int *)(state+0x7C)=-1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state+0x74)=1;
                *(float *)(arg0+0x14)=*(float *)(state+0x60);
                func_002A7750(arg0,1,-1);
            }
        } else func_002AA548(arg0+0x14,state+0x68,*(float *)(state+0x60),*(float *)(state+0x6C),*(float *)(state+0x6C),0.20000002f);
        break;
    case 3:
        if (func_002B3868(arg0)) *(int *)(state+0x68)=0;
        if (func_00282C48(*(float *)(arg0+0x14)-*(float *)(state+0x64)) < 0.03f) {
            int i=*(int *)(state+0x7C);
            if (i != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)D_00188660+i*0x70);
                if (slot->owner==arg0 && slot->active) func_002E59F8(i);
            }
            *(int *)(state+0x7C)=-1;
            if (!func_L14_003DE908(arg0)) {
                *(int *)(state+0x74)=0;
                *(float *)(arg0+0x14)=*(float *)(state+0x64);
                func_002A7750(arg0,1,-1);
            }
        } else func_002AA548(arg0+0x14,state+0x68,*(float *)(state+0x64),*(float *)(state+0x6C),*(float *)(state+0x6C),0.20000002f);
        break;
    }
    func_00282CF0(&delta,arg0+0x10,&pos);
    func_002AD6F0(state+0x20,&delta,&rot,arg0+0xF0);
}

extern void func_L00_003294F0(char *, int);
extern void func_L20_00447640(char *);

void func_L20_004473B0(char *arg0) {
    char *state;
    TI128 pos, rot, delta;
    float accel;

    state = *(char **)(arg0 + 0x68);
    qcopy(&pos, arg0 + 0x10);
    qcopy(&rot, arg0 + 0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        qcopy(state + 0x60, arg0 + 0x10);
        *(int *)(state + 0x5C) |= 1;
        func_L00_003294F0(arg0, 1);
        func_002A7750((int)arg0, 4, -1);
        break;
    case 1:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x74);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 2, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68) + speed;
            accel = (speed * 4.0f) / (float)(duration * duration);
            func_002AA548(arg0 + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 2:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x78);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 3, -1);
        }
        break;
    case 3:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x7C);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 4, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68);
            accel = (speed * 4.0f) / (float)(duration * duration);
            func_002AA548(arg0 + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 4:
        if (func_002B3868(arg0) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x80);
        }
        if (func_00282948(state + 0x84) != 0) {
            func_002A7750((int)arg0, 1, -1);
        }
        break;
    }
    if (func_002B38B8(arg0) == 0) {
        if (0.0f < *(float *)(state + 0x8C)) {
            func_L20_00447640(arg0);
            *(float *)(state + 0x8C) = -1000.0f;
        }
    }
    func_00282CF0(&delta, arg0 + 0x10, &pos);
    func_002AD6F0(state + 0x20, &delta, &rot, arg0 + 0xF0);
}

/* func_L20_00447640 is defined in L20_00447640-g8.c (it reads D_L20_001B2FB8 through $gp). */

/* func_L20_00447748 is defined in L20_00447748-g8.c. */

extern char D_L20_002AB980[];

extern void func_L04_003A21F8();

void func_L20_00447908(void) {
    func_L04_003A21F8(D_L20_002AB980, 6);
}

/* func_L20_00447930 is defined in L20_00447930-g8.c (it reaches data through $gp). */

extern float func_00283B98(float, float);
extern int func_00277258(char *, int, char *, float);
extern float func_00282DB0(char *, char *);
extern void func_00282F20(char *, char *, float);
extern float func_00282DF0(char *);

extern char D_L20_001C0430[];

void func_L20_00448858(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    float d, f;
    char v[0x10];

    d = *(float *)(state + 8);
    *(float *)(state + 8) = d - (d > 0.0f ? *(float *)(state + 0x20) * 4.0f : *(float *)(state + 0x20));

    func_00282CC0(arg0 + 0x10, arg0 + 0x10, state);
    *(float *)(arg0 + 0xF0) = func_00283B98(*(float *)(arg0 + 0xF0), *(float *)(state + 0x10));
    *(float *)(arg0 + 0xF4) = func_00283B98(*(float *)(arg0 + 0xF4), *(float *)(state + 0x14));
    *(float *)(arg0 + 0xF8) = func_00283B98(*(float *)(arg0 + 0xF8), *(float *)(state + 0x18));

    if (func_00277258(arg0 + 0x10, 0, arg0, 1.5f) != 0) {
        char *p = D_L20_001C0430;

        qcopy(arg0 + 0x10, p);
        if (func_00282DB0(state, p + 0x10) < 0.0f) {
            func_00282F20(p + 0x10, p + 0x10, 1.0f);
            f = func_00282DF0(state);
            func_00282D30(v, p + 0x10, -func_00282DB0(state, p + 0x10) * 1.25f);
            func_00282CC0(state, state, v);
            func_00282F20(state, state, f * 0.5f);
        }
        *(int *)(state + 0x24) = 0;
        if ((unsigned char)arg0[0x23] > 0x60) {
            arg0[0x23] = 0x60;
        }
    }

    if (func_00282948(state + 0x24) != 0) {
        if ((unsigned char)arg0[0x23] < 5) {
            func_0029F338(arg0);
        } else {
            arg0[0x23] = arg0[0x23] - 4;
        }
    }
}

/* func_L20_00448A18 is defined in L20_00448A18-helpers-g8.c. */
/* func_L20_00448A18 reaches four globals through $gp: its near miss is in
   nonmatching/levels/func_L20_00448A18.c and belongs in the -G8 sibling. */
