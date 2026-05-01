/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048
#define CMDLEN 512

// Attempt to add delim logic like on dwmblocks
#define DEF_DELIM " "
// If you want a block to not have a delimiter you can make it an empty string
// For example, i like having cpu freq and perc showing in one block

#include "Blocks/brightnessBlock.c"
#include "Blocks/pamixerBlock.c"
#include "Blocks/mediaBlock.c"

/* Custom status functions, add or remove blocks as per use case */

static const struct arg args[] = {
    { datetime,             " [%s]",        "%e-%m / %H:%M",          .turn = 60, .delim=NULL },
	{ run_command,          "[%s]",               "systemps",         .turn = 10, . delim=DEF_DELIM},
//    { cpu_freq,             "[\uf4bc %shz]",      NULL,               .turn = 2,  .delim=DEF_DELIM },
    { cpu_perc,             "[󰻠 %s%%]",            NULL,               .turn = 2,  .delim=DEF_DELIM },
    { volume,               "[%s]",              NULL,               .turn = 0,  .signal = 1, .delim=DEF_DELIM },
//    { get_player_metadata,  "[ %s]",            NULL,               .turn = 1,  .delim=DEF_DELIM  },
};

