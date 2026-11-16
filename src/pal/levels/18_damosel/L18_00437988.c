#include "include_asm.h"
#include "names.h"



typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u8 g_beam_target_vec[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 g_max_l18_group_index[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern s32 IsPointInCuboid(u8 *, s32);
extern s32 CollLine(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 g_max_l18_group_index[] __attribute__((sda));
extern u8 g_data_block_base[];
extern void snd_stop_voice(s32 arg0);
extern int PlayMobySound(s32 arg0, s32 arg1, u8 *arg2);
extern void moby_mark_spawned(void *arg0);
extern char *SpawnExplosion(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                           s32 arg6, s32 arg7, float arg8, float arg9, s32 arg10, s32 arg11,
                           s32 arg12, s32 arg13);

/* Destroys a piece and its three linked parts, stops its sound, and makes an explosion. */
void extermibot_destroy_piece_and_parts_pal(u8 *moby) {
    u8 *vars;
    s32 voice_slot;
    vars = *(u8 **)(moby + 0x68);
    voice_slot = *(s32 *)(vars + 0x7F0);
    if (voice_slot != -1) {
        u8 *record = g_data_block_base - 0x79A0 + voice_slot * 0x70;
        if (*(u32 *)(record + 0x88) != (u32)moby) goto end;
        if (record[0x74] == 0) goto end;
        snd_stop_voice(voice_slot);
    }
end:
    *(s32 *)(vars + 0x7F0) = -1;
    SpawnExplosion(moby + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
    PlayMobySound(6, 0, moby);
    if (*(u32 *)(vars + 0x7C0)) {
        moby_mark_spawned(*(void **)(vars + 0x7C0));
        *(u32 *)(vars + 0x7C0) = 0;
    }
    if (*(u32 *)(vars + 0x7C4)) {
        moby_mark_spawned(*(void **)(vars + 0x7C4));
        *(u32 *)(vars + 0x7C4) = 0;
    }
    if (*(u32 *)(vars + 0x7C8)) {
        moby_mark_spawned(*(void **)(vars + 0x7C8));
        *(u32 *)(vars + 0x7C8) = 0;
    }
    moby_mark_spawned(moby);
}

