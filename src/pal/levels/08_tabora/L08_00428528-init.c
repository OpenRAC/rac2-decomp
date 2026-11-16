#include "include_asm.h"

#include "common.h"
typedef struct Ent Ent;
typedef int V4 __attribute__((mode(TI)));
typedef struct {
    u8 pad0[0x28];
    unsigned char unk_28;
    unsigned char unk_29;
    u8 pad2A[0x6];
    float unk_30;
    u8 pad34[0x14];
    unsigned char unk_48;
    u8 pad49[0x1];
    unsigned char unk_4A;
    u8 pad4B[0x15];
    unsigned char unk_60;
    unsigned char unk_61;
    unsigned char unk_62;
    u8 pad63[0x3];
    unsigned char unk_66;
    unsigned char unk_67;
    u8 pad68[0x2];
    unsigned char unk_6A;
    u8 pad6B[0x1];
    float unk_6C;
    float unk_70;
    float unk_74;
    float unk_78;
    float unk_7C;
    float unk_80;
    float unk_84;
    short unk_88;
    u8 pad8A[0x2];
    float unk_8C;
    u8 pad90[0x8];
    int unk_98;
    u8 pad9C[0x20];
    unsigned char unk_BC;
    unsigned char unk_BD;
    unsigned char unk_BE;
    unsigned char unk_BF;
    u8 padC0[0x2];
    unsigned char unk_C2;
    unsigned char unk_C3;
    unsigned char unk_C4;
    u8 padC5[0x1];
    unsigned char unk_C6;
    u8 padC7[0x95];
    float unk_15C;
    u8 pad160[0x28];
    unsigned char unk_188;
    unsigned char unk_189;
    unsigned char unk_18A;
    u8 pad18B[0x5];
    int unk_190;
    int unk_194;
    int unk_198;
    int unk_19C;
    int unk_1A0;
    int unk_1A4;
    int unk_1A8;
    u8 pad1AC[0x4];
    float unk_1B0;
    u8 pad1B4[0xA];
    short unk_1BE;
    float unk_1C0;
} InitState1348;
extern int FloatToInt(f32);
extern f32 math_random_float_range(f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void vehicle_compute_height_limits(Ent *);
extern int g_frame_l08_counter[] __attribute__((sda));
extern void *g_path_list_table[];
extern float coll_point_depth_in_volumes(void *, int, int, int, int);
extern float path_l01_compute_segment_lengths(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void sandfly_pick_random_target(Ent *);

/* Sets up a new Mutant Sandfly: its health, sizes, timers and start position, and its first state (PAL: 50 Hz timings). */
void sandfly_init_pal(u8 *object)
{
    InitState1348 *state = *(InitState1348 **)(object + 0x68);
    float position[4], radius;
    state->unk_48 = FloatToInt(15.0f);
    state->unk_4A = FloatToInt(3.2f);
    state->unk_29 = 1;
    if (!g_frame_l08_counter[0]) **(int **)((char *)state+0x1CC)=0;
    qcopy((char *)state+0x150,object+0x10);
    vehicle_compute_height_limits((Ent *)object);
    *(float *)(object+0x18)=state->unk_1B0;
    qcopy((char *)state+0x150,object+0x10);
    state->unk_188=object[0x30];
    *(V4 *)position=*(V4 *)(object+0x10);
    radius=coll_point_depth_in_volumes(position,state->unk_190,state->unk_198,state->unk_194,-1);
    if(radius>0) object[0x30]=FloatToInt(radius+2.0f);
    state->unk_188=state->unk_189=object[0x30];
    *(V4 *)position=*(V4 *)(object+0x10);
    radius=coll_point_depth_in_volumes(position,state->unk_19C,state->unk_1A4,state->unk_1A0,-1);
    if(radius>0) state->unk_188=FloatToInt(radius+2.0f);
    if(state->unk_1A8!=-1) path_l01_compute_segment_lengths(g_path_list_table[state->unk_1A8]);
    *(void **)((char *)state+0x10)=(char *)state+0x50;
    state->unk_60=9; state->unk_98=-1;
    state->unk_88=0; state->unk_6A=0;
    state->unk_62=state->unk_61=255; state->unk_67=state->unk_66=5;
    state->unk_6C=0.3f; state->unk_70=0.16000001f;
    state->unk_74=0.006f; state->unk_78=0.012f;
    state->unk_7C=0.004f; state->unk_80=0.3f;
    state->unk_8C=0.4f;
    state->unk_84=0;
    state->unk_BC=1; state->unk_BD=3; state->unk_BE=1; state->unk_BF=3; state->unk_C2=1; state->unk_C3=3; state->unk_C6=1; state->unk_C4=0;
    state->unk_1BE=0; state->unk_28=0; state->unk_30=0;
    qcopy((char *)state+0x160,object+0x10);
    state->unk_1C0=0;
    switch((unsigned char)state->unk_18A) {
    case 0:
        *(float *)(object+0x18)=state->unk_1B0-1.7f;
        qcopy((char *)state+0x150,object+0x10); qzero_nc((char *)state+0x170);
        *(unsigned short *)(object+0x34)&=0xEFFF;
        if((unsigned char)object[0x43]!=1) anim_start_blended_pal(object,1,0,3);
        object[0x31]=0; *(unsigned short *)(object+0x34)|=1;
        moby_set_state(object,1,-1); break;
    case 1:
        *(float *)(object+0x18)=state->unk_1B0+2.7f;
        qcopy((char *)state+0x150,object+0x10); qzero_nc((char *)state+0x170);
        sandfly_pick_random_target((Ent *)object);
        *(unsigned short *)(object+0x34)|=0x1000;
        if((unsigned char)object[0x43]!=1) anim_start_blended_pal(object,1,0,3);
        moby_set_state(object,6,0); break;
    case 2:
        qcopy((char *)state+0x170,(char *)state+0xD0);
        FastVecAdd(object+0x10,object+0x10,(char *)state+0x170);
        qcopy((char *)state+0x150,object+0x10);
        if((unsigned char)object[0x43]!=5) anim_start_blended_pal(object,5,0,3);
        object[0x31]=1;
        *(unsigned short *)(object+0x34)=(*(unsigned short *)(object+0x34)|0x1000)&0xFFFE;
        moby_set_state(object,4,-1); break;
    }
    state->unk_15C=math_random_float_range(0,1);
}
