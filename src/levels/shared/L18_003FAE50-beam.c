#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));

typedef struct { unsigned char pad[0x70]; long f70,f78,f80,f88; } QuadPacket;
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; long header[4]; } QuadPayload;
typedef union { QuadPacket raw; QuadPayload view; } BeamPacket;
typedef struct { Vector128 start,next,ray,firstSide,secondSide,step; BeamPacket packet; Vector128 scratch; } BeamWorkspace;
extern Vector128 g_beam_start_points[11],g_beam_end_points[11];
extern char g_camera_l18_position[];
extern float g_beam_uv_v_coords[] MACRO_ADDR;
extern float g_beam_l18_uv_table[4][2] __attribute__((sda));
extern unsigned int g_beam_source_color __attribute__((sda)),g_beam_end_color __attribute__((sda));
extern float g_beam_uv_scroll_step __attribute__((sda));
extern float g_beam_alpha_range[] __attribute__((sda));
extern float g_beam_first_side_length __attribute__((sda)),g_beam_second_side_length __attribute__((sda)),g_beam_segment_count __attribute__((sda));
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float math_random_float_range(float,float);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void gfx_init_quad_packet_state(QuadPacket *,int,int,int);
extern void draw_world_quad(void *,void *,int);
/* Gives the two outer vertices of the beam's first or last segment the
 * alpha-free colour, which fades both ends of the beam out. */
static __inline__ void BeamFadeEnds(BeamPacket *packet,unsigned int rgb,const int *segment)
{
    if(*segment==0) {
        packet->view.colors[0]=rgb;
        packet->view.colors[1]=rgb;
    } else if((float)*segment==g_beam_segment_count-1.0f) {
        packet->view.colors[2]=rgb;
        packet->view.colors[3]=rgb;
    }
}
/* Draws a set of jagged glowing beams that slide along their length and fade at both ends. */
void DrawSegmentedBeams(char *object)
{
    BeamWorkspace local;
    char *state=*(char **)(object+0x68);
    unsigned int faded,rgb,endColor;
    float alpha;
    unsigned int alphaByte,sourceColor;
    int beam,i;
    for(beam=0;beam<11;beam++) {
        qcopy(&local.start,&g_beam_start_points[beam]);
        FastVecSub(&local.step,&g_beam_end_points[beam],&local.start);
        FastVecScale(&local.step,&local.step,1.0f/g_beam_segment_count);
        FastVecAdd(&local.next,&local.start,&local.step);
        alpha=math_random_float_range(g_beam_alpha_range[0],g_beam_alpha_range[1]);
        sourceColor=g_beam_source_color;
        alphaByte=sourceColor>>24;
        faded=sourceColor&0xffffffu;
        faded|=(unsigned int)(int)(alpha*(float)(int)alphaByte)<<24;
        {
        int segment;
        for(segment=0;(float)segment<g_beam_segment_count;) {
            rgb=faded&0xffffffu;
            FastVecSub(&local.ray,&local.start,&local.next);
            FastVecSub(&local.firstSide,&local.start,g_camera_l18_position);
            FastVecSub(&local.secondSide,&local.next,g_camera_l18_position);
            FastVecCross(&local.firstSide,&local.firstSide,&local.ray);
            FastVecCross(&local.secondSide,&local.secondSide,&local.ray);
            vec_scale_to_length(&local.firstSide,&local.firstSide,g_beam_first_side_length);
            vec_scale_to_length(&local.secondSide,&local.secondSide,g_beam_first_side_length);
            gfx_init_quad_packet_state(&local.packet.raw,0x17,1,0x80);
            local.packet.view.colors[3]=faded;
            local.packet.view.colors[2]=faded;
            local.packet.view.colors[1]=faded;
            local.packet.view.colors[0]=faded;
            {
            int index=segment;
            BeamFadeEnds(&local.packet,rgb,&segment);
            for(i=0;i<4;i++) {
                local.packet.view.uv[i][0]=g_beam_l18_uv_table[i][0]+*(float *)(state+0x8c);
                local.packet.view.uv[i][1]=g_beam_uv_v_coords[i*2];
            }
            FastVecSub(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[0]=local.scratch;
            FastVecAdd(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[1]=local.scratch;
            FastVecSub(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[2]=local.scratch;
            FastVecAdd(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[3]=local.scratch;
            draw_world_quad(&local.packet.raw,0,0);
            vec_scale_to_length(&local.firstSide,&local.firstSide,g_beam_second_side_length);
            vec_scale_to_length(&local.secondSide,&local.secondSide,g_beam_second_side_length);
            FastVecSub(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[0]=local.scratch;
            FastVecAdd(&local.scratch,&local.start,&local.firstSide);
            local.packet.view.vertices[1]=local.scratch;
            FastVecSub(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[2]=local.scratch;
            FastVecAdd(&local.scratch,&local.next,&local.secondSide);
            local.packet.view.vertices[3]=local.scratch;
            gfx_init_quad_packet_state(&local.packet.raw,0x2b,1,0x80);
            endColor=g_beam_end_color;
            local.packet.view.colors[3]=endColor;
            local.packet.view.colors[2]=endColor;
            local.packet.view.colors[1]=endColor;
            local.packet.view.colors[0]=endColor;
            if(segment==0) {
                local.packet.view.colors[0]=endColor&0xffffffu;
                local.packet.view.colors[1]=endColor&0xffffffu;
            } else if((float)segment==g_beam_segment_count-1.0f) {
                local.packet.view.colors[2]=endColor&0xffffffu;
                local.packet.view.colors[3]=endColor&0xffffffu;
            }
            segment=index+1;
            }
            draw_world_quad(&local.packet.raw,0,0);
            qcopy(&local.start,&local.next);
            FastVecAdd(&local.next,&local.next,&local.step);
        }
        }
    }
    *(float *)(state+0x8c)+=g_beam_uv_scroll_step;
    if(*(float *)(state+0x8c)>1.0f) *(float *)(state+0x8c)-=2.0f;
    if(*(float *)(state+0x8c)<-1.0f) *(float *)(state+0x8c)+=2.0f;
}
