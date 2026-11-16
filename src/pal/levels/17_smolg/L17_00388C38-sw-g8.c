#include "include_asm.h"

#include "common.h"
typedef struct Moby Moby;
typedef struct {
    int count;                   
    u8 pad04[0x10 - 0x04];
    float start[3];              
    float length;                
    float end[4];                
} HazardPath;
typedef struct {
    int path;                    
    int next;                    
    float chain_span;             
    float chain_time;             
    float x10;                   
    int x14;                     
    int x18;                     
    Moby *parent;                
    float x20;                   
    float x24;                   
    float x28;                   
    int sound;                   
    int timer;                   
    int is_linked;                
} HazardVars;
struct Moby {
    u8 pad0[0x10];
    float position[3];           
    float update_dist;            
    u8 state;                    
    u8 pad21[0x30 - 0x21];
    u8 x30;                      
    u8 pad31;
    u16 x32;                     
    u8 pad34[0x68 - 0x34];
    HazardVars *vars;            
    u8 pad6C[0x78 - 0x6C];
    int color;                   
    u8 pad7C[0xA8 - 0x7C];
    u8 impact_slot;               
    u8 padA9;
    s16 oClass;                  
    u8 padAC[0xB2 - 0xAC];
    s16 uid;                     
    u8 padB4[0xF0 - 0xB4];
    float rotation[4];           
};
typedef struct {
    u8 bytes[0x70];
} SoundRecord;
typedef struct {
    u8 pad0[0x74];
    u8 active;                   
    u8 pad75[0x88 - 0x75];
    Moby *owner;                 
} SoundVoice;
extern HazardPath *g_path_l17_table[];
extern Moby *g_moby_l17_pool;
extern Moby *D_L17_001B2C1C_1[] __attribute__((sda));
extern int g_flash_frame_counter MACRO_ADDR;
extern float g_hazard_var24_a __attribute__((sda)), g_hazard_var20_a __attribute__((sda));
extern float g_hazard_var28_a __attribute__((sda)), g_hazard_var10_a __attribute__((sda));
extern float g_hazard_var24_b __attribute__((sda)), g_hazard_var20_b __attribute__((sda));
extern float g_hazard_var28_b __attribute__((sda)), g_hazard_var10_b __attribute__((sda));
extern int g_hazard_linked_flag __attribute__((sda));
extern char g_hero_position[];
extern SoundRecord g_sound_state[];
extern char g_effect_color_params[] MACRO_ADDR;
extern char g_str_hazard_debug_a[], g_str_hazard_debug_b[];
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void STUB_printf(const char *, ...);
extern void moby_set_state(void *, int, int);
extern int PlacePathFollowerChainAtStart_pal(void *);
extern int UpdatePathFollowerChain_pal(void *);
extern void *part_find_owned_effect_slot(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(int *);
extern char *SpawnExplosion_pal(void *, float, int, int, int, int, int, int, int, int,
                          int, int, int, float);
extern void part_spawn_masked_debris_pal(void *, int, void *, float, float, float, float, int);
extern Moby *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, int, float, float);
extern void part_spawn_scaled_bolts_pal(void *, int, float);
extern void moby_mark_spawned(void *);

