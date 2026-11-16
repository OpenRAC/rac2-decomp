/* Path driver with child coordination, sound phases and pose oscillation. */
#include "common.h"

typedef struct {
    u8 pad[0x50];
    s32 path0, path1, path2, trigger, child;
    u8 pad64[12];
    f32 position[4], rotation[4];
    f32 length, phase0, phase1, phase2;
    f32 progress, velocity;
    s32 timer, sound, soundTimer;
} DriverState;
typedef struct DriverObject DriverObject;
struct DriverObject {
    u8 pad00[0x10];
    float position[4];
    u8 state;
    u8 pad21[0xF];
    u8 f30;
    u8 pad31;
    u16 f32;
    u8 pad34[0xE];
    u8 animation, nextAnimation;
    u8 pad44[0x24];
    DriverState *vars;
    u8 pad6C[0x84];
    float rotation[4];
};
/* Partial sound anchor: indices advance by 0x70, independently of this view. */
typedef struct {
    u8 pad[0x74];
    u8 active;
    u8 pad75[9];
    s16 kind;
    u8 pad80[8];
    DriverObject *owner;
} DriverSound;
extern u8 g_sound_state[];
extern u8 *g_moby_list_start MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern u8 *g_path_zone_table[];
extern float g_driver_sight_start_local[2] __attribute__((sda));
extern float g_driver_sight_end_local[2] __attribute__((sda));
extern float g_driver_bob_amplitude __attribute__((sda));
extern float g_driver_bob_speed __attribute__((sda));
extern float g_driver_tilt_y_amplitude __attribute__((sda));
extern float g_driver_tilt_y_speed __attribute__((sda));
extern float g_driver_tilt_x_amplitude __attribute__((sda));
extern float g_driver_tilt_x_speed __attribute__((sda));
extern float g_driver_turn_speed __attribute__((sda));
extern float g_driver_move_speed __attribute__((sda));
extern void moby_set_state(void *,int,int);
extern void anim_start_blended(void *,int,void *,int);
extern float math_random_angle(void);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern int PlayMobySound(int,int,void *);
extern float fast_vec_dist(void *,void *);
extern int math_fast_float_d(int *);
extern float math_step_value_toward_target(float *,float *,float,float,float,float);
extern void path_sample_position(void *,int,void *,void *,int,float);
extern void part_spawn_driver_spark_bursts(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern float coll_probe_ground_height_below(float,void *,int);
extern int space_tourist_launch(int,void *,void *);
extern int space_tourist_all_idle(int);
extern void moby_reset_to_saved_position(void *);
extern int moby_is_first_state(void *);
extern int path_is_at_last_point(void *);
extern u8 *part_find_owned_effect_slot(void *,int,int);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void SetDeathBits(void *,int,int);
extern void moby_mark_spawned(void *);
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_b(float);

#define SOUND_ENTRY(index) ((DriverSound *)((s32)D_00188660 + (index) * 0x70))
#define SOUND_LIVE(index) (SOUND_ENTRY(index)->owner == self && SOUND_ENTRY(index)->active)
static __inline__ void driver_clear_sound(DriverObject *self, DriverState *state)
{
    int slot = state->sound;
    if (slot != -1) {
        DriverSound *entry = SOUND_ENTRY(slot);
        if (entry->owner == self && entry->active) snd_stop_voice(slot);
    }
    state->sound = -1;
}
#define CLEAR_SOUND() driver_clear_sound(self, state)

void UpdateTodanoPathDriver(DriverObject *self)
{
    DriverState *state = self->vars;
    u8 *path;
    float sight_start[4] __attribute__((aligned(16)));
    float sight_end[4] __attribute__((aligned(16)));
    u8 *hit;
    int accepted;
    switch (self->state) {
    case 0: {
        u8 *initialPath;
        state->sound = -1;
        if (state->path0 == -1 && state->path2 == -1 && state->path1 != 0 &&
            state->trigger == -1 && state->child == -1) {
            moby_set_state(self,7,-1);
            break;
        }
        initialPath = g_path_zone_table[state->path0];
        state->length = fast_vec_dist(initialPath+0x10,initialPath+0x20);
        moby_set_state(self,3,-1);
        self->f30 = 0xff;
        self->f32 = 0xff;
        qcopy(state->position,self->position);
        qcopy(state->rotation,self->rotation);
        state->phase0 = math_random_angle();
        state->phase1 = math_random_angle();
        state->phase2 = math_random_angle();
        moby_set_state(self,1,-1);
        break;
    }
    case 1:
        if (flag_set_first_pending(self)) CLEAR_SOUND();
        if (moby_is_first_state(g_moby_list_start + (state->child << 8)))
            moby_set_state(self,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(self)) CLEAR_SOUND();
        path = g_path_zone_table[state->path0];
        math_step_value_toward_target(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     0.013888889f,0.0013888889225199819f,0.33333334f);
        path_sample_position(path,0,state->position,state->rotation,0,state->progress);
        part_spawn_driver_spark_bursts(self);
        state->rotation[1] *= -0.333f;
        if (!SOUND_LIVE(state->sound))
            state->sound = PlayMobySound(0,4,self);
        if (state->progress >= (float)(*(int *)path-1)) {
            moby_set_state(self,3,-1);
            state->timer = 60;
            if (self->nextAnimation != 1) anim_start_blended(self,1,0,30);
            CLEAR_SOUND();
            state->sound = PlayMobySound(1,0,self);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) CLEAR_SOUND();
        if (math_fast_float_d(&state->timer)) {
            matrix_mul_vec3(sight_start,g_driver_sight_start_local,(u8 *)self+0xC0);
            FastVecAdd(sight_start,sight_start,self->position);
            matrix_mul_vec3(sight_end,g_driver_sight_end_local,(u8 *)self+0xC0);
            FastVecAdd(sight_end,sight_end,self->position);
            sight_end[2] += 2.0f;
            sight_end[2] = coll_probe_ground_height_below(0.5f,sight_end,0);
            if (!space_tourist_launch(state->trigger,sight_start,sight_end)) {
                moby_reset_to_saved_position(g_moby_list_start + (state->child << 8));
                moby_set_state(self,4,-1);
                if (self->nextAnimation != 0) anim_start_blended(self,0,0,30);
                CLEAR_SOUND();
                state->sound = PlayMobySound(2,0,self);
                state->soundTimer = 15;
                state->progress = 0;
                state->velocity = 0;
            } else state->timer = 45;
        } else if (state->timer >= 46) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound) ||
                SOUND_ENTRY(state->sound)->kind != 1)
                state->sound = PlayMobySound(1,0,self);
        }
        break;
    case 4:
        if (flag_set_first_pending(self)) CLEAR_SOUND();
        path = g_path_zone_table[state->path1];
        math_step_value_toward_target(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     0.0013888889225199819f,0.0013888889225199819f,0.33333334f);
        path_sample_position(path,0,state->position,state->rotation,0,state->progress);
        part_spawn_driver_spark_bursts(self);
        state->rotation[1] *= -0.333f;
        if (!math_fast_float_d(&state->soundTimer)) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound))
                state->sound = PlayMobySound(2,0,self);
        }
        if (state->progress >= (float)(*(int *)path-1)) {
            moby_set_state(self,5,-1);
            state->progress = 0;
        }
        break;
    case 5:
        if (flag_set_first_pending(self)) CLEAR_SOUND();
        if (self->nextAnimation == 0 &&
            path_is_at_last_point(D_L12_001B2E9C_gp + (state->child << 8))) {
            if (self->nextAnimation != 1) anim_start_blended(self,1,0,30);
            state->soundTimer = 15;
            CLEAR_SOUND();
            state->sound = PlayMobySound(1,0,self);
        } else if (space_tourist_all_idle(state->trigger)) {
            moby_set_state(self,6,-1);
            if (self->nextAnimation != 0) anim_start_blended(self,0,0,30);
            CLEAR_SOUND();
            if (!SOUND_LIVE(state->sound))
                state->sound = PlayMobySound(2,4,self);
        } else if (self->animation == 1 && !math_fast_float_d(&state->soundTimer)) {
            if (state->sound == -1 || !SOUND_LIVE(state->sound) ||
                SOUND_ENTRY(state->sound)->kind != 1)
                state->sound = PlayMobySound(1,0,self);
        }
        break;
    case 6:
        if (flag_set_first_pending(self)) CLEAR_SOUND();
        path = g_path_zone_table[state->path2];
        math_step_value_toward_target(&state->progress,&state->velocity,(float)(*(int *)path-1),
                     g_driver_turn_speed*0.00027777778f,
                     g_driver_turn_speed*0.00027777778f,
                     g_driver_move_speed*0.016666668f);
        path_sample_position(path,0,state->position,state->rotation,0,state->progress);
        part_spawn_driver_spark_bursts(self);
        state->rotation[1] *= -0.333f;
        if (!SOUND_LIVE(state->sound)) state->sound = PlayMobySound(0,4,self);
        if (state->progress >= (float)(*(int *)path-1)) {
            moby_set_state(self,1,-1);
            state->progress = 0;
        }
        break;
    case 7:
        if (flag_set_first_pending(self)) CLEAR_SOUND();
        hit = part_find_owned_effect_slot(self,0x10000,0);
        if (hit) {
            u8 *owner = *(u8 **)(hit+0x20);
            accepted = 0;
            if (owner && (*(s16 *)(owner+0xAA) == MOBY_CLASS_PROTOPET || *(s16 *)(owner+0xAA) == 0xF9E /* moby class 3998 */))
                accepted = 1;
            if (!accepted) {
                SpawnExplosionEffects(self,self->position,0,0,0,10,3,9,4,2,9,0,-1,15,1,1,-1,0,0x810001);
                SetDeathBits(self,0,3);
                moby_mark_spawned(self);
                return;
            }
        }
        break;
    }
    if (self->state != 7) {
        qcopy(self->position,state->position);
        qcopy(self->rotation,state->rotation);
        state->phase0 = FastAddRotations(state->phase0,g_driver_tilt_x_speed*0.00029088825f);
        self->rotation[0] = FastAddRotations(g_driver_tilt_x_amplitude*(math_fast_sin_or_cos_b(state->phase0)*0.017453294f),state->rotation[0]);
        state->phase1 = FastAddRotations(state->phase1,g_driver_tilt_y_speed*0.00029088825f);
        self->rotation[1] = FastAddRotations(g_driver_tilt_y_amplitude*(math_fast_sin_or_cos_b(state->phase1)*0.017453294f),state->rotation[1]);
        state->phase2 = FastAddRotations(state->phase2,g_driver_bob_speed*0.00029088825f);
        self->position[2] += g_driver_bob_amplitude*math_fast_sin_or_cos_b(state->phase2);
    }
}
