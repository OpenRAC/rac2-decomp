#include "names.h"
/* Spawns a bolt effect moby (class 0xCF7) from a position and velocity: the state block holds its
   frame count and rate, its fade, and a slot from a three-way counter; mode 1 aims it at the camera,
   mode 2 first steps it once and flags a hit. Needs -g (pre-div.s nop pair). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int save_is_record_value(int,int);
extern char *CreateMoby(int);
extern void vec_add_transformed_or_copy(void *,void *,void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern char *level_get_slot_body(int,int);
extern void cam_compute_view_direction(void *,void *,int);
extern void FastVecScale(void *,void *,float);
extern void moby_build_axes(char *,char *);
extern void vaporizer_bolt_start_trail_sample(char *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int vaporizer_bolt_test_hit(char *,char *);
extern unsigned char g_beam_weapon_index[];
typedef struct { char prefix[0x50]; float speed; char gap[0x1c]; float distance; char rest[0x6c]; } Tuning;
extern Tuning g_weapon_l00_table[];
extern unsigned short g_vaporizer_bolt_fade_frames __attribute__((sda));
extern unsigned int g_vaporizer_bolt_slot_counter __attribute__((sda));
extern char g_camera_l00_position[];
/* Only the measured header fields are viewed; this is not a whole-object size. */
typedef struct { char prefix[0x30]; unsigned char stamp,enabled; short tag; } HeaderView;
typedef struct {
    char pad00[0x10];
    int frames;
    float rate;
    short slot, id;
    char *target;
    short age, fadeFrames;
    float fadeRate;
    int mode;
    char pad2C[4];
    TI128 velocity, origin;
} BoltState;

/* Fires a Vaporizer bolt. It creates the bolt moby (class 3319) and sets its speed, lifetime,
   fade and trail slot. Returns the moby, or null if it cannot be made. */
char *vaporizer_bolt_spawn(char *position,char *velocity,int id,int mode)
{
    TI128 direction, previous;
    char *object,*location;
    BoltState *state;
    float frames;
    HeaderView *header;
    unsigned char stamp;
    int next;
    if (id == -1 || save_is_record_value(MOBY_CLASS_VAPORIZER,id) == 0) return 0;
    object=CreateMoby(0xcf7 /* moby class 3319 */);
    if (object != 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(unsigned short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x31) = 1;
        location=object+0x10;
        state=*(BoltState **)(object+0x68);
        qcopy(location,position);
        object[0x20]=0;
        vec_add_transformed_or_copy(state,velocity,position);
        frames=0.016666668f * (g_weapon_l00_table + g_beam_weapon_index[0])->speed;
        state->frames=FloatToInt(128.0f / frames);
        /* Call and division in one statement: retail has no line label between them,
           so no division padding (docs/build/compiler-notes.md). */
        state->rate=1.0f/IntToFloat(state->frames);
        state->id=id;
        state->target=level_get_slot_body(MOBY_CLASS_VAPORIZER,id);
        state->age=0;
        state->fadeFrames=g_vaporizer_bolt_fade_frames;
        state->fadeRate=1.0f/IntToFloat(state->fadeFrames);
        state->mode=mode;
        cam_compute_view_direction(location,&direction,1);
        FastVecScale(&direction,&direction,-1.0f);
        moby_build_axes(object,(char *)&direction);
        if (g_vaporizer_bolt_slot_counter > 3) g_vaporizer_bolt_slot_counter=0;
        state->slot=g_vaporizer_bolt_slot_counter;
        g_vaporizer_bolt_slot_counter=((int)(g_vaporizer_bolt_slot_counter+1))%3;
        vaporizer_bolt_start_trail_sample(object);
        if (mode == 1) {
            qcopy(&state->origin,g_camera_l00_position);
            vec_scale_to_length(&state->velocity,g_camera_l00_position + 0x230,FastVecLength(velocity));
        }
        if (mode == 2) {
            qcopy(&previous,position);
            FastVecAdd(location,position,velocity);
            if (vaporizer_bolt_test_hit(object,(char *)&previous) != 0) object[0x20]=2;
        }
    }
    return object;
}
