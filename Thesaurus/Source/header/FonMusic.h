#pragma once
#include <SFML\Audio.hpp>
#include <Windows.h>
#include <iostream>

class FonMusic
{
public:
	sf::Music fonMusic;
	std::string fonMusicFileNameDefault;

	std::string fonMusicFileName;

	FonMusic();
	~FonMusic();

	void setFonMusic(std::string filename);
	bool setFonMusicExplorer();
	void reuploadMusic();

	void setVolume(float);
	void startMusic();
	void stopMusic();
};