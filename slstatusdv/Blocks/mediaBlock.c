// Function to get the currently playing media title and artist
const char* get_player_metadata() {
    static char buffer[128];  

    // Command to fetch metadata from the currently playing player
    FILE *fp = popen(
        "playerctl -a metadata --format '{{playerInstance}} {{status}} - {{title}}' 2>/dev/null | "
        "awk -F'Playing ' '/Playing/ {print substr($2, 1, 35); exit}'",
        "r"
    );

    if (fp) {
        if (fgets(buffer, sizeof(buffer), fp)) {
            // Remove the newline character from the output
            buffer[strcspn(buffer, "\n")] = '\0';
            pclose(fp);
            return buffer;
        }
        pclose(fp);
    }

    // Fallback if no player is playing or if the command fails
    return "No audio playing";
}
