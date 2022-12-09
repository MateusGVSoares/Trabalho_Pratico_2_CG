#include "MusicPlayer.h"

int MusicPlayer::loadMusic(const char *music_name, const char *filename)
{
    Mix_Music *music = NULL;

    // Tenta carregar a musica
    music = Mix_LoadMUS(filename);

    // Verifica se ocorreu erro na hora de carregar a musica
    if (music == NULL)
    {
        printf("Falhou em carregar a musica [%s] \n", filename);
        return -1;
    }

    // Insere a música no map de acordo com o nome dado
    this->loaded_sounds.insert({music_name, music});
    return 0;
}

void MusicPlayer::setVolume(float vol)
{
    // Calcula o volume baseado no volume maximo da SDL
    this->volume = (MIX_MAX_VOLUME * vol) / 100.0f;

    // Chama a funcao da SDL_MIXER pra setar o volume
    Mix_VolumeMusic(this->volume);
}

void MusicPlayer::playMusic(const char *name)
{
    Mix_Music *music = NULL;
    std::map<std::string, Mix_Music *>::iterator it;

    it = this->loaded_sounds.find(name);

    // Verifica se retornou que nao existe a key no map
    if (it == loaded_sounds.end())
    {
        printf("MIXER::Esse arquivo de audio nao foi carregado ou o nome nao existe");
        return;
    }

    // No iterator, tem um pair
    // first é a key / nome da musica
    // second é o valor / objeto de musica carregado

    // Pega a musica correspondente aquele nome
    music = it->second;

    // Toca a musica
    Mix_PlayMusic(music, 0);
}

bool MusicPlayer::isPlaying()
{
    // Usa funcao da SDL para verificar se esta tocando musica
    return Mix_PlayingMusic();
}

void MusicPlayer::resumeMusic(const char *name)
{
    // Verifica se tem alguma musica pausada no SDL
    if (Mix_PausedMusic())
    {
        // Se tiver, ele retoma essa musica
        Mix_ResumeMusic();
    }

    // Verifica se esta tocando musica
    if (!Mix_PlayingMusic())
    {
        // Poe pra tocar a musica do parametro
        this->playMusic(name);
    }
}

// Pausa a musica
void MusicPlayer::stopMusic()
{
    // Verifica se esta tocando musica
    if (Mix_PlayingMusic())
    {
        // Pausa a musica que esta tocando
        Mix_PauseMusic();
    }
    else
        printf("MIXER::Nao esta tocando nenhuma musica no momento");
}

MusicPlayer::MusicPlayer()
{
    // Começa o volume em 20%
    this->volume = MIX_MAX_VOLUME * 20 / 100;
}

MusicPlayer::~MusicPlayer()
{
    std::map<std::string, Mix_Music *>::iterator it;

    // Libera toda a memoria alocada pelo SDL_MIXER ao carregar as musicas
    for (it = this->loaded_sounds.begin(); it != this->loaded_sounds.end(); it++)
    {
        Mix_FreeMusic(it->second);
    }
}