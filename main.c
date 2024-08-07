#include "utils.h"
#include "music.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdbool.h>

#define MOAN_DURATION_MS 3000

int main(int argc, const char *argv[argc + 1]) {
    pthread_t thread;
    const char* link = parse_input(argc, argv);
    if (link == NULL) {
        return EXIT_FAILURE;
    }

    struct music_options sound_options = { .filepath = "./surprise.mp3", .min_duration_ms = MOAN_DURATION_MS };

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Curl init failed\n");
        return EXIT_FAILURE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, link);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, request_callback);

    play_sound_async(&thread, &sound_options);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download problem %s\n", curl_easy_strerror(result));
    }

    curl_easy_cleanup(curl);

    pthread_join(thread, NULL);
    return EXIT_SUCCESS;
}
