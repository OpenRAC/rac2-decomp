#include "common.h"
#include "include_asm.h"

extern int D_001A72E0;

extern int D_001A72E0_1;

extern short g_screen_adjust_offsets[];

extern void VU1_addGSregister(int id, long long value);

extern void gfx_draw_colored_rectangle(int a, int b, int c, int d, int e);

extern char g_fading_moby_list[];

extern int g_fading_moby_count;

extern void mem_fast_helper_b(char *buf, int size);

/* Draws a white screen flash over the whole screen, using the blast's current brightness. */
void blast_draw_screen_flash(char *object)
{
    char *s1;

    s1 = *(char **)(object + 0x68);
    if (*(int *)(s1 + 0x24) != 0) {
        VU1_addGSregister(0x4E, (((long long)(D_001A72E0 >> 13) | 0x1000000) | (1LL << 32)));
        gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], (*(int *)(s1 + 0x24) << 24) | 0xFFFFFF);
        VU1_addGSregister(0x4E, (D_001A72E0_1 >> 13) | 0x1000000);
    }
}

/* Empties the list of fading objects. */
void moby_clear_fading_list(void)
{
    mem_fast_helper_b(g_fading_moby_list, 0x800);
    g_fading_moby_count = 0;
}

typedef float QuadVector[4] __attribute__((aligned(16)));

extern int D_L00_001B05E0 __attribute__((sda));
extern int D_L00_001B05E4 __attribute__((sda));
extern int D_L00_001B05E8 __attribute__((sda));
extern int D_L00_001B05EC __attribute__((sda));
extern int D_L00_001B05F0 __attribute__((sda));
extern int D_L00_001B05F4 __attribute__((sda));
extern int D_L00_001B05F8 __attribute__((sda));
extern float D_L00_001B05FC __attribute__((sda));
/* 64 quads of a shared mesh: per corner, a vertex index and a texture-coordinate index. */
extern short D_L00_00297020[][4][2];
extern QuadVector D_L00_00296B20[];
extern float D_L00_00297420[][2];
extern unsigned long long GetEffectTextureDescriptor(int);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern void ref_L00_003E5710_00(void *, void *, int);
extern void ref_L00_003E5978_00(void *, void *, int);

/* Draws the 64-quad mesh at OBJECT: every corner of the shared vertex table is scaled by the
   state's size (doubled on the first two axes, a quarter on the third), turned by the object's
   matrix, moved to its position and offset by the vector the helper leaves in matrix[3], which
   is halved at every corner. */
void blast_draw_ring_mesh_large(char *object)
{
    QuadVector vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long long registers[4];
    QuadVector matrix[4];
    char *state = *(char **)(object + 0x68);
    int quad, corner;
    float *first_u, *first_v;

    registers[1] = GetEffectTextureDescriptor(D_L00_001B05F4);
    registers[2] = 0xFF9000000260ULL;
    registers[3] = D_L00_001B05E0 | (unsigned long long)D_L00_001B05E4 << 2;
    registers[3] |= (unsigned long long)D_L00_001B05E8 << 4;
    registers[3] |= (unsigned long long)D_L00_001B05EC << 6;
    registers[3] |= (unsigned long long)D_L00_001B05F0 << 32;
    registers[0] = 0;
    vec_clear_128(matrix[0]);
    vec_clear_128(matrix[1]);
    vec_clear_128(matrix[2]);
    matrix[0][0] = *(float *)(state + 0x10) * 2.0f;
    matrix[1][1] = *(float *)(state + 0x10) * 2.0f;
    matrix[2][2] = *(float *)(state + 0x10) * 0.25f;
    colors[0] = colors[1] = colors[2] = colors[3] = D_L00_001B05F8 + (*(int *)(state + 0x24) << 24);
    ref_L00_003E5710_00(object + 0x10, matrix[3], 1);
    first_u = &uv[0][0];
    first_v = &uv[0][1];
    quad = 0;
    do {
        float *u, *v;

        v = first_v;
        u = first_u;
        for (corner = 0; corner < 4; corner++) {
            int vertex = D_L00_00297020[quad][corner][0];
            int texel = D_L00_00297020[quad][corner][1];

            FastVecScale(vertices[corner], D_L00_00296B20[vertex], D_L00_001B05FC);
            *u = D_L00_00297420[texel][0];
            *v = D_L00_00297420[texel][1];
            matrix_mul_vec3(vertices[corner], vertices[corner], matrix);
            matrix_mul_vec3(vertices[corner], vertices[corner], object + 0xC0);
            FastVecAdd(vertices[corner], vertices[corner], object + 0x10);
            vec_scale_to_length(matrix[3], matrix[3], 0.5f);
            FastVecAdd(vertices[corner], vertices[corner], matrix[3]);
            u += 2;
            v += 2;
        }
        draw_world_quad(vertices, 0, 0);
    } while (++quad < 64);
}

/* The same mesh at the state's size (an eighth on the third axis); the position pointer is
   taken again for every quad. */
