
#include <avant_cyclades.h>

void efclose_cyclade(t_cyclade *c)
{
    int compt;

    bunny_delete_vm110n(c->carte);
    compt = 0;
    while (compt < c->datapass_R_len)
    {
        free(c->datapass_R[compt]);
        compt = compt + 1;
    }
    if (c->datapass_R != NULL)
        free(c->datapass_R);
    compt = 0;
    while (compt < c->datapass_L_len)
    {
        free(c->datapass_L[compt]);
        compt = compt + 1;
    }
    if (c->datapass_L != NULL)
        free(c->datapass_L);
    compt = 0;
    while (compt < c->datain_len)
    {
        free(c->datain[compt]);
        compt = compt + 1;
    }
    if (c->datain != NULL)
        free(c->datain);
    compt = 0;
    while (compt < c->dataout_len)
    {
        free(c->dataout[compt]);
        compt = compt + 1;
    }
    if (c->dataout != NULL)
        free(c->dataout);
    compt = 0;
    while (compt < c->packet_R_len)
    {
        free(c->packet_R[compt]);
        compt = compt + 1;
    }
    if (c->packet_R != NULL)
        free(c->packet_R);
    compt = 0;
    while (compt < c->packet_L_len)
    {
        free(c->packet_L[compt]);
        compt = compt + 1;
    }
    if (c->packet_L != NULL)
        free(c->packet_L);
    compt = 0;
    if (c->data_writing_R != NULL)
        free(c->data_writing_R);
    if (c->data_writing_L != NULL)
        free(c->data_writing_L);
    while (compt < c->reg_len)
    {
        free(c->reg[compt]);
        compt = compt + 1;
    }
    if (c->reg != NULL)
        free(c->reg);
    free(c);
}

