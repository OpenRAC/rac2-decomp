#include "common.h"
typedef int CameraQuad __attribute__((mode(TI)));
typedef union {
    CameraQuad q;
    float f[4];
} CameraVector;
typedef struct {
    CameraVector rows[3], pos;
    char pad40[0x24];
    float prevpos[3];
    char *buffer;
    int pad74;
    float duration;
    char pad7c;
    unsigned char handoff;
    short state;
    char pad80[4];
    short index, id;
    char pad88[4];
    short type, cut;
    char pad90[0x10];
} Camera;
typedef struct {
    char prefix[0x1d];
    unsigned char kind;
} CameraInfo;
typedef struct {
    char prefix[0x1c];
    CameraInfo *info;
} CameraDefinition;
typedef struct {
    char prefix[0x140];
    CameraVector pos;
    char pad150[0x40];
    Camera *current, *previous;
    char pad198[0xf8];
    short phase;
    unsigned char kind, nextkind;
    char pad294[0x14];
    float posrate;
    char pad2ac[8];
    float rotrate;
    char pad2b8[0x5c];
    int frames;
    char pad318[0xec];
    int timer;
} CameraSystem;
extern CameraSystem g_active_camera;
extern char D_001B79B0[];
extern CameraDefinition *D_001B1504 __attribute__((sda));
extern int FloatToInt(float);
extern void mem_fast_helper_c(void *, void *, int);
extern void moby_call_handler_second(char *);
extern void cam_copy_working_data(void);

/* Selects the new camera, configures its transition and swaps the state buffers. */
void cam_switch_active(char *camera)
{
    Camera *next = (Camera *)camera;
    Camera *prev;
    CameraInfo *info;
    int kind = 0;
    int state;
    CameraVector *pos;
    float *prevpos;
    info = D_001B1504[next->index].info;
    prev = g_active_camera.current;
    state = prev->state;
    if (info)
        kind = info->kind;
    if (state == 4) {
        next->cut = 1;
    } else if (state == 2 || kind == 1 || kind == 5) {
        if (kind == 1) {
            float duration = next->duration;
            g_active_camera.nextkind = 0;
            if (duration > 0.0f) {
                g_active_camera.rotrate = duration;
                g_active_camera.posrate = duration;
            } else {
                g_active_camera.rotrate = 0.018f;
                g_active_camera.posrate = 0.018f;
            }
        } else if (kind == 5) {
            float duration = next->duration;
            g_active_camera.nextkind = 2;
            if (duration > 0.0f)
                g_active_camera.frames = FloatToInt(duration);
            else
                g_active_camera.frames = 40;
        }
        if (g_active_camera.phase == 0)
            g_active_camera.phase = 1;
        else
            g_active_camera.phase = 2;
    } else if (state == 3 || state == 5 || kind == 3 || kind == 6) {
        qcopy(&next->pos, &prev->pos);
        qcopy(&next->rows[0], &prev->rows[0]);
        qcopy(&next->rows[1], &prev->rows[1]);
        qcopy(&next->rows[2], &prev->rows[2]);
        next->handoff = 2;
        if (prev->state == 5 || kind == 6) {
            float duration = next->duration;
            g_active_camera.nextkind = 0;
            if (duration > 0.0f) {
                g_active_camera.rotrate = duration;
                g_active_camera.posrate = duration;
            } else {
                g_active_camera.rotrate = 0.018f;
                g_active_camera.posrate = 0.018f;
            }
        }
    } else {
        next->cut = 1;
    }
    prev->state = 0;
    prev->handoff = 0;
    prev->cut = 0;
    g_active_camera.previous = prev;
    mem_fast_helper_c(D_001B79B0, D_001B79B0 - 0x280, 0x280);
    g_active_camera.previous->buffer = D_001B79B0;
    g_active_camera.current = next;
    next->buffer = D_001B79B0 - 0x280;
    prev = next;
    g_active_camera.timer = 0;
    moby_call_handler_second((char *)prev);
    cam_copy_working_data();
    pos = &prev->pos;
    qcopy(&g_active_camera.pos, pos);
    prevpos = prev->prevpos;
    prevpos[0] = prev->pos.f[0];
    prevpos[1] = pos->f[1];
    prevpos[2] = pos->f[2];
}
