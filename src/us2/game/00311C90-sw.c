#include "include_asm.h"

#include "common.h"
typedef struct CrateMoby CrateMoby;
typedef struct {
    char pad00[0x10];
    int collision;               
} CrateClass;
typedef struct {
    char pad00[0x24];
    int flags;                   
    char pad28[4];
    float f2C;                   
} CrateHit;
typedef struct {
    char pad00[0x1E];
    unsigned short flags;        
} CrateColl;
typedef struct {
    char pad00[0x20];
    CrateColl coll;              
    char pad40[0x90 - 0x40];
    float f90[4];                
    CrateMoby *above;            
    CrateMoby *below;            
    int fA8;                     
    int flags;                   
    char padB0[4];
    int frame;                   
    long long savedColor;        
    char padC0[6];
    short fC6;                   
    unsigned char respawns;      
    unsigned char respawnTimer;  
    unsigned char burstFrame;    
    char padCB;
    int fCC;                     
    char padD0[0xFC - 0xD0];
    void *linked;                
    int f100;                    
} CrateVars;
struct CrateMoby {
    char pad00[0x10];
    float position[4];           
    unsigned char state;         
    unsigned char group;         
    char pad22[2];
    CrateClass *pclass;          
    char pad28[0x31 - 0x28];
    unsigned char visible;       
    short drawDistance;          
    unsigned short flags;        
    char pad36[2];
    long long color;             
    char pad40[0x68 - 0x40];
    CrateVars *vars;             
    char pad6C[0x98 - 0x6C];
    int collision;               
    char pad9C[0xA8 - 0x9C];
    unsigned char hitSlot;       
    char padA9;
    short oClass;                
    char padAC[0xB4 - 0xAC];
    short fB4;                   
    char padB6[0xBC - 0xB6];
    unsigned char command;       
    char padBD[0xC0 - 0xBD];
    float forward[4];            
    char padD0[0x10];
    float up[4];                 
};
typedef struct {
    char pad000[0x26C];
    CrateMoby *collHitMoby;      
    CrateMoby *f270;             
    char pad274[0x33C - 0x274];
    CrateMoby *groundMoby;       
    char pad340[0x34E - 0x340];
    short airFrames;             
    char pad350[0x588 - 0x350];
    CrateMoby *ledgeMoby;        
    char pad58C[0x2290 - 0x58C];
    CrateMoby *moby;             
    char pad2294[0x229C - 0x2294];
    int f229C;                   
} CrateHero;
typedef struct {
    float position[4];           
    CrateMoby *moby;             
    int f14;                     
    char pad18[4];
    float f1C;                   
    int f20;                     
    char pad24[0xC];
} __attribute__((aligned(16))) CrateBurst;
extern int g_game_time MACRO_ADDR;
extern char g_hero_state[];
extern char g_nearby_mobys[];
extern int g_hero_mode;
#define HERO ((CrateHero *)D_00189E20)
extern void UpdateCrateStackMotion_us2(CrateMoby *);
extern CrateHit *part_find_owned_effect_slot(CrateMoby *, int, int);
extern int moby_is_in_special_class_range(CrateMoby *);
extern void vec_clear_128(void *);
extern void GroundAttachedUpdate(CrateMoby *);
extern void *moby_spawn_linked_child(CrateMoby *, int);
extern int flag_set_first_pending(CrateMoby *);
extern void DestroyCrate(CrateMoby *, int, CrateHit *);
extern void crate_drop_loot_us2(CrateMoby *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern int coll_process_hit(void *, int, CrateMoby *, void *, float);
extern void moby_queue_knockback_for_nodes(CrateMoby *, void *, void *, int, CrateMoby *, int, int, int, float, float, float);
extern int math_random_int_range(int, int);
extern void moby_mark_spawned(CrateMoby *);
extern int math_fast_helper_a(void *, float);
extern int vec_fast_helper_a(unsigned char *);
extern void moby_set_state(CrateMoby *, int, int);
extern int GetFirstMobyInGroup(CrateMoby **, int, int, int);
extern int GetNextMobyInGroup(CrateMoby **, CrateMoby *, int, int);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern int PlayMobySound(int, int, CrateMoby *);
extern void set_moby_color(CrateMoby *, int, int, int);

/* Updates a crate: follows the stack motion, reacts to hits, breaks open and drops its loot, and respawns when allowed (v2.00 copy). */
void CrateUpdate_us2(CrateMoby *moby)
{
    CrateBurst burst;
    float position[4] __attribute__((aligned(16)));
    CrateMoby *found;
    CrateVars *vars = moby->vars;
    CrateHit *hit;
    int touched;
    CrateColl *coll = &vars->coll;

    if (vars->flags & 0xC) {
        if (vars->frame != g_game_time) {
            UpdateCrateStackMotion_us2(moby);
        }
    }
    if (vars->above == 0) {
        coll->flags |= 1;
    }
    hit = part_find_owned_effect_slot(moby, 0x5830001, 0);
    touched = 0;
    if (hit != 0 && hit->flags == 0x1000000) {
        hit = 0;
        touched = 1;
    }
    switch (moby->state) {
    case 0:
        if (vars->above != 0 && !moby_is_in_special_class_range(vars->above)) {
            vars->above = 0;
        }
        if (vars->below != 0 && !moby_is_in_special_class_range(vars->below)) {
            vars->below = 0;
        }
        vec_clear_128(vars->f90);
        moby->state = 1;
        vars->fA8 = 0;
        if (moby->oClass == MOBY_CLASS_AMMO_CRATE) {
            vars->frame++;
        }
        if (vars->fCC == 0) {
            vars->flags |= 0x14;
            if ((vars->flags ^ 1) & 1) {
                GroundAttachedUpdate(moby);
            }
        }
        vars->linked = 0;
        if (moby->oClass == MOBY_CLASS_AMMO_CRATE) {
            vars->fC6 = 100;
        } else if (moby->oClass == MOBY_CLASS_NANOTECH_CRATE) {
            vars->linked = moby_spawn_linked_child(moby, 0);
        } else if (moby->oClass == MOBY_CLASS_PURPLE_NANOTECH_CRATE) {
            vars->linked = moby_spawn_linked_child(moby, 1);
        }
        break;
    case 1:
        if (flag_set_first_pending(moby)) {
            vars->f100 = 0;
        }
        if (moby->oClass == MOBY_CLASS_EXPLOSIVE_CRATE &&
            (HERO->f270 == moby || HERO->collHitMoby == moby ||
             (HERO->groundMoby == moby && HERO->airFrames == 0) ||
             HERO->ledgeMoby == moby || touched)) {
            if (HERO->f229C == 15) {
                DestroyCrate(moby, 1, 0);
                crate_drop_loot_us2(moby);
                break;
            }
            moby->command = 0;
            moby->state = 5;
            break;
        }
        if (hit != 0 && hit->f2C > 0.0f) {
            int do_hit = 1;

            if (moby->oClass == 0x1F6 /* moby class 502 */ && !(hit->flags & 0x20000)) {
                do_hit = 0;
            }
            if (moby->oClass == MOBY_CLASS_EXPLOSIVE_CRATE) {
                moby->state = 5;
                if (hit->flags & 0x20000) {
                    moby->command = 1;
                } else {
                    moby->command = FloatToInt(math_random_float_range(5.0f, 15.0f));
                }
                vars->savedColor = moby->color;
                do_hit = 0;
            }
            if (do_hit) {
                DestroyCrate(moby, moby->oClass == MOBY_CLASS_EXPLOSIVE_CRATE, hit);
                crate_drop_loot_us2(moby);
            }
            moby->hitSlot = 255;
        }
        break;
    case 2:
        if (--moby->command == 255) {
            moby->hitSlot = 255;
            moby->state = 1;
        }
        break;
    case 3:
        if (moby->oClass == MOBY_CLASS_EXPLOSIVE_CRATE && vars->burstFrame < 21) {
            float radius;
            int target;

            burst.moby = moby;
            burst.f1C = 2.0f;
            qcopy(&burst, moby->forward);
            burst.f20 = 0;
            vec_scale_to_length(position, moby->up, 0.5f);
            FastVecAdd(position, position, moby->position);
            radius = IntToFloat(vars->burstFrame) * 0.05f;
            burst.f14 = 1;
            coll_process_hit(position, 16, moby, &burst, radius + radius);
            burst.f14 = 0x30000;
            target = coll_process_hit(position, 16, HERO->moby, 0, radius * 3.0f);
            if (target != 0) {
                moby_queue_knockback_for_nodes(moby, position, g_nearby_mobys, target, HERO->moby, 0x10000, 0, 0x30000, 4.0f, 1.0f, 1.0f);
            }
            vars->burstFrame++;
        } else if (vars->respawns != 0) {
            moby->flags = (moby->flags | 0x41) & 0xEFFF;
            moby->collision = 0;
            if (moby->fB4 >= 2) {
                moby->fB4 = 1;
            }
            moby->state = 6;
            if (vars->respawnTimer != 255) {
                vars->respawnTimer = math_random_int_range(30, 60);
            }
        } else {
            moby_mark_spawned(moby);
            break;
        }
        moby->hitSlot = 255;
        break;
    case 6:
        vars->f100++;
        if (vars->respawnTimer == 255) {
            break;
        }
        qcopy(&burst, moby->position);
        burst.position[2] += 0.5f;
        burst.position[3] = 1.0f;
        if (math_fast_helper_a(&burst, (float)moby->drawDistance) != -1 || !vec_fast_helper_a(&vars->respawnTimer)) {
            goto done;
        }
        if (moby->group == 255) {
            moby_set_state(moby, 1, -1);
            moby->flags = (moby->flags & 0xFFBE) | 0x1000;
            moby->collision = moby->pclass->collision;
            break;
        }
        GetFirstMobyInGroup(&found, moby->group, 0, 0);
        while (found != 0) {
            if (moby != found && !(vec_distance_xy(moby->position, found->position) > 0.1f) && found->state == 1) {
                CrateVars *other = found->vars;

                if (other->above == 0) {
                    qcopy(moby->position, found->position);
                    moby->position[2] += 1.0f;
                    other->above = moby;
                    vars->below = found;
                    vars->above = 0;
                    moby->state = 1;
                    moby->visible = 1;
                    moby->flags &= 0xFFFE;
                    moby->collision = moby->pclass->collision;
                    moby->flags |= 0x1000;
                    break;
                }
            }
            GetNextMobyInGroup(&found, found, 0, 0);
        }
        if (moby->state != 1) {
            moby->position[2] = coll_probe_ground_height_below(moby->position, 0, 0.5f);
            moby->state = 1;
            vars->above = 0;
            vars->below = 0;
            moby->visible = 1;
            moby->flags &= 0xFFFE;
            moby->collision = moby->pclass->collision;
        }
        goto done;
    case 5:
        if (moby->command == 0) {
            moby->command = 179;
            vars->savedColor = moby->color;
        } else if (moby->command >= 16 && hit != 0) {
            moby->command = FloatToInt(math_random_float_range(5.0f, 15.0f));
        }
        if (moby->command % 60 == 57 || moby->command == 13) {
            PlayMobySound(1, 32, moby);
        }
        if (moby->command % 60 > 40 || moby->command < 15) {
            set_moby_color(moby, 200, 64, 64);
        } else {
            moby->color = vars->savedColor;
        }
        if (moby->command == 1 || g_hero_mode == 22) {
            moby->color = vars->savedColor;
            DestroyCrate(moby, 1, 0);
            crate_drop_loot_us2(moby);
        }
        moby->hitSlot = 255;
        moby->command--;
        break;
    case 4:
        if (vec_fast_helper_a(&moby->command)) {
            moby->state = 1;
            moby->flags &= 0xFFFE;
        }
done:
        moby->hitSlot = 255;
        break;
    }
}
