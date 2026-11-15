#include "include_asm.h"
#include "common.h"

extern float math_square(float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern void vec_transform_or_copy(char *, char *);
extern int FastDecTimer(char *);
extern void part_kill(char *);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecScale(char *, char *, float);
extern void vec_scale_to_length(float *, float *, float);

typedef struct { char pad[0x20]; int buffer; char pad24[0xAC]; int saved; } CaptureState;
extern int D_001B1598 MACRO_ADDR __attribute__((sda));
extern int g_screen_height MACRO_ADDR __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern void gfx_wait_for_dma_status_bits(int);
extern void FlushCache(int);

extern int F250fbfa4_FUN_00282978(char *p);

extern void F250fbfa4_FUN_002B9180(char *p);

extern void F250fbfa4_FUN_00282CC0(char *p0, char *p1, char *p2);

extern int Ff4dd22f3_FUN_00282978(char *p);

extern void Ff4dd22f3_FUN_002B9180(char *p);

extern void Ff4dd22f3_FUN_00282CC0(char *p, char *q, float *v);

extern int Fc40b1162_FUN_00282978();

extern void Fc40b1162_FUN_002B9180();

extern void Fbdd4a4aa_FUN_00300190(char *a, char *b);

extern void Fbdd4a4aa_FUN_00282CC0(char *a, char *b, char *c);

extern void Fbdd4a4aa_FUN_00282D30(char *a, char *b, float f);

extern void Fbdd4a4aa_FUN_002FE8D8(char *a, char *b);

extern int Fbdd4a4aa_FUN_00283D38(unsigned int a, int b, float f);

extern void Fbdd4a4aa_FUN_002B9180(char *a);

/* Frozen Batch A A15-struct-pad-20; acknowledged claim 6d4515f9ca5619f8d02349c6c2ad116dc989f5a4c317c4d31105f9a9271aa080. */
typedef unsigned char BatchA_A15_u8;

typedef unsigned int BatchA_A15_u32;

extern BatchA_A15_u8 D_L15_001FF640[];

/* Frozen Batch A A10-twin-base-32; acknowledged claim b588059f8808a6607867ee41ec367b24cfb85d2f4cc33273a4392842e34233d5. */
typedef unsigned char BatchA_A10_u8;

typedef unsigned int BatchA_A10_u32;

extern BatchA_A10_u8 D_L03_001FF8C0[];

extern BatchA_A10_u8 D_L03_001FFAC0[];

extern int func_00288FB8_1 ();

extern void text_draw_medium (int v, int p7, long k, int r, int m1);

extern void text_draw_right_aligned_medium (int v, int p7, long k, int r, int m1);

typedef int BatchA_A12_s32;

typedef struct { BatchA_A12_s32 a; BatchA_A12_s32 b; } BatchA_A12_BatchA24;

extern BatchA_A12_BatchA24 D_L08_001FF980;

/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls func_0027C540(0)
 *   - Calls func_0029C138()
 *   - Calls func_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void SetupGifPaging(long);
extern void func_0029C138(void);

extern void DoGifPaging(void);


/*
 * Function: func_002D2EE0
 *
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls func_0027C540(0) (with zero argument)
 * - Calls func_0029C7A0()
 * - Calls func_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */


/* External functions declared with exact aliases from task.externals */

/* func_002C7E28 is defined in 002C7E28-qcopy.c. */

/* func_002C7F78 is defined in 002C7F78.c. */

extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastDiffRots(float, float);
extern float math_fabs(float);

extern float Fbdd4a4aa_FUN_002A89A8(char *a, int b, float f);

extern float Fbdd4a4aa_FUN_00283B98(float a, float b);

extern float Fbdd4a4aa_FUN_00283198(float a);

extern void Fbdd4a4aa_FUN_00282F20(char *a, char *b, float f);

extern float Fbdd4a4aa_FUN_00283CE0(int a);

extern int Fbdd4a4aa_FUN_00283CF0(float a);

extern int g_game_time __attribute__((sda));

extern char g_active_camera[];

extern float math_random_float_range(float a, float b);
extern void shop_trigger_current_state_effect(char *a, char *b);

extern void lerp_vector(float *out, float *a, float *b, float t);
extern void FastVecSub(float *out, float *a, float *b);
extern float vec_length_xy(float *v);
extern float mat_fast_helper_a(float y, float x);

extern int D_001F2A30;

extern char *D_001A8CFC[] __attribute__((sda));
extern void popup_set_box_value(void *, int);

extern char g_pause_menu_state[];

/* func_002C9C60 is matched in 002C9C60.c (built with -g). */

extern int g_current_game_mode __attribute__((sda));
extern int D_001A7A08 __attribute__((sda));
extern char D_00259918[];
extern char D_00259AF8[];
extern char D_00259AA8[];
extern int g_current_map_index __attribute__((sda));
extern int D_0025B5F8;
extern void snd_send_cmd22(int);
extern void music_Pause(int);
extern int snd_Pump(void);
extern void ConfigureMenuChoiceList(void);
extern void map_set_current_and_refresh(int);
extern int menu_update_entry_states(void);
extern void menu_update_unlock_entries(void);

typedef struct {
    char pad[0x38];
    char *next;
    char *previous;
} Links_2C9CF8;

typedef struct {
    int f0, pad4, f8;
    char padC[0x10];
    int f1C, f20;
    char pad24[0xB7];
    char byteDB;
    char padDC[0xC];
    int fE8;
    char padEC[0x18];
    unsigned int f104;
    int f108;
    char pad10C[0x14];
    int f120;
    char pad124[0x20];
    int f144, f148, f14C, f150;
    char pad154[0x6C];
    int f1C0, f1C4, f1C8;
} State_2C9CF8;

/* Uploads the saved screen image back to VRAM in 0x4000-byte strips (0x600 bytes per
   line of the current height), from the start buffer or, when a0 is set, ending at
   0x3FB000, after setting the restore mode (2 with a0, else 1) and bumping the frame
   counter. */
typedef struct { long q[12]; } GsLoadImage2C9E60 __attribute__((aligned(16)));
extern int sceGsSyncV(int);
extern int func_00126288(GsLoadImage2C9E60 *, short, short, short, short, short, short, short);
extern int sceGsExecLoadImage(GsLoadImage2C9E60 *, void *);
extern int gfx_wait_paths_idle(int, int);

extern void menu_enter_pause_state(void);
extern unsigned int D_L00_001FEC40[2];

extern void gfx_set_clear_color_packet(int, int, int, int);

/* func_002CAB00 is defined in 002CAB00-g8.c. */

extern short D_001A63AC;
extern int D_001C51D0;
extern int g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
extern int request_end_slot(int, int);
extern int request_begin_slot(int, int, int, int, void *);
extern void snd_pump_music_and_disc_read(int);
extern void LoadClassIntoFreeCacheSlot(int);

typedef struct {
    char pad00[0x1C];
    int mode;
    char pad20[0x04];
    volatile int count;
    char pad28[0x08];
    int field30;
    char pad34[0x0C];
    int field40;
    char pad44[0xB0];
    int fieldF4;
} GameState_1F2840;

extern int menu_send_request(int, char *);
extern char D_0025BA90[];

extern short D_0018A000[];
extern void level_set_dependent_value(void);

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState_2CC490;

typedef struct {
    char reserved00[0x1C4];
    int flags;
} GameState_2CC490;

extern char g_pad_state[];

/* The menu entries are 0x50 apart; D_001B1680 holds the selection and D_001A8B84
 * whether it is enabled. Both scalars and the enable flags are small data: the
 * -G0 compiler addresses them absolutely, and $gp-relative only in delay slots. */
typedef struct { char pad[0x1C4]; int flags; } InputState_2CCF68;
typedef struct { short x, kind; int a, b; } MenuEntry_2CCF68;
extern char D_00259148[], D_00259198[], D_002591E8[], D_00259238[], D_00259288[], D_002592D8[];
extern int UpdateMenuListActions(char *);
extern int D_001A8B84 __attribute__((sda));
extern int D_001B1680 __attribute__((sda));
typedef struct { unsigned char value; } ResidentFlag_2CCF68;
extern ResidentFlag_2CCF68 D_001A7BC9 __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCA __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCB __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCC __attribute__((sda));
extern ResidentFlag_2CCF68 D_001A7BCE __attribute__((sda));

extern int D_00138344;

extern int func_0029C168(int);

extern unsigned int stub_empty_23(void);

extern unsigned int stub_empty_24(void);

extern unsigned int stub_empty_25(void);

extern unsigned int stub_empty_26(void);

extern unsigned int stub_empty_27(void);

extern unsigned int stub_empty_28(void);

extern int menu_handle_step_simple(int);

extern int menu_handle_mode_action(int);

extern int menu_run_action_by_index(int);

extern int menu_handle_command(int);

extern void snd_play_from_global_bank(int, unsigned int, void *);

typedef struct {
    char reserved00[0x44];
    int state;
    char reserved48[0x8];
    int handle;
    int last;
    int current;
} MenuObject_2CD4E0;

typedef struct {
    char reserved00[0x10];
    int flags;
} ToggleState_2CD4E0;

extern MenuObject_2CD4E0 D_00259C78;
extern ToggleState_2CD4E0 *D_00259C44;
extern int func_0029C248(int first, void *second);
extern int menu_get_setting_value(void);

/* func_002C7748 is defined in 002C7748-create-g8.c. */

/* Updates a particle that fades in or out while it drifts and falls. It is removed when its life runs out. */
void part_update_fading_drift_alt(char *particle)
{
    char velocity[16];
    char *self = particle;
    char *motion;
    int color_word;
    int new_alpha;
    char *position;

    if (F250fbfa4_FUN_00282978(particle + 10) != 0) {
        F250fbfa4_FUN_002B9180(particle);
        return;
    }
    motion = particle + 32;
    color_word = *(int *)(self + 4);
    new_alpha = (color_word >> 24) + *(unsigned char *)(motion + 20);
    *(int *)(self + 4) = (color_word & 0x00ffffff) | (new_alpha << 24);
    position = self + 16;
    *(float *)(velocity + 0) = *(float *)(self + 32);
    *(float *)(velocity + 4) = *(float *)(motion + 4);
    *(float *)(velocity + 8) = *(float *)(motion + 8);
    *(int *)(velocity + 12) = 0;
    F250fbfa4_FUN_00282CC0(position, position, velocity);
    *(float *)(motion + 8) = *(float *)(motion + 8) - *(float *)(motion + 12);
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 21);
    *(float *)(self + 12) = *(float *)(self + 12) + *(float *)(motion + 16);
}

