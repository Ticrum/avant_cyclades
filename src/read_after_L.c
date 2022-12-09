
#include <avant_cyclades.h>

void read_after_L(t_cyclade *c)
{
    t_packet **temp_pack;

    if (c->compt_read_L == 0)
    {
        write(1,"alloc2!!",8);
        if ((c->packet_L[c->packet_L_len] = malloc(sizeof(t_packet))) == NULL)
            write(1,"err malloc",10);
        //read_bit(c->carte, c->packet_R[0], &c->compt_read_R, false);
    }
    write(1,"r",1);
    read_bit(c->carte, c->packet_L[c->packet_L_len], &c->compt_read_L, true);
    if (c->compt_read_L >= (int)sizeof(t_packet) * 8)
    {
        printf("/pktread: src = %d dest = %d pktnbr = %d mpkt = %d len = %d / parcour = %d/\n", c->packet_L[c->packet_L_len]->src, c->packet_L[c->packet_L_len]->dest, c->packet_L[c->packet_L_len]->packet_nbr, c->packet_L[c->packet_L_len]->max_packet, c->packet_L[c->packet_L_len]->len, c->compt_read_L);
        write(1,c->packet_L[c->packet_L_len]->data,c->packet_L[c->packet_L_len]->len);
        write(1, "\n", 1);
        if (c->packet_L_len == 0)
        {
            write(1,"alloc!!",6);
            temp_pack = c->packet_L;
            if ((c->packet_L = malloc(sizeof(t_packet *) * c->packet_L[0]->max_packet)) == NULL)
                write(1,"err malloc",10);//return (-1);
            c->packet_L[0] = temp_pack[0];
            free(temp_pack);
        }
        c->packet_L_len = c->packet_L_len + 1;
        c->compt_read_L = 0;
        if (c->packet_L_len == c->packet_L[0]->max_packet)
        {
            write(1,"finish",6);
            class_data(c, make_data(c->packet_L, c->packet_L_len, true));
            free_packet(c->packet_L, c->packet_L_len);
            c->packet_L_len = 0;
            c->packet_L = NULL;
            //printf("%p\n", c->datapass_L);
            //printf("\nauto out : src %d dest %d len %ld\n", c->datapass_L[0]->srcbuf, c->datapass_L[0]->destbuf, c->datapass_L[0]->buflen);
            c->compt_read_L = 1;
        }
    }
    //else
    //    c->compt_read_R = c->compt_read_R + 1;
}


