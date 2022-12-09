
#include <avant_cyclades.h>

void make_packet_write_R(t_cyclade *c)
{
    float maxpacket;

    if (c->compt_packet_R == 0)//&& c->nbr_packet_L == 0)
    {
        write(1,"/p1/",4);
        c->packet_W_R.src = 3;//c->data_writing_L->srcbuf;
        c->packet_W_R.dest = c->data_writing_R->destbuf;
        maxpacket = (float)c->data_writing_R->buflen / 12.0;
        if ((int)maxpacket == 0)
            maxpacket = maxpacket + 1;
        else if (c->data_writing_R->buflen % 12)//(int)maxpacket != 0)
            maxpacket = maxpacket + 1;
        c->packet_W_R.max_packet = maxpacket;
        c->packet_W_R.packet_nbr = c->nbr_packet_L;
        c->packet_W_R.maj_reg = false;
        if (c->nbr_packet_R < (int)maxpacket - 1)
            c->packet_W_R.len = 12;
        else
        {
            //write(1,"/norm/",6);
            printf("/mpkt = %d/", (int)maxpacket);
            if ((int)maxpacket == 0 || (int)maxpacket == 1)
            {
                c->packet_W_R.len = c->data_writing_R->buflen;
                write(1,"/norm/",6);
            }
            else
            {
                c->packet_W_R.len = c->data_writing_R->buflen % 12;//(int)maxpacket;
                if (c->packet_W_R.len == 0)
                    c->packet_W_R.len = 12;
            }
            printf("!!!%d!! %ld / %d !\n", c->packet_W_R.len, c->data_writing_R->buflen, (int)maxpacket);
        }
        data_cpy(c->data_writing_R, &c->packet_W_R, c->nbr_packet_R);
    }
}

