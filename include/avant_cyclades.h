
#ifndef     AVANT_CYCLADES
#define     AVANT_CYCLADES

#include <lapin.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

// include pour test
#include <stdio.h>

typedef struct s_packet
{
    uint32_t    src;
    uint32_t    dest;
    uint16_t    packet_nbr;
    uint16_t    max_packet;
    uint8_t     len;
    uint8_t     data[12];
    union
    {
        struct {
            bool        maj_reg:1;
            // Autres flags
        };
        uint8_t flags;
    };
}t_packet;

typedef struct s_data
{
    uint32_t    srcbuf;
    uint32_t    destbuf;
    void        *buf;
    size_t      buflen;
    bool        isleft;
}t_data;

typedef struct s_cyclade
{
    uint32_t    name;
    t_bunny_vm110n *carte;
    t_data      **datapass_R; // packet a transiter droite
    int         datapass_R_len;
    t_data      **datapass_L; // packet a transiter gauche
    int         datapass_L_len;
    t_data      **datain; // packet recu pour nous
    int         datain_len;
    t_data      **dataout; // packet qu'on envoi
    int         dataout_len;
    t_packet    **packet_R;
    int         packet_R_len;
    int         compt_read_R;
    bool        read_R;
    t_packet    **packet_L;
    int         packet_L_len;
    int         compt_read_L;
    bool        read_L;
    t_data      *data_writing_R;
    t_packet    packet_W_R;
    int         compt_packet_R;
    int         nbr_packet_R;
    bool        write_R;
    t_data      *data_writing_L;
    t_packet    packet_W_L;
    int         compt_packet_L;
    int         nbr_packet_L;
    bool        write_L;
    uint32_t    **reg; // registre des cartes
    int         reg_len;
}t_cyclade;

t_cyclade   *efopen_cyclade(void);

void        efclose_cyclade(t_cyclade   *c);

int         efcyclade(t_cyclade         *c);

void        read_bit(t_bunny_vm110n     *carte,
                     t_packet           *packet,
                     int                *compt,
                     bool               isleft);

t_data      *make_data(t_packet         **packet,
                       int              len,
                       bool             isleft);

t_data      **insert_data(t_data        ***data,
                          int           len,
                          t_data        *newdata);

void        class_data(t_cyclade        *c,
                       t_data           *data);

void        free_packet(t_packet        **pack,
                        int             len);

void        data_cpy(t_data             *data,
                     t_packet           *packet,
                     int                nbr_packet);

size_t      efwrite_cyclade(t_cyclade   *c,
                            uint32_t    target,
                            void        *data,
                            size_t      datalen);

bool        write_bit(t_packet          *packet,
                      int               compt);

size_t      efread_cyclade(t_cyclade    *c,
                           uint32_t     *srcbuf,
                           void         **buf,
                           size_t       *buflen);

#endif //   AVANT_CYCLADES
