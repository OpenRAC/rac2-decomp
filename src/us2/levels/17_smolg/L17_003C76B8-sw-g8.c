#include "include_asm.h"

#include "common.h"
typedef unsigned int PlatformQuad __attribute__((mode(TI)));
typedef union { PlatformQuad q; float f[4]; } PlatformVector;
typedef struct { int paths[5]; } PlatformPathRow;
typedef struct {
    u8 pad0[0x3E];
    u16 flags3E;
    u8 pad40[0x50 - 0x40];
    u8 motion[0x8C - 0x50];
    int flags8C;
    float progress;
    int point;
    float field98, pitchSpeed, yawSpeed;
    int selection, sound, enabled;
    int triggers[5];
    int entryPaths[5];
    int middlePaths[5];
    int exitPaths[5];
    u8 pad100[0x114 - 0x100];
    int field114;
    float field118, field11C, field120, field124;
    int path128;
    float startHeight;
} PlatformVars;
typedef struct {
    u8 pad0[0x10];
    PlatformVector position;
    u8 state;
    u8 pad21[0x30 - 0x21];
    u8 opacity, field31;
    short timer;
    u16 flags;
    u8 pad36[0x68 - 0x36];
    PlatformVars *vars;
    u8 pad6C[0x98 - 0x6C];
    int animation;
    u8 pad9C[0xB0 - 0x9C];
    u8 group, fieldB1;
    u16 uid;
    u8 padB4[0xBC - 0xB4];
    u8 choice;
    u8 padBD[0xF0 - 0xBD];
    PlatformVector rotation;
} PlatformMoby;
typedef struct {
    int count;
    u8 pad04[0xC];
    PlatformVector points[2];
} PlatformPath;
extern PlatformPath *D_L17_001FE880[];
extern int D_L17_001B0340 __attribute__((sda));
extern float D_L17_001B034C __attribute__((sda));
extern float D_L17_001B0354 __attribute__((sda));
typedef struct {
    u8 pad0[0x212];
    short mode212, mode214;
    u8 pad216[0x33C - 0x216];
    u8 *groundObject;
    u8 pad340[0x34E - 0x340];
    short mode34E;
} PlatformHero;
extern PlatformHero D_00189E20;
extern float D_00189EA0[];
extern char *D_0018A15C NOT_SDA;
extern int D_001A79F0;
extern u8 D_0019B4A8[], D_0019B2E8[];
typedef struct { u8 pad[0x464]; u8 collected[0]; } L17SaveState;
extern L17SaveState D_L17_0021EBB0;
extern int D_00138324 NOT_SDA;
extern u8 D_L17_001DBF82[];
extern char D_00188660[];
extern int func_L17_003C5DF0(void *);
extern void func_L06_0036F728(void *, int);
extern void func_L03_00339128(void *, void *, int, u32, int, int, int, float);
extern float func_00283248(float, float);
extern void func_0029F338(void *);
extern void func_L17_003C5F58(void *);
extern int func_L17_003C69A8(void *, int, void *);
extern int func_L17_003C6CE8(void *, int, void *);
extern int func_L17_003C5E20(void *);
extern void func_L17_003C5E78(void *);
extern float func_002AAA00(void *, float, void *, float, float, float, int);
extern void func_002B0C28(int, int, int);
extern float func_00282E48(void *, void *);
extern int func_002E59B0(void *, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_002E59F8(int);
extern void func_L17_003C7018(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
static __inline__ void stopSound(u8 *object, PlatformVars *data)
{
    char *sound;

    if (data->sound != -1) {
        sound = D_00188660 + data->sound * 0x70;
        if (*(u8 **)(sound + 0x88) == object && *(u8 *)(sound + 0x74))
            func_002E59F8(data->sound);
    }
    data->sound = -1;
}

/* Updates a ride platform. State 1 idles until triggered; states 3 and 8 wait for input bit 0x10
   from the player standing on it; the others follow its entry, middle or exit path, chosen by
   moby->choice, forwards or back, and stop its sound on the way. */
void func_US2_L17_003C76B8(u8 *object)
{
    PlatformVector oldPosition, oldRotation, delta;
    PlatformMoby *moby = (PlatformMoby *)object;
    PlatformVars *data = moby->vars;

    u16 id;
    PlatformPathRow *exitRow;
    func_L06_0036F728(object, func_L17_003C5DF0(object));
    data->flags8C |= 1;
    data->flags3E |= 8;
    if (D_L17_001B0340) {
        int i;
        for (i = 0; i < D_L17_001FE880[data->entryPaths[0]]->count; i++)
            func_L03_00339128(&D_L17_001FE880[data->entryPaths[0]]->points[i],
                              object, 4, 0x800000FF, 0x7F, 2, 0xFF, 0.333f);
        for (i = 0; i < D_L17_001FE880[data->middlePaths[0]]->count; i++)
            func_L03_00339128(&D_L17_001FE880[data->middlePaths[0]]->points[i],
                              object, 4, 0x8000FF00, 0x7F, 2, 0xFF, 0.333f);
        for (i = 0; i < D_L17_001FE880[data->exitPaths[0]]->count; i++)
            func_L03_00339128(&D_L17_001FE880[data->exitPaths[0]]->points[i],
                              object, 4, 0x80FF0000, 0x7F, 2, 0xFF, 0.333f);
    }
    qcopy(&oldPosition, &moby->position);
    qcopy(&oldRotation, &moby->rotation);
    switch (moby->state) {
    case 0:
        if (data->entryPaths[0] != -1) {
            PlatformPath *path = D_L17_001FE880[data->entryPaths[0]];
            qcopy(&moby->position, &path->points[0]);
            moby->rotation.f[2] = func_00283248(path->points[1].f[0] - moby->position.f[0],
                                           path->points[1].f[1] - moby->position.f[1]);
        } else if (data->middlePaths[0] != -1) {
            PlatformPath *path = D_L17_001FE880[data->middlePaths[0]];
            qcopy(&moby->position, &path->points[0]);
            moby->rotation.f[2] = func_00283248(path->points[1].f[0] - moby->position.f[0],
                                           path->points[1].f[1] - moby->position.f[1]);
        }
        moby->timer = 0;
        moby->opacity = 0xFF;
        data->selection = -1;
        data->sound = -1;
        moby->state = 1;
        moby->flags = (moby->flags | 0x41) & 0xEFFF;
        moby->animation = 0;
        id = moby->uid;
        if (D_L17_0021EBB0.collected[(s16)id]) goto destroy;
        {
            int packed = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];
            if ((id & 1) ? ((packed >> 4) & 7) : (packed & 7)) {
        destroy:
                func_0029F338(object);
                return;
            }
        }
        break;
    case 1: {
        int i;
        if (data->enabled && (D_0019B2E8[moby->group + (D_001A79F0 << 4)] & 0x80)) {
            for (i = 0; i < 5; i++) {
                if (data->triggers[i] != -1 || data->selection == i)
                    func_L17_003C5F58(object);
            }
        }
        break;
    }
    case 2:
        if (data->entryPaths[moby->choice] == -1 ||
            func_L17_003C69A8(object, data->entryPaths[moby->choice], &data->sound)) {
            moby->state = 3;
            data->field114 = -1;
            data->startHeight = moby->position.f[2];
        }
        break;
    case 3:
        func_002AAA00(&moby->rotation.f[1], 0.0f, &data->pitchSpeed,
                     D_L17_001B034C * 4.848137450608192e-06f,
                     D_L17_001B034C * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        func_002AAA00(&moby->rotation, 0.0f, &data->yawSpeed,
                     D_L17_001B0354 * 4.848137450608192e-06f,
                     D_L17_001B0354 * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        if (D_00189E20.groundObject == object && D_00189E20.mode34E == 0) {
            func_002B0C28(10, 0x133F, 1);
            if (D_00138324 & 0x10) {
                data->progress = 0;
                moby->state = 4;
                data->point = 1;
            }
        } else func_L17_003C5F58(object);
        goto updateSound;
    case 4:
        moby->state = 5;
        stopSound(object, data);
        break;
    case 5:
        if (func_L17_003C5E20(object)) {
            D_00189E20.mode212 = 4;
            D_00189E20.mode214 = 4;
        }
        if (func_L17_003C69A8(object, data->middlePaths[moby->choice], &data->sound))
            moby->state = 6;
        else func_L17_003C5E78(object);
        break;
    case 6:
        func_002AAA00(&moby->rotation.f[1], 0.0f, &data->pitchSpeed,
                     D_L17_001B034C * 4.848137450608192e-06f,
                     D_L17_001B034C * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        func_002AAA00(&moby->rotation, 0.0f, &data->yawSpeed,
                     D_L17_001B0354 * 4.848137450608192e-06f,
                     D_L17_001B0354 * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        exitRow = (PlatformPathRow *)data->exitPaths;
        if (exitRow->paths[moby->choice] != -1 &&
            func_00282E48(&moby->position, D_00189EA0) > 15.0f) {
            moby->state = 7;
            data->point = 1;
        } else if (exitRow->paths[moby->choice] == -1 && D_0018A15C != (char *)object)
            moby->state = 1;
        goto updateSound;
    case 8:
        func_002AAA00(&moby->rotation.f[1], 0.0f, &data->pitchSpeed,
                     D_L17_001B034C * 4.848137450608192e-06f,
                     D_L17_001B034C * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        func_002AAA00(&moby->rotation, 0.0f, &data->yawSpeed,
                     D_L17_001B0354 * 4.848137450608192e-06f,
                     D_L17_001B0354 * 4.848137450608192e-06f, 0.20943954586982727f, 0);
        if (D_00189E20.groundObject == object && D_00189E20.mode34E == 0) {
            func_002B0C28(10, 0x133F, 1);
            if (D_00138324 & 0x10) {
                data->progress = 0;
                moby->state = 9;
                data->point = D_L17_001FE880[data->middlePaths[moby->choice]]->count - 2;
            }
        }
updateSound:
        if (!func_002E59B0(object, data->sound) && D_L17_001DBF82[0] != 0xFF)
            data->sound = func_002E5DA0(1, 4, object, 0x922);
        break;
    case 9:
        moby->state = 10;
        stopSound(object, data);
        break;
    case 10:
        if (func_L17_003C5E20(object)) {
            D_00189E20.mode212 = 4;
            D_00189E20.mode214 = 4;
        }
        if (func_L17_003C6CE8(object, data->middlePaths[moby->choice], &data->sound))
            moby->state = 6;
        break;
    case 7:
        if (func_L17_003C69A8(object, data->exitPaths[moby->choice], &data->sound)) {
            moby->timer = 0;
            moby->state = 1;
            moby->animation = 0;
        }
        break;
    }
    func_L17_003C7018(object);
    func_00282CF0(&delta, &moby->position, &oldPosition);
    func_002AD6F0(data->motion, &delta, &oldRotation, &moby->rotation);
}
