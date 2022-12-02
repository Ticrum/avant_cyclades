
#include <avant_cyclades.h>

t_data **insert_data(t_data ***data,
                     int    len,
                     t_data *newdata)
{
    t_data **cpdata;
    int compt;

    if ((cpdata = malloc(sizeof(t_data *) * (len + 1))) == NULL)
        return (NULL);
    compt = 0;
    while (compt < len)
    {
        cpdata[compt] = (*data)[compt];
        compt = compt + 1;
    }
    cpdata[compt] = newdata;
    if (*data != NULL)
        free(*data);
    *data = cpdata;
    return (cpdata);
}

