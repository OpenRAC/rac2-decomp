/* 1 November 2026: with compiler/block-move-quad, packet = D_L00_002A26A0 gives retail's lq/sq copy: 2564/2572,
 * 192 aligned words (412 before). Left: retail saves f26 and has four more spill slots in order; the frame is
 * 0x10 short. func_L00_0038E880 is the same routine family. */
/* GPT-6.1 Sol (high), USA v1.01, default -O2 -G0 -ffunction-sections.
 * Retained reconstruction: 2572/2572 bytes, 0/27 placements; equal size is
 * not a match. The frame is 0x190 rather than 0x1A0, initial paired-copy
 * allocation/scheduling differs, material bases live too long and the first
 * material float access uses mult/addu instead of mtlo/madd. Later allocation,
 * spills and scheduling still differ. All declarations are included below.
 *
 * Relative to the 2540-byte draft, sharing the doubled-distance/fade local
 * recovers f25 and the timestep's f23. Reusing the bounded loop counter and
 * using an explicitly guarded do/while recovers the table pointer in s2,
 * asset spill at +0xF4 and the bnez loop tail. The camera's shared local base
 * recovers its two-branch store shape. The vector's scale factor is the
 * measured float 0x3B5A740F; 1.0f/300.0f emits 0x3B5A740E instead.
 *
 * Eleven check.py candidates plus a regalloc baseline/dump comparison were
 * measured. -mno-split-addresses: 2592 bytes; -fno-gcse: 2504 bytes (earlier
 * source layouts). -fno-rerun-loop-opt: 2548 bytes with separate loop counters.
 * -fno-strength-reduce and -fno-force-mem leave the final 2572-byte layout
 * short of a match; -fno-rerun-cse-after-loop grows it to 2668 bytes. No
 * options are needed for this retained source. regalloc.py verified identical
 * baseline/dump objects; the force multiply has already moved to its call's
 * f12 setup in the loop dump. Next investigate the packet's grouped block
 * copy lowering and the force/material-base lifetimes, using independent
 * source or compiler evidence rather than more equivalent expressions.
 *
 * The old HANDWRITTEN/MMI-only note is incorrect: 0x71936000 at +0x188 is
 * madd t4,t4,s3, and 0x70001CA9 / 0x700044A9 / 0x700024A9 at
 * +0x1C8/+0x308/+0x42C/+0x430 are por zeroing. These are compiler-reachable.
 * The source marker remains INCLUDE_ASM; no ASM_FUNC or linked match claimed.
 */
