/* fetch volume */
const char *
volume(const char *unused) {
    static char vol[16];  // Increased size to accommodate longer strings
    FILE *fp;

    // Check if muted
    fp = popen("pamixer --get-mute", "r");
    if (fp == NULL) {
        strcpy(vol, "N/A");
    } else {
        char mute_status[8];  // Buffer to hold mute status
        fgets(mute_status, sizeof(mute_status), fp);
        pclose(fp);

        // Check if the output is "true\n" or "false\n"
        if (strcmp(mute_status, "true\n") == 0) {
            strcpy(vol, "\ueee8 ");
            return vol;
        }
    }

    // Get volume percentage if not muted
    fp = popen("pamixer --get-volume", "r");
    if (fp == NULL) {
        strcpy(vol, "N/A");
    } else {
        int current_volume;
        if (fscanf(fp, "%d", &current_volume) == 1) {
            snprintf(vol, sizeof(vol), "󰕾 %d", current_volume); // Format output
        } else {
            strcpy(vol, "N/A");
        }
        pclose(fp);
    }

    return vol;  // Return the constructed string
}

const char *
volume_icon(const char *unused)
{
    FILE *fp;
    char status[8];
    int current_volume = 0;
    int w_val;
    int is_muted = 0;
    const char *color = "#ffffff"; 

    fp = popen("pamixer --get-mute", "r");
    if (fp != NULL) {
        if (fgets(status, sizeof(status), fp) != NULL) {
            if (strncmp(status, "true", 4) == 0) {
                is_muted = 1;
            }
        }
        pclose(fp);
    }

    fp = popen("pamixer --get-volume", "r");
    if (fp != NULL) {
        if (fscanf(fp, "%d", &current_volume) != 1) {
            current_volume = 0;
        }
        pclose(fp);
    }

    if (current_volume > 100) current_volume = 100;
    if (current_volume < 0) current_volume = 0;

    // Map 0-100% to a max bar width of 16 pixels
    w_val = (current_volume * 16) / 100;

    if (is_muted) {
        color = "#ee3311"; 
        w_val = 0;         /* Empty the bar entirely */
    } else if (current_volume == 0) {
        color = "#555555"; 
    }

/*
 * Draw composition:
 * ^c%s^        -> Set main color
 * ^r0,8,3,4^   -> Speaker base
 * ^r3,6,3,8^   -> Speaker cone
 * ^c#555555^   -> Change to dark gray for background bar
 * ^r8,9,16,2^  -> Background volume bar 
 * ^c%s^        -> Switch back to main color for foreground fill
 * ^r8,9,%d,2^  -> Dynamic volume bar (width varies with volume)
 * ^d^^f26^     -> Reset colors and forward cursor by 26 pixels
*/

    return bprintf("^c%s^^r0,8,3,5^^r3,6,3,9^^c#555555^^r8,9,16,2^^c%s^^r8,9,%d,4^^d^^f26^",
                   color, color, w_val);
}
