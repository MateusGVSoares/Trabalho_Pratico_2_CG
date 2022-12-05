#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>
// Player de musica, tentar utilizar da sdlmixer pra mexer com isso

// Map com musicas carregadas e o inteiro respectivo da musica
class MusicPlayer
{

private:
    std::map<std::string, Mix_Music *> loaded_sounds;
    int volume;

public:
    MusicPlayer();
    ~MusicPlayer();

    void setVolume(float vol);
    int loadMusic(const char *music_name, const char *filename);
    bool isPlaying();
    void playMusic(const char *name);
    void resumeMusic(const char * name);
    void stopMusic();
};