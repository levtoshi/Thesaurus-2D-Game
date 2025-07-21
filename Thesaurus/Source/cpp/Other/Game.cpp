#include "../../header/Game.h"
Game::Game()
{
	MainWindow = new Window;
	MainMenu = new Menu;
	MainPlot = new Plot;
	MainSettings = new Settings;
	MainPlay = new Play;
	MainBeforeGame = new BeforeGame;
	MainAfterGame = new AfterGame;
	MainBackup = new Backup;
	FonMusicArr = new FonMusic[2];

	FonMusicArr[0].fonMusicFileNameDefault = (fs::current_path() / "Game\\Audio\\Menu.wav").string();
	FonMusicArr[1].fonMusicFileNameDefault = (fs::current_path() / "Game\\Audio\\game-bg.wav").string();
	FonMusicArr[0].setFonMusic(FonMusicArr[0].fonMusicFileNameDefault);
	FonMusicArr[0].startMusic();
	FonMusicArr[1].setFonMusic(FonMusicArr[1].fonMusicFileNameDefault);

	// Program icon
	ProgramIcon.loadFromFile("Game\\Texture\\Map\\program-icon.png");
	MainWindow->WindowObject.setIcon(ProgramIcon.getSize().x, ProgramIcon.getSize().y, ProgramIcon.getPixelsPtr());
}

Game::~Game()
{
	if (AfterDead) {
		MainBackup->DeleteBackUp();
	}
	if (MainWindow != nullptr) {
		delete MainWindow;
		MainWindow = nullptr;
	}
	if (MainMenu != nullptr) {
		delete MainMenu;
		MainMenu = nullptr;
	}
	if (MainPlot != nullptr) {
		delete MainPlot;
		MainPlot = nullptr;
	}
	if (MainSettings != nullptr) {
		delete MainSettings;
		MainSettings = nullptr;
	}
	if (MainPlay != nullptr) {
		if (!AfterDead) {
			MainBackup->SaveUp(MainPlay);
		}
		delete MainPlay;
		MainPlay = nullptr;
	}
	if (MainBeforeGame != nullptr) {
		delete MainBeforeGame;
		MainBeforeGame = nullptr;
	}
	if (MainAfterGame != nullptr) {
		delete MainAfterGame;
		MainAfterGame = nullptr;
	}
	if (MainBackup != nullptr) {
		delete MainBackup;
		MainBackup = nullptr;
	}

	if (FonMusicArr != nullptr) {
		delete[] FonMusicArr;
		FonMusicArr = nullptr;
	}
}

void Game::CloseProgram()
{
	MainWindow->WindowObject.close();
}

void Game::run()
{
	while (MainWindow->WindowObject.isOpen()) {
		control();
		update();
		display();
	}
}

