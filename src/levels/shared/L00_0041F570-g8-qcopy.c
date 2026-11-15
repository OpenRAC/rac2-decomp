#include "names.h"
/* Trail history: refresh, shift and redraw the per-bank history of 16-byte points.
   The shift loop runs over its own base pointer so loop strength reduction
   produces the offset-plus-base pointers; alpha and glow are set after the count test. */
#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern int level_get_slot_body(int,int);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
extern void vec_transform_or_copy(void *,void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void DrawFadingDualRibbon(Quad128 *,int,int,int,unsigned int,unsigned int,float,float,float);
extern float D_L00_001B1494 __attribute__((sda));
/* Updates and draws the glowing ribbon trail of a shot, fading it out when the shot has ended. */
void shot_update_and_draw_trail(void *self)
{
    char *object=self,*state=*(char **)(object+0x68);
    Quad128 **table,*history;
    int bank=*(int *)state,index,count,n,firstCount,alpha,glow;
    unsigned int color,edge;
    float fraction;
    table=(Quad128 **)level_get_slot_body(*(int *)(state+0x18),*(int *)(state+0x14));
    if(!table) { table_clear_entry_flag(*(int *)(state+0x34)); moby_mark_spawned(object); return; }
    for(index=0;index<*(int *)(state+0x10);index++) vec_transform_or_copy(table[bank]+index,table[bank]+index);
    if(*(unsigned char *)(object+0x20)==0) {
        *(int *)(state+0x10)+=1;
        if(*(int *)(state+0x10)>=40) *(int *)(state+0x10)=40;
        n=*(int *)(state+0x10)-1;
        if(n>0) { Quad128 *h=table[bank]; for(;n>0;n--) h[n]=h[n-1]; }
        history=table[bank]; *history=*(Quad128 *)(object+0x10); ((float *)history)[3]=0.05f;
    }
    D_L00_001B1494-=0.1f;
    if(D_L00_001B1494<=-7.0f) D_L00_001B1494+=7.0f;
    count=*(int *)(state+0x10); if(count<2) return;
    firstCount=20; if(count<=19) firstCount=count;
    alpha=255; glow=64;
    if(*(unsigned char *)(object+0x20)==1) {
        fraction=IntToFloat(*(int *)(state+0x38)); fraction/=IntToFloat(6);
        alpha=FloatToInt(IntToFloat(255)*fraction);
        glow=FloatToInt(IntToFloat(64)*fraction);
    }
    color=((unsigned int)alpha<<24)|0xffffff; edge=((unsigned int)glow<<24)|0x2020ff;
    DrawFadingDualRibbon(table[bank],23,14,firstCount,color,edge,0.0f,4.0f,D_L00_001B1494);
    if(*(int *)(state+0x10)>20) DrawFadingDualRibbon(table[bank],23,14,*(int *)(state+0x10),color,edge,0.0f,4.0f,D_L00_001B1494);
}
