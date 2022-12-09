
#include <avant_cyclades.h>

size_t efwrite_cyclade(t_cyclade    *c,
                       uint32_t     target,
                       void         *data,
                       size_t       datalen)
{
    t_data *newdata;

    if ((newdata = malloc(sizeof(t_data))) == NULL)
        return (-1);
    newdata->srcbuf = c->name;
    newdata->destbuf = target;
    newdata->buf = data;
    newdata->buflen = datalen;
    newdata->isleft = true;
    insert_data(&c->dataout, c->dataout_len, newdata);
    printf("%d\n", c->dataout[0]->srcbuf);
    c->dataout_len = c->dataout_len + 1;
    return(datalen);
}

