#include "names.h"
/* func_PAL_L00_004266C8, the PAL copy of func_L00_004212B8: the same C, where the 15 and 16 frame limits
   become 12 and 13 and the timers are scaled by (D * 5 + 2) / 6. */
#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; } Hero;
extern char g_hero_state[];
typedef struct {
    float base[4];
    float a10[4];
    float a20[4];
    float a30[4];
    char pad40[0x20];
    float a60[4];
    char pad70[0x40];
    float rB0;
    char padB4[0x10];
    u8 st;
    char padC5;
    s16 tC6;
    float invC8;
    float rCC;
    float rD0;
    s16 tD4;
    u8 fD6;
    u8 fD7;
    s16 hD8;
    char padDA[0x12];
    s16 hEC;
    s16 hEE;
} Ctl;
extern int coll_test_point(void *, int, void *, float);
extern int FastDecTimer(void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float FastVecLength(void *);
extern void hero_copy_vector_to_out(void *, void *);
extern int cam_resolve_position(void *, int);
extern float cam_compute_signed_angle_to_point(void *, float);
extern void cam_compute_offset(void *, int, float);
extern int g_hero_locked_flag MACRO_ADDR;
extern float g_cam_follow_distance_max __attribute__((sda));
extern float g_cam_follow_distance_min __attribute__((sda));
extern int g_camera_default_frame_count __attribute__((sda));
extern u16 g_weapon_anim_ctrl2_frames __attribute__((sda));
extern int g_weapon_aim_in_frames __attribute__((sda));
extern u16 g_weapon_anim_return_frames __attribute__((sda));
extern float g_weapon_aim15_level __attribute__((sda));
extern int g_weapon_anim_timer2_frames __attribute__((sda));
extern float g_cam_follow_lerp_factor __attribute__((sda));
extern char g_camera_move_state[];
void func_PAL_L00_004266C8(char *moby, void *out)
{
    float sp[4], tmp[4];
    Ctl *s = (Ctl *)(*(char **)(moby + 0x70) + 0x60);
    char *cam = g_camera_move_state;
    char *c;
    char *v;
    int use;
    float d;
    if (((Hero *)g_hero_state)->h[0x348 / 2] != 0 || g_hero_locked_flag != 0 || (s->hEE != 0 && ((Hero *)g_hero_state)->h[0x34E / 2] != 0)) {
        s->hEC = 0xC;
        s->fD6 = 1;
        s->hEE = 1;
        FastVecScale(s->a10, cam + 0x30, FastVecDot(s, cam + 0x30));
        qcopy(s->a20, s->a10);
        if ((u32)(s->st - 5) < 3 || s->st == 3)
            cam_compute_offset(s->a30, 1, g_weapon_aim15_level * 0.5f);
    } else {
        short st = s->hEE;
        if (st == 1) {
            float r;
            FastVecScale(s->a10, cam + 0x30, FastVecDot(s, cam + 0x30));
            qcopy(s->a20, s->a10);
            if ((u32)(s->st - 5) < 3 || s->st == 3)
                cam_compute_offset(s->a30, 1, g_weapon_aim15_level * 0.5f);
            r = IntToFloat(s->hD8);
            r = r / IntToFloat(0xC);
            s->hD8 = FloatToInt(IntToFloat(s->hEC) * r);
            s->hEE = 2;
        } else {
            if (st >= 2) {
                FastVecScale(s->a10, cam + 0x30, FastVecDot(s, cam + 0x30));
                qcopy(s->a20, s->a10);
                if ((u32)(s->st - 5) < 3 || s->st == 3)
                    cam_compute_offset(s->a30, 1, g_weapon_aim15_level * 0.5f);
                s->hEE = s->hEE + 1;
                if (s->hEE >= 0xD)
                    s->hEE = 0;
            }
        }
    }
    c = cam + 0x30;
    hero_copy_vector_to_out(moby, sp);
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x74) {
        FastVecScale(out, c, FastVecDot(s, c));
        FastVecSub(s, s, out);
        FastVecScale(out, c, FastVecDot(c, s->a60));
        qcopy(s->a10, out);
        if (s->st != 0xB) {
            s->st = 0xB;
            {
                char *o;
                int t;
                qcopy(moby + 0x40, moby);
                o = *(char **)(moby + 0x70);
                t = (g_camera_default_frame_count * 5 + 2) / 6;
                { char *m = o + 0x20;
                *(s16 *)m = t;
                *(float *)(m + 0x24) = 1.0f / IntToFloat((s16)t); }
            }
        }
    } else {
        switch (s->st) {
        case 2:
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x11
                || (((Hero *)g_hero_state)->b[0x49E] != 0 && ((Hero *)g_hero_state)->f[0x31C / 4] > 0.2f)) {
                u16 t;
                if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x11) {
                    d = cam_compute_signed_angle_to_point(moby, s->rB0);
                    if (!(d < g_cam_follow_distance_min) && !(g_cam_follow_distance_max < d))
                        goto next;
                }
                s->st = 1;
                t = g_weapon_anim_ctrl2_frames;
                s->tC6 = t;
                s->invC8 = 1.0f / IntToFloat((s16)t);
            }
        next:
            use = 0;
            if (((Hero *)g_hero_state)->h[0x34C / 2] != 0 && (((Hero *)g_hero_state)->b[0x49E] == 0 || ((Hero *)g_hero_state)->h[0x4AE / 2] >= 0x10)) {
                use = 1;
            } else {
                if (cam_resolve_position(tmp, 1) != 1)
                    use = 1;
                else if (FastVecDot(tmp, c) < FastVecLength(s->a10))
                    use = 1;
            }
            v = (char *)tmp;
            if (use) {
                qcopy(out, s->a10);
                FastVecScale(v, c, FastVecDot(sp, c));
                FastVecSub(s, sp, v);
            } else {
                cam_resolve_position(v, 1);
                FastVecScale(out, c, FastVecDot(v, c));
                FastVecSub(s, v, out);
            }
            break;
        case 3:
        case 5:
        case 6:
        case 7:
            {
                lerp_vector(s->a10, s->a30, s->a20, (float)s->tD4 * s->rCC);
                if (s->fD7 == 0 && coll_test_point(moby + 0x30, 0x12, 0, 0.2f) != 0) {
                    qcopy(s->a30, s->a10);
                    s->fD7 = 1;
                }
                qcopy(out, s->a10);
                d = FastVecDot(sp, c);
                v = (char *)tmp;
                FastVecScale(v, c, d);
                FastVecSub(s, sp, v);
                if (FastDecTimer(&s->tD4) != 0) {
                    if (s->st == 9) {
                        s->st = 0xA;
                        s->tD4 = (g_weapon_anim_timer2_frames * 5 + 2) / 6;
                        qcopy(s->a20, s->a10);
                        FastVecScale(v, c, s->rD0);
                        FastVecSub(s->a30, s->a20, v);
                    } else if (s->st == 6) {
                        s->st = 7;
                        s->tD4 = (g_weapon_aim_in_frames * 5 + 2) / 6;
                        qcopy(s->a30, s->a20);
                        qcopy(s->a20, s->a10);
                    } else {
                        u16 t;
                        s->st = 4;
                        t = g_weapon_anim_return_frames;
                        s->tC6 = t;
                        s->invC8 = 1.0f / IntToFloat((s16)t);
                    }
                }
            }
            break;
        case 8:
            qcopy(out, s->a10);
            d = FastVecDot(sp, c);
            v = (char *)tmp;
            FastVecScale(v, c, d);
            FastVecSub(s, sp, v);
            break;
        case 9:
        case 10:
            FastVecScale(out, c, FastVecDot(sp, c));
            FastVecSub(s, sp, out);
            lerp_vector(out, out, s->a20, g_cam_follow_lerp_factor);
            break;
        default:
            FastVecScale(out, c, FastVecDot(sp, c));
            FastVecSub(s, sp, out);
            break;
        }
    }
}
