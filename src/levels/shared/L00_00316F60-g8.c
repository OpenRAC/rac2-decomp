#include "include_asm.h"
#include "common.h"

extern int D_L00_001B1B30;
extern int D_L00_001A9034 __attribute__((sda));
extern int D_L00_001B1B48;
extern int D_L00_001A9038 __attribute__((sda));

void func_L00_0032A138(void) {
    int count = 4;
    int *cursor = &D_L00_001B1B30;

    do {
        *cursor = 0;
        --cursor;
        --count;
    } while (count >= 0);
    D_L00_001A9034 = 0;
}

void func_L00_0032A170(void) {
    int count = 4;
    int *cursor = &D_L00_001B1B48;

    do {
        *cursor = 0;
        --cursor;
        --count;
    } while (count >= 0);
    D_L00_001A9038 = 0;
}

extern int D_L00_001A8FB4;
extern int D_L00_001A8FB4_1 __attribute__((sda));
extern int D_L00_001A8FB0;
extern int D_L00_001B2084;
extern int D_L00_001B2084_1 __attribute__((sda));
extern void func_L00_0030DDF0(void);
extern void func_0028B5D0(int);

int func_L00_003268E8(int value) {
    if (D_L00_001A8FB4 != value)
        return 0;
    if (D_L00_001B2084 == -1)
        return 0;

    D_L00_001A8FB0 = 0;
    D_L00_001A8FB4_1 = 0;
    func_L00_0030DDF0();
    func_0028B5D0(D_L00_001B2084_1);
    D_L00_001B2084 = -1;
    return 1;
}

extern unsigned char *D_L00_001B1F9C;

extern int func_2EE138(void *, void *, void *);
extern void func_2EE5B0(void *, void *, void *);
extern float func_2EE268(void *);

/* Screens the 128-byte record the index picks out of the resident object table: runs the
   caller's transform through the record's two matrices and accepts only when the remaining
   length is under 1 and the record's own z direction stays inside [-1, 1]. */
int func_L00_003206B8(void *a0, int a1)
{
    unsigned char *s0;
    float b1[4];
    float b2[4];

    if (a1 < 0)
        return 0;
    s0 = D_L00_001B1F9C + (a1 << 7);
    func_2EE138(b1, a0, s0 + 0x30);
    *(int *)((unsigned char *)b1 + 0xC) = 0;
    func_2EE5B0(b2, b1, s0 + 0x40);
    if (func_2EE268(b2) < 1.0f) {
        if (*(float *)((unsigned char *)b2 + 8) >= -1.0f) {
            if (*(float *)((unsigned char *)b2 + 8) <= 1.0f)
                return 1;
        }
    }
    return 0;
}

