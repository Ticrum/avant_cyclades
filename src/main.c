
#include <avant_cyclades.h>

static void carte_reset(t_bunny_vm110n *carte)
{
    int compt;

    compt = 0;
    while (compt < 8)
    {
        carte->digital_outputs[compt] = false;
        compt = compt + 1;
    }
}

static void cpy_inputs(t_bunny_vm110n *carte)
{
    int compt;

    compt = 0;
    while (compt < 5)
        {
            carte->digital_outputs[compt] = carte->digital_inputs[compt];
            compt = compt + 1;
        }
}

int main(void)
{
    t_bunny_vm110n *carte;

    carte = bunny_new_vm110n(0);
    if (carte != NULL)
        write(1,"yes",3);
    carte_reset(carte);
    while (1)
    {
        bunny_vm110n_read(carte);
        cpy_inputs(carte);
        bunny_vm110n_write(carte);
        carte_reset(carte);
    }
    bunny_delete_vm110n(carte);
    return (0);
}

