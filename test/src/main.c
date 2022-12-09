
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
    compt = 0;
    while (compt < 5)
    {
        ((bool *)carte->digital_inputs)[compt] = false;
        compt = compt + 1;
    }

}
/*
static void cpy_inputs(t_bunny_vm110n *carte)
{
    int compt;

    compt = 0;
    
    while (compt < 4)
        {
            carte->digital_outputs[compt + 4] = carte->digital_inputs[compt];
            compt = compt + 1;
        }
    
    carte->digital_inputs[3] = carte->digital_outputs[4];
    carte->digital_inputs[2] = carte->digital_outputs[5];
    carte->digital_inputs[1] = carte->digital_outputs[6];
    carte->digital_inputs[0] = carte->digital_outputs[7];
    
}
*/
int main(void)
{
    int compt;
    int compt2;
    double start;
    double finish;
    double curr;
    double currc;
    t_cyclade *c;
    bool state;
    bool state2;
    char tab[512];
    char tab2[512];
    int lu;

    uint32_t src;
    size_t len;
    void *buf;
    char id[40];

    srand(time(NULL));
    src = 0;
    len = 0;
    buf = NULL;
    c = efopen_cyclade();
    //c->name = 3;
    if (c->carte != NULL)
        write(1,"yes",3);
    else
        return (-1);
    state = false;
    state2 = false;
    carte_reset(c->carte);
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    start = clock();
    curr = 0;
    currc = 0;
    compt = 0;
    compt2 = 0;
    tab[0] = '\0';
    c->carte->digital_outputs[3] = true;
    bunny_vm110n_write(c->carte);
    //carte_reset(c->carte);
    while (tab[0] != 'e')
    {
        tab[0] = '\0';
        lu = read(0, tab, 512);
        tab[lu] = '\0';
        bunny_vm110n_read(c->carte);
        if (c->carte->digital_inputs[4] != state)
        {
            compt2 = compt2 + 1;
            state = !state;
        }
        if (tab[0] == 'w' && tab[1] == ' ')
            {
                printf("lengo = %d\n", lu - 2);
                sscanf(tab, "w %s %s", id, tab2);
                printf("!!! %s !!!", id);
                efwrite_cyclade(c, atoi(id), &tab2, strlen(tab2));//"azertyeuhfziufhihfiuzefzieuibifeiubfizebf",
                                                       //41);
            }
        if (tab[0] == 'r')
            {
                efread_cyclade(c, &src, &buf, &len);
                printf("\nout : src %d len %ld\n", src, len);
                write(1,(char *)buf, len);
            }
        if (tab[0] == 'n')
            printf("name = %d\n", c->name);
        if (compt2 % 2 == 0)
        {
            state2 = !state2;
            //state = carte->digital_inputs[4];
            compt = compt + 1;
            finish = clock();
            currc = currc + CLOCKS_PER_SEC;
            curr = curr + 0.010 / ((finish - start) / (currc / compt));//CLOCKS_PER_SEC);
            start = finish;
            efcyclade(c);
            bunny_vm110n_write(c->carte);
        }
    }
    carte_reset(c->carte);
    bunny_usleep(0.2e6);
    bunny_vm110n_write(c->carte);
    //efclose_cyclade(c);
    return (0);
}

