
#include <avant_cyclades.h>

t_cyclade *efopen_cyclade(void)
{
    t_cyclade *card;

    if ((card = malloc(sizeof(t_cyclade))) == NULL)
        return (NULL);
    card->carte = bunny_new_vm110n(0);
    card->datapass_R = NULL;
    card->datapass_R_len = 0;
    card->datapass_L = NULL;
    card->datapass_L_len = 0;
    card->datain = NULL;
    card->datain_len = 0;
    card->dataout = NULL;
    card->dataout_len = 0;
    card->packet_R = NULL;
    card->packet_R_len = 0;
    card->compt_read_R = 1;
    card->read_R = false;
    card->packet_L = NULL;
    card->packet_L_len = 0;
    card->compt_read_L = 1;
    card->read_L = false;
    card->data_writing_R = NULL;
    card->compt_packet_R = 0;
    card->nbr_packet_R = 0;
    card->write_R = false;
    card->data_writing_L = NULL;
    card->compt_packet_L = 0;
    card->nbr_packet_L = 0;
    card->write_L = false;
    card->reg = NULL;
    card->reg_len = 0;
    card->name = rand();
    return (card);
}

