#include "names.h"
/* func_L03_003C4800: visit the object group and emit an effect at each class-specific
   transformed point. Retail reads the id and vector tables $gp-relative, so they are sda
   arrays of their measured sizes (the largest 48 bytes) in a -G64 unit; the 80-byte table and
   the incomplete group table stay absolute. The entry base pointer is a MACRO_ADDR scalar
   (tied lui/lw), and the copy goes straight into the stack vector. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int g_object_group_count __attribute__((sda));
extern unsigned char *g_moby_record_base MACRO_ADDR;
extern unsigned short *g_entity_id_lists[];

extern void moby_transform_joint_point(char *, int, char *);
extern void transform_vector(void *, void *, void *);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

extern int g_attachment_bone_ids_a[6] __attribute__((sda));
extern int g_attachment_bone_ids_b[4] __attribute__((sda));
extern int g_attachment_bone_ids_c[4] __attribute__((sda));
extern int g_attachment_bone_ids_d[6] __attribute__((sda));
extern TI128 g_attachment_offsets_a[3] __attribute__((sda));
extern TI128 g_attachment_offsets_b[3] __attribute__((sda));
extern TI128 g_attachment_offsets_c[3] __attribute__((sda));
extern TI128 g_attachment_point_offsets[5];


/* Visits the objects in a group and spawns an effect at each of their fixed attachment points. */
void part_spawn_at_attachment_points(unsigned char *object) {
    unsigned short *id_list;
    unsigned char *entity;
    int *bone_ids;
    TI128 *offsets;
    int count;
    int j;
    float radius;
    float matrix[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float *vp;

    for (id_list = g_entity_id_lists[object[0x21]];
         object[0x21] != 0xFF && object[0x21] <= g_object_group_count && id_list != 0 &&
         ((id_list != 0 && (short)id_list[-1] >= 0) || id_list == g_entity_id_lists[object[0x21]]);
         id_list++) {
        entity = g_moby_record_base + ((*id_list & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x31] == 0)
            continue;
        if (entity[0x20] == 0xFE)
            continue;
        if (entity[0x20] == 0xFD)
            continue;
        switch (*(short *)(entity + 0xAA)) {
        case 0x940: /* Bridgebot */
            bone_ids = g_attachment_bone_ids_c;
            offsets = g_attachment_offsets_b;
            count = 3;
            break;
        case 0x93C: /* moby class 2364 */
            bone_ids = g_attachment_bone_ids_b;
            offsets = g_attachment_offsets_a;
            count = 3;
            break;
        case 0x964: /* Gadgebot */
            bone_ids = g_attachment_bone_ids_a;
            offsets = g_attachment_point_offsets;
            count = 5;
            break;
        default:
            bone_ids = g_attachment_bone_ids_d;
            offsets = g_attachment_offsets_c;
            count = 3;
            break;
        }
        for (j = 0; j < count; j++) {
            moby_transform_joint_point((char *)entity, bone_ids[j], (char *)matrix);
            qcopy(point, &offsets[j]);
            radius = point[3];
            point[3] = 1.0f;
            transform_vector(point, point, matrix);
            gfx_l00_draw_billboard_quad(point, *(int *)(entity + 0x78), radius, 0.08f);
        }
    }
}
