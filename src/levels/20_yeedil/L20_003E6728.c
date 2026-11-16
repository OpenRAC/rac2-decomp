/* func_L20_003E6728: Yeedil's own copy of func_L00_003C5310 (same C); needs -frac2-sticky-volatile-refs, see docs/build/compiler-notes.md. */
#include "common.h"

/* Own unit: -fmove-all-movables lets loop.c hoist the second strip loop's
 * copy-destination address in its first pass (the default threshold leaves it
 * to the rerun pass), which gives retail's preheader order and allocation. */

typedef struct { float f[4]; } Vector __attribute__((aligned(16)));
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[8];
    long reserved, texture, state, flags;
} QuadPacket;
extern Vector g_camera_l20_position;
extern void gfx_init_quad_packet_state(QuadPacket *,int,int,int);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern float IntToFloat(int);
extern unsigned int FastTweenColor(unsigned int,unsigned int,float);
extern void draw_world_quad(QuadPacket *,void *,int);
extern float FastVecLength(void *);
extern void FastVecScale(void *,void *,float);
extern void VU1_addGSregister(unsigned int,unsigned long long);

/* Draws a ribbon along a loop of points, with a second narrower bevel strip drawn on the inside edge. */
void gfx_draw_ribbon_along_points(Vector *points,int count,int texture1,int texture2,
    unsigned int colorEnd1,unsigned int colorStart1,unsigned int colorEnd2,unsigned int colorStart2,
    int first,int last,int segments,float width1,float width2,float inset)
{
    QuadPacket strip, bevel;
    Vector cross, scaledCross, radial, tangent, left, right, nextRadial, previousRadial, scaledRadial, equalRadial1, equalRadial2, offset;
    float step, fraction, previousLength, nextLength;
    int current, previous, next;
    gfx_init_quad_packet_state(&strip,texture1,1,128);
    strip.color[0]=strip.color[1]=strip.color[2]=strip.color[3]=colorStart1;
    strip.uv[0]=0; strip.uv[1]=0; strip.uv[2]=0; strip.uv[3]=1;
    strip.uv[4]=1; strip.uv[5]=0; strip.uv[6]=1; strip.uv[7]=1;
    gfx_init_quad_packet_state(&bevel,texture2,1,128);
    bevel.color[0]=bevel.color[1]=bevel.color[2]=bevel.color[3]=colorStart2;
    bevel.uv[0]=0; bevel.uv[1]=0; bevel.uv[2]=0; bevel.uv[3]=1;
    bevel.uv[4]=1; bevel.uv[5]=0; bevel.uv[6]=1; bevel.uv[7]=1;
    next=(first+1)%count;
    FastVecSub(&radial,&points[first],&g_camera_l20_position);
    FastVecSub(&tangent,&points[next],&points[first]);
    FastVecCross(&cross,&tangent,&radial);
    vec_scale_to_length(&cross,&cross,width1);
    FastVecAdd(&strip.vertex[0],&points[first],&cross);
    FastVecSub(&strip.vertex[1],&points[first],&cross);
    step=1.0f/IntToFloat(segments-1);
    fraction=step;
    current=next;
    previous=first;
    while (current!=last) {
        FastVecSub(&radial,&points[current],&g_camera_l20_position);
        FastVecSub(&tangent,&points[current],&points[previous]);
        FastVecCross(&cross,&tangent,&radial);
        vec_scale_to_length(&cross,&cross,width1);
        FastVecAdd(&strip.vertex[2],&points[current],&cross);
        FastVecSub(&strip.vertex[3],&points[current],&cross);
        strip.color[2]=strip.color[3]=FastTweenColor(colorStart1,colorEnd1,fraction);
        draw_world_quad(&strip,0,0);
        qcopy(&strip.vertex[0],&strip.vertex[2]);
        qcopy(&strip.vertex[1],&strip.vertex[3]);
        strip.color[0]=strip.color[1]=strip.color[2];
        fraction+=step;
        previous=current;
        current=(previous+1)%count;
    }
    FastVecSub(&previousRadial,&points[first],&g_camera_l20_position);
    previousLength=FastVecLength(&previousRadial);
    fraction=step;
    current=next;
    while (current!=last) {
        FastVecSub(&nextRadial,&points[current],&g_camera_l20_position);
        nextLength=FastVecLength(&nextRadial);
        if (previousLength<nextLength) {
            if (previousLength==0.0f) qcopy(&equalRadial1,&nextRadial);
            else FastVecScale(&equalRadial1,&previousRadial,nextLength/previousLength);
            FastVecAdd(&left,&g_camera_l20_position,&nextRadial);
            FastVecAdd(&right,&g_camera_l20_position,&equalRadial1);
        } else {
            if (nextLength==0.0f) qcopy(&equalRadial2,&previousRadial);
            else FastVecScale(&equalRadial2,&nextRadial,previousLength/nextLength);
            FastVecAdd(&left,&g_camera_l20_position,&equalRadial2);
            FastVecAdd(&right,&g_camera_l20_position,&previousRadial);
        }
        FastVecSub(&tangent,&right,&left);
        FastVecScale(&offset,&tangent,inset);
        FastVecSub(&left,&left,&offset);
        FastVecAdd(&right,&right,&offset);
        FastVecSub(&scaledRadial,&g_camera_l20_position,&left);
        FastVecCross(&cross,&scaledRadial,&tangent);
        vec_scale_to_length(&scaledCross,&cross,width2);
        FastVecAdd(&bevel.vertex[0],&left,&scaledCross);
        FastVecSub(&bevel.vertex[1],&left,&scaledCross);
        FastVecAdd(&bevel.vertex[2],&right,&scaledCross);
        FastVecSub(&bevel.vertex[3],&right,&scaledCross);
        bevel.color[2]=bevel.color[3]=FastTweenColor(colorStart2,colorEnd2,fraction);
        draw_world_quad(&bevel,0,0);
        qcopy(&previousRadial,&nextRadial);
        bevel.color[0]=bevel.color[1]=bevel.color[2];
        current=(current+1)%count;
        fraction+=step;
        previousLength=nextLength;
    }
    VU1_addGSregister(0x47,0x5360b);
}
