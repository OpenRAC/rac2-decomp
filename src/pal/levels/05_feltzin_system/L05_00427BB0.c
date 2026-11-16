#include "include_asm.h"
#include "names.h"


typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;
extern s32 func_003062A0(u8 *a0);
extern s32 func_0030CBA8(s32 a0);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern s32 func_00379860(u8 *a0);
extern s32 func_0037B3A0(u8 *a0);
extern s32 func_00332AF8(s32 a0, s32 a1);
extern u32 *func_00379CA0(u8 *a0);
extern void func_0037AEC0(u8 *a0, s32 a1);
extern void func_00379C68(u8 *a0, s32 a1);
extern u8 *func_0037B440(s32 a0);
extern void feltzin_target_spawner_init(u8 *a0);
extern s32 g_sdata_word_unused_b __attribute__((sda));
extern s32 g_sdata_word_unused_c __attribute__((sda));
extern u8 g_feltzin_challenge_state[];
extern u8 g_feltzin_timer[];
extern s32 g_feltzin_mission_index;
extern u8 *g_spot_record_table;
extern u8 g_feltzin_challenge_param_a[];
extern u8 g_feltzin_challenge_param_b[];
extern u8 g_feltzin_challenge_param_c[];
extern u8 g_level_data_block[];
extern u8 *g_level_byte_ptr_table[];
extern u8 *g_moby_pool_base;
extern s32 g_sdata_word_unused_a __attribute__((sda));

/* Sets up a target spawner: marks it active and resets its timers. */
void feltzin_target_spawner_init_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    *(u16 *)(moby + 0x34) |= 0x100;
    moby[0x20] = 1;
    *(s32 *)((u8 *)func_00379CA0(moby) + 0x148) = 0xA;
    func_0037AEC0(moby, 1);
    *(s32 *)(vars + 0x26C) = 0;
    *(s32 *)(vars + 0x268) = 0;
    *(f32 *)(vars + 0x230) = 10.0f;
    func_00379C68(moby, 0xFFFF);
}