/* func_002C7BB8 is defined in 002C7BB8.c. */

/* Updates a particle that fades while it drifts, falls and changes size. It is removed when its life runs out. */
void part_update_size_changing(char *particle)
{
    char *motion = particle + 32;
    float velocity[4];
    int color_word;

    if (Ff4dd22f3_FUN_00282978(particle + 10) != 0)
    {
        Ff4dd22f3_FUN_002B9180(particle);
        return;
    }

    color_word = *(int *)(particle + 4);
    *(int *)(particle + 4) = (color_word & 0xffffff) | (((color_word >> 24) + (int)*(unsigned char *)(motion + 20)) << 24);
    velocity[0] = *(float *)(particle + 32);
    velocity[1] = *(float *)(motion + 4);
    velocity[2] = *(float *)(motion + 8);
    velocity[3] = 0.0f;
    Ff4dd22f3_FUN_00282CC0(particle + 16, particle + 16, velocity);
    *(unsigned char *)(particle + 8) += *(unsigned char *)(motion + 21);
    *(float *)(particle + 12) += *(float *)(motion + 16);
    *(float *)(motion + 8) -= *(float *)(motion + 12);
}

/* Spins a particle around a centre point and removes it when it has gone round far enough. */
void part_update_orbiting(char *particle)
{
    char *self = particle;
    char *motion = self + 0x20;
    float angle_diff;

    *(u8 *)(self + 8) = *(u8 *)(self + 8) + *(u8 *)(motion + 0x14);
    *(float *)(motion + 8) = FastAddRotations(*(float *)(motion + 8), *(float *)(motion + 0xC));
    *(float *)(self + 0xC) = *(float *)(self + 0xC) + *(float *)(motion + 0x10);
    *(float *)(self + 0x10) = *(float *)(*(char **)(self + 0x20)) +
                            *(float *)(motion + 4) * math_fast_sin_or_cos_a(*(float *)(motion + 8));
    *(float *)(self + 0x18) = *(float *)(*(char **)(self + 0x20) + 8) +
                            *(float *)(motion + 4) * math_fast_sin_or_cos_b(*(float *)(motion + 8));
    angle_diff = FastDiffRots(*(float *)(motion + 8), *(float *)(*(char **)(self + 0x20) + 0x10));
    if (angle_diff < math_fabs(*(float *)(motion + 0xC) + *(float *)(motion + 0xC)))
        part_kill(self);
}

