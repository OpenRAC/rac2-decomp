#include "common.h"

/* func_PAL_L06_004046D8, the PAL copy of func_L06_004009B8: the same C, where the
 * 60 Hz divisor D_L06_001AFF20 * 60.0f becomes (ref * 300.0f + 2.0f) / 6, ref being
 * this function's own 0.45f: a different variable from the 0.45f that
 * func_PAL_L06_003E8A88 reads, at a different address in each level. */

/* Draws the scrolling mesh grid as textured quads, fading each column by age.
 * Corresponds to RAC1 render_data_processor_linked_effect; the packet layout,
 * loop lifetimes and matrix copies follow the measured RAC2 body.
 */
#define RI(p,o) (*(s32 *)((char *)(p)+(o)))
#define RF(p,o) (*(float *)((char *)(p)+(o)))
typedef int QuadWord __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) RenderVec;
typedef struct { RenderVec points[4]; u32 colors[4]; float uv[4][2]; u64 r70,texture,flags,blend; } RenderQuad;
extern char *D_L06_001B281C;
extern char D_L06_001B9840[];
extern float D_L06_001AFE7C[] MACRO_ADDR;
extern s32 D_L06_001AFE50 __attribute__((sda));
extern s32 D_L06_001AFE54 __attribute__((sda));
extern s32 D_L06_001AFE58 __attribute__((sda));
extern s32 D_L06_001AFE5C __attribute__((sda));
extern u32 D_L06_001AFE70 __attribute__((sda));
extern u32 D_L06_001AFE74 __attribute__((sda));
extern float D_L06_001AFE78[8] __attribute__((sda));
extern RenderVec D_L06_001AFEA0[4] __attribute__((sda));
extern float D_L06_001AF71C;
extern s32 D_L06_001B31B4;
extern s32 D_L06_001B31B0;
extern float ref_PAL_L06_004046D8_00 __attribute__((sda));
extern float func_00282E48(void *,void *);
extern void func_002833B8(void *,float);
extern void func_00283410(void *,void *);
extern void func_00283788(void *,void *,void *);
extern float func_00283CE0(s32);
extern s32 func_00283CF0(float);
extern u64 func_0027C878(s32);
extern u32 func_00283D38(u32,u32,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00280B90(void *,void *,s32);

void func_PAL_L06_004046D8(char *obj)
{
    RenderQuad quad[2];
    RenderVec rotation[4];
    char *data = *(char **)(obj+0x68);
    char *mesh = *(char **)(D_L06_001B281C + RI(data,0xC)*256+0x68);
    char *matrices = __builtin_alloca((u32)(RI(data,4)<<9)>>3);
    float fade;
    float distance;
    s32 n,uvIndex,i,j,k;
    u8 *order;
    s32 groupAge;
    char *ageBase, *ages;
    s32 groupVertices;
    float *uv0;
    s32 nextGroup, nextRow;
    float *uv1, *v0, *v1;
    s32 matrixIndex;
    u64 blend;
    u64 texture;
    float scroll;
    u32 color;
    s32 opacity;

    distance = func_00282E48(obj+0x10,D_L06_001B9840);
    if (distance>48.0f) fade=(80.0f-distance)*0.03125f;
    else fade=1.0f;
    func_002833B8(rotation,RF(data,0)*0.5f);
    uv0=&quad[0].uv[0][0];
    uv1=&quad[1].uv[0][0];
    v0=uv0+1;
    v1=uv1+1;
    for (matrixIndex=0;matrixIndex<RI(data,4);matrixIndex++) {
        char *matrix=matrices+matrixIndex*64;
        func_00283410(matrix,obj+0xF0);
        func_00283788(matrix,matrix,rotation);
        *(QuadWord *)(matrix+0x30) = *(QuadWord *)(obj+0x10);
        RF(matrix,0x38)+=func_00283CE0(matrixIndex+1)*RF(data,8);
    }
    texture=func_0027C878(14);
    blend=(u64)D_L06_001AFE50 | ((u64)D_L06_001AFE54<<2);
    blend |= ((u64)D_L06_001AFE58<<4);
    blend |= ((u64)D_L06_001AFE5C<<6);
    blend |= 0x8000000000ULL;
    quad[1].texture=texture;
    quad[0].texture=texture;
    quad[1].flags=0xFF9000000260ULL;
    quad[0].flags=0xFF9000000260ULL;
    quad[0].r70=quad[1].r70=0;
    quad[0].blend=quad[1].blend=blend;
    {
        s32 initialUV;
        for(initialUV=0;initialUV<4;initialUV++) {
            v0[initialUV*2]=v1[initialUV*2]=D_L06_001AFE7C[initialUV*2];
        }
    }
    i=0;
    do {
        nextGroup=i+1;
        scroll=0.0f;
        j=0;
        do {
            s32 next;
            scroll+=D_L06_001AF71C;
            if(scroll>1.0f) scroll-=1.0f;
            nextRow=j+1;
            for(uvIndex=0;uvIndex<4;uvIndex++) {
                float uv=D_L06_001AFE78[uvIndex*2]+scroll+RF(mesh,0x12DE0);
                uv0[uvIndex*2]=uv1[uvIndex*2]=uv;
            }
            for(n=0;n<RI(data,4);n=next) {
                s32 offset;
                float progress;
                float alpha;
                s32 time;
                order=(u8 *)data+0x10;
                groupAge=i*120;
                ageBase=mesh+0x10000;
                ages=ageBase+0x2C00;
                time=RI(ages,order[n]*4+groupAge);
                groupVertices=i*0x2580;
                if(time>D_L06_001B31B4) progress=func_00283CE0(time-D_L06_001B31B4)/func_00283CE0(D_L06_001B31B0-D_L06_001B31B4);
                else progress=1.0f-func_00283CE0(time)/func_00283CE0(D_L06_001B31B4);
                color=func_00283D38(D_L06_001AFE70,D_L06_001AFE74,progress);
                alpha=func_00283CE0((s32)color>>24);
                opacity=func_00283CF0(fade*fade*alpha);
                color=(color&0xFFFFFF)+(opacity<<24);
                if((u8)obj[0x20]==2) {
                    alpha=func_00283CE0(opacity)*func_00283CE0(RI(data,0x34));
                    color=(color&0xFFFFFF)+(func_00283CF0(alpha/((ref_PAL_L06_004046D8_00*300.0f+2.0f)*0.16666667f))<<24);
                }
                k=0;
                offset=n*64;
                next=n+1;
                quad[1].colors[3]=color;
                quad[1].colors[2]=color;
                quad[1].colors[1]=color;
                quad[1].colors[0]=color;
                for(;k<4;k++) {
                    func_00282CC0(&quad[1].points[k],&D_L06_001AFEA0[k],&((RenderVec (*)[20])(mesh+groupVertices))[j+(k>>1)][order[n]]);
                }
                func_00280B90(&quad[1],matrices+offset,0);
            }
            j=nextRow;
        } while(j<19);
        i=nextGroup;
    } while(i<4);
}