#include "common.h"
extern float func_002A7878_1(float, float);
extern float func_00282DF0(char *);
extern void func_00282F20(char *, char *, float);
extern int func_002A77E0(int);
typedef int V1306TI __attribute__((mode(TI)));
typedef union { V1306TI q; float f[4]; } V1306Vec;
typedef struct { int entry[6]; } V1306Table;
typedef struct { V1306TI q[5]; } __attribute__((aligned(16))) V1306Packet;
typedef struct { char pad[4]; unsigned char flag; char tail[219]; } V1306Material;
extern unsigned char D_00139568[];
extern V1306Material D_L00_00262570[];
extern V1306Packet D_L00_002A26A0;
extern V1306Table D_L00_001AEFE0, D_L00_001AEFF8;
extern char D_L00_001B8DC0[], D_L00_001C3280[];
typedef struct { char pad[0x160]; float amount; int unused, duration, state; } V1439Camera;
extern V1439Camera D_L00_001B8C80;
extern float func_00283CE0(int);
extern void func_00282D30(char *, char *, float);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern float func_00282DB0(char *, char *);
extern void func_00282FB8(char *, char *, float);
extern int func_00277F48(char *, int, char *, int, float);
extern void func_002A9850(char *, char *, char *, int, int, int, int, int, float, float, float);
extern int func_002A7820(int, int);
extern void func_00308600(char *, char *, int, int, int);
extern int func_00283CF0(float);
extern int func_002AAFA0(int, int);
extern void func_002BBCB0(char *, char *, int, int, int, int, int, int, float, float);
extern void func_L00_003A0DA0(char *, char *, char *, int, int, int, int, int, float);
extern void func_002AAF40(int *, int *, int *, int);
extern void func_002E5CF8(int, int, char *);
extern void func_00312B70(void *, char *, int, int);
#define V1306_MAT ((V1306Material *)(D_00139568[12] * 224 + (int)D_L00_00262570))
#define V1306_FLAG (((V1306Material *)((unsigned)D_L00_00262570 + (unsigned)D_00139568[12] * 224))->flag != 0)
void func_L00_0038DE70(char *object, char *direction, char *axis)
{
    V1306Packet packet;
    V1306Vec delta, temp, vector, random;
    V1306Table first, second;
    int red, green, blue, red2, green2, blue2;
    int *child;
    int i, n, counter, asset1, asset2, life1, life2;
    float scale, length, twice, speed, force;
    packet = D_L00_002A26A0;
    child = *(int **)(object + 0x68);
    counter = 9;
    scale = func_00283CE0(V1306_FLAG) + 1.0f;
    func_00282D30(direction, direction, scale);
    func_00282CF0((char *)&delta, D_L00_001B8DC0, object + 0x10);
    length = func_00282DF0((char *)&delta);
    i = func_00277F48(object + 0x10, 16, object, 0, scale * 0.5f);
    vector.q = *(V1306TI *)(object + 0x10);
    func_002A9850(object, (char *)&vector, D_L00_001C3280, i, 0, 0x830000, 2, 1,
        *(float *)((char *)V1306_MAT + 0x70), 1.0f, 1.0f);
    object[0x20] = 1;
    do {
        counter--;
        random.q = 0;
        random.f[0] = func_002A7878_1(-1.0f, 1.0f);
        random.f[1] = func_002A7878_1(-1.0f, 1.0f);
        vector.q = random.q;
        func_00282F20((char *)&temp, axis, func_00282DB0((char *)&vector, axis));
        func_00282CF0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&temp, axis, func_002A7878_1(0.0f, 1.0f));
        func_00282CC0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&vector, (char *)&vector, scale * func_002A7878_1(3.5f, 6.5f) * (1.0f/60.0f));
        func_00282CC0((char *)&vector, (char *)&vector, direction);
        life1 = func_002A7820(60,120);
        func_00308600(object+0x10, (char *)&vector, life1, 0, V1306_FLAG);
    } while (counter >= 0);
    twice = length + length;
    for (n = 3; n >= 0; n--) {
        random.q = 0;
        random.f[0] = func_002A7878_1(-1.0f, 1.0f);
        random.f[1] = func_002A7878_1(-1.0f, 1.0f);
        vector.q = random.q;
        func_00282F20((char *)&temp, axis, func_00282DB0((char *)&vector, axis));
        func_00282CF0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&temp, axis, func_002A7878_1(0.0f, 1.0f));
        func_00282CC0((char *)&vector, (char *)&vector, (char *)&temp);
        func_00282F20((char *)&vector, (char *)&vector, scale * func_002A7878_1(6.5f, 10.0f) * (1.0f/60.0f));
        func_00282CC0((char *)&vector, (char *)&vector, direction);
        life1 = func_002A7820(60,90);
        func_00308600(object+0x10, (char *)&vector, life1, 1, V1306_FLAG);
    }
    random.q = 0;
    random.f[0] = func_002A7878_1(-1.0f, 1.0f);
    random.f[1] = func_002A7878_1(-1.0f, 1.0f);
    random.f[2] = func_002A7878_1(-1.0f, 1.0f);
    vector.q = random.q;
    delta.f[2] += length * 0.5f;
    func_00282F20((char *)&vector, (char *)&vector, length * 0.0033333336468786f);
    func_00282F20((char *)&delta, (char *)&delta, twice * (1.0f/60.0f));
    func_00282CC0((char *)&vector, (char *)&vector, (char *)&delta);
    func_00282FB8((char *)&vector, (char *)&vector, 1.0f/6.0f);
    life1 = func_002A7820(60,90);
    func_00308600(object+0x10, (char *)&vector, life1, 1, V1306_FLAG);
    if (length < 6.0f) n = func_00283CF0(length) + 1;
    else n = 4;
    twice = 0.0f;
    if (length < 7.0f) twice = 7.0f - length;
    if (n > 0) do {
        n--;
        force = scale * 400000.0f;
        speed = scale * func_002A7878_1(8.0f, 10.0f);
        first = D_L00_001AEFE0;
        second = D_L00_001AEFF8;
        speed = speed * (1.0f/60.0f) - twice * (1.0f/60.0f);
        asset1 = func_002AAFA0(first.entry[func_002A77E0(6)], V1306_FLAG);
        asset2 = func_002AAFA0(second.entry[func_002A77E0(6)], V1306_FLAG);
        life1 = func_002A7820(15,20);
        life2 = func_002A7820(25,30);
        func_002BBCB0(object+0x10, direction, asset1, asset2, life1, life2, 0, 0, force, speed);
    } while (n);
    if (length > 9.0f) {
        speed = scale * 4.0f;
        func_L00_003A0DA0(object,object+0x10,direction,15,127,127,127,32,speed);
        red=127; green=32; blue=0;
        func_002AAF40(&red,&green,&blue,V1306_FLAG);
        func_L00_003A0DA0(object,object+0x10,direction,24,(unsigned char)red,(unsigned char)green,(unsigned char)blue,32,speed);
    }
    red2=127; green2=63; blue2=0;
    func_002AAF40(&red2,&green2,&blue2,V1306_FLAG);
    func_L00_003A0DA0(object,object+0x10,direction,20,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,48,scale*4.0f);
    red2=96; green2=16; blue2=0;
    func_002AAF40(&red2,&green2,&blue2,V1306_FLAG);
    func_L00_003A0DA0(object,object+0x10,direction,27,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,64,scale*3.5f);
    red2=32; green2=0; blue2=0;
    func_002AAF40(&red2,&green2,&blue2,V1306_FLAG);
    func_L00_003A0DA0(object,object+0x10,direction,29,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,32,scale*3.0f);
    *child = 0;
    object[0xBC] = 0;
    if (V1306_FLAG) func_002E5CF8(0,0,object);
    else func_002E5CF8(0,0,object);
    { V1439Camera *camera = &D_L00_001B8C80;
    if (length < 20.0f) camera->amount = 0.4f - length * 0.0175f;
    else camera->amount = 0.050000011920928955f;
    }
    D_L00_001B8C80.duration=25;
    D_L00_001B8C80.state=0;
    func_00312B70(&packet,object+0x10,0,0);
}
