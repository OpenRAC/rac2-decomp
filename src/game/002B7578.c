#include "names.h"
/* Adapted from RAC1 src/game/music.c music_Update (GPL-3.0); RAC2 layout and behavior measured from retail. */
typedef struct { unsigned int handle; short track,volume,flags,state,fade_flags,unknown,crossfade_enabled,unknown2; int poll_interval,remaining_time,unknown1C,slot; } Channel;
typedef struct { int unknown0; short read_state; unsigned char break_requested,updates_suspended; int read_sector,unknownC,read_sector_count,read_dst; void (*callback)(int,int); int callback_data,unknown20,queued_secondary_track,queued_volume; short crossfade_state,pad2E; int crossfade_remaining_time,crossfade_interval,retry_timer; short requested_track,requested_transition_track; int mode; Channel primary,secondary,transition; } State;
extern unsigned char D_001A63A8[];
#define S (*(State *)D_001A63A8)
extern int func_00282948(void *);
extern void func_002B6E78(int,int,int),func_002B6F70(int,int,int),func_002B6D80(int,int,int);
extern int func_002B7088(int,int,int,int);
extern void func_002B6958(int,int,int,int);
extern void func_00132BC0(int,int,int,int,int,int,void (*)(int,long),long);
extern void func_002B7FF0(int,long),func_00133400(int),func_002B7380(void *);
extern int func_00133580(int),func_002B7B18(int,int,int);
extern void func_0026FEB8(void *);
extern char D_001AA1B0[],D_001AA1C0[],D_001AA1D0[];
/* Runs the music system once per frame: starts and swaps tracks, fades between them, updates the three channels and continues disc reads. */
void func_002B7578(void) {
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
            StartMusicStreamNoLoop(S.primary.track, (short)S.primary.flags,
                              S.primary.volume);
        } else if (S.primary.handle != 0) {
            if (S.primary.handle != 0xFFFFFFFF && S.primary.state == 8) {
                QueueMusicTransitionStream(S.primary.track, S.primary.flags,
                                       S.primary.volume);
            }
        }
    }
    if (FastFloatHelperD(&S.retry_timer) != 0) {
        requested_track = S.requested_track;
        if (requested_track != -1 && S.crossfade_state == 0) {
            if (S.primary.track != requested_track) {
                if (S.requested_transition_track == -1) {
                    if (S.primary.state & 0x8000) {
                        S.crossfade_state=3;
                        S.primary.state=5;
                    } else {
                        S.crossfade_interval=15;
                        S.transition.remaining_time=15;
                        S.crossfade_state=6;
                    }
                    S.retry_timer=300;
                } else if (StartMusicTransition(requested_track,S.requested_transition_track,S.primary.flags,S.primary.volume)) {
                    S.retry_timer=420;
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
            PlaySoundStreamById(S.queued_secondary_track, 0, S.queued_volume, 0x400);
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
            func_00132BC0(handle,5,fade_volume,0,0,0,StoreRequestResultOnce,(long)&S.primary.handle);
            if(FastFloatHelperD(&S.transition.remaining_time)) { S.crossfade_state=3; S.primary.state=5; }
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
                func_00132BC0(handle, 5, fade_volume, 0, 0, 0, StoreRequestResultOnce,
                                        (long)&S.primary.handle);
            }
            break;
        case 3:
            if (S.primary.state == 0 && (S.transition.crossfade_enabled != 0 ||
                                                   S.transition.handle == 0)) {
                StartMusicStream(S.requested_track, S.primary.flags,
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
                    SendSoundCommand46(S.primary.handle);
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
    UpdateMusicChannel(&S.primary.handle);
    UpdateMusicChannel(&S.transition.handle);
    UpdateMusicChannel(&S.secondary.handle);
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
            StartDiscRead(S.read_dst, S.read_sector,
                                    S.read_sector_count);
            if (S.read_state == 0) {
                S.read_state = pending_state;
            }
        }
    }
}
