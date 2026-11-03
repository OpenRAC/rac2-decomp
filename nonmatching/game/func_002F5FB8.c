/* 2 November 2026:
 * Correct the ignored integer returns of func_002B4B70, func_00288A00 and func_002B49E0. The
 * current matched func_002EF010 returns unsigned long (64 bits on EE); explicitly narrow its
 * result before the observed 32-bit index shift. This qualified declaration experiment emits
 * 1192/1184 bytes, 0/28 US placements, rather than the old 1184-byte draft with an int
 * declaration. The packet frame and descriptor lifetimes remain unresolved; no complete match.
 */
/* sol-high, v0961, USA v1.01: 1184/1184 bytes, 0/28 places.
 * Game -O2 -G8 -ffunction-sections. The target frame is 0xD0, this draft
 * uses 0xC0; allocation, startup spills, descriptor-base rematerialization
 * and some loop scheduling remain different. No linked build was run.
 * This replaces the 1152-byte draft with complete, corrected loop processing.
 * Crucially, the old ref_15 volatile read was spurious: boot gp+0x3220
 * and absolute 0x1B2210 both reference ref_10, the descriptor pointer.
 * Its ordinary reload naturally fills the backward branch's delay slot.
 * The result XOR preserves retail's test; staged signed-long GS fields
 * preserve its separate constants. Next useful work is the lifetimes of
 * textureIndex, the two aligned buffers and the descriptor/frame bases.
 * All required declarations follow. Use a -g8.c sibling when retrying.
 */
