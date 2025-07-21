#include "../../header/FonMusic.h"

FonMusic::FonMusic()
{
}

FonMusic::~FonMusic()
{
}


void FonMusic::setFonMusic(std::string filename)
{
	fonMusicFileName = filename;
	fonMusic.openFromFile(fonMusicFileName);
}

bool FonMusic::setFonMusicExplorer()
{
    OPENFILENAME explorer;
    ZeroMemory(&explorer, sizeof(explorer));
    explorer.lStructSize = sizeof(explorer);
    explorer.hwndOwner = NULL;
    wchar_t buffer[150];
    explorer.nMaxFile = sizeof(buffer) / sizeof(buffer[0]);
    explorer.lpstrFile = buffer;
    explorer.lpstrFile[0] = L'\0';

    if (GetOpenFileName(&explorer)) {
        std::wstring temp(explorer.lpstrFile);
        setFonMusic(std::string(temp.begin(), temp.end()));
        return true;
    }
    else { 
        return false;
    }
}

void FonMusic::reuploadMusic()
{
    fonMusicFileName = fonMusicFileNameDefault;
	fonMusic.openFromFile(fonMusicFileName);
}


void FonMusic::setVolume(float volumeLevel)
{
	fonMusic.setVolume(volumeLevel * 100);
}

void FonMusic::startMusic()
{
	fonMusic.play();
	fonMusic.setLoop(true);
}

void FonMusic::stopMusic()
{
	if (fonMusic.getStatus() == sf::Music::Playing)
		fonMusic.stop();
}