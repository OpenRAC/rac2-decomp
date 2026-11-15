#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;

/* func_L22_003C9880: the level's pulse settings, read as {low, high} pairs.  A pair's
 * first word is a plain small-data symbol (one instruction, so it can take a call's
 * delay slot, where the assembler gives it the $gp form), its second word
 * `[1]` an offset address, which stays the absolute macro load.  The colour pair
 * at 0x001AFF18 also reads its first word through $gp outside a delay slot:
 * common.h's SDATA view, spelled out (this unit does not include common.h). */
extern float D_L22_001AFF08[] __attribute__((sda));
extern float D_L22_001AFF10[] __attribute__((sda));
extern int D_L22_001AFF18[] __attribute__((sda));
extern int D_L22_001AFF18_gp[] __asm__("D_L22_001AFF18__gp") __attribute__((section(".sdata")));
extern float D_L22_001AFF20[] __attribute__((sda));
extern float D_L22_001A7CD8[] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));

/* The per-subtitle history src/game/00289178.c updates (12-byte rows). */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern SubtitleHistory g_subtitle_history[];

extern void moby_set_state(void *, int, int);
extern f32 math_random_float_range(f32 low, f32 high);
extern int PlayMobySound(int index, int a1, char *a2);
extern int subtitle_request_voice_line(int, int);
extern f32 FastVecDot(void *, void *);
extern void spark_emit_random(char *);
extern void spark_lane_draw(u8 *);
extern void gfx_add_draw_callback_first(void (*)(u8 *), void *);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern int FastTweenColor(int, int, f32);

/* Family cbc1388ebe801e68 (116 B, 2 placements): arm one animation slot on a
 * resident object.  Two global guards, a "current slot" guard, then five
 * resident stores in the retail order.
 *
 * The indexed read `p + a1 * 4 + 1152` must be written as a named byte pointer
 * (`w = p + a1 * 4`) followed by the load at `w + 1152`: when the 1152 is folded
 * into the same PLUS chain, gcc canonicalises the commutative `addu` with the
 * scaled index as the first source operand, one byte away from retail.
 */

extern u8 D_001A63A8_4[];

/* func_L22_003A5018 is defined in L22_003A5018-hud-g8.c. */

/* func_L22_003A5BD8 is in L22_003A5BD8-effects-g32.c. */

/* func_L22_003A5F90 is matched in L22_003A5F90.c. */

extern int list_is_key_missing(int);

/* Checks that exactly one bit is set in the given value and that the matching entry passes its test; returns 1 if so, otherwise 0. */
int mask_is_single_bit_set_and_valid(f32 maskValue) {
    union { f32 f; unsigned int u; } bits;
    int bitCount = 0;
    int i;
    int bitIndex = 0;

    bits.f = maskValue;
    for (i = 0; i < 32; i++) {
        if (bits.u & 1) {
            bitCount++;
            if (bitCount >= 2)
                return 0;
            bitIndex = i;
        }
        bits.u >>= 1;
    }
    if (bitCount == 0)
        return 0;
    if (bitCount == 1) {
        if (list_is_key_missing(bitIndex) == 0)
            return 1;
    }
    return 0;
}

/* func_L22_003A6230 is defined in L22_003A6230-g8.c. */

/* shared native body of family cbc1388ebe801e68 */
/* Starts the animation in the given slot on an object, unless another one is already running, and sets its timer. */
void anim_start_slot(u8 *moby, int slot) {
    u8 *animState = D_001A63A8_4;
    u8 *vars = *(u8 **)(moby + 104);
    int bit;
    if (*(int *)(animState + 104) != 0) return;
    if (*(int *)(animState + 36) != -1) return;
    if (slot == *(int *)(vars + 1256)) return;
    bit = 1 << slot;
    { u8 *entry = vars + slot * 4; *(int *)(animState + 36) = (*(int *)(entry + 1152) & 0x3fff) + 2000; }
    *(int *)(animState + 40) = 0;
    *(int *)(vars + 1256) = slot;
    *(int *)(vars + 1252) = 1800;
    *(int *)(vars + 1248) |= bit;
}

extern int math_random_int_below(int a0);

