/* func_US2_003002E0, the USA v2.00 copy of func_002FF450: the same C, where rename func_00288508 becomes func_US2_00288F30. */
#include "common.h"

/* The object preview's sequencer (func_US2_003002E0), in a unit of its own: it is
   built with -g, whose line label before each division keeps the two padding
   nops retail has in front of div.s, and its jump table is the unit's only
   .rodata. */

/* State of the object preview (PreviewState in 002FC8D0.c), seen whole. It is
   a small-data object: fields past the first halfword are offsets from it
   (two-word macros that never fill a delay slot), while the state halfword is
   a one-word access that the assembler turns into a $gp store in a delay
   slot. */
typedef struct {
    short state;              /* 0x00 */
    short frames;             /* 0x02 */
    float rate;               /* 0x04 */
    short s08;                /* 0x08 */
    char pad0A[0x0D - 0x0A];
    unsigned char b0D;        /* 0x0D */
    short s0E;                /* 0x0E */
    char pad10[0x30 - 0x10];
    char *object;             /* 0x30 */
    unsigned char phase;      /* 0x34 */
    unsigned char spin;       /* 0x35 */
    short alpha;              /* 0x36 */
} PreviewState;

/* The camera (PreviewCameraPrefix in 002FC8D0.c). */
typedef struct {
    char reserved000[0x140];
    float position[4];        /* 0x140 */
    float rotation[4];        /* 0x150 */
    char reserved160[0x370 - 0x160];
    float forward[4];         /* 0x370 */
} PreviewCamera;

/* The subtitle owner (SubtitleOwnerUpdate in 00289178.c). */
typedef struct {
    char pad00[0x6C];
    short id;
    char pad6E[4];
    short state;
} PreviewSubtitleOwner;

extern PreviewState g_object_preview_state __attribute__((sda));
extern PreviewCamera g_active_camera;
extern PreviewSubtitleOwner g_music_state;
extern int D_001AD7E4 SDATA(D_001AD7E4) __attribute__((sda));
extern int D_001AD7E8 SDATA(D_001AD7E8) __attribute__((sda));
extern int D_001AD7F8 SDATA(D_001AD7F8) __attribute__((sda));
extern int D_001AD7FC SDATA(D_001AD7FC) __attribute__((sda));
extern int D_001AD800 SDATA(D_001AD800) __attribute__((sda));
extern int D_001AD804 SDATA(D_001AD804) __attribute__((sda));
extern float D_001B90F0;
extern short D_0018A000;

extern int FastDecTimer(short *);
extern int snd_resume_music_stream(void);
extern void set_identity_rotation_rows(float *);
extern void UpdateViewContext(void);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void gfx_register_final_draw_callback(void (*)(void), int);
extern void shop_draw_preview_fade_overlay(void);
extern void shop_draw_preview_dim_overlay(void);
extern void shop_setup_preview_object(void);
extern void PlaceObjectBeforeCamera(char *);
/* Retail passes the object in $a0; the matched body does not read it. */
extern void EmitParticlesBeforeCamera(char *);
extern char *part_spawn_mode_effect_object(char *);
extern void menu_advance_chain_entry(int);
extern void func_US2_00288F30(int);
extern int moby_handle_request_slot_state(int);
extern int request_begin_slot(int, int, int, int, int);

/* Steps the object preview through its eight states: wait for the subtitle
   owner (at most 181 frames), set up the camera and the object, show it,
   fade, release it and hand control back. */