/* Updates a smoke-like particle that falls, drifts sideways and fades, and is removed when its life ends. */
void part_update_falling_smoke(char *particle)
{
    char *self = particle;
    char *motion = particle + 0x20;
    char *position;
    char drift[16];
    float ground_height;
    float life_now;
    float life_total;

    Fbdd4a4aa_FUN_00282D30(motion, motion, 0.9f);
    position = particle + 0x10;
    ground_height = Fbdd4a4aa_FUN_002A89A8(position, 0, 0.5f) + 0.25f;
    if (ground_height < *(float *)(self + 0x18)) {
        *(float *)(motion + 8) = *(float *)(motion + 8) - *(float *)(motion + 12);
        *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 22);
    }
    Fbdd4a4aa_FUN_00282CC0(position, position, motion);
    if (g_game_time % 10 == 0) {
        if (ground_height < *(float *)(self + 0x18)) {
            *(float *)(motion + 0x1C) = Fbdd4a4aa_FUN_00283B98(*(float *)(motion + 0x1C), 1.0f);
            life_total = Fbdd4a4aa_FUN_00283198(*(float *)(motion + 0x1C));
            Fbdd4a4aa_FUN_00282F20(drift, g_active_camera, life_total * 0.0075f);
            Fbdd4a4aa_FUN_00282CC0(motion, motion, drift);
        }
    }
    if (*(short *)(self + 0xA) < *(short *)(motion + 0x14)) {
        life_now = Fbdd4a4aa_FUN_00283CE0(*(short *)(self + 0xA));
        life_total = Fbdd4a4aa_FUN_00283CE0(*(short *)(motion + 0x14));
        *(int *)(self + 4) = (Fbdd4a4aa_FUN_00283CF0(life_now / life_total * 128.0f) << 24) | 0x00050505;
    } else {
        *(int *)(self + 4) = 0x9F050505;
    }
    if (F250fbfa4_FUN_00282978(self + 0xA)) {
        Fbdd4a4aa_FUN_002B9180(self);
    }
}

/* Removes a particle once its life runs out. */
void part_remove_expired(char *particle)
{
    if (Fc40b1162_FUN_00282978(particle + 10)) {
        Fc40b1162_FUN_002B9180(particle);
    }
}

/* func_002C8610 is in 002C8610.c. */

/* Updates a particle that fades while it drifts and falls. It is removed when its life runs out. */
void part_update_fading_falling(char *particle)
{
    char velocity[16];
    char *self = particle;
    char *motion;
    int color_word;
    int new_alpha;
    char *position;

    if (F250fbfa4_FUN_00282978(particle + 10) != 0) {
        F250fbfa4_FUN_002B9180(particle);
        return;
    }
    motion = particle + 32;
    color_word = *(int *)(self + 4);
    new_alpha = (color_word >> 24) + *(unsigned char *)(motion + 20);
    *(int *)(self + 4) = (color_word & 0x00ffffff) | (new_alpha << 24);
    position = self + 16;
    *(float *)(velocity + 0) = *(float *)(self + 32);
    *(float *)(velocity + 4) = *(float *)(motion + 4);
    *(float *)(velocity + 8) = *(float *)(motion + 8);
    *(int *)(velocity + 12) = 0;
    F250fbfa4_FUN_00282CC0(position, position, velocity);
    *(float *)(motion + 8) = *(float *)(motion + 8) - *(float *)(motion + 12);
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 21);
    *(float *)(self + 12) = *(float *)(self + 12) + *(float *)(motion + 16);
}

/* func_002C8A38 is defined in 002C8A38.c. */

/* Like func_002C8A38 with a second vector at +0x30 scaled into the motion. Its
 * address e is an integer: retail loads that vector's last two words only after
 * the first vector is stored, the order alias analysis gives an untraced base. */
/* Updates a particle that changes colour, size and speed over its life, and may restart for a short time before it goes away. */
void part_update_color_changing(char *particle)
{
    char *motion = particle + 32;
    int extra_addr = (int)particle + 48;
    float scaled[4], v[4], w[4], tmp[4];
    int color, alpha, fading, spin;
    float size0, size1, speed0, speed1, scale, t, inverse, life_now, life_total;
    v[3] = 0;
    v[0] = *(float *)(motion + 0); v[1] = *(float *)(motion + 4); v[2] = *(float *)(motion + 8);
    w[0] = *(float *)(extra_addr + 0); w[1] = *(float *)(extra_addr + 4); w[2] = *(float *)(extra_addr + 8); w[3] = 0;
    color = *(unsigned char *)(motion + 12) & 15;
    alpha = (*(unsigned char *)(motion + 12) >> 4) | 0x70;
    color |= (color << 16) | (color << 8);
    spin = *(unsigned char *)(motion + 13) >> 4;
    fading = *(unsigned char *)(motion + 13) & 15;
    size0 = IntToFloat(*(unsigned char *)(motion + 30)) * 1640.625f;
    size1 = IntToFloat(*(unsigned char *)(motion + 31)) * 1640.625f;
    speed0 = IntToFloat(*(unsigned char *)(motion + 28)) * (1.0f / 128);
    speed1 = IntToFloat(*(unsigned char *)(motion + 29)) * (1.0f / 128);
    scale = IntToFloat(*(unsigned char *)(motion + 15)) * (1.0f / 128);
    vec_transform_or_copy(particle + 16, particle + 16);
    t = IntToFloat(*(short *)(particle + 10));
    t /= IntToFloat(*(unsigned char *)(motion + 14)); inverse = 1.0f - t;
    if (!fading) {
        *(int *)(particle + 4) = FastTweenColor(0x103080, color, inverse) | (alpha << 24);
        *(float *)(particle + 12) = size0 + (size1 - size0) * inverse;
        speed0 += (speed1 - speed0) * inverse;
        FastVecScale((char *)scaled, (char *)w, scale * math_square(inverse));
    } else {
        speed0 = speed1;
        life_now = IntToFloat(alpha); life_total = IntToFloat(alpha);
        life_total *= math_square(inverse);
        *(int *)(particle + 4) = color | (FloatToInt(life_now - life_total) << 24);
        FastVecScale((char *)scaled, (char *)w, scale);
    }
    vec_scale_to_length(tmp, v, speed0);
    FastVecAdd(particle + 16, particle + 16, (char *)tmp);
    FastVecAdd(particle + 16, (char *)scaled, particle + 16);
    *(unsigned char *)(particle + 8) += spin;
    if (FastDecTimer(particle + 10)) {
        if (!fading) {
            *(unsigned char *)(motion + 14) = 20;
            *(unsigned char *)(motion + 13) |= 1;
            *(short *)(particle + 10) = 20;
        } else part_kill(particle);
    }
}

/* Updates a swirling particle that slows down, slowly fades out and is removed when it is fully faded. */
void part_update_swirling(int *particle)
{
    char *position = (char *)particle + 16;
    char *motion = (char *)particle + 32;
    char swirl[16];

    Fbdd4a4aa_FUN_00300190(position, position);
    *(int *)(motion + 16) = *(int *)(motion + 16) - 1;
    if (*(int *)(motion + 16) < 0)
        *(int *)(motion + 16) = 0;
    *(unsigned char *)((char *)particle + 8) = *(unsigned char *)((char *)particle + 8) + 1;
    Fbdd4a4aa_FUN_00282CC0(position, motion, position);
    *(float *)((char *)particle + 12) = *(float *)((char *)particle + 12) + 1.5750000000000000000000e+03f;
    Fbdd4a4aa_FUN_00282D30(motion, motion, 9.9000000953674316406250e-01f);
    Fbdd4a4aa_FUN_002FE8D8(position, swirl);
    if ((*(int *)((char *)particle + 4) & 0xFF) < 32) {
        Fbdd4a4aa_FUN_00282D30(swirl, swirl, 1.5000000130385160446167e-03f);
        Fbdd4a4aa_FUN_00282CC0(motion, motion, swirl);
    } else {
        Fbdd4a4aa_FUN_00282D30(swirl, swirl, -7.5000000651925802230835e-04f);
        Fbdd4a4aa_FUN_00282CC0(motion, motion, swirl);
    }
    *(int *)((char *)particle + 4) = Fbdd4a4aa_FUN_00283D38(*(unsigned int *)((char *)particle + 4) & 0x00FFFFFF, 0, 2.5000000372529029846191e-02f)
        | (*(int *)(motion + 16) << 24);
    if (*(int *)(motion + 16) == 0)
        Fbdd4a4aa_FUN_002B9180((char *)particle);
}

