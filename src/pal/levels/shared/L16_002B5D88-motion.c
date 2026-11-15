#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define V(offset) ((char *)&D_00189E20+(offset))
typedef struct {
char pad0[268];
float field10c;
char pad110[8];
float field118;
char pad11c[64];
float field15c;
char pad160[16];
float field170;
float field174;
float field178;
float field17c;
float field180;
float field184;
char pad188[104];
s16 field1f0;
char pad1f2[114];
float field264;
char pad268[4];
int field26c;
char pad270[23];
u8 field287;
char pad288[148];
float field31c;
char pad320[616];
int field588;
char pad58c[7432];
int field2294;
char pad2298[4];
int field229c;
} Resident;
extern Resident g_hero_state;
extern void func_PAL_L00_002D4668(int,void *,void *);
extern float cam_get_view_space_vector_length(char *);
extern float cam_get_view_space_height(char *);
extern void cam_set_view_space_vector_length(char *,char *,float);
extern void cam_set_view_space_height(Quad *,Quad *,float);
extern float vec_length_xy(void *);
extern void vec_fast_normalize_helper(void *,void *,float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_clear_128(Quad *);
extern float FastVecDot(void *,void *);
extern void FastVecScale(void *,void *,float);
extern void hero_resolve_collision_with_rewind(void);
extern void hero_probe_ground(void);
extern void func_PAL_L00_002B5178(void);
extern void cam_project_vector_onto_view_plane(char *,char *);
extern float hero_get_speed_along_forward(void *);

void func_PAL_L16_002B5D88(void)
{
    float oldPosition[4],horizontal[4],vertical[4];
    float limit,saved;
    qcopy(oldPosition,V(0x80));
    func_PAL_L00_002D4668(g_hero_state.field588,V(0x100),V(0x90));
    if (g_hero_state.field2294==0x14 || g_hero_state.field2294==0x5B || g_hero_state.field2294==0x58 || g_hero_state.field2294==0x81) {
        if (g_hero_state.field1f0==0 && cam_get_view_space_vector_length(V(0xF0))>g_hero_state.field264-0.02f)
            cam_set_view_space_vector_length(V(0xF0),V(0xF0),g_hero_state.field264-0.02f);
        if (cam_get_view_space_height(V(0xF0)) < -g_hero_state.field31c) {
            limit=-g_hero_state.field31c-0.02f;
            if (limit>0.0f) limit=0.0f;
            cam_set_view_space_height((Quad *)V(0xF0),(Quad *)V(0xF0),limit);
        }
    } else if (g_hero_state.field229c==15) {
        if (g_hero_state.field1f0==0 && vec_length_xy(V(0xF0))>g_hero_state.field264-0.02f)
            vec_fast_normalize_helper(V(0xF0),V(0xF0),g_hero_state.field264-0.02f);
    } else {
        if (g_hero_state.field229c==13) goto moved;
        if (g_hero_state.field229c==14) goto moved;
        if (g_hero_state.field1f0==0 && FastVecLength(V(0xF0))>g_hero_state.field264-0.02f)
            vec_scale_to_length(V(0xF0),V(0xF0),g_hero_state.field264-0.02f);
    }
moved:
    FastVecAdd(V(0x80),V(0x80),V(0xF0));
    FastVecAdd(V(0x80),V(0x80),V(0xA60));
    vec_clear_128((Quad *)V(0xA60));
    g_hero_state.field287=0;
    g_hero_state.field26c=0;
    if (FastVecLength(V(0x100))<=0.0001f) {
        hero_resolve_collision_with_rewind();
        hero_probe_ground();
        FastVecSub(V(0x110),V(0x80),oldPosition);
        func_PAL_L00_002B5178();
    } else hero_probe_ground();
    FastVecSub(V(0x120),V(0x80),oldPosition);
    qcopy(V(0x140),V(0x120));
    qcopy(V(0x130),V(0x120));
    vec_scale_to_length(V(0x120),V(0x120),1.0f);
    { float dot;
    dot=FastVecDot(V(0x120),V(0xF0));
    if (dot<0.0f) dot=0.0f;
    vec_scale_to_length(V(0x120),V(0xF0),dot);
    }
    qcopy(horizontal,V(0xF0));
    cam_project_vector_onto_view_plane((char *)horizontal,(char *)horizontal);
    cam_project_vector_onto_view_plane(V(0x140),V(0x140));
    vec_scale_to_length(V(0x140),V(0x140),1.0f);
    { float dot;
    dot=FastVecDot(V(0x140),horizontal);
    if (dot<0.0f) dot=0.0f;
    vec_scale_to_length(V(0x140),horizontal,dot);
    }
    qcopy(vertical,V(0xF0));
    cam_set_view_space_vector_length((char *)vertical,(char *)vertical,0.0f);
    cam_set_view_space_vector_length(V(0x130),V(0x130),0.0f);
    vec_scale_to_length(V(0x130),V(0x130),1.0f);
    { float dot;
    dot=FastVecDot(V(0x130),vertical);
    if (dot<0.0f) dot=0.0f;
    vec_scale_to_length(V(0x130),vertical,dot);
    }
    g_hero_state.field170=FastVecLength(V(0x120));
    g_hero_state.field174=cam_get_view_space_vector_length(V(0x120));
    *(Quad *)horizontal=*(Quad *)V(0x120);
    g_hero_state.field178=hero_get_speed_along_forward(horizontal);
    g_hero_state.field180=cam_get_view_space_height(V(0x120));
    if (g_hero_state.field178<0.0f) g_hero_state.field178=0.0f;
    qcopy(horizontal,V(0x80));
    if (FastVecLength(V(0x100))>0.0001f) {
        FastVecAdd(V(0x80),V(0x80),V(0x100));
        saved=g_hero_state.field10c;
        vec_clear_128((Quad *)V(0x100));
        g_hero_state.field10c=saved;
        hero_resolve_collision_with_rewind();
        hero_probe_ground();
        FastVecSub(V(0x110),V(0x80),oldPosition);
        func_PAL_L00_002B5178();
    }
    FastVecSub(V(0x150),V(0x80),horizontal);
    g_hero_state.field184=FastVecLength(V(0x150));
    g_hero_state.field15c=g_hero_state.field10c;
    g_hero_state.field10c=0.0f;
    FastVecSub(V(0x110),V(0x80),oldPosition);
    g_hero_state.field17c=0.0f;
    if (g_hero_state.field174>0.004f) {
        g_hero_state.field17c=g_hero_state.field118/g_hero_state.field174;
        if (g_hero_state.field17c>0.5f) g_hero_state.field17c=0.5f;
        else if (g_hero_state.field17c<-0.5f) g_hero_state.field17c=-0.5f;
    }
    if (g_hero_state.field170>1.0400001f) {
        FastVecScale(V(0x110),V(0x110),1.0400001f/g_hero_state.field170);
        g_hero_state.field170=1.0400001f;
    }
}
