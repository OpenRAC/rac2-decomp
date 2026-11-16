#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
typedef struct { int first,second,third; } AllocationOffsets;
typedef struct { void *data; int first,second; float cooldown; int timer; void *target,*previous; short acquire,release; } WeaponContext;
typedef struct HeroView {
char pad0[1180];
unsigned char field49c;
char pad49d[1935];
int fieldc2c;
char padc30[1536];
int field1230;
char pad1234[12];
int field1240;
char pad1244[700];
int field1500;
char pad1504[3468];
unsigned char * field2290;
int field2294;
char pad2298[4];
int field229c;
char pad22a0[528];
int field24b0;
char pad24b4[128];
int field2534;
} HeroView;
extern HeroView g_hero_state;
extern unsigned int g_pad_pressed_flags;
extern unsigned char g_chopper_weapon_index;
typedef struct { char pad[0x54]; float rate; char rest[0x88]; } WeaponEntry;
extern WeaponEntry g_weapon_l00_table[];
extern void weapon_update_target_lock(void *), weapon_release_shot_slots(void);
extern int get_ammo(int);
extern void hud_add_moby_marker(void *,float,unsigned int,void *,int,float,int,float,int);
extern int AcquireEntitySlot(void *,void (*)(void),int *);
extern char*level_get_slot_body(int,void *);
extern char *mem_round_up_to_16(void *);
extern AllocationOffsets *level_get_slot_header(int,void *);
extern void mem_fast_helper_b(void *,int);
extern int math_fast_float_d(int *),vec_fast_helper_b(float *);
extern int math_is_below_plane_within_depth(float);
extern void start_equipped_item_animation(void),initialize_moby_animation_blend(void *,void *,int,int,int,int);
extern int weapon_spend_ammo(int,int);
extern int PlayMobySound(int,int,void *);
extern char *guided_rocket_create(void *,void *,int,void *,int,int);
/* Runs the Chopper and Multi-Star weapon: sets up its shot slots, then fires when the button is pressed and the weapon is ready. */
void chopper_update(unsigned char *object)
{
    int existing;
    WeaponContext *state=*(WeaponContext **)(object+0x68);
    char *ctx=(char *)state;
    char *cursor,*base,*other,*result;
    int offset;
    void **table;
    int triggered,secondary,finished,allowed;
    weapon_update_target_lock(object);
    if(g_hero_state.field1500 || g_hero_state.field2294==29 || g_hero_state.field2294==1) {
        unsigned int color;
        if(F(ctx,0xC)>0.0f && get_ammo(-1)) color=0x600000FF;
        else color=0x600FFF0F;
        hud_add_moby_marker(object,1.0f,color,0,38,0.0f,-1,90.0f,4);
    }
    switch(object[0x20]) {
    case 0: {
        other=AcquireEntitySlot(object,weapon_release_shot_slots,&existing);
        state->data=other;
        if(!existing) {
            cursor=level_get_slot_body(H(object,0xAA),other);
            base=cursor;
            cursor=mem_round_up_to_16(cursor+0x64);
            { int i; for(i=0;i<25;i++) {((void **)base)[i]=cursor;cursor+=0x280;} }
            cursor=mem_round_up_to_16(cursor);
            I(ctx,4)=cursor-base;
            mem_fast_helper_b(cursor,0x20D0);
            cursor=mem_round_up_to_16(cursor+0x20D0);
            I(ctx,8)=cursor-base;
            { int j; for(j=24;j>=0;j--) ((int *)cursor)[j]=0; }
            cursor=mem_round_up_to_16(cursor+0x64);
            offset=cursor-base;
            table=(void **)cursor;
            cursor=mem_round_up_to_16(cursor+0x64);
            { int k; for(k=0;k<25;k++) {table[k]=cursor;cursor+=0x280;} }
            { AllocationOffsets *offsets=level_get_slot_header(H(object,0xAA),*(void **)ctx);
            offsets->first=I(ctx,4);offsets->second=I(ctx,8);offsets->third=offset; }
        }
        object[0x20]=1;H(ctx,0x1C)=4;
        state->cooldown=0;state->target=0;state->previous=0;state->release=0;
        return;
    }
    case 1: case 2:
        triggered=0;secondary=0;finished=0;allowed=1;
        if(g_hero_state.field1500 || g_hero_state.field2294==29) {
            if(!math_fast_float_d(&g_hero_state.field2534)) allowed=0;
        } else g_hero_state.field2534=40;
        if(object[0x20]==1) {
            if(vec_fast_helper_b((float *)(ctx+0xC)) && allowed &&
               (g_pad_pressed_flags & g_hero_state.field1230) && g_hero_state.field1240>=23 &&
               (g_hero_state.field1500 || g_hero_state.field2294==1 || g_hero_state.field2294==29) && get_ammo(22)) {
                { WeaponEntry *w=&g_weapon_l00_table[g_chopper_weapon_index];
                F(ctx,0xC)=1.0f/w->rate; }
                triggered=1;
            }
            secondary=0;
            if(g_hero_state.field2294==0x83 && !g_hero_state.fieldc2c && math_is_below_plane_within_depth(33.0f)) secondary=get_ammo(22)!=0;
            if(g_hero_state.field229c==4 && allowed && !g_hero_state.field49c &&
               F(ctx,0xC)==0.0f && (g_pad_pressed_flags&0x20) && g_hero_state.field1240>=23 && get_ammo(22)) {
                start_equipped_item_animation();
                other=*(char **)((char *)&g_hero_state+0xE98);
                if(other) {
                    F(other,8)=0.0f;
                    initialize_moby_animation_blend(g_hero_state.field2290,other,g_hero_state.field24b0,1,1,1);
                }
                object[0x20]=2;
                { WeaponEntry *w=&g_weapon_l00_table[g_chopper_weapon_index];
                F(ctx,0xC)=1.0f/w->rate; }
                I(ctx,0x10)=8;
            }
        } else if(math_fast_float_d((int *)(ctx+0x10))) {finished=1;object[0x20]=1;}
        if(triggered || secondary || finished) {
            weapon_spend_ammo(-1,1);PlayMobySound(2,0,object);
            result=guided_rocket_create(object,object+0x10,triggered,*(void **)ctx,I(ctx,0x14),1);
            if(result) *(void **)(result+0xB8)=object;
        }
        return;
    }
}
