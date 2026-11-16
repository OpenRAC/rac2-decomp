#include "common.h"

typedef struct { int time; short counter,delay,active,pad; } Event;
extern Event g_ring_table[];
extern int g_orb_burst_pending __attribute__((sda));
extern int g_orb_delay_time __attribute__((sda));
extern float g_orb_speed_param __attribute__((sda));
extern float g_orb_rate_scale __attribute__((sda));
extern short g_ring_start_alpha __attribute__((sda));
extern int g_ring_timer MACRO_ADDR;
extern int g_ring_blocked;
extern int g_ring_growth_frames;
extern float g_ring_growth_rate;

extern int FloatToInt(float);
extern float IntToFloat(int);
extern int math_fast_float_d(int *);
extern int FastDecTimer(void *);

/* func_PAL_L00_003B7A10, the PAL copy of func_L00_003B4018: the same C, with the frame time 1/50 and the next time scaled to 50 Hz. */
/* Updates the timed rings: starts a new one when the timer is up and ages the active ones. (PAL: 50
 * Hz timings) */
void update_timed_events_pal(void)
{
    if(g_orb_burst_pending) {
        int i;
        for(i=9;i>=0;i--) g_ring_table[i].active=0;
        g_orb_burst_pending=0;
        g_ring_timer=0;
        g_ring_growth_frames=FloatToInt(g_orb_speed_param/(g_orb_rate_scale*0.020000001f));
        g_ring_growth_rate=1.0f/IntToFloat(g_ring_growth_frames);
    }
    if(!g_ring_blocked && math_fast_float_d(&g_ring_timer)) {
        int time=g_orb_delay_time;
        short on;
        unsigned short counter=*(unsigned short *)&g_ring_growth_frames;
        unsigned short delay=g_ring_start_alpha;
        int next=g_ring_timer;
        {
        Event *scan=g_ring_table;
        do {
            if(!scan->active) {
                next=((s32)(time)*5+2)/6;
                on=1;
                scan->active=on;
                scan->counter=counter;
                scan->delay=delay;
                break;
            }
            scan++;
        } while ((int)scan<(int)(g_ring_table+10));
        }
        g_ring_timer=next;
    }
    {
    int i;
    for(i=0;i<10;i++) {
        if(g_ring_table[i].active && FastDecTimer(&g_ring_table[i].counter)) g_ring_table[i].active=0;
    }
    }
}
