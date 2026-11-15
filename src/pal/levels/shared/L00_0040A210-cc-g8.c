/* func_PAL_L00_0040A210, the PAL copy of func_L00_00405808: the same C, where the frame counts 40, 15, 30 and 20 become 33, 12, 25 and 17, 0.016666668f becomes 0.020000001f, the time compared with and stored in best takes the 50 Hz scale, and five callees take their PAL names. */
#include "common.h"

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) Vec;
typedef struct {
    char pad0[0x730]; float basis[12];
    char pad760[0x1230-0x760]; int buttons;
    char pad1234[0x1244-0x1234]; int itemState;
    char pad1248[0x2290-0x1248]; char *object; int current;
    int pad2298; unsigned int control;
    char pad22a0[0x24ec-0x22a0]; short direction;
    char pad24ee[0x2534-0x24ee]; int timer;
} Hero;
typedef struct { char pad[0x360]; unsigned short kills, pad362; unsigned int best, levels; } Stats;
typedef struct { int present; unsigned char type; char pad[219]; } Upgrade;
typedef struct { float color[4]; float pos[3]; float radius; } Light;
typedef struct { float pos[4]; char *target; float total, left; short timer, seen;
    char pad20[0x44-0x20]; int delay; float yaw,pitch; } Ray;
typedef struct { char pad0[0x74]; unsigned char playing; char pad75[0x88-0x75]; char *owner; } Voice;
extern Hero g_hero_state;
extern Stats D_0018C360;
typedef struct { unsigned char pad0[0x10]; unsigned char current; unsigned char pad11[0x48-0x11]; unsigned char equipped; } Inventory;
extern Inventory g_item_slot_to_record;
extern char g_sound_state[];
extern Upgrade g_weapon_l00_table[];
extern char D_L00_001B8C80[];
extern Light D_L00_001C6F40[];
extern int D_001A7390 MACRO_ADDR, g_current_map_index MACRO_ADDR;
extern unsigned char D_001A7A60[32] __attribute__((sda));
extern int D_00138320 __attribute__((nosda));
extern int D_L00_001B2C74 MACRO_ADDR;
extern int D_L00_001B2C78 MACRO_ADDR;
extern int D_L00_001B2C7C MACRO_ADDR;

