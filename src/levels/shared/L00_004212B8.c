#include "names.h"
/* Follow-camera state (object +0x70, +0x60): the 0x74 and per-state cases, with the offset from the target. */
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
extern int D_L00_001A8FF0 MACRO_ADDR;
extern float D_L00_001B1500 __attribute__((sda));
extern float D_L00_001B1504 __attribute__((sda));
extern u16 D_L00_001B1518 __attribute__((sda));
extern u16 D_L00_001B1530 __attribute__((sda));
extern u16 D_L00_001B1534 __attribute__((sda));
extern u16 D_L00_001B1548 __attribute__((sda));
extern float D_L00_001B154C __attribute__((sda));
extern u16 D_L00_001B1560 __attribute__((sda));
extern float D_L00_001B1574 __attribute__((sda));
extern char D_L00_001B8E20[];
#define HERO ((Hero *)D_00189E20)
/* Works out where the follow camera wants to be this frame, depending on its mode and what the hero is doing, and writes the result to out. */
void cam_follow_compute_position(char *moby, void *out)
{
    float position[4], scratch[4];
    Ctl *settings = (Ctl *)(*(char **)(moby + 0x70) + 0x60);
    char *cam = D_L00_001B8E20;
    char *axis;
    char *work;
    int use;
    float d;
    if (HERO->h[0x348 / 2] != 0 || D_L00_001A8FF0 != 0 || (settings->hEE != 0 && HERO->h[0x34E / 2] != 0)) {
        settings->hEC = 0xF;
        settings->fD6 = 1;
        settings->hEE = 1;
        FastVecScale(settings->a10, cam + 0x30, FastVecDot(settings, cam + 0x30));
        qcopy(settings->a20, settings->a10);
        if ((u32)(settings->st - 5) < 3 || settings->st == 3)
            cam_compute_offset(settings->a30, 1, D_L00_001B154C * 0.5f);
    } else {
        short st = settings->hEE;
        if (st == 1) {
            float r;
            FastVecScale(settings->a10, cam + 0x30, FastVecDot(settings, cam + 0x30));
            qcopy(settings->a20, settings->a10);
            if ((u32)(settings->st - 5) < 3 || settings->st == 3)
                cam_compute_offset(settings->a30, 1, D_L00_001B154C * 0.5f);
            r = IntToFloat(settings->hD8);
            r = r / IntToFloat(0xF);
            settings->hD8 = FloatToInt(IntToFloat(settings->hEC) * r);
            settings->hEE = 2;
        } else {
            if (st >= 2) {
                FastVecScale(settings->a10, cam + 0x30, FastVecDot(settings, cam + 0x30));
                qcopy(settings->a20, settings->a10);
                if ((u32)(settings->st - 5) < 3 || settings->st == 3)
                    cam_compute_offset(settings->a30, 1, D_L00_001B154C * 0.5f);
                settings->hEE = settings->hEE + 1;
                if (settings->hEE >= 0x10)
                    settings->hEE = 0;
            }
        }
    }
    axis = cam + 0x30;
    hero_copy_vector_to_out(moby, position);
    if (HERO->i[0x2294 / 4] == 0x74) {
        FastVecScale(out, axis, FastVecDot(settings, axis));
        FastVecSub(settings, settings, out);
        FastVecScale(out, axis, FastVecDot(axis, settings->a60));
        qcopy(settings->a10, out);
        if (settings->st != 0xB) {
            settings->st = 0xB;
            {
                char *o;
                u16 frames;
                qcopy(moby + 0x40, moby);
                frames = D_L00_001B1518;
                o = *(char **)(moby + 0x70);
                { char *m = o + 0x20;
                *(s16 *)m = frames;
                *(float *)(m + 0x24) = 1.0f / IntToFloat((s16)frames); }
            }
        }
    } else {
        switch (settings->st) {
        case 2:
            if (HERO->i[0x2294 / 4] == 0x11
                || (HERO->b[0x49E] != 0 && HERO->f[0x31C / 4] > 0.2f)) {
                u16 frames;
                if (HERO->i[0x2294 / 4] != 0x11) {
                    d = cam_compute_signed_angle_to_point(moby, settings->rB0);
                    if (!(d < D_L00_001B1504) && !(D_L00_001B1500 < d))
                        goto next;
                }
                settings->st = 1;
                frames = D_L00_001B1530;
                settings->tC6 = frames;
                settings->invC8 = 1.0f / IntToFloat((s16)frames);
            }
        next:
            use = 0;
            if (HERO->h[0x34C / 2] != 0 && (HERO->b[0x49E] == 0 || HERO->h[0x4AE / 2] >= 0x10)) {
                use = 1;
            } else {
                if (cam_resolve_position(scratch, 1) != 1 || FastVecDot(scratch, axis) < FastVecLength(settings->a10))
                    use = 1;
            }
            work = (char *)scratch;
            if (use) {
                qcopy(out, settings->a10);
                FastVecScale(work, axis, FastVecDot(position, axis));
                FastVecSub(settings, position, work);
            } else {
                cam_resolve_position(work, 1);
                FastVecScale(out, axis, FastVecDot(work, axis));
                FastVecSub(settings, work, out);
            }
            break;
        case 3:
        case 5:
        case 6:
        case 7:
            {
                lerp_vector(settings->a10, settings->a30, settings->a20, (float)settings->tD4 * settings->rCC);
                if (settings->fD7 == 0 && coll_test_point(moby + 0x30, 0x12, 0, 0.2f) != 0) {
                    qcopy(settings->a30, settings->a10);
                    settings->fD7 = 1;
                }
                qcopy(out, settings->a10);
                d = FastVecDot(position, axis);
                work = (char *)scratch;
                FastVecScale(work, axis, d);
                FastVecSub(settings, position, work);
                if (FastDecTimer(&settings->tD4) != 0) {
                    if (settings->st == 9) {
                        settings->st = 0xA;
                        settings->tD4 = D_L00_001B1560;
                        qcopy(settings->a20, settings->a10);
                        FastVecScale(work, axis, settings->rD0);
                        FastVecSub(settings->a30, settings->a20, work);
                    } else if (settings->st == 6) {
                        settings->st = 7;
                        settings->tD4 = D_L00_001B1534;
                        qcopy(settings->a30, settings->a20);
                        qcopy(settings->a20, settings->a10);
                    } else {
                        u16 frames;
                        settings->st = 4;
                        frames = D_L00_001B1548;
                        settings->tC6 = frames;
                        settings->invC8 = 1.0f / IntToFloat((s16)frames);
                    }
                }
            }
            break;
        case 8:
            qcopy(out, settings->a10);
            d = FastVecDot(position, axis);
            work = (char *)scratch;
            FastVecScale(work, axis, d);
            FastVecSub(settings, position, work);
            break;
        case 9:
        case 10:
            FastVecScale(out, axis, FastVecDot(position, axis));
            FastVecSub(settings, position, out);
            lerp_vector(out, out, settings->a20, D_L00_001B1574);
            break;
        default:
            FastVecScale(out, axis, FastVecDot(position, axis));
            FastVecSub(settings, position, out);
            break;
        }
    }
}
