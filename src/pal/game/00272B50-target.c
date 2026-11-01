#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad[0x1450];
    char *requested;
    char gap[0x2C];
    char *current;
    float fade;
    float angle;
} TargetReticleState;
extern TargetReticleState D_00189E20;
extern char D_001B5340[];
extern int D_001A7348[] __attribute__((sda));
extern float D_001A85C0 SDATA(D_001A85C0);
extern float D_001A85C4 SDATA(D_001A85C4);
extern float D_001A85C8 SDATA(D_001A85C8);
extern float D_001A85CC SDATA(D_001A85CC);
extern unsigned int D_001A85D0[] SDATA(D_001A85D0);
extern unsigned int D_001A85E0[] SDATA(D_001A85E0);
extern float D_001A85F0[] SDATA(D_001A85F0);
extern float D_001A85FC SDATA(D_001A85FC);
extern float D_001A8600 SDATA(D_001A8600);
extern int D_001A8604 SDATA(D_001A8604);
extern unsigned int D_001A8608[] SDATA(D_001A8608);
extern int D_001A8618 SDATA(D_001A8618);
extern int D_001A861C SDATA(D_001A861C);
extern unsigned int D_001A8620 SDATA(D_001A8620);
extern unsigned int D_001A8624 SDATA(D_001A8624);
extern float D_001A8628 SDATA(D_001A8628);
extern float D_001A862C SDATA(D_001A862C);
extern float func_002AA2E8(float *, float, float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern char *func_002AB1F0(char *);
extern void func_00282F20(float *, void *, float);
extern void func_00282CC0(float *, float *, void *);
extern void func_00279BD8(float *, float *);
extern float func_00283CE0(int);
extern float func_00282E48(void *, void *);
extern float func_00283248(float, float);
extern long func_0027C878(int);
extern int func_00283D38(unsigned int, unsigned int, float);
extern int func_00283CF0(float);
extern void func_0027E4A8(float, float, float, float, float, int, int, long, int, int,
                          unsigned char, unsigned char, float, float);
extern void func_0027EE58(int, int, int, int, unsigned int *, unsigned int *, int, int, float, float);

/* Fades the reticle in on the requested target and out when the target changes, spins it, then
   draws it at the target's projected position: three layers of four rotated quads, with a
   health arc under them when the target's info gives a maximum health. */
void func_PAL_00272B50(void)
{
    float screen[4];
    float offset[4];
    float position[4];
    unsigned int colors[4];
    unsigned int uv[4];
    char *obj;
    char *info;
    float *pos;
    float health;
    float maxHealth;
    float radius;
    float scale;
    float angle;
    float size;
    float bar;
    float edge;
    int i;
    int color;
    int width;
    int height;
    int width2;
    int height2;
    long texture;
    long x;
    long y;

    if (!D_00189E20.requested && D_00189E20.fade == 0.0f) {
        return;
    }
    if (D_00189E20.requested != D_00189E20.current) {
        func_002AA2E8(&D_00189E20.fade, 0.0f, D_001A85CC * (0.020000001f));
        if (D_00189E20.fade <= 0.0f) {
            D_00189E20.current = D_00189E20.requested;
        }
    } else if (D_00189E20.requested && D_00189E20.fade < 1.0f) {
        func_002AA2E8(&D_00189E20.fade, 1.0f, D_001A85CC * (0.020000001f));
        D_00189E20.angle = func_00283B98(D_00189E20.angle, D_001A8600 * 0.0003490659f);
    }
    D_00189E20.angle = func_00283B98(D_00189E20.angle, D_001A8600 * 0.0003490659f);
    obj = D_00189E20.current;
    if (!obj || D_00189E20.fade == 0.0f) {
        return;
    }
    health = 0.0f;
    maxHealth = health;
    info = func_002AB1F0(obj);
    if (info) {
        func_00282F20(position, obj + 0xE0, *(float *)(info + 0x10));
        func_00282CC0(position, position, obj + 0x10);
        maxHealth = *(short *)(info + 4);
        health = *(float *)info;
        pos = position;
    } else {
        qcopy(position, obj + 0x10);
        pos = position;
    }
    func_00279BD8(screen, pos);
    offset[0] = (screen[0] - func_00283CE0(D_001A7348[2])) * 0.0625f;
    offset[1] = (screen[1] - func_00283CE0(D_001A7348[3])) * 0.0625f;
    radius = *(float *)(info + 0x10);
    if (radius > 2.0f) {
        radius = 2.0f;
    }
    scale = func_00283248(func_00282E48(D_001B5340, obj + 0x10), radius) * D_001A85C0;
    if (scale > D_001A85C4) {
        scale = D_001A85C4;
    } else if (scale < D_001A85C8) {
        scale = D_001A85C8;
    }
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            angle = D_00189E20.angle;
            break;
        case 1:
            angle = -D_00189E20.angle;
            break;
        case 2:
        default:
            angle = D_001A85FC * 0.01745329424738884f;
            break;
        }
        texture = func_0027C878(i + 0x33);
        color = func_00283D38(D_001A85E0[i], D_001A85D0[i], D_00189E20.fade);
        size = ((D_001A85F0[i] - 1.0f) * (1.0f - D_00189E20.fade) + 1.0f) * scale;
        func_0027E4A8(offset[0], offset[1], size, size, angle, 64, 64, texture, 0xFFFFF3, color,
                      0, 0, 0.0f, 0.0f);
        func_0027E4A8(offset[0], offset[1], size, size, func_00283B98(angle, 1.57079637f), 64, 64,
                      texture, 0xFFFFF3, color, 0, 0, 0.0f, 0.0f);
        func_0027E4A8(offset[0], offset[1], size, size, func_00283B98(angle, 3.14159274f), 64, 64,
                      texture, 0xFFFFF3, color, 0, 0, 0.0f, 0.0f);
        func_0027E4A8(offset[0], offset[1], size, size, func_00283BE0(angle, 1.57079637f), 64, 64,
                      texture, 0xFFFFF3, color, 0, 0, 0.0f, 0.0f);
    }
    if (maxHealth != 0.0f) {
        uv[0] = D_001A8608[0];
        uv[1] = D_001A8608[1];
        uv[2] = D_001A8608[2];
        uv[3] = D_001A8608[3];
        colors[0] = colors[1] = colors[2] = colors[3] =
            func_00283D38(D_001A8620 & 0xFFFFFF, D_001A8620, D_00189E20.fade);
        x = func_00283CF0(screen[0]);
        y = func_00283CF0(screen[1]);
        bar = D_001A862C * func_00283248(D_001A8628, maxHealth);
        edge = -bar;
        width = func_00283CF0(scale * (float)D_001A8618);
        height = func_00283CF0(scale * (float)D_001A861C);
        func_0027EE58(x, y, width, height, colors, uv, D_001A8604, 16, bar, edge);
        colors[0] = colors[1] = colors[2] = colors[3] =
            func_00283D38(D_001A8624 & 0xFFFFFF, D_001A8624, D_00189E20.fade);
        edge = bar - (bar + bar) * (health / maxHealth);
        width2 = func_00283CF0(scale * (float)D_001A8618);
        height2 = func_00283CF0(scale * (float)D_001A861C);
        func_0027EE58(x, y, width2, height2, colors, uv, D_001A8604, 16, bar, edge);
    }
}
