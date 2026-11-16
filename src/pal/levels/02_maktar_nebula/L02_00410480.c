#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
extern void moby_set_state();
extern void set_moby_color(void *, void *, void *, void *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern void anim_start_blended_pal(void *, int, int, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern u8 g_unlock_flag_c __attribute__((sda));
extern u8 g_message_sequence_flags[];
extern u8 g_message_queue[];
extern u8 g_moby_group_flags[];
extern u16 g_beam_emitter_id;
extern u8 g_moby_nibble_table[];

/* brings the actor into its armed state */
void flamethrower_robot_wake_pal(u8 *moby, int wait_threshold) {
    u8 *vars = *(u8 **)(moby + 0x68);
    int one = 1;
    u32 flags;

    *(float *)(vars + 0x20) = (float)*(s16 *)(vars + 0x24);
    *(u16 *)(vars + 0x2E2) = one;
    moby_set_controller_speed_limits(moby, 0.0064000003f, 0.16000001f,
                  0.0016755164f, 0.12566373f);
    moby_set_state(moby, 3, 1);
    if (*(u8 *)(moby + 0x43) != 2)
        anim_start_blended_pal(moby, 2, 0, 0);
    *(u32 *)(moby + 0x98) = *(u32 *)(*(u32 *)(moby + 0x24) + 0x10);
    *(u8 *)(vars + 0x6A) = 0;
    *(u8 *)(vars + 0x2E) = one;
    *(u8 *)(moby + 0x31) = one;
    flags = *(u16 *)(moby + 0x34);
    *(u8 *)(moby + 0x7F) = 0;
    *(u16 *)(moby + 0x34) = (flags | 0x1000) & 0xFFB8;
    *(u16 *)(vars + 0x2E8) = wait_threshold;
    *(u16 *)(vars + 0x88) = 0;
    if (*(s16 *)(vars + 0x50) != 0) {
        *(u16 *)(vars + 0x50) = 0;
        set_moby_color(moby, *(u8 *)(vars + 0x54), *(u8 *)(vars + 0x55), *(u8 *)(vars + 0x56));
        *(u16 *)(vars + 0x52) = one;
    }
}


extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float,
                          int, int, int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_masked_debris_pal(void *, int, void *, float, float, float, float, int);
extern void func_PAL_002A0F68(void *);
extern void flamethrower_robot_knock_out(u8 *);

/* arms the actor: its two effect tracks, then the shared state resets */
void flamethrower_robot_knock_out_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float direction[3];

    *(u16 *)(vars + 0x2E2) = 0;
    *(u32 *)(vars + 0x2D4) = 0;
    if (moby[0x31]) {
        SpawnExplosion_pal(moby + 0x10, 0, 5, 5, 0x19, 0x14, 0xA, 1, 0.5f, 0.0f,
                      1, 0, 0, 0);
        snd_play_from_class_bank(0, 0, moby, 0xC3E);
        vec_random_direction(direction, 0.10000001f, 0.14000002f);
        FastVecAdd(direction, direction, vars + 0xD0);
        part_spawn_masked_debris_pal(moby, 0xFF, direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    anim_start_blended_pal(moby, 0, 0, 3);
    func_PAL_002A0F68(moby);
    moby_set_state(moby, 1, 0);
    *(u8 *)(moby + 0x31) = 0;
    *(u32 *)(moby + 0x98) = 0;
    *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xEFFF) | 0x47;
}

