#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern void vec_scale_to_length(void *,void *,float),transform_vector(void *,void *,void *),FastVecSub(void *,void *,void *),FastVecScale(void *,void *,float),matrix_mul_vec3(void *,void *,void *);
extern float math_fabs(float),FastVecDot(void *,void *),square_root(float);
extern u64 GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *,int,int);
extern char g_camera_pose_buffer[];
typedef float ReflectUV[2];
extern ReflectUV g_reflect_uvs[57];
extern float g_reflect_vertices[57][4];
extern float g_reflect_source_vertices[57][4],g_reflect_normals[57][4],g_reflect_points[42][4],g_reflect_centers[42][4],g_reflect_uv_table[][2];
extern short g_reflect_index_table[42][4][2];
extern int g_effect_l03_texture_id __attribute__((sda)),g_effect_mode_field_a __attribute__((sda)),g_effect_mode_field_b __attribute__((sda)),g_effect_mode_field_c __attribute__((sda)),g_effect_mode_field_d __attribute__((sda)),g_effect_mode_field_e __attribute__((sda)),g_effect_packet_color __attribute__((sda));
extern float g_reflect_vector_length __attribute__((sda));
typedef struct {
 float position[4][4];
 int color0,color1,color2,color3;
 float uv[4][2];
 u64 zero, texture, mode, blend;
} ReflectPacket;
typedef struct {char pad[0x140];float pos[4];} ReflectCamera;
extern ReflectCamera g_hero_l03_state_alias;

/* Transform src by the matrix into dst (RAC1 TransformPoint). */
static inline void TransformPoint(float *dst,void *src,void *m)
{
    transform_vector(dst,src,m);
}

/* Draws the reflective container moby: 57 vertices, 42 faces (RAC1 draw_gadgebot_spawn_container). */
void DrawGadgebotSpawnContainer(char *moby){
 ReflectPacket packet __attribute__((aligned(16)));
 typedef unsigned int ReflectQ __attribute__((mode(TI)));
 typedef union {float f[4];ReflectQ q;} ReflectVec;
 typedef struct {ReflectVec row[4];} ReflectMatrix;
 ReflectMatrix transform;
 ReflectVec dir,normal,reflected,temp;
 float (*verts)[4];
 int near=0,i,j,index;float scale,denom;u64 flags;
 scale=F(moby,0x2c)/F(*(char **)(moby+0x24),0x24);
 vec_scale_to_length(transform.row[0].f,moby+0xc0,scale);vec_scale_to_length(transform.row[1].f,moby+0xd0,scale);vec_scale_to_length(transform.row[2].f,moby+0xe0,scale);
 transform.row[3].f[0]=F(moby,0x10);transform.row[3].f[1]=F(moby,0x14);transform.row[3].f[2]=F(moby,0x18);transform.row[3].f[3]=1;
 if(math_fabs(g_hero_l03_state_alias.pos[0]-F(moby,0x10))<16&&math_fabs(g_hero_l03_state_alias.pos[1]-F(moby,0x14))<16)near=1;
 if(near!=0){
 ReflectUV *uv=g_reflect_uvs;
 for(i=0;i<57;i++,uv++){
 verts=g_reflect_vertices;
 transform_vector(verts[i],g_reflect_source_vertices[i],&transform);
 FastVecSub(dir.f,verts[i],g_camera_pose_buffer);vec_scale_to_length(dir.f,dir.f,1);
 transform_vector(reflected.f,g_reflect_normals[i],&transform);
 vec_scale_to_length(reflected.f,reflected.f,g_reflect_vector_length);
 denom=FastVecDot(reflected.f,dir.f);FastVecScale(temp.f,reflected.f,denom+denom);
 FastVecSub(temp.f,dir.f,temp.f);vec_scale_to_length(temp.f,temp.f,1);
 temp.f[2]+=1;
 denom=square_root(temp.f[2]+temp.f[2]);
 denom+=denom;
 {float u=temp.f[0]/denom;
 float v=temp.f[1]/denom;
 (*uv)[1]=v+0.5f;(*uv)[0]=u+0.5f;}
 }
 }else{
 for(i=0;i<57;i++){transform_vector(g_reflect_vertices[i],g_reflect_source_vertices[i],&transform);}
 }
  /* Dead store: keeps gcse's reaching register for the table's high half alive until cse2,
    so both preheaders share it (flow then deletes this statement). */
 verts=g_reflect_vertices;
 {u64 texture=GetEffectTextureDescriptor(g_effect_l03_texture_id);
 flags=(u64)g_effect_mode_field_a;
 flags|=(u64)g_effect_mode_field_b<<2;
 flags|=(u64)g_effect_mode_field_c<<4;
 flags|=(u64)g_effect_mode_field_d<<6;
 flags|=(u64)g_effect_mode_field_e<<32;
 packet.texture=texture;packet.mode=0x0000ff9000000260ULL;packet.blend=flags;}
 packet.zero=0;
 packet.color3=g_effect_packet_color;
 packet.color2=g_effect_packet_color;
 packet.color1=g_effect_packet_color;
 packet.color0=g_effect_packet_color;
 i=0;
 do{
 float *center=normal.f;
 TransformPoint(center,g_reflect_points[i],&transform);
 FastVecSub(dir.f,center,g_camera_pose_buffer);vec_scale_to_length(dir.f,dir.f,1);
 matrix_mul_vec3(center,g_reflect_centers[i],&transform);
 if(!(0.0f<FastVecDot(dir.f,center))){
 short *idx=g_reflect_index_table[i][0];
 for(j=0;j<4;j++,idx+=2){
 index=idx[0];qcopy(packet.position[j],g_reflect_vertices[index]);
 if(near){packet.uv[j][0]=g_reflect_uvs[index][0];packet.uv[j][1]=g_reflect_uvs[index][1];}
 else {packet.uv[j][0]=g_reflect_uv_table[idx[1]][0];packet.uv[j][1]=g_reflect_uv_table[idx[1]][1];}
 }
 draw_world_quad(&packet,0,0);
 }
 i++;
 }while(i<42);
}
