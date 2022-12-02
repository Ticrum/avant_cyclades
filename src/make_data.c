
#include <avant_cyclades.h>

int datas_len(t_packet  **packet,
              int       len)
{
    int total;
    int compt;

    compt = 0;
    total = 0;
    while (compt < len)
    {
        total = total + packet[compt]->len;
        compt = compt + 1;
    }
    return (total);
}

t_data *make_data(t_packet  **packet,
                  int       len,
                  bool      isleft)
{
    int total_len;
    int compt;
    int compt2;
    int compt3;
    t_data *data;
    uint8_t *buf;

    total_len = datas_len(packet, len);
    if ((data = malloc(sizeof(t_data))) == NULL)
        return (NULL);
    if ((data->buf = malloc(sizeof(bool) * total_len)) == NULL)
        return (NULL);
    data->buflen = total_len;
    data->srcbuf = packet[0]->src;
    data->destbuf = packet[0]->dest;
    data->isleft = isleft;
    buf = (uint8_t *)data->buf;
    compt = 0;
    compt3 = 0;
    while (compt < len)
    {
        compt2 = 0;
        while (compt2 < packet[compt]->len)
        {
            buf[compt3 + compt2] = packet[compt]->data[compt2];
            compt2 = compt2 + 1;
        }
        compt3 = compt3 + compt2;;
        compt = compt + 1;
    }
    return (data);
}

