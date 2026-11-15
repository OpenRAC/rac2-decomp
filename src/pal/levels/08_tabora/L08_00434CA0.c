#include "include_asm.h"

#include "common.h"
extern s32 D_L08_001B29DC __attribute__((sda));
extern f32 D_L08_001B250C __attribute__((sda));
extern s32 g_active_emitter_count __attribute__((sda));
extern char D_L08_001A8F20[] MACRO_ADDR;
extern char *part_find_owned_effect_slot(s32 a, s32 b, s32 c);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void func_PAL_002B15D8(char *a0, f32 f12, f32 f13, s32 a1, char *a2,
                        f32 f14, f32 f15, s32 a3);
extern void func_PAL_L00_003281C0(char *a0, s32 a1, f32 f12);
extern int PlayMobySound(s32 a0, s32 a1, char *a2);
extern s32 flag_set_first_pending(char *a0);
extern s32 math_fast_float_d(char *a0);
extern void moby_mark_spawned(char *a0);

void func_PAL_L08_00434CA0(char *a0) {
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
            char *e = (char *)(D_L08_001B29DC + (n << 8));

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
        if (*(u8 *)(a0 + 0x31) != 0 && D_L08_001B250C < 0.9f &&
            g_active_emitter_count < 10) {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 15, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 9, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        }
        func_PAL_L00_003281C0(a0, 1, 0.0f);
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
extern void func_PAL_002AC718(char *,float,float,float,float,float,float,float,char *,void *,int,int,int,int,int,int,int,int,int);

void func_PAL_L08_00434EC0(char *a0) {
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
            char *e = (char *)(D_L08_001B29DC + (n << 8));

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
        if (*(u8 *)(a0 + 0x31) != 0 && D_L08_001B250C < 0.9f &&
            g_active_emitter_count < 10) {
            func_PAL_002AC718(a0,0.0f,0.0f,1.0f,0.5f,9.0f,*(float *)(a0+0x2C)*1.3f,15.0f,
                         D_L08_001A8F20,v,10,3,16,-1,0,1,-1,0,0);
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 15, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 1, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        }
        func_PAL_L00_003281C0(a0, 1, 0.0f);
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



void func_PAL_L08_00435320(char *a0) {
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
            char *e = (char *)(D_L08_001B29DC + (n << 8));

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
        if (*(u8 *)(a0 + 0x31) != 0 && D_L08_001B250C < 0.9f &&
            g_active_emitter_count < 10) {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 15, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(a0, 3.0f, 6.0f, 1, D_L08_001A8F20, 3.0f, 6.0f, 0xFF);
        }
        func_PAL_L00_003281C0(a0, 1, 0.0f);
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


