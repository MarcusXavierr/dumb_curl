#ifndef MUSIC_H
#define MUSIC_H
#include <pthread.h>
#include <stdbool.h>
#include <curl/curl.h>

struct music_options {
    const char *filepath;
    unsigned min_duration_ms;
};

/**
* @param arg is a struct of music_options
*/
void* play_sound(void *arg);
void play_sound_async(pthread_t *thread, struct music_options* options);

#endif
