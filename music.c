#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include "music.h"

#define FREQUENCY 44100
#define CHANNELS 2
#define CHUNK_SIZE 2048
#define SLEEP_PER_LOOP_MS 10

bool play_sound(const char* filepath, void(handler)(CURL *curl), CURL *curl, unsigned min_duration_ms) {
    unsigned elapsed_time = 0;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "could not initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE) < 0) {
        SDL_Quit();
        fprintf(stderr, "SDL_Mixed could not initialize: %s\n", Mix_GetError());
        return false;
    }

    Mix_Music *music = Mix_LoadMUS(filepath);
    if (music == NULL) {
        fprintf(stderr, "Failed to load music on path %s: %s\n", filepath, Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return false;
    }

    if (Mix_PlayMusic(music, 1) == -1) {
        fprintf(stderr, "Failed to play music: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return false;
    }

    while(Mix_PlayingMusic()) {
        elapsed_time += SLEEP_PER_LOOP_MS;
        SDL_Delay(SLEEP_PER_LOOP_MS);
        if (elapsed_time >= min_duration_ms) {
            handler(curl);
            return true;
        }
    }

    handler(curl);
    return true;
}
