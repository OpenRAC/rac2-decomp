#include "include_asm.h"
#include "names.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef int TI128 __attribute__((mode(TI)));

extern s32 func_003062A0(u8 *a0);
extern s32 func_0030CBA8(s32 a0);
extern void thrown_object_update(s32 a0, s32 a1);
extern void func_002FF9F8(s32 a0);
extern void func_0037B210(void);
extern void func_003404B8(void);
extern void func_00379F18(s32 a0);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern void func_0037B280(u8 *a0, s32 a1);
extern void func_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_0037D608(u8 *a0, u8 *a1, f32 f12);
extern s32 func_00379860(u8 *a0);
extern void func_00379E60(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_0037B538(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_0037B3A0(u8 *a0);
extern s32 func_00332AF8(s32 a0, s32 a1);
extern u32 *func_00379CA0(u8 *a0);
extern void func_0037AEC0(u8 *a0, s32 a1);
extern void func_00379C68(u8 *a0, s32 a1);
extern u8 *func_0037B440(s32 a0);
extern void func_0037D210(u8 *a0);
extern void func_00306748(u8 *a0, u8 *a1, u8 *a2);
extern void func_003068F8(u8 *a0, u8 *a1, f32 f12);
extern void func_00329960(u8 *a0, u8 *a1, u8 *a2);
extern void func_003298C0(u8 *a0, u8 *a1, u8 *a2);
extern void UpdateFeltzinMissionReward(u8 *a0, s32 a1);
extern void feltzin_mission_handle_failure(u8 *a0, s32 a1);
extern void feltzin_challenge_reset(u8 *a0);
extern void feltzin_target_spawner_init(u8 *a0);
extern void feltzin_target_spawn_random(u8 *a0);

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
extern u32 g_spawn_list_table[];
extern u8 *g_feltzin_target_mobys[] __attribute__((sda));
extern s32 g_sdata_word_unused_a __attribute__((sda));

/* func_L05_00420360 lives in L05_00420360-g8.c. */

/* func_L05_00420788 lives in L05_00420788-g8.c. */

/* func_L05_004209D8 lives in the -g8 sibling: its reset flag is reached through $gp. */

/* func_L05_00420A88 lives in L05_00420A88-g8.c. */



/* func_L05_00420FB0 lives in L05_00420FB0-g8.c. */

/* func_L05_00421100 lives in L05_00421100-g8.c. */

/* func_L05_00421B98 lives in L05_00421B98-g8.c. */


/* State 0 waits for func_00379860, then enters state 1. State 1 calls func_0037B538 and, when the
   +0x26C timer of its state expires, picks an entry of the object's id list and passes that object
   (this one when the list has fewer than two entries) to func_L05_00422540. */
void feltzin_target_spawner_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *target;
    s32 i;
    s32 n;

    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        if (func_00379860(moby) == 0)
            return;
        feltzin_target_spawner_init(moby);
        if (*(s32 *)(vars + 0x264) == 0)
            return;
        func_00379E60(moby, 0, 0, 0);
        return;
    }

    func_0037B538(moby, 0, 1, 1);
    if (*(s32 *)(vars + 0x264) == 0)
        return;
    if (func_003062A0(vars + 0x26C) == 0)
        return;
    target = 0;
    n = func_0037B3A0(moby);

    if (n >= 2) {
        s32 count = func_00332AF8(0, n - 1);
        u16 *idPtr = (u16 *)g_spawn_list_table[moby[0x21]];
        u16 idWord;
        i = 0;
        do {
            idWord = *idPtr;
            n = idWord & 0x7FFF;
            if (i == count)
                goto found;
            i++;
            idPtr++;
        } while ((s16)idWord >= 0);
        goto done;
found:
        target = g_feltzin_target_mobys[0] + (n << 8);
    } else {
        target = moby;
    }
done:
    if (target != 0)
        feltzin_target_spawn_random(target);
    *(s32 *)(vars + 0x26C) = 0x78;
}

/* Puts the spawner object into its active state and clears its timers. */
void feltzin_target_spawner_init(u8 *moby) {
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

/* func_L05_00422540 lives in L05_00422540-qcopy.c. */

/* shared native body of family 5a97ab89858c */
/* Fills a block with default values: corner coordinates of -1 and 1, zeroed fields. */
void corner_block_init_default(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
