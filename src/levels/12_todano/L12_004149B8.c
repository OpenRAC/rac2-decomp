#include "common.h"

typedef struct {
    char pad0[0x110];
    s32 f110;             /* 0x110 */
    char pad114[0x10c];
    u32 f220;             /* 0x220 */
} Tab698;

typedef struct {
    char pad0[0x20];
    u8 f20;               /* 0x20 */
    char pad21[0x0f];
    u8 f30;               /* 0x30 */
    u16 f32;              /* 0x32 */
    char pad34[0xc4];
    f32 fF8;              /* 0xF8 */
} Obj390;

typedef struct {
    char pad00[0x20];
    u8 f20;                 /* 0x20 */
    char pad21[0x31 - 0x21];
    u8 f31;                 /* 0x31 */
    char pad32[0x34 - 0x32];
    u16 f34;                /* 0x34 */
    char pad36[0xAA - 0x36];
    s16 fAA;                /* 0xAA */
} Sub114B;

typedef struct {
    char pad00[0x2F0];
    Sub114B *f2F0[2];       /* 0x2F0 */
    Sub114B *f2F8;          /* 0x2F8 */
} Moby49B8;

typedef struct {
    char pad00[0x31];
    u8 f31;                 /* 0x31 */
    char pad32[0x68 - 0x32];
    Moby49B8 *f68;          /* 0x68 */
} Ent49B8;

extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, void *, int);

extern s32 *g_path_zone_table[];

extern f32 func_002F2950(f32, f32);

extern void func_002A0F48(void *);

extern void vec_scale_to_length(f32 *, void *, f32);


extern void helper_push_objects(u8 *);

extern void func_326F10(void *, void *, s32, s32);

extern void moby_copy_color(void *, void *);

/* A pointer table of level-12 data, reached absolutely (out of the $gp window). */

/* func_L12_0041BDF8 is matched in L12_0041BDF8-rc2.c. */


/* Returns 1 as soon as one of the two bound sub-objects carries a live state word. */
s32 helper_has_live_object(u8 *moby)
{
    u8 *moby_copy = moby;
    u8 *vars;
    u8 **slot;
    s32 i;

    if (moby_copy == 0)
        return 0;
    if (*(s16 *)(moby_copy + 0xAA) != 0xFAE /* moby class 4014 */)
        return 0;
    vars = *(u8 **)(moby_copy + 0x68);
    helper_push_objects(moby_copy);
    slot = (u8 **)(vars + 8);
    for (i = 0; i < 2; i++, slot++) {
        if (*slot != 0) {
            if (*(s32 *)(*slot + 0x98) != 0)
                return 1;
        }
    }
    return 0;
}

/* --- func_L12_0041A698 (52 B) ------------------------------------------------------ */

/* Tells whether the object has reached the last point of its path. */
s32 path_is_at_last_point(u8 *self)
{
    Tab698 *vars = *(Tab698 **)(self + 0x68);

    return (vars->f220 ^ (u32)(*g_path_zone_table[vars->f110] - 1)) < 1;
}

/* --- func_L12_00416390 (88 B) ------------------------------------------------------ */

/* Turns the object a little more each frame so it spins slowly. */
f32 slow_spinning_update(Obj390 *self)
{
    if (self->f20 == 0) {
        self->f20 = 1;
        self->f30 = 0x20;
        self->f32 = 0x20;
    }
    return self->fF8 = func_002F2950(self->fF8, 0.017453294f);
}

/* --- func_L12_0041BDA8 (68 B) ------------------------------------------------------ */

/* Clears the state word of the object's two helper objects. */
void helper_clear_states(u8 *moby)
{
    s32 i;
    u8 **slot;

    if (moby == 0)
        return;
    if (*(s16 *)(moby + 0xAA) != 0xFAE /* moby class 4014 */)
        return;
    slot = (u8 **)(*(u8 **)(moby + 0x68) + 8);
    for (i = 1; i >= 0; i--, slot++) {
        if (*slot != 0)
            *(u32 *)(*slot + 0x98) = 0;
    }
}

/* func_L12_0041BDF8 (104 B) and func_L12_0041BE60 (120 B): best attempt reaches every
   instruction but one — the retail keeps the incoming pointer in $a1 (a copy of $a0 at
   entry) and mine folds it onto $a0.  Left as markers; both attempts are in the wave's
   drafts/ directory. */

