/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048
#define CMDLEN 512

/* Custom status functions, add or remove "Blocks according to your needs" */
#include "Blocks/brightnessBlock.c"
#include "Blocks/mediaBlock.c"
#include "Blocks/nmcliBlock.c"
#include "Blocks/pamixerBlock.c"

static const struct arg args[] = {
    { datetime,             " \uef37 %s",          "%b %e %a / %H:%M", .turn = 60 },
    { ram_used,             " | \uefc5 %s",        NULL,          .turn = 2 },
//    { battery_remaining,    " | %s",               "BAT1",        .turn = 3 },
//    { battery_state,        "%s",                  "BAT1",        .turn = 3 },
//    { battery_perc,         "%s%%",                "BAT1",        .turn = 3 },
    { cpu_freq,             " | \uf4bc %shz",      NULL,          .turn = 2 },
    { cpu_perc,             " %s%%",               NULL,          .turn = 2 },
    { connection,           " | ?¿ %s",            NULL,          .turn = 1 },
//    { volume,               " | %s",               NULL,          .turn = 0, .signal = 1},
//    { brightness,           " | %s",               "acpi_video0", .turn = 0, .signal = 2},
    { get_player_metadata,  " |  %s",             NULL,          .turn = 1 },
    { run_command,          " | %s ",              "curl -s 'wttr.in/Aravaca?format=1'", .turn = 30 },
};