void func_US2_003002E0(void)
{
    char *object, *current;
    float angle, sine, tangent, zero;

    switch (g_object_preview_state.state) {
    case 0:
        if (FastDecTimer(&g_object_preview_state.frames)
            && !(D_001AD7E4 && (g_music_state.state != 3 || g_music_state.id >= 6000)
                 && D_001AD7E8++ < 181)) {
            snd_resume_music_stream();
            g_active_camera.position[0] = 25.0f;
            g_active_camera.position[2] = 900.0f;
            g_active_camera.position[1] = 25.0f;
            D_001AD7E4 = 0;
            D_001AD7E8 = 0;
            set_identity_rotation_rows(g_active_camera.forward);
            object = g_object_preview_state.object;
            zero = 0.0f;
            g_active_camera.rotation[2] = zero;
            g_active_camera.rotation[1] = zero;
            g_active_camera.rotation[0] = zero;
            g_object_preview_state.state = 1;
            g_object_preview_state.frames = D_001AD7FC;
            g_object_preview_state.s0E = 0;
            qcopy(object + 0xF0, g_active_camera.rotation);
            if (g_object_preview_state.spin)
                *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), -1.5707964897155762f);
            angle = 0.5621705651283264f;
            sine = math_fast_sin_or_cos_b(angle);
            tangent = sine / math_fast_sin_or_cos_a(angle);
            D_001B90F0 = tangent;
            UpdateViewContext();
            *(unsigned short *)(object + 0x34) &= ~0x41;
        } else {
            gfx_register_final_draw_callback(shop_draw_preview_fade_overlay, 0);
        }
        break;
    case 1:
        PlaceObjectBeforeCamera(g_object_preview_state.object);
        if (FastDecTimer(&g_object_preview_state.frames)) {
            g_object_preview_state.frames = D_001AD800;
            g_object_preview_state.rate = 1.0f / IntToFloat(g_object_preview_state.frames);
            g_object_preview_state.state = 2;
            g_object_preview_state.phase = 0;
        }
        break;
    case 2:
        current = g_object_preview_state.object;
        PlaceObjectBeforeCamera(current);
        EmitParticlesBeforeCamera(current);
        if (FastDecTimer(&g_object_preview_state.frames)) {
            g_object_preview_state.frames = 2;
            g_object_preview_state.state = 3;
            g_object_preview_state.alpha = 128;
            gfx_register_final_draw_callback(shop_draw_preview_dim_overlay, 0);
        }
        break;
    case 3:
        current = g_object_preview_state.object;
        gfx_register_final_draw_callback(shop_draw_preview_dim_overlay, 0);
        if (FastDecTimer(&g_object_preview_state.frames)) {
            g_object_preview_state.frames = 12;
            g_object_preview_state.state = 4;
            g_object_preview_state.object = part_spawn_mode_effect_object(current);
        }
        break;
    case 4:
        if (g_object_preview_state.object)
            PlaceObjectBeforeCamera(g_object_preview_state.object);
        gfx_register_final_draw_callback(shop_draw_preview_dim_overlay, 0);
        g_object_preview_state.alpha = FloatToInt(IntToFloat(g_object_preview_state.frames) * (1.0f / 12.0f) * 128.0f);
        if (FastDecTimer(&g_object_preview_state.frames)) {
            g_object_preview_state.state = 5;
            g_object_preview_state.frames = D_001AD804;
            g_object_preview_state.alpha = 0;
        }
        break;
    case 5:
        if (g_object_preview_state.object)
            PlaceObjectBeforeCamera(g_object_preview_state.object);
        if (FastDecTimer(&g_object_preview_state.frames)) {
            g_object_preview_state.frames = 3;
            g_object_preview_state.state = 6;
        }
        break;
    case 6:
        if (g_object_preview_state.object)
            PlaceObjectBeforeCamera(g_object_preview_state.object);
        gfx_register_final_draw_callback(shop_draw_preview_fade_overlay, 0);
        if (FastDecTimer(&g_object_preview_state.frames)) {
            g_object_preview_state.frames = 0;
            g_object_preview_state.rate = 1.0f / IntToFloat(D_001AD7F8);
            g_object_preview_state.b0D = g_object_preview_state.s0E = 1;
            D_0018A000 = D_001AD7F8 + 5;
            shop_setup_preview_object();
            g_object_preview_state.object = 0;
            menu_advance_chain_entry(g_object_preview_state.s08);
            func_US2_00288F30(g_object_preview_state.s08);
            if (g_object_preview_state.spin)
                moby_handle_request_slot_state(g_object_preview_state.s08);
            g_object_preview_state.state = 7;
        }
        break;
    case 7:
        if (g_object_preview_state.frames++ >= D_001AD7F8)
            request_begin_slot(0, 2, 0, 0, 0);
        else
            gfx_register_final_draw_callback(shop_draw_preview_fade_overlay, 0);
        break;
    }
}
