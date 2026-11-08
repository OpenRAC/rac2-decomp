#include "ps2_hw.h"
#include "include_asm.h"

extern void *func_00115484(void *, int, int);
extern char D_001BAEC0[];
extern char D_02000000[];
extern int D_001B22B0[] __attribute__((sda));
extern char ref_L00_00290B48_00[];
extern char ref_L00_00290B48_01[];

typedef struct {
    unsigned long long words[2];
} __attribute__((aligned(16))) ParserScratch;

extern unsigned char ref_L00_00291640_01[];
extern unsigned short *func_002F4FA0(unsigned short *, unsigned short *, int, ParserScratch *);
extern unsigned short *func_002E31E8(unsigned short *, unsigned short *, int, ParserScratch *);
extern unsigned short *func_002F0B78(unsigned short *, unsigned short *, int, ParserScratch *);


extern int func_002886C8(int a, char *b);

extern void func_002883E8(int a);

/* Qwen draft (branch qwen/autonomy, d969a356), checked by tools/check.py */
void func_00278EB0(void);

/* loops 56 times calling a two-argument helper and, unless the current index is zero, a second one-argument helper with that index. */
void func_00290A40(char *a0)
{
    int i;

    for (i = 0; i < 56; i++) {
        if (func_002886C8(i, a0) == 0)
            continue;
        if (i != 0)
            func_002883E8(i);
    }
}


typedef struct { int source, length, destination, flags; } Request_290AB0;
extern int func_0011AFE0(Request_290AB0 *, int);
extern int func_0011AFC0(int);
extern int func_0011ED08(int, int, int);

int func_00290AB0(int source, int destination, int length)
{
    Request_290AB0 request;
    int handle;
    int result = 1;
    request.source = source;
    request.destination = destination;
    request.length = length;
    request.flags = 0;
    handle = func_0011AFE0(&request, 1);
    if (handle) {
        while (func_0011AFC0(handle) >= 0) {}
        if (func_0011ED08(length, 0, 0) < 0)
            result = 0;
    }
    return result;
}

void func_00290B48(void)
{
    int *state = (int *)D_001BAEC0;
    unsigned int start, size;

    func_00115484(state, 0, 0x9C);
    state[0] = 0;
    state[1] = 0x100000;
    start = ((unsigned int)ref_L00_00290B48_00 + 0x3FFF) & ~0x3FFF;
    state[2] = start;
    state[3] = start;
    size = D_001B22B0[0];
    state[4] = state[3] + size;
    state[5] = state[4] + size;
    state[6] = state[5] + state[1];
    state[0x84 / 4] = (unsigned int)ref_L00_00290B48_01 - 0x8000;
    state[0x80 / 4] = state[0x84 / 4] - 0x40000;
    state[0x7C / 4] = state[0x80 / 4] - 0x64000;
    state[0x78 / 4] = state[0x7C / 4] - 0x2C000;
    state[0x74 / 4] = state[0x78 / 4] - 0x8000;
    state[0x68 / 4] = state[6];
    state[0x88 / 4] = (unsigned int)D_02000000 - 0x4000;
    state[0x70 / 4] = state[0x74 / 4] - 0x14000;
    state[0x6C / 4] = state[0x70 / 4];
    state[0x8C / 4] = 0x07000000;
    state[0x90 / 4] = 0x07100000;
    state[0x94 / 4] = 0x07180000;
    state[0x98 / 4] = 0x07200000;
}

extern void func_00124418(void);
extern void func_00126F60(int);
extern void func_00284000(void);
extern void func_0029D050(void);
extern void func_0027B440(int);
extern void func_0011AE70(int);
extern void func_00126DC0(int (*)(void));
extern int func_001339B0(void);
extern void func_002FC138(void);
extern void func_002FC1D8(void);
extern void func_002FCD18(void);
extern void func_0027B858(void);
extern int func_00124E08(int);
extern int func_001250E8(int);
extern int func_0011EED8(char *);
extern int func_0011EEA0(void);
extern void func_0026FEB8(char *);
extern void func_0011CF78(int);
extern void func_0011F5E0(void);
extern void func_0011E7A0(void);
extern void func_0011F628(void);
extern void func_0011EAC8(void);
extern void func_001252E0(int);
extern void func_0011E0A0(void);
extern void func_00133A28(int, int, void *);
extern void func_0011AEA0(int);
extern void func_00298BB8(void *);
extern void func_002FC070(void *);
/* Takes an address in retail's call, though its body (src/core/001339F0.c) never reads it. */
extern void func_00133A78(void *);
extern void func_0029D4D0(void *, void *);
extern int func_0011E828(int, int, int);
extern void func_0011E8A8(int);
extern void func_002EEBC8(void);
extern void func_002B8548(void);
extern void func_0029AE48(void);
extern void func_0027A9F0(void);
extern void func_0027AB40(void);
extern void func_002E48E8(void);
extern void func_002B68C8(void);
extern void func_002940C0(void);
extern int func_00131628(void);
extern void func_00282A60(void *, int, int);
extern void func_00126288(void *, int, int, int, int, int, int, int);
extern void func_001265B0(void *, void *);
extern void func_001244B8(int, int);
extern void func_0026FE48(void);
extern void func_002889B8(void *);

