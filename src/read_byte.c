
#include <avant_cyclades.h>

static void bit_set(void *data,
                    int  emp,
                    bool bit)
{
    char *datac;

    datac = (char *)data;
    //printf(" read int %d , emp = %d, bit = %d\n", datac[emp / 8], emp % 8, bit);

    if (bit == true)
    {
        datac[emp / 8] = datac[emp / 8] | (1 << (7 - emp % 8));
    }
    else
    {
        datac[emp / 8] = datac[emp / 8] & ~(1 << (7 - emp % 8));
    }
    //printf("apres read int %d\n", datac[emp / 8]);
}

void read_bit(t_bunny_vm110n    *carte,
              t_packet          *packet,
              int               *compt,
              bool              isleft)
{
    //uint8_t *pack;

    //pack = (uint8_t *)packet;
    if (isleft == true)
        bit_set(packet, *compt - 1, carte->digital_inputs[2]);
    //    pack[*compt] = !carte->digital_inputs[2];
    else
        bit_set(packet, *compt - 1, carte->digital_inputs[0]);
    *compt = *compt + 1;
}

