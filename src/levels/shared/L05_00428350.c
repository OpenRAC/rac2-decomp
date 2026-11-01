#include "include_asm.h"
#include "common.h"
typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct { Vector row[3]; Vector position; } Frame;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern Vector D_0018A0E0;
extern Vector ref_L05_0042F4E8_01[4];
extern void func_00281DE8(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027C768(int, float *, float *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);

extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern void func_00282DD8(char *, char *, char *);
extern void func_00280B90(char *, int, int);
extern char ref_L05_0042F4E8_00[];


extern int D_001A7350 __attribute__((sda));

extern int D_001A7354 __attribute__((sda));

extern void func_2FC560(char *out, char *src);

extern int func_307778(float value);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_14(char *target, char *first, char *local);

extern char *D_L05_001B9710;

extern int func_00282978(void *);

extern void func_0029F338(void *);

/* The call target and the callback it registers are not the same function in
   every level this unit is placed in, so neither name may state an address. */
extern void ref_L05_0042E4E8_00(void);

extern int ref_L05_0042E4E8_01(void *, void *);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

/* func_L05_00428350 is defined in L05_00428350-g8.c. */

/* func_L05_00428518 is defined in L05_00428518-g8.c. */

/* func_L05_00428AC8 is defined in L05_00428AC8-g8.c. */



INCLUDE_ASM("asm/levels", func_L05_0042AFE0);

INCLUDE_ASM("asm/levels", func_L05_0042B2C0);

/* func_L05_0042BB10 is defined in L05_0042BB10-g8.c. */

extern char *func_328508(char *);

extern void func_32AF08(char *);

extern void func_3073E0(char *, char *);

extern void func_3065F8(char *);

extern void func_3066A0(char *, char *, float);

extern void func_306630(char *, char *, char *);

extern int func_2F9888(char *, int, char *, int, float);

extern void func_2DCB60(int, int);

extern void func_2EB6E8(void);

extern int D_00221D94;

extern int D_001A79F0;

extern char *D_001B1EC4;

extern char *D_001B251C;

extern char D_00189E20[];

extern char D_0019B2E8[];

extern char D_001B3620[];

extern char D_001BFB30[];

#ifndef RAC2_T_TI128_15C4FA
#define RAC2_T_TI128_15C4FA
typedef int TI128 __attribute__((mode(TI)));
#endif

/* Creates the 0x1226 object, seeds its flags from the caller's two floats and copies the
   caller's quadword into the object's transform slot. */
char *func_L05_0042BCE0(char *a0, char *a1, float f12, float f13)
{
    char *obj = func_328508((char *)0x1226);

    if (obj != 0) {
        char *sub;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0x1FF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * f12;
        *(unsigned short *)(obj + 0x34) =
            (*(unsigned short *)(obj + 0x34) & 0xFFF8) | 0x100;
        sub = *(char **)(obj + 0x68);
        qcopy(obj + 0x10, a0);
        func_3073E0(a1, obj + 0xC0);
        *(float *)(sub + 0x10) = f13;
        func_32AF08(obj);
    }
    return obj;
}

/* func_L05_0042BDB0 is defined in L05_0042BDB0-g8.c. */

INCLUDE_ASM("asm/levels", func_L05_0042C928);

/* Two bound helpers at the node's +0x68; the second call registers a callback
   and the context, the other branch calls a one-argument helper. */
void func_L05_0042E4E8(char *a0)
{
    char *context = a0;
    char *node = *(char **)(context + 0x68);

    if (func_00282978(node) == 0) {
        func_00282978(node + 4);
        ref_L05_0042E4E8_01(&ref_L05_0042E4E8_00, context);
    } else {
        func_0029F338(context);
    }
}

/* Draws a camera-facing quad, then redraws it with jittered, clamped screen-projected UVs. */
void func_L05_0042F4E8(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    func_00281DE8(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    func_00282CF0((char *)&frame.row[0], (char *)(ref_L05_0042F4E8_00 + 0x140), (char *)&frame.position);
    func_00282F20((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    func_00282DD8((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    func_00282F20((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    func_00282DD8((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        func_002833F0(scratch.u.rotation, &scratch.angles);
        func_00283738(frame.row, frame.row, scratch.u.rotation);
    }
    func_00282D30(&scratch.angles, &frame.row[0], offset);
    func_00282CC0(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = ref_L05_0042F4E8_01;
        count = 3;
        do {
            func_00282D30(vertex, corner, size);
            ++corner;
            --count;
            func_002830C0(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    func_002FC560(0x47, 0x31001ULL);
    func_00280B90((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                func_00282CC0(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        func_00282D30(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            func_00282CF0((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            func_00282D30(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            func_00282CC0(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            func_0027C768((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            func_0027C768((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (func_002A77E0(1) == 0) {
                packet.uv[i][0] += func_002A7878(-jitter, jitter);
                packet.uv[i][1] += func_002A7878(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    func_00281DE8(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    func_002FC560(0x47, 0x33001ULL);
    func_00280B90((char *)&packet, 0, 0);
    func_002FC560(0x47, 0x5360bULL);
}


/* func_L05_00430318 is defined in x-qcopy.c. */

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L05_00430BF0(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_14((char *)&object[index - 1], (char *)&object[index - 2], local);
}


/* Creates the 0x10E3 object and copies the caller's transforms into it. */
/* func_L05_00432080 is defined in L05_00432080.c. */

/* func_L05_00432158 is matched in its own unit, src/levels/shared/L05_00432158.c (-frac2-qcopy -frac2-qcopy-barrier -fno-strength-reduce). */


INCLUDE_ASM("asm/levels", func_L05_00441D40);


/* func_L05_00441F30 is defined in L05_00441F30-g8.c. */

/* func_L05_00442398 is defined in L05_00442398-g8.c. */

/* func_L05_00442560 is defined in L05_00442560-q.c. */

/* func_L05_00442720 is matched in L05_00442720.c (built with -mno-split-addresses). */

/* func_L05_004427A8 is defined in L05_004427A8-flags.c. */


/* func_L05_00442880 is defined in L05_00428350-g8.c. */

INCLUDE_ASM("asm/levels", func_L05_00442A58);

/* func_L05_004431A0 is defined in L05_004431A0.c. */

INCLUDE_ASM("asm/levels", func_L05_004432E0);

/* func_L05_00443740 is defined in L05_00443740-g8.c. */

/* Folds the object's two turn rates out of its parent's rotation into the moby, then
   rebuilds the three orientation blocks the driver reads. */
/* func_L05_00443C18 is matched in L05_00443C18.c (built with -g). */

INCLUDE_ASM("asm/levels", func_L05_00443D08);

INCLUDE_ASM("asm/levels", func_L05_00444840);

/* Converts a two-float record to the coordinate pair the level's bias words expect. */
void func_L05_00444D60(char *a0, int *a1, int *a2, int a3)
{
    float local[2];
    float bias;

    func_2FC560((char *)local, a0);
    bias = (float)D_001A7350;
    *a1 = func_307778((local[0] - bias) * 0.0625f);
    bias = (float)D_001A7354;
    *a2 = func_307778((local[1] - bias) * 0.0625f) + a3;
}


/* func_L05_00444FD0 is in L05_00444FD0.c. */

/* func_L05_00445338 is defined in L05_00445338-g8.c. */

/* Reads a state word from a fixed global; unless its +0x86 halfword is 0x19 it
   returns 0, otherwise it reports whether the signed halfword reached through
   the pointer at +0x70, offset +0xD8, is non-zero. */
int func_L05_00445980(void)
{
    char *base = D_L05_001B9710;

    if (*(short *)(base + 0x86) != 0x19)
        return 0;
    return *(short *)(*(char **)(base + 0x70) + 0xD8) != 0;
}

INCLUDE_ASM("asm/levels", func_L05_004459B0);

/* func_L05_00445B58 lives in L05_00445B58.c. */

/* func_L05_00445C38 lives in L05_00445C38-g8.c. */

/* func_L05_00445B58 is defined in L05_00445B58.c. */

/* func_L05_00445C38 is defined in L05_00445C38-g8.c. */

/* func_L05_00445D60 is defined in L05_00445D60-g8.c. */
