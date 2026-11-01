#include "include_asm.h"

#include "common.h"
typedef struct { char prefix[0x3C]; int abort; } SequencePlayback;
extern SequencePlayback D_L00_001BEFC0;
extern float D_L00_001B18E0 __attribute__((sda));
extern int D_001A7A00[] __attribute__((sda));
extern int D_001A7478 __attribute__((sda)), D_001A79F0 __attribute__((sda)), D_001A7B90 __attribute__((sda));
typedef struct { char prefix[0x1A0]; union { unsigned long long all; struct { unsigned int low, high; } word; } buttons; } SequenceInput;
extern SequenceInput D_00138180;
extern short D_001A63AC;
extern void func_00288BB8(void *);
extern int func_002B4B70(int, int);
extern void func_PAL_L00_002FE328(void);
extern void func_002B6658(void);
extern void func_002E5F60(void);
extern void func_PAL_L00_002A6CB8(void);
extern float func_002AA2E8(float *, float, float);
extern int func_002B6D28(void);
extern int func_00288BE8(void *);
extern void func_00293D30(void);
extern int func_PAL_002F6A48(void);
extern void func_0029F390(unsigned char *);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A0F48(unsigned char *);
extern void ref_L00_00370408_00(void (*)(void *), void *);
extern void func_PAL_002EDA88(void *);
extern void func_002A93B0(void *);
extern void func_PAL_L00_002D5380(void *, int);
extern void func_PAL_L00_002A6FE0(void *);
extern void func_PAL_L00_002FE768(void);
extern void func_002914B8(void);
extern void func_0029FFB8(void);
extern int D_L00_001BCAC0[];
extern void func_PAL_002B8898(int);
extern void func_002F5220(void);
extern void func_002B9390(void);
extern int func_PAL_L00_003062B0(int);
extern void func_PAL_002E5898(void);
extern void func_PAL_002F6208(void);
typedef struct {
    char prefix[0x34];
    int time, frame, chunk;
    short end_time, pad42, count, pad46, fade_time;
    char pad4a[14];
    int done;
    char pad5c[0x130];
    unsigned char *actors[0];
} SequenceState;

void func_PAL_L00_00372EA8(void) {
    float first[4];
    float second[4];
    int ended;
    unsigned char *object;
    char *path;
    int abort;
    int threshold;
    int complete;
    int i;
    short id;
    if (((SequenceState *)D_L00_001BCAC0)->done) return;
    if (((SequenceState *)D_L00_001BCAC0)->end_time == 0) {
        func_00288BB8(&D_L00_001BEFC0);
        ((SequenceState *)D_L00_001BCAC0)->done = 1;
        func_002B4B70(0, 0);
        return;
    }
    func_002F5220();
    func_PAL_L00_002FE328();
    func_002B6658();
    func_002E5F60();
    func_PAL_L00_002A6CB8();
    func_002B9390();
    { int t; ++((SequenceState *)D_L00_001BCAC0)->frame; t = ++((SequenceState *)D_L00_001BCAC0)->time; if (t < 15) {
        func_002AA2E8(&D_L00_001B18E0, 0.0f, 0.20000002f);
        if (D_L00_001B18E0 > 1.0f) D_L00_001B18E0 = 1.0f;
    }
    }
    if (((SequenceState *)D_L00_001BCAC0)->fade_time <= ((SequenceState *)D_L00_001BCAC0)->time) func_002B6D28();
    ended = ((SequenceState *)D_L00_001BCAC0)->time >= ((SequenceState *)D_L00_001BCAC0)->end_time;
    abort = 0;
    if (((SequenceState *)D_L00_001BCAC0)->time > 14 && D_L00_001B18E0 == 0.0f) {
        if (!(((D_001A7A00[2] & 0xFFFF0000) == 0) && D_001A7478 == 0 && D_001A79F0 > 0) && (D_00138180.buttons.word.high & 0x800)) abort = 1;
        else { unsigned long long v = (D_00138180.buttons.all & 0x8000000000FULL) ^ 0x8000000000FULL; abort = 1; if (v) abort = 0; }
    }
    if (abort) {
        D_L00_001BEFC0.abort = 1;
        func_00288BB8(&D_L00_001BEFC0);
        ((SequenceState *)D_L00_001BCAC0)->done = 1;
        func_002B4B70(0, 0);
    } else {
        if (ended) {
            ((SequenceState *)D_L00_001BCAC0)->done = 1;
            if (!func_00288BE8(&D_L00_001BEFC0)) func_002B4B70(0, 0);
        } else {
            threshold = D_001A7B90 ? 80 : 96;
            if (((SequenceState *)D_L00_001BCAC0)->frame >= threshold) {
                ++((SequenceState *)D_L00_001BCAC0)->chunk;
                if (D_001A63AC) func_PAL_002B8898(1);
                func_00293D30();
                func_PAL_L00_003062B0(((SequenceState *)D_L00_001BCAC0)->chunk + 1);
            }
            complete = func_PAL_002F6A48();
            for (i = 0; i < ((SequenceState *)D_L00_001BCAC0)->count; i++) {
                object = ((SequenceState *)D_L00_001BCAC0)->actors[i];
                { int frame = ((SequenceState *)D_L00_001BCAC0)->frame >> 1;
                object[0x41] = frame + 1;
                object[0x40] = frame; }
                func_0029F390(object);
                *(float *)(object + 0x44) = func_00283CE0(((SequenceState *)D_L00_001BCAC0)->frame & 1) * 0.5f;
                if (complete && (((SequenceState *)D_L00_001BCAC0)->frame & 1)) *(float *)(object + 0x44) = 1.0f;
                path = *(char **)(object + 0x68);
                func_00282D30(first, path + object[0x40] * 16, 1.0f - *(float *)(object + 0x44));
                func_00282D30(second, path + object[0x41] * 16, *(float *)(object + 0x44));
                func_00282CC0(object + 0x10, first, second);
                object[0x61] = 0xFF;
                func_002A0F48(object);
                if (*(short *)(object + 0xAA) == 0xD54) ref_L00_00370408_00(func_PAL_002EDA88, object);
                if (object[0x6F]) func_002A93B0(object);
                id = *(short *)(object + 0xAA);
                if (id == 0 || id == 0xF6B) func_PAL_L00_002D5380(object, 0);
                id = *(short *)(object + 0xAA);
                if (id == 10 || id == 0x1159 || id == 0x57 || id == 0xD6B) func_PAL_L00_002A6FE0(object);
            }
        }
    }
    func_PAL_L00_002FE768();
    func_PAL_002E5898();
    func_002914B8();
    func_0029FFB8();
    func_PAL_002F6208();
}
