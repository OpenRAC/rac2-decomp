#include "include_asm.h"
/* Trail history, the twin of func_L00_0041F570: the same shift-and-redraw over the
   per-bank 16-byte points with its own scroll scalar, a 0.025 step and a blue edge. */
#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern int func_L00_0032A088(int,int);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern void func_00300190(void *,void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L00_003E2E80(Quad128 *,int,int,int,unsigned int,unsigned int,float,float,float);
extern float D_L00_001B05B4 __attribute__((sda));
void func_L00_003E2BD0(void *self)
{
    char *object=self,*state=*(char **)(object+0x68);
    Quad128 **table,*history;
    int bank=*(int *)state,index,count,n,firstCount,alpha,glow;
    unsigned int color,edge;
    float fraction;
    table=(Quad128 **)func_L00_0032A088(*(int *)(state+0x18),*(int *)(state+0x14));
    if(!table) { func_002FEE50(*(int *)(state+0x34)); func_0029F338(object); return; }
    for(index=0;index<*(int *)(state+0x10);index++) func_00300190(table[bank]+index,table[bank]+index);
    if(*(unsigned char *)(object+0x20)==0) {
        *(int *)(state+0x10)+=1;
        if(*(int *)(state+0x10)>=40) *(int *)(state+0x10)=40;
        n=*(int *)(state+0x10)-1;
        if(n>0) { Quad128 *h=table[bank]; for(;n>0;n--) h[n]=h[n-1]; }
        history=table[bank]; *history=*(Quad128 *)(object+0x10); ((float *)history)[3]=0.025f;
    }
    D_L00_001B05B4-=0.1f;
    if(D_L00_001B05B4<=-7.0f) D_L00_001B05B4+=7.0f;
    count=*(int *)(state+0x10); if(count<2) return;
    firstCount=20; if(count<=19) firstCount=count;
    alpha=255; glow=64;
    if(*(unsigned char *)(object+0x20)==1) {
        fraction=IntToFloat(*(int *)(state+0x38)); fraction/=IntToFloat(6);
        alpha=FloatToInt(IntToFloat(255)*fraction);
        glow=FloatToInt(IntToFloat(64)*fraction);
    }
    color=((unsigned int)alpha<<24)|0xffffff; edge=((unsigned int)glow<<24)|0x204080;
    DrawFadingTwoPassRibbon(table[bank],23,14,firstCount,color,edge,0.0f,4.0f,D_L00_001B05B4);
    if(*(int *)(state+0x10)>20) DrawFadingTwoPassRibbon(table[bank],23,14,*(int *)(state+0x10),color,edge,0.0f,4.0f,D_L00_001B05B4);
}
