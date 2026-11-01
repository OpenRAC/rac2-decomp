#include "include_asm.h"

#include "common.h"
extern float D_L00_001B15B8 __attribute__((sda));
extern char D_L00_001B9040[];
extern char D_00189F70[];
extern int D_001A7BAC;
extern float D_L00_001A8904;
extern int D_L00_001A8FF0;
extern void func_00282CC0(char *, char *, char *);
extern float func_00283B98(float, float);
extern void func_PAL_L00_00425B98(char *, float *);
extern void func_PAL_L00_00427960(char *);
extern void func_L00_00421C50(char *);
extern void func_PAL_L00_0042B858(int);
extern void func_PAL_L00_004276D8(char *);

/* Builds the hero's 16-byte block from the hero record and the parameter block, stores the
   table's current blend weight in the global, refines the block's last float with the
   parameter block's own float (the hero's own float only when the global allows it) and
   hands the block to the object's own refresh, which then runs the five owner helpers.
   The retail reaches the blend table through $gp, so this body needs the small-data
   profile (-G8, from this file's name). */
void func_PAL_L00_0042B8D0(char *object)
{
    char local[16];
    char *hero = D_00189F70;
    char *self = object;
    char *parameters = D_L00_001B9040;
    float value = (&D_L00_001B15B8)[D_001A7BAC];
    float first;

    D_L00_001A8904 = value;
    func_00282CC0(local, hero, parameters);
    first = *(float *)(hero + 12);
    if (D_L00_001A8FF0 != 0) {
        first = 0.0f;
    }
    *(float *)(local + 12) = func_00283B98(first, *(float *)(parameters + 12));
    func_PAL_L00_00425B98(self, (float *)local);
    func_PAL_L00_00427960(self);
    func_L00_00421C50(self);
    func_PAL_L00_0042B858((int)self);
    func_PAL_L00_004276D8(self);
}
