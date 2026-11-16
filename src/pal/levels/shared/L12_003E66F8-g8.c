#include "include_asm.h"

#include "common.h"
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define W(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
extern char g_hero_prev_position[];
extern int FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_update_ground_check(void *);
extern int func_PAL_002B1A50(void *, void *, int);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern int FastDecTimer(void *);
extern float vec_distance_xy(void *, void *);
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern void func_PAL_002B14F8(void *, void *, int, int, float);
extern void STUB_printf(const char *, ...);
extern int flag_set_first_pending(void *);
extern int flag_set_second_pending(void *);
extern int flag_is_third_pending_set(void *);
extern int CollLine(void *, void *, int, int, int);
extern char *g_path_zone_table[];
extern char g_str_debug_robot_guard_init[];
extern unsigned short g_robot_guard_init_value __attribute__((sda));
extern float g_robot_guard_spawn_height __attribute__((sda));
extern float g_robot_guard_smooth_value __attribute__((sda));
extern int g_frame_l12_counter __attribute__((sda));
extern char *g_hit_l12_result NOT_SDA;
extern char *g_hero_moby NOT_SDA;

void func_PAL_L12_003E7E08(char *obj) {
    char *s = P(obj, 0x68);
    unsigned char oldstate, oldanim;
    int result;
    float angle;
    float pos[4];
    if (!B(obj, 0x20)) {
        H(P(obj, 0x24), 0x46) = 5;
        U(obj, 0x34) |= 0x1000;
        F(s, 0x30) = 2.25f;
        B(s, 0x48) = FloatToInt(20.0f);
        B(s, 0x4A) = FloatToInt(24.0f);
        B(s, 0x70) = 17;
        W(s, 0xA8) = 3;
        B(s, 0x71) = 4;
        B(s, 0x72) = 5;
        B(s, 0x76) = 6;
        F(s, 0x7C) = 0.20000002f;
        F(s, 0x80) = 0.080000006f;
        F(s, 0x88) = 0.010000001f;
        F(s, 0x8C) = F(s, 0x84) = 0.006f;
        F(s, 0x94) = F(s, 0x90) = 0.5f;
        F(s, 0x9C) = 0.4f;
        B(s, 0xCD) = 26;
        B(s, 0xCE) = 8;
        B(s, 0xCF) = B(s, 0xCC) = 11;
        B(s, 0xD2) = 10;
        B(s, 0xD3) = 17;
        B(s, 0xD5) = 1;
        if (W(s, 0x158) == -1) {
            moby_mark_spawned(obj);
            return;
        }
        W(s, 0x1A8) |= 0x15;
        B(s, 0x28) = 3;
        F(s, 0x1A4) = 0.3f;
        F(s, 0x170) = 1.25f;
        F(s, 0x17C) = F(s, 0x178) = F(s, 0x174) = 2.0f;
        F(s, 0x180) = 3.1415929794311523f;
        F(s, 0x1A0) = 0.523598849773407f;
        F(s, 0x19C) = 0.008f;
        B(s, 0xD6) = 1;
        moby_set_state(obj, 5, 0);
        if (B(obj, 0x43))
            func_PAL_002A7E68(obj, 0, 0, 0);
        W(s, 0x154) = W(s, 0x150);
        if (W(s, 0x164) == -1)
            qcopy(obj + 0x10, g_path_zone_table[W(s, 0x158)] + 0x10);
        else
            qcopy(obj + 0x10, g_path_zone_table[W(s, 0x164)] + 0x10);
        if (W(s, 0x164) != -1)
            moby_set_state(obj, 2, 7);
        if (P(s, 0x294))
            W(P(s, 0x294), 0) = -1;
    }
    if (B(obj, 0x31) && fast_vec_dist(obj + 0x10, g_hero_prev_position) < 24.0f) {
        moby_update_ground_check(obj);
        B(obj, 0x6F) = 22;
    }
    if (W(s, 0x2A0) && flag_is_third_pending_set(obj))
        moby_set_state(obj, 24, 4);
    oldstate = B(obj, 0x20);
    oldanim = B(obj, 0x95);
    result = func_PAL_002B1A50(obj, s + 0x60, 0);
    if (result) {
        if (result == 4) {
            STUB_printf(g_str_debug_robot_guard_init);
            W(s, 0x278) = 5;
        } else
            W(s, 0x278) = 1;
        B(obj, 0x20) = oldstate;
        B(obj, 0x95) = oldanim;
        flag_set_first_pending(obj);
        flag_set_second_pending(obj);
        H(s, 0x26) = g_robot_guard_init_value;
        H(s, 0x274) = 125;
    }
    if (FastDecTimer(s + 0x274)) {
        if (W(s, 0x278) != 1)
            W(s, 0x278) = 0;
        else
            H(s, 0x274) = 42;
    }
    H(s, 0x276) = weapon_select_aim_target(obj, W(s, 0x150), 0, 0, 6.0f, 0.0f);
    W(s, 0x270) = W(s, 0x140);
    if (P(s, 0x140) && vec_distance_xy(P(s, 0x140) + 0x10, obj + 0x10) < 16.0f) {
        qcopy(pos, obj + 0x10);
        pos[2] += g_robot_guard_spawn_height;
        if (!CollLine(pos, s + 0x130, 16, 0, 0) || g_hit_l12_result == g_hero_moby) {
            if (H(s, 0x276) != 1)
                H(s, 0x276) = 1;
        }
    }
    if (B(obj, 0x31)) {
        angle = IntToFloat(g_frame_l12_counter % 50);
        angle = angle * 6.2831854820251465f / IntToFloat(50) - 3.1415927410125732f;
        W(obj, 0x78) = PulseColor(0x80808080, 0x80303030, angle);
    }
    func_PAL_002B14F8(obj, s + 0x2B0, 1, 1, g_robot_guard_smooth_value);
}

/* func_PAL_L12_003E66F8, the PAL copy of func_L12_003E2448: the same C, where the word read of
   D_L12_001B0B0C (a `lhu` in USA) takes the 50 Hz scale. */
extern int g_moby_init_state_value __attribute__((sda));

void func_PAL_L12_003E66F8(unsigned char *a0) {
    *(unsigned char *)(a0 + 0x95) = 9;
    *(unsigned short *)(*(unsigned int *)(a0 + 0x68) + 0x29E) = ((s32)(g_moby_init_state_value) * 5 + 2) / 6;
}