/* Updates a particle that grows, drifts and slows down while it fades out, and is removed when its life ends. */
void part_update_growing_fading(char *particle)
{
    char *motion = particle + 32;
    char *position = particle + 16;
    float progress, life_total, fade_amount, growth;
    int alpha_byte, color_word;

    progress = IntToFloat(*(short *)(particle + 10));
    life_total = IntToFloat(*(int *)(motion + 24));
    progress = progress / life_total;
    fade_amount = IntToFloat(*(int *)(motion + 16));
    alpha_byte = FloatToInt(fade_amount * progress);
    color_word = FastTweenColor(0, *(int *)(motion + 20), progress * 0.5f);
    *(char *)(particle + 8) = *(unsigned char *)(particle + 8) + 1;
    growth = math_random_float_range(0.004f, 0.012f);
    *(float *)(particle + 12) = *(float *)(particle + 12) + growth * 210000.0f;
    FastVecAdd(position, position, motion);
    FastVecScale(motion, motion, 0.99f);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(motion, motion);
    *(int *)(particle + 4) = color_word | (alpha_byte << 24);
    if (FastDecTimer(particle + 10) != 0) {
        part_kill(particle);
    }
}

/* func_002C9218 is defined in 002C9218.c. */

/* func_002C94C8 is defined in 002C94C8.c. */

