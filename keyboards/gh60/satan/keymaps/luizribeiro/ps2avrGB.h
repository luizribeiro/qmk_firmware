// this converts from my ps2avrGB keymap to gh60 satan, so I can reuse the
// keymap from my larger board to my smaller one
#include "keyboards/winkeyless/bmini/bmini.h"
#undef LAYOUT
#define LAYOUT( \
    K05, K25, K35, K45, K55, K06, KA6, KA7, K07, KB5, KC5, KD5, KE5, KD1, KE1, KE2, \
    K04, K14, K24, K34, K44, K54, K16, KB6, KB7, K17, KA4, KB4, KC4, KE4,      KD0, \
    K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, KC3, KD3,      K67, \
    K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, KB2, KD2,           KE0, \
    K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, KB1,           K86, K77, \
    K00, K10, K20,           K56,                     K57, KB0, KC0, K66, K76, K96  \
) LAYOUT_60_ansi( \
    K04, K14, K24, K34, K44, K54, K16, KB6, KB7, K17, KA4, KB4, KC4, KE4, \
    K03, K13, K23, K33, K43, K53, K26, KC6, KC7, K27, KA3, KB3, KC3, KD3, \
    K02, K12, K22, K32, K42, K52, K36, KD6, KD7, K37, KA2, KB2, KD2,      \
    K01, K11, K21, K31, K41, K51, K46, KE6, KE7, K47, KA1, KB1,           \
    K00, K10, K20,           K56,                     K67, K57, KB0, KC0  \
)
