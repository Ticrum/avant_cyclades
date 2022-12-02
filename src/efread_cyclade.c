
#include <avant_cyclades.h>

size_t efread_cyclade(t_cyclade   *c,
                      uint32_t    *srcbuf,
                      void        **buf,
                      size_t      *buflen)
{
    if (c->datain_len != 0)
    {
        write(1,"pass",4);
        *srcbuf = c->datain[c->datain_len - 1]->srcbuf;
        *buf = c->datain[c->datain_len - 1]->buf;
        *buflen = c->datain[c->datain_len - 1]->buflen;
        free(c->datain[c->datain_len - 1]);
        c->datain_len = c->datain_len - 1;
        if (c->datain_len == 0)
        {
            free(c->datain);
            c->datain = NULL;
        }
    }
    return (*buflen);
}