/* Finds a point along a looping path at position t. It can also give the direction the path is facing there. */
void path_sample_position(char *path, int clamp, float *out, float *angles, int flags, float t)
{
    float point0[4] __attribute__((aligned(16)));
    float point1[4] __attribute__((aligned(16)));
    float point2[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float dir01[4] __attribute__((aligned(16)));
    float dir12[4] __attribute__((aligned(16)));
    int segment = FloatToInt(t);
    int at_end = 0;
    int index0;
    int index1;
    int index2;
    int count;

    if (clamp == 0) {
        if (segment >= *(int *)path - 2) {
            segment = *(int *)path - 2;
            at_end = 1;
        }
    }
    t -= segment;
    if (at_end) {
        if (t > 1.0f)
            t = 1.0f;
    }
    count = *(int *)path;
    index0 = segment;
    index1 = segment + 1;
    index2 = segment + 2;
    if (index2 >= count) {
        index0 = index0 % count;
        index1 = index1 % count;
        index2 = index2 % count;
    }
    qcopy(point0, path + 0x10 + index0 * 16);
    qcopy(point1, path + 0x10 + index1 * 16);
    lerp_vector(out, point0, point1, t);
    if (flags & 1)
        return;
    if (at_end) {
        FastVecSub(direction, point1, point0);
    } else {
        qcopy(point2, path + 0x10 + index2 * 16);
        FastVecSub(dir01, point1, point0);
        FastVecSub(dir12, point2, point1);
        lerp_vector(direction, dir01, dir12, t);
    }
    angles[1] = -mat_fast_helper_a(vec_length_xy(direction), direction[2]);
    angles[2] = mat_fast_helper_a(direction[0], direction[1]);
    angles[3] = point0[3] * (1.0f - t) + point1[3] * t;
}

/* Returns a saved value that other menu code reads. */
int menu_get_saved_value(void) {
    return D_001F2A30;
}

/* A15-struct-pad-20 freshly exact-verified under family reservation */
/* Clears two fields in a fixed data block. */
void menu_clear_block_fields(void) {
    BatchA_A15_u8 *p = D_L15_001FF640;
    *(BatchA_A15_u32 *)(p + 0xF0) = 0;
    *(BatchA_A15_u32 *)(p + 0x1F0) = 0;
}

/* A10-twin-base-32 freshly exact-verified under family reservation */
/* Sets two fields in a fixed data block. */
void menu_init_block_fields(void) {
    BatchA_A10_u8 *p = D_L03_001FF8C0;
    *(BatchA_A10_u32 *)(p + 0xF0) = (BatchA_A10_u32)D_L03_001FFAC0;
    *(BatchA_A10_u32 *)(p + 0x1F0) = 1;
}

/* Steps a ring-shaped list back to the previous filled entry. */
void menu_ring_list_step_backward(s32 *ring) {
 s32 *entries=ring+3; s32 index;
 do {
  index=--ring[1];
  if(index<=0) index=ring[0];
  ring[1]=index;
 } while(*(s32 *)((u32)entries+(index<<2))==0);
}

/* Steps a ring-shaped list forward to the next filled entry. */
void menu_ring_list_step_forward(s32 *ring) {
 s32 last_index=ring[0]; s32 *entries=ring+3; s32 index;
 do {
  index=ring[1]+1;
  if(last_index<index) index=0;
  ring[1]=index;
 } while(*(s32 *)((u32)entries+(index<<2))==0);
}

/* Tells the sound or menu system to turn off, then returns 0. */
int menu_disable_subsystem(void) {
    if (D_001A8CFC[0] != 0)
        popup_set_box_value(D_001A8CFC[0] + 0x3CAA8, 0);
    return 0;
}

/* Tells the sound or menu system to turn on, then returns 0. */
int menu_enable_subsystem(void) {
    if (D_001A8CFC[0] != 0)
        popup_set_box_value(D_001A8CFC[0] + 0x3CAA8, 1);
    return 0;
}

/* reads two object fields, forms centre plus and minus half of a third, and issues two five-argument draw calls taking an id-derived value and a fixed 64-bit attribute */
/* Draws two small icons on either side of a menu item. Returns 0. */
int menu_draw_item_side_icons (int *item)
{
  int center = item[6];
  int half_width = item[8] >> 1;
  int left_x = center - half_width;
  int right_x = center + half_width;
  int icon;

  icon = func_00288FB8_1 (4412);
  text_draw_medium (left_x, item[7], (long) 0x80f0f0f0, icon, -1);
  icon = func_00288FB8_1 (4408);
  text_draw_right_aligned_medium (right_x, item[7], (long) 0x80f0f0f0, icon, -1);
  return 0;
}

/* Resets the 20 saved menu slots to -1. */
void menu_reset_slots(void)
{
    char *menu_state = g_pause_menu_state;
    int empty_value = -1;
    int *slot = (int *)(menu_state + 0x1BC);
    int i;

    for (i = 0x13; i >= 0; i--)
        *slot-- = empty_value;
}

/* Sets up the pause menu state when the menu opens, including its screen links and starting values. */
void menu_init_pause_state(int mode)
{
    snd_send_cmd22(0x5D);
    music_Pause(0);
    ((State_2C9CF8 *)g_pause_menu_state)->byteDB = 0;
    snd_Pump();
    ((State_2C9CF8 *)g_pause_menu_state)->f0 = 1;
    if (!g_current_game_mode) ConfigureMenuChoiceList();
    ((State_2C9CF8 *)g_pause_menu_state)->f144 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f148 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->fE8 = (D_001A7A08 & 0xFFFF0000) || ((State_2C9CF8 *)g_pause_menu_state)->f108 ? 1 : 0;
    ((Links_2C9CF8 *)D_00259918)->next = ((State_2C9CF8 *)g_pause_menu_state)->fE8 ? D_00259AF8 : D_00259AA8;
    ((Links_2C9CF8 *)D_00259AA8)->previous = ((State_2C9CF8 *)g_pause_menu_state)->fE8 ? D_00259AF8 : D_00259918;
    ((State_2C9CF8 *)g_pause_menu_state)->f8 = ((State_2C9CF8 *)g_pause_menu_state)->f104 ? (int)((State_2C9CF8 *)g_pause_menu_state)->f104 : mode;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f20 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f120 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C0 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C4 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f1C8 = 0;
    if (mode != 6) {
        map_set_current_and_refresh(g_current_map_index);
        menu_update_entry_states();
        D_0025B5F8 = 0;
        menu_update_unlock_entries();
    }
    ((State_2C9CF8 *)g_pause_menu_state)->f150 = 0;
    ((State_2C9CF8 *)g_pause_menu_state)->f14C = 1;
}

/* Puts the saved screen picture back into video memory in strips. */
void menu_restore_saved_screen_image(int from_end)
{
    GsLoadImage2C9E60 image;
    int remaining;
    int dest_addr;
    char *src_ptr;
    char *state = g_pause_menu_state;

    *(int *)(state + 0xD0) = from_end != 0 ? 2 : 1;
    gfx_wait_for_dma_status_bits(1);
    sceGsSyncV(0);
    D_001B1598++;
    remaining = g_screen_height * 0x600;
    src_ptr = *(char **)(state + 0x20);
    dest_addr = D_001A72D4;
    if (from_end != 0)
        dest_addr = 0x3FB000 - remaining;
    for (; remaining >= 0; remaining -= 0x4000) {
        func_00126288(&image, dest_addr >> 8, 1, 0, 0, 0, 64, 64);
        dest_addr += 0x4000;
        FlushCache(0);
        sceGsExecLoadImage(&image, src_ptr);
        src_ptr += 0x4000;
        gfx_wait_paths_idle(0, 0);
    }
}


/* func_002CA070 is defined in 002CA070-pause.c. */

/* func_002CA5D0 is defined in 002C7748-g8.c. */

/* func_002CA790 is defined in 002CA790.c. */

/* Pause-menu state at D_001F2840 (RAC1 update_menu_system: update_count, timer, ...). */
typedef struct {
    int mode;
    char pad04[0x10];
    int arg;
    char pad18[4];
    int pending;
    char pad20[0x100];
    int update_count;
    char pad124[0x34];
    int timer;
    char pad15C[8];
    int card_error_frames;
    int clear;
} PauseState;
/* Memory-card state: state and error code (RAC1 memory_card_state). */
typedef struct {
    char pad[0x15C];
    int state;
    int pad160;
    int err;
} PauseCardState;
#define PAUSE ((PauseState *)D_001F2840)
extern PauseCardState g_memcard_state;
extern int g_save_menu_flags __attribute__((sda));
extern int D_001B1684 __attribute__((sda));
extern s32 D_001B18A4[] __attribute__((sda));
extern void process_unlock_code_input(void);
extern void menu_enter_pause_mode_two(void);
extern void menu_enter_pause_mode_three(void);
extern void menu_enter_pause_mode_four(void);
extern void menu_update_pause_widgets(void);
extern void menu_handle_pause_fade_timer(void);
extern int UpdateSoundVoices(void);
extern void moby_update_visible_objects(void);
extern void menu_close_and_save_choices(void);

/* Runs one frame of the pause menu and calls the handler for the current menu mode. */
void menu_update_pause(void)
{
    PAUSE->update_count = PAUSE->update_count > 31999 ? 32000 : PAUSE->update_count + 1;
    PAUSE->clear = 0;
    if (PAUSE->timer) --PAUSE->timer;
    if (g_memcard_state.state < 3 && g_memcard_state.err < 0) ++PAUSE->card_error_frames;
    else PAUSE->card_error_frames = 0;
    process_unlock_code_input();
    if ((g_save_menu_flags & 1) && PAUSE->mode == 4 && D_001B1684 >= 8) {
        if (!request_begin_slot(4, 1, 1, PAUSE->arg, 0)) return;
    }
    switch (PAUSE->mode) {
    case 1: menu_enter_pause_mode_two(); break;
    case 2: menu_enter_pause_mode_three(); break;
    case 3: menu_enter_pause_mode_four(); break;
    case 4: menu_update_pause_widgets(); break;
    case 5:
        menu_handle_pause_fade_timer();
        UpdateSoundVoices();
        D_0018A000[0] = 10;
        D_001B18A4[1] = 0;
        return;
    }
    moby_update_visible_objects();
    UpdateSoundVoices();
    if (PAUSE->pending) menu_close_and_save_choices();
}
#undef PAUSE

/* Switches the pause menu to its second mode after a setup call. */
void menu_enter_pause_mode_two(void)
{
    menu_enter_pause_state();
    D_L00_001FEC40[0] = 2;
    D_L00_001FEC40[1] = 0;
}

/* A12-struct-2field-24 freshly exact-verified under family reservation */
/* Switches the menu to mode 3. */
void menu_enter_pause_mode_three(void) {
    BatchA_A12_BatchA24 *p = &D_L08_001FF980;
    p->a = 3;
    p->b = 0;
}

/* Switches the pause menu to mode 4 and remembers the previous choice. */
void menu_enter_pause_mode_four(void)
{
    int *menu;

    gfx_set_clear_color_packet(0, 0, 0, 0x38);
    menu = (int *)g_pause_menu_state;
    if (menu[1] == 0)
        menu[1] = 1;
    menu[0] = 4;
    menu[5] = menu[6];
    menu[6] = 0;
    menu[1] = 0;
}

/* Counts down a menu timer and, when it ends, starts the screen change for the current menu mode. */
void menu_handle_pause_fade_timer(void)
{
    int frames_left = ((GameState_1F2840 *)g_pause_menu_state)->count;

    if (frames_left != 0)
        ((GameState_1F2840 *)g_pause_menu_state)->count = frames_left - 1;
    if (((GameState_1F2840 *)g_pause_menu_state)->count != 0)
        return;
    if (D_001A63AC != 0)
        return;
    if (((GameState_1F2840 *)g_pause_menu_state)->mode == 2) {
        request_end_slot(0, D_001C51D0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 3) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 4) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 6) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 5) {
        request_begin_slot(2, 1, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0, 0);
    } else {
        request_end_slot(0, 0);
    }
    if (((GameState_1F2840 *)g_pause_menu_state)->field40 != 0 &&
        ((GameState_1F2840 *)g_pause_menu_state)->field30 != ((GameState_1F2840 *)g_pause_menu_state)->field40) {
        int entry_id;
        int *rec;
        snd_pump_music_and_disc_read(1);
        entry_id = ((GameState_1F2840 *)g_pause_menu_state)->field40;
        rec = (int *)((char *)g_weapon_table + g_item_slot_to_record[entry_id] * 0xE0);
        LoadClassIntoFreeCacheSlot(rec[5]);
        snd_pump_music_and_disc_read(1);
    }
    snd_pump_music_and_disc_read(1);
}