/* Draws a smaller copy of the blast mesh, a flatter shell at the blast's size. */
void blast_draw_ring_mesh_small(char *object)
{
    QuadVector vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long long registers[4];
    QuadVector matrix[4];
    char *state = *(char **)(object + 0x68);
    int quad, corner;
    char *position;
    float *first_u, *first_v;

    registers[1] = GetEffectTextureDescriptor(D_L00_001B05F4);
    registers[2] = 0xFF9000000260ULL;
    registers[3] = D_L00_001B05E0 | (unsigned long long)D_L00_001B05E4 << 2;
    registers[3] |= (unsigned long long)D_L00_001B05E8 << 4;
    registers[3] |= (unsigned long long)D_L00_001B05EC << 6;
    registers[3] |= (unsigned long long)D_L00_001B05F0 << 32;
    registers[0] = 0;
    vec_clear_128(matrix[0]);
    vec_clear_128(matrix[1]);
    vec_clear_128(matrix[2]);
    matrix[0][0] = *(float *)(state + 0x10) * 1.0f;
    matrix[1][1] = *(float *)(state + 0x10) * 1.0f;
    matrix[2][2] = *(float *)(state + 0x10) * 0.125f;
    colors[0] = colors[1] = colors[2] = colors[3] = D_L00_001B05F8 + (*(int *)(state + 0x24) << 24);
    ref_L00_003E5978_00(object + 0x10, matrix[3], 1);
    first_u = &uv[0][0];
    first_v = &uv[0][1];
    quad = 0;
    do {
        float *u, *v;

        position = object + 0x10;
        v = first_v;
        u = first_u;
        for (corner = 0; corner < 4; corner++) {
            int vertex = D_L00_00297020[quad][corner][0];
            int texel = D_L00_00297020[quad][corner][1];

            FastVecScale(vertices[corner], D_L00_00296B20[vertex], D_L00_001B05FC);
            *u = D_L00_00297420[texel][0];
            *v = D_L00_00297420[texel][1];
            matrix_mul_vec3(vertices[corner], vertices[corner], matrix);
            matrix_mul_vec3(vertices[corner], vertices[corner], object + 0xC0);
            FastVecAdd(vertices[corner], vertices[corner], position);
            vec_scale_to_length(matrix[3], matrix[3], 0.5f);
            FastVecAdd(vertices[corner], vertices[corner], matrix[3]);
            u += 2;
            v += 2;
        }
        draw_world_quad(vertices, 0, 0);
    } while (++quad < 64);
}

