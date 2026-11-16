#include "include_asm.h"

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
extern char g_hero_state_block_2[];
extern InputState g_pad_state;
extern int FastDecTimer(void *);
extern int hero_get_movement_mode_pal(void);
extern float vec_length_xy(void *);
extern void hero_l00_update_state_machine_pal(void);
extern void euler_to_matrix(void *, void *);
extern void set_identity_matrix(void *);
extern void matrix_from_basis_rows(void *, void *);
extern void hero_update_collision_capsule_pal(void);
extern void hero_probe_ground_and_ledge_pal(void);
extern void hero_l00_update_timers_pal(void);
extern float hero_get_stick_magnitude(void);

/* Updates input and history rings, then refreshes the hero's movement matrices. */
void UpdateHeroInputAndHistory_pal(void)
{
    HeroFrame *p;
    int bits;

    qcopy(g_hero_state_block_2, g_hero_state_block_2 - 0x1fb0);
    if (g_pad_state.flags & 3) {
        if (((TimerState *)(g_hero_state_block_2 - 0x2030))->timer <= 0)
            ((TimerState *)(g_hero_state_block_2 - 0x2030))->timer = 1;
    } else {
        FastDecTimer(g_hero_state_block_2 - 0xbdc);
    }
    p = &g_hero_state;
    if (p->state == 16)
        p->timer = 0;
    {
        int active = hero_get_movement_mode_pal();
        p->stick_x = g_pad_state.x;
        p->gravity_mode = active;
        p->stick_y = g_pad_state.y;
    }
    p->field270 = 0;
    p->raw_speed = hero_get_stick_magnitude();
    if (vec_length_xy(&p->stick_x) < 0.25f) {
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
    hero_l00_update_state_machine_pal();
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
    euler_to_matrix(p, (char *)p + 0x90);
    set_identity_matrix((char *)p + 0x40);
    matrix_from_basis_rows((char *)p + 0x40, p);
    hero_update_collision_capsule_pal();
    hero_probe_ground_and_ledge_pal();
    hero_l00_update_timers_pal();
}
