#include "include_asm.h"

#include "common.h"
extern void cancel_hero_item_animation_pal(void);
extern void matrix_mul_vec3(void *, void *, void *);
extern char g_action_table[];
extern float FastAddRotations(float f12, float f13);
typedef int HeroQuad __attribute__((mode(TI)));
extern char g_hero_state[];
extern unsigned char g_item_slot_to_record[];
extern char g_hero_attached_moby_buffers[];
extern int get_ammo(int);
extern int hero_slot_item_id(int);
extern void initialize_moby_animation_blend(void *, void *, int, int, int, int);
extern void AdvanceAndDecodeAnimationFrames(void *, void *);
extern f32 ApproachValue(void *, float, float);
extern void release_moby_animation_slot(void *, void *);
extern void vec_clear_128(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastAddRotations(float, float);
typedef struct MobyModel {
    char pad00[0x10];
    int f10;
    char pad14[0x32];
    short kind;                  
} MobyModel;
typedef struct Moby {
    char pad00[5];
    unsigned char flags;
    char pad06[2];
    float fade;                  
    char pad0C[0x17];
    unsigned char animation;     
    MobyModel *model;            
    int f28;
    char pad2C[5];
    unsigned char f31;
    char pad32[2];
    unsigned short state;        
    char pad36[2];
    char *buffer0;               
    char *buffer1;               
    char pad40[0x58];
    int f98;
    char pad9C[0x24];
    HeroQuad matrix[3];          
    char padF0[0x10];
} Moby;
typedef struct WeaponInfo {
    char pad00[0x2C];
    int animation;               
    int alt_animation;            
    char pad34[0xAC];
} WeaponInfo;
typedef struct HeroState {
    char pad00[0x90];
    HeroQuad position;           
    char padA0[0x730 - 0xA0];
    HeroQuad matrix[3];          
    float f760;
    char pad764[0xC];
    union {
        HeroQuad quad;
        float v[4];
    } f770;                      
    char pad780[0xE98 - 0x780];
    Moby *attached[2];           
    char padEA0[4];
    int attached_mode;            
    char padEA8[0x2290 - 0xEA8];
    Moby *moby;                  
    char pad2294[8];
    int state;                   
    char pad22A0[0x22B8 - 0x22A0];
    unsigned char f22B8;
    char pad22B9;
    unsigned char f22BA;
    char pad22BB[8];
    unsigned char f22C3;
    char pad22C4[0x24B0 - 0x22C4];
    int animation;               
    int weapon_id;                
} HeroState;
extern void cancel_hero_item_animation_pal(void);
extern char g_hero_state[];

/* For the hero's two attached mobys: point them at their buffers, start the animation the
   current item's table entry names, fade them in or out (removing one that has faded out),
   then copy the hero moby's matrix to hero + 0x730 and ease hero + 0x778 to 0. */
void hero_update_attached_mobys_pal(void)
{
    HeroState *hero;
    HeroState *state;
    HeroQuad *matrix;
    WeaponInfo *weapon;
    int weapon_id, animation;
    int i;

    hero = (HeroState *)g_hero_state;
    if (hero->f22B8 && hero->f22BA && !get_ammo(-1))
        cancel_hero_item_animation_pal();
    for (i = 0; i < 2; i++) {
        HeroState *player = (HeroState *)g_hero_state;
        Moby **slot = &player->attached[i];

        if (*slot) {
            (*slot)->buffer0 = g_hero_attached_moby_buffers + i * 0xC00;
            (*slot)->buffer1 = g_hero_attached_moby_buffers + 0x600 + i * 0xC00;
            weapon_id = hero_slot_item_id(0);
            if (weapon_id == player->weapon_id) {
                weapon = &((WeaponInfo *)g_action_table)[g_item_slot_to_record[weapon_id]];
                animation = weapon->animation;
                if (player->state == 12)
                    animation = weapon->alt_animation;
                if (animation != -1 && (*slot)->animation != animation) {
                    player->animation = animation;
                    initialize_moby_animation_blend(player->moby, *slot, animation, 0, 7, 1);
                }
            }
            {
                HeroState *owner = (HeroState *)g_hero_state;

                AdvanceAndDecodeAnimationFrames(owner->moby, *slot);
                if (owner->attached_mode) {
                    if (owner->attached_mode == 2)
                        ApproachValue(&(*slot)->fade, 0.0f, 0.3f);
                    else
                        ApproachValue(&(*slot)->fade, 0.0f, 0.08400001f);
                    hero = (HeroState *)g_hero_state;
                    if ((*slot)->fade == 0.0f) {
                        release_moby_animation_slot(hero->moby, slot);
                        return;
                    }
                } else {
                    ApproachValue(&(*slot)->fade, 1.0f, 0.24000001f);
                    if (((*slot)->flags & 2) && !owner->f22BA) {
                        owner->attached_mode = 1;
                        (*slot)->f28 = 0;
                        owner->f22B8 = 0;
                        return;
                    }
                }
            }
        }
    }
    matrix = ((HeroState *)g_hero_state)->matrix;
    state = (HeroState *)g_hero_state;
    {
        Moby *moby = state->moby;

        matrix[0] = moby->matrix[0];
        matrix[1] = moby->matrix[1];
        matrix[2] = moby->matrix[2];
        vec_clear_128(&state->f760);
    }
    state->f760 = 1.0f;
    matrix_mul_vec3(&state->f760, &state->f760, matrix);
    state->f770.quad = state->position;
    if (!state->f22C3)
        state->f770.v[2] = FastAddRotations(state->f770.v[2], 0.0f);
}
