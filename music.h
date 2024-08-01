#ifndef MUSIC_H
#define MUSIC_H
#include <stdbool.h>
#include <curl/curl.h>

bool play_sound(const char* filepath, void(handler)(CURL *curl), CURL *curl, unsigned min_duration_ms);

#endif
