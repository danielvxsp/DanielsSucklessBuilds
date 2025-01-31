const char *
brightness(const char *unused) {
    static char temp[16];        // Buffer for the brightness value
    char buffer[32];             // Temporary buffer for formatted output
    FILE *fp;                    // Declare the FILE pointer

    fp = popen("brightnessctl -m acpi_video0 | awk -F, '{print substr($4, 0, length($4)-1)}'", "r");
    if (fp == NULL) {
        strcpy(temp, "N/A");
    } else {
        // Read the brightness value into temp
        fgets(temp, sizeof(temp), fp);
        pclose(fp);
        
        // Strip newline characters from temp

        // Format the output string in buffer
        snprintf(buffer, sizeof(buffer), "\uf522 %s", temp); // Only use temp here

        // Copy formatted output back to temp
        strncpy(temp, buffer, sizeof(temp) - 1);
        temp[strcspn(temp, "\n")] = '\0'; // Remove newline if present
        temp[sizeof(temp) - 1] = '\0'; // Ensure null-termination
    }
   
    return temp;  // Return the brightness value stored in temp
}

