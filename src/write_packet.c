
#include <avant_cyclades.h>

static bool bit_get(void *data,
                    int  emp)
{
    char *datac;

    datac = (char *)data;
    //printf(" int %d , emp = %d\n", datac[emp / 8], emp% 8);
    return ((datac[emp / 8] & (1 << (7 - emp % 8))) >> (7 - emp % 8));
}

bool write_bit(t_packet  *packet,
               int       compt)
{
    bool test;

    test = bit_get(packet, compt);
    //printf(" %d \n", test);
    return (test);
}