extern void func_0029FC20(void *, int, void *);
extern void func_002833F0(void *, void *);
extern void func_00283678(void *, void *);
extern void func_00283738(void *, void *, void *);
extern char *D_L00_001B1E9C;
extern char *D_L00_001B251C;
extern char *D_L00_001B2400;
typedef struct {
    char transform[48];
    float position[4];
    void *offset;
    void *attachment;
    short index;
    unsigned char end, joint, type, copy_matrix, period, phase;
} B1320Entry;
extern void func_00282B50(void *, void *, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CA8(void *, void *, void *);
extern void func_00283658(void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_002A0F48(void *);
extern void func_L00_0036AE00(int, int);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern void func_00282D60(void *, void *, float);
extern int D_L00_001B19C8 __attribute__((sda));
extern char *D_L00_001B23F8;
extern char *D_L00_0021EA20[];
void func_L00_00323958(char *object, B1320Entry *entries)
{
    char matrix[64] __attribute__((aligned(16)));
    char temp[64] __attribute__((aligned(16)));
    char rotation[64] __attribute__((aligned(16)));
    unsigned int i;
    float x, y;
    int sx, sy, active;
    if (!entries->end) return;
    if (entries->copy_matrix) func_00282B50(matrix, object + 0xC0, 48);
    else func_002833F0(matrix, object + 0xF0);
    qcopy_nc(matrix + 48, object + 0x10);
    *(int *)(matrix + 60) = 0;
    i = 0;
    do {
        if (entries[i].attachment) {
            func_0029FC20(entries[i].attachment, entries[i].joint, temp);
            func_00283678(matrix, temp);
        }
        switch (entries[i].type) {
        case 0:
            func_00283098(temp, entries[i].position, matrix);
            func_00282CC0(D_L00_001B1E9C + entries[i].index * 256 + 0x10, matrix + 48, temp);
            if (entries[i].offset) func_00282CC0(D_L00_001B1E9C + entries[i].index * 256 + 0x10, D_L00_001B1E9C + entries[i].index * 256 + 0x10, (char *)entries[i].offset + 0x10);
            break;
        case 1:
            func_00283098(temp, entries[i].position, matrix);
            func_00282CA8(D_L00_001B251C + entries[i].index * 64 + 0x30, matrix + 48, temp);
            break;
        case 2:
            func_00283098(temp, entries[i].position, matrix);
            func_00282CA8(D_L00_001B2400 + entries[i].index * 64 + 0x30, matrix + 48, temp);
            break;
        }
        switch (entries[i].type) {
        case 0: {
            char *item;
            item = D_L00_001B1E9C + entries[i].index * 256;
            if (!*(int *)(item + 0x24)) func_002833F0(item + 0xC0, item + 0xF0);
            func_00283738(item + 0xC0, matrix, &entries[i]);
            if (entries[i].offset) {
                func_002833F0(temp + 16, entries[i].offset);
                func_00283738(item + 0xC0, item + 0xC0, temp + 16);
            }
            if (!*(int *)(item + 0x24)) {
                func_00283658(rotation, item + 0xC0);
                func_002AB6D8(rotation, item + 0xF0);
            }
            break;
        }
        case 1: {
            char *item;
            item = D_L00_001B251C + entries[i].index * 64;
            func_00283738(item, matrix, &entries[i]);
            if (entries[i].offset) {
                func_002833F0(temp + 16, entries[i].offset);
                func_00283738(item, item, temp + 16);
            }
            break;
        }
        case 2:
            func_00283738(D_L00_001B2400 + entries[i].index * 64, matrix, &entries[i]);
            break;
        }
        switch (entries[i].type) {
        case 0: {
            typedef struct { char p[0x24]; int f; char q[256-0x28]; } M;
            if (((M *)D_L00_001B1E9C)[entries[i].index].f) func_002A0F48(&((M *)D_L00_001B1E9C)[entries[i].index]);
            break;
        }
        case 1:
            active = 0;
            if (entries[i].period == 0) active = 1;
            else if (entries[i].period != 255) {
                if (D_L00_001B19C8 % entries[i].period == entries[i].phase) active = 1;
            }
            func_L00_0036AE00(entries[i].index, active);
            break;
        case 2: {
            char *item, *data;
            item = D_L00_001B2400 + entries[i].index * 64;
            data = D_L00_001B23F8 + entries[i].index * 32;
            x = func_00282DF0(item);
            x += func_00282DF0(item + 0x10);
            x *= 0.5f;
            y = func_00282DF0(item + 0x20);
            sx = func_00283CF0(x * 4096.0f);
            sy = func_00283CF0(y * 4096.0f);
            sy = sy <= 65536 ? sy : 65536;
            sy <<= 16;
            if (sx > 65536) sx = 65536;
            *(int *)(item + 0x2C) = sx | sy;
            func_00283098(data, D_L00_0021EA20[(unsigned char)data[0x1A]], item);
            func_00282D60(data, data, *(float *)(item + 0x3C));
            func_00282CC0(data, data, item + 0x30);
            break;
        }
        }
    } while (entries[i++].end != 1);
}
