#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00282D30(void *dst, void *src, float scale);
typedef struct {
    char pad0[0x18];
    float height;                  
    char pad1C[0xAA - 0x1C];
    short type;                    
} GroundMoby;
typedef struct {
    char pad0[0x33C];
    GroundMoby *ground;            
    char pad340[8];
    short flag348;                 
    char pad34A[0x2294 - 0x34A];
    int state;                     
} HeroMove;
typedef struct {
    char pad0[0x30];
    TI128 axis;                    
    char pad40[0x40];
    TI128 v80;                     
    char pad90[0x14];
    float fA4;                     
} CamMove;
typedef struct {
    TI128 v00;                     
    TI128 v10;                     
    char pad20[0x10];
    TI128 v30;                     
    char pad40[0x20];
    TI128 v60;                     
    char pad70[0x20];
    TI128 v90;                     
    char padA0[0x58];
    GroundMoby *ground;            
    float groundHeight;            
} MoveView;
typedef struct {
    TI128 v00;                     
    short h10;                     
    char pad12[0x60 - 0x12];
    MoveView view;                 
    char pad160[0x1E0 - 0x160];
    float f1E0;                    
} MoveState;
typedef struct {
    char pad0[0x30];
    TI128 position;                
    char pad40[0x30];
    MoveState *state;              
} MoveObject;
extern HeroMove D_00189E20;
extern int D_L00_001A8FF0[] __attribute__((sda));
extern CamMove D_L00_001B8E20;
extern int D_L00_001B9084;
extern void func_00282CC0(void *dst, void *a, void *b);
extern float func_00282DB0(void *a, void *b);

/* Moves the object, its state's vectors and the view by the input step. While the hero
   stands on the same moby (hero +0x33C), a rise of that moby's height (+0x18) since the
   last frame raises the step's height. Then the step's component along the axis at
   D_L00_001B8E20 + 0x30 goes to the view's vector at +0x10, and in hero states 11 and 12
   the off-axis part is cancelled again with the vector at +0x80 scaled by +0xA4. */
void func_PAL_L00_00425B98(MoveObject *object, TI128 *input)
{
    TI128 delta, projected, correction, remainder;
    TI128 *step = &delta;
    CamMove *cam = &D_L00_001B8E20;
    MoveState *state = object->state;
    MoveView *view = &state->view;
    GroundMoby *ground;
    float height, along;

    delta = *input;
    ground = D_00189E20.ground;
    if (ground != 0) {
        if (D_L00_001A8FF0[0] == 0) {
            if (D_00189E20.flag348 == 0) {
                if (ground == view->ground) {
                    height = ground->height - view->groundHeight;
                    if (height > 0.0f && ((float *)step)[2] < height)
                        ((float *)step)[2] = height;
                    view->groundHeight = D_00189E20.ground->height;
                } else {
                    view->ground = ground;
                    view->groundHeight = D_00189E20.ground->height;
                }
            } else
                view->ground = 0;
        } else
            view->ground = 0;
    } else
        view->ground = 0;

    func_00282CC0(&object->position, step, &object->position);
    func_00282CC0(&view->v60, step, &view->v60);
    func_00282CC0(&view->v00, step, &view->v00);
    func_00282CC0(&view->v90, step, &view->v90);
    func_00282CC0(&view->v30, step, &view->v30);
    func_00282CC0(&state->v00, step, &state->v00);
    along = func_00282DB0(step, &cam->axis);
    func_00282D30(&projected, &cam->axis, along);
    func_00282CC0(&view->v10, &view->v10, &projected);
    if (D_00189E20.flag348 == 0 &&
        !(D_00189E20.ground != 0 && D_00189E20.ground->type == 0x22D &&
          D_L00_001B9084 < 26))
        object->state->f1E0 = ((float *)step)[3];
    if ((unsigned int)(D_00189E20.state - 11) < 2) {
        MoveState *next = object->state;

        next->h10 = 0;
        func_00282D30(&correction, &cam->v80, cam->fA4);
        along = func_00282DB0(&cam->axis, step);
        func_00282D30(&remainder, &cam->axis, along);
        func_00282CF0(&remainder, step, &remainder);
        func_00282CF0(&correction, &correction, &remainder);
        func_00282CC0(&object->position, &correction, &object->position);
        func_00282CC0(&view->v60, &correction, &view->v60);
        func_00282CC0(&view->v00, &correction, &view->v00);
        func_00282CC0(&view->v90, &correction, &view->v90);
        func_00282CC0(&next->v00, &correction, &next->v00);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_00425F08);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_004266C8);