extern int D_L00_001B0E30 __attribute__((sda));
extern float D_L00_001B0E3C __attribute__((sda));
extern float D_L00_001B0E48 __attribute__((sda));
extern int D_L00_001B2C70 __attribute__((sda));
extern int D_L00_001A903C;
extern float moby_get_anim_value(void *);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern s32 func_PAL_L00_002C4480(int,int);
extern void copy_matrix3x4(void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern void transform_vector(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float mat_fast_helper_a(float,float);
extern float vec_length_xy(void *);
extern char *sheepinator_find_target(void *,void *,void *,void *);
extern char *moby_get_private_value_0(void *);
extern float IntToFloat(int);
extern void gauge_popup_show(int,int,int,float);
extern int snd_play_from_global_bank(int,int,void *);
extern void func_PAL_002B1588(int,int);
extern int PlayMobySound(int,int,void *);
extern void *func_PAL_L00_0040D328(void *);
extern void func_PAL_L00_0040AB80(void *);
extern int gfx_add_point_light(void *,float,float,unsigned int);
extern void vec_scale_to_length(void *,void *,float);
extern int snd_is_voice_playing_for_owner(void *,int);
extern void gfx_free_point_light(int);
extern void snd_stop_voice(int);
extern void anim_start_blended_with_flags(void *,int,int,int,int);

void func_PAL_L00_0040A210(char *object)
{
    Vec offset;
    Vec direction;
    Vec matrix[3];
    Vec basis[4];
    Ray *state=*(Ray **)(object+0x68);
    char *target, *info; Light *entry;
    int special=0;
    float rate, value;
    int index;
    int boosted;
    int near;
    if (g_hero_state.itemState==3) special=1;
    if (!B(object,0x20)) {
        B(object,0x20)=1;
        D_L00_001B2C74=-1;
        D_L00_001B2C7C=-1;
        D_L00_001B2C78=0;
    }
    /* RAC1 also gates the beam on near; here nothing reads it, so only the call survives. */
    near=1;
    if (!B(object,0x43) && moby_get_anim_value(object)<6.0f) near=0;
    {
    Hero *player=&g_hero_state;
    int permitted=1;
    if (player->current==29) { if (!math_fast_float_d(&player->timer)) permitted=0; }
    else g_hero_state.timer=33;
    FastDecTimer(&state->timer);
    if ((unsigned int)g_hero_state.control<2 && (D_00138320&g_hero_state.buttons) && permitted) {
        if (B(object,0x43)!=2) func_PAL_002A7E68(object,2,0,0);
        if (!state->seen) {
            state->seen=1;
            if (D_0018C360.kills<65535) D_0018C360.kills++;
            if ((unsigned int)(((s32)(D_001A7390) * 5 + 2) / 6)>D_0018C360.best) D_0018C360.best=((s32)(D_001A7390) * 5 + 2) / 6;
            D_0018C360.levels = (D_0018C360.levels | (1<<g_current_map_index)) | 0x80000000;
        }
        if (!state->timer) state->timer=12;
        *(Quad *)&offset=0;
        offset.x=0.15f; offset.y=-1.0f; offset.z=0.06f; offset.w=1.0f;
        matrix_mul_vec3(&offset,&offset,object+0xc0);
        FastVecAdd(state,object+0x10,&offset);
        if (g_hero_state.current==1) func_PAL_L00_002C4480(29,1);
        *(Quad *)&direction=0;
        if (g_hero_state.current==29 && (U(g_hero_state.object,0x34)&1)) {
            copy_matrix3x4(matrix,D_L00_001B8C80);
            matrix_from_basis_rows(basis,matrix);
            direction.z=1.0f;
            transform_vector(&direction,&direction,basis);
        } else if (g_hero_state.direction==1) FastVecScale(&direction,object+0xd0,-1.0f);
        else {
            direction.x=1.0f;
            matrix_mul_vec3(&direction,&direction,g_hero_state.basis);
        }
        state->yaw=mat_fast_helper_a(direction.x,direction.y);
        value=vec_length_xy(&direction);
        state->pitch=mat_fast_helper_a(value,direction.z);
        *(Quad *)matrix=*(Quad *)state;
        target=sheepinator_find_target(object,matrix,&state->yaw,&state->pitch);
        math_fast_float_d(&state->delay);
        if (state->target) {
            if (B(state->target,0x20)==254) goto clear_target;
            if (B(state->target,0x20)==253) {
clear_target:
                state->target=0; state->delay=0;
            }
        }
        if (target || state->delay) {
            if (target) {
                info=moby_get_private_value_0(target);
                if (target!=state->target && !state->delay) {
                    state->target=target;
                    state->total=IntToFloat(H(info,4));
                    state->left=F(info,0);
                    state->delay=25;
                    if (state->total<=1.0f) state->left=0;
                }
            }
            {
            Inventory *inventory=&g_item_slot_to_record;
            Upgrade *upgrades=g_weapon_l00_table;
            rate=1.0f;
            if (upgrades[inventory->equipped].type) rate=1.33f;
            boosted=upgrades[inventory->current].present!=0 && upgrades[inventory->current].type==3;
            }
            D_L00_001B0E3C=boosted?50.0f:12.5f;
            state->left-=D_L00_001B0E3C*(rate*0.020000001f);
            if (state->left<0.0f) state->left=0.0f;
            D_L00_001B0E48=state->left/state->total;
        } else D_L00_001B0E48=1.0f;
        gauge_popup_show(1,0x60000000,0,D_L00_001B0E48);
        if (state->target && state->left<=0.0f) {
            int oclass=H(state->target,0xaa);
            if (g_current_map_index==12 && oclass==4020) {
                if (++D_L00_001B0E30>=16 && !D_001A7A60[22]) {
                    D_001A7A60[22]=1; snd_play_from_global_bank(1,0,0); func_PAL_002B1588(4659,-1); D_L00_001A903C=1;
                }
            }
            PlayMobySound(3,0,object);
            func_PAL_L00_0040D328(state->target); state->target=0;
        }
        func_PAL_L00_0040AB80(object);
        if (D_L00_001B2C74==-1) D_L00_001B2C74=gfx_add_point_light(object+0x10,7.5f,0.0f,0x207f7f);
        if (D_L00_001B2C74>=0) {
            D_L00_001B2C78=17;
            vec_scale_to_length(matrix,object+0xd0,-0.5f);
            FastVecAdd(&matrix[1],state,matrix);
            { Light *light=&D_L00_001C6F40[D_L00_001B2C74];
            float x=matrix[1].x, y=matrix[1].y, z=matrix[1].z; light->pos[0]=x; light->pos[1]=y; light->pos[2]=z; light->radius=7.5f; }
        }
        if (!snd_is_voice_playing_for_owner(object,D_L00_001B2C7C)) D_L00_001B2C7C=PlayMobySound(1,4,object);
    } else {
        state->target=0; state->seen=0; state->delay=0; D_L00_001B2C70=1;
        if (D_L00_001B2C74>=0) {
            vec_scale_to_length(&offset,object+0xd0,-0.5f);
            FastVecAdd(&direction,state,&offset);
            entry=&D_L00_001C6F40[D_L00_001B2C74];
            { float x=direction.x, y=direction.y, z=direction.z; entry->pos[0]=x; entry->pos[1]=y; entry->pos[2]=z; entry->radius=7.5f; }
            value=IntToFloat(D_L00_001B2C78)*0.05f;
            entry=&D_L00_001C6F40[D_L00_001B2C74];
            entry->color[0]=value; entry->color[1]=value; entry->color[2]=value*0.25f;
            if (math_fast_float_d(&D_L00_001B2C78)) { gfx_free_point_light(D_L00_001B2C74); D_L00_001B2C74=-1; }
        }
    if (D_L00_001B2C74>=0 && !D_L00_001B2C78) { gfx_free_point_light(D_L00_001B2C74); D_L00_001B2C74=-1; }
    index=D_L00_001B2C7C;
    if (index>=0) {
        if (index!=-1 && ((Voice *)(g_sound_state+index*112))->owner==object && ((Voice *)(g_sound_state+index*112))->playing) snd_stop_voice(index);
        D_L00_001B2C7C=-1;
    }
    if (B(object,0x60)&2) anim_start_blended_with_flags(object,1,0,1,0);
    }
    }
    if (special && D_L00_001B2C74>=0) { gfx_free_point_light(D_L00_001B2C74); D_L00_001B2C74=-1; }
}
