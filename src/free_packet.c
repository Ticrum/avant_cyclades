
#include <avant_cyclades.h>

void free_packet(t_packet   **pack,
                 int        len)
{
    int compt;

    compt = 0;
    while (compt < len)
    {
        free(pack[compt]);
        compt = compt + 1;
    }
    free(pack);
}

