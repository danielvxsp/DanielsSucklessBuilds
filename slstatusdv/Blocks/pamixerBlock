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
            snprintf(vol, sizeof(vol), "\uf028 %d", current_volume); // Format output
        } else {
            strcpy(vol, "N/A");
        }
        pclose(fp);
    }

    return vol;  // Return the constructed string
}
