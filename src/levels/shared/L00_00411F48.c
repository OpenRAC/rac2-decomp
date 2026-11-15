#include "include_asm.h"
#include "names.h"
typedef struct {
    char pad0[0x7C];
    char *owner;
    char pad80[0x88 - 0x80];
    int busy;
} Sub_411F48;

typedef struct {
    char pad0[0x30];
    Sub_411F48 sub;
    char pad[0xD0 - 0x30 - sizeof(Sub_411F48)];
} Ent_411F48;

extern Ent_411F48 ref_L00_00411F48_00[];
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_00281EB8(void *, int, unsigned int, int, float, float, float);
extern void func_L00_00412230(char *object, char *state);

/* Redraws each lightning arc owned by this object and adds glow sprites while the arc is idle. */
void func_L00_00411F48(char *moby)
{
    Ent_411F48 *entry;
    int i;

    for (i = 0; i < 0x30; i++) {
        entry = &ref_L00_00411F48_00[i];
        if (entry->sub.owner == moby) {
            BuildJitteredLightningBolt(moby, (char *)entry);
            if (entry->sub.busy == 0) {
                DrawBillboardQuad_00281EB8(&entry->sub, 0x31, (RandomIntRange(0x50, 0x60) << 24) | 0x103080, 1, 0.5f, 0.1f, RandomAngle());
                DrawBillboardQuad_00281EB8(&entry->sub, 0x31, (RandomIntRange(0x50, 0x60) << 24) | 0xFFFFFF, 1, 0.5f, 0.1f, RandomAngle());
            }
        }
    }
}
