#pragma once
#include <iostream>
#include "Window.h"
#include "Menu.h"
#include "Settings.h"
#include "Plot.h"
#include "Play.h"
#include "FonMusic.h"
#include "BeforeGame.h"
#include "AfterGame.h"
#include "Backup.h"

#include <filesystem>

namespace fs = std::filesystem;

enum Win {
	MENU,
	SETTINGS,
	PLOT,
	GAME,
	BEFOREGAME,
	AFTERGAME
};

class Game
{
public:
	sf::Image ProgramIcon;
	
	Window* MainWindow = nullptr;
	Menu* MainMenu = nullptr;
	Plot* MainPlot = nullptr;
	Settings* MainSettings = nullptr;
	Play* MainPlay = nullptr;
	BeforeGame* MainBeforeGame = nullptr;
	AfterGame* MainAfterGame = nullptr;
	Backup* MainBackup = nullptr;

	sf::Cursor MainCursor;
	bool MainCursorState = false;
	bool AfterDead = false;

	sf::Event MainEvent;
	sf::Clock MainClock;

	Win CurrentWin = MENU;

	float MainVolume;
	bool MenuMusicPermission = true;
	bool GameMusicPermission = true;
	FonMusic* FonMusicArr = nullptr;

	Game();
	~Game();

	void run();
	void control();
	void update();
	void display();

	void CloseProgram();
};