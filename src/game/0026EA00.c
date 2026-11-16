#include "include_asm.h"
#include "names.h"

typedef struct { float x, y, z, w; } MarkerVector;
typedef struct {
    unsigned char *target;
    int active;
    float timer;
    int reserved;
    short alpha[16];
    short texture[16];
    unsigned int colour[16];
    float interpolation[16];
    float scale[16];
} MarkerStateView;
extern MarkerStateView g_marker_state;
extern MarkerVector g_camera_eye_state;
extern int g_reticle_screen_params[] __attribute__((sda));
extern float fast_vec_dist(MarkerVector *, MarkerVector *);
extern float IntToFloat(int);
extern void gfx_project_world_point_to_screen(MarkerVector *, MarkerVector *);
extern long GetEffectTextureDescriptor(int);
extern float math_fabs(float);
extern int FloatToInt(float);
extern void DrawTexturedQuad(int x, int y, int width, int height,
                        int u, int v, int uw, int vh, long colour, long texture);


extern void cam_switch_active(char *);
extern int Camera_ActivationCheckPriority(char *, char *);
extern int func_002A6640(void *, float *, int *);
extern int FloatToInt(float);

/* Family 34e74db3063e7a24 — 108 bytes, 2 placements (18_damosel, 6_notak).
   Same shape as be569dc253cd5555: walk the resident function-pointer table at
   0x1B2180, call each entry while the resident count at 0x1B21C0 says there is
   one, then clear the count.  Small-data profile: the count is a 4-byte scalar,
   so cc1 prints the bare-symbol macro and gas expands every site on its own. */
extern int g_delayed_call_count __attribute__((sda));

extern void (*g_delayed_call_list[])(void);

extern float math_fabs(float t);

extern float func_00283BE0_3(float, float);

extern float func_00282C48_5(float);

extern float FastAddRotations(float, float);

typedef unsigned char u8;

typedef unsigned short u16;

typedef struct {u8 prefix[0x190];u8 *object;} NativeObjectRefView;

extern NativeObjectRefView g_hero_object_ref;

extern void func_00282CF0_9(float *p);

extern float func_00282E20_4(float *p);

extern float func_00283248_7(float a, float b);

extern float func_00283BE0_5(float a, float b);

extern float func_00282DF0_3(float *p);

extern void Fdb046c5d_FUN_002742E8(void *);

extern void Fdb046c5d_FUN_00274128(void *);

extern int Fdb046c5d_FUN_00274500(void *);

extern void Fdb046c5d_FUN_00282F20(float, void *, void *);

extern void Fdb046c5d_FUN_00282DD8(void *, void *, void *);

extern void Fdb046c5d_FUN_00274A88(void *, void *, void *);

extern void Fdb046c5d_FUN_002AFFD8(void *, void *, int);

extern int Fdb046c5d_FUN_00274BA8(void *, void *, void *, float, float);

extern int Fdb046c5d_FUN_002E5CF8(int, int, void *);

extern unsigned int Fdb046c5d_FUN_00274768(void *, int, void *);

extern int Fdb046c5d_FUN_002E5F00(int, void *);

extern char Fdb046c5d_D_001BAFC0[];

extern char g_loader_memory[];
extern int g_vram_display_address[] __attribute__((sda));
extern int fast_decompress(int, void *);
extern void FlushCache(int);
extern void gfx_reset_packet_buffer(void);
extern long long tex_upload_blocks_return_setup(void *, int, int, int);
extern void gfx_write_clear_color_packets(void);
extern void PutDrawBufferSmall(void);
extern void gfx_queue_second_strip_packet(void);
extern void SubmitBufferedDmaChain(void);
extern void gfx_wait_for_dma_status_bits(int);
extern int gfx_wait_paths_idle(int, int);
extern int sceGsSyncV(int);

/* func_0026EA00 is in 0026EA00-splash.c. */

