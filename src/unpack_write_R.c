
#include <avant_cyclades.h>

int unpack_write_R(t_cyclade *c)
{
    if (c->write_R == false)
    {
        //write(1,"b",1);
        //if ()
        if (c->datapass_R_len == 0)
        {
            if (c->dataout_len != 0 && c->dataout[c->dataout_len - 1]->isleft == false)
            {
                write(1,"c",1);
                c->data_writing_R = c->dataout[c->dataout_len - 1];
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
            c->data_writing_R = c->datapass_R[c->datapass_R_len - 1];
            c->datapass_R_len = c->datapass_R_len - 1;
            if (c->datapass_R_len == 0)
            {
                free(c->datapass_L);
                c->datapass_R = NULL;
            }
        }
        write(1,"/c1/",4);
        c->write_R = true;
    }
    return (1);
}

