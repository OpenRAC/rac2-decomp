/* func_L01_003CAFE0 needs -G16 small data, quadword copies and -g line labels
 * (the nop pairs before both div.s); -frac2-hazard-labels keeps the second
 * division guard's label on its padding.  The frame entries are block-local,
 * so local allocation ties them to their index chains. */
#include "common.h"


typedef unsigned int Quad __attribute__((mode(TI)));
extern unsigned char D_L01_001BD9C0[];
typedef struct { u8 prefix[8]; u16 first, second; u32 other; } FrameEntry;
extern FrameEntry D_L01_001BE0C0[];
extern unsigned char D_L01_00297B50[], D_L01_0026A050[], D_L01_001AC740[];
extern unsigned char D_L01_001A8EF0[];
extern unsigned char D_L01_001B0270[] SDATA(D_L01_001B0270);
extern unsigned char D_L01_001B0240[] SDATA(D_L01_001B0240);
/* The camera position follows its view matrix by 0x100, as in RAC1 CameraSystem. */
typedef struct { float matrix[16]; u8 unknown40[0xc0]; float pos[4]; } CameraView;
extern CameraView D_L01_001B93C0[];
extern unsigned char *D_L01_001B2004;
extern unsigned char *D_L01_001B2CC8[] __attribute__((sda));
extern int D_L01_001B2054[] __attribute__((sda));
extern int D_L01_001B2088, D_L01_001B209C;
extern float D_L01_001B31D4, D_L01_001B31D8, D_L01_001B31DC;
extern float D_L01_001B31E0 __attribute__((sda));
extern float D_L01_001B0330 __attribute__((sda)), D_L01_001B0334 __attribute__((sda));
extern float D_L01_001B0338 __attribute__((sda)), D_L01_001B033C __attribute__((sda));
extern int D_L01_001B0340 __attribute__((sda)), D_L01_001B0344 __attribute__((sda)), D_L01_001B0348 __attribute__((sda));
extern int D_L01_001B034C __attribute__((sda)), D_L01_001B0350 __attribute__((sda)), D_L01_001B0354 __attribute__((sda));
extern int D_L01_001B0358 __attribute__((sda)), D_L01_001B0360 __attribute__((sda)), D_L01_001B0364 __attribute__((sda));
extern int D_L01_001B0368 __attribute__((sda));
extern unsigned char *D_L01_001B035C __attribute__((sda)), *D_L01_001B036C __attribute__((sda));
extern Quad D_L01_001B02E0 __attribute__((sda)), D_L01_001B02F0 __attribute__((sda));
extern unsigned char D_L01_001B0300[] SDATA(D_L01_001B0300);
extern int D_001A72D0;
extern unsigned short D_0010FFB0[];
extern unsigned char D_0010FFC0[];
extern void func_0027AB40(void), func_00279D18(void);
extern void func_00282AB0(void *, void *, int), func_00282B50(void *, void *, int);
extern void func_002FC410(unsigned int, unsigned int);
extern void func_00283388(float *);
extern void func_00282D30(float *, float *, float);
extern void func_00283788(float *, float *, float *);
extern void func_L01_003042AC(unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned char *, int, float);
#define CONTEXT_FLOAT(offset) (*(float *)(context + (offset)))
#define CONTEXT_INT(offset) (*(int *)(context + (offset)))
#define PACKET_LONG(ptr,offset) (*(u64 *)((ptr) + (offset)))
void func_L01_003CAFE0(void)
{
    float matrix[16] __attribute__((aligned(16)));
    unsigned char *packet;
    u8 *context = D_L01_001BD9C0;
    int mode = D_L01_001B2054[0];
    D_L01_001B31D4 = CONTEXT_FLOAT(0x218);
    D_L01_001B31D8 = CONTEXT_FLOAT(0x21c);
    D_L01_001B31DC = CONTEXT_FLOAT(0x228);
    D_L01_001B31E0 = CONTEXT_FLOAT(0x22c);
    if (mode != 1) {
        CONTEXT_FLOAT(0x218) = D_L01_001B0330;
        CONTEXT_FLOAT(0x21c) = D_L01_001B0334;
        CONTEXT_FLOAT(0x228) = D_L01_001B0338;
        CONTEXT_FLOAT(0x22c) = D_L01_001B033C;
    }
    func_0027AB40();
    func_00279D18();
    {
        u8 *header = D_L01_001B2CC8[0];
        qcopy(header, &D_L01_001B02E0);
        packet = header + 0x10;
    }
    D_L01_001B2CC8[0] = packet;
    func_00282AB0(packet, D_L01_00297B50, 0xa0);
    D_L01_001B2CC8[0] += 0xa0;
    PACKET_LONG(packet,0x20) = ((u64)D_L01_001B034C << 32) | 100;
    PACKET_LONG(packet,0x30) = (u64)((D_001A72D0 >> 8) | 0x18100000) | 0x580000000UL;
    PACKET_LONG(packet,0x40) = (s32)((u32)D_L01_001B0340 | ((u32)D_L01_001B0344 << 8) | ((u32)D_L01_001B0348 << 16));
    if (D_L01_001B2054[0] == 1)
        PACKET_LONG(packet,0x40) = (s32)((u32)CONTEXT_INT(0x230) | ((u32)CONTEXT_INT(0x234) << 8) | ((u32)CONTEXT_INT(0x238) << 16));
    PACKET_LONG(packet,0x50) = ((u64)((long)D_001A72D0 >> 8) << 32) | 0x1000000000000UL;
    PACKET_LONG(packet,0x90) = 0x5360a;
    if (D_L01_001B034C < 97) PACKET_LONG(packet,0x90) = 0x5370b;
    {
        FrameEntry *entry0, *entry1;
        int frame;
        float fraction;
        int ticks = D_L01_001B2088;
        int interval = D_L01_001B0350;
        fraction = (float)ticks / (float)interval;
        frame = ticks / interval;
        fraction -= (float)frame;
        entry0 = D_L01_001BE0C0 + (D_L01_001B0354 + frame % D_L01_001B0358);
        entry1 = D_L01_001BE0C0 + (D_L01_001B0354 + (frame + 1) % D_L01_001B0358);
        {
            /* Each entry's second index is read before its first. */
            u16 idx1 = entry0->second;
            u16 idx0 = entry0->first;
            u16 idx3 = entry1->second;
            u16 idx2 = entry1->first;
            u8 *src0 = D_L01_001B2004 + idx0 * 16;
            u8 *src1 = D_L01_001B2004 + idx1 * 16;
            u8 *src2 = D_L01_001B2004 + idx2 * 16;
            u8 *src3 = D_L01_001B2004 + idx3 * 16;
            PACKET_LONG(D_L01_001B035C,0) = 0x800000000000400UL;
            PACKET_LONG(D_L01_001B035C,8) = 0;
            func_L01_003042AC(D_L01_001B035C + 0x10, src0, src1, src2, src3, 4096, fraction);
        }
    }
    {
        FrameEntry *entry0, *entry1;
        int frame;
        float fraction;
        int ticks = D_L01_001B2088;
        int interval = D_L01_001B0360;
        D_001A72D0 += 0x4000;
        fraction = (float)ticks / (float)interval;
        frame = ticks / interval;
        fraction -= (float)frame;
        entry0 = D_L01_001BE0C0 + (D_L01_001B0364 + frame % D_L01_001B0368);
        entry1 = D_L01_001BE0C0 + (D_L01_001B0364 + (frame + 1) % D_L01_001B0368);
        {
            /* Each entry's second index is read before its first. */
            u16 idx1 = entry0->second;
            u16 idx0 = entry0->first;
            u16 idx3 = entry1->second;
            u16 idx2 = entry1->first;
            u8 *src0 = D_L01_001B2004 + idx0 * 16;
            u8 *src1 = D_L01_001B2004 + idx1 * 16;
            u8 *src2 = D_L01_001B2004 + idx2 * 16;
            u8 *src3 = D_L01_001B2004 + idx3 * 16;
            PACKET_LONG(D_L01_001B035C,0) = 0x800000000000400UL;
            PACKET_LONG(D_L01_001B035C,8) = 0;
            func_L01_003042AC(D_L01_001B036C, src0, src1, src2, src3, 4096, fraction);
        }
    }
    {
        u8 *header = D_L01_001B2CC8[0];
        qcopy(header, &D_L01_001B02F0);
        *(unsigned char **)(header + 4) = D_L01_001B035C;
    }
    D_L01_001B2CC8[0] += 0x10;
    func_00282B50(D_L01_001B2CC8[0], D_L01_001B0300, 0x30);
    D_L01_001B2CC8[0] += 0x30;
    if (D_L01_001B209C != 6) {
        func_002FC410((unsigned int)D_0010FFC0, D_0010FFB0[0]);
        D_L01_001B209C = 6;
    }
    packet = D_L01_001B2CC8[0];
    {
        unsigned char *tmpl = D_L01_0026A050;
        *(unsigned char **)(tmpl + 4) = D_L01_001AC740;
        func_00282B50(packet, tmpl, 0x50);
    }
    D_L01_001B2CC8[0] += 0x50;
    *(unsigned char **)(packet + 0x24) = D_L01_001B2CC8[0];
    *(unsigned char **)(packet + 0x34) = D_L01_001B2CC8[0];
    *(unsigned char **)(packet + 0x44) = D_L01_001B2CC8[0] + 0x60;
    func_00282B50(D_L01_001B2CC8[0], context, 0x60);
    D_L01_001B2CC8[0] += 0x60;
    func_00283388(matrix);
    func_00282D30(matrix + 12, D_L01_001B93C0[0].pos, -1024.0f);
    matrix[15] = 1.0f;
    func_00283788(matrix, D_L01_001B93C0[0].matrix, matrix);
    func_00282B50(D_L01_001B2CC8[0], D_L01_001A8EF0, 0x20);
    *(unsigned char **)(D_L01_001B2CC8[0] + 4) = D_L01_001B2CC8[0] + 0x20;
    func_00282B50(D_L01_001B2CC8[0] + 0x20, matrix, 0x40);
    D_L01_001B2CC8[0] += 0x60;
    func_00282AB0(D_L01_001B2CC8[0], D_L01_001B0270, 0x20);
    D_L01_001B2CC8[0] += 0x20;
    func_00282AB0(D_L01_001B2CC8[0], D_L01_001B0240, 0x20);
    D_L01_001B2CC8[0] += 0x20;
}
