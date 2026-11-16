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
/* Works out where the follow camera wants to be: blends the stored offsets, in a state-dependent way,
   into the hero-relative position (PAL: 50 Hz timings). */
void cam_follow_compute_position_pal(char *moby, void *out)
{
    float move_vec[4], tmp[4];
    Ctl *ctl = (Ctl *)(*(char **)(moby + 0x70) + 0x60);
    char *cam = g_camera_move_state;
    char *axis;
    char *proj;
    int use_stored;
    float dist;
    if (((Hero *)g_hero_state)->h[0x348 / 2] != 0 || g_hero_locked_flag != 0 || (ctl->hEE != 0 && ((Hero *)g_hero_state)->h[0x34E / 2] != 0)) {
        ctl->hEC = 0xC;
        ctl->fD6 = 1;
        ctl->hEE = 1;
        FastVecScale(ctl->a10, cam + 0x30, FastVecDot(ctl, cam + 0x30));
        qcopy(ctl->a20, ctl->a10);
        if ((u32)(ctl->st - 5) < 3 || ctl->st == 3)
            cam_compute_offset(ctl->a30, 1, g_weapon_aim15_level * 0.5f);
    } else {
        short st = ctl->hEE;
        if (st == 1) {
            float r;
            FastVecScale(ctl->a10, cam + 0x30, FastVecDot(ctl, cam + 0x30));
            qcopy(ctl->a20, ctl->a10);
            if ((u32)(ctl->st - 5) < 3 || ctl->st == 3)
                cam_compute_offset(ctl->a30, 1, g_weapon_aim15_level * 0.5f);
            r = IntToFloat(ctl->hD8);
            r = r / IntToFloat(0xC);
            ctl->hD8 = FloatToInt(IntToFloat(ctl->hEC) * r);
            ctl->hEE = 2;
        } else {
            if (st >= 2) {
                FastVecScale(ctl->a10, cam + 0x30, FastVecDot(ctl, cam + 0x30));
                qcopy(ctl->a20, ctl->a10);
                if ((u32)(ctl->st - 5) < 3 || ctl->st == 3)
                    cam_compute_offset(ctl->a30, 1, g_weapon_aim15_level * 0.5f);
                ctl->hEE = ctl->hEE + 1;
                if (ctl->hEE >= 0xD)
                    ctl->hEE = 0;
            }
        }
    }
    axis = cam + 0x30;
    hero_copy_vector_to_out(moby, move_vec);
    if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x74) {
        FastVecScale(out, axis, FastVecDot(ctl, axis));
        FastVecSub(ctl, ctl, out);
        FastVecScale(out, axis, FastVecDot(axis, ctl->a60));
        qcopy(ctl->a10, out);
        if (ctl->st != 0xB) {
            ctl->st = 0xB;
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
        switch (ctl->st) {
        case 2:
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x11
                || (((Hero *)g_hero_state)->b[0x49E] != 0 && ((Hero *)g_hero_state)->f[0x31C / 4] > 0.2f)) {
                u16 t;
                if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x11) {
                    dist = cam_compute_signed_angle_to_point(moby, ctl->rB0);
                    if (!(dist < g_cam_follow_distance_min) && !(g_cam_follow_distance_max < dist))
                        goto next;
                }
                ctl->st = 1;
                t = g_weapon_anim_ctrl2_frames;
                ctl->tC6 = t;
                ctl->invC8 = 1.0f / IntToFloat((s16)t);
            }
        next:
            use_stored = 0;
            if (((Hero *)g_hero_state)->h[0x34C / 2] != 0 && (((Hero *)g_hero_state)->b[0x49E] == 0 || ((Hero *)g_hero_state)->h[0x4AE / 2] >= 0x10)) {
                use_stored = 1;
            } else {
                if (cam_resolve_position(tmp, 1) != 1)
                    use_stored = 1;
                else if (FastVecDot(tmp, axis) < FastVecLength(ctl->a10))
                    use_stored = 1;
            }
            proj = (char *)tmp;
            if (use_stored) {
                qcopy(out, ctl->a10);
                FastVecScale(proj, axis, FastVecDot(move_vec, axis));
                FastVecSub(ctl, move_vec, proj);
            } else {
                cam_resolve_position(proj, 1);
                FastVecScale(out, axis, FastVecDot(proj, axis));
                FastVecSub(ctl, proj, out);
            }
            break;
        case 3:
        case 5:
        case 6:
        case 7:
            {
                lerp_vector(ctl->a10, ctl->a30, ctl->a20, (float)ctl->tD4 * ctl->rCC);
                if (ctl->fD7 == 0 && coll_test_point(moby + 0x30, 0x12, 0, 0.2f) != 0) {
                    qcopy(ctl->a30, ctl->a10);
                    ctl->fD7 = 1;
                }
                qcopy(out, ctl->a10);
                dist = FastVecDot(move_vec, axis);
                proj = (char *)tmp;
                FastVecScale(proj, axis, dist);
                FastVecSub(ctl, move_vec, proj);
                if (FastDecTimer(&ctl->tD4) != 0) {
                    if (ctl->st == 9) {
                        ctl->st = 0xA;
                        ctl->tD4 = (g_weapon_anim_timer2_frames * 5 + 2) / 6;
                        qcopy(ctl->a20, ctl->a10);
                        FastVecScale(proj, axis, ctl->rD0);
                        FastVecSub(ctl->a30, ctl->a20, proj);
                    } else if (ctl->st == 6) {
                        ctl->st = 7;
                        ctl->tD4 = (g_weapon_aim_in_frames * 5 + 2) / 6;
                        qcopy(ctl->a30, ctl->a20);
                        qcopy(ctl->a20, ctl->a10);
                    } else {
                        u16 t;
                        ctl->st = 4;
                        t = g_weapon_anim_return_frames;
                        ctl->tC6 = t;
                        ctl->invC8 = 1.0f / IntToFloat((s16)t);
                    }
                }
            }
            break;
        case 8:
            qcopy(out, ctl->a10);
            dist = FastVecDot(move_vec, axis);
            proj = (char *)tmp;
            FastVecScale(proj, axis, dist);
            FastVecSub(ctl, move_vec, proj);
            break;
        case 9:
        case 10:
            FastVecScale(out, axis, FastVecDot(move_vec, axis));
            FastVecSub(ctl, move_vec, out);
            lerp_vector(out, out, ctl->a20, g_cam_follow_lerp_factor);
            break;
        default:
            FastVecScale(out, axis, FastVecDot(move_vec, axis));
            FastVecSub(ctl, move_vec, out);
            break;
        }
    }
}
