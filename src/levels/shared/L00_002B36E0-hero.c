#include "common.h"

typedef int HeroHistoryVector __attribute__((mode(TI)));
typedef struct {
    char pad[0x1454];
    short timer;
} TimerState;

typedef struct {
    char pad0[0x98];
    float yaw;
    char pad9c[0x270 - 0x9c];
    int field270;
    char pad274[0x1454 - 0x274];
    short timer;
    char pad1456[0x1d90 - 0x1456];
    HeroHistoryVector positions[32];
    char pad1f90[0x1fb0 - 0x1f90];
    float stick_x, stick_y;
    char pad1fb8[0x2294 - 0x1fb8];
    int state;
    char pad2298[0x22c3 - 0x2298];
    unsigned char gravity_mode;
    char pad22c4[0x233c - 0x22c4];
    float yaws[32];
    int yaw_index, yaw_count, position_index, position_count;
    char pad23cc[0x24b8 - 0x23cc];
    float speed, raw_speed;
} HeroFrame;

typedef struct {
    char pad[0x108];
    float x, y;
    char pad2[0x1a0 - 0x110];
    int flags;
    char pad3[0xc];
    int buttons;
} InputState;

extern HeroFrame g_hero_state;
extern char D_0018BE50[];
extern InputState g_pad_state;
extern void func_L00_002EDD78(void *);
extern int hero_get_movement_mode(void);
extern float func_L00_002EE268(void *);
extern void hero_l00_update_state_machine(void);
extern void func_L00_002EE970(void *, void *);
extern void func_L00_002EE8E8(void *);
extern void func_L00_002EEBF8(void *, void *);
extern void hero_update_collision_capsule(void);
extern void hero_probe_ground_and_ledge(void);
extern void hero_l00_update_timers(void);
extern float hero_get_stick_magnitude(void);

/* Updates input and history rings, then refreshes the hero's movement matrices. */
void UpdateHeroInputAndHistory(void)
{
    HeroFrame *p;
    int bits;

    qcopy(D_0018BE50, D_0018BE50 - 0x1fb0);
    if (g_pad_state.flags & 3) {
        if (((TimerState *)(D_0018BE50 - 0x2030))->timer <= 0)
            ((TimerState *)(D_0018BE50 - 0x2030))->timer = 1;
    } else {
        func_L00_002EDD78(D_0018BE50 - 0xbdc);
    }
    p = &g_hero_state;
    if (p->state == 16)
        p->timer = 0;
    {
        int active = hero_get_movement_mode();
        p->stick_x = g_pad_state.x;
        p->gravity_mode = active;
        p->stick_y = g_pad_state.y;
    }
    p->field270 = 0;
    p->raw_speed = hero_get_stick_magnitude();
    if (func_L00_002EE268(&p->stick_x) < 0.25f) {
        bits = g_pad_state.buttons;
        {
            int right = (bits >> 13) & 1;
            int left = (bits >> 15) & 1;
            int down = (bits >> 14) & 1;
            int up = (bits >> 12) & 1;
            left = right - left;
            up = down - up;
            p->stick_x = left;
            p->stick_y = up;
        }
    }
    p->speed = hero_get_stick_magnitude();
    hero_l00_update_state_machine();
    p->yaws[p->yaw_index] = p->yaw;
    p->yaw_index = (p->yaw_index + 1) % 32;
    if (++p->yaw_count > 32)
        p->yaw_count = 32;
    {
        HeroHistoryVector *history = p->positions;
        /* The next accesses update the ring counters, outside the copied vector. */
        qcopy_nc(&history[p->position_index], (char *)p + 0x80);
    }
    p->position_index = (p->position_index + 1) % 32;
    if (++p->position_count > 32)
        p->position_count = 32;
    func_L00_002EE970(p, (char *)p + 0x90);
    func_L00_002EE8E8((char *)p + 0x40);
    func_L00_002EEBF8((char *)p + 0x40, p);
    hero_update_collision_capsule();
    hero_probe_ground_and_ledge();
    hero_l00_update_timers();
}
