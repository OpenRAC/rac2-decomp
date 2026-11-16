#include "include_asm.h"

#include "common.h"
extern s32 g_moby_array __attribute__((sda));
extern f32 g_emitter_spawn_fraction __attribute__((sda));
extern s32 g_active_emitter_count __attribute__((sda));
extern char g_str_effect_name[] MACRO_ADDR;
extern char *part_find_owned_effect_slot(s32 a, s32 b, s32 c);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void func_PAL_002B15D8(char *a0, f32 f12, f32 f13, s32 a1, char *a2,
                        f32 f14, f32 f15, s32 a3);
extern void part_spawn_scaled_bolts_pal(char *a0, s32 a1, f32 f12);
extern int PlayMobySound(s32 a0, s32 a1, char *a2);
extern s32 flag_set_first_pending(char *a0);
extern s32 math_fast_float_d(char *a0);
extern void moby_mark_spawned(char *a0);

void emitter_update_pal(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    u8 state = *(u8 *)(a0 + 0x20);
    char *p;
    s32 n;
    u8 st;

    switch (state) {
    case 0:
        moby_set_state(a0, 1, -1);
        return;
    case 1:
        p = part_find_owned_effect_slot((s32)a0, 0x04010000, 0);
        if (p != 0 && *(s32 *)s1 == 0) {
            moby_set_state(a0, 2, -1);
            return;
        }
        *(u8 *)(a0 + 0xA8) = 0xFF;
        n = *(s32 *)(s1 + 4);
        if (n > 0) {
            char *e = (char *)(g_moby_array + (n << 8));

            if (e == 0) {
                return;
            }
            st = *(u8 *)(e + 0x20);
            if (st == 0xFE || (st == 0xFD || st == 3)) {
                moby_set_state(a0, 2, -1);
            }
        }
        return;
    case 2:
        if (*(u8 *)(a0 + 0x31) != 0 && g_emitter_spawn_fraction < 0.9f &&
            g_active_emitter_count < 10) {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 15, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 9, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(a0, 1, 0.0f);
        PlayMobySound(0, 0, a0);
        moby_set_state(a0, 3, -1);
        return;
    case 3:
        if (flag_set_first_pending(a0) != 0) {
            s32 c;
            *(u8 *)(a0 + 0x31) = 0;
            c = g_active_emitter_count;
            *(u16 *)(a0 + 0x34) |= 1;
            *(s32 *)(a0 + 0x98) = 0;
            g_active_emitter_count = c + 1;
            *(s32 *)(s1 + 8) = 0x64;
        }
        if (math_fast_float_d(s1 + 8) != 0) {
            g_active_emitter_count = g_active_emitter_count - 1;
            moby_mark_spawned(a0);
        }
        return;
    }
}


extern void vec_local_offset_to_world(char *,void *,float,float,float);
extern void SpawnExplosionEffects_pal(char *,float,float,float,float,float,float,float,char *,void *,int,int,int,int,int,int,int,int,int);

void emitter_burst_update_pal(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    u8 state = *(u8 *)(a0 + 0x20);
    char *p;
    s32 n;
    u8 st;

    switch (state) {
    case 0:
        g_active_emitter_count = 0;
        moby_set_state(a0, 1, -1);
        return;
    case 1:
        p = part_find_owned_effect_slot((s32)a0, 0x04010000, 0);
        if (p != 0 && *(s32 *)s1 == 0) {
            moby_set_state(a0, 2, -1);
            return;
        }
        *(u8 *)(a0 + 0xA8) = 0xFF;
        n = *(s32 *)(s1 + 4);
        if (n > 0) {
            char *e = (char *)(g_moby_array + (n << 8));

            if (e == 0) {
                return;
            }
            st = *(u8 *)(e + 0x20);
            if (st == 0xFE || (st == 0xFD || st == 3)) {
                moby_set_state(a0, 2, -1);
            }
        }
        return;
    case 2:
        { float v[4];
        vec_local_offset_to_world(a0,v,0.0f,0.0f,3.0f);
        if (*(u8 *)(a0 + 0x31) != 0 && g_emitter_spawn_fraction < 0.9f &&
            g_active_emitter_count < 10) {
            SpawnExplosionEffects_pal(a0,0.0f,0.0f,1.0f,0.5f,9.0f,*(float *)(a0+0x2C)*1.3f,15.0f,
                         g_str_effect_name,v,10,3,16,-1,0,1,-1,0,0);
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 15, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 1, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(a0, 1, 0.0f);
        PlayMobySound(0, 0, a0);
        moby_set_state(a0, 3, -1);
        return; }
    case 3:
        if (flag_set_first_pending(a0) != 0) {
            s32 c;
            *(u8 *)(a0 + 0x31) = 0;
            c = g_active_emitter_count;
            *(u16 *)(a0 + 0x34) |= 1;
            *(s32 *)(a0 + 0x98) = 0;
            g_active_emitter_count = c + 1;
            *(s32 *)(s1 + 8) = 0x64;
        }
        if (math_fast_float_d(s1 + 8) != 0) {
            g_active_emitter_count = g_active_emitter_count - 1;
            moby_mark_spawned(a0);
        }
        return;
    }
}



void emitter_alt_update_pal(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    u8 state = *(u8 *)(a0 + 0x20);
    char *p;
    s32 n;
    u8 st;

    switch (state) {
    case 0:
        moby_set_state(a0, 1, -1);
        return;
    case 1:
        p = part_find_owned_effect_slot((s32)a0, 0x04010000, 0);
        if (p != 0 && *(s32 *)s1 == 0) {
            moby_set_state(a0, 2, -1);
            return;
        }
        *(u8 *)(a0 + 0xA8) = 0xFF;
        n = *(s32 *)(s1 + 4);
        if (n > 0) {
            char *e = (char *)(g_moby_array + (n << 8));

            if (e == 0) {
                return;
            }
            st = *(u8 *)(e + 0x20);
            if (st == 0xFE || (st == 0xFD || st == 3)) {
                moby_set_state(a0, 2, -1);
            }
        }
        return;
    case 2:
        if (*(u8 *)(a0 + 0x31) != 0 && g_emitter_spawn_fraction < 0.9f &&
            g_active_emitter_count < 10) {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 15, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 1, g_str_effect_name, 3.0f, 6.0f, 0xFF);
        }
        part_spawn_scaled_bolts_pal(a0, 1, 0.0f);
        PlayMobySound(0, 0, a0);
        moby_set_state(a0, 3, -1);
        return;
    case 3:
        if (flag_set_first_pending(a0) != 0) {
            s32 c;
            *(u8 *)(a0 + 0x31) = 0;
            c = g_active_emitter_count;
            *(u16 *)(a0 + 0x34) |= 1;
            *(s32 *)(a0 + 0x98) = 0;
            g_active_emitter_count = c + 1;
            *(s32 *)(s1 + 8) = 0x64;
        }
        if (math_fast_float_d(s1 + 8) != 0) {
            g_active_emitter_count = g_active_emitter_count - 1;
            moby_mark_spawned(a0);
        }
        return;
    }
}