extern void anim_start_free_slot_in_range(u8 *a0, int a1, int a2);

/* Arm one animation slot in the range [a1, a2]: a random slot of the range is
 * tried first and the next one after it, wrapping around, until a free slot
 * is found; when every slot of the range is taken, the range is cleared and
 * the last slot tried is armed.
 *
 * The mask lives in the controller at +0x4E0 of the object at +0x68.
 */
void anim_start_free_slot_in_range(u8 *moby, int first, int last) {
    u8 *ctl = *(u8 **)(moby + 0x68);
    int count;
    int offset;
    int i;

    if (last < first)
        return;
    count = last - first + 1;
    offset = math_random_int_below(count);
    for (i = 0; i < count; i++) {
        int slot = first + offset;
        if (((*(int *)(ctl + 0x4E0) >> slot) ^ 1) & 1) {
            anim_start_slot(moby, slot);
            return;
        }
        offset = (offset + 1) % count;
    }
    i = 0;
    if (count > 0) {
        int mask = *(int *)(ctl + 0x4E0);
        for (; i < count; i++) {
            mask &= ~(1 << (first + i));
        }
        *(int *)(ctl + 0x4E0) = mask;
    }
    anim_start_slot(moby, first + offset);
}

/* A three-label switch, the third one sharing the default's body: with only two cases cc1
 * emits a comparison chain, and the third label is what makes it build the decision tree
 * (`beq` on the high case, then an `slti` guard on the range, then `bne` on the low one). */
/* Returns a float setting from the object's private data, picked by the object's class. */
f32 moby_get_class_setting_value(u8 *moby) {
    switch (*(short *)(moby + 0xAA)) {
    case 0xE3A /* moby class 3642 */: return *(f32 *)(*(u8 **)(moby + 0x68) + 0x2C);
    case 0xE3B /* moby class 3643 */: return *(f32 *)(*(u8 **)(moby + 0x68) + 0x44);
    case 0xE3C /* moby class 3644 */:
    default: return *(f32 *)(*(u8 **)(moby + 0x68) + 0x44);
    }
}

/* func_L22_003A6640 is defined in L22_003A6640-g8.c. */

extern u8 g_hero_state[];
extern f32 fast_vec_dist(void *a0, void *a1);
extern void hero_restart_in_mode(int a0, int a1, void *a2);

/* Per-frame update for moby class 637: when the player is close, it starts an effect on this object. */
void proximity_effect_update(u8 *moby) {
    if (g_hero_state[0x22B4] != 0) return;
    if (fast_vec_dist(g_hero_state + 0x80, moby + 0x10) < 4.0f) {
        hero_restart_in_mode(2, 0x56, moby);
    }
}

extern int FloatToInt(f32);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern int coll_sweep_from_object(void *, void *, int, f32, f32, f32, int, int, int);

/* Halves whatever the two floats say, doubles it back, rescales it by the
 * controller's rate, then hands the result to the placement call as the alpha;
 * the controller's counter also drives the byte at +0x23 (a 127/40 ramp). */
/* Per-frame update for moby class 1427: rescales the object, fades it in with a timer, places an effect on it and removes it when the timer ends. */
void fading_scaled_moby_update(u8 *moby) {
    u8 *obj = moby;
    u8 *sub = *(u8 **)(obj + 0x24);
    u8 *ctl = *(u8 **)(obj + 0x68);
    u8 *resident;
    f32 v;
    int n;

    v = *(f32 *)(obj + 0x2C) / *(f32 *)(sub + 0x24) * 0.5f;
    v += *(f32 *)(ctl + 0x0);
    *(f32 *)(obj + 0x2C) = v + v;
    *(f32 *)(obj + 0x2C) = *(f32 *)(obj + 0x2C) * *(f32 *)(sub + 0x24);
    n = *(int *)(ctl + 0x8);
    if (n < 0x28) *(u8 *)(obj + 0x23) = n * 127 / 40;
    resident = g_hero_state;
    coll_sweep_from_object(*(void **)(resident + 0x2290), obj + 0x10, 0x30000, v,
                  (f32)FloatToInt(*(f32 *)(ctl + 0xC)), 1.0f, 0, 1, 0);
    if (math_fast_float_d(ctl + 0x8))
        moby_mark_spawned(obj);
}

