#include "common.h"

/* Work record of the cloud objects: velocity at +0x00, the spawner's argument, a timer
   and the index of the start point in D_L10_002BABF0. */
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
Actor *cloud_spawn_object(int arg)
{
    Actor *cloud;
    CloudWork *work;
    int index;
    int kind = math_random_int_below(5);

    if (kind == 0) cloud = CreateMoby(0x1315 /* moby class 4885 */);
    else if (kind == 1) cloud = CreateMoby(0x1328 /* moby class 4904 */);
    else cloud = CreateMoby(0x1327 /* moby class 4903 */);
    if (cloud) {
        cloud->state = 0;
        cloud->alpha = 255;
        cloud->flags = 255;
        cloud->active = 1;
        work = cloud->work;
        set_moby_color(cloud, 20, 20, 20);
        index = math_random_int_below(5);
        work->index = index;
        qcopy(&cloud->pos, g_cloud_start_points + index * 16);
        cloud->pos[0] += math_random_float_range(5.0f, -5.0f);
        cloud->pos[1] += math_random_float_range(5.0f, -5.0f);
        cloud->pos[2] += math_random_float_range(5.0f, -5.0f);
        cloud->rx = math_random_angle();
        cloud->ry = math_random_angle();
        cloud->rz = math_random_angle();
        work->timer = math_random_int_below(3600);
        work->arg = arg;
        if (!g_cloud_boss_actor) {
            Actor *node = g_cloud_object_list;
            while (node) {
                if (node->kind == 0xFBF /* moby class 4031 */) g_cloud_boss_actor = node;
                node = node->next;
            }
        }
        if (cloud->kind == 0x1315 /* moby class 4885 */)
            cloud->scale = *(float *)(cloud->classData + 0x24) * 1.5f;
        else if (cloud->kind == 0x1328 /* moby class 4904 */)
            cloud->scale = *(float *)(cloud->classData + 0x24);
        else if (cloud->kind == 0x1327 /* moby class 4903 */)
            cloud->scale = *(float *)(cloud->classData + 0x24) * 1.5f;
        return cloud;
    }
    return 0;
}
