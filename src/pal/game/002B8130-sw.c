#include "include_asm.h"
#include "names.h"

typedef struct { unsigned int handle; short track,volume,flags,state,fade_flags,unknown,crossfade_enabled,unknown2; int poll_interval,remaining_time,unknown1C,slot; } Channel;
typedef struct { int unknown0; short read_state; unsigned char break_requested,updates_suspended; int read_sector,unknownC,read_sector_count,read_dst; void (*callback)(int,int); int callback_data,unknown20,queued_secondary_track,queued_volume; short crossfade_state,pad2E; int crossfade_remaining_time,crossfade_interval,retry_timer; short requested_track,requested_transition_track; int mode; Channel primary,secondary,transition; } State;
extern unsigned char g_music_state[];
#define S (*(State *)D_001A63A8)
extern int math_fast_float_d(void *);
extern void snd_start_music_stream_no_loop(int,int,int),snd_queue_music_transition_stream(int,int,int),snd_start_music_stream(int,int,int);
extern int snd_start_music_transition(int,int,int,int);
extern void snd_play_stream_by_id(int,int,int,int);
extern void snd_send_cmd21_callback(int,int,int,int,int,int,void (*)(int,long),long);
extern void request_store_result_once(int,long),snd_send_cmd46(int),snd_update_music_channel(void *);
extern int snd_CheckLoadInProgress(int),load_start_disc_read(int,int,int);
extern void STUB_printf(void *);
extern char D_001AA1B0[],D_001AA1C0[],D_001AA1D0[];

void func_PAL_002B8130(void) {
    short requested_track;
    int fade_volume;
    int handle;
    short pending_state;

    if (S.updates_suspended != 0) {
        return;
    }
    if (!(S.primary.fade_flags & 0x8000) && !(S.primary.state & 0x8000)) {
        if (S.primary.handle == 0 && (S.primary.flags & 1) &&
            S.requested_track == -1) {
            snd_start_music_stream_no_loop(S.primary.track, (short)S.primary.flags,
                              S.primary.volume);
        } else if (S.primary.handle != 0) {
            if (S.primary.handle != 0xFFFFFFFF && S.primary.state == 8) {
                snd_queue_music_transition_stream(S.primary.track, S.primary.flags,
                                       S.primary.volume);
            }
        }
    }
    if (math_fast_float_d(&S.retry_timer) != 0) {
        requested_track = S.requested_track;
        if (requested_track != -1 && S.crossfade_state == 0) {
            if (S.primary.track != requested_track) {
                if (S.requested_transition_track == -1) {
                    if (S.primary.state & 0x8000) {
                        S.crossfade_state=3;
                        S.primary.state=5;
                    } else {
                        S.crossfade_interval=12;
                        S.transition.remaining_time=12;
                        S.crossfade_state=6;
                    }
                    S.retry_timer=250;
                } else if (snd_start_music_transition(requested_track,S.requested_transition_track,S.primary.flags,S.primary.volume)) {
                    S.retry_timer=350;
                }
            } else {
                S.requested_track = -1;
            }
        }
    }
    if (S.queued_secondary_track >= 0) {
        if (S.secondary.handle != 0) {
            if ((unsigned short)S.secondary.state - 6 >= 2U) {
                S.secondary.state = 5;
            }
        } else {
            snd_play_stream_by_id(S.queued_secondary_track, 0, S.queued_volume, 0x400);
            S.queued_volume=0;
            S.queued_secondary_track = -1;
        }
    }
    if (S.primary.state != 9 && S.primary.handle != 0xFFFFFFFF &&
        !(S.primary.fade_flags & 0x8000) && !(S.primary.state & 0x8000) &&
        (S.requested_transition_track == -1 || (!(S.transition.fade_flags & 0x8000) && !(S.transition.state & 0x8000)))) {
        switch (S.crossfade_state) {
        case 6:
            fade_volume=S.primary.volume*S.transition.remaining_time/S.crossfade_interval;
            handle=S.primary.handle;
            S.primary.handle=0xFFFFFFFF;
            snd_send_cmd21_callback(handle,5,fade_volume,0,0,0,request_store_result_once,(long)&S.primary.handle);
            if(math_fast_float_d(&S.transition.remaining_time)) { S.crossfade_state=3; S.primary.state=5; }
            break;
        case 2:
            /* Fade the primary stream against the transition's remaining time. */
            fade_volume =
                S.primary.volume *
                (S.crossfade_interval -
                 (S.crossfade_remaining_time - S.transition.remaining_time)) /
                S.crossfade_interval;
            if (fade_volume <= 0 ||
                ((S.transition.state != 4 ||
                  S.transition.crossfade_enabled == 0) &&
                 S.transition.handle == 0) ||
                (handle = S.primary.handle) == 0) {
                S.crossfade_state = 3;
                S.primary.state = 5;
            } else if (S.primary.state != 9) {
                /* The callback receives the old handle; mark its slot pending before submission. */
                *(unsigned int *)&S.primary.handle = 0xFFFFFFFF;
                snd_send_cmd21_callback(handle, 5, fade_volume, 0, 0, 0, request_store_result_once,
                                        (long)&S.primary.handle);
            }
            break;
        case 3:
            if (S.primary.state == 0 && (S.transition.crossfade_enabled != 0 ||
                                                   S.transition.handle == 0)) {
                snd_start_music_stream(S.requested_track, S.primary.flags,
                                    S.primary.volume);
                S.requested_track = -1;
                S.crossfade_state = 4;
            }
            break;
        case 4:
            if (S.primary.state == 3) {
                if (S.transition.remaining_time < S.crossfade_interval ||
                    S.transition.state != 4 ||
                    (S.transition.crossfade_enabled == 0 &&
                     S.transition.handle == 0)) {
                    snd_send_cmd46(S.primary.handle);
                    S.primary.state = 8;
                    S.crossfade_state = 5;
                }
            }
            break;
        case 5:
            if (S.transition.state != 4 ||
                S.transition.crossfade_enabled == 0) {
                S.crossfade_state = 0;
            }
            break;
        }
    }
    snd_update_music_channel(&S.primary.handle);
    snd_update_music_channel(&S.transition.handle);
    snd_update_music_channel(&S.secondary.handle);
    if (S.break_requested != 0) {
        STUB_printf(D_001AA1B0);
        if (snd_CheckLoadInProgress(1) == 0) {
            S.read_state = 0;
            S.break_requested = 0;
            STUB_printf(D_001AA1C0);
            if(S.callback) { void (*cb)(int,int)=S.callback; int data=S.callback_data; S.callback=0; S.callback_data=0; STUB_printf(D_001AA1D0); cb(data,0); }
        }
    } else {
        pending_state = S.read_state;
        if (pending_state == 2) {
            S.read_state = 0;
            load_start_disc_read(S.read_dst, S.read_sector,
                                    S.read_sector_count);
            if (S.read_state == 0) {
                S.read_state = pending_state;
            }
        }
    }
}