extern void gfx_install_dma_handlers(void);
extern void SetBackgroundColor(int, int, int);
extern void gfx_append_draw_list_header(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_remove_dma_handlers(void);

/* Draws one loading or splash screen frame by decompressing the image and sending it to the screen. */
void gfx_draw_splash_screen_frame(int arg)
{
    char *state = g_loader_memory;
    int *data;
    fast_decompress(arg, *(void **)(state + 20));
    FlushCache(0);
    gfx_reset_packet_buffer();
    gfx_install_dma_handlers();
    SetBackgroundColor(0, 0, 0);
    gfx_append_draw_list_header();
    gfx_append_draw_list_buffer_tag(0);
    data = *(int **)(state + 20);
    tex_upload_blocks_return_setup(data + 4, g_vram_display_address[0], data[0], data[1]);
    gfx_write_clear_color_packets();
    PutDrawBufferSmall();
    gfx_queue_second_strip_packet();
    FlushCache(0);
    SubmitBufferedDmaChain();
    gfx_wait_for_dma_status_bits(1);
    gfx_wait_paths_idle(0, 0);
    sceGsSyncV(0);
    gfx_remove_dma_handlers();
}


extern int math_random_int_below(int);

/* Picks a random order of the numbers 0, 1 and 2 and stores it in the three outputs. */
void math_shuffle_three_indices(int *first, int *second, int *third) {
    switch (math_random_int_below(3)) {
    case 0:
        *first = 0;
        *second = 1;
        *third = 2;
        break;
    case 1:
        *first = 1;
        *second = 0;
        *third = 2;
        break;
    case 2:
        *first = 2;
        *second = 1;
        *third = 0;
        break;
    }
    if (math_random_int_below(2) != 0) {
        int value = *second;
        *second = *third;
        *third = value;
    }
}

typedef struct { char b[8]; } CdClock;
extern int sceCdReadClock(CdClock *);
extern void func_001163A0(unsigned int);
/* Seeds the random generator from the disc clock, then fills a table of 24 tile numbers with shuffled values. */
void menu_fill_shuffled_tile_table(unsigned short *out)
{
    CdClock clock;
    int first, second, third;
    int low, high;
    int seed;
    sceCdReadClock(&clock);
    seed = (unsigned char)clock.b[1] + 1;
    seed *= (unsigned char)clock.b[3] + 1;
    seed *= (unsigned char)clock.b[2] + 1;
    seed *= (unsigned char)clock.b[5] + 1;
    seed *= (unsigned char)clock.b[6] + 1;
    func_001163A0(seed);
    math_shuffle_three_indices(&first, &second, &third);
    out[0x20/2] = out[0x08/2] = (unsigned short)first + 0xb9;
    out[0x28/2] = out[0x10/2] = (unsigned short)second + 0xb9;
    out[0x30/2] = out[0x18/2] = (unsigned short)third + 0xb9;
    if (math_random_int_below(2)) {
        low = 0xb3;
        high = 0xb6;
    } else {
        low = 0xb6;
        high = 0xb3;
    }
    math_shuffle_three_indices(&first, &second, &third);
    out[0x02/2] = (unsigned short)first + low;
    out[0x06/2] = (unsigned short)second + low;
    out[0x0c/2] = (unsigned short)third + low;
    out[0x12/2] = out[0x02/2];
    out[0x16/2] = out[0x06/2];
    out[0x1c/2] = out[0x0c/2];
    out[0x22/2] = out[0x02/2];
    out[0x26/2] = out[0x06/2];
    out[0x2c/2] = out[0x0c/2];
    math_shuffle_three_indices(&first, &second, &third);
    out[0x04/2] = (unsigned short)first + high;
    out[0x0a/2] = (unsigned short)second + high;
    out[0x0e/2] = (unsigned short)third + high;
    out[0x14/2] = out[0x04/2];
    out[0x1a/2] = out[0x0a/2];
    out[0x1e/2] = out[0x0e/2];
    out[0x24/2] = out[0x04/2];
    out[0x2a/2] = out[0x0a/2];
    out[0x2e/2] = out[0x0e/2];
}

/* func_0026EDE8 is in 0026EA00-loader.c. */

/* Empty stub that returns zero. */
unsigned int stub_empty(void)
{
    return 0;
}

void stub_empty_2(void)
{
}

void stub_empty_3(void)
{
}

void stub_empty_4(void)
{
}

unsigned int stub_empty_5(void)
{
    return 0;
}

unsigned int stub_empty_6(void)
{
    return 0;
}

unsigned int stub_empty_7(void)
{
    return 0;
}

unsigned int stub_empty_8(int unused0, int unused1)
{
    return 0;
}

void stub_empty_9(void)
{
}

void stub_empty_10(void)
{
}

void stub_empty_11(void)
{
}

void stub_empty_12(void)
{
}

void stub_empty_13(void)
{
}

void stub_empty_14(void)
{
}

void stub_empty_15(void)
{
}

void stub_empty_16(void)
{
}

void stub_empty_17(void)
{
}

void stub_empty_18(void)
{
}

unsigned int stub_empty_19(void)
{
    return 0;
}

void stub_empty_20(void)
{
}

unsigned int stub_empty_21(void)
{
    return 0;
}

unsigned int stub_empty_22(void)
{
    return 0;
}

unsigned int stub_empty_23(void)
{
    return 0;
}

unsigned int stub_empty_24(void)
{
    return 0;
}

unsigned int stub_empty_25(void)
{
    return 0;
}

unsigned int stub_empty_26(void)
{
    return 0;
}

unsigned int stub_empty_27(void)
{
    return 0;
}

unsigned int stub_empty_28(void)
{
    return 0;
}

unsigned int stub_empty_29(void)
{
    return 0;
}

unsigned int stub_empty_30(void)
{
    return 0;
}

void stub_empty_31(void)
{
}

/* func_0026F810 is in 0026EA00-actuator.c (jump table and float pool). */


extern void FlushCache(int);
extern int gfx_wait_paths_idle(int, int);

/* Uploads a PIF image (header arg0, CLUT at +0x20 of 0x200 bytes when +0x14 is set, else
   0x400, then w * h pixels) to GS memory: the 16x16 CLUT to block cbp >> 8 and the pixels
   as PSMT8H to tbp >> 8 with a buffer width of w / 64 (at least 1), then writes the
   matching TEX0 plus 1, 0 to arg1 (rac1's LoadPifAsPSMT8H). */
typedef struct {
    long q[12];
} GsLoadImage26FC78 __attribute__((aligned(16)));

typedef struct {
    void *clut;
    void *image;
    int unk08[3];
    int clutSize;
    int imageSize;
    int unk1C[4];
    int tbp;
    int unk30[3];
    int tbw;
    int unk40[3];
    int tw;
    int th;
} PifTex26FC78;

typedef struct {
    char unk00[8];
    int w;
    int h;
    int unk10;
    int psm;
} PifHeader26FC78;

extern void mem_clear(void *, int, int);
extern int log2dim(int);
extern int func_00126288(GsLoadImage26FC78 *, short, short, short, short, short, short, short);
extern int sceGsExecLoadImage(GsLoadImage26FC78 *, void *);

void LoadPifAsPSMT8H(char *pifData, unsigned long long *out, int tbp, int cbp)
{
    PifTex26FC78 d;
    GsLoadImage26FC78 li;
    PifHeader26FC78 *pif = (PifHeader26FC78 *)pifData;
    int clutBlock;

    mem_clear(&d, 0, sizeof(d));
    d.clut = (char *)pif + 0x20;
    if (pif->psm == 0) {
        d.clutSize = 0x400;
    } else {
        d.clutSize = 0x200;
    }
    clutBlock = cbp >> 8;
    d.tw = log2dim(pif->w);
    d.th = log2dim(pif->h);
    d.image = (char *)pif + (d.clutSize + 0x20);
    d.imageSize = pif->w * pif->h;
    func_00126288(&li, clutBlock, 1, pif->psm, 0, 0, 16, 16);
    FlushCache(0);
    sceGsExecLoadImage(&li, d.clut);
    gfx_wait_paths_idle(0, 0);
    d.tbw = pif->w >> 6;
    if (d.tbw <= 0) {
        d.tbw = 1;
    }
    d.tbp = tbp >> 8;
    func_00126288(&li, d.tbp, d.tbw, 0x1B, 0, 0, pif->w, pif->h);
    FlushCache(0);
    sceGsExecLoadImage(&li, d.image);
    gfx_wait_paths_idle(0, 0);
    /* The TEX0 layout, with no zero fields. Retail's groups are this flat chain's without
       fold's flattening of four or more operands of one type, which the changes of
       signedness keep it from doing. */
    out[0] = (unsigned long)((long)((unsigned long)d.tbp | ((unsigned long)d.tbw << 14)
           | ((unsigned long)0x1B << 20) | ((unsigned long)d.tw << 26))
           | ((long)d.th << 30) | ((long)1 << 34) | ((long)clutBlock << 37))
           | ((unsigned long)pif->psm << 51) | ((unsigned long)4 << 61);
    out[1] = 1;
    out[2] = 0;
}

typedef struct { char pad[0x32C]; int base; int offset; int count; } Table26FE48;
extern Table26FE48 g_copy_setup_data;
extern char g_setup_entry_buffer[];
extern int g_pif_vram_address __attribute__((sda));
extern unsigned long long g_disc_table_pif_word __attribute__((sda));
extern int load_read_disc_with_pause(char *, int, int);
extern void LoadPifAsPSMT8H(char *, unsigned long long *, int, int);

/* Loads the PIF image from the disc table and saves its texture setting for later use. */
void tex_load_pif_from_disc_table(void)
{
    unsigned long long local[4];
    char *data = g_setup_entry_buffer;
    load_read_disc_with_pause(data, g_copy_setup_data.offset + g_copy_setup_data.base, g_copy_setup_data.count);
    LoadPifAsPSMT8H(data, local, g_pif_vram_address, 0x3FFC00);
    *(volatile unsigned long long *)&g_disc_table_pif_word = local[0];
}

/* Empty replacement for printf. */
void STUB_printf(const char *format,...) {
}


typedef struct {
    u8 pad[0x3D0];
    float f3D0;
    float f3D4;
    float f3D8;
    float f3DC;
    float f3E0;
    float f3E4;
    u8 mode;
    u8 active;
    short s3EA;
    float f3EC;
    float f3F0;
} F270018Aim;

extern F270018Aim g_active_camera;
extern float g_fov_tangent[];
extern float math_step_spring_damper_stored(char *, float, float, float, float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_cosine_blend(float, float, float);
extern float IntToFloat(int);
extern int FastDecTimer(void *);
extern void UpdateViewContext(void);

/* Updates the camera field of view change each frame and recomputes the zoom value. */
void cam_update_fov_transition(void) {
    float half;
    float t;

    if (g_active_camera.active == 1) {
        switch (g_active_camera.mode) {
        case 0:
            g_active_camera.f3D8 = g_active_camera.f3D4;
            g_active_camera.active = 0;
            break;
        case 3:
            g_active_camera.f3D8 = math_step_spring_damper_stored((char *)&g_active_camera.f3D0, g_active_camera.f3D8, g_active_camera.f3D4, g_active_camera.f3DC, g_active_camera.f3E0, g_active_camera.f3E4);
            if (math_fabs(g_active_camera.f3D0) < 0.0001f)
                g_active_camera.active = 0;
            break;
        case 1:
            if (FastDecTimer(&g_active_camera.s3EA))
                g_active_camera.active = 0;
            t = IntToFloat(g_active_camera.s3EA) * g_active_camera.f3EC;
            g_active_camera.f3D8 = g_active_camera.f3D4 + (g_active_camera.f3F0 - g_active_camera.f3D4) * t;
            break;
        case 2:
            if (FastDecTimer(&g_active_camera.s3EA))
                g_active_camera.active = 0;
            g_active_camera.f3D8 = math_cosine_blend(g_active_camera.f3D4, g_active_camera.f3F0, IntToFloat(g_active_camera.s3EA) * g_active_camera.f3EC);
            break;
        }
        half = g_active_camera.f3D8 * 0.5f;
        g_fov_tangent[0] = math_fast_sin_or_cos_b(half) / math_fast_sin_or_cos_a(half);
        UpdateViewContext();
    }
}


extern void mem_fast_helper_c(void *, void *, int);
extern char *g_camera_state_ptr;
extern char g_camera_working_data[];
extern char g_camera_work_buffer[];

/* Copies the current camera data into the working copy and links the second block to it. */
void cam_copy_working_data(void)
{
    mem_fast_helper_c(g_camera_working_data, g_camera_state_ptr, 0xA0);
    mem_fast_helper_c(g_camera_work_buffer, g_camera_work_buffer - 0x500, 0x280);
    *(char **)(g_camera_working_data + 0x70) = g_camera_work_buffer;
}

/* shared native body of family 34e74db3063e7a24 */
/* Calls every function waiting in the delayed call list, then empties the list. */
void script_run_delayed_call_list(void)
{
    int i;

    for (i = 0; i < g_delayed_call_count; i++) {
        g_delayed_call_list[i]();
    }

    g_delayed_call_count = 0;
}

extern char g_camera_records[];

/* Finds the record whose halfword at 0x86 equals the argument, in the table of
   0xA0-byte records that starts at 0x1B5750, and returns it; returns 0 once
   the table is exhausted.  The end of the table is held in an int so that the
   comparison is the signed one the retail does (slt, not sltu). */
char *moby_find_record_by_handle_id(int recordId)
{
    char *record = g_camera_records;
    int limit = (int)record + 0x1E00;

    for (;;) {
        if (*(short *)(record + 0x86) != recordId) {
            record += 0xA0;
            if ((int)record >= limit) {
                return 0;
            }
        } else {
            return record;
        }
    }
}

/* Integrates one float field with a spring-damper step, clamps it to a symmetric limit, then lets a helper raise or lower it, returning a bias plus the field. */
float math_step_spring_damper_clamped(float *value, float current, float target, float spring, float damping, float limit)
{
    float diff = target - current;
    float newValue = *value;
    float maxStep;

    newValue += spring * diff - damping * newValue;
    *value = newValue;
    if (limit != 0.0f) {
        if (newValue > limit) *value = limit;
        else if (newValue < -limit) *value = -limit;
    }
    maxStep = math_fabs(diff);
    if (maxStep < *value) {
        *value = math_fabs(diff);
    } else {
        float negStep = -math_fabs(diff);
        if (*value < negStep) {
            *value = -math_fabs(diff);
        }
    }
    return current + *value;
}

/* Advances a stored float by a scaled helper result, then clamps it against a positive limit, then clamps it again with a second helper and finally rescales it through a third helper. */
float math_step_spring_damper_stored(char *obj, float current, float target, float spring, float damping, float limit)
{
    float diff;
    float newValue;
    float change;
    float negLimit;

    diff = func_00283BE0_3(target, current);
    newValue = *(float *)obj;
    change = spring * diff - damping * newValue;
    newValue = newValue + change;
    *(float *)obj = newValue;

    if (limit != 0.0f) {
        if (newValue > limit) {
            *(float *)obj = limit;
        } else {
            negLimit = -limit;
            if (newValue < negLimit)
                *(float *)obj = negLimit;
        }
    }

    if (func_00282C48_5(diff) < *(float *)obj) {
        *(float *)obj = func_00282C48_5(diff);
    } else if (*(float *)obj < -func_00282C48_5(diff)) {
        *(float *)obj = -func_00282C48_5(diff);
    }

    return FastAddRotations(current, *(float *)obj);
}

/* sets the referenced object halfword at 0x7e and clears its byte at 0x7d */
/* Marks the current object as hidden by setting one flag and clearing another. */
void moby_clear_visible_flags(void) {
 *(u16 *)(g_hero_object_ref.object+0x7e)=1;
 g_hero_object_ref.object[0x7d]=0;
}

extern char g_camera_follow_state[];
extern void *moby_place_fixed_id_object(void *);
extern void moby_mark_spawned(void *);

/* Starts or stops an effect on an object depending on whether a value in the object is zero. */
void moby_toggle_effect(char *p)
{
    char *base = g_camera_follow_state;
    if (*(short *)(p + 0x86) == 0) {
        if (*(void **)(base + 0xC4) == 0)
            *(void **)(base + 0xC4) = moby_place_fixed_id_object(base - 0x60);
    } else {
        if (*(void **)(base + 0xC4) != 0) {
            moby_mark_spawned(*(void **)(base + 0xC4));
            *(void **)(base + 0xC4) = 0;
        }
    }
}

typedef void (*ObjectDispatch)(void *);
typedef struct { ObjectDispatch entries[5]; } ObjectDispatchRecord;
extern ObjectDispatchRecord g_object_dispatch_table[];

/* Calls the second handler for an object, based on its type. */
void moby_call_handler_second(char *object) {
    ObjectDispatch callback = g_object_dispatch_table[*(short *)(object + 0x8C)].entries[2];
    if (callback != 0)
        callback(object);
}

/* func_00270598 is in 00270598.c. */

/* func_00270838 is in 00270838-g8.c. */

/* Calls the fourth handler for an object, based on its type. */
void moby_call_handler_fourth(char *object) {
    ObjectDispatch callback = g_object_dispatch_table[*(short *)(object + 0x8C)].entries[4];
    if (callback != 0)
        callback(object);
}


extern void FastVecSub(float *dst, float *a, float *b);
extern float FastVecDot(float *a, float *b);
extern float FastVecLength(float *a);
extern void vec_scale_to_length(float *dst, float *a, float len);
extern float math_fast_angle_helper(float x);
extern void math_apply_axis_rotation_to_quat(float *dst, float *vec, float *axis, float angle);

/* The angles of a target seen from a camera: the difference of the two points is
   split along the axis and across it, the yaw of the first direction around the
   axis and the pitch of the difference after it, with the length of the
   difference beside them. A zero length becomes 0.0001 before the arcsine. */
void cam_compute_aim_angles(float *out, float *p0, float *p1, float *dir0, float *dir1, float *axis)
{
    float diff[4];
    float proj[4];
    float perp[4];
    float unit[4];
    float rotated[4];
    float alongAxis, dirDot, sideDot, rotDot, axisDot;
    float lenPerp, lenDiff;
    float angle1, angle2;
    float yaw, pitch;

    FastVecSub(diff, p0, p1);
    alongAxis = FastVecDot(diff, axis);
    vec_scale_to_length(proj, axis, alongAxis);
    FastVecSub(perp, diff, proj);

    dirDot = FastVecDot(dir0, perp);
    lenPerp = FastVecLength(perp);
    if (lenPerp == 0.0f) {
        lenPerp = 0.0001f;
    }
    angle1 = math_fast_angle_helper(dirDot / lenPerp);
    yaw = 1.57079637f - angle1;

    vec_scale_to_length(unit, perp, 1.0f);
    sideDot = FastVecDot(dir1, unit);
    if (sideDot < 0.0f) {
        yaw = -yaw;
    }
    out[0] = yaw;

    math_apply_axis_rotation_to_quat(rotated, dir0, axis, yaw);
    rotDot = FastVecDot(rotated, diff);
    lenDiff = FastVecLength(diff);
    if (lenDiff == 0.0f) {
        lenDiff = 0.0001f;
    }
    angle2 = math_fast_angle_helper(rotDot / lenDiff);
    pitch = -(1.57079637f - angle2);

    vec_scale_to_length(unit, diff, 1.0f);
    axisDot = FastVecDot(axis, unit);
    if (axisDot < 0.0f) {
        pitch = 1.57079637f - angle2;
    }
    out[1] = pitch;

    out[2] = FastVecLength(diff);
}

/* func_00270D50 is defined separately in 00270D50.c. */

/* func_00270E30 uses the quadword-copy profile in 0026EA00-qcopy.c. */

/* func_00270EA8 uses the quadword-copy profile in 0026EA00-qcopy.c. */

/* func_00270EE0 is in 00270EE0-qcopy.c. */

/* func_002712D8 is in 002712D8.c. */

/* func_002718B8 uses the quadword-copy profile in 0026EA00-qcopy.c. */

/* func_00271958 is in 00271958-g8.c. */

/* func_00271B90 is in 00271B90.c. */

/* func_00271FD8 is in 00271FD8-g8.c. */


/* Advances the shared scalar towards the stored target and updates its timer. */
typedef struct {
    char prefix[0x268];
    float step;
    float target;
    int timer;
    float step2;
    float rate2;
    float target2;
    int timer2;
} ScalarTransitionView;
extern ScalarTransitionView g_scalar_transition_state;
extern float g_hero_scalar_transition_value __attribute__((sda));
extern float ApproachValue(float *, float, float);
extern int math_fast_float_d(void *);

void cam_update_scalar_transition(void)
{
    ScalarTransitionView *state = &g_scalar_transition_state;

    if (state->step != 0.0f) {
        ApproachValue(&g_hero_scalar_transition_value,
                     state->target, state->step);
        if (g_hero_scalar_transition_value == state->target) {
            if (math_fast_float_d(&state->timer) == 1)
                state->target = 0.0f;
        }
        if (g_scalar_transition_state.target <= 0.0f && g_hero_scalar_transition_value <= 0.0f)
            g_scalar_transition_state.step = 0.0f;
    }
}

/* Advances the second shared scalar towards its stored target and updates its timer. */
extern float g_hero_second_scalar_transition_value __attribute__((sda));

void cam_update_second_scalar_transition(void)
{
    if (g_scalar_transition_state.step2 != 0.0f) {
        if (g_scalar_transition_state.target2 != 0.0f)
            ApproachValue(&g_hero_second_scalar_transition_value, g_scalar_transition_state.target2, g_scalar_transition_state.step2);
        else
            ApproachValue(&g_hero_second_scalar_transition_value, g_scalar_transition_state.target2, g_scalar_transition_state.rate2);
        if (g_hero_second_scalar_transition_value == g_scalar_transition_state.target2) {
            if (math_fast_float_d(&g_scalar_transition_state.timer2) == 1)
                g_scalar_transition_state.target2 = 0.0f;
        }
        if (g_scalar_transition_state.target2 <= 0.0f && g_hero_second_scalar_transition_value <= 0.0f)
            g_scalar_transition_state.step2 = 0.0f;
    }
}

/* func_00272CB0 is in 0026EA00-target.c (-g for its nop pair before div.s). */

/* Fills a three-float local through two setup calls, stores a two-argument float helper result into a field, then stores a second helper result into two more fields and returns zero. */
int cam_compute_direction_angles(float *out)
{
    float local[3];
    float angle;

    func_00282CF0_9(local);
    out[1] = func_00283248_7(func_00282E20_4(local), local[2]);

    angle = func_00283248_7(local[0], local[1]);
    func_00283BE0_5(angle, out[0]);
    out[0] = angle;

    out[2] = func_00282DF0_3(local);

    return 0;
}

/* Draw sixteen lens-flare elements with distance and screen-edge fades.
 * Corresponds to RAC1 draw_lens_flare, src/game/effects.c (GPL-3.0). */

void DrawLensFlare(void)
{
    MarkerVector projected;
    float centre[2], delta[2], scaled[2], point[2];
    float distance;
    int i;

    if (g_marker_state.active != 1 || (g_marker_state.target[0x20] & 0x80)) {
        g_marker_state.active = 0;
        return;
    }
    if (g_marker_state.timer <= 0.0f) return;
    distance = fast_vec_dist(&g_camera_eye_state, (MarkerVector *)(g_marker_state.target + 0x10));
    centre[0] = IntToFloat(g_reticle_screen_params[0]);
    centre[1] = IntToFloat(g_reticle_screen_params[1]);
    gfx_project_world_point_to_screen(&projected, (MarkerVector *)(g_marker_state.target + 0x10));
    projected.x = (projected.x - IntToFloat(g_reticle_screen_params[2])) * 0.0625f;
    projected.y = (projected.y - IntToFloat(g_reticle_screen_params[3])) * 0.0625f;
    delta[0] = centre[0] - projected.x;
    delta[1] = centre[1] - projected.y;
    for (i = 0; i < 16; ++i) {
        long texture = GetEffectTextureDescriptor(g_marker_state.texture[i] + 6);
        int width = i ? 32 : 64;
        int size, x, y;
        float fade = distance - 5.0f;
        float fade_x, fade_y, radius;
        unsigned int colour;
        scaled[0] = delta[0] * g_marker_state.interpolation[i];
        scaled[1] = delta[1] * g_marker_state.interpolation[i];
        point[0] = centre[0] + scaled[0];
        point[1] = centre[1] + scaled[1];
        if (fade > 1.0f) fade = 1.0f;
        else if (fade < 0.0f) fade = 0.0f;
        fade_x = math_fabs(delta[0]) / centre[0] * -5.0f + 5.5f;
        if (fade_x > 1.0f) fade_x = 1.0f;
        else if (fade_x < 0.0f) fade_x = 0.0f;
        fade_y = math_fabs(delta[1]) / centre[1] * -5.0f + 5.5f;
        if (fade_y > 1.0f) fade_y = 1.0f;
        else if (fade_y < 0.0f) fade_y = 0.0f;
        fade *= fade_x * fade_y;
        colour = (FloatToInt(fade * (float)g_marker_state.alpha[i]) << 24) |
                 (g_marker_state.colour[i] & 0xFFFFFF);
        size = FloatToInt((float)width * g_marker_state.scale[i]);
        radius = (float)(size >> 1);
        x = FloatToInt(point[0] - radius);
        y = FloatToInt(point[1] - radius);
        DrawTexturedQuad(x, y, size, size, 0, 0, width, width, (int)colour, texture);
    }
    g_marker_state.timer = 0.0f;
}








/* Blends the fog preset between the two colours and depth ranges of the camera environment
   region the position falls in (rac1's camera_switch_and_update twin). */
typedef struct {
    u8 pad0[0x50];
    int flags;
    int negative_color;
    int positive_color;
    float negative_depth_start;
    float negative_value_start;
    float negative_depth_end;
    float negative_value_end;
    float positive_depth_start;
    float positive_value_start;
    float positive_depth_end;
    float positive_value_end;
    u8 pad7C[4];
} CameraEnvironmentRegion;
typedef struct {
    u8 r, g, b, pad3;
    float f[4];
} FogPresetView;
extern CameraEnvironmentRegion g_camera_env_regions[];
#ifndef MACRO_ADDR
#define MACRO_ADDR __attribute__((section(".sdata")))
#endif
extern FogPresetView g_fog_color MACRO_ADDR;
extern int func_002A6640(void *, float *, int *);
extern int FloatToInt(float);

/* Arithmetic follows RAC1's update_camera_environment_from_regions,
   src/game/effects.c (Lombyte/OpenRAC, GPL-3.0). */
/* Mixes the fog colour and distances from the camera region the position is in. */
void gfx_blend_fog_from_cam_region(void *position)
{
    float blend;
    int region_index;
    CameraEnvironmentRegion *region;
    unsigned int positive_weight;
    unsigned int negative_weight;
    int negative_color;
    int positive_color;
    float inverse_blend;
    unsigned int red, green;
    unsigned int positive_red, negative_red, positive_green, negative_green, positive_blue, negative_blue;

    if (func_002A6640(position, &blend, &region_index) == 0)
        return;
    region = &g_camera_env_regions[region_index];
    if (!(region->flags & 2))
        return;
    positive_weight = FloatToInt(blend * 255.0f);
    negative_weight = 255 - positive_weight;
    inverse_blend = 1.0f - blend;
    positive_color = region->positive_color;
    negative_color = region->negative_color;
    positive_red = (positive_color & 0xFF) * positive_weight;
    positive_green = ((positive_color >> 8) & 0xFF) * positive_weight;
    positive_blue = (positive_color >> 16) & 0xFF;
    negative_red = (negative_color & 0xFF) * negative_weight;
    negative_green = ((negative_color >> 8) & 0xFF) * negative_weight;
    negative_blue = (negative_color >> 16) & 0xFF;
    red = (int)(positive_red + negative_red) >> 8;
    green = (int)(positive_green + negative_green) >> 8;
    g_fog_color.b = (int)(positive_blue * positive_weight + negative_blue * negative_weight) >> 8;
    g_fog_color.r = red;
    g_fog_color.g = green;
    g_fog_color.f[0] = (region->positive_depth_start * blend + region->negative_depth_start * inverse_blend) * 1024.0f;
    g_fog_color.f[1] = (region->positive_depth_end * blend + region->negative_depth_end * inverse_blend) * 1024.0f;
    g_fog_color.f[2] = 255.0f - (region->positive_value_start * blend + region->negative_value_start * inverse_blend) * 255.0f;
    g_fog_color.f[3] = 255.0f - (region->positive_value_end * blend + region->negative_value_end * inverse_blend) * 255.0f;
}

/* func_00273730 is in 00273730.c. */

/* func_00273978 is in 00273978.c. */


/* Updates a moby that moves toward a target and starts a sound or effect when it hits something. */
int target_seeker_update(char *obj)
{
    float buf[4];
    float out[4];
    char *vars;
    char *scratch;
    unsigned char mode;
    int result;
    int effectHandle;
    int hitResult;

    vars = *(char **)(obj + 104);
    mode = *(unsigned char *)(vars + 92);
    if (mode >= 3)
        return 1;
    if (mode != 0)
        Fdb046c5d_FUN_002742E8(obj);
    else
        Fdb046c5d_FUN_00274128(obj);

    hitResult = Fdb046c5d_FUN_00274500(obj);
    if (hitResult == -1)
        return 0;

    scratch = Fdb046c5d_D_001BAFC0;
    effectHandle = -1;
    Fdb046c5d_FUN_00282F20(1.0f, scratch, scratch);
    Fdb046c5d_FUN_00282DD8(buf, scratch, vars);
    Fdb046c5d_FUN_00274A88(obj, vars + 16, buf);
    Fdb046c5d_FUN_002AFFD8(obj + 16, out, 1);
    result = Fdb046c5d_FUN_00274BA8(vars, scratch, out, *(float *)(vars + 56), *(float *)(vars + 60));
    if (result == 0) {
        if (*(unsigned char *)(vars + 94) != 255 && *(unsigned char *)(vars + 92) == 0)
            effectHandle = Fdb046c5d_FUN_002E5CF8(*(unsigned char *)(vars + 94), 0, obj);
        Fdb046c5d_FUN_00274768(obj, hitResult, out);
    } else {
        if (*(unsigned char *)(vars + 94) != 255)
            effectHandle = Fdb046c5d_FUN_002E5CF8(*(unsigned char *)(vars + 94), 0, obj);
    }
    if (effectHandle != -1)
        Fdb046c5d_FUN_002E5F00(effectHandle, vars + 32);
    return 0;
}

/* func_00273E98 is defined in 00273E98.c. */
