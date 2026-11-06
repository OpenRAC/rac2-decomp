/* func_PAL_L09_00408690, the PAL copy of func_L09_00403798: the same C, where D_L09_001B13C0 is read as
   a word and scaled to 50 Hz, the func_002A7470 blend times 5 and (in state 8 only) 20 scale, and the
   floats passed to func_002B60B0 and func_00282F20 change. */
#include "common.h"

/* Offsets from the sound-table anchor; the index stride is 0x70. */
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad2[0x13];
    char *owner;
} DobboSoundAnchor;

extern s32 D_L09_001B13C0 __attribute__((sda));
extern int D_L09_001B13D4 __attribute__((sda));
extern char D_L09_001B13D8[], D_00189EA0[], D_00188660[];
extern struct {
    char pad[0x80];
    char position[0x10];
    char pad2[0x240C];
    char *target;
} D_00189E20;
extern int *D_L09_001FE6C0[];

extern void func_L09_00403270(char *);
extern void func_L09_00403378(char *);
extern void func_L09_00403080(char *);
extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern void func_002B60B0(char *, float, float, float, float);
extern void func_L01_00318638(char *, char *, char *);
extern float func_00283CE0(int);
/* The wrapper replaces the path index with its pointer and forwards the other
   arguments to func_002C9828, then returns a status. */
