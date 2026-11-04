/* func_PAL_L00_003F9B90, the PAL copy of func_L00_003F5750: the same C, where 0.016666668f becomes
   0.020000001f. */
#include "include_asm.h"
#include "common.h"

extern char *func_L00_0032A088(int a0, int a1);

extern void func_L00_003F5870(char *rec, int index);

extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern float D_L00_001B0940 __attribute__((sda));
extern float D_L00_001B0944 __attribute__((sda));
extern float D_L00_001B0948 __attribute__((sda));
extern float D_L00_001B094C __attribute__((sda));
extern float D_L00_001B0950 __attribute__((sda));
extern float D_L00_001B0954 __attribute__((sda));

typedef struct {
    float offset[4];
    float position[4];
    float angle;
    float length;
    float f28;
    float f2c;
} L00Joint;

/* Places one joint of a table entry's chain at `position`: its angle, length and two
   rates come from level tuning values, then func_L00_003F5870 lays out its offset and
   the entry's joint count advances. The record offset is computed once and added to the
   reloaded chain pointer at every store, as retail's addu order shows. */
void func_PAL_L00_003F9B90(char *object, char *position)
{
    char *state = *(char **)(object + 0x68);
    char **table = (char **)func_L00_0032A088(0xc04, *(short *)(state + 0x1a));
    short index = *(short *)(state + 0x20);
    char **entry;
    int offset = index * 0x30;
    entry = (char **)((*(short *)(state + 0x18) << 2) + (int)table);
    qcopy(((L00Joint *)(offset + (int)*entry))->position, position);
    ((L00Joint *)(offset + (int)*entry))->angle = func_002ABB18(func_00283CE0(index) * 0.017453294f * D_L00_001B0948);
    ((L00Joint *)(offset + (int)*entry))->f28 = func_002A7878(D_L00_001B0940, D_L00_001B0944) * 0.017453294f;
    ((L00Joint *)(offset + (int)*entry))->length = D_L00_001B094C;
    ((L00Joint *)(offset + (int)*entry))->f2c = func_002A78D8(D_L00_001B0950, D_L00_001B0954) * 0.020000001f;
    func_L00_003F5870(*entry, index);
    (*(unsigned short *)(state + 0x20))++;
}
