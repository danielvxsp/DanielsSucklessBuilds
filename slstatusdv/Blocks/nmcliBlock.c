static const char *
connection(const char *unused) {
    static char temp[32];        
    char formatted[64];          

    FILE *fp = popen("nmcli device show wlp2s0 | awk -F':[ \t]+' '/CONNECTION/ {print $2}'", "r");
    if (fp && fgets(temp, sizeof(temp), fp)) {
        pclose(fp);
        temp[strcspn(temp, "\n")] = '\0'; 
        snprintf(formatted, sizeof(formatted), "%s", temp); 
        strncpy(temp, formatted, sizeof(temp) - 1); 
        temp[sizeof(temp) - 1] = '\0'; 
    } else {
        pclose(fp);
        strcpy(temp, "N/A"); 
    }

    return temp; 
}

