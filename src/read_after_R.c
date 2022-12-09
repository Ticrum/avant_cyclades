
#include <avant_cyclades.h>

void read_after_R(t_cyclade *c)
{
    t_packet **temp_pack;

    if (c->compt_read_R == 0)
    {
        write(1,"alloc2!!",8);
        if ((c->packet_R[c->packet_R_len] = malloc(sizeof(t_packet))) == NULL)
            write(1,"err malloc",10);
        //read_bit(c->carte, c->packet_R[0], &c->compt_read_R, false);
    }
    write(1,"r",1);
    read_bit(c->carte, c->packet_R[c->packet_R_len], &c->compt_read_R, false);
    if (c->compt_read_R >= (int)sizeof(t_packet) * 8)
    {
        printf("/pktread: src = %d dest = %d pktnbr = %d mpkt = %d len = %d / parcour = %d/\n", c->packet_R[c->packet_R_len]->src, c->packet_R[c->packet_R_len]->dest, c->packet_R[c->packet_R_len]->packet_nbr, c->packet_R[c->packet_R_len]->max_packet, c->packet_R[c->packet_R_len]->len, c->compt_read_R);
        write(1,c->packet_R[c->packet_R_len]->data,c->packet_R[c->packet_R_len]->len);
        write(1, "\n", 1);
        if (c->packet_R_len == 0)
        {
            write(1,"alloc!!",6);
            temp_pack = c->packet_R;
            if ((c->packet_R = malloc(sizeof(t_packet *) * c->packet_R[0]->max_packet)) == NULL)
                write(1,"err malloc",10);//return (-1);
            c->packet_R[0] = temp_pack[0];
            free(temp_pack);
        }
        c->packet_R_len = c->packet_R_len + 1;
        c->compt_read_R = 0;
        if (c->packet_R_len == c->packet_R[0]->max_packet)
        {
            write(1,"finish",6);
            class_data(c, make_data(c->packet_R, c->packet_R_len, false));
            free_packet(c->packet_R, c->packet_R_len);
            c->packet_R_len = 0;
            c->packet_R = NULL;
            //printf("%p\n", c->datapass_L);
            //printf("\nauto out : src %d dest %d len %ld\n", c->datapass_L[0]->srcbuf, c->datapass_L[0]->destbuf, c->datapass_L[0]->buflen);
            c->compt_read_R = 1;
        }
    }
    //else
    //    c->compt_read_R = c->compt_read_R + 1;
}


