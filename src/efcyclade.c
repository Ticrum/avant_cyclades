
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
    //t_packet **temp_pack;

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
            read_after_R(c);
    }
}

static void read_L(t_cyclade *c)
{
    //t_packet **temp_pack;

    //printf("/c = %d %d %d/\n", c->compt_packet_L, c->packet_W_L.len, c->data_writing_L->buflen);
    //if (c->read_R == true)
    //    printf("/bool3 = %d/\n", c->write_L);
    if (c->read_L == 1)
    {
        if (c->packet_L == NULL)
        {
            if ((c->packet_L = malloc(sizeof(t_packet *))) == NULL)
                write(1,"err malloc",10);//return (-1);
            if ((c->packet_L[0] = malloc(sizeof(t_packet))) == NULL)
                write(1,"err malloc",10);//return (-1);
            read_bit(c->carte, c->packet_L[0], &c->compt_read_L, true);
        write(1,"fr",2);
        }
        else
            read_after_L(c);
    }
}

static int write_L(t_cyclade *c)
{
    float maxpacket;

    //if (c->write_L == true)
    //    printf("/bool = %d/\n", c->write_L);
    if (unpack_write_L(c) == 0)
        return (0);
    make_packet_write_L(c);
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

static int write_R(t_cyclade *c)
{
    float maxpacket;

    //if (c->write_L == true)
    //    printf("/bool = %d/\n", c->write_L);
    if (unpack_write_R(c) == 0)
        return (0);
    make_packet_write_R(c);
    maxpacket = (float)c->data_writing_R->buflen / 12.0;
    if ((int)maxpacket == 0)
        maxpacket = maxpacket + 1;
    else if (c->data_writing_R->buflen % 12)//(int)maxpacket != 0)
        maxpacket = maxpacket + 1;
    //c->carte->digital_outputs[5] = c->packet_W_L.data[c->compt_packet_L];
    write(1,"p",1);
    c->carte->digital_outputs[7] = write_bit(&c->packet_W_R, c->compt_packet_R);
    //if (c->compt_packet_L != 0)
    //    read_bit(c->carte, &c->test, &c->compt_packet_L, c->carte->digital_outputs[5]);
    c->compt_packet_R = c->compt_packet_R + 1;
     //printf("/c = %d %d %d/\n", c->compt_packet_L, c->packet_W_L.len,
     //c->data_writing_L->buflen);
    //printf("%d\n", sizeof(t_packet * 8);
    //printf("////////////////////// %d ////////////////////\n", c->nbr_packet_L);
    if (c->compt_packet_R == sizeof(t_packet) * 8)//c->packet_W_L.len + (sizeof(t_packet) - c->packet_W_L.len / 8))
    {
        write(1,"\nf",2);
        printf("/pktwrite: src = %d dest = %d pktnbr = %d mpkt = %d len = %d / parcour = %d/\n", c->packet_W_R.src, c->packet_W_R.dest, c->packet_W_R.packet_nbr, c->packet_W_R.max_packet, c->packet_W_R.len, c->compt_packet_R);
        write(1,c->packet_W_R.data,c->packet_W_R.len);
        write(1, "\n", 1);
        c->compt_packet_R = 0;
        c->nbr_packet_R = c->nbr_packet_R + 1;
    }
    //printf("////////////////////// %d ////////////////////\n", c->nbr_packet_L);
    if (c->nbr_packet_R == (int)maxpacket)
    {
        write(1,"s",1);
        printf("outlen = %d\n", c->dataout_len);
        //printf(" %d \n", write_bit())
        c->nbr_packet_R = 0;
        free(c->data_writing_R);
        c->write_R = false;
    }
    return (0);
}

int efcyclade(t_cyclade *c)
{
    maj_bool_com_in(c);
    read_R(c);
    read_L(c);
    write_L(c);
    write_R(c);
    maj_bool_com_out(c);
    //write(1,"\n",1);
    return (0);
}