/* func_002CB820 reads $gp slots: it is defined in 002C7748-g8.c. */


/* Says whether a menu item number is in the allowed range. Returns 1 if so, else 0. */
s32 menu_is_index_allowed(s32 index) {
 s32 result=0;
 if(index<0x15 || index==0x18) result=1;
 return result;
}

/* func_002CB510 is defined in 002CB510.c. */

/* func_002CB648 is defined in 002CB648-g8.c. */

/* Handles one menu step: step 0 accepts, step 1 asks another menu function. */
int menu_handle_step_simple(int mode)
{
    int result = 0;
    switch (mode) {
    case 0: result = 1; break;
    case 1: result = menu_send_request(3, D_0025BA90); break;
    }
    return result;
}

/* Handles one menu step with three cases: accept, ask another function, or run a reset. */
int menu_handle_step_with_reset(int mode)
{
    int result = 0;
    switch (mode) {
    case 0: D_0018A000[0] = 10; result = 1; break;
    case 1: result = menu_send_request(3, D_0025BA90); break;
    case 2: level_set_dependent_value(); result = 1; break;
    }
    return result;
}

/* func_002CBAE0 is defined in 002C7748-g8.c. */

/* func_002CBC58 is in 002C7748-panels-g8.c. */

/* Checks whether a button press belongs to this menu item and says if it was accepted. */
int menu_check_item_input(int item_id)
{
    if (*(int *)(((CallbackState_2CC490 *)g_pause_menu_state)->source + 0xE8) != item_id)
        return 0;
    if ((((GameState_2CC490 *)g_pad_state)->flags & 0x900) != 0 &&
        ((CallbackState_2CC490 *)g_pause_menu_state)->fallback == 0)
        return 1;
    if ((((GameState_2CC490 *)g_pad_state)->flags & 0x10) != 0) {
        int value = *(int *)(((CallbackState_2CC490 *)g_pause_menu_state)->source + 0xE0);
        int result;
        if (value != 0)
            ((CallbackState_2CC490 *)g_pause_menu_state)->value = value;
        else if (((CallbackState_2CC490 *)g_pause_menu_state)->fallback == 0) {
            result = -1;
            goto done;
        }
        result = 0;
done:
        return result;
    }
    return 0;
}

