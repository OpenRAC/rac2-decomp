#include "common.h"
#include "structs.h"

extern void func_0012F9C8(void *);

extern void func_00130178(void *arg0);

extern void func_00130088(void *arg0);

extern int func_0012FA18(void *);

/* The callback table at +0x40: {callback, data} pairs from +0xC, one
   per callback type. */
typedef int (*MpegCbFn)(void *, void *, void *);

typedef struct { MpegCbFn func; void *data; } MpegCbEnt;

typedef struct { char pad[0xC]; MpegCbEnt cb[1]; } MpegCbTbl;

extern void func_0012FAE8(int);

extern void func_0012FB48(void *, int, int);

extern void func_0012FB60(void *);

/* rac1-decomp src/core/0012AC80.c: func_0012BB98 */
/* Tells whether the video decoder has not decoded any picture yet. */
int func_0012F9B8(void *mpeg) {
    return ((Wrapper *)mpeg)->obj->unk004 == 0;
}

/* rac1-decomp src/core/0012AC80.c: func_0012BBA8 */
/*
 * sceMpegReset (libmpeg.a:mpeg.o): clear the object's decode state
 * (unk000/004/008/0AC, the handler-table slot at +0x80, and +0x118), and
 * the wrapper's own +0x08, then call _clearEach (func_00130178) and hand
 * the object to func_00130088 (zero +0x848, kick the IPU chain via
 * r1_func_00127378).
 */
/* Resets the video decoder back to its starting state. */
void func_0012F9C8(void *mpeg) {
    char *wrapper = (char *)mpeg;
    char *decoder = *(char **)(wrapper + 0x40);

    *(int *)(decoder + 0x0) = 0;
    *(int *)(decoder + 0x4) = 0;
    *(int *)(decoder + 0x8) = 0;
    *(int *)(wrapper + 0x8) = 0;
    *(int *)(decoder + 0xAC) = 0;
    *(int *)(decoder + 0x80) = -1;
    ResetMpegHardware(decoder);
    *(int *)(decoder + 0x118) = 0;
    RestartMpegHardware(decoder);
}

/* rac1-decomp src/core/0012AC80.c: func_0012BBF8 */
/* Clears one field in each of the six picture buffers of the video decoder. */
int func_0012FA18(void *mpeg) {
    char *decoder = *(char **)((char *)mpeg + 0x40);
    char *buffer;
    buffer = *(char **)(decoder + 0x1B8); if (buffer != 0) *(int *)(buffer + 0x28) = 0;
    buffer = *(char **)(decoder + 0x1C8); if (buffer != 0) *(int *)(buffer + 0x28) = 0;
    buffer = *(char **)(decoder + 0x1D8); if (buffer != 0) *(int *)(buffer + 0x28) = 0;
    buffer = *(char **)(decoder + 0x1BC); if (buffer != 0) *(int *)(buffer + 0x28) = 0;
    buffer = *(char **)(decoder + 0x1CC); if (buffer != 0) *(int *)(buffer + 0x28) = 0;
    buffer = *(char **)(decoder + 0x1DC); if (buffer != 0) *(int *)(buffer + 0x28) = 0;
    return 1;
}

/* rac1-decomp src/core/0012AC80.c: func_0012BC50 */
/*
 * sceMpegAddCallback: install (callback arg2, data arg3) for type arg1 and
 * return the old callback.
 *
 * Typing the entry as {function pointer, void *} is the lever: 2.9-ee's
 * type-based alias analysis (-fstrict-aliasing is its default) then knows
 * the `data` store cannot alias the `func` load, so sched1 computes
 * `t + 0xC` before `t + off` and the registers fall as in retail. Under
 * 2.95.3 (no type-based aliasing) the same C is 17/36; the old int-offset
 * spelling was 12/36 under both.
 */
/* Sets the function to call for one kind of video event and returns the previous one. */
int func_0012FA70(void *mpeg, int eventType, int callback, int callbackData) {
    MpegCbTbl *table = *(MpegCbTbl **)((char *)mpeg + 0x40);
    MpegCbFn oldCallback;
    table->cb[eventType].data = (void *)callbackData;
    oldCallback = table->cb[eventType].func;
    table->cb[eventType].func = (MpegCbFn)callback;
    return (int)oldCallback;
}

/* rac1-decomp src/core/0012AC80.c: func_0012BC78 */
/*
 * Dispatch the callback registered for *arg1 (the callback data's type
 * field) with its data; returns the callback's result, 0 if none.
 *
 * The table entry is indexed afresh for each use (test `.func`, call
 * `.func(arg0, arg1, .data)`) instead of through one `entry` pointer. CSE
 * merges the two `.func` loads, but the `.data` address is rebuilt after
 * the branch, which is retail's second `addu` in a plain beqz slot, and
 * `ret` then lands in $a3 with the table in $a2. Exact under both
 * compilers (one `entry` pointer is SIZE 84/80; the old spelling 12/80).
 */
/* Calls the function registered for a video event, if there is one, and returns its result. */
void *func_0012FA98(void *mpeg, int *event) {
    int result = 0;
    if (mpeg != 0) {
        MpegCbTbl *table = *(MpegCbTbl **)((char *)mpeg + 0x40);
        if (table != 0) {
            if (table->cb[*event].func != 0) {
                result = table->cb[*event].func(mpeg, event, table->cb[*event].data);
            }
        }
    }
    return (void *)result;
}

/* rac1-decomp src/core/0012AC80.c: func_0012BCC8 */
/* No declaration needed: the definition above precedes this caller. The
   extern that used to sit here guessed `void (int, void *)` and now
   conflicts with the real signature. */
/* Sends video event number 1 to the registered callback. */
void func_0012FAE8(int mpeg) {
    int event[8];
    event[0] = 1;
    DispatchMpegCallback(mpeg, event);
}

/* rac1-decomp src/core/0012AC80.c: func_0012BD28 */
/* Sets up four counters of a small state block from a start value and a size. */
void func_0012FB48(void *state, int startValue, int size) {
    int *words = (int *)state;
    words[1] = size;
    words[0] = startValue;
    words[2] = startValue;
    words[3] = startValue;
}

/* rac1-decomp src/core/0012AC80.c: func_0012BD40 */
/* Copies one counter in a small state block into the one next to it. */
void func_0012FB60(void *state) {
    char *bytes = (char *)state;
    *(int *)(bytes + 0xC) = *(int *)(bytes + 0x8);
}
