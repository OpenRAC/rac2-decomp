#include "common.h"

typedef unsigned int GroupEffectQuad __attribute__((mode(TI)));
extern void moby_transform_joint_to_world(char *,int,float *);
extern void moby_transform_joint_point(char *,int,float *);
extern void transform_vector(float *,float *,float *);
/* Integer and FP arguments retain their order in the separate EE banks. */
extern void gfx_draw_camera_facing_flash_b(int, char *, float, int, int, int);
extern short *g_moby_group_lists[];
extern char *g_moby_pool_start;
extern int g_moby_group_count __attribute__((sda));

/* Draws glowing effects at three joints of the object and of the other members of its group. */
void group_draw_joint_glows(unsigned char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float other[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    short *list;
    unsigned char *object;
    if ((unsigned char)self[0x21] == 255) {
        if ((unsigned char)self[0x31]) {
            *(GroupEffectQuad *)offset = 0;
            offset[0] = 0.25f; offset[3] = 1.0f;
            moby_transform_joint_to_world(self,4,pos);
            moby_transform_joint_to_world(self,5,other);
            moby_transform_joint_point(self,6,matrix);
            transform_vector(offset,offset,matrix);
            gfx_draw_camera_facing_flash_b((int)self,(char *)pos,0.125f,0x36F6,0x20000000,0x20000000);
            gfx_draw_camera_facing_flash_b((int)self,(char *)other,0.15f,0xFF3E00,0x30000000,0x20000000);
            gfx_draw_camera_facing_flash_b((int)self,(char *)offset,0.15f,0xFF3E00,0x10000000,0x30000000);
        }
    } else {
        list = g_moby_group_lists[(unsigned char)self[0x21]];
        while ((unsigned char)self[0x21] != 255 && (unsigned char)self[0x21] <= g_moby_group_count && list && ((list && list[-1] >= 0) || list == g_moby_group_lists[(unsigned char)self[0x21]])) {
            object = g_moby_pool_start + ((unsigned short)*list & 0x7FFF) * 256;
            if (!object) break;
            if (object[0x20] == 254) goto next;
            if (object[0x20] == 253) goto next;
            if ((unsigned char)object[0x31] && *(short *)(object+0xAA) == *(short *)(self+0xAA)) {
                *(GroupEffectQuad *)offset = 0;
                offset[0] = 0.25f; offset[3] = 1.0f;
                moby_transform_joint_to_world(object,4,pos);
                moby_transform_joint_to_world(object,5,other);
                moby_transform_joint_point(object,6,matrix);
                transform_vector(offset,offset,matrix);
                gfx_draw_camera_facing_flash_b((int)object,(char *)pos,0.125f,0x36F6,0x20000000,0x20000000);
                gfx_draw_camera_facing_flash_b((int)object,(char *)other,0.15f,0xFF3E00,0x30000000,0x20000000);
                gfx_draw_camera_facing_flash_b((int)object,(char *)offset,0.15f,0xFF3E00,0x10000000,0x30000000);
            }
next:
            list++;
        }
    }
}