/* func_002CC528 lives in 002CC528-g8.c. */

/* Near miss: nonmatching/game/func_002CC550.c (316/316 bytes; the two address
   materialisations in the loop preheader keep a separate %hi temporary). */

/* Does nothing and returns 0. */
int menu_return_zero_a(void) {
    return 0;
}

/* Does nothing and returns 0. */
int menu_return_zero_b(void) {
    return 0;
}

/* Sets a field in an object to -1 and returns 0. */
s32 menu_clear_object_handle(u8 *obj) { *(s32 *)(obj + 0x44) = -1; return 0; }

/* func_002CC6B0 is defined in 002CC6B0-hud-g8.c. */

/* Handles a button press on a menu entry, switching the selected entry and its enabled flag. */
int menu_handle_entry_input(char *obj)
{
    int old_selection;
    int kind;
    MenuEntry_2CCF68 *entry;

    if (*(char **)(*(char **)(g_pause_menu_state + 0x14) + 0xE8) != obj) goto fallback;
    if ((((InputState_2CCF68 *)g_pad_state)->flags & ~0x40) != 0 && obj == D_00259148) return 0;
    old_selection = D_001B1680;
    if (D_001A8B84) goto fallback;
    entry = (MenuEntry_2CCF68 *)(*(int *)(obj + 0x40) * 12 + *(int *)(obj + 0x34));
    kind = entry->kind;
    if (kind != 3) goto fallback;
    if (obj == D_00259148) {
        D_001A8B84 = 1;
        D_001B1680 = 1;
        return 0;
    }
    if (((InputState_2CCF68 *)g_pad_state)->flags & 0x40) {
        if (obj == D_00259198) {
            D_001A8B84 = D_001A7BC9.value != 0;
            D_001B1680 = 1;
        } else if (obj == D_002591E8) {
            D_001A8B84 = D_001A7BCA.value != 0;
            D_001B1680 = 2;
        } else if (obj == D_00259238) {
            D_001A8B84 = D_001A7BCB.value != 0;
            D_001B1680 = 3;
        } else if (obj == D_00259288) {
            D_001A8B84 = D_001A7BCC.value != 0;
            D_001B1680 = 4;
        } else if (obj == D_002592D8) {
            D_001A8B84 = D_001A7BCE.value != 0;
            D_001B1680 = 6;
        }
        if (!D_001A8B84)
            D_001B1680 = old_selection;
        return 0;
    }
fallback:
    return UpdateMenuListActions(obj);
}

/* Handles menu button input and picks the right handler for the current screen. Plays a sound if input was used. */
int menu_handle_button_input(void)
{
    unsigned int flags = D_00138344;
    int handled = 0;

    if (flags & 0x910) {
        handled = 1;
    } else if (flags & 0x40) {
        handled = func_0029C168(flags);
        if (stub_empty_23() && stub_empty_24()) {
            handled = menu_handle_command(handled);
        } else if (stub_empty_26()) {
            handled = menu_handle_mode_action(handled);
        } else if (stub_empty_25()) {
            handled = menu_handle_step_with_reset(handled);
        } else if (stub_empty_28() == 0x31) {
            handled = menu_handle_step_simple(handled);
        } else if (stub_empty_27()) {
            handled = menu_handle_step_simple(handled);
        } else if (stub_empty_28() == 0x1C) {
            handled = menu_handle_step_simple(handled);
        } else {
            handled = menu_run_action_by_index(handled);
        }
    } else {
        func_0029C168(flags);
    }

    if (handled) {
        snd_play_from_global_bank(0x12, 0, 0);
    }
    return handled;
}

/* Runs three setup calls and returns 0. */
int menu_run_setup_calls(void)
{
  SetupGifPaging(0);
  func_0029C138();
  DoGifPaging();
  return 0;
}

/* func_002CD3C0 is defined in 002CD3C0.c. */

/* Handles menu input and keeps the menu flags in step with the current selection. */
int menu_update_input_flags(void)
{
    int scratch[4];
    int first = menu_get_setting_value();
    int result = 0;
    int flags = D_00138344;

    if (flags & 0x10) {
        int value = *(int *)(((CallbackState_2CC490 *)g_pause_menu_state)->source + 0xE0);
        if (value != 0)
            ((CallbackState_2CC490 *)g_pause_menu_state)->value = value;
        else if (((CallbackState_2CC490 *)g_pause_menu_state)->fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }

    if (flags & 0x900) {
        result = 1;
    } else {
        func_0029C248(flags, scratch);
    }

    if (D_001A8CFC[0] != 0) {
        int second = menu_get_setting_value();
        if (first == second && D_001A63AC == 0 &&
            ((D_00259C78.handle == second && D_00259C78.state == 2) ||
             (D_00259C78.last == second && D_00259C78.state == 4))) {
            D_00259C44->flags &= -5;
        } else {
            D_00259C44->flags |= 4;
        }
        D_00259C78.current = second;
    }
    return result;
}
