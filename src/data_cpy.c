
#include <avant_cyclades.h>

void data_cpy(t_data    *data,
              t_packet  *packet,
              int       nbr_packet)
{
    int compt;
    uint8_t *buf;

    buf = (uint8_t *)data->buf;
    compt = nbr_packet * 12;
    while (compt < packet->len + nbr_packet * 12)
    {
        packet->data[compt - nbr_packet * 12] = buf[compt];
        compt = compt + 1;
    }
}

