#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; TI128 q[0x260]; } Hero;
extern char D_00189E20[];

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 f20;
    u8 pad21[0x68 - 0x21];
    struct Mount *f68;
} Ent;

typedef struct Mount {
    u8 pad00[0x158];
    f32 f158;
    u8 pad15C[0x1B0 - 0x15C];
    f32 f1B0;
    f32 f1B4;
    u8 pad1B8[0x1D0 - 0x1B8];
    f32 f1D0;
    f32 f1D4;
} Mount;

extern f32 func_L08_00422850(void *, f32, f32, f32, f32);

/* The mount's floor under the entry, raised to its minimum, and the ceiling over the hero. */
/* Works out how low and how high the ridden vehicle may go, from the ground below it and the hero's height. */
void func_L08_00422900(Ent *entry)
{
    Mount *mount = entry->f68;
    f32 pos[4] __attribute__((aligned(16)));
    f32 floorTop, hero;
    qcopy(pos, entry->pos);
    if (entry->f20 == 0) {
        mount->f1B0 = FindGroundHeight(pos, mount->f158 + 20.0f, mount->f158 - 10.0f, mount->f1D4, mount->f1D0);
    } else {
        mount->f1B0 = FindGroundHeight(pos, entry->pos[2] + 2.0f, entry->pos[2] - 10.0f, mount->f1D4, mount->f1D0);
    }
    if (mount->f1B0 < mount->f1D4) mount->f1B0 = mount->f1D4;
    floorTop = mount->f1B0 + 1.7f;
    hero = ((Hero *)gHeroState)->f[0x88 / 4] + 0.1f;
    mount->f1B4 = floorTop > hero ? floorTop : hero;
}
