
#include <avant_cyclades.h>

int efask_cyclade_next_message(t_cyclade        *c,
                               uint32_t         host)
{
    int compt;

    compt = 0;
    while (compt < c->datain_len)
    {
        if (c->datain[compt]->srcbuf == host)
            return (c->datain[compt]->buflen);
        compt = compt + 1;
    }
    return (-1);
}

