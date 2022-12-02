
#include <avant_cyclades.h>

void class_data(t_cyclade *c,
                t_data *data)
{
    if (data->destbuf == c->name)
    {
        write(1,"d",1);
        insert_data(&c->datain, c->datain_len, data);
        c->datain_len = c->datain_len + 1;
    }
    else if (data->isleft == true)
    {
        insert_data(&c->datapass_R, c->datapass_R_len, data);
        c->datapass_R_len = c->datapass_R_len + 1;
    }
    else
    {
        write(1,"nihruini",8);
        insert_data(&c->datapass_L, c->datapass_L_len, data);
        c->datapass_L_len = c->datapass_L_len + 1;
    }
}

