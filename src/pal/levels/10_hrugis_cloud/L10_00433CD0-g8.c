#include "include_asm.h"

#include "common.h"
typedef struct {
    float vel[4];
    char pad10[4];
    int arg;
    char pad18[4];
    int timer;
    char pad20[8];
    int index;
} CloudWork;
typedef struct Actor {
    char pad0[0x10];
    float pos[4];
    unsigned char state;
    char pad21[3];
    char *classData;
    struct Actor *next;
    float scale;
    unsigned char alpha, active;
    unsigned short flags;
    char pad34[0x34];
    CloudWork *work;
    char pad6c[0x3E];
    short kind;
    char padac[0x44];
    float rx, ry, rz;
} Actor;
extern int math_random_int_below(int);
extern Actor *CreateMoby(int);
extern void set_moby_color(Actor *, int, int, int);
extern char g_cloud_start_points[];
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern Actor *g_cloud_boss_actor __attribute__((sda));
extern Actor *g_cloud_object_list;

/* Spawns one of three cloud classes (0x1315, 0x1328, 0x1327) at a random start point
   from D_L10_002BABF0, jittered by +-5 on each axis, with a random orientation and
   timer. The first call also caches the last class-0xFBF object of the list in
   D_L10_001B1780. Classes 0x1315 and 0x1327 get 1.5 times their class scale. */
Actor *cloud_spawn_object_pal(int arg)
{
    Actor *actor;
    CloudWork *st;
    int index;
    int kind = math_random_int_below(5);

    if (kind == 0) actor = CreateMoby(0x1315);
    else if (kind == 1) actor = CreateMoby(0x1328);
    else actor = CreateMoby(0x1327);
    if (actor) {
        actor->state = 0;
        actor->alpha = 255;
        actor->flags = 255;
        actor->active = 1;
        st = actor->work;
        set_moby_color(actor, 20, 20, 20);
        index = math_random_int_below(5);
        st->index = index;
        qcopy(&actor->pos, g_cloud_start_points + index * 16);
        actor->pos[0] += math_random_float_range(5.0f, -5.0f);
        actor->pos[1] += math_random_float_range(5.0f, -5.0f);
        actor->pos[2] += math_random_float_range(5.0f, -5.0f);
        actor->rx = math_random_angle();
        actor->ry = math_random_angle();
        actor->rz = math_random_angle();
        st->timer = ((s32)(math_random_int_below(3600)) * 5 + 2) / 6;
        st->arg = arg;
        if (!g_cloud_boss_actor) {
            Actor *cur = g_cloud_object_list;
            while (cur) {
                if (cur->kind == 0xFBF) g_cloud_boss_actor = cur;
                cur = cur->next;
            }
        }
        if (actor->kind == 0x1315)
            actor->scale = *(float *)(actor->classData + 0x24) * 1.5f;
        else if (actor->kind == 0x1328)
            actor->scale = *(float *)(actor->classData + 0x24);
        else if (actor->kind == 0x1327)
            actor->scale = *(float *)(actor->classData + 0x24) * 1.5f;
        return actor;
    }
    return 0;
}
