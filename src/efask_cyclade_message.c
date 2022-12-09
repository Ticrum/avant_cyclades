
#include <avant_cyclades.h>

int efask_cyclade_message(t_cyclade   *c,
                          uint32_t    host)
{
    int compt;
    int occur;

    compt = 0;
    occur = 0;
    while (compt < c->datain_len)
    {
        if (c->datain[compt]->srcbuf == host)
            occur = occur + 1;
        compt = compt + 1;
    }
    return (occur);
}

