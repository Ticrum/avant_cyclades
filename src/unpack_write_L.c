
#include <avant_cyclades.h>

int unpack_write_L(t_cyclade *c)
{
    if (c->write_L == false)
    {
        //write(1,"b",1);
        //if ()
        if (c->datapass_L_len == 0)
        {
            if (c->dataout_len != 0 && c->dataout[c->dataout_len - 1]->isleft == true)
            {
                write(1,"c",1);
                c->data_writing_L = c->dataout[c->dataout_len - 1];
                c->dataout_len = c->dataout_len - 1;
                if (c->dataout_len == 0)
                {
                    free(c->dataout);
                    c->dataout = NULL;
                }
            }
            else
            {
                //write(1,"bien",4);
                return (0);
            }
        }
        else
        {
            write(1,"z",1);
            c->data_writing_L = c->datapass_L[c->datapass_L_len - 1];
            c->datapass_L_len = c->datapass_L_len - 1;
            if (c->datapass_L_len == 0)
            {
                free(c->datapass_L);
                c->datapass_L = NULL;
            }
        }
        write(1,"/c1/",4);
        c->write_L = true;
    }
    return (1);
}

