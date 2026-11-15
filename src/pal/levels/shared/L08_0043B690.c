#include "names.h"
/* func_PAL_L08_0043B690, the PAL copy of func_L08_00435A78: the same C, with PAL's text ids,
   the 50 Hz scale on its timers and random periods, and 1.44f on the final speed and blend. */
#include "common.h"

typedef struct L08Thing L08Thing;

extern void moby_mark_spawned(void *);
extern void anim_start_blended(void *, int, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern float math_random_float_range(float, float);
extern float FastVecLength(void *);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_range(int, int);
extern float vec_distance_xy(char *, void *);
extern void mystic_handle_entity_list(L08Thing *);

extern u8 D_001A7A40[] __attribute__((sda));
extern s32 D_L08_001A8F00[] __attribute__((sda));

extern void moby_set_state(void *, int, int);
extern s32 level_get_saved_count(void);
extern void moby_disable_object_list_flags(void), moby_reset_vars_defaults(void *);
extern int hero_is_reachable_for_count(void *, int, float);
extern void level_apply_index_for_key(void *), text_print_localized_formatted(int, ...);
extern int req_push_queue(void *, int), game_is_either_mode_two(void);
extern void req_launch_queued(void *), moby_set_byte_on_group(int, int), moby_restore_object_list_flags(void);
extern void STUB_printf(const char *, ...);
extern int MemcardSave(int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void func_L00_0030C710(int);
extern int FastDecTimer(void *), math_fast_float_d(void *), FloatToInt(float);
extern float mat_fast_helper_a(float, float), FastDiffRots(float, float);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float), vec_length_xy(void *);
extern void FastVecSub(void *, void *, void *);
extern void moby_update_eased_node(void *, void *, int, float, float);

/* The hero: read at 0x80 (centre), 0xE0 (position) and 0x110 (velocity). */
typedef struct {
    u8 pad0[0x80];
    char x80[0x60];
    f32 pos[4];
    u8 padF0[0x20];
    f32 x110[4];
} L08Hero;
extern L08Hero g_hero_state;

/* One 0x100-byte entity of the table at D_L08_001B29DC. */
typedef struct {
    u8 pad0[0x31];
    u8 x31;
    u8 pad32[2];
    u16 x34;
    u8 pad36[0xBC - 0x36];
    u8 xBC;
    u8 padBD[0x100 - 0xBD];
} L08Moby;
extern L08Moby *D_L08_001B29DC MACRO_ADDR;

/* Words retail never moves into a delay slot are fields read at an offset from
   an earlier symbol; bare names are loaded by $gp in a slot (docs/build/compiler-notes.md). */
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_L08_001A7C80[] __attribute__((sda));
extern int D_L08_001B2724[] __attribute__((sda));
extern int D_L08_001B2508 MACRO_ADDR;
extern int D_L08_001B1FA8 MACRO_ADDR;
extern int g_player_bolts MACRO_ADDR;
extern u8 D_001395B8[];
extern int D_00138324;
extern int D_L08_00295E50[];
extern u8 D_L08_001BFD00[];
extern char D_L08_001B1FB0[];

#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))

/* An interaction state machine at byte 0x20: offers an item for its price while
   the quantity at D_001A7A00+0x1A covers it, then buys the remaining quantity back
   at 1000 (10000 with the flag at D_001A7A00+0xA) each; afterwards aims the head at the hero. */
void func_PAL_L08_0043B690(u8 *self)
{
    float dest[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    u8 *data = *(u8 **)(self + 0x68);
    int n, active;
    float speed, yaw, pitch, angle;
    float blend;

    mystic_handle_entity_list((L08Thing *)self);
    if (D_L08_001A8F00[0] == 6) {
        self[0x31] = 0;
        H(self, 0x34) |= 1;
        F(self, 0xF4) = -3.14159274f;
    } else {
        self[0x31] = 1;
        F(self, 0xF4) = 0;
        H(self, 0x34) &= 0xFFFE;
    }
    if (D_L08_001B2508 == 5)
        level_get_saved_count();
    switch (self[0x20]) {
    case 0:
        if (!D_001395B8[0x1C])
            moby_disable_object_list_flags();
        else if (I(data, 0x124) != -1) {
            moby_mark_spawned(&D_L08_001B29DC[I(data, 0x124)]);
            I(data, 0x124) = -1;
        }
        level_get_saved_count();
        moby_reset_vars_defaults(self);
        if (D_001395B8[0x1C]) {
            if ((*(s16 *)(D_001A7A00 + 0x1A)) <= 0)
                moby_set_state(self, 6, -1);
            else
                moby_set_state(self, 7, -1);
        } else if (D_001395B8[0x1B]) {
            if ((*(s16 *)(D_001A7A00 + 0x1A)) < (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
                moby_set_state(self, 3, -1);
            else
                moby_set_state(self, 4, -1);
        } else
            moby_set_state(self, 1, -1);
        break;
    case 1:
        if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            level_apply_index_for_key(self);
            if (req_push_queue(D_L08_001BFD00, 0x59)) {
                D_001395B8[0x1B] = 1;
                req_launch_queued(D_L08_001BFD00);
                moby_set_state(self, 2, -1);
            }
        }
        break;
    case 2:
        if (D_L08_001A8F00[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (I(data, 0x124) != -1 && D_L08_001A8F00[0] == 2) {
            D_L08_001B29DC[I(data, 0x124)].x34 |= 1;
            D_L08_001B29DC[I(data, 0x124)].x31 = 0;
        }
        D_L08_001B2724[1] = 1;
        if (!game_is_either_mode_two()) {
            D_L08_001B2724[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            if (I(data, 0x124) != -1) {
                D_L08_001B29DC[I(data, 0x124)].x34 &= 0xFFFE;
                D_L08_001B29DC[I(data, 0x124)].x31 = 1;
            }
            if ((*(s16 *)(D_001A7A00 + 0x1A)) < (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
                moby_set_state(self, 3, -1);
            else
                moby_set_state(self, 4, -1);
        }
        break;
    case 3:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) >= (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
            moby_set_state(self, 4, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            text_print_localized_formatted(0x12F6, (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]), -1);
            level_apply_index_for_key(self);
        }
        break;
    case 4:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) < (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]))
            moby_set_state(self, 3, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            text_print_localized_formatted(0x12E8, (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]), -1);
            level_apply_index_for_key(self);
            if (D_00138324 & 0x10) {
                req_push_queue(D_L08_001BFD00, 0x5A);
                (*(s16 *)(D_001A7A00 + 0x1A)) -= (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2]);
                req_launch_queued(D_L08_001BFD00);
                moby_set_state(self, 5, -1);
            }
        }
        break;
    case 5:
        if (D_L08_001A8F00[0] == 2) {
            self[0x31] = 0;
            H(self, 0x34) |= 1;
        }
        if (I(data, 0x124) != -1 && D_L08_001A8F00[0] == 2) {
            moby_mark_spawned(&D_L08_001B29DC[I(data, 0x124)]);
            I(data, 0x124) = -1;
        }
        D_L08_001B2724[1] = 1;
        if (!game_is_either_mode_two()) {
            D_L08_001B2724[1] = 0;
            self[0x31] = 1;
            H(self, 0x34) &= 0xFFFE;
            if (self[0x21] != 0xFF)
                moby_set_byte_on_group(self[0x21], 1);
            D_001395B8[0x1C] = 1;
            moby_restore_object_list_flags();
            STUB_printf(D_L08_001B1FB0);
            if (I(data, 0x124) != -1) {
                moby_mark_spawned(&D_L08_001B29DC[I(data, 0x124)]);
                I(data, 0x124) = -1;
            }
            if (I(data, 0x120) != -1)
                D_L08_001B29DC[I(data, 0x120)].xBC = 1;
            MemcardSave(0, -1);
            if ((*(s16 *)(D_001A7A00 + 0x1A)) <= 0)
                moby_set_state(self, 6, -1);
            else
                moby_set_state(self, 7, -1);
        }
        break;
    case 6:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) > 0)
            moby_set_state(self, 7, -1);
        else if (hero_is_reachable_for_count(self, 10, 2.5f)) {
            if (!D_L08_001B1FA8)
                text_print_localized_formatted(0x1322, 0, -1);
            else
                text_print_localized_formatted(0x12F9, -1);
            level_apply_index_for_key(self);
        }
        break;
    case 7:
        if ((*(s16 *)(D_001A7A00 + 0x1A)) <= 0)
            moby_set_state(self, 6, -1);
        else {
            n = D_001A7A00[0xA] ? 10 : 1;
            if (hero_is_reachable_for_count(self, 10, 2.5f)) {
                n *= 1000;
                text_print_localized_formatted(0x12E9, (*(s16 *)(D_001A7A00 + 0x1A)), (*(s16 *)(D_001A7A00 + 0x1A)) * n, -1);
                level_apply_index_for_key(self);
                if (D_00138324 & 0x10) {
                    level_get_saved_count();
                    g_player_bolts += (*(s16 *)(D_001A7A00 + 0x1A)) * n;
                    snd_play_from_class_bank(0, 0, self, math_random_int_range(13, 17));
                    (*(s16 *)(D_001A7A00 + 0x1A)) = 0;
                    func_L00_0030C710(150);
                    moby_set_state(self, 8, -1);
                }
            }
        }
        break;
    case 8:
        H(self, 0x96)++;
        if (H(self, 0x96) > 0x7FF8)
            H(self, 0x96) = 0x7FF8;
        if (H(self, 0x96) > 33 && H(self, 0x96) < 75 && H(self, 0x96) % 3 == 0)
            snd_play_from_class_bank(0, 0, self, math_random_int_range(13, 17));
        if (hero_is_reachable_for_count(self, 10, 2.5f))
            text_print_localized_formatted(0x1322, D_L08_001B1FA8, -1);
        else
            moby_set_state(self, 6, -1);
        break;
    }
    if (self[0x20]) {
        if (self[0x43] == 1 && FastDecTimer(data + 0x11E)) {
            H(data, 0x11E) = FloatToInt((math_random_float_range(1200, 2400) * 5 + 2) * 0.16666667f);
            if (self[0x43] != 2)
                anim_start_blended(self, 2, 0, 8);
        } else if ((self[0x60] & 2) && self[0x43] != 1)
            anim_start_blended(self, 1, 0, 8);
    }
    speed = 0.02f;
    blend = 0.3f;
    active = 0;
    if (self[0x43] == 1) {
        active = 1;
        if (vec_distance_xy((char *)self + 0x10, g_hero_state.x80) < 8 &&
            FastDiffRots(F(self, 0xF8), mat_fast_helper_a(g_hero_state.pos[0] - F(self, 0x10),
                                                       g_hero_state.pos[1] - F(self, 0x14))) < 1.57079649f) {
            if (FastVecLength(g_hero_state.x110) > 0.01f)
                I(data, 0x114) = 100;
            else
                math_fast_float_d(data + 0x114);
        } else if (I(data, 0x114)) {
            I(data, 0x114) = 0;
            qcopy(data + 0x100, g_hero_state.pos);
        }
        if (math_fast_float_d(data + 0x118)) {
            I(data, 0x118) = FloatToInt((math_random_float_range(180, 300) * 5 + 2) * 0.16666667f);
            angle = FastAddRotations(F(self, 0xF8), math_random_float_range(-90, 90) * 0.0174532942f);
            pitch = math_random_float_range(0, 30) * 0.0174532942f;
            vec_build_spherical_offset(data + 0x100, 6, angle, pitch);
            FastVecAdd(data + 0x100, data + 0x100, self + 0x10);
        }
        if (I(data, 0x114)) {
            qcopy(dest, g_hero_state.pos);
            speed = 0.04f;
            blend = 0.3f;
        } else
            qcopy(dest, data + 0x100);
    }
    if (active) {
        qcopy(pos, self + 0x10);
        pos[2] += 2;
        FastVecSub(delta, dest, pos);
        yaw = fast_subtract_rotations(mat_fast_helper_a(delta[0], delta[1]), F(self, 0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(delta), delta[2]);
        if (yaw > 1.57079649f)
            yaw = 1.57079649f;
        else if (yaw < -1.57079649f)
            yaw = -1.57079649f;
        if (pitch > 0.52359885f)
            pitch = 0.52359885f;
        else if (pitch < -0.52359885f)
            pitch = -0.52359885f;
        F(data, 0x64) = pitch;
        F(data, 0x68) = yaw * 0.6f;
        F(data, 0xE8) = yaw * 0.4f;
    }
    if (D_001A7A40[0])
        F(data, 0x70) = 2.75f;
    moby_update_eased_node(self, data, 0, speed * 1.44f, blend * 1.44f);
    moby_update_eased_node(self, data + 0x80, 1, speed * 1.44f, blend * 1.44f);
}
