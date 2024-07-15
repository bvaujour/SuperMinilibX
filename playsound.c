#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <pthread.h>

int	playsound(char *path)
{
	// Initialiser SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Initialiser SDL_mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        fprintf(stderr, "Erreur d'initialisation de SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    // Charger le fichier audio
    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (sound == NULL) {
        fprintf(stderr, "Erreur de chargement du fichier audio: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Jouer le son
    if (Mix_PlayChannel(-1, sound, 0) == -1) {
        fprintf(stderr, "Erreur lors de la lecture du son: %s\n", Mix_GetError());
        Mix_FreeChunk(sound);
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // Attendre que le son soit fini
    SDL_Delay(3000);  // Attendre 3 secondes

    // Nettoyer
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
	// free (sound);
	return 0;
}

int main()
{
	playsound("SWSH_Whoosh 4 (ID 1796)_LS.wav");
}

