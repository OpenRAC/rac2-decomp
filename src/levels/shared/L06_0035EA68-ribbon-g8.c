/* Adapted from RAC1's render_data_processor_linked_effect in
   src/overlays/l10_orxon/platforms_doors_and_bombthrower.c (GPL-3.0). */
#include "common.h"
extern char *D_L06_001B281C;
extern char D_L06_001B9840[];
extern float func_00282E48(char *,char *);
extern void func_002833B8(void *,float);
extern void func_00283410(void *,void *);
extern void func_00283788(void *,void *,void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(int,int,float);
extern unsigned long func_0027C878(int);
extern void func_00282CC0(void *,void *,void *);
extern void func_00280B90(void *,void *,int);
extern int D_L06_001AF550 __attribute__((sda)),D_L06_001AF554 __attribute__((sda)),D_L06_001AF558 __attribute__((sda)),D_L06_001AF55C __attribute__((sda));
extern int D_L06_001AF570 __attribute__((sda)),D_L06_001AF574 __attribute__((sda));
extern float D_L06_001AF578[] SDATA(D_L06_001AF578);
extern float D_L06_001AF5A0[] SDATA(D_L06_001AF5A0);
extern float D_L06_001AF620 __attribute__((sda));
extern float D_L06_001AF57C[7] __attribute__((sda));
extern float D_L06_001AF71C;
extern int D_L06_001B31B0,D_L06_001B31B4;
typedef unsigned int Quad57 __attribute__((mode(TI)));
void func_L06_003E57E8(u8 *moby) {
    char *data = (*(char **)(moby + 0x68));
    char *base = *(char **)((*(int *)(data + 0xc) << 8) + (int)D_L06_001B281C + 0x68);
    char scratch[(unsigned int)*(int *)(data + 4) * 0x40];
    struct {
        struct {
            float xyz[4][4];
            unsigned int color[4];
            float uv[8];
            u64 tag[4];
        } front, back;
        float rotation[16];
    } buffers __attribute__((aligned(16)));
    int i, j, group, row, vertex;
    float fade, phase;
    unsigned char *order;
    int group_age;
    char *age_base;
    char *ages;
    int group_vertices;
    float *matrix1;
    int next_group, next_row;
    float *matrix2, *uv1, *uv2;

    {
        float distance = func_00282E48(moby + 0x10, D_L06_001B9840);
        if (distance > 48.0f) fade = (80.0f - distance) * 0.03125f;
        else fade = 1.0f;
    }
    func_002833B8(buffers.rotation, *(float *)data * 0.5f);
    matrix1 = buffers.front.uv;
    matrix2 = buffers.back.uv;
    uv1 = matrix1 + 1;
    uv2 = matrix2 + 1;
    {
        int n;
        for (n = 0; n < *(int *)(data + 4); n++) {
            func_00283410(scratch + n * 0x40, moby + 0xf0);
            func_00283788(scratch + n * 0x40, scratch + n * 0x40, buffers.rotation);
            *(Quad57 *)(scratch + n * 0x40 + 0x30) = *(Quad57 *)(moby + 0x10);
            *(float *)(scratch + n * 0x40 + 0x38) += func_00283CE0(n + 1) * *(float *)(data + 8);
        }
    }
    {
        u64 texture = func_0027C878(14);
        u64 packet_flags = (u64)D_L06_001AF550 | ((u64)D_L06_001AF554 << 2);
        packet_flags |= (u64)D_L06_001AF558 << 4;
        packet_flags |= (u64)D_L06_001AF55C << 6;
        packet_flags |= 0x8000000000ULL;
        ((u64 *)buffers.back.uv)[5] = texture;
        ((u64 *)buffers.front.uv)[5] = texture;
        ((u64 *)buffers.back.uv)[6] = 0xff9000000260ULL;
        ((u64 *)buffers.front.uv)[6] = 0xff9000000260ULL;
        ((u64 *)buffers.back.uv)[4] = 0;
        ((u64 *)buffers.front.uv)[4] = 0;
        ((u64 *)buffers.back.uv)[7] = packet_flags;
        ((u64 *)buffers.front.uv)[7] = packet_flags;
    }
    {
        int k;
        for (k = 0; k < 4; k++) {
            uv1[k * 2] = uv2[k * 2] = D_L06_001AF57C[k * 2];
        }
    }
    group = 0;
    do {
        next_group = group + 1;
        phase = 0.0f;
        row = 0;
        do {
            int next;
            phase += D_L06_001AF71C;
            if (phase > 1.0f) phase -= 1.0f;
            next_row = row + 1;
            for (j = 0; j < 4; j++) {
                matrix1[j * 2] = matrix2[j * 2] =
                    D_L06_001AF578[j * 2] + phase + *(float *)(base + 0x12de0);
            }
            for (i = 0; i < *(int *)(data + 4); i = next) {
                int offset;
                int age;
                float progress;
                unsigned int color;
                order = (unsigned char *)(data + 0x10);
                group_age = group * 0x78;
                age_base = base + 0x10000;
                ages = age_base + 0x2c00;
                age = *(int *)(ages + (order[i] * 4 + group_age));
                group_vertices = group * 0x2580;
                if (age > D_L06_001B31B4) {
                    progress = func_00283CE0(age - D_L06_001B31B4) /
                               func_00283CE0(D_L06_001B31B0 - D_L06_001B31B4);
                } else {
                    progress = 1.0f - func_00283CE0(age) /
                               func_00283CE0(D_L06_001B31B4);
                }
                color = func_00283D38(D_L06_001AF570, D_L06_001AF574, progress);
                color = (color & 0xffffff) +
                        (func_00283CF0(fade * fade *
                         func_00283CE0((int)color >> 24)) << 24);
                if (moby[0x20] == 2) {
                    float alpha = func_00283CE0(*(int *)(data + 0x34));
                    float duration;
                    alpha *= 255.0f;
                    duration = D_L06_001AF620 * 60.0f;
                    color = (func_00283CF0(alpha / duration) << 24) | 0xffffff;
                }
                vertex = 0;
                offset = i * 0x40;
                next = i + 1;
                buffers.back.color[3] = color;
                buffers.back.color[2] = color;
                buffers.back.color[1] = color;
                buffers.back.color[0] = color;
                for (; vertex < 4; vertex++) {
                    func_00282CC0(buffers.back.xyz[vertex], (char *)D_L06_001AF5A0 + vertex * 0x10,
                        (char *)((float (*)[80])(base + group_vertices))[(row + (vertex >> 1))] + order[i] * 0x10);
                }
                func_00280B90(buffers.back.xyz, scratch + offset, 0);
            }
            row = next_row;
        } while (row < 19);
        group = next_group;
    } while (group < 4);
}
