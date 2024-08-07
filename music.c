#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>
#include <pthread.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include "music.h"

#define FREQUENCY 44100
#define CHANNELS 2
#define CHUNK_SIZE 2048

void* play(void *arg) {
    struct music_options *options = (struct music_options*)arg;
    const char* filepath = options->filepath;

    puts(filepath);
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "could not initialize SDL: %s\n", SDL_GetError());
        return NULL;
    }

    if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE) < 0) {
        SDL_Quit();
        fprintf(stderr, "SDL_Mixed could not initialize: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Music *music = Mix_LoadMUS(filepath);
    if (music == NULL) {
        fprintf(stderr, "Failed to load music on path %s: %s\n", filepath, Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return NULL;
    }

    if (Mix_PlayMusic(music, 1) == -1) {
        fprintf(stderr, "Failed to play music: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return NULL;
    }

    while(Mix_PlayingMusic()) {
        SDL_Delay(options->min_duration_ms);
        break;
    }

    return NULL;
}

void play_sound_async(pthread_t *thread, struct music_options* options) {
    if (pthread_create(thread, NULL, play, options) != 0) {
        perror("Error playing sound on another thread");
        return;
    }
}
