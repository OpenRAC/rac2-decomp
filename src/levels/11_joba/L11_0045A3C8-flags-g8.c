
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct { float vertex[4][4]; u32 color[4]; float uv[8]; u64 reserved,texture,setup,state; } QuadPacket;
extern void ref_L11_0045A3C8_00(char *);
extern u64 func_0027C878(int);
extern int func_002A7820(int,int);
extern float func_00283248(float,float);
extern float func_00282E80(void *,void *);
extern float func_002A7940(void);
extern void func_00283410(void *,void *);
extern float func_002A7878(float,float);
extern void func_00282D30(void *,void *,float);
extern void func_00280B90(void *,void *,int);
/* Observed target prefix: retail addresses its position at base + 0x140. */
typedef struct { u8 reserved[0x140]; float position[4]; } FlareTargetView;
extern FlareTargetView D_L11_001BA780 __attribute__((nosda));
extern u32 D_L11_001B2014 __attribute__((sda));

/* Submit one billboarding flare at the object's current endpoint. */
/* Same body as func_L02_00422BB8, with this function's own callees. */
void func_L11_0045A3C8(u8 *object)
{
    QuadPacket packet;
    float transform[16];
    float rotation[4];
    u8 *state=*(u8 **)(object+0x68);
    float size;
    u32 color;
    ref_L11_0045A3C8_00((char *)&packet);
    packet.texture=func_0027C878(11);
    packet.setup=0xFF9000000260ULL;
    packet.state=0x8000000048ULL;
    packet.reserved=0;
    color=(D_L11_001B2014&0xFFFFFF)+(func_002A7820(32,48)<<24);
    packet.color[3]=color; packet.color[2]=color; packet.color[1]=color; packet.color[0]=color;
    rotation[3]=0;
    rotation[2]=func_00283248(D_L11_001BA780.position[0]-*(float *)(object+0x10),D_L11_001BA780.position[1]-*(float *)(object+0x14));
    rotation[1]=-func_00283248(func_00282E80(object+0x10,D_L11_001BA780.position),D_L11_001BA780.position[2]-*(float *)(object+0x18));
    rotation[0]=func_002A7940();
    func_00283410(transform,rotation);
    transform[12]=*(float *)(object+0x10); transform[13]=*(float *)(object+0x14); transform[14]=*(float *)(object+0x18); transform[15]=1;
    size=func_002A7878(0.35f,0.45f)**(float *)(state+0x60);
    func_00282D30(packet.vertex[0],packet.vertex[0],size);
    func_00282D30(packet.vertex[1],packet.vertex[1],size);
    func_00282D30(packet.vertex[2],packet.vertex[2],size);
    func_00282D30(packet.vertex[3],packet.vertex[3],size);
    func_00280B90(&packet,transform,0);
}
