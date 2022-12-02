
#include <avant_cyclades.h>

static void maj_bool_com_in(t_cyclade *c)
{
    c->read_R = c->carte->digital_inputs[1];
    c->read_L = c->carte->digital_inputs[3];
}

static void maj_bool_com_out(t_cyclade *c)
{
    //if (c->carte->digital_outputs[4] == true)
    //    printf("/bool2 = %d/\n", c->write_L);

    c->carte->digital_outputs[6] = c->write_R;
    c->carte->digital_outputs[4] = c->write_L;
}

static void read_R(t_cyclade *c)
{
    t_packet **temp_pack;

    //printf("/c = %d %d %d/\n", c->compt_packet_L, c->packet_W_L.len, c->data_writing_L->buflen);
    //if (c->read_R == true)
    //    printf("/bool3 = %d/\n", c->write_L);
    if (c->read_R == 1)
    {
        if (c->packet_R == NULL)
        {
            if ((c->packet_R = malloc(sizeof(t_packet *))) == NULL)
                write(1,"err malloc",10);//return (-1);
            if ((c->packet_R[0] = malloc(sizeof(t_packet))) == NULL)
                write(1,"err malloc",10);//return (-1);
            read_bit(c->carte, c->packet_R[0], &c->compt_read_R, false);
        write(1,"fr",2);
        }
        else
        {
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
    }
}

static int write_L(t_cyclade *c)
{
    float maxpacket;

    //if (c->write_L == true)
    //    printf("/bool = %d/\n", c->write_L);
    if (c->write_L == false)
    {
        //write(1,"b",1);
        //if ()
        if (c->datapass_L_len == 0)
        {
            if (c->dataout_len != 0)
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
    if (c->compt_packet_L == 0)//&& c->nbr_packet_L == 0)
    {
        write(1,"/p1/",4);
        c->packet_W_L.src = 3;//c->data_writing_L->srcbuf;
        c->packet_W_L.dest = c->data_writing_L->destbuf;
        maxpacket = (float)c->data_writing_L->buflen / 12.0;
        if ((int)maxpacket == 0)
            maxpacket = maxpacket + 1;
        else if (c->data_writing_L->buflen % 12)//(int)maxpacket != 0)
            maxpacket = maxpacket + 1;
        c->packet_W_L.max_packet = maxpacket;
        c->packet_W_L.packet_nbr = c->nbr_packet_L;
        c->packet_W_L.maj_reg = false;
        if (c->nbr_packet_L < (int)maxpacket - 1)
            c->packet_W_L.len = 12;
        else
        {
            //write(1,"/norm/",6);
            printf("/mpkt = %d/", (int)maxpacket);
            if ((int)maxpacket == 0 || (int)maxpacket == 1)
            {
                c->packet_W_L.len = c->data_writing_L->buflen;
                write(1,"/norm/",6);
            }
            else
            {
                c->packet_W_L.len = c->data_writing_L->buflen % 12;//(int)maxpacket;
                if (c->packet_W_L.len == 0)
                    c->packet_W_L.len = 12;
            }
            printf("!!!%d!! %d / %d !\n", c->packet_W_L.len, c->data_writing_L->buflen, (int)maxpacket);
        }
        data_cpy(c->data_writing_L, &c->packet_W_L, c->nbr_packet_L);
    }
    maxpacket = (float)c->data_writing_L->buflen / 12.0;
    if ((int)maxpacket == 0)
        maxpacket = maxpacket + 1;
    else if (c->data_writing_L->buflen % 12)//(int)maxpacket != 0)
        maxpacket = maxpacket + 1;
    //c->carte->digital_outputs[5] = c->packet_W_L.data[c->compt_packet_L];
    write(1,"p",1);
    c->carte->digital_outputs[5] = write_bit(&c->packet_W_L, c->compt_packet_L);
    //if (c->compt_packet_L != 0)
    //    read_bit(c->carte, &c->test, &c->compt_packet_L, c->carte->digital_outputs[5]);
    c->compt_packet_L = c->compt_packet_L + 1;
     //printf("/c = %d %d %d/\n", c->compt_packet_L, c->packet_W_L.len,
     //c->data_writing_L->buflen);
    //printf("%d\n", sizeof(t_packet * 8);
    //printf("////////////////////// %d ////////////////////\n", c->nbr_packet_L);
    if (c->compt_packet_L == sizeof(t_packet) * 8)//c->packet_W_L.len + (sizeof(t_packet) - c->packet_W_L.len / 8))
    {
        write(1,"\nf",2);
        printf("/pktwrite: src = %d dest = %d pktnbr = %d mpkt = %d len = %d / parcour = %d/\n", c->packet_W_L.src, c->packet_W_L.dest, c->packet_W_L.packet_nbr, c->packet_W_L.max_packet, c->packet_W_L.len, c->compt_packet_L);
        write(1,c->packet_W_L.data,c->packet_W_L.len);
        write(1, "\n", 1);
        c->compt_packet_L = 0;
        c->nbr_packet_L = c->nbr_packet_L + 1;
    }
    //printf("////////////////////// %d ////////////////////\n", c->nbr_packet_L);
    if (c->nbr_packet_L == (int)maxpacket)
    {
        write(1,"s",1);
        printf("outlen = %d\n", c->dataout_len);
        //printf(" %d \n", write_bit())
        c->nbr_packet_L = 0;
        free(c->data_writing_L);
        c->write_L = false;
    }
    return (0);
}

int efcyclade(t_cyclade *c)
{
    maj_bool_com_in(c);
    read_R(c);
    write_L(c);
    maj_bool_com_out(c);
    //write(1,"\n",1);
    return (0);
}

