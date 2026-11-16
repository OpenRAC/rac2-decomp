#include "names.h"
/* func_L15_00437B68: draws the 100-quad grid in up to four height layers, the
 * u coordinates scrolling with the float at state+4.
 * Source forms the compiler's loop heuristics depend on:
 * - the two middle layers walk four cursors declared colors, v, u, vertex, so
 *   their pass-1 loop.c count allows the factor 6 to move and those two corner
 *   loops reverse; the first and last layers index the packet directly.
 * - the last layer loads positions before the index shift and clamps through a
 *   second local: that hoists -1 out of the corner loop but leaves the mask in. */

#include "common.h"

typedef struct { float x,y,z,w; } GornVec __attribute__((aligned(16)));
typedef struct { GornVec vertex[4]; unsigned int color[4]; float uv[4][2]; long long tag[4]; GornVec matrix[4]; } GornPacket;
typedef struct { short position,uv,color; } GornCorner;
extern GornVec g_backdrop_vertex_table[];
extern GornCorner g_backdrop_corner_table[][4];
extern float g_backdrop_uv_table[][2];
extern unsigned int g_backdrop_color_table[];
extern int g_backdrop_effect_flag __attribute__((sda));
extern int g_backdrop_fade_amount __attribute__((sda));
extern long long GetEffectTextureDescriptor(int);
extern void FastVecScale(void *,const void *,float);
extern void draw_world_quad(void *,void *,int);
/* Draws the scrolling grid of layered quads that forms the backdrop, and scrolls its texture a little each frame. */
void DrawScrollingGridLayers(char *object,int preview)
{
    GornPacket packet;
    char *state;
    int i,corner,alpha,faded;
    int position_index,uv_index,color_index;
    unsigned int color;
    state=*(char **)(object+0x68);
    packet.tag[1]=GetEffectTextureDescriptor(72);
    packet.tag[2]=0xFF9000000260LL;
    packet.tag[3]=0x8000000044LL;
    packet.tag[0]=0;
    qcopy(&packet.matrix[0], (object+0xC0));
    qcopy(&packet.matrix[1], (object+0xD0));
    qcopy(&packet.matrix[2], (object+0xE0));
    packet.matrix[3].x=*(float *)(object+0x10);
    packet.matrix[3].y=*(float *)(object+0x14);
    packet.matrix[3].z=*(float *)(object+0x18);
    packet.matrix[3].w=1.0f;
    packet.color[0]=packet.color[1]=packet.color[2]=packet.color[3]=0x80808080;
    *(float *)(state+4)-=0.00045f;
    if (*(float *)(state+4)<=-8.0f) *(float *)(state+4)+=8.0f;
    if (preview) {
        for(i=0;i<121;i++) g_backdrop_vertex_table[i].z=300.0f;
        for(i=0;i<100;i++) {
            for(corner=0;corner<4;corner++) {
                position_index=g_backdrop_corner_table[i][corner].position; uv_index=g_backdrop_corner_table[i][corner].uv; color_index=g_backdrop_corner_table[i][corner].color;
                FastVecScale(&packet.vertex[corner],&g_backdrop_vertex_table[position_index],1.0f);
                packet.uv[corner][0]=g_backdrop_uv_table[uv_index][0]+*(float *)(state+4);
                packet.uv[corner][1]=g_backdrop_uv_table[uv_index][1];
                packet.color[corner]=(g_backdrop_color_table[color_index]&0xFFFFFF)|0x7F000000;
            }
            draw_world_quad(&packet,0,0);
        }
        return;
    }
    for(i=0;i<121;i++) g_backdrop_vertex_table[i].z=800.0f;
    for(i=0;i<100;i++) {
        unsigned int *colors=packet.color; float *v=&packet.uv[0][1]; float *u=&packet.uv[0][0]; GornVec *vertex=packet.vertex;
        for(corner=0;corner<4;corner++) {
            position_index=g_backdrop_corner_table[i][corner].position; uv_index=g_backdrop_corner_table[i][corner].uv; color_index=g_backdrop_corner_table[i][corner].color;
            FastVecScale(vertex,&g_backdrop_vertex_table[position_index],1.0f);
            *u=g_backdrop_uv_table[uv_index][0]+*(float *)(state+4);
            *v=g_backdrop_uv_table[uv_index][1];
            *colors=g_backdrop_color_table[color_index];
            vertex++;u+=2;v+=2;colors++;
        }
        draw_world_quad(&packet,0,0);
    }
    for(i=0;i<121;i++) g_backdrop_vertex_table[i].z=1200.0f;
    for(i=0;i<100;i++) {
        unsigned int *colors=packet.color; float *v=&packet.uv[0][1]; float *u=&packet.uv[0][0]; GornVec *vertex=packet.vertex;
        for(corner=0;corner<4;corner++) {
            position_index=g_backdrop_corner_table[i][corner].position; uv_index=g_backdrop_corner_table[i][corner].uv; color_index=g_backdrop_corner_table[i][corner].color;
            FastVecScale(vertex,&g_backdrop_vertex_table[position_index],1.0f);
            *u=g_backdrop_uv_table[uv_index][0]+*(float *)(state+4);
            *v=g_backdrop_uv_table[uv_index][1];
            *colors=g_backdrop_color_table[color_index];
            vertex++;u+=2;v+=2;colors++;
        }
        draw_world_quad(&packet,0,0);
    }
    if (g_backdrop_effect_flag) {
        for(i=0;i<121;i++) g_backdrop_vertex_table[i].z=405.0f;
        for(i=0;i<100;i++) {
            for(corner=0;corner<4;corner++) {
                GornVec *positions;
                position_index=g_backdrop_corner_table[i][corner].position; uv_index=g_backdrop_corner_table[i][corner].uv; color_index=g_backdrop_corner_table[i][corner].color;
                positions=g_backdrop_vertex_table;
                FastVecScale(&packet.vertex[corner],positions+position_index,1.0f);
                packet.uv[corner][0]=g_backdrop_uv_table[uv_index][0]+*(float *)(state+4);
                packet.uv[corner][1]=g_backdrop_uv_table[uv_index][1];
                color=g_backdrop_color_table[color_index];
                faded=((int)color>>24)-g_backdrop_fade_amount;
                alpha=faded<0?0:faded;
                packet.color[corner]=(color&0xFFFFFF)|((unsigned int)alpha<<24);
            }
            draw_world_quad(&packet,0,0);
        }
    }
}
