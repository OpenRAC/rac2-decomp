#include "common.h"

#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define U(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define W(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))

extern char D_L12_001B9E00[];
extern int FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object(void *, void *, int);
extern int weapon_select_aim_target(void *, int, int, int, float, float);
extern int FastDecTimer(void *);
extern float vec_distance_xy(void *, void *);
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern void value_set_and_smooth(void *, void *, int, int, float);
extern void STUB_printf(const char *, ...);
extern int flag_set_first_pending(void *);
extern int flag_set_second_pending(void *);
extern int flag_is_third_pending_set(void *);
extern int CollLine(void *, void *, int, int, int);
extern char *D_L12_001FEAC0[];
extern char D_L12_001B0B70[];
extern unsigned short D_L12_001B0B00 __attribute__((sda));
extern float D_L12_001B0B68 __attribute__((sda));
extern float D_L12_001B0B64 __attribute__((sda));
extern int D_L12_001B29C8 __attribute__((sda));
extern char *D_L12_001C0258 NOT_SDA;
extern char *g_hero_moby NOT_SDA;

/* Sets up the robot guard on its first frame, then handles its hits, its colour pulse and its awareness of the hero. */
void robot_guard_init_update_state(char *obj) {
    char *vars = P(obj, 0x68);
    unsigned char oldState, oldAnim;
    int hitResult;
    float angle;
    float pos[4];
    if (!B(obj, 0x20)) {
        H(P(obj, 0x24), 0x46) = 5;
        U(obj, 0x34) |= 0x1000;
        F(vars, 0x30) = 2.25f;
        B(vars, 0x48) = FloatToInt(20.0f);
        B(vars, 0x4A) = FloatToInt(24.0f);
        B(vars, 0x70) = 17;
        W(vars, 0xA8) = 3;
        B(vars, 0x71) = 4;
        B(vars, 0x72) = 5;
        B(vars, 0x76) = 6;
        F(vars, 0x7C) = 0.1666666716337204f;
        F(vars, 0x80) = 0.06666667014360428f;
        F(vars, 0x88) = 0.0069444444961845875f;
        F(vars, 0x8C) = F(vars, 0x84) = 0.004166666883975267f;
        F(vars, 0x94) = F(vars, 0x90) = 0.5f;
        F(vars, 0x9C) = 0.4f;
        B(vars, 0xCD) = 26;
        B(vars, 0xCE) = 8;
        B(vars, 0xCF) = B(vars, 0xCC) = 11;
        B(vars, 0xD2) = 10;
        B(vars, 0xD3) = 17;
        B(vars, 0xD5) = 1;
        if (W(vars, 0x158) == -1) {
            moby_mark_spawned(obj);
            return;
        }
        W(vars, 0x1A8) |= 0x15;
        B(vars, 0x28) = 3;
        F(vars, 0x1A4) = 0.3f;
        F(vars, 0x170) = 1.25f;
        F(vars, 0x17C) = F(vars, 0x178) = F(vars, 0x174) = 2.0f;
        F(vars, 0x180) = 3.1415929794311523f;
        F(vars, 0x1A0) = 0.523598849773407f;
        F(vars, 0x19C) = 0.0055555556900799274f;
        B(vars, 0xD6) = 1;
        moby_set_state(obj, 5, 0);
        if (B(obj, 0x43))
            anim_start_blended(obj, 0, 0, 0);
        W(vars, 0x154) = W(vars, 0x150);
        if (W(vars, 0x164) == -1)
            qcopy(obj + 0x10, D_L12_001FEAC0[W(vars, 0x158)] + 0x10);
        else
            qcopy(obj + 0x10, D_L12_001FEAC0[W(vars, 0x164)] + 0x10);
        if (W(vars, 0x164) != -1)
            moby_set_state(obj, 2, 7);
        if (P(vars, 0x294))
            W(P(vars, 0x294), 0) = -1;
    }
    if (B(obj, 0x31) && fast_vec_dist(obj + 0x10, D_L12_001B9E00) < 24.0f) {
        moby_update_ground_check(obj);
        B(obj, 0x6F) = 22;
    }
    if (W(vars, 0x2A0) && flag_is_third_pending_set(obj))
        moby_set_state(obj, 24, 4);
    oldState = B(obj, 0x20);
    oldAnim = B(obj, 0x95);
    hitResult = moby_apply_damage_to_object(obj, vars + 0x60, 0);
    if (hitResult) {
        if (hitResult == 4) {
            STUB_printf(D_L12_001B0B70);
            W(vars, 0x278) = 5;
        } else
            W(vars, 0x278) = 1;
        B(obj, 0x20) = oldState;
        B(obj, 0x95) = oldAnim;
        flag_set_first_pending(obj);
        flag_set_second_pending(obj);
        H(vars, 0x26) = D_L12_001B0B00;
        H(vars, 0x274) = 150;
    }
    if (FastDecTimer(vars + 0x274)) {
        if (W(vars, 0x278) != 1)
            W(vars, 0x278) = 0;
        else
            H(vars, 0x274) = 50;
    }
    H(vars, 0x276) = weapon_select_aim_target(obj, W(vars, 0x150), 0, 0, 6.0f, 0.0f);
    W(vars, 0x270) = W(vars, 0x140);
    if (P(vars, 0x140) && vec_distance_xy(P(vars, 0x140) + 0x10, obj + 0x10) < 16.0f) {
        qcopy(pos, obj + 0x10);
        pos[2] += D_L12_001B0B68;
        if (!CollLine(pos, vars + 0x130, 16, 0, 0) || D_L12_001C0258 == g_hero_moby) {
            if (H(vars, 0x276) != 1)
                H(vars, 0x276) = 1;
        }
    }
    if (B(obj, 0x31)) {
        angle = IntToFloat(D_L12_001B29C8 % 60);
        angle = angle * 6.2831854820251465f / IntToFloat(60) - 3.1415927410125732f;
        W(obj, 0x78) = PulseColor(0x80808080, 0x80303030, angle);
    }
    value_set_and_smooth(obj, vars + 0x2B0, 1, 1, D_L12_001B0B64);
}
