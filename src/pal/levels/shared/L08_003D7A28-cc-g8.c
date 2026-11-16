/* func_PAL_L08_003D7A28, the PAL copy of func_L08_003D39F0: the same C, where rename func_L00_002D70A0 becomes func_PAL_L00_002D7850. */
#include "common.h"

/* The one body of L08_003D3928.c whose retail bytes reach 8_tabora's data through $gp:
   a store in ordinary flow, which only the small-data profile (-G8, from this file's
   name) reaches, as a one-instruction form.  The `sda` declaration is what makes cc1
   emit the bare symbol operand and the `.extern` the assembler needs. */

/* Totals three table lookups into one $-gp word and returns it. */
typedef int TI128 __attribute__((mode(TI)));

/* The three 0x30-byte target records of L08_003D3928.c: [0] the tracked owner, [1] the
   nearest one seen this frame, [2] last frame's [1]. MACRO_ADDR keeps every field access
   one assembler macro and every address taken one unsplit `la`. */
typedef struct {
    TI128 pos;      /* 0x00 */
    void *owner;    /* 0x10 */
    float dist;     /* 0x14 */
    s32 unk18;      /* 0x18 */
    s32 unk1C;      /* 0x1C */
    s32 valid;      /* 0x20 */
    s32 pad[3];
} L08Target;

extern L08Target g_lock_on_targets[3] MACRO_ADDR;

/* A 0x40-byte pool entry from func_PAL_L00_002D7850; its position vector is at 0x20. */
typedef struct {
    float x0;
    float x4;
    float x8;
    float xC;
    u8 pad10[0x1F - 0x10];
    u8 x1F;
    float pos[4];
    u8 pad30[0x10];
} L08Marker;

/* The resident player state: the vehicle at 0x1830, the movement mode at 0x2294. */
typedef struct {
    u8 pad0[0x1830];
    u8 *vehicle;
    u8 pad1834[0x2294 - 0x1834];
    s32 mode;
} L08Player;

extern L08Player g_hero_state;
extern L08Marker *g_lock_on_marker __attribute__((sda));
extern s32 g_lock_on_hold_frames __attribute__((sda));
extern float g_lock_on_offset_radius __attribute__((sda));
extern float g_lock_on_marker_x_a __attribute__((sda));
extern float g_lock_on_marker_x_b __attribute__((sda));
extern float g_lock_on_marker_xc __attribute__((sda));
extern float g_lock_on_marker_x8 __attribute__((sda));
extern TI128 g_hero_position_vec;
extern s32 g_lock_on_state MACRO_ADDR;

extern void *memset(void *, int, unsigned int);
extern int IsPointInCuboid(void *, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern L08Marker *cam_alloc_override_slot_pal(int);
extern void cam_end_override(void *);

static __inline__ void CopyTarget(L08Target *dst, L08Target *src)
{
    TI128 *d = (TI128 *)dst;
    TI128 *s = (TI128 *)src;

    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
}

/* Per-frame target tracker: a vehicle mode places a marker ahead of the vehicle; on foot
   record [1] replaces record [0] once it has been nearest for long enough, a marker
   follows record [0]'s owner, and [1] is shifted into [2] and cleared for the next frame. */
void lock_on_target_tracker_update_pal(u8 *object)
{
    float offset[4] __attribute__((aligned(16)));
    u8 *vehicle;
    int *data = *(int **)(object + 0x68);
    int limit;

    switch (object[0x20]) {
    case 0:
        memset(&g_lock_on_targets[0], 0, 48);
        memset(&g_lock_on_targets[1], 0, 48);
        memset(&g_lock_on_targets[2], 0, 48);
        g_lock_on_targets[0].dist = 100000.0f;
        g_lock_on_targets[0].unk18 = 65535;
        g_lock_on_targets[1].dist = 100000.0f;
        g_lock_on_targets[1].unk18 = 65535;
        g_lock_on_targets[2].dist = 100000.0f;
        g_lock_on_targets[2].unk18 = 65535;
        g_lock_on_marker = 0;
        object[0x20] = 1;
        return;
    case 1:
        break;
    default:
        return;
    }
    if (*data != -1 && IsPointInCuboid(&g_hero_position_vec, *data))
        g_lock_on_state = 2;
    if (g_hero_state.mode == 0x31 && (vehicle = g_hero_state.vehicle) != 0) {
        vec_build_spherical_offset(offset, g_lock_on_offset_radius, *(float *)(vehicle + 0xF8), -*(float *)(vehicle + 0xF4) * 0.5f);
        FastVecAdd(&g_lock_on_targets[0].pos, offset, g_hero_state.vehicle + 0x10);
        if (g_lock_on_marker == 0) {
            g_lock_on_marker = cam_alloc_override_slot_pal(5);
            if (g_lock_on_marker == 0)
                goto shift;
        }
        if (*(s16 *)(g_hero_state.vehicle + 0xAA) == 0x905) {
            g_lock_on_marker->x0 = g_lock_on_marker_x_a;
            g_lock_on_marker->xC = -1.0f;
            g_lock_on_marker->x8 = -1.0f;
        } else {
            g_lock_on_marker->x0 = g_lock_on_marker_x_b;
            g_lock_on_marker->xC = g_lock_on_marker_xc;
            g_lock_on_marker->x8 = g_lock_on_marker_x8;
        }
        g_lock_on_marker->x1F = 1;
        FastVecSub(g_lock_on_marker->pos, &g_lock_on_targets[0].pos, &g_hero_position_vec);
        goto shift;
    }
    if (g_lock_on_targets[2].owner == g_lock_on_targets[1].owner)
        g_lock_on_targets[1].unk1C = g_lock_on_targets[2].unk1C + 1;
    if (g_lock_on_targets[1].owner != g_lock_on_targets[0].owner && g_lock_on_targets[1].owner != 0) {
        limit = g_lock_on_targets[1].unk1C;
        if (limit < g_lock_on_hold_frames)
            limit = g_lock_on_hold_frames;
        g_lock_on_targets[0].unk18++;
        if (g_lock_on_targets[0].unk18 >= limit) {
            CopyTarget(&g_lock_on_targets[0], &g_lock_on_targets[1]);
            g_lock_on_targets[0].valid = 1;
        }
    } else if (g_lock_on_targets[0].valid == 0) {
        CopyTarget(&g_lock_on_targets[0], &g_lock_on_targets[1]);
        g_lock_on_targets[0].valid = 1;
    }
    if (g_lock_on_targets[0].owner != 0) {
        if (g_lock_on_marker == 0) {
            g_lock_on_marker = cam_alloc_override_slot_pal(5);
            if (g_lock_on_marker == 0)
                goto shift;
        }
        g_lock_on_marker->x0 = 7.0f;
        g_lock_on_marker->x1F = 1;
        FastVecSub(g_lock_on_marker->pos, &g_lock_on_targets[0].pos, &g_hero_position_vec);
    } else if (g_lock_on_marker != 0) {
        cam_end_override(g_lock_on_marker);
        g_lock_on_marker = 0;
    }
shift:
    CopyTarget(&g_lock_on_targets[2], &g_lock_on_targets[1]);
    memset(&g_lock_on_targets[1], 0, 48);
    g_lock_on_targets[1].unk18 = 65535;
    g_lock_on_targets[1].dist = 100000.0f;
    g_lock_on_targets[0].valid = 0;
}