extern char D_001A9048[];   /* path of the IOP reboot image */
extern char D_001A9060[];   /* "Rebooted IOP" */
extern char D_001A9070[];   /* "loaded irx modules" */
extern char D_0010E9E0[];
extern char D_001BB000[];
extern char D_001BAD40[];
extern int D_001A7BB8[] __attribute__((sda));
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int D_001A7290[] __attribute__((sda));
extern int D_001A72F8 __attribute__((sda));
extern int D_001A72FC __attribute__((sda));
extern int D_00152C00[];

typedef struct {
    char pad000[0x32C];
    int base;
    char pad330[8];
    int offset;
    int count;
} Toc_00290C60;
extern Toc_00290C60 D_0014B540;

/* The boot's one-time setup, RAC1's InitOnce: reboots the IOP, sets up video and the VU, loads
   the compressed module table from the disc and starts the IOP modules in it, sets up the
   memory areas and sound, and clears a small image. */
void func_00290C60(void)
{
    char buffer[2048];
    char *image;
    char *scratch;
    int *state;
    int handle;
    int mode;

    func_00124418();
    func_00126F60(1);
    D_001A7BB8[0] = 0;
    D_001A7BB0[1] = 0;
    func_00284000();
    func_0029D050();
    func_0027B440(1);
    func_0011AE70(3);
    func_00126DC0(func_001339B0);
    func_002FC138();
    func_00290B48();
    func_002FC138();
    func_002FC1D8();
    func_002FCD18();
    func_0027B858();
    func_00124E08(0);
    func_001250E8(0);
    while (!func_0011EED8(D_001A9048)) {
    }
    while (!func_0011EEA0()) {
    }
    func_0026FEB8(D_001A9060);
    func_0011CF78(0);
    func_0011F5E0();
    func_0011E7A0();
    func_0011F628();
    func_0011EAC8();
    func_00124E08(0);
    func_001250E8(0);
    func_001252E0(2);
    func_0011E0A0();
    func_00133A28(1000, 1, buffer);
    func_0011AEA0(0);
    D_001A7B90 = 0;
    func_00298BB8(buffer);
    func_002FC070(D_0010E9E0);
    func_00133A78(D_02000000 - 0xFE8C);
    image = (char *)((((unsigned int)ref_L00_00290B48_00 + 0x3FFF) & ~0x3FFF) + 0x2C0000);
    scratch = D_02000000 - 0x8000 - (D_0014B540.count << 11);
    func_00133A28(D_0014B540.offset + D_0014B540.base, D_0014B540.count, scratch);
    func_0011AEA0(0);
    func_0029D4D0(scratch, image);
    func_0011AEA0(0);
    handle = func_0011E828(1, 0x55730, 0);
    func_00290AB0(*(int *)(image + 0x50) + (int)image, *(int *)(image + 0x54), handle);
    func_00290AB0(*(int *)(image + 0x48) + (int)image, *(int *)(image + 0x4C), handle);
    func_00290AB0(*(int *)(image + 0x18) + (int)image, *(int *)(image + 0x1C), handle);
    func_00290AB0(*(int *)(image + 0x20) + (int)image, *(int *)(image + 0x24), handle);
    func_00290AB0(*(int *)(image + 0x28) + (int)image, *(int *)(image + 0x2C), handle);
    func_00290AB0(*(int *)(image + 0x30) + (int)image, *(int *)(image + 0x34), handle);
    func_00290AB0(*(int *)(image + 0x38) + (int)image, *(int *)(image + 0x3C), handle);
    func_00290AB0(*(int *)(image + 0x40) + (int)image, *(int *)(image + 0x44), handle);
    func_00290AB0(*(int *)(image + 0x40) + (int)image, *(int *)(image + 0x44), handle);
    func_00290AB0(*(int *)(image + 0x58) + (int)image, *(int *)(image + 0x5C), handle);
    func_0011E8A8(handle);
    func_0026FEB8(D_001A9070);
    func_002EEBC8();
    func_001250E8(0);
    func_002B8548();
    state = (int *)D_001BAEC0;
    D_001A7290[0] = -1;
    D_001A7290[12] = -1;
    D_001A72F8 = 0;
    D_001A72FC = 0x60000;
    D_001A7290[28] = 0x70000;
    D_001A7290[29] = 0xB0000;
    D_001A7290[30] = 0x140000;
    D_001A7290[31] = 0x1D0000;
    D_001A7290[32] = 0x1E0000;
    D_001A7290[1] = state[0x78 / 4];
    D_00152C00[12] = -1;
    D_00152C00[6] = -1;
    func_001250E8(0);
    func_0029AE48();
    func_0027A9F0();
    func_0027AB40();
    func_002FC1D8();
    func_001250E8(0);
    func_002E48E8();
    func_002B68C8();
    func_002940C0();
    mode = func_00131628();
    switch (mode) {
    case 1:
        D_001A7BB0[1] = mode;
        break;
    case 0:
    case 2:
        D_001A7BB0[1] = 0;
        break;
    }
    func_00282A60(D_001BB000, 0x80808080, 0x100);
    func_00126288(buffer, 0x3FFB, 1, 0, 0, 0, 8, 8);
    func_0011AEA0(0);
    func_001265B0(buffer, D_001BB000);
    func_001244B8(0, 0);
    func_0026FE48();
    T1_MODE = 0x82;
    T1_COUNT = 0;
    func_002889B8(D_001BAD40);
}

void func_00291108(void)
{
  func_00278EB0();
  return;
}

extern void func_00278F80(void);

void func_00291128(void) {
    func_00278F80();
}


/* func_00291158 is matched in its own unit, 00291158.c. */

/* func_00291268 is in 00290A40-g8.c. */


void func_002912F0(void)
{
}


static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

typedef struct {
    float color[3];
    float radius;
    float position[3];
    float range;
} LightDef;

typedef struct {
    char pad0[0xC];
    char *buffer;
    int active;
    char pad14[0x30 - 0x14];
} LightSlot;

extern float func_00283CE0(int);
extern char D_001C2DC0[];
extern char D_001C2B40[];
extern char D_001C2C40[];
extern void func_00282A88(void *, int);

int func_00291308(float *position, float range, float radius, int color)
{
    LightDef *def;
    LightSlot *slot;
    int i;

    for (i = 0; i < 8; i++) {
        if (((LightSlot *)D_001C2C40)[i].active == 0) {
            break;
        }
    }
    if (i == 8) {
        return -1;
    }
    def = (LightDef *)(D_001C2B40 + (i << 5));
    slot = (LightSlot *)(D_001C2C40 + i * 0x30);
    qcopy(def->position, position);
    def->range = range;
    def->color[0] = func_00283CE0(color & 0xFF) * 0.0078125f;
    def->color[1] = func_00283CE0((color >> 8) & 0xFF) * 0.0078125f;
    def->color[2] = func_00283CE0((color >> 16) & 0xFF) * 0.0078125f;
    def->radius = radius;
    func_00282A88(slot, 0x30);
    slot->active = 1;
    slot->buffer = D_001C2DC0 + (i << 10);
    return i;
}


extern void func_00291788(int index);
extern void func_00282A88(void *, int);
extern char D_001C2B40[];
extern char D_001C2C40[];

void func_00291450(int index) {
    if ((unsigned int)index >= 8)
        return;
    func_00291788(index);
    func_00282A88((void *)(D_001C2B40 + (index << 5)), 0x20);
    func_00282A88((void *)(D_001C2C40 + index * 0x30), 0x30);
}

/* func_002914B8 is in 00290A40-g16.c. */

void func_00291640(int index)
{
    unsigned char *record = ref_L00_00291640_01 + index * 0x30;
    unsigned short *position = *(unsigned short **)(record + 0xC);
    unsigned short *end = position + 0x200;
    LightDef *def = &((LightDef *)D_001C2B40)[index];
    ParserScratch *scratch = (ParserScratch *)def->position;
    ParserScratch scratchCopy;
    qcopy(&scratchCopy, scratch);

    if (position < end) {
        *(short *)record = 0;
        position = func_002F4FA0(position, end, index, scratch);
        *(short *)(record + 2) = (position - *(unsigned short **)(record + 0xC));
        if (position < end) {
            *(short *)(record + 4) = (position - *(unsigned short **)(record + 0xC));
            position = func_002E31E8(position, end, index, scratch);
            *(short *)(record + 6) = (position - *(unsigned short **)(record + 0xC)) - *(unsigned short *)(record + 4);
            if (position < end) {
                *(short *)(record + 8) = (position - *(unsigned short **)(record + 0xC));
                position = func_002F0B78(position, end, index, scratch);
                *(short *)(record + 0xA) = (position - *(unsigned short **)(record + 0xC)) - *(unsigned short *)(record + 8);
            }
        }
    }
}
