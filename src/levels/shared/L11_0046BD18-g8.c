#include "common.h"

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vector;

/* One bolt's row of the level's vertex table (640 bytes): the jittered points
 * along the path, then the same points displaced by the wave. */
typedef struct { Vector core[20]; Vector wave[20]; } BoltBuffer;

/* An entry of the level's path table: a point count, then the points. */
typedef struct { int count; int pad[3]; Vector points[1]; } Path;

/* The bolt's state record (object + 0x68). */
typedef struct {
    Vector start;   /* 0x00 */
    Vector end;     /* 0x10 */
    char pad20[12];
    int count;      /* 0x2C */
    int pad30;
    int path;       /* 0x34: index into the level's path table */
    int row;        /* 0x38: this bolt's row of the vertex table */
} BoltState;

extern int D_L11_001B25A0 __attribute__((sda));
extern Path *D_L11_001FF580[];
extern BoltBuffer D_L11_00264760[];
extern float D_L11_001B25A8 __attribute__((sda));
extern float D_L11_001B25C0 __attribute__((sda));
extern float D_L11_001B25C8 __attribute__((sda));
extern float D_L11_001B25D0 __attribute__((sda));
extern float D_L11_001B25D4 __attribute__((sda));
extern float D_L11_001B25D8 __attribute__((sda));
extern float D_L11_001B25DC __attribute__((sda));
extern float D_L11_001B25E0 __attribute__((sda));
extern float D_L11_001B25E4 __attribute__((sda));
extern float D_L11_001B25F8 __attribute__((sda));
extern float D_L11_001B25FC __attribute__((sda));
extern char D_L11_001A8F20[] __attribute__((sda));
extern float func_002A7940(void);
extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_002A78D8(float, float);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283248(float, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern int func_002761F8(void *, void *, int, void *, void *);

/* Rebuilds a lightning bolt along its path: each point gets a random jitter
 * (core), a copy of it is displaced by a travelling wave (wave), and every
 * second segment spawns a spark effect. */
void func_L11_0046BD18(char *object)
{
    Vector position;
    Vector direction;
    Vector delta;
    Vector step;
    Vector perpendicular;
    char effect[48] __attribute__((aligned(16)));
    BoltState *state;
    Path *path;
    Vector *wave, *prev;
    float phase, angle, amplitude, horizontalAmplitude, nx, nz, ny, f;
    float scale = D_L11_001B25A8 / (float)D_L11_001B25A0;
    int i;

    state = *(BoltState **)(object + 0x68);
    D_L11_001B25C0 = func_002A7940();
    D_L11_001B25C8 = func_002A7940();
    D_L11_001B25DC = FastAddRotations(D_L11_001B25DC, D_L11_001B25E0);
    func_00282C88(&position);
    state->count = D_L11_001B25A0;
    FastVecSub(&direction, &state->end, &state->start);
    vec_scale_to_length(&direction, &direction, 1.0f);
    FastVecScale(&step, &direction, scale);
    path = D_L11_001FF580[state->path];
    qcopy_nc(&D_L11_00264760[state->row].core[0], &path->points[0]);
    qcopy_nc(&D_L11_00264760[state->row].wave[0], &path->points[0]);
    for (i = 1; i < D_L11_001B25A0; i++) {
        nz = func_002A78D8(D_L11_001B25F8, D_L11_001B25FC);
        nx = func_002A78D8(D_L11_001B25F8, D_L11_001B25FC);
        ny = func_002A78D8(D_L11_001B25F8, D_L11_001B25FC);
        qcopy_nc(&D_L11_00264760[state->row].core[i], &path->points[i]);
        f = (float)i;
        D_L11_00264760[state->row].core[i].z += nz;
        D_L11_00264760[state->row].core[i].x += nx;
        D_L11_00264760[state->row].core[i].y += ny;
        /* Previous point: the row's points from index -1. */
        prev = &D_L11_00264760[state->row].core[-1];
        FastVecSub(&delta, &D_L11_00264760[state->row].core[i], &prev[i]);
        phase = func_002ABB18(D_L11_001B25C8 + f * D_L11_001B25D0);
        angle = func_002ABB18(D_L11_001B25DC + f * D_L11_001B25E4);
        amplitude = D_L11_001B25D4 * func_00283198(angle);
        /* Column i of the wave points, then this bolt's row. */
        qcopy_nc(&D_L11_00264760[0].wave[i] + state->row * 40,
                 &D_L11_00264760[state->row].core[i]);
        nz = amplitude * func_00283198(phase) + func_002A78D8(0.0f, 0.1f);
        D_L11_00264760[state->row].wave[i].z += nz;
        angle = FastAddRotations(func_00283248(delta.x, delta.y), 1.5707964897155762f);
        horizontalAmplitude = D_L11_001B25D8 * func_00283180(phase);
        perpendicular.x = func_00283180(angle) * horizontalAmplitude;
        perpendicular.y = func_00283198(angle) * horizontalAmplitude;
        perpendicular.z = 0.0f;
        wave = D_L11_00264760[state->row].wave;
        FastVecAdd(&wave[i], &wave[i], &perpendicular);
        if (i > 1 && (i == D_L11_001B25A0 - 1 || !(i & 1))) {
            make_hit_descriptor(effect, object, 1, 10.0f, D_L11_001A8F20);
            *(unsigned short *)(effect + 26) = *(unsigned short *)(object + 0xaa);
            CollLine(&path->points[i - 2], &path->points[i], 16, object, effect);
        }
    }
}
