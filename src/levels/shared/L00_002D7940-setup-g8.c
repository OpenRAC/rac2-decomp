#include "common.h"

typedef struct { float x,y,z,w; } CameraVec9E;
typedef struct {
    char pad00[0x20];
    CameraVec9E up, target, previous, velocity, hero;
    char pad70[0xac-0x70];
    float yaw0, yaw1, yaw2, yaw3, yaw4;
    int c0, c4, c8, cc;
    char padd0[0xe4-0xd0];
    int e4, e8, ec;
} CameraFollow9E;
typedef struct {
    short phase; char pad002[0x110-2]; int unknown[5];
} CameraBlend9E;
typedef struct {
    char pad000[0x194];
    int previous;
    char pad198[8];
    CameraFollow9E follow;
    CameraBlend9E blend;
    char pad3b4[12];
    CameraVec9E clear;
    char pad3d0[0x30];
    int frames, underwater;
} CameraState9E;
typedef struct {
    char pad00[0x74]; int activation; float blend_time;
    u8 priority, handoff; short transition, field80, field82, index, id;
    char field88; u8 hit; short snap, type, hard_cut;
    char pad90[16];
} CameraSlot9E;
typedef struct {
    int field0; CameraSlot9E *slot;
    char pad08[0x1c-8]; u8 priority, field1d, field1e, activation;
} CameraInfo9E;
typedef struct {
    char pad00[12]; unsigned short id; char pad0e[14]; CameraInfo9E *info;
} CameraDef9E;
typedef struct {
    char pad00[0x80]; CameraVec9E pos;
    char pad90[8]; float yaw;
    char pad9c[0x2290-0x9c]; char *object;
} CameraHero9E;
extern CameraState9E D_L00_001B8C80;
extern CameraSlot9E D_L00_001B91D0[];
extern int D_L00_001BB930[];
extern CameraHero9E g_hero_state;
extern float D_001A8900 __attribute__((sda));
extern int D_L00_001B1840 MACRO_ADDR, D_L00_001B1848 MACRO_ADDR;
extern CameraDef9E *D_L00_001B1844 MACRO_ADDR;
extern void cam_clear_override_slots(void),cam_l00_init_blend_values(void),cam_reset_default(void);
extern int cam_find_entry_index(int);
extern void func_L00_002EE3D0(void *,void *,float);
extern void func_L00_002EE0D0(void *);

/* SetupLevelCameras: the layout and initialization sequence correspond to RAC1's
   setup_level_cameras (rac1-decomp src/overlays/shared/level_camera_setup.c, GPL-3.0),
   with RAC2 offsets measured from the retail body. As in RAC1 the second block takes a
   fresh state pointer (g1). The descriptor address is summed as an integer, offset
   first, which is the operand order retail's addu has without RAC1's -fno-force-mem. */
/* Resets all level cameras when a level starts. */
void SetupLevelCameras(void) {
    CameraState9E *cam_state = &D_L00_001B8C80;
    CameraState9E *cam_state2;
    CameraFollow9E *follow;
    CameraVec9E *up;
    CameraHero9E *hero;
    int i,slot_index;
    cam_state->frames=0;
    cam_state->underwater=0;
    D_001A8900=0.85f;
    D_L00_001B1840=0;
    for(slot_index=0;slot_index<48;slot_index++) {
        D_L00_001B91D0[slot_index].hard_cut=0;
        D_L00_001BB930[slot_index]=0;
    }
    cam_clear_override_slots();
    cam_l00_init_blend_values();
    cam_state2=&D_L00_001B8C80;
    cam_state2->previous=0;
    cam_state2->blend.phase=0;
    qzero_nc(&cam_state2->clear);
    follow=&D_L00_001B8C80.follow;
    hero=&g_hero_state;
    up=&follow->up;
    func_L00_002EE3D0(up,hero->object+0xe0,1.0f);
    qcopy(&follow->target,up);
    qcopy(&follow->previous,up);
    func_L00_002EE0D0(&follow->velocity);
    qcopy(&follow->hero,&hero->pos);
    {
        float yaw=hero->yaw;
        follow->c4=0;
        follow->e4=0;
        follow->c0=0;
        follow->cc=0;
        follow->e8=0;
        follow->yaw4=yaw;
        follow->yaw3=yaw;
        follow->yaw2=yaw;
        follow->yaw1=yaw;
        follow->yaw0=yaw;
    }
    i=0;
    if(D_L00_001B1848>0) do {
        int off=i*32;
        CameraDef9E *source=(CameraDef9E *)(off+(int)D_L00_001B1844);
        CameraInfo9E *object=source->info;
        CameraSlot9E *entry=&D_L00_001B91D0[i];
        int id;
        entry->index=i;
        object->slot=entry;
        entry->hard_cut=0;
        entry->hit=0;
        entry->snap=0;
        entry->field82=-1;
        entry->field80=-1;
        entry->handoff=0;
        entry->transition=0;
        entry->blend_time=-1.0f;
        entry->priority=object->priority;
        entry->activation=object->activation;
        id=source->id;
        D_L00_001BB930[i]=1;
        entry->id=id;
        entry->type=cam_find_entry_index((short)id);
        i++;
    } while(i<D_L00_001B1848);
    cam_reset_default();
    {
        CameraBlend9E *b=&D_L00_001B8C80.blend;
        int *u=b->unknown;
        b->phase=0;
        u[0]=0;
        u[3]=0;
        u[1]=0;
        u[4]=0;
    }
}
