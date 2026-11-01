#include "include_asm.h"

#include "common.h"
extern float func_00283B98(float a0, float a1);
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} Aimvec_F0b10;
extern Aimvec_F0b10 D_L00_001B8C80;
extern Aimvec_F0b10 D_L00_001B8C80;
extern void func_0029F338(char *);
extern int func_002ACBC8(void *, int);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_L00_0036EF68(char *, int, int, int);
extern void ref_L00_003F3160_00(void *, void *);
extern void func_L00_003F3518(char *);
extern int D_L00_001A9018 __attribute__((sda));
extern unsigned short **D_L00_001A9014 __attribute__((sda));
extern unsigned char *D_L00_001B2514 __attribute__((sda));
extern void func_0029F338(char *a0);

/* A three-state object whose record (the pointer at +0x68) carries a group index at +0, two
   RGB triples and two RGBA quadruples as separate bytes, a packed colour at +0x10 and a few
   angle and flag words. State 0 arms it: an index outside the group table releases the object;
   otherwise the two angles are turned into radians, the byte triples are packed into the words
   at +0x14, +0x18, +0x30 and +0x34, and the object is handed to the binder with
   func_L00_003F3518 as its handler (state 2), or parked in state 1 when the word at +0x1C is set.
   State 1 steps the angle at +0xC and eases the colour at +0x10 towards one of the two packed
   colours; when it changed, its three bytes go to every entity of the group's id list. State 2
   re-binds the handler. The two stores of the byte at +0x30 sit in the arms of the select: the
   record's word at +0x68 either supplies its low byte or the object gets 0xFF. */
void func_PAL_L00_003F7528(char *obj)
{
    unsigned char *st = *(unsigned char **)(obj + 0x68);
    int group;
    int prev;
    int stamp;
    int word_a, word_b;
    int target;
    float angle;
    unsigned short *q;
    unsigned char *e;
    int r, g, b;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        group = *(int *)st;
        if (group >= D_L00_001A9018 || D_L00_001A9014[group] == 0 || group == -1) {
            func_0029F338(obj);
            return;
        }
        *(float *)(st + 8) = *(float *)(st + 8) * 0.017453294f;
        *(float *)(st + 4) = *(float *)(st + 4) * 0.0003490659f;
        *(int *)(st + 0x14) = st[0x22] << 16 | st[0x21] << 8 | st[0x20];
        *(int *)(st + 0x18) = st[0x25] << 16 | st[0x24] << 8 | st[0x23];
        if (*(int *)(st + 0x68) != 0) {
            stamp = st[0x68];
            obj[0x30] = stamp;
        } else {
            stamp = 0xFF;
            obj[0x30] = stamp;
        }
        if (*(int *)(st + 0x1C) != 0) {
            obj[0x20] = 1;
            return;
        }
        word_a = st[0x29] << 24 | st[0x28] << 16;
        word_a |= st[0x27] << 8;
        word_a |= st[0x26];
        *(int *)(st + 0x30) = word_a;
        word_b = st[0x2D] << 24 | st[0x2C] << 16;
        word_b |= st[0x2B] << 8;
        word_b |= st[0x2A];
        *(int *)(st + 0x34) = word_b;
        if (*(float *)(st + 0x40) == 0.0f && *(float *)(st + 0x44) == 0.0f &&
            *(float *)(st + 0x48) == 0.0f)
            *(int *)(st + 0x6C) = 1;
        ref_L00_003F3160_00((void *)func_L00_003F3518, obj);
        obj[0x20] = 2;
        return;
    case 1:
        if (*(int *)(st + 0x64) != -1) {
            if (func_002ACBC8(&D_L00_001B8C80.x_140, *(int *)(st + 0x64)) == 0)
                return;
        }
        angle = func_00283B98(*(float *)(st + 0xC), *(float *)(st + 4));
        prev = *(int *)(st + 0x10);
        *(float *)(st + 0xC) = angle;
        if (*(float *)(st + 8) != 0.0f) {
            target = *(int *)(st + 0x14);
            if (angle > *(float *)(st + 8))
                target = *(int *)(st + 0x18);
            *(int *)(st + 0x10) = func_00283D38(prev, target, 0.120000005f);
        } else {
            *(int *)(st + 0x10) = func_00283D38(*(int *)(st + 0x14), *(int *)(st + 0x18),
                                                func_00283198(angle) * 0.5f + 0.5f);
        }
        if (*(int *)(st + 0x10) == prev)
            return;
        q = D_L00_001A9014[*(int *)st];
        r = *(int *)(st + 0x10) & 0xFF;
        g = (*(int *)(st + 0x10) >> 8) & 0xFF;
        b = (*(int *)(st + 0x10) >> 16) & 0xFF;
        for (; q != 0 && ((short)q[-1] >= 0 || q == D_L00_001A9014[*(int *)st]) &&
               (e = D_L00_001B2514 + ((*q & 0x7FFF) << 5)) != 0;
             q++)
            func_L00_0036EF68((char *)e, r, g, b);
        return;
    case 2:
        if (*(int *)(st + 0x64) == -1 ||
            func_002ACBC8(&D_L00_001B8C80.x_140, *(int *)(st + 0x64)) != 0)
            ref_L00_003F3160_00((void *)func_L00_003F3518, obj);
        return;
    }
}

