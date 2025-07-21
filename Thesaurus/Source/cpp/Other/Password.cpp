#include "../../header/Password.h"

Password::Password(sf::FloatRect* WallPos)
{
	srand(time(NULL));

	TeilsetPath = "Game\\Texture\\Map\\wall-numbers.png";

	TeilsetImage.loadFromFile(TeilsetPath);
	DoorImage.loadFromFile("Game\\Texture\\Map\\password.png");
	DoorWrongImage.loadFromFile("Game\\Texture\\Map\\password-wrong.png");

	TeilsetTexture.loadFromImage(TeilsetImage);
	DoorTexture.loadFromImage(DoorImage);
	DoorWrongTexture.loadFromImage(DoorWrongImage);

	TeilsetSprite.setTexture(TeilsetTexture);
	DoorSprite.setTexture(DoorTexture);

	DoorSprite.setPosition(sf::Vector2f(1216, 272));

	TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
	EnteredText.setFont(TextFont);
	EnteredText.setCharacterSize(16);
	EnteredText.setFillColor(sf::Color::White);
	EnteredText.setPosition(sf::Vector2f(1356, 386));

	for (int i = 0; i < 7; ++i) {
		PasswordValue += (char)(rand() % 9 + '1');
	}
	WallNumbersPos = new sf::FloatRect[7];
	for (int i = 0; i < 7; ++i) {
		WallNumbersPos[i] = WallPos[i];
	}
}

Password::~Password()
{
	if (WallNumbersPos != nullptr) {
		delete[] WallNumbersPos;
		WallNumbersPos = nullptr;
	}
}

void Password::PasswordWallDisplaier(sf::RenderWindow& MainWin)
{
	for (int i = 0; i < 7; ++i) {
		TeilsetSprite.setTextureRect(sf::IntRect(32 * (PasswordValue[i] - '1'), 0, 32, 32));
		TeilsetSprite.setPosition(WallNumbersPos[i].left, WallNumbersPos[i].top);
		MainWin.draw(TeilsetSprite);
	}
}

int Password::PasswordWindowController(sf::RenderWindow& MainWin, char enteredCh)
{
	if (enteredCh == 8) {
		std::string temp = EnteredPassword;
		if (temp.length()) {
			temp.pop_back();
			EnteredPassword = temp;
		}
	}
	else if (enteredCh == 13) {
		if (EnteredPassword == PasswordValue) {
			return 1;
		}
		else {
			DoorSprite.setTexture(DoorWrongTexture);
		}
	}
	else if (enteredCh == 122) {
		return 0;
	}
	else {
		EnteredPassword += enteredCh;
	}
	return 2;
}

void Password::PasswordWindowDisplaier(sf::RenderWindow& MainWin)
{
	EnteredText.setString(EnteredPassword);
	MainWin.draw(DoorSprite);
	MainWin.draw(EnteredText);
}

void Password::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		IOFile << PasswordValue << std::endl;
		IOFile << (std::string)EnteredPassword << std::endl;
	}
	IOFile.close();
}

void Password::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: PasswordValue = temp; break;
				case 1: EnteredPassword = temp; break;
			};
			counter++;
		}
		if (!EnteredPassword.isEmpty()) {
			std::string tempS = EnteredPassword;
			if (tempS[tempS.length() - 1] == 27) {
				tempS.pop_back();
				EnteredPassword = tempS;
			}
		}
	}
	IOFile.close();
}