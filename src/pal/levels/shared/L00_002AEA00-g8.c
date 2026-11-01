#include "include_asm.h"

typedef struct {
    unsigned char pad0[0xE98];
    char *objects[2];
    int unused;
    int pending;
    unsigned char pad1[0x2290 - 0xEA8];
    int resource;
    unsigned char pad2[0x22B4 - 0x2294];
    unsigned char disabled;
    unsigned char pad3[3];
    unsigned char enabled;
    unsigned char pad4;
    unsigned char active;
    unsigned char mode;
} StateAF3D8;
typedef struct {
    char pad[44];
    int id;
    char rest[176];
} EntryAF3D8;
typedef struct {
    char first[0x600];
    char second[0x600];
} BufferAF3D8;
extern unsigned char D_00139568[];
extern StateAF3D8 D_00189E20_26;
extern int D_L00_001A7D00[2] __attribute__((sda));
extern BufferAF3D8 D_L00_001B7400[];
extern char D_L00_00262570[];
extern int func_L00_002ADEA0(int);
extern char *ref_L00_002AF3D8_0(int, int);
extern void ref_L00_002AF3D8_1(int, void *, int, int, int, int);

void func_PAL_L00_002AF2C8(int arg0, int arg1)
{
    int id, i;

    if (D_00189E20_26.disabled || !D_00189E20_26.enabled ||
        !D_00189E20_26.active || arg0 || !arg1)
        return;

    id = ((EntryAF3D8 *)D_L00_00262570)[D_00139568[func_L00_002ADEA0(0)]].id;
    if (id == -1)
        return;

    for (i = 0; i < 2; i++) {
        char *object;

        if (D_00189E20_26.objects[i])
            continue;
        if (i == 1 && D_00189E20_26.mode != 2)
            break;

        object = ref_L00_002AF3D8_0(D_00189E20_26.resource, D_L00_001A7D00[i]);
        D_00189E20_26.objects[i] = object;
        if (object) {
            D_00189E20_26.pending = 0;
            *(int *)(object + 8) = 0;
            *(char **)(object + 56) = D_L00_001B7400[i].first;
            *(char **)(object + 60) = D_L00_001B7400[i].second;
            ref_L00_002AF3D8_1(D_00189E20_26.resource, object, id, 0, 12, 1);
            *(float *)(object + 40) = 1.0f;
        }
    }
}
