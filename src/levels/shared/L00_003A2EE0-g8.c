/* Scoped weapon update: targeting, zoom, firing, reload and muzzle light. */
#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; } Hero;
typedef union { u8 b[0x200]; s32 i[0x80]; } GameState;
typedef union { u8 b[0x70]; s32 i[0x1C]; char *p[0x1C]; } SoundSlot;

typedef struct {
    s16 zoomed;
    s16 fire_timer;
    f32 reload;
    f32 zoom_max;
    f32 zoom;
    s32 light;
    s32 flash;
    s32 model;
    char *record;
    s32 sound;
    s32 hud;
    s32 shots;
    s16 locked;
    s16 blink;
    char *target;
} ScopeState;

typedef struct { f32 radius, spread, power, reserved; f32 position[4]; } MuzzleLight;
typedef struct { u8 pad[0x54]; f32 rate; u8 tail[0x88]; } WeaponEntry;
typedef struct { u8 b[0x10]; } TargetRecord;

extern char D_00189E20[];
extern char D_00138180[];
extern SoundSlot D_00188660[];
extern u16 D_0018CCD0[];
extern u8 D_0013957F[];

extern s32 D_L00_001AA0F8;
extern s32 D_L00_001B19C8;
extern f32 D_L00_001AF614 __attribute__((sda));
extern f32 D_L00_001AF618 __attribute__((sda));
extern f32 D_L00_001AF61C __attribute__((sda));
extern f32 D_L00_001AF620 __attribute__((sda));
extern f32 D_L00_001B15CC;
extern f32 D_L00_001B15D0;
extern f32 D_L00_001B15D4;
extern f32 D_L00_001B15D8;
extern f32 D_L00_001BD370[];
extern char D_L00_001B8DC0[];
extern char *D_L00_001BF218[];
extern MuzzleLight D_L00_001C6F40[];
extern WeaponEntry D_L00_00262570[];
extern TargetRecord D_L00_00294800[];

extern void func_0026FF08(int, int, float, float, float, float);
extern void func_00273318(void *, float, u32, void *, int, float, int, float, int);
extern int func_002761F8(void *, void *, int, int, void *);
extern int func_00282948(void *);
extern int func_00282978(void *);
extern int func_002829D8(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283248(float, float);
extern float func_00283CE0(int);
extern int func_00288E18(int, int);
extern int func_00291308(float, void *, u32, float);
extern void func_00291450(s32);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002A75E0(void *, int, int, int, int);
extern float *func_002AB1F0(void *);
extern int func_002ABB78(void *);
extern void func_002E59F8(s32);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002AF568(void);
extern void func_L00_002C42E0(int, int);
extern int func_L00_002D3F30(int, int);
extern int func_L00_002D4040(int);
extern int func_L00_002D6998(TargetRecord *);
extern void func_L00_002D6B70(int);
extern int func_L00_00329E90(void *, int, int *);
extern int func_L00_00329FF0(char *);
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
extern void func_L00_00368F58(int);
extern void func_L00_003A3B58(void *);
extern void func_L00_003A8508(int);

#define HERO ((Hero *)D_00189E20)
#define GAME ((GameState *)D_00138180)

/* Per-frame update for the Pulse Rifle moby: lets the player zoom in, aim, fire and reload, and flashes the muzzle light. */
void func_L00_003A2EE0(u8 *moby)
{
    ScopeState *st = *(ScopeState **)(moby + 0x68);
    float saved[4];
    float muzzle[4];
    float offset[4];
    int found;
    int fire;

    if (HERO->i[0x1244 / 4] == 3) {
        if (moby[0x20] == 0)
            return;
        D_L00_001B15D0 = D_L00_001AF614;
        D_L00_001B15D4 = D_L00_001AF618;
        D_L00_001B15D8 = D_L00_001AF61C;
        D_L00_001B15CC = D_L00_001AF620;
        SetCameraValueTarget(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
        if (st->light >= 0)
            FreePointLight(st->light);
        st->light = -1;
        D_L00_001AA0F8 = 0xE0;
        UpdateFrameTimeScales(1);
        return;
    }
    if (HERO->i[0x2294 / 4] == 0x6F) {
        if (moby[0x20] == 4)
            return;
        moby[0x20] = 4;
        if (st->light >= 0)
            FreePointLight(st->light);
        st->light = -1;
        D_L00_001B15D0 = D_L00_001AF614;
        D_L00_001B15D4 = D_L00_001AF618;
        D_L00_001B15D8 = D_L00_001AF61C;
        D_L00_001B15CC = D_L00_001AF620;
        SetCameraValueTarget(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
        UpdateFrameTimeScales(1);
        return;
    }
    if (moby[0x20] == 4)
        moby[0x20] = 1;
    qcopy(saved, moby + 0x10);
    if (moby[0x42] == moby[0x43] && (moby[0x60] & 2))
        StartAnimationBlendedWithFlags(moby, 1, 0, 2, 0);
    if (HERO->i[0x1500 / 4] != 0 && moby[0x20] != 0) {
        if (gFrameCounter_L00 & 4) {
            st->target = 0;
            st->locked = 0;
            vec_scale_to_length(muzzle, gCameraPosition_L00 + 0x230, 128.0f);
            FastVecAdd(muzzle, muzzle, gCameraPosition_L00);
            if (CollLine(gCameraPosition_L00, muzzle, 0x10, HERO->i[0x2290 / 4], 0) != 0) {
                u8 *hit = (u8 *)D_L00_001BF218[0];
                if (hit != 0 && hit[0x31] != 0) {
                    float *health = GetMobyPrivateValue0(hit);
                    if (IsMobyInSpecialClassRange(hit) != 0
                        || (health != 0 && *health > 0.0f && *(u8 **)(hit + 0x24) != 0
                            && *(s16 *)(*(u8 **)(hit + 0x24) + 0x46) == 5)) {
                        st->target = (char *)hit;
                        st->locked = 1;
                    }
                }
            }
        }
        if (HERO->i[0x2534 / 4] == 0) {
            if (st->locked != 0) {
                st->blink++;
                if (st->blink > 20)
                    st->blink = 0;
                if (st->reload <= 0.0f && get_ammo(-1) != 0 && st->blink > 10)
                    AddMobyMarker(moby, 1.5f, 0x400000FF, 0, 0x20, 0.0f, -1, 90.0f, 4);
            }
            AddMobyMarker(moby, 2.0f, (st->reload > 0.0f && get_ammo(-1) != 0) ? 0x600000FF : 0x600FFF0F,
                          0, 0x27, 0.0f, -1, 90.0f, 4);
        }
    }
    switch (moby[0x20]) {
    case 0: {
        float max;
        st->zoomed = 0;
        st->reload = 0.36666667f;
        moby[0x20] = 3;
        max = FastMatrixHelperA(1.0f, D_L00_001BD370[0]) * 2.0f;
        st->zoom_max = max;
        st->zoom = max + (0.17453295f - max) * 0.25f;
        D_L00_001AF614 = D_L00_001B15D0;
        D_L00_001AF618 = D_L00_001B15D4;
        D_L00_001AF61C = D_L00_001B15D8;
        D_L00_001AF620 = D_L00_001B15CC;
        st->flash = 0;
        st->locked = 0;
        st->blink = 0;
        st->target = 0;
        st->light = -1;
        st->sound = -1;
        st->hud = -1;
        st->model = AcquireEntitySlot(moby, 0, &found);
        if (found == 0) {
            char *record = GetSlotBody(*(s16 *)(moby + 0xAA), st->model);
            int *size = GetSlotHeader(*(s16 *)(moby + 0xAA), st->model);
            st->record = record;
            *size = RoundUpToMultipleOf16_L00(record + 0x2300) - (int)record;
        }
        if (st->model >= 0)
            ClearBeamParticlePool(st->model);
        break;
    }
    case 1: {
        float zoomBlend;
        if (HERO->i[0x2294 / 4] == 1)
            SetHeroAction_L00(0x1D, 1);
        fire = 1;
        if (HERO->i[0x1500 / 4] != 0) {
            fire = 0;
            if (FastFloatHelperD(&HERO->i[0x2534 / 4]) != 0)
                fire = 1;
            if (st->zoomed == 0)
                D_L00_001AA0F8 = 0;
            st->zoomed = 1;
        } else {
            HERO->i[0x2534 / 4] = 0x28;
        }
        if (HERO->i[0x1450 / 4] != 0)
            HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];
        if (HERO->i[0x1500 / 4] != 0) {
            if ((GAME->i[0x1A0 / 4] & 8) && st->zoom > 0.17453295f) {
                SoundSlot *slot = &gSoundState[st->sound];
                if ((u8 *)slot->p[0x88 / 4] != moby || slot->b[0x74] == 0)
                    st->sound = PlayMobySound(2, 4, moby);
                D_0018CCD0[0] = 0xFFFF;
                st->zoom -= 0.01f;
            } else if ((GAME->i[0x1A0 / 4] & 2) && st->zoom < st->zoom_max) {
                SoundSlot *slot = &gSoundState[st->sound];
                if ((u8 *)slot->p[0x88 / 4] != moby || slot->b[0x74] == 0)
                    st->sound = PlayMobySound(3, 4, moby);
                D_0018CCD0[0] = 0xFFFF;
                st->zoom += 0.01f;
            } else {
                int h = st->sound;
                if (h != -1) {
                    SoundSlot *slot = &gSoundState[h];
                    if ((u8 *)slot->p[0x88 / 4] == moby && slot->b[0x74] != 0)
                        StopSoundVoice(h);
                }
                st->sound = -1;
            }
            if (st->zoom > st->zoom_max)
                st->zoom = st->zoom_max;
            else if (st->zoom < 0.17453295f)
                st->zoom = 0.17453295f;
            SetCameraValueTarget(0, 3, st->zoom, 0.02f, 0.2f, 0.0f);
            UpdateFrameTimeScales(0);
        } else {
            int h = st->sound;
            if (h != -1) {
                SoundSlot *slot = &gSoundState[h];
                if ((u8 *)slot->p[0x88 / 4] == moby && slot->b[0x74] != 0)
                    StopSoundVoice(h);
            }
            st->sound = -1;
            if (st->zoomed != 0) {
                float max = st->zoom_max;
                st->zoom = max + (0.17453295f - max) * 0.25f;
                SetCameraValueTarget(0, 3, max, 0.005f, 0.2f, 0.0f);
                st->zoomed = 0;
                D_L00_001AA0F8 = 0xE0;
                UpdateFrameTimeScales(1);
            }
        }
        zoomBlend = (st->zoom - 0.17453295f) / (st->zoom_max - 0.17453295f);
        D_L00_001B15D0 = (D_L00_001AF614 - 0.03f) * zoomBlend + 0.03f;
        D_L00_001B15D4 = (D_L00_001AF618 - 0.4f) * zoomBlend + 0.4f;
        D_L00_001B15CC = (D_L00_001AF620 - 0.010471977f) * zoomBlend + 0.010471977f;
        if (HERO->b[0x22BC] == 0 && (GAME->i[0x1A4 / 4] & HERO->i[0x1230 / 4]) && fire) {
            if (SpendWeaponAmmo(-1, 1) != 0) {
                start_equipped_item_animation();
                st->hud = CopyRecordsToFreeSlots(D_L00_00294800);
                st->fire_timer = 2;
                moby[0x20] = 2;
                StartAnimationBlended(moby, 2, 0, 0);
            } else {
                PlayMobySound(1, 0, moby);
            }
        }
        if (!(GAME->i[0x1A0 / 4] & HERO->i[0x1230 / 4]) || get_ammo(-1) == 0 || HERO->b[0x22B8] == 0) {
            if (st->hud >= 0) {
                ResetActiveSlots(st->hud);
                st->hud = -1;
            }
        }
        break;
    }
    case 2:
        if (HERO->i[0x1450 / 4] != 0)
            HERO->i[0xBF8 / 4] = HERO->i[0x1450 / 4];
        if (FastDecTimer(&st->fire_timer) != 0 || st->zoomed != 0) {
            int h = st->sound;
            if (h != -1) {
                SoundSlot *slot = &gSoundState[h];
                if ((u8 *)slot->p[0x88 / 4] == moby && slot->b[0x74] != 0)
                    StopSoundVoice(h);
            }
            st->sound = -1;
            PlayMobySound(0, 0, moby);
            FireBeamWithMuzzleFlash(moby);
            {
                WeaponEntry *weapon = &gWeaponTable_L00[D_0013957F[0]];
                st->reload = 1.0f / weapon->rate;
            }
            moby[0x20] = 3;
            if (++st->shots == 5)
                RequestSubtitleVoiceLine(0x9F3, 0x4A);
        }
        break;
    case 3:
        if (FastVectorHelperB(&st->reload) != 0)
            moby[0x20] = 1;
        break;
    }
    if (st->flash != 0) {
        if (FastFloatHelperD(&st->flash) != 0) {
            if (st->light >= 0)
                FreePointLight(st->light);
            st->light = -1;
        } else {
            if (st->light == -1)
                st->light = AddPointLight(15.0f, moby + 0x10, 0x7F608060, 0.0f);
            if (st->light >= 0) {
                float flashFraction;
                if (HERO->h[0x24EC / 2] == 1) {
                    TransformMobyJointToWorld(moby, 0, muzzle);
                    vec_scale_to_length(offset, moby + 0xD0, -1.5f);
                } else {
                    TransformMobyJointToWorld(moby, 0, muzzle);
                    vec_scale_to_length(offset, &HERO->f[0x760 / 4], 1.5f);
                }
                {
                    float (*positions)[8] = (float (*)[8])D_L00_001C6F40[0].position;
                    MuzzleLight *lights;
                    FastVecAdd(positions[st->light], muzzle, offset);
                    lights = (MuzzleLight *)((char *)positions - 0x10);
                    lights[st->light].position[3] = 15.0f;
                    flashFraction = IntToFloat(st->flash) / IntToFloat(30);
                    lights[st->light].spread = flashFraction;
                    lights[st->light].radius = flashFraction * 0.75f;
                    lights[st->light].power = lights[st->light].radius;
                }
            }
        }
    }
}
