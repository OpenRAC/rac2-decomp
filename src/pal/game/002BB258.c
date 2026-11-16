#include "include_asm.h"

#include "common.h"
extern void part_kill(char *);
extern void FastVecAdd(char *, char *, char *);
typedef int TI __attribute__((mode(TI)));
extern float coll_get_heightmap_height(TI *pos);
extern int g_current_map_index MACRO_ADDR;
extern float g_particle_ground_vector[] MACRO_ADDR;

/* Moves a falling particle with gravity and drag, and removes it when it leaves the map or sinks below the ground. */
void part_update_falling_pal(char *part)
{
    float *f = (float *)part;
    float *vel = f + 0xC;
    float floor_z = vel[3];
    float step[4] __attribute__((aligned(16)));
    TI pos_a, pos_b;
    int cell_x, cell_y;
    float height;

    if (g_current_map_index == 15) {
        if (f[6] < floor_z) {
            part_kill(part);
            return;
        }
    } else if (f[6] < floor_z || f[4] < 0.0f || f[5] < 0.0f || f[4] > 1024.0f || f[5] > 1024.0f) {
        part_kill(part);
        return;
    }
    cell_x = (int)f[8];
    cell_y = (int)f[9];
    FastVecAdd((char *)step, (char *)vel, (char *)g_particle_ground_vector);
    FastVecAdd((char *)(f + 8), (char *)(f + 8), (char *)step);
    FastVecAdd((char *)(f + 4), (char *)(f + 4), (char *)step);
    if (*(short *)(part + 0xA) != 2 && (cell_x != (int)f[8] || cell_y != (int)f[9])) {
        pos_a = *(TI *)(f + 8);
        height = coll_get_heightmap_height(&pos_a);
        if (height >= g_particle_ground_vector[4]) {
            pos_b = *(TI *)(f + 8);
            floor_z = coll_get_heightmap_height(&pos_b);
        } else {
            floor_z = g_particle_ground_vector[4];
        }
        if (f[10] < floor_z) {
            part_kill(part);
            return;
        }
    }
    vel[2] -= 0.00392f;
    vel[3] = floor_z + g_particle_ground_vector[2];
}


extern char *part_alloc(int size);
extern int ref_002BA8A0_01(float f);
extern unsigned char *ref_002BA8A0_00;

/* Allocates a one-byte record, nudges the source's field 8 up by 0.2, copies the source's
 * first 16 bytes into the record and fills the record's header. */
void part_spawn_glow_pal(void *source, int alpha)
{
    char *part = (char *)part_alloc(1);
    unsigned char texture;
    int jitter;

    if (part == 0)
        return;
    *(float *)((char *)source + 8) = *(float *)((char *)source + 8) + 0.2f;
    qcopy(part + 0x10, source);
    *(int *)(part + 4) = (alpha << 24) | 0x00907070;
    jitter = ref_002BA8A0_01(2.0f);
    *(char *)(part + 9) = (char)(jitter + 0x40);
    *(char *)(part + 3) = 0x44;
    *(char *)(part + 1) = 0;
    texture = *ref_002BA8A0_00;
    *(int *)(part + 0x20) = alpha;
    *(float *)(part + 0xC) = 63000.00390625f;
    *(unsigned char *)(part + 8) = 0xA0;
    *(short *)(part + 0xA) = 0x16;
    *(char *)(part + 2) = texture;
}


extern int FastDecTimer(char *);
extern unsigned char *g_fading_texture_indices;

/* func_PAL_002BB530, the PAL copy of func_002BA978: the same C, with a lifetime of 22 frames for
 * 27, and the table index scaled to span the same ten entries: (22 - t) * 9 / 22 for (27 - t) / 3. */
void part_update_fading_texture_pal(char *self)
{
    int alpha = *(short *)(self + 0xA) * *(int *)(self + 0x20) / 22;
    *(unsigned int *)(self + 4) = (*(unsigned int *)(self + 4) & 0xFFFFFFu) | (alpha << 24);
    if (FastDecTimer(self + 0xA)) {
        part_kill(self);
    } else {
        self[2] = g_fading_texture_indices[(22 - *(short *)(self + 0xA)) * 9 / 22];
    }
}
