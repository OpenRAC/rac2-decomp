/* functional: high. Same calls, arguments, reads and writes as retail; the 16-byte lq/sq copies of the position and velocity are four word copies (same bytes). Like retail, it takes source->position even when source is null. */

/* Spawns a bolt pickup (SpawnBoltByValue) of denomination `value` at `position` with `velocity`: when the
 * position is 64 or more from the camera (D_001B5340) it only adds the value to the bolt count D_001A7A14 and
 * returns 0. Otherwise it creates the moby of the denomination's class (13..19, scale D_001AE8B0..D_001AE8C8),
 * parents it to source's top-most parent, sets its draw state, colour and render command, copies position and
 * velocity, randomises its flip/angle/phase, spins it around velocity x (source - bolt), and when flags & 2
 * attaches it (func_003022A0) at a random +-30 degree angle if flags & 0x10. Returns the moby. */

typedef struct {
    char pad00[0x20];
    float velocity[4];  /* 0x20 */
    float spin[4];      /* 0x30 */
    unsigned char kind; /* 0x40 */
    char pad41[0xF];
    float angle;        /* 0x50 */
    char pad54;
    unsigned char flags;/* 0x55 */
    char pad56[2];
    float phase;        /* 0x58 */
    char pad5c[0xC];
    float startZ;       /* 0x68 */
} BoltSpawnVars;

typedef struct { char pad00[0x24]; float scale; } BoltSpawnClass;

typedef struct BoltSpawnMoby {
    char pad00[0x10];
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[3];
    BoltSpawnClass *objectClass;/* 0x24 */
    char pad28[4];
    float scale;                /* 0x2C */
    unsigned char updateDistance;/* 0x30 */
    unsigned char visible;      /* 0x31 */
    short drawDistance;         /* 0x32 */
    unsigned short flags;       /* 0x34 */
    char pad36[0x2d];
    unsigned char life;         /* 0x63 */
    char pad64[4];
    BoltSpawnVars *vars;        /* 0x68 */
    char pad6c[0x4c];
    struct BoltSpawnMoby *parent;/* 0xB8 */
    char padbc[4];
    float orientation[3][4];    /* 0xC0 */
    float rotation[4];          /* 0xF0 */
} BoltSpawnMoby;

extern float D_001B5340[];
extern int D_001A7A14;
extern float D_001AE8B0, D_001AE8B4, D_001AE8B8, D_001AE8BC, D_001AE8C0, D_001AE8C4, D_001AE8C8;
extern int D_001AE8E0;
extern int D_0018C0B0;

extern float func_00282E48(void *, void *);
extern BoltSpawnMoby *func_0029EFD0(int);
extern void func_002833F0(void *, void *);
extern void func_002AEC18(void *, int);
extern void func_002A04B8(void *, int *, int *, int *);
extern void func_002A0468(unsigned long long *, unsigned long long, unsigned long long, unsigned long long, unsigned long long);
extern void func_002A0488(void *, int, int, int);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern int func_003022A0(void *, int, float, float);
extern void func_002A0F48(void *);

BoltSpawnMoby *func_00302470(BoltSpawnMoby *source, float *position, float *velocity, unsigned int flags, int value, int kind)
{
    BoltSpawnMoby *object, *parent;
    BoltSpawnVars *state;
    float difference[4], crossed[4];
    int red, green, blue;
    float scale, spin, angle, distance;
    int i;

    distance = func_00282E48(position, D_001B5340);
    if (64.0f <= distance) {
        D_001A7A14 += value;
        return 0;
    }
    switch (value) {
    case 5:    object = func_0029EFD0(14); scale = D_001AE8B4; break;
    case 20:   object = func_0029EFD0(15); scale = D_001AE8B8; break;
    case 50:   object = func_0029EFD0(16); scale = D_001AE8BC; break;
    case 100:  object = func_0029EFD0(17); scale = D_001AE8C0; break;
    case 500:  object = func_0029EFD0(18); scale = D_001AE8C4; break;
    case 1000: object = func_0029EFD0(19); scale = D_001AE8C8; break;
    default:   object = func_0029EFD0(13); scale = D_001AE8B0; break;
    }
    if (object == 0)
        return 0;

    state = object->vars;
    state->kind = (unsigned char)kind;
    parent = source;
    if (parent != 0)
        while (parent->parent != 0)
            parent = parent->parent;
    object->flags |= 0x100;
    object->life = 20;
    object->state = 1;
    object->visible = 1;
    object->updateDistance = 64;
    object->drawDistance = 64;
    object->parent = parent;
    object->scale = object->objectClass->scale * scale;
    func_002833F0(object->orientation, object->rotation);
    func_002AEC18(object, D_001AE8E0);
    func_002A04B8(object, &red, &green, &blue);
    func_002A0468((unsigned long long *)object, 0, 13, 0, 0);
    func_002A0488(object, red, green, blue);
    for (i = 0; i < 4; i++)
        object->position[i] = position[i];
    for (i = 0; i < 4; i++)
        state->velocity[i] = velocity[i];
    if (func_002A77E0(2))
        state->flags |= 1;
    state->angle = func_002A7940();
    state->phase = func_002A7940();
    state->startZ = object->position[2];
    spin = func_002A7878(0.0f, 720.0f) * 0.00029088825f;
    func_00282CF0(difference, source->position, object->position);
    func_00282DD8(crossed, state->velocity, difference);
    func_00282F20(state->spin, crossed, 1.0f);
    func_002AB668(state->spin, state->spin, spin);
    if (flags & 2) {
        angle = 0.0f;
        if (flags & 0x10)
            angle = func_002A7878(-30.0f, 30.0f) * 0.017453294f;
        func_003022A0(object, D_0018C0B0, angle, 0.0f);
    }
    func_002A0F48(object);
    return object;
}
