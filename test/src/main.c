
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
//    t_bunny_vm110n *carte;
    t_cyclade *c;
    bool state;
    bool state2;
    char tab[512];
    int lu;

    uint32_t src;
    size_t len;
    void *buf;

    srand(time(NULL));
    src = 0;
    len = 0;
    buf = NULL;
    c = efopen_cyclade();
    c->name = 3;
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
        //write(1,"b",1);
        bunny_vm110n_read(c->carte);
        if (c->carte->digital_inputs[4] != state)
        {
            //printf("%d\n", compt2);
            compt2 = compt2 + 1;
            state = !state;
        }
        if (tab[0] == 'w' && tab[1] == ' ')
            {
                printf("lengo = %d\n", lu - 2);
                efwrite_cyclade(c, 3, &tab[2], lu - 2);//"azertyeuhfziufhihfiuzefzieuibifeiubfizebf",
                                                       //41);
            }
            if (tab[0] == 'r')
            {
                //write(1,(char *)c->datain[0]->buf, c->datain[0]->buflen);
                //printf("\nout : src %d dest %d len %ld\n", c->datain[0]->srcbuf, c->datain[0]->destbuf, c->datain[0]->buflen);
                efread_cyclade(c, &src, &buf, &len);
                printf("\nout : src %d len %ld\n", src, len);
                write(1,(char *)buf, len);
            }
        if (compt2 % 2 == 0)
        {
            state2 = !state2;
            //state = carte->digital_inputs[4];
            compt = compt + 1;
            finish = clock();
            currc = currc + CLOCKS_PER_SEC;
            curr = curr + 0.010 / ((finish - start) / (currc / compt));//CLOCKS_PER_SEC);
            //printf("%f %d %f\n", curr / compt, c->carte->digital_inputs[4], (currc / compt));//CLOCKS_PER_SEC);
            start = finish;
            //c->carte->digital_outputs[0] = state2;

            efcyclade(c);
/*
            if (c->read_R == 1)
            {
                if (c->packet_R == NULL)
                {
                    if ((c->packet_R = malloc(sizeof(t_packet *))) == NULL)
                        return (-1);
                    if ((c->packet_R[0] = malloc(sizeof(t_packet))) == NULL)
                        return (-1);
                    read_R(c->packet_R[0], &c->compt_read_R);
                }
            }
*/
            //cpy_inputs(c->carte);
            bunny_vm110n_write(c->carte);
        }
        //carte_reset(carte);
    }
    carte_reset(c->carte);
    bunny_usleep(0.2e6);
    bunny_vm110n_write(c->carte);
    //efclose_cyclade(c);
    return (0);
}

