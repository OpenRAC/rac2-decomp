#include "common.h"

typedef struct { char pad[8]; void *active; char gap[20]; float data[4]; } EquipState;

typedef struct {
    char pad00[0x30];
    unsigned char alpha;
    char pad31;
    unsigned short drawMask;
    unsigned short flags;
    char pad36[0x63 - 0x36];
    unsigned char mode;
    char pad64[4];
    EquipState *state;
} EquipPiece;

extern EquipPiece *CreateMoby(int);
extern void hero_destroy_equipment_pieces(void);
extern EquipPiece *g_hero_moby_default;
extern unsigned int g_equipment_bits MACRO_ADDR;
extern short g_robot_part_ids_b[] MACRO_ADDR, g_robot_part_ids_c[] MACRO_ADDR, g_robot_part_ids_d[] MACRO_ADDR, g_robot_part_ids_e[] MACRO_ADDR;
extern short g_robot_part_ids_f[] MACRO_ADDR, g_robot_part_ids_g[] MACRO_ADDR, g_robot_part_ids_h[] MACRO_ADDR;
extern EquipPiece *g_equipment_pieces[];

/* Spawns the hero's equipment pieces from the equipment bits and flags them. */
void SpawnEquipmentPieces(EquipPiece *base)
{
    EquipPiece **parts;
    EquipPiece **p;
    EquipPiece *piece;
    EquipState *state;
    unsigned int equipment;
    int chassis, partA, partB, partC, partD, partE, partF, count;

    if (!base)
        base = g_hero_moby_default;
    hero_destroy_equipment_pieces();
    count = 5;
    base->alpha = 255;
    parts = g_equipment_pieces;
    equipment = g_equipment_bits;
    chassis = (equipment >> 2) & 3;
    partA = (equipment >> 4) & 1;
    partB = (equipment >> 6) & 1;
    partC = (equipment >> 7) & 3;
    partD = (equipment >> 9) & 1;
    partE = (equipment >> 10) & 3;
    partF = (equipment >> 14) & 3;
    parts[0] = CreateMoby(g_robot_part_ids_b[chassis]);
    parts[1] = CreateMoby(g_robot_part_ids_b[chassis]);
    parts[1]->flags |= 0x8000;
    parts[2] = CreateMoby(g_robot_part_ids_c[partA]);
    parts[3] = CreateMoby(g_robot_part_ids_d[partB]);
    parts[4] = CreateMoby(g_robot_part_ids_d[partB]);
    parts[4]->flags |= 0x8000;
    if (g_robot_part_ids_e[partC]) {
        parts[5] = CreateMoby(g_robot_part_ids_e[partC]);
        parts[6] = CreateMoby(g_robot_part_ids_e[partC]);
        count = 7;
        parts[6]->flags |= 0x8000;
    }
    parts[count++] = CreateMoby(g_robot_part_ids_f[partD]);
    piece = parts[count++] = CreateMoby(g_robot_part_ids_f[partD]);
    piece->flags |= 0x8000;
    parts[count++] = CreateMoby(g_robot_part_ids_g[partE]);
    piece = parts[count++] = CreateMoby(g_robot_part_ids_g[partE]);
    piece->flags |= 0x8000;
    if ((g_equipment_bits >> 12) & 1)
        parts[count++] = CreateMoby(0x10E2 /* moby class 4322 */);
    if ((g_equipment_bits >> 13) & 1)
        parts[count++] = CreateMoby(0x10E4 /* moby class 4324 */);
    if (partF)
        parts[count] = CreateMoby(g_robot_part_ids_h[partF]);
    if (*parts) {
        p = parts;
        do {
            if ((*p)->mode)
                (*p)->mode = 8;
            (*p)->flags |= 0x124;
            (*p)->drawMask = 0x1FF;
            (*p)->state->active = (*p)->state->data;
        } while (*++p);
    }
    base->flags |= 0x20;
    state = base->state;
    state->active = state->data;
}