void Game::control()
{
	while (MainWindow->WindowObject.pollEvent(MainEvent)) {
		switch (MainEvent.type) {
			case sf::Event::Closed: {
				CloseProgram();
			} break;
			case sf::Event::MouseMoved: {
				if (CurrentWin == MENU) {
					MainCursorState = MainMenu->MenuControllerMouseMoved(sf::Mouse::getPosition(MainWindow->WindowObject));
				}
				else if (CurrentWin == PLOT) {
					MainCursorState = MainPlot->PlotControllerMouseMoved(sf::Mouse::getPosition(MainWindow->WindowObject));
				}
				else if (CurrentWin == SETTINGS) {
					MainCursorState = MainSettings->SettingsControllerMouseMoved(sf::Mouse::getPosition(MainWindow->WindowObject));
				}
				else if (CurrentWin == BEFOREGAME) {
					MainCursorState = MainBeforeGame->BeforeGameControllerMouseMoved(sf::Mouse::getPosition(MainWindow->WindowObject), MainBackup->BackUpStatus, AfterDead);
				}
				else if (CurrentWin == AFTERGAME) {
					MainCursorState = MainAfterGame->AfterGameMouseMoved(sf::Mouse::getPosition(MainWindow->WindowObject));
				}
				else if (CurrentWin == GAME) {
					MainCursorState = false;
				}
				MainCursor.loadFromSystem((MainCursorState) ? sf::Cursor::Type::Hand : sf::Cursor::Type::Arrow);
				MainWindow->WindowObject.setMouseCursor(MainCursor);
			} break;
			case sf::Event::MouseButtonPressed: {
				if (MainEvent.mouseButton.button == sf::Mouse::Left) {
					if (CurrentWin == MENU) {
						int MenuButtonClickResult = MainMenu->MenuControllerMouseClicked(sf::Mouse::getPosition(MainWindow->WindowObject));
						switch (MenuButtonClickResult) {
							case 0: {
								CurrentWin = BEFOREGAME;
								MainCursor.loadFromSystem(sf::Cursor::Type::Arrow);
								MainWindow->WindowObject.setMouseCursor(MainCursor);
							} break;
							case 1: CurrentWin = PLOT; break;
							case 2: CloseProgram(); break;
							case 3: {
								CurrentWin = SETTINGS;
								MainSettings->GOTO = 0;
							}; break;
						};
					}
					else if (CurrentWin == PLOT) {
						if (MainPlot->PlotControllerMouseClicked(sf::Mouse::getPosition(MainWindow->WindowObject))) {
							CurrentWin = MENU;
						}
					}
					else if (CurrentWin == SETTINGS) {
						if (MainSettings->SettingsControllerMouseClicked(sf::Mouse::getPosition(MainWindow->WindowObject), MenuMusicPermission,
							GameMusicPermission, FonMusicArr[0], FonMusicArr[1])) {
							if (!MainSettings->GOTO) {
								CurrentWin = MENU;
							}
							else {
								CurrentWin = AFTERGAME;
							}
						}
						if (MainSettings->SliderObject->SliderClick(sf::Mouse::getPosition(MainWindow->WindowObject), MainVolume)) {
							if (MenuMusicPermission) {
								FonMusicArr[0].setVolume(MainVolume);
							}
							if (GameMusicPermission) {
								FonMusicArr[1].setVolume(MainVolume);
							}
						}
					}
					else if (CurrentWin == BEFOREGAME) {
						switch (MainBeforeGame->BeforeGameControllerMouseClicked(sf::Mouse::getPosition(MainWindow->WindowObject), MainBackup->BackUpStatus, AfterDead)) {
							case 0: {
								CurrentWin = MENU;
							}; break;
							case 1: { // Past Game
								if (!MainPlay->DYNAMIC) {
									MainBackup->PullUp(MainPlay);
									MainClock.restart();
								}
								CurrentWin = GAME;
								MainWindow->WindowObject.setView(MainPlay->PlayCamera->CameraView);
								if (FonMusicArr[0].fonMusic.getStatus() == sf::Music::Playing) {
									FonMusicArr[0].stopMusic();
								}
								if (GameMusicPermission) {
									FonMusicArr[1].startMusic();
								}
								MainCursor.loadFromSystem(sf::Cursor::Type::Arrow);
								MainWindow->WindowObject.setMouseCursor(MainCursor);
							}; break;
							case 2: { // New Game
								if (MainPlay != nullptr) {
									delete MainPlay;
									MainPlay = new Play;
								}
								else {
									MainPlay = new Play;
									AfterDead = false;
								}
								CurrentWin = GAME;
								
								MainWindow->WindowObject.setView(MainPlay->PlayCamera->CameraView);
								if (FonMusicArr[0].fonMusic.getStatus() == sf::Music::Playing) {
									FonMusicArr[0].stopMusic();
								}
								if (GameMusicPermission) {
									FonMusicArr[1].startMusic();
								}
								MainCursor.loadFromSystem(sf::Cursor::Type::Arrow);
								MainWindow->WindowObject.setMouseCursor(MainCursor);
							}; break;
						};
					}
					else if (CurrentWin == AFTERGAME) {
						switch (MainAfterGame->AfterGameMouseClicked(sf::Mouse::getPosition(MainWindow->WindowObject))) {
							case 0: {
								CurrentWin = GAME;
								MainCursor.loadFromSystem(sf::Cursor::Type::Arrow);
								MainWindow->WindowObject.setMouseCursor(MainCursor);
								MainWindow->WindowObject.setView(MainPlay->PlayCamera->CameraView);
								if (FonMusicArr[0].fonMusic.getStatus() == sf::Music::Playing) {
									FonMusicArr[0].stopMusic();
								}
								if (GameMusicPermission) {
									FonMusicArr[1].startMusic();
								}
							}; break;
							case 1: {
								CurrentWin = SETTINGS;
								MainCursor.loadFromSystem(sf::Cursor::Type::Arrow);
								MainWindow->WindowObject.setMouseCursor(MainCursor);
								MainSettings->GOTO = 1;
							}; break;
							case 2: {
								CurrentWin = MENU;
								MainBackup->SaveUp(MainPlay);
								MainCursor.loadFromSystem(sf::Cursor::Type::Arrow);
								MainWindow->WindowObject.setMouseCursor(MainCursor);
							}; break;
						};
					}
					else if (CurrentWin == GAME) {
						MainPlay->PlayHero->HeroFight = true;
					}
				}
			} break;
			case sf::Event::MouseButtonReleased: {
				if (MainEvent.mouseButton.button == sf::Mouse::Left) {
					if (CurrentWin == GAME) {
						MainPlay->PlayHero->HeroFight = false;
					}
				}
			}; break;
			case sf::Event::MouseWheelScrolled: {
				if (MainEvent.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					if (CurrentWin == GAME) {
						if (!MainPlay->PasswordWinOpened) {
							MainPlay->PlayCamera->CameraZoom(MainEvent.mouseWheelScroll.delta);
						}
					}
				}
			}; break;
			case sf::Event::TextEntered: {
				if (CurrentWin == GAME) {
					if (MainPlay->PasswordWinOpened && MainEvent.text.unicode < 128) {
						switch (MainPlay->PlayPassword->PasswordWindowController(MainWindow->WindowObject, MainEvent.text.unicode)) {
							case 0: {
								MainPlay->PasswordWinOpened = false;
							}; break;
							case 1: {
								MainPlay->PlayMaps[1]->ChangeSectionToOpen(MainPlay->TempCollision[1].ObjectsArray[0]);
								MainPlay->DeleteArrElement(MainPlay->TempCollision[1].ObjectsArray, MainPlay->TempCollision[1].ArraySize, 0);
								MainPlay->PlayHero->HeroHeart = 5.f;
								if (MainPlay->PlaySounds[6].getStatus() != sf::Sound::Status::Playing) {
									MainPlay->PlaySounds[6].play();
								}
								MainPlay->CurrentSection++;
								MainPlay->PasswordWinOpened = false;
							}; break;
						};
					}
				}
				
			}; break;
		};
	}
	
	if (CurrentWin == GAME) {
		if (MainPlay->PlayController(MainWindow->WindowObject)) {
			if (MainPlay->HeroDeadBoolean) {
				CurrentWin = MENU;
				MainPlay->DYNAMIC = false;
				AfterDead = true;
				delete MainPlay;
				
				MainPlay = nullptr;
			}
			else {
				CurrentWin = AFTERGAME;	
			}
			MainWindow->WindowObject.setView(sf::View(sf::FloatRect(0, 0, MainWindow->WinSize.x, MainWindow->WinSize.y)));
			if (FonMusicArr[1].fonMusic.getStatus() == sf::Music::Playing) {
				FonMusicArr[1].stopMusic();
			}
			if (MenuMusicPermission) {
				FonMusicArr[0].startMusic();
			}
		}
	}
}

void Game::update()
{
	if (CurrentWin == GAME) {
		MainPlay->PlayUpdater(MainClock, MainVolume);
	}
	MainBackup->BackupUpdater();
}

void Game::display()
{
	if (CurrentWin == GAME) {
		MainPlay->PlayDisplaier(MainWindow->WindowObject);
	}
	else if (CurrentWin == MENU) {
		MainMenu->MenuDisplaier(MainWindow->WindowObject);
	}
	else if (CurrentWin == PLOT) {
		MainPlot->PlotDisplaier(MainWindow->WindowObject);
	}
	else if (CurrentWin == SETTINGS) {
		MainSettings->SettingsDisplaier(MainWindow->WindowObject);
	}
	else if (CurrentWin == BEFOREGAME) {
		MainBeforeGame->BeforeGameDisplaier(MainWindow->WindowObject, MainBackup->BackUpStatus, AfterDead);
	}
	else if (CurrentWin == AFTERGAME) {
		MainAfterGame->AfterGameDisplaier(MainWindow->WindowObject);
	}
	
	MainWindow->WindowObject.display();
}