#include "names.h"
/* func_L03_003C4800: visit the object group and emit an effect at each class-specific
   transformed point. Retail reads the id and vector tables $gp-relative, so they are sda
   arrays of their measured sizes (the largest 48 bytes) in a -G64 unit; the 80-byte table and
   the incomplete group table stay absolute. The entry base pointer is a MACRO_ADDR scalar
   (tied lui/lw), and the copy goes straight into the stack vector. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L03_001B2A38 __attribute__((sda));
extern unsigned char *D_L03_001B2A1C MACRO_ADDR;
extern unsigned short *D_L03_001FB5A0[];

extern void moby_transform_joint_point(char *, int, char *);
extern void transform_vector(void *, void *, void *);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

extern int D_L03_001AFF60[6] __attribute__((sda));
extern int D_L03_001AFF78[4] __attribute__((sda));
extern int D_L03_001AFF88[4] __attribute__((sda));
extern int D_L03_001AFF98[6] __attribute__((sda));
extern TI128 D_L03_001AFFB0[3] __attribute__((sda));
extern TI128 D_L03_001AFFE0[3] __attribute__((sda));
extern TI128 D_L03_001B0010[3] __attribute__((sda));
extern TI128 D_L03_0029A880[5];


/* Visits the objects in a group and spawns an effect at each of their fixed attachment points. */
void part_spawn_at_attachment_points(unsigned char *object) {
    unsigned short *idList;
    unsigned char *entity;
    int *boneIds;
    TI128 *offsets;
    int count;
    int j;
    float radius;
    float matrix[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float *vp;

    for (idList = D_L03_001FB5A0[object[0x21]];
         object[0x21] != 0xFF && object[0x21] <= D_L03_001B2A38 && idList != 0 &&
         ((idList != 0 && (short)idList[-1] >= 0) || idList == D_L03_001FB5A0[object[0x21]]);
         idList++) {
        entity = D_L03_001B2A1C + ((*idList & 0x7FFF) << 8);
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
            boneIds = D_L03_001AFF88;
            offsets = D_L03_001AFFE0;
            count = 3;
            break;
        case 0x93C: /* moby class 2364 */
            boneIds = D_L03_001AFF78;
            offsets = D_L03_001AFFB0;
            count = 3;
            break;
        case 0x964: /* Gadgebot */
            boneIds = D_L03_001AFF60;
            offsets = D_L03_0029A880;
            count = 5;
            break;
        default:
            boneIds = D_L03_001AFF98;
            offsets = D_L03_001B0010;
            count = 3;
            break;
        }
        for (j = 0; j < count; j++) {
            moby_transform_joint_point((char *)entity, boneIds[j], (char *)matrix);
            qcopy(point, &offsets[j]);
            radius = point[3];
            point[3] = 1.0f;
            transform_vector(point, point, matrix);
            gfx_l00_draw_billboard_quad(point, *(int *)(entity + 0x78), radius, 0.08f);
        }
    }
}
