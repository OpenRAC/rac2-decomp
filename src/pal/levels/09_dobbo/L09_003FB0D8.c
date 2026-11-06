#include "include_asm.h"
#include "common.h"

/* func_PAL_L09_003FB0D8, the PAL copy of func_L09_003F6820: the same C, where the duration is scaled
   to 50 Hz before both of its uses and func_002A7470 becomes the release's own func_PAL_002A7E68. */

extern unsigned char *func_0029EFD0(int);
extern float func_00283CE0(int);
extern void func_002A7750(unsigned char *, int, int);
extern void func_PAL_002A7E68(unsigned char *, int, int, int);
extern float func_002A7940(void);

typedef struct DobboMoby DobboMoby;

/* State block of a beam link (class 0xD09), at its +0x68. */
typedef struct {
    float direction[4];
    float velocity[4];
    DobboMoby *owner;
    DobboMoby *partner;
    float radius;
    float f2c;
    int timer;
    float max_distance;
    float duration_f;
    int hit_timer;
} DobboLinkState;

typedef struct {
    char pad00[0x24];
    float scale;
} DobboMobyClass;

/* Fields shared by the beam link and its owner. */
struct DobboMoby {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[2];
    unsigned char alpha;
    DobboMobyClass *cls;
    char pad28[4];
    float scale;
    unsigned char f30;
    unsigned char f31;
    unsigned short f32;
    unsigned short flags;
    char pad36[0x43 - 0x36];
    unsigned char f43;
    char pad44[4];
    float f48;
    char pad4C[0x60 - 0x4C];
    unsigned char f60;
    char pad61[0x68 - 0x61];
    DobboLinkState *data;
    char pad6C[0xAA - 0x6C];
    short type;
    char padAC[0xBC - 0xAC];
    unsigned char f_bc;
    char padBD[0xF0 - 0xBD];
    float rotation[3];
};

/* Spawns a beam-link moby (class 0xD09) at the given position with a random rotation, the
   class scale and the given direction, owner, partner link, radius, range and duration. A spawn
   without a partner also sets byte 0xBC. Returns the moby, or NULL if none was available. */
DobboMoby *func_PAL_L09_003FB0D8(void *position, void *direction, DobboMoby *owner, DobboMoby *partner,
                                 int duration, float radius, float f2c, float max_distance)
{
    DobboMoby *moby = (DobboMoby *)func_0029EFD0(0xD09);
    DobboLinkState *state;

    if (moby) {
        moby->f30 = 255;
        moby->f32 = 255;
        moby->f31 = 1;
        state = moby->data;
        moby->rotation[2] = func_002A7940();
        moby->rotation[1] = func_002A7940();
        moby->rotation[0] = func_002A7940();
        moby->scale = moby->cls->scale;
        state->owner = owner;
        moby->flags |= 0x2200;
        qcopy(moby->position, position);
        qcopy(state->direction, direction);
        qzero(state->velocity);
        state->radius = radius;
        state->f2c = f2c;
        state->partner = partner;
        duration = ((s32)(duration) * 5 + 2) / 6;
        state->timer = duration;
        state->duration_f = func_00283CE0(duration);
        state->max_distance = max_distance;
        moby->alpha = 0;
        /* stored as !partner: a plain 1 here is not what retail emits */
        if (!partner)
            moby->f_bc = !partner;
        if (moby->f43)
            func_PAL_002A7E68((unsigned char *)moby, 0, 0, 1);
        moby->f31 = 0;
        moby->f48 = 0.5f;
        moby->flags |= 1;
        func_002A7750((unsigned char *)moby, 0, -1);
    }
    return moby;
}