/* Updates a path-linked hazard, its movement sound and its destruction effects. */
void UpdatePathHazard_pal(Moby *moby)
{
    HazardVars *vars = moby->vars;
    int flash;
    int color;

    vars->x20 = moby->oClass == 0x8AD ? g_hazard_var20_a : g_hazard_var20_b;
    vars->x24 = moby->oClass == 0x8AD ? g_hazard_var24_a : g_hazard_var24_b;
    vars->x28 = moby->oClass == 0x8AD ? g_hazard_var28_a : g_hazard_var28_b;
    vars->x10 = moby->oClass == 0x8AD ? g_hazard_var10_a : g_hazard_var10_b;

    flash = (g_flash_frame_counter + moby->uid) % 50 < 12;
    color = flash ? 0x80FFFFFF : 0x80404040;
    moby->color = color;

    if (moby->oClass == 0x8D8 || moby->oClass == 0x8AD) {
        if (moby->state == 2 && vec_distance_xy(moby->position, g_hero_position) < 80.0f) {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[vars->sound];
            if (voice->owner != moby || !voice->active)
                vars->sound = PlayMobySound(0, 4, moby);
        } else {
            int sound = vars->sound;
            if (sound != -1) {
                SoundVoice *voice = (SoundVoice *)&g_sound_state[sound];
                if (voice->owner == moby && voice->active)
                    snd_stop_voice(sound);
            }
            vars->sound = -1;
        }
    }

    switch (moby->state) {
    case 0:
        vars->sound = -1;
        vars->is_linked = 0;
        if (vars->path == -1 || g_path_l17_table[vars->path]->count < 2) {
            STUB_printf(g_str_hazard_debug_a, moby->oClass, moby->uid);
            STUB_printf(g_str_hazard_debug_b);
            moby_mark_spawned(moby);
            break;
        }
        moby->x32 = 0x180;
        moby->x30 = 0xFF;
        {
            int index = vars->next;
            if (index == -1) {
                vars->chain_span = 0.0f;
            } else {
                int count = 0;
                do {
                    index = g_moby_l17_pool[index].vars->next;
                    count++;
                } while (index != -1);
                vars->chain_span = IntToFloat(count);
            }
        }
        vars->chain_time = vars->chain_span * 4.0f;
        {
            HazardPath *path = g_path_l17_table[vars->path];
            path->length = fast_vec_dist(path->start, path->end);
        }
        vars->x14 = 0;
        vars->x18 = 0;
        if (vars->next != -1) {
            D_L17_001B2C1C_1[0][vars->next].vars->parent = moby;
            vars->is_linked = 1;
            moby_set_state(moby, 3, -1);
        } else {
            moby_set_state(moby, 2, -1);
        }
        moby->state = 1;
        break;
    case 1:
        PlacePathFollowerChainAtStart_pal(moby);
        if (g_hazard_linked_flag && !vars->is_linked)
            moby->state = 2;
        else
            moby->state = 3;
        break;
    case 2:
        if (g_hazard_linked_flag)
            UpdatePathFollowerChain_pal(moby);
        if (part_find_owned_effect_slot(moby, 0x4010000, 1))
            moby_set_state(moby, 5, -1);
        moby->impact_slot = 0xFF;
        break;
    case 3:
        if (vars->next != -1) {
            Moby *other = g_moby_l17_pool + vars->next;
            if (!other || other->state == 0xFE || other->state == 0xFD)
                moby_set_state(moby, 4, -1);
        }
        if (part_find_owned_effect_slot(moby, 0x4010000, 1))
            moby_set_state(moby, 5, -1);
        moby->impact_slot = 0xFF;
        break;
    case 4:
        if (flag_set_first_pending(moby))
            vars->timer = 4;
        if (math_fast_float_d(&vars->timer))
            moby_set_state(moby, 5, -1);
        break;
    case 5:
        if (moby->oClass == 0x8AD) {
            float *pos = moby->position;
            float *rot;
            float a, b;
            Moby *created;
            moby->update_dist = 1000000.0f;
            SpawnExplosion_pal(pos, 10.0f, 0, 10, 10, 10, 10, 20, 0, 1, 0, 0, 0, 20.0f);
            rot = moby->rotation;
            part_spawn_masked_debris_pal(moby, 11, g_effect_color_params, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            a = math_random_float_range(-10.0f, 10.0f);
            b = math_random_float_range(20.0f, 30.0f);
            created = cam_moby_create_pal(moby, 2, 0x8AD, 2, pos, rot, g_effect_color_params, 255, a, b);
            if (created)
                created->vars->sound = 0;
            part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
            moby_mark_spawned(moby);
        } else {
            moby->update_dist = 1000000.0f;
            SpawnExplosion_pal(moby->position, 3.0f, 0, 10, 10, 10, 10, 20, 0, 1, 0, 0, 0, 20.0f);
            part_spawn_masked_debris_pal(moby, 31, g_effect_color_params, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            part_spawn_scaled_bolts_pal(moby, 1, 0.0f);
            moby_mark_spawned(moby);
        }
        break;
    }
}