typedef int TI4BF0 __attribute__((mode(TI)));
typedef float Vec4BF0[4] __attribute__((aligned(16)));
typedef struct { char prefix[0x74]; float damage; char tail[0x68]; } Weapon4BF0;
extern Weapon4BF0 g_weapon_l00_table[] __attribute__((nosda));
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad[0x2290]; char *target; } Hero4BF0;
extern Hero4BF0 g_hero_state;
typedef struct { char pad[0x160]; float amount; int unused, timer, state; } Camera4BF0;
extern Camera4BF0 D_L00_001B8C80;
extern char *D_L00_001B2B50 __attribute__((sda));
extern char *D_L00_001B2B54;
extern int *D_L00_001B2B58[] MACRO_ADDR;
extern float D_L00_001B05D4 __attribute__((sda));
extern float D_L00_001B05D8 __attribute__((sda));
extern char *D_L00_001B2B50_1 MACRO_ADDR;
extern char *g_area_hit_targets[];
extern int save_is_record_value(short,int);
extern void vec_transform_or_copy(void *,void *);
extern int AcquireEntitySlot(void *,int,void *);
extern char *level_get_slot_body(short,int);
extern int mem_align_size_16(int);
extern void cam_compute_view_direction(void *,void *,int);
extern void FastVecAdd(void *,void *,void *);
extern void part_spawn_explosion_with_sparks(void *,void *,int,float,float);
extern void blast_init_effect_record(void *,int,void *,void *,float);
extern void part_spawn_blast_sparks(void *,void *);
extern int math_fast_helper_a(void *,float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int coll_process_hit(void *,int,void *,int,float);
extern char *moby_get_private_value_0(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void make_hit_descriptor(float,void *,void *,int,void *);
extern void QueueMobyImpact(void *,void *);
extern int StartAttachedEffect(void *,int,int);
extern int math_fast_float_d(void *);
extern void blast_clear_state(void);
extern void moby_mark_spawned(void *);
extern void blast_update_effect_records(void *);
extern void ref_L00_003E4BF0_00(void (*)(void *),void *);
extern void mini_nuke_blast_draw(void *);
typedef struct { char pad[0x10]; float phase; int timer; float rate; int alpha, unused, count, handle; } State4BF0;
/* Updates the Mini-Nuke blast: it grows, hurts everything inside its radius, shakes the camera, then fades out and removes itself. */
void mini_nuke_blast_update(char *object)
{
    Vec4BF0 center, offset, query, direction;
    struct { Vec4BF0 point; char pad[8]; unsigned char type, flags; short id; int unused; int active; } hit;
    int allocation;
    int *timer;
    State4BF0 *data = *(State4BF0 **)(object+0x68);
    float scale;
    if (*(unsigned char *)(object+0x20) && !save_is_record_value(*(short *)(object+0xAA),data->handle)) goto destroy;
    vec_transform_or_copy(object+0x10,object+0x10);
    switch (*(unsigned char *)(object+0x20)) {
    case 0: {
        int i;
        char *mem;
        *(unsigned char *)(object+0x20)=1;
        data->phase=0;
        data->timer=20;
        data->rate=2.0f/3.0f;
        data->alpha=127;
        data->count=111;
        data->handle=AcquireEntitySlot(object,0,&allocation);
        mem=level_get_slot_body(*(short *)(object+0xAA),data->handle);
        D_L00_001B2B50=mem;
        D_L00_001B2B54=(char *)mem_align_size_16((int)(mem+0x50));
        D_L00_001B2B58[0]=(int *)mem_align_size_16((int)(D_L00_001B2B54+0xA000));
        i=0;
        do { D_L00_001B2B58[0][i]=0; i++; } while(i<144);
        { char *p = D_L00_001B2B54+319*128+124;
        for(i=319;i>=0;i--,p-=128) *(int *)p=0; }
        *(int *)(D_L00_001B2B50_1+0x30)=0;
        qcopy(center,object+0x10);
        cam_compute_view_direction(object+0x10,offset,1);
        FastVecAdd(center,object+0x10,offset);
        part_spawn_explosion_with_sparks(object,center,-1,2.0f,20.0f);
        blast_init_effect_record(object,20,object+0x10,data,1.0f/6.0f);
        part_spawn_blast_sparks(object,object+0x10);
        qcopy(query,center);
        query[3]=2.0f;
        if(math_fast_helper_a(query,100.0f)!=-1) {
            D_L00_001B8C80.amount=0.45f;
            D_L00_001B8C80.timer=40;
            D_L00_001B8C80.state=0;
        }
    }
    case 1: {
        int count;
        int i;
        data->count-=5;
        if(data->count<0) data->count=0;
        data->phase+=data->rate;
        timer=&data->timer;
        scale=1.0f-IntToFloat(*timer)/IntToFloat(20);
        scale*=8.0f;
        count=coll_process_hit(object+0x10,0,object,0,scale+0.001f);
        for(i=0;i<count;i++) {
            if((moby_get_private_value_0(g_area_hit_targets[i]) || (*(unsigned short *)(g_area_hit_targets[i]+0x34)&0x4000)) && g_area_hit_targets[i]!=g_hero_state.target && *(short *)(g_area_hit_targets[i]+0xAA)!=MOBY_CLASS_MINI_NUKE) {
                FastVecSub(direction,g_area_hit_targets[i]+0x10,object+0x10);
                vec_scale_to_length(direction,direction,1.0f);
                vec_scale_to_length(&hit,&hit,1.0f);
                make_hit_descriptor(((Weapon4BF0 *)((unsigned int)g_weapon_l00_table + g_item_slot_to_record[0x2A] * sizeof(Weapon4BF0)))->damage,&hit,object,0x830000,direction);
                *(TI4BF0 *)hit.point = *(TI4BF0 *)direction;
                hit.flags=3; hit.type=5; hit.active=1;
                hit.point[3]=5627.925f;
                hit.id=*(short *)(g_area_hit_targets[i]+0xAA);
                QueueMobyImpact(g_area_hit_targets[i],&hit);
                StartAttachedEffect(g_area_hit_targets[i],71,*(int *)(object+0xB8));
            }
        }
        if(math_fast_float_d(timer)) {
            *(unsigned char *)(object+0x20)=2;
            data->timer=40;
        }
        break;
    }
    case 2:
        data->phase+=data->rate;
        scale=IntToFloat(data->timer)*0.025f;
        if(data->timer==20) part_spawn_blast_sparks(object,object+0x10);
        if(math_fast_float_d(&data->timer)) {
            if(data->alpha) --data->alpha;
            else { data->alpha=0; *(unsigned char *)(object+0x20)=6; }
        } else data->alpha=FloatToInt(IntToFloat(127)*scale);
        break;
    case 6:
        data->rate-=0.016666668f;
        if(data->rate<1.0f/12.0f) data->rate=1.0f/12.0f;
        data->phase+=data->rate;
        if(!*(int *)(D_L00_001B2B50_1+0x38)) {
destroy:
            blast_clear_state();
            moby_mark_spawned(object); return;
        }
        break;
    }
    D_L00_001B05D8-=0.04f;
    if(D_L00_001B05D4 < -8.0f) D_L00_001B05D4+=8.0f;
    if(D_L00_001B05D8 < -8.0f) D_L00_001B05D8+=8.0f;
    blast_update_effect_records(object);
    ref_L00_003E4BF0_00(mini_nuke_blast_draw,object);
}
