/* Nonmatching: US696/696 bytes, 0/1; absent from US2 and PAL.
 * Nine checks, including one corrected malformed block. Best profile:
 * -O2 -G0 -ffunction-sections -fno-strength-reduce. Qualified scene donor:
 * levels/10_hrugis_cloud/L10_003170D0-scene.c, func_L10_00317528.
 * Native four-byte D_001A79F0 MACRO_ADDR exactly emits the measured mixed
 * absolute/GP reads; root confirmed this is valid for independently proved
 * complete scalar storage. Snapshot real object-list begin/end once, as
 * retail does. Explicit object cursor plus strength reduction off recovers
 * the indexed 256-byte scan; default strength reduction produces688 bytes,
 * and rerun-loop optimization off drops required FP lifetimes (664 bytes).
 * Remaining: first scene-header/entry cursor priorities and phase-invariant
 * address hoist scheduling. Scoped header/camera views692, no-split688;
 * neither closes instructions. Reopen with new lifetime/scheduling evidence.
 * Local position is a full16-byte event copy. Existing camera prefix includes
 * full48-byte matrix and16-byte position; no shortened owning allocations.
 * 32C700 returns pointer; eight32-bit GPR, two F32, four32-bit stack args
 * independently verified by full retail body, including LW at+E0/E8/F0/F8.
 */
#include "common.h"

/* Scene header and its existing trailing object-pointer array. The zero-size
 * member is an open tail view; it does not bound the owning allocation. */
typedef struct {
    unsigned char reserved00[0x30];
    int mode,frame;
    unsigned char reserved38[0xC];
    short count;
    unsigned char reserved46[0x146];
    unsigned char *objects[0];
} SceneState;
extern SceneState D_L18_001BD4C0 NOT_SDA;
extern int D_001A79F0 MACRO_ADDR;
extern unsigned char *D_L18_001B281C NOT_SDA;
extern unsigned char *D_L18_001B2820 NOT_SDA;
/* Measured camera-field prefix. No allocation is made from this partial view. */
extern struct {
    unsigned char reserved00[0x140];
    float position[4];
    unsigned char reserved150[0x10];
    float intensity;
    int reserved164,duration,reserved16C;
    unsigned char reserved170[0x10];
    float secondaryIntensity;
    int reserved184,secondaryDuration;
    unsigned char reserved18C[0x370-0x18C];
    float matrix[12];
} D_L18_001B9680 NOT_SDA;
typedef struct {
    float position[4];
    int frame;
    float scale;
    int cameraRelative;
    float shake;
} SceneEffect;
extern SceneEffect D_L18_00287D10[] NOT_SDA;
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *,void *,unsigned int,unsigned int,float);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
/* Eight32-bit GPR arguments, two F32s, then four32-bit stack arguments.
 * Retail uses LW for every incoming stack argument and returns its object. */
extern void *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);

void func_L18_003170F8(void)
{
    float position[4] __attribute__((aligned(16)));
    int i;
    unsigned char **entry;
    func_L00_002FC980();
    for(i=0,entry=D_L18_001BD4C0.objects;i<D_L18_001BD4C0.count;i++,entry++) {
        unsigned char *object=*entry;
        if(object && *(short *)(object+0xAA)==0xE29)
            *(unsigned short *)(object+0x34)|=0x800;
        if(*(short *)(object+0xAA)==0xD54) func_002E64A0(object);
        if(object && *(short *)(object+0xAA)==0xFA0) {
            unsigned char *state=*(unsigned char **)(object+0x68);
            if(state) func_L00_00326048(object,state+0xC,0x80AAAAD2,0x80396464,0.06108653545379639f);
        }
    }
    if(D_001A79F0!=18 || D_L18_001BD4C0.mode!=4) return;
    if(D_L18_001BD4C0.frame==1) {
        unsigned char *begin=D_L18_001B281C;
        unsigned char *end=D_L18_001B2820;
        unsigned int i=0;
        while((unsigned int)(begin+(i<<8))<(unsigned int)end) {
            *(unsigned short *)(begin+(i<<8)+0x34)|=0x41;
            i++;
        }
    }
    {
        SceneEffect *effect=D_L18_00287D10;
        int remaining;
        for(remaining=12;remaining>=0;remaining--,effect++) {
            if(D_L18_001BD4C0.frame==effect->frame) {
                qcopy(position,effect->position);
                if(effect->cameraRelative) {
                    func_00283098(position,position,D_L18_001B9680.matrix);
                    func_00282CC0(position,position,D_L18_001B9680.position);
                }
                func_0032C700(position,0,25,20,20,20,45,1,effect->scale,20.0f,1,1,0,0);
                if(effect->shake>0.0f) {
                    float primary=effect->shake*0.08f;
                    float secondary=effect->shake*0.07f;
                    D_L18_001B9680.duration=55;
                    D_L18_001B9680.secondaryDuration=70;
                    D_L18_001B9680.reserved16C=0;
                    D_L18_001B9680.secondaryIntensity=secondary;
                    D_L18_001B9680.intensity=primary;
                }
            }
        }
    }
}
