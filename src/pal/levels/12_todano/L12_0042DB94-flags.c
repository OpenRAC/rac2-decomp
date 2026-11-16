#include "include_asm.h"

#include "common.h"
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern unsigned char *part_spawn_spinning_spark_pal(void *,float,float,float,int,void *,float,unsigned int,int);
struct SparkPayloadPrefix {
    unsigned char reserved00[4];
    unsigned int mode;
    unsigned char reserved08[2];
    unsigned char alpha;
    unsigned char lifetime;
};

/* Spawns a small spray of sparks below the object, going up or down. */
void part_l12_spawn_spark_spray_pal(unsigned char *object,int positive)
{
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    int rotation;
    unsigned char *first_spark,*white_spark;
    velocity[0]=0.0f;
    velocity[2]=positive?0.5f:-0.5f;
    velocity[1]=0.0f;
    velocity[3]=1.0f;
    rotation=math_random_int_below(16);
    if(math_random_int_below(2))
        rotation=-rotation;
    qcopy(position,object+0x10);
    position[2]-=0.25f;
    first_spark=part_spawn_spinning_spark_pal(position,0.1f,1.0f,0.9f,rotation,velocity,420000.0f,0xDF204080u,0);
    if(first_spark) {
        unsigned char *data;
        *(unsigned short *)(first_spark+0xA)=8;
        data=first_spark+0x20;
        first_spark[9]=FloatToInt(4.0f)+0x70;
        *(int *)(data+4)=2;
        data[0xA]=0xDF;
        data[0xB]=first_spark[0xA];
    }
    {
        unsigned char *second_spark=part_spawn_spinning_spark_pal(position,0.1f,1.0f,0.9f,rotation,velocity,420000.0f,0xDF204080u,0);
        if(second_spark) {
            unsigned char *data=second_spark+0x20;
            /* The retail second_spark allocation updates the first_spark header. */
            *(unsigned short *)(first_spark+0xA)=8;
            first_spark[9]=FloatToInt(4.0f)+0x70;
            *(int *)(data+4)=2;
            data[0xA]=0xDF;
            data[0xB]=first_spark[0xA];
        }
    }
    white_spark=part_spawn_spinning_spark_pal(position,0.05f,1.0f,0.97f,16,velocity,210000.0f,0xDFFFFFFFu,0);
    if(white_spark) {
        struct SparkPayloadPrefix *data=(struct SparkPayloadPrefix *)(white_spark+0x20);
        int brightness=FloatToInt(4.0f);
        *(unsigned short *)(white_spark+0xA)=4;
        white_spark[9]=brightness+0x70;
        white_spark[8]=math_random_int_below(255);
        data->mode=2;
        data->alpha=0xDF;
        data->lifetime=first_spark[0xA];
    }
}
