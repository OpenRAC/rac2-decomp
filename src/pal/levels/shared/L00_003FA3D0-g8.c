#include "include_asm.h"

#include "common.h"
typedef int Qword __attribute__((mode(TI)));
typedef struct {
    Qword pos;
    Qword a;
    Qword b;
    Qword c;
    Qword d;
    short flag;
    short count;
    float t;
    float u;
    float rate;
} TrailSlot;
typedef struct {
    char pad0[0x18];
    short index;
    short id;
} TrailSource;
typedef struct {
    char pad0[0x10];
    Qword pos;
    char pad20[0x48];
    TrailSource *source;
} TrailActor;
extern float D_L00_001AF760 __attribute__((sda));
extern float D_L00_001AF798 __attribute__((sda));
extern float D_L00_001AF774 __attribute__((sda));
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern int ref_L00_003A9000_00(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003FA5C8);