/* State 0 seeds four lanes (phase offsets, random rates and values); state 1
 * reacts to the player (distance, sound, subtitle 31's history, a facing test that
 * runs func_L22_003C9B60 and registers func_L22_003C9D48); while visible the
 * phase advances and drives the packed colour at +0x78.  Reading the player through pointer locals
 * lets cse derive the first one from the position address the distance call
 * took (`addiu $a0,$s1,-0x80`) and rebuild the second, as retail does. */
/* Per-frame update for moby class 2489: sets up four flickering lanes, reacts to the player being near, throws sparks and pulses its colour. */
void spark_lane_update(u8 *obj)
{
    u8 *ctl = *(u8 **)(obj + 0x68);
    int state = obj[0x20];
    int i;

    switch (state) {
    case 0:
        moby_set_state(obj, 1, -1);
        *(short *)(obj + 0x32) = 255;
        {
            float *offset, *rate, *radius;
            i = 0;
            radius = (float *)(ctl + 0x10);
            rate = (float *)(ctl + 0x30);
            offset = (float *)(ctl + 0x20);
            for (; i < 4; i++) {
                *offset++ = (float)i * 0.25f;
                *rate++ = math_random_float_range(D_L22_001AFF08[0], D_L22_001AFF08[1]) * (1.0f / 60.0f);
                *radius++ = math_random_float_range(D_L22_001AFF10[0], D_L22_001AFF10[1]);
            }
        }
        break;
    case 1: {
        u8 *player;
        SubtitleHistory *history;

        if (fast_vec_dist(g_hero_state + 0x80, obj + 0x10) < 3.0f)
            D_L22_001A7CD8[0] = *(float *)ctl;
        player = g_hero_state;
        if (*(int *)(player + 0x2294) == 0x81 && *(int *)(player + 0x1B8) == state)
            PlayMobySound(0, 0, (char *)obj);
        history = g_subtitle_history;
        {
            /* unsigned int snapshot: retail tests the u16 with an andi and
             * increments the unmasked value */
            unsigned int count = history[31].count;
            if ((unsigned short)count <= 65534) {
                u8 *player2 = g_hero_state;
                if (*(int *)(player2 + 0x2294) == 0x81)
                    history[31].count = 65535;
                else if (*(u8 **)(player2 + 0x33C) == obj) {
                    /* each arm reads the clock itself: reorg merges the two
                     * reads into the branch's delay slot */
                    if ((unsigned short)count != 0) {
                        unsigned int last = history[31].time;
                        if (D_001A7390[0] - last > 1080 || last == 0)
                            subtitle_request_voice_line(2504, 31);
                        else if (last < D_001A7390[0])
                            history[31].time = D_001A7390[0];
                    } else {
                        history[31].count = count + 1;
                        if (history[31].time < D_001A7390[0])
                            history[31].time = D_001A7390[0];
                        history[31].levels =
                            (history[31].levels | (1 << g_current_map_index[0])) | 0x80000000;
                    }
                }
            }
        }
        if (FastVecDot(obj + 0xE0, g_hero_state + 0x2C0) < -0.6f) {
            spark_emit_random((char *)obj);
            gfx_add_draw_callback_first(spark_lane_draw, obj);
        }
        break;
    }
    }
    if (obj[0x31]) {
        float f;
        *(float *)(ctl + 4) = FastAddRotations(*(float *)(ctl + 4),
                                            D_L22_001AFF20[0] * 0.0002908882452175021f);
        f = math_fast_sin_or_cos_b(*(float *)(ctl + 4));
        f = f * f;
        f = f * f;
        *(int *)(obj + 0x78) = FastTweenColor(D_L22_001AFF18_gp[0], D_L22_001AFF18[1], f * f);
    }
}

/* func_L22_003C9B60 is defined in L22_003C9B60-g8.c. */

/* func_L22_003C9D48 is in L22_003C9D48-g8.c. */

extern void *part_find_owned_effect_slot(void *a0, int a1, int a2);

extern int math_random_int_below(int a0);

