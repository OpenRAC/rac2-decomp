/* Nonmatching: US/US2/PAL 744/752 bytes, 0/8 each. Default profile.
 * Four checks. A real working multiplier/angle value and a scoped node-path
 * pointer recover the retail0xF0 frame and incoming-object spill (732/E0
 * before them). No-cse-follow-jumps ties744/F0. GCSE off still744 bytes but
 * shrinks the frame back to0xE0, and is rejected.
 * Remaining: basis-table address retention, path-pointer hoist, initial
 * matrix/state saved-register priorities and call argument scheduling.
 * Reopen with a measured narrow lifetime/control witness. No synthetic
 * accesses, pinned registers, volatile data or barriers were added.
 * 83958 reads16 bytes and writes48; 837D0 reads/writes16; cross-product
 * 82DD8 reads/writes16. One48-byte matrix and five16-byte vectors therefore
 * cover every actual access. W components are set at their real points in
 * the quaternion calculations, with no invented zeroing or padded buffers.
 */
#include "common.h"

extern float D_L03_0029BBF0[][4] NOT_SDA;
extern int D_L03_0024A7B0[][6] NOT_SDA;
extern float D_L03_001B9BB0[][4] NOT_SDA;
extern float D_L03_001B36B0[] NOT_SDA;
extern float D_L03_001B36C0[] NOT_SDA;
extern void func_00283098(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern float func_00283248(float,float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282F20(void *,void *,float);
extern void func_00283958(void *,void *);
extern void func_00283738(void *,void *,void *);
extern void func_002837D0(void *,void *,void *);

/* The quaternion producer writes three matrix rows,48 bytes. Every vector
 * occupies16 bytes. These are independent extents from the actual primitives,
 * not equal-size assumptions from the stack frame. */
void func_L03_003E3018(unsigned char *object)
{
    float matrix[12] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float forward[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float turn[4] __attribute__((aligned(16)));
    float candidate[4] __attribute__((aligned(16)));
    unsigned char *state=*(unsigned char **)(object+0x68);
    float amount=-1.0f;
    float best=amount;
    float score,side;
    {
        void *frame=object+0xC0;
        func_00283098(forward,D_L03_0029BBF0[*(short *)(state+0x50)],frame);
        func_00282D30(normal,D_L03_001B9BB0[0],amount);
        func_00282DD8(rotation,forward,normal);
        rotation[3]=func_00282DB0(forward,normal);
        amount=func_00283248(rotation[3],func_00282DF0(rotation))*0.5f;
        func_00282F20(rotation,rotation,func_00283198(amount));
        rotation[3]=func_00283180(amount);
        func_00283958(rotation,matrix);
        func_00283738(frame,matrix,frame);
        {
            unsigned char *path=state+0x30;
            if(path[*(short *)(state+0x5E)]==255) {
                int i;
                for(i=0;i<6;i++) {
                    int node=D_L03_0024A7B0[*(short *)(state+0x50)][i];
                    if(node!=-1) {
                        func_00283098(candidate,D_L03_0029BBF0[node],frame);
                        score=func_00282DB0(candidate,D_L03_001B9BB0[2]);
                        side=func_00282DB0(candidate,D_L03_001B9BB0[1]);
                        if(best<score) {
                            /* Retail retains this angle evaluation and discards
                             * its float result; keep the genuine call contract. */
                            func_00283248(score,side);
                            best=score;
                            path[*(short *)(state+0x5E)]=node;
                        }
                    }
                }
            }
        }
    }
    {
        void *frame=object+0xC0;
        func_00283098(candidate,D_L03_0029BBF0[state[0x30+*(short *)(state+0x5E)]],frame);
        score=func_00282DB0(candidate,D_L03_001B9BB0[2]);
        side=func_00282DB0(candidate,D_L03_001B9BB0[1]);
        amount=func_00283248(score,side)*0.5f;
        func_00282F20(turn,normal,func_00283198(amount));
        turn[3]=func_00283180(amount);
        func_002837D0(D_L03_001B36C0,D_L03_001B36B0,rotation);
        func_002837D0(D_L03_001B36C0,D_L03_001B36C0,turn);
        func_00283958(D_L03_001B36B0,frame);
    }
}
