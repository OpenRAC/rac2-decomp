#include "common.h"

/* func_US2_002F6E10, the USA v2.00 copy of func_002F5FB8: the same C, where the display slot's
   width and height become bytes followed by a pixel format short at 0xE (passed to the upload
   and put in TEX0 in place of 0x13), the TEX0 word sets bit 62 instead of bit 63, and the
   queued dialog voice is cleared before waiting for the sound streams. */
typedef struct { int sector; int size; } TocFile_002F5D40;
typedef struct {
    int header;
    int base;
    TocFile_002F5D40 files[0];
} Toc_002F5D40;
extern char D_0014B540[];
extern int func_002EF010(int);
extern void func_002FC1D8(void);
/* The dialog voice block: v2.00 clears the queued voice id before the movie plays. */
typedef struct { char pad[0x24]; int pendingVoice; } Voice_6E10;
extern Voice_6E10 D_001A63A8;

/* Plays the current FMV (D_001B220C, set up by func_002F5E20). With no stream it shows the
   message and ends the movie state. Otherwise it uploads the two movie textures into display
   slot 2, sets the slot's TEX0 word, waits for the sound streams to idle, then decodes frames into
   the two 64-aligned buffers until the stream or the scripted frame list ends, loading each
   chunk's sector and size from the table of contents. Finally it restores the texture, clears
   the slot and either chains the next scene or returns to the game. */
typedef unsigned long long U64_5FB8;
typedef struct { U64_5FB8 packet; unsigned short tex0, tex1; unsigned char width, height; short psm; } Display_5FB8;
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
extern char D_001339B0[];
extern void func_US2_0029DAD0(int, int);
extern void func_00288BB8(void *);
extern int func_002B4B70(int,int);
extern void func_002FC3C0(int);
extern int func_00126288(void *,short,short,short,short,short,short,short);
extern void func_0011AEA0(int);
extern int func_001265B0(void *,void *);
extern int func_001244B8(int,int);
extern void func_002E5FE0(void);
extern void func_002B7170(void);
extern int func_00133580(int);
extern void func_US2_00299CF0(void);
extern int func_002B7C80(char *,int,int);
extern int func_0034EF58(void *,void *,char *,char *,int,int);
extern int func_00288A00(void *,int *,int *);
extern void func_00126DC0(void *);
extern void func_002F0FA0(void);
extern int func_002B49E0(int,int,int,int,unsigned char *);
void func_US2_002F6E10(void)
{
    long packet[12] __attribute__((aligned(16)));
    long low, high;
    long base;
    long highFlags;
    int textureIndex;
    int frame, status, done, result;
    int first, second, index;
    Display_5FB8 *displays;
    char *destination;
    Display_5FB8 *display;
    Stream_5FB8 *stream;
    Display_5FB8 *slot;
    if (ref_L00_002F5FB8_00 == 0) {
        func_US2_0029DAD0((int)ref_L00_002F5FB8_04,-1);
        func_00288BB8(ref_L00_002F5FB8_05);
        func_002B4B70(0,0);
        return;
    }
    first = ref_L00_002F5FB8_06[3];
    second = ref_L00_002F5FB8_06[5];
    destination = (char *)(second + 0xE0000);
    func_002FC3C0(1);
    textureIndex = 2;
    displays = ref_L00_002F5FB8_07;
    display = &displays[textureIndex];
    base = 0x3F70;
    func_00126288(packet,(short)base,(short)((1 << display->width) >> 6),display->psm,0,0,(short)(1 << display->width),(short)(1 << display->height));
    func_0011AEA0(0);
    func_001265B0(packet,ref_L00_002F5FB8_08 + display->tex0 * 16);
    func_001244B8(0,0);
    func_00126288(packet,0x3F6C,1,0,0,0,16,16);
    func_0011AEA0(0);
    func_001265B0(packet,ref_L00_002F5FB8_08 + display->tex1 * 16);
    func_001244B8(0,0);
    highFlags = 0x7ED8400000000L;
    low = ((long)((1 << display->width) >> 6) << 14) | (long)base;
    low = low | ((long)display->psm << 20);
    low = low | ((long)display->width << 26);
    low = low | ((long)display->height << 30);
    high = low | highFlags;
    displays[textureIndex].packet = high | 0x4000000000000000ULL;
    func_0011AEA0(0);
    func_002E5FE0();
    func_002B7170();
    func_00133580(0);
    D_001A63A8.pendingVoice = -1;
    while (D_001393E0[0x15C/4] >= 3 || D_001393E0[0x164/4] >= 0) func_US2_00299CF0();
    frame = 0;
    status = -1;
    done = 0;
    for (;;) {
        int *descriptor;
        descriptor = ref_L00_002F5FB8_10;
        if (descriptor != 0 && descriptor[0] != 0) {
            func_002B7C80(destination,descriptor[0] + ((Toc_002F5D40 *)D_0014B540)->base,(descriptor[1] + 2047)/2048);
            ref_L00_002F5FB8_16[0x4C/4] = (int)destination;
            ref_L00_002F5FB8_16[0x34/4] = 0;
        } else {
            ref_L00_002F5FB8_16[0x4C/4] = 0;
            ref_L00_002F5FB8_16[0x34/4] = 0;
        }
        stream = (Stream_5FB8 *)ref_L00_002F5FB8_05;
        result = func_0034EF58((void *)ref_L00_002F5FB8_01,(void *)ref_L00_002F5FB8_00,(char *)((first + 63) & -64),(char *)((second + 63) & -64),ref_L00_002F5FB8_13,ref_L00_002F5FB8_12 != 0);
        stream->mode = (result ^ 1) == 0 ? 1 : stream->mode;
        if (result != 0) { stream->mode = 1; func_00288BB8(stream); }
        if (ref_L00_002F5FB8_05[0] != 0) {
            ref_L00_002F5FB8_05[0]++;
            if (ref_L00_002F5FB8_05[0] >= 25) ref_L00_002F5FB8_05[0] = 1;
            index = func_002EF010(stream->frames[ref_L00_002F5FB8_05[0]]);
            ref_L00_002F5FB8_01 = ((Toc_002F5D40 *)D_0014B540)->files[index * 2 + 1].sector + ((Toc_002F5D40 *)D_0014B540)->base;
            ref_L00_002F5FB8_14 = ((Toc_002F5D40 *)D_0014B540)->files[index * 2 + 1].size;
        } else if (stream->active == 0) {
            done = 1;
        } else {
            func_00288A00(stream,&frame,&status);
            if (status == 0) {
                index = func_002EF010(frame);
                ref_L00_002F5FB8_01 = ((Toc_002F5D40 *)D_0014B540)->files[index * 2 + 1].sector + ((Toc_002F5D40 *)D_0014B540)->base;
                ref_L00_002F5FB8_14 = ((Toc_002F5D40 *)D_0014B540)->files[index * 2 + 1].size;
            } else if (status == 1) {
                done = 1;
            }
        }
        if (done) break;
    }
    func_00133580(0);
    func_00126DC0(D_001339B0);
    func_001244B8(0,0);
    slot = &ref_L00_002F5FB8_07[textureIndex];
    func_001265B0(packet,ref_L00_002F5FB8_08 + slot->tex1 * 16);
    func_001244B8(0,0);
    func_002F0FA0();
    slot->packet = 0;
    func_002FC1D8();
    if (result == 0 && status == 1) func_002B49E0(2,2,frame,0,0);
    else func_002B4B70(0,0);
}