/* ---------------------------------------------------------------------------------- */

/* the two bound sub-objects of the moby this driver walks */

/* Walks the moby's two sub-objects, re-arms each one's parent link and releases it. */
void guard_reattach_helpers(Ent49B8 *guard)
{
    Moby49B8 *moby = guard->f68;
    Sub114B *head = moby->f2F8;
    s32 i;

    if (head == 0)
        return;
    if (head->fAA != 0x114B /* moby class 4427 */)
        return;
    if (head->f20 == 0xFE)
        return;
    if (head->f20 == 0xFD)
        return;
    for (i = 0; i < 2; i++) {
        if (moby->f2F0[i] != 0) {
            func_326F10(moby->f2F8, moby->f2F0[i], i, (i ^ 1) ? 0 : 6);
            if (guard->f31 != 0) {
                moby->f2F0[i]->f34 = moby->f2F0[i]->f34 & 0xFFFE;
                moby->f2F0[i]->f31 = 1;
            } else {
                moby->f2F0[i]->f34 = moby->f2F0[i]->f34 | 1;
                moby->f2F0[i]->f31 = 0;
            }
            moby_copy_color(guard, moby->f2F0[i]);
        }
    }
}


/* func_L12_00414C60 is in L12_00414C60-g8.c. */

/* func_L12_00414EB8 is in L12_004149B8-effects-g8.c. */

/* func_L12_004163E8 is in L12_004163E8-g8.c. */

/* func_L12_00417690 is in L12_004149B8-f7-g8.c. */

/* func_L12_00417CA8 is in L12_00417CA8-g16.c. */

/* func_L12_00418418 is defined in L12_00418418-g8.c. */

/* func_L12_00418D20 is in L12_00418D20-g16.c. */

/* func_L12_004190A8 is in L12_004190A8-g8.c. */

/* func_L12_00419D68 is matched in its own unit, L12_00419D68.c. */

/* Puts the object back at its saved spot, switches it to state 2 and starts animation 8. */
void moby_reset_to_saved_position(u8 *self)
{
    u8 *dst = self + 0x10;
    u8 *vars = *(u8 **)(self + 0x68);
    void *class_def;

    qcopy(dst, vars + 0x210);
    *(f32 *)(self + 0xF8) = *(f32 *)(vars + 0x21C);
    *(u32 *)(vars + 0x224) = 0;
    *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) & 0xFFBE) | 0x1000;
    class_def = *(void **)(self + 0x24);
    *(u32 *)(self + 0x98) = *(u32 *)((u8 *)class_def + 0x10);
    moby_fuse_linked_objects(self, dst, self + 0xF0, 0, 0);
    moby_set_state(self, 2, -1);
    if (*(u8 *)(self + 0x43) != 8)
        anim_start_blended(self, 8, 0, 1);
}

/* func_L12_0041A790 is matched in L12_0041A790-g8.c. */

/* func_L12_0041AEF0 is in L12_0041AEF0-g8.c. */

/* func_L12_0041B2A8 is in L12_0041B2A8-g8.c. */

/* --- func_L12_0041BED8 (176 B) ----------------------------------------------------- */

/* Pushes each of the object's two helper objects along a little and updates their size every
   frame. */
void helper_push_objects(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    u8 **slot = (u8 **)(vars + 8);
    s32 i;

    for (i = 1; i >= 0; i--, slot++) {
        if (*slot != 0) {
            f32 scale = (*(f32 *)((u8 *)slot + 0x2C) + *(f32 *)(vars + 0x40) * 0.5f)
                    * 0.16666667f;
            f32 size;

            vec_scale_to_length((f32 *)(*slot + 0xD0), *slot + 0xD0, scale);
            func_002A0F48(*slot);
            size = *(f32 *)(*(u8 **)(*slot + 0x24) + 0x3C);
            *(f32 *)(*slot + 0xC) = size + size;
        }
    }
}


/* func_L12_0041CF10 is in L12_0041CF10-g8.c. */

/* func_L12_0041D3B0 is in L12_0041D3B0-g8.c. */

/* func_L12_0041D808 is in L12_0041D808-g8.c. */

/* func_L12_0041DDA8 is in L12_0041DDA8-g8.c. */
