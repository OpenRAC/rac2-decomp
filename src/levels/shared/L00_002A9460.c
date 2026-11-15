/* func_L00_002A9460: needs -frac2-sticky-volatile-refs (reorg stops at the second qcopy asm); see docs/build/compiler-notes.md. */
#include "common.h"

/* Its first two callees differ by level (ref_ names); func_L00_002ADF80 is C in
   L00_002A6420.c with the same 27 places. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad000[0x80];
    TI128 position;
    TI128 unk90;
    char padA0[0x150];
    short unk1F0;
    char pad1F2[0x5E];
    float unk250;
    float unk254;
    char pad258[0xC];
    float unk264;
    char pad268[0x2028];
    unsigned char *moby;
    char pad2294[0x8];
    int unk229C;
} HeroView_L00_002A9460;

extern char g_hero_state[];
extern void hero_update_model_tilt(void);
extern void hero_update_model_wobble(void);
extern void mem_copy_aligned(void *, void *, int);
extern void func_002A0F48(void *);
extern void hero_apply_mode_transform_reversed(void *, void *, float);
extern void vec_store_transformed_entry(void *, int, void *, float, float);
extern int hero_is_in_special_kind_or_mode(void);


/* Copies the hero position and facing onto the hero object each frame. When it is on the ground it updates the two foot contact points. */
void update_hero_moby(void)
{
    float footPos[4] __attribute__((aligned(16)));
    float footHeight, footGap;
    unsigned char *mobyPtr;

    ((HeroView_L00_002A9460 *)g_hero_state)->moby[0xA8] = 0xFF;
    qcopy(((HeroView_L00_002A9460 *)g_hero_state)->moby + 0x10, &((HeroView_L00_002A9460 *)g_hero_state)->position);
    hero_update_model_tilt();
    qcopy(((HeroView_L00_002A9460 *)g_hero_state)->moby + 0xF0, &((HeroView_L00_002A9460 *)g_hero_state)->unk90);
    hero_update_model_wobble();
    mem_copy_aligned(((HeroView_L00_002A9460 *)g_hero_state)->moby + 0xC0, g_hero_state, 0x30);
    func_002A0F48(((HeroView_L00_002A9460 *)g_hero_state)->moby);
    mobyPtr = ((HeroView_L00_002A9460 *)g_hero_state)->moby;
    if ((*(unsigned char **)(mobyPtr + 0x24))[6] != 0)
        mobyPtr[0x63] = 0x10;
    else
        mobyPtr[0x63] = 0x10;
    if (((HeroView_L00_002A9460 *)g_hero_state)->unk1F0 != 0 || *(int *)(((HeroView_L00_002A9460 *)g_hero_state)->moby + 0x98) == 0)
        return;
    qcopy(footPos, &((HeroView_L00_002A9460 *)g_hero_state)->position);
    hero_apply_mode_transform_reversed(footPos, footPos, ((HeroView_L00_002A9460 *)g_hero_state)->unk254);
    footGap = ((HeroView_L00_002A9460 *)g_hero_state)->unk250 - ((HeroView_L00_002A9460 *)g_hero_state)->unk254;
    if (footGap < 0.05f)
        footGap = 0.05f;
    vec_store_transformed_entry(((HeroView_L00_002A9460 *)g_hero_state)->moby, 0, footPos, ((HeroView_L00_002A9460 *)g_hero_state)->unk264, footGap);
    footHeight = ((HeroView_L00_002A9460 *)g_hero_state)->unk264 + 0.05f;
    if (((HeroView_L00_002A9460 *)g_hero_state)->unk229C == 4)
        footHeight += 0.15f;
    if (hero_is_in_special_kind_or_mode() != 0)
        footHeight = ((HeroView_L00_002A9460 *)g_hero_state)->unk254;
    qcopy(footPos, &((HeroView_L00_002A9460 *)g_hero_state)->position);
    hero_apply_mode_transform_reversed(footPos, footPos, footHeight);
    footGap = ((HeroView_L00_002A9460 *)g_hero_state)->unk250 - footHeight;
    if (footGap < 0.05f)
        footGap = 0.05f;
    vec_store_transformed_entry(((HeroView_L00_002A9460 *)g_hero_state)->moby, 1, footPos, ((HeroView_L00_002A9460 *)g_hero_state)->unk264, footGap);
}