#include "common.h"
extern void func_002FC1D8(void);
typedef unsigned long long U64_5FB8;
typedef struct { U64_5FB8 packet; unsigned short tex0, tex1; short width, height; } Display_5FB8;
typedef struct { int frame; short *frames; char pad[0x2C]; int field34, active, mode; } Stream_5FB8;
extern int ref_L00_002F5FB8_00, ref_L00_002F5FB8_01;
extern char ref_L00_002F5FB8_04[];
extern int ref_L00_002F5FB8_05[];
extern int ref_L00_002F5FB8_06[];
extern Display_5FB8 ref_L00_002F5FB8_07[];
extern char *ref_L00_002F5FB8_08;
extern int *ref_L00_002F5FB8_10;
extern int ref_L00_002F5FB8_12;
extern int ref_L00_002F5FB8_13 __attribute__((sda));
extern int ref_L00_002F5FB8_14 __attribute__((sda));
extern int ref_L00_002F5FB8_16[];
extern int D_001393E0[];
extern int D_0014B540[];
extern char D_001339B0[];
extern void func_0029CC98(int, int);
extern void func_00288BB8(void *);
extern int func_002B4B70(int,int);
extern void func_002FC3C0(unsigned long);
extern int func_00126288(void *,short,short,short,short,short,short,short);
extern void func_0011AEA0(int);
extern int func_001265B0(void *,void *);
extern int func_001244B8(int,int);
extern void func_002E5FE0(void);
extern void func_002B7170(void);
extern int func_00133580(int);
extern void func_00298F00(void);
extern int func_002B7C80(char *,int,int);
extern int func_0034EF58(void *,void *,char *,char *,int,int);
extern int func_00288A00(void *,int *,int *);
extern unsigned long func_002EF010(int);
extern void func_00126DC0(void *);
extern void func_002F0FA0(void);
extern int func_002B49E0(int,int,int,int,unsigned char *);
void func_002F5FB8(void)
{
    long packet[12] __attribute__((aligned(16)));
    long low, dimensions, high;
    long base;
    long highFlags;
    int textureIndex;
    int frame, status, done, result;
    int first, second, nextFrame;
    int *sectors;
    int *sizes;
    Display_5FB8 *displays;
    char *destination;
    Display_5FB8 *display;
    Stream_5FB8 *stream;
    if (ref_L00_002F5FB8_00 == 0) {
        func_0029CC98((int)ref_L00_002F5FB8_04,-1);
        func_00288BB8(ref_L00_002F5FB8_05);
        func_002B4B70(0,0);
        return;
    }
    second = ref_L00_002F5FB8_06[5];
    first = ref_L00_002F5FB8_06[3];
    destination = (char *)(second + 0xE0000);
    displays = ref_L00_002F5FB8_07;
    display = &displays[2];
    func_002FC3C0(1);
    base = 0x3F70;
    func_00126288(packet,(short)base,(short)((1 << display->width) >> 6),0x13,0,0,(short)(1 << display->width),(short)(1 << display->height));
    func_0011AEA0(0);
    func_001265B0(packet,ref_L00_002F5FB8_08 + display->tex0 * 16);
    func_001244B8(0,0);
    func_00126288(packet,0x3F6C,1,0,0,0,16,16);
    func_0011AEA0(0);
    func_001265B0(packet,ref_L00_002F5FB8_08 + display->tex1 * 16);
    func_001244B8(0,0);
    highFlags = 0x7ED8400000000L;
    low = ((long)((1 << display->width) >> 6) << 14) | (long)base;
    dimensions = ((long)display->width << 26) | 0x1300000L;
    low = low | dimensions;
    low = low | ((long)display->height << 30);
    high = low | highFlags;
    ref_L00_002F5FB8_07[2].packet = high | 0x8000000000000000ULL;
    func_0011AEA0(0);
    func_002E5FE0();
    func_002B7170();
    func_00133580(0);
    while (D_001393E0[0x15C/4] >= 3 || D_001393E0[0x164/4] >= 0) func_00298F00();
    frame = 0;
    status = -1;
    sectors = D_0014B540 + 2; sizes = D_0014B540 + 3;
    first += 63;
    second += 63;
    done = 0;

    textureIndex = 2;
    do {
        int *descriptor;
        descriptor = ref_L00_002F5FB8_10;
        if (descriptor != 0 && descriptor[0] != 0) {
            func_002B7C80(destination,descriptor[0] + D_0014B540[1],(descriptor[1] + 2047)/2048);
            ref_L00_002F5FB8_16[0x34/4] = 0;
            ref_L00_002F5FB8_16[0x4C/4] = (int)destination;
        } else {
            ref_L00_002F5FB8_16[0x4C/4] = 0;
            ref_L00_002F5FB8_16[0x34/4] = 0;
        }
        stream = (Stream_5FB8 *)ref_L00_002F5FB8_05;
        result = func_0034EF58((void *)ref_L00_002F5FB8_01,(void *)ref_L00_002F5FB8_00,(char *)(first & -64),(char *)(second & -64),ref_L00_002F5FB8_13,ref_L00_002F5FB8_12 != 0);
        stream->mode = (result ^ 1) == 0 ? 1 : stream->mode;
        if (result != 0) { stream->mode = 1; func_00288BB8(stream); }
        if (ref_L00_002F5FB8_05[0] != 0) {
            ref_L00_002F5FB8_05[0]++;
            if (ref_L00_002F5FB8_05[0] >= 25) ref_L00_002F5FB8_05[0] = 1;
            nextFrame = stream->frames[ref_L00_002F5FB8_05[0]];
        } else {
            if (stream->active == 0) { done = 1; goto end_frame; }
            func_00288A00(stream,&frame,&status);
            if (status != 0) goto bad_status;
            nextFrame = frame;
        }
        {
            int offset = ((int)func_002EF010(nextFrame) << 4) | 8;
            ref_L00_002F5FB8_01 = *(int *)((char *)sectors + offset) + D_0014B540[1];
            ref_L00_002F5FB8_14 = *(int *)((char *)sizes + offset);
        }
        goto end_frame;
bad_status:
        if (status == 1) done = 1;
end_frame:

    } while (!done);
    func_00133580(0);
    func_00126DC0(D_001339B0);
    func_001244B8(0,0);
    displays = ref_L00_002F5FB8_07;
    display = &displays[textureIndex];
    func_001265B0(packet,ref_L00_002F5FB8_08 + display->tex1 * 16);
    func_001244B8(0,0);
    func_002F0FA0();
    display->packet = 0;
    func_002FC1D8();
    if (result == 0 && status == 1) func_002B49E0(2,2,frame,0,0);
    else func_002B4B70(0,0);
}