extern int func_L07_00338D20(int, int, char *, char *, int, float);
extern int func_002B3868(char *);
extern int func_002E5CF8(int, int, char *);
extern int func_002B4FF0(char *, char *, float);
extern float func_00282E80(char *, char *);
extern int func_002B1C20(char *, char *);
extern void func_0026FEB8(char *, ...);
extern void func_002E59F8(int);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFEB8(char *, void *, void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_002B0A68(char *, int, void *, u8, float, float, float, float);
extern void func_002A6C58(char *, int, int);
extern void func_0029F338(char *);
extern void func_PAL_L09_00408090(char *);
extern void func_PAL_L09_00408290(char *);
extern void func_L09_00403700(char *);

void func_PAL_L09_00408690(char *obj)
{
    char *p = *(char **)(obj + 0x68);
    int state, flags, index;
    int *path;
    float length;
    float v[4];

    func_L09_00403270(obj);
    func_L09_00403378(obj);
    state = (u8)obj[0x95];
    switch (state) {
    case 0:
        if (*(int *)(p + 0x234) == 1 || *(s16 *)(p + 0x26C)) {
            func_L09_00403080(obj);
            if ((u8)obj[0x43] != 2)
                func_002A7470(obj, 2, 0, 4);
            *(int *)(p + 0x28C) = *(int *)(p + 0x244);
            *(float *)(p + 0x290) = 0;
            *(int *)(p + 0x138) |= 4;
            func_002A7750(obj, 4, 1);
        }
        break;
    case 2:
        if (*(int *)(p + 0x234) == 1 || *(s16 *)(p + 0x26C)) {
            func_L09_00403080(obj);
            *(u16 *)(p + 0x26C) = ((s32)(D_L09_001B13C0) * 5 + 2) / 6;
            if ((u8)obj[0x43] != state)
                func_002A7470(obj, 2, 0, 4);
            func_002B60B0(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            *(int *)(p + 0x13C) = *(int *)(p + 0x254);
            *(int *)(p + 0x28C) = *(int *)(p + 0x244);
            func_002A7750(obj, 3, 3);
        }
        break;
    case 3:
        if (!*(int *)(p + 0x234) && !*(s16 *)(p + 0x26C)) {
            func_002B60B0(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            if (*(u8 *)(obj + 0x43) != 0)
                func_002A7470(obj, 0, 0, 20);
            func_002A7750(obj, 2, 2);
        }
        break;
    }

    switch ((u8)obj[0x20]) {
    case 2:
        func_L01_00318638(obj, p + 0x1F0, p + 0x100);
        break;
    case 3:
        if (obj[0x60] & 2)
            func_002A7750(obj, 5, -1);
        break;
    case 4:
        if (obj[0x60] & 2) {
            if (*(u8 *)(obj + 0x43) != 0)
                func_002A7470(obj, 0, 0, 20);
        }
        path = D_L09_001FE6C0[*(int *)(p + 0x250)];
        length = func_00283CE0(*path);
        *(float *)(p + 0x290) += length / (*(float *)(p + 0x25C) * 60.0f);
        if (length <= *(float *)(p + 0x290)) {
            *(float *)(p + 0x290) = length;
            func_002B60B0(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            *(int *)(p + 0x138) &= ~4;
            func_002A7750(obj, 5, 3);
        }
        func_L07_00338D20(*(int *)(p + 0x250), 0, obj + 0x10, obj + 0xF0, 0,
                         *(float *)(p + 0x290));
        break;
    case 5:
        if (obj[0x60] & 2) {
            if (*(u8 *)(obj + 0x43) != 0)
                func_002A7470(obj, 0, 0, 20);
        }
        func_L01_00318638(obj, p + 0x1F0, p + 0x100);
        if (*(s16 *)(p + 0x26A)) {
            func_002B60B0(obj, 0.0096f, 0.080000006f, 1.0053098f, 1.0053098f);
            if ((u8)obj[0x43] != 2)
                func_002A7470(obj, 2, 0, 4);
            func_002A7750(obj, 6, -1);
        }
        break;
    case 6:
        if ((obj[0x60] & 2) && (u8)obj[0x42] == 2) {
            if ((u8)obj[0x43] != 3)
                func_002A7470(obj, 3, 0, 4);
            func_002A7750(obj, 7, -1);
        }
        break;
    case 7:
        if (func_002B3868(obj)) {
            DobboSoundAnchor *entry = (DobboSoundAnchor *)(D_00188660 + *(s16 *)(p + 0x274) * 0x70);
            if (entry->owner != obj || !entry->active)
                *(s16 *)(p + 0x274) = func_002E5CF8(D_L09_001B13D4, 4, obj);
        }
        func_002B4FF0(obj, p + 0x220, 0.0f);
        if (D_00189E20.target == obj || func_00282E80(obj + 0x10, D_00189E20.position) < 1.2f) {
            if ((u8)obj[0x43] != 4)
                func_002A7470(obj, 4, 0, 4);
            func_002A7750(obj, 8, -1);
        }
        break;
    case 8:
        if ((obj[0x60] & 2) && (u8)obj[0x42] == 4) {
            if (*(u8 *)(obj + 0x43) != 0)
                func_002A7470(obj, 0, 0, 17);
            func_002A7750(obj, 5, -1);
        }
        break;
    case 9:
        flags = func_002B1C20(obj, p + 0x50);
        if (flags & 1) {
            func_0026FEB8(D_L09_001B13D8, *(s16 *)(p + 0x274), *(s16 *)(obj + 0xB2));
            index = *(s16 *)(p + 0x274);
            if (index != -1) {
                DobboSoundAnchor *entry = (DobboSoundAnchor *)(D_00188660 + index * 0x70);
                if (entry->owner == obj && entry->active)
                    func_002E59F8(index);
            }
            *(s16 *)(p + 0x274) = -1;
            func_00282CF0(v, obj + 0x10, D_00189EA0);
            func_002AFEB8(obj, v, v, 0, 0.0f);
            func_00282F20(v, v, 0.120000005f);
            func_002B0A68(obj, 0x3F, v, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            func_002E5CF8(0, 0, obj);
            func_002A6C58(obj, 0, 3);
            func_0029F338(obj);
            return;
        } else if (flags & 2) {
            *(u16 *)(p + 0x26C) = ((s32)(D_L09_001B13C0) * 5 + 2) / 6;
            func_002A7750(obj, 5, 3);
            func_002E5CF8(3, 0, obj);
        }
        break;
    }

    if ((u8)obj[0x20] != 7) {
        index = *(s16 *)(p + 0x274);
        if (index != -1) {
            DobboSoundAnchor *entry = (DobboSoundAnchor *)(D_00188660 + index * 0x70);
            if (entry->owner == obj && entry->active)
                func_002E59F8(index);
        }
        *(s16 *)(p + 0x274) = -1;
    }
    func_PAL_L09_00408090(obj);
    func_PAL_L09_00408290(obj);
    func_L09_00403700(obj);
}
