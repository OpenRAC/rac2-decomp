#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct __attribute__((packed)) { int values[2]; } Pair;

/* An incomplete array: retail builds this address with lui + addiu into a register of its own. */
extern Pair g_debris_choice_pair[];
extern int g_debris_piece_counter __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern void *CreateType6DObject(void *, void *, int, float);

/* Creates a small flying piece at a position, thrown along the given direction. It alternates between two kinds each time. */
void part_spawn_debris_piece(char *self, void *position, Quad *src)
{
    struct { Quad local; Pair choices; } temp;
    char *state = *(char **)(self + 0x68);
    float size;
    int *selected;

    temp.local = *src;
    vec_scale_to_length(&temp.local, &temp.local, 0.05f);
    temp.choices = g_debris_choice_pair[0];
    selected = temp.choices.values;
    size = math_random_float_range(0.05f, 0.1f);
    selected += g_debris_piece_counter % 2;
    CreateType6DObject(position, &temp.local, *selected,
                       size * *(float *)(state + 0x50) * 0.1f);
    g_debris_piece_counter += 1;
}
