
#include <avant_cyclades.h>

static int not_in_talkees(uint32_t  src,
                          uint32_t  *talkees,
                          int       len)
{
    int compt;

    compt = 0;
    while (compt < len)
    {
        if (talkees[compt] == src)
            return (1);
        compt = compt + 1;
    }
    return (0);
}

int efask_cyclade_talkee(t_cyclade  *c,
                         uint32_t   *talkees,
                         size_t     talkeeslen)
{
    int compt;
    int compt2;

    compt = 0;
    compt2 = 0;
    while (compt < c->datain_len && compt2 < (int)talkeeslen)
    {
        if (not_in_talkees(c->datain[compt]->srcbuf, talkees, compt2))
        {
            talkees[compt2] = c->datain[compt]->srcbuf;
            compt2 = compt2 + 1;
        }
        compt = compt + 1;
    }
    return (compt2);
}

