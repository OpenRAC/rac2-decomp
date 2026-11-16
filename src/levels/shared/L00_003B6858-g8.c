#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { char *objects[2]; char pad08[8]; Quad positions[2]; Quad velocity[2]; char pad50[0x18]; int seed; } PairState;
extern Quad g_pair_game_effect_sources[2] SDATA(D_L00_001AFA70);
extern Quad g_pair_game_effect_positions[2] SDATA(D_L00_001AFA50);
extern float g_pair_game_effect_rates[2] __attribute__((sda));
extern float g_pair_game_effect_scales[2] SDATA(D_L00_001AFA90);
extern int g_pair_game_effect_materials[2] SDATA(D_L00_001AFA98);
extern int math_random_int_below(int);
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(char *,int);
extern void moby_set_light_color(char *,int);

int InitializePairedObjects(char *object)
{
    int i=0;
    Quad *source,*position;
    int *material;
    float *scale,*rate;

    PairState *state=*(PairState **)(object+0x68);
    char **slot;
    Quad *out,*velocity;
    slot=state->objects;
    velocity=state->velocity;
    state->seed=math_random_int_below(255);
    material=g_pair_game_effect_materials;
    scale=g_pair_game_effect_scales;
    rate=g_pair_game_effect_rates;
    position=g_pair_game_effect_positions;
    source=g_pair_game_effect_sources;
    out=state->positions;
    do {
        *slot=CreateMoby(i?MOBY_CLASS_SHEEP:MOBY_CLASS_DARK_SHEEP);
        moby_init_child_from_parent(*slot,0);
        *(unsigned short *)(*slot+0x34)|=0x4100;
        (*slot)[0xbc]=i;
        *(Quad *)(*slot+0xf0)=*source;
        *out=*position;
        *velocity=0;
        ((float *)velocity)[1]=*rate*(1.0f/60.0f);
        *(float *)(*slot+0x2c)=*(float *)(*(char **)(*slot+0x24)+0x24)* *scale;
        moby_set_light_color(*slot,*material);
        slot++;rate++;position++;out++;source++;velocity++;scale++;material++;i++;
    }while(i<2);
    if(state->objects[0]) {
        if(state->objects[1]) return 1;
    }
    return 0;
}
