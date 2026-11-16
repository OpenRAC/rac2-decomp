#include "names.h"
/* func_L00_004079C8 needs -G64 -Wa,-G64: its 64-byte corner table D_L00_001B0F20 is reached
   through $gp. Same packet layout as func_L00_00407C18 and func_L00_00396078. The packet's GS
   registers are set in RAC1's order (texture, flags, mode, primitive); the record is reached by
   pointer arithmetic (product + base, as retail adds them) and the colour is masked in the
   loop, where loop.c hoists the mask into the preheader as retail does. */
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    Vec points[4];
    unsigned int colours[4];
    float params[8];
    u64 regs[4];
} DrawPacket79C8;
typedef struct { unsigned char pad[4]; unsigned char active; unsigned char rest[219]; } Record;

extern u64 GetEffectTextureDescriptor(int);
extern int FloatToInt(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);

extern unsigned char g_weapon_active_index __attribute__((nosda));
extern Record g_weapon_l00_table[];
extern unsigned int g_sheepinator_beam_color_active __attribute__((sda));
extern unsigned int g_sheepinator_beam_color_idle __attribute__((sda));
extern int g_sheepinator_spark_active[] __attribute__((sda));
extern float g_sheepinator_spark_alphas[] __attribute__((sda));
extern float g_sheepinator_spark_sizes[] __attribute__((sda));
extern Vec g_sheepinator_spark_positions[] __attribute__((sda));
extern Vec g_sheepinator_spark_directions[] __attribute__((sda));
extern Vec g_beam_l00_corner_table[4] __attribute__((sda));
extern Vec g_hero_state_block __attribute__((nosda));

/* Draws a quad for each of the three active sparks of func_L00_00406150's table: basis from
   the spark's direction D_L00_001B2CC0[i] and the up vector D_0018A0E0, placed at
   D_L00_001B2C90[i], corners D_L00_001B0F20 scaled by D_L00_001B2D20[i], alpha from
   D_L00_001B2D00[i] and colour D_L00_001B0EC0 or D_L00_001B0EBC by the current record's
   active byte. */
/* Draws the three bright sparks that run along the Sheepinator beam. */
void DrawLightningArcSparks(void)
{
    DrawPacket79C8 packet;
    Vec basis[4], vertex;
    Vec *corner;
    unsigned int color, c;
    int i, j;

    packet.regs[1] = GetEffectTextureDescriptor(8);
    packet.regs[3] = 0x8000000048ULL;
    packet.regs[2] = 0xFF9000000260ULL;
    packet.regs[0] = 0;
    packet.params[0] = 0; packet.params[1] = 0; packet.params[2] = 0; packet.params[3] = 1;
    packet.params[4] = 1; packet.params[5] = 0; packet.params[6] = 1; packet.params[7] = 1;
    color = (g_weapon_l00_table + g_weapon_active_index)->active ? g_sheepinator_beam_color_active : g_sheepinator_beam_color_idle;
    for (i = 0; i < 3; i++) {
        if (g_sheepinator_spark_active[i]) {
            c = (color & 0xFFFFFF) | (FloatToInt(g_sheepinator_spark_alphas[i]) << 24);
            packet.colours[0] = packet.colours[1] = packet.colours[2] = packet.colours[3] = c;
            qcopy(&basis[3], &g_sheepinator_spark_positions[i]);
            qcopy(&basis[0], &g_sheepinator_spark_directions[i]);
            FastVecScale(&basis[2], &g_hero_state_block, -1.0f);
            FastVecCross(&basis[1], &basis[0], &basis[2]);
            vec_scale_to_length(&basis[1], &basis[1], 1.0f);
            FastVecCross(&basis[2], &basis[1], &basis[0]);
            corner = g_beam_l00_corner_table;
            for (j = 3; j >= 0; corner++, j--) {
                FastVecScale(&vertex, corner, g_sheepinator_spark_sizes[i]);
                transform_vector(&packet.points[3 - j], &vertex, basis);
            }
            draw_world_quad(&packet, 0, 0);
        }
    }
}
