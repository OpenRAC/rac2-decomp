#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; TI128 q[0x260]; } Hero;
extern char g_hero_position[];

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 f20;
    u8 pad21[0x68 - 0x21];
    struct Mount *f68;
} Ent;

typedef struct Mount {
    u8 pad00[0x1D8];
    f32 f1D8;
    u8 pad1DC[0x224 - 0x1DC];
    f32 f224;
    f32 f228;
    u8 pad22C[0x27C - 0x22C];
    f32 f27C;
    u8 pad280[8];
    f32 f288;
} Mount;

extern f32 coll_get_ground_height_with_limit(void *, f32, f32, f32, f32);

/* The mount's floor under the entry, raised to its minimum, and the ceiling over the hero. */
/* Works out the floor height under the moby and the ceiling height used to keep it above the player. */
void moby_update_floor_and_ceiling_heights(Ent *moby)
{
    Mount *mount = moby->f68;
    f32 pos[4] __attribute__((aligned(16)));
    f32 top, heroTop;
    qcopy(pos, moby->pos);
    if (moby->f20 == 0) {
        mount->f224 = coll_get_ground_height_with_limit(pos, mount->f1D8 + 20.0f, mount->f1D8 - 10.0f, mount->f27C, mount->f288);
    } else {
        mount->f224 = coll_get_ground_height_with_limit(pos, moby->pos[2] + 2.0f, moby->pos[2] - 10.0f, mount->f27C, mount->f288);
    }
    if (mount->f224 < mount->f27C) mount->f224 = mount->f27C;
    top = mount->f224 + 1.7f;
    heroTop = ((Hero *)g_hero_position)->f[8 / 4] + 0.1f;
    mount->f228 = top > heroTop ? top : heroTop;
}
