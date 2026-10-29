/* Nonmatching: US/US2/PAL 644/672 bytes, 0/8 placements each.
 * Four checks. Profile -O2 -G0 -ffunction-sections -fno-rerun-loop-opt.
 * First for-loop form652; explicit bounded edge progression removes a
 * redundant six-edge guard,644. GCSE off652, no-split-addresses644 with
 * different setup. Neither recovers the retail register lifetime pattern.
 * Remaining: register pressure spills oldCount in retail, but carries it in
 * a saved register here; cyclic remainder and adjacency-address priorities,
 * insertion index increment and tail branch scheduling differ accordingly.
 * Reopen with a measured source-layout/allocation witness. Ordinary C only,
 * no fake live values, shortened bounds, volatile or register assignments.
 * RNG takes/returns int32. Existing adjacency rows are24B and state list
 * lives at+0x20; caller owns all storage and limits growth through the real
 * count global. No local buffer is supplied or partially initialized.
 */
#include "common.h"

/* Existing adjacency storage has six 32-bit neighbors per measured row.
 * The owner extent is unknown. The mutable list belongs to the existing
 * state record; this unit does not allocate or shorten either object. */
extern int D_L03_0024A7B0[][6] NOT_SDA;
extern int D_L03_001B0B50;
extern int D_L03_001B0B50_gp SDATA(D_L03_001B0B50);
extern int func_002A77E0(int);

void func_L03_003E2968(unsigned char *object)
{
    unsigned char *state=*(unsigned char **)(object+0x68);
    int count=3;
    state[0x20]=0;
    switch(func_002A77E0(4)) {
    case 0: state[0x21]=1; state[0x22]=2; break;
    case 1: state[0x22]=3; state[0x21]=2; break;
    case 2: state[0x21]=3; state[0x22]=4; break;
    default: state[0x21]=4; state[0x22]=1; break;
    }
    while(count<D_L03_001B0B50_gp) {
        int start=func_002A77E0(count);
        int oldCount=count;
        int changed=0;
        int pass;
        for(pass=0;pass<count;pass++) {
            unsigned char *list=state+0x20;
            int index=(start+pass)%count;
            int next=(start+pass+1)%count;
            int edge=0;
            int candidate=D_L03_0024A7B0[list[index]][0];
            while(candidate!=-1) {
                int found=0;
                int j;
                for(j=0;j<count;j++)
                    if(candidate==list[j]) found=1;
                if(!found) {
                    for(j=0;j<6;j++) {
                        if(D_L03_0024A7B0[candidate][j]==list[next]) {
                            int k;
                            for(k=count-1;k>index;k--) list[k+1]=list[k];
                            count++;
                            list[index+1]=candidate;
                            changed=1;
                            break;
                        }
                    }
                }
                if(changed) break;
                if(++edge>=6) break;
                candidate=D_L03_0024A7B0[list[index]][edge];
            }
            if(changed) break;
        }
        if(oldCount==count) {
            D_L03_001B0B50_gp=count;
            break;
        }
    }
}
