#include "common.h"

typedef struct { float x, y, z, w; } QuadPoint;
extern void func_0027B9C0(int, int, float);
extern void func_0027BA48(void);
extern void func_002FC560(unsigned int, unsigned long);
/* Snapshot the view, render the selected object into a texture, then draw
   its four-corner world-space quad after restoring the view. */
typedef struct {
    QuadPoint vertices[4];
    unsigned int colors[4];
    float uv[4][2];
    unsigned long state[4];
} CaptureQuad;
typedef struct { char pad[0x34]; unsigned short flags; } CaptureMoby;
typedef struct { QuadPoint position; float angles[4]; QuadPoint vertices[4]; float width, height; CaptureMoby *moby; } CaptureObject;
typedef struct { char pad[0x50]; CaptureObject *capture; } CaptureState;
extern CaptureState D_001B8840;
typedef struct {
    char reserved0[0x140];
    QuadPoint position;
    char reserved150[0x370 - 0x150];
    QuadPoint matrix[4];
} CaptureCamera;
extern CaptureCamera D_001B5200;
typedef struct { char pad[0xB0]; float scale; } CaptureView;
extern CaptureView D_001B9040;
extern char D_001C2AC0[];
extern QuadPoint D_001A8820 __attribute__((sda));
extern QuadPoint D_001A8830 __attribute__((sda));
extern QuadPoint D_001A8840 __attribute__((sda));
extern QuadPoint D_001A8850 __attribute__((sda));
extern float D_001A87F8[4] __attribute__((sda));
extern float D_001A8808[4] __attribute__((sda));
extern unsigned long D_001A7470[] __attribute__((sda));
extern int D_001B1B58[] __attribute__((sda));
extern void func_002A0250(void), func_002A01C8(void), func_002A01F0(void);
extern void func_002A0300(void *, int);
extern void func_00282B50(void *, void *, int);
extern void func_00129178(void *);
extern void func_001292C0(void *, void *, float);
extern void func_00129368(void *, void *, float);
extern void func_00129218(void *, void *, float);
extern void func_00279D18(void);
extern void func_002A0468(void *, int, int, int, int);
extern void func_0027AB40(void), func_002FC748(void), func_002A0220(void), func_002A03C0(void);
extern int func_002A0380(void);
extern void func_00280B90(void *, int, int);

void func_0027BA68(void)
{
    CaptureObject *object = D_001B8840.capture;
    QuadPoint saved_matrix[4], saved_position, matrix[4];
    CaptureQuad quad;
    if (object) {
        CaptureMoby *moby = object->moby;
        QuadPoint *position = &object->position;
        char *view_matrix;
        char *view_position;
        float saved_scale;
        void *scene;
        int i;
        func_002A0250();
        func_002A01C8();
        func_002A01F0();
        scene = (void *)D_001B1B58[1];
        moby->flags |= 1;
        func_002A0300(scene, -1);
        moby->flags &= ~1;
        view_matrix = (char *)&D_001B5200 + 0x370;
        func_00282B50(saved_matrix, view_matrix, 0x40);
        do { view_position = view_matrix - 0x230; } while (0);
        qcopy(&saved_position, view_position);
        saved_scale = D_001B9040.scale;
        func_0027B9C0(8, 8, 1.0f);
        func_00129178(matrix);
        func_001292C0(matrix, matrix, object->angles[0]);
        func_00129368(matrix, matrix, object->angles[1]);
        func_00129218(matrix, matrix, object->angles[2]);
        func_00282B50(view_matrix, matrix, 0x40);
        qcopy(view_position, position);
        func_00279D18();
        func_002A0468(moby, 0x404040, 0xE, 0, 0);
        qcopy(D_001C2AC0, &D_001A8820);
        qcopy(D_001C2AC0 + 0x20, &D_001A8830);
        qcopy(D_001C2AC0 + 0x10, &D_001A8840);
        qcopy(D_001C2AC0 + 0x30, &D_001A8850);
        func_002A0300(moby, 1); func_0027BA48();
        D_001B9040.scale = saved_scale;
        func_0027AB40();
        func_00282B50(view_matrix, saved_matrix, 0x40);
        qcopy(view_position, &saved_position);
        func_00279D18();
        func_002FC560(0x42, 0x8000000044UL); func_002FC560(8, 5);
        func_002FC748(); func_002A0220(); func_002A0380();
        quad.state[1] = D_001A7470[0];
        quad.state[2] = 0xFF9000000260UL;
        quad.state[0] = 5;
        quad.state[3] = 0x8000000044UL;
        for (i = 0; i < 4; i++) {
            quad.colors[i] = 0x80808080;
            quad.uv[i][0] = object->width * D_001A87F8[i] + 0.5f;
            quad.uv[i][1] = object->height * D_001A8808[i] + 0.5f;
            qcopy(&quad.vertices[i], &object->vertices[i]);
        }
        func_00280B90(&quad, 0, 0);
    } else func_002A03C0();
}