extern int snd_play_from_class_bank(int index, int value, char *object, int kind);

extern void part_spawn_explosion_with_sparks(void *a0, void *a1, int a2, float f12, float f13);

extern int PlayMobySound(int index, int a1, char *a2);

extern void vec_scale_to_length(float *a0, void *a1, float f12);

extern void part_spawn_masked_debris(void *a0, int a1, void *a2, unsigned char a3,
                           float f12, float f13, float f14, float f15);

extern void moby_mark_spawned(void *object);

/* Blows the object up: plays a random sound, adds an effect and a burst of sparks, then removes it. */
void moby_explode(u8 *moby, int a1, int a2) {
    u8 *obj = moby;
    void *target;
    int soundBase;
    int soundId;
    float offset[4];

    target = part_find_owned_effect_slot(moby, -1, 0);
    if (target == 0)
        return;
    if (*(short *)(obj + 0xAA) == 0x1213 /* moby class 4627 */) {
        soundBase = 0xB;
        soundId = 0xF7F;
    } else {
        soundBase = 0xC;
        soundId = 0xE0B;
    }
    snd_play_from_class_bank(soundBase + math_random_int_below(3), 0, obj, soundId);
    part_spawn_explosion_with_sparks(obj, obj + 0x10, -1, 2.0f, 13.0f);
    PlayMobySound(0, 0, obj);
    vec_scale_to_length(offset, target + 0x10, 0.23333335f);
    part_spawn_masked_debris(obj, 3, offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(obj);
}

extern void moby_explode(u8 *a0, int a1, int a2);

/* Runs the explosion routine for the object and makes it fully visible. */
void moby_trigger_explosion(u8 *moby) {
    int vars = *(int *)(moby + 0x68);
    moby_explode(moby, vars, vars);
    *(u8 *)(moby + 0x30) = 0xFF;
}

/* func_L22_003F45D8 is in L22_003F45D8-g8.c. */

/* func_L22_003F52D8 is in L22_003F52D8-g8.c. */

/* func_L22_003F54B8 is in L22_003A5018-g8.c. */

/* func_L22_003F5580 is in L22_003A5018-g8.c: it reaches the level's scale factor
 * through $gp, which this -G0 unit cannot produce. */

/* func_L22_003F5688 is defined in L22_003F5688.c. */

/* func_L22_003F58F8 is defined in L22_003A5018-g8.c (it reads $gp data outside a delay slot). */

/* func_L22_003F85A0 is defined in L22_003F85A0-flags-g8.c. */

/* func_L22_003F8658 is defined in L22_003F8658-helper-g8.c. */

/* func_L22_003FB1F8 is in L22_003FB1F8-g8.c. */

/* func_L22_003FB310 is defined in L22_003FB310-g8.c. */

/* func_L22_003FB9B8 is defined in L22_003FB9B8-g8.c. */

/* func_L22_003FBBF0 is in L22_003FBBF0-particles-g8.c. */

/* func_L22_003FC048 is in L22_003FC048-particles-g32.c. */

/* func_L22_003FC338 is defined in L22_003A5018-g8.c. */

/* func_L22_003FC780 is defined in L22_003FC780-helper-g8.c. */


/* func_L22_003FCF08 is defined in L22_003FCF08-g8.c. */

/* func_L22_003FD1E8 is defined in L22_003FD1E8-helper-g8.c. */

/* func_L22_003FD2D8: see L22_003FD2D8-g8.c. */

/* func_L22_003FD958 is defined in L22_003FD958-g8.c. */

/* func_L22_0040DD40 is defined in L22_0040DD40-helper-g8.c. */

extern f32 math_random_float_range(f32 low, f32 high);

extern char *SpawnExplosion(void *a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                          int a8, int a9, int a10, int a11, f32 f12, f32 f13);

/* Starts an effect on the object with a random size between 0.8 and 1.2. */
void part_start_random_scale_effect(u8 *moby) {
    f32 scale = math_random_float_range(0.8f, 1.2f);
    SpawnExplosion(moby, 0, 5, 4, 4, 4, 4, 0, 0, 0, 0, 0, scale, 20.0f);
}
