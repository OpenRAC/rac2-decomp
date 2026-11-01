#include "include_asm.h"

typedef struct {
    char pad_000[0xBF8];
    int field_BF8;
    char pad_BFC[0x1230 - 0xBFC];
    int field_1230;
    char pad_1234[0x1240 - 0x1234];
    int field_1240;
    char pad_1244[0x1450 - 0x1244];
    int field_1450;
    char pad_1454[0x2294 - 0x1454];
    int field_2294;
    char pad_2298[0x22BC - 0x2298];
    unsigned char field_22BC;
    char pad_22BD[0x2534 - 0x22BD];
    int field_2534;
} HeroState;
typedef struct {
    char pad[0x1A0];
    int field_1A0, field_1A4;
} InputState;
typedef struct {
    char pad[0x1D];
    unsigned char selected;
} Selection3EA540;
typedef struct {
    char pad[0x54];
    float rate;
    char rest[0x88];
} Entry;
extern HeroState D_00189E20;
extern InputState D_00138180;
extern Selection3EA540 D_00139568;
extern Entry D_L00_00262570[];
extern char D_L00_001B2B90[] __attribute__((sda));
extern void func_L00_003EA7D0(void);
extern int func_00282948(void *), func_002829D8(void *);
extern int func_L00_002D3F30(int, int), func_L00_002D4040(int);
extern void func_002A75E0(char *, int, int, int, int);
extern void func_002E5CF8(int, int, char *), func_PAL_002A7E68(char *, int, int, int);
extern int func_L00_00329E90(char *, int, void *), func_L00_0032A088(int, int);
extern void func_00282C88(void *), func_00283098(void *, void *, void *);
extern void func_0029FCC0(char *, int, void *);
extern char *func_PAL_L00_003E0120(char *, int, void *, void *);
extern void ref_L00_003EA540_00(void *, char *);

void func_PAL_L00_003EE818(char *self)
{
    float v[4];
    int tmp[4];
    char *st = *(char **)(self + 0x68);
    int ready = 1;
    char *shot;

    if (D_00189E20.field_2294 == 0x1D) {
        if (!func_00282948(&D_00189E20.field_2534))
            ready = 0;
    } else {
        D_00189E20.field_2534 = 33;
    }
    if (*(unsigned char *)(self + 0x42) == *(unsigned char *)(self + 0x43) &&
        (*(unsigned char *)(self + 0x60) & 2))
        func_002A75E0(self, 1, 0, 2, 0);
    if (D_00189E20.field_1450)
        D_00189E20.field_BF8 = D_00189E20.field_1450;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        self[0x20] = 1;
        *(int *)(st + 0xC) = 0;
        *(int *)st = 0;
        *(int *)(st + 4) = func_L00_00329E90(self, 0, tmp);
        *(int *)(st + 8) = func_L00_0032A088(*(short *)(self + 0xAA), *(int *)(st + 4));
        /* Fall through. */
    case 1:
        if (func_002829D8(st) && ready && D_00189E20.field_1240 >= 19 &&
            (D_00138180.field_1A0 & D_00189E20.field_1230) &&
            !D_00189E20.field_22BC && func_L00_002D3F30(-1, 1)) {
            func_00282C88(v);
            v[1] = -1.0f;
            func_00283098(v, v, self + 0xC0);
            func_0029FCC0(self, 0, D_L00_001B2B90);
            shot = func_PAL_L00_003E0120(self, *(int *)(st + 4), D_L00_001B2B90, v);
            func_002E5CF8(0, 0, self);
            if (*(unsigned char *)(self + 0x43) != 2)
                func_PAL_002A7E68(self, 2, 0, 0);
            *(float *)(self + 0x48) = 2.0f;
            if (shot)
                *(char **)(shot + 0xB8) = self;
            {
                int selected = D_00139568.selected;
                Entry *entry = &D_L00_00262570[selected];
                *(float *)st = 1.0f / entry->rate;
            }
        } else if ((D_00138180.field_1A4 & D_00189E20.field_1230) &&
                   !func_L00_002D4040(-1) && !D_00189E20.field_22BC) {
            func_002E5CF8(2, 0, self);
        }
    }
    ref_L00_003EA540_00(func_L00_003EA7D0, self);
}
