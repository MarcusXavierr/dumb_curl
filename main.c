#include "utils.h"
#include "music.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdbool.h>

void perform_call(CURL *curl) {
    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download problem %s\n", curl_easy_strerror(result));
    }
}

int main(int argc, const char *argv[argc + 1]) {
    const char* link = parse_input(argc, argv);
    if (link == NULL) {
        return EXIT_FAILURE;
    }

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Curl init failed\n");
        return EXIT_FAILURE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, link);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, request_callback);

    bool success = play_sound("./surprise.mp3", perform_call, curl, 3000);
    curl_easy_cleanup(curl);

    if (!success) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
