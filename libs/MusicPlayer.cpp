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
    this->volume = (MIX_MAX_VOLUME * vol) / 100.0f;
    Mix_VolumeMusic(this->volume);
}

void MusicPlayer::playMusic(const char *name)
{
    Mix_Music *music = NULL;
    std::map<std::string, Mix_Music *>::iterator it;

    it = this->loaded_sounds.find(name);

    if (it == loaded_sounds.end())
    {
        printf("MIXER::Esse arquivo de audio nao foi carregado ou o nome nao existe");
        return;
    }

    // Pega a musica correspondente aquele nome
    music = it->second;

    if (!Mix_PlayingMusic())
    {
        Mix_PlayMusic(music, 0);
    }
    else
        printf("MIXER::Ja ta tocando musica, pare a musica antes de tocar outra \n");
}

bool MusicPlayer::isPlaying()
{
    return Mix_PlayingMusic();
}

void MusicPlayer::resumeMusic(const char *name)
{
    if (Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
    if (!Mix_PlayingMusic())
    {
        this->playMusic(name);
    }
}

// Pausa a musica
void MusicPlayer::stopMusic()
{
    if (Mix_PlayingMusic())
    {
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