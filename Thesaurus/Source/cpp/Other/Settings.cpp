#include "../../header/Settings.h"

void Settings::SettingsFieldStart(SettingsField& Field)
{
	// Rect
	Field.FieldRect.setFillColor(Field.FieldFillColor);
	Field.FieldRect.setOutlineColor(Field.FieldOutColor);
	Field.FieldRect.setOutlineThickness(Field.FieldOutThick);
	Field.FieldRect.setSize(Field.FieldSize);
	Field.FieldRect.setPosition(Field.FieldPos);

	// Text
	SettingsTextStart(Field.FieldText);
}

void Settings::SettingsTickerStart(SettingsTicker& Ticker) {
	Ticker.TickerShape.setFillColor(Ticker.TickerFillColor);
	Ticker.TickerShape.setOutlineColor(Ticker.TickerOutColor);
	Ticker.TickerShape.setOutlineThickness(Ticker.TickerOutThick);
	Ticker.TickerShape.setRadius(Ticker.TickerRadius);
	Ticker.TickerShape.setPosition(Ticker.TickerPos);
}

void Settings::SettingsTextStart(SettingsText& SettingsText)
{
	SettingsText.Text.setFont(SettingsText.TextFont);
	SettingsText.Text.setCharacterSize(SettingsText.TextSize);
	SettingsText.Text.setFillColor(SettingsText.TextColor);
	SettingsText.Text.setPosition(SettingsText.TextPos);
	SettingsText.Text.setString(SettingsText.TextTitle);
}

Settings::Settings()
{
	// Image & Texture
	SettingsImages = new sf::Image[5];
	SettingsTextures = new sf::Texture[5];
	SliderObject = new VolumeSlider;

	SettingsImages[0].loadFromFile("Game\\Texture\\Menu\\background-settings.png");
	SettingsImages[1].loadFromFile("Game\\Texture\\Menu\\pixel-settings.png");
	SettingsImages[2].loadFromFile("Game\\Texture\\Menu\\back.png");
	SettingsImages[3].loadFromFile("Game\\Texture\\Menu\\back-hover.png");
	SettingsImages[4].loadFromFile("Game\\Texture\\Menu\\tick.png");

	for (int i = 0; i < 5; ++i) {
		SettingsTextures[i].loadFromImage(SettingsImages[i]);
	}

	// Background
	SettingsBackgroundSprite.setTexture(SettingsTextures[0]);
	SettingsIconSprite.setTexture(SettingsTextures[1]);

	SettingsBackgroundSprite.setPosition(400, 0);
	SettingsIconSprite.setPosition(400, 100);

	// Fields
	FieldsArray = new SettingsField[5];
	sf::String* StringArr = new sf::String[5]{ L"Вкл/Вимк фонову музику в меню" , L"Вкл/Вимк фонову музику в грі" , L"Прив’язати файл для фонової музики в меню" ,
		L"Прив’язати файл для фонової музики в грі", L"Гучність" };
	sf::Vector2f* TextPos = new sf::Vector2f[5]{sf::Vector2f(45, 214),  sf::Vector2f(45, 302), sf::Vector2f(32, 390), sf::Vector2f(41, 478), sf::Vector2f(45, 566) };

	for (int i = 0; i < 5; ++i) {
		FieldsArray[i].FieldPos = sf::Vector2f(25, 198 + i * 88);
		FieldsArray[i].FieldText.TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
		FieldsArray[i].FieldText.TextTitle = StringArr[i];
		FieldsArray[i].FieldText.TextPos = TextPos[i];
		SettingsFieldStart(FieldsArray[i]);
	}
	delete[] StringArr;
	delete[] TextPos;
	StringArr = nullptr;
	TextPos = nullptr;

	// Tickers
	TickersArray = new SettingsTicker[2];
	TickersSpritesArray = new sf::Sprite[2];

	for (int i = 0; i < 2; ++i) {
		TickersArray[i].TickerPos = sf::Vector2f(338, 212 + i * 90);
		SettingsTickerStart(TickersArray[i]);
		TickersSpritesArray[i].setTexture(SettingsTextures[4]);
		TickersSpritesArray[i].setPosition(TickersArray[i].TickerPos);
	}

	// Main Title
	SettingsTitle.TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
	SettingsTitle.TextSize = 36;
	SettingsTitle.TextPos = sf::Vector2f(66, 116);
	SettingsTitle.TextTitle = L"Налаштування";
	SettingsTextStart(SettingsTitle);

	// Back button
	SettingsBackButtonIcon.setTexture(SettingsTextures[2]);
	SettingsBackButtonIcon.setPosition(sf::Vector2f(32, 32));
	SettingsBackButton.setFillColor(sf::Color::Black);
	SettingsBackButton.setOutlineColor(sf::Color::Black);
	SettingsBackButton.setOutlineThickness(2.f);
	SettingsBackButton.setRadius(25.f);
	SettingsBackButton.setPosition(sf::Vector2f(20, 20));
}

Settings::~Settings()
{
	if (FieldsArray != nullptr) {
		delete[] FieldsArray;
		FieldsArray = nullptr;
	}
	if (TickersArray != nullptr) {
		delete[] TickersArray;
		TickersArray = nullptr;
	}
	if (TickersSpritesArray != nullptr) {
		delete[] TickersSpritesArray;
		TickersSpritesArray = nullptr;
	}
	if (SettingsImages != nullptr) {
		delete[] SettingsImages;
		SettingsImages = nullptr;
	}
	if (SettingsTextures != nullptr) {
		delete[] SettingsTextures;
		SettingsTextures = nullptr;
	}
	if (SliderObject != nullptr) {
		delete SliderObject;
		SliderObject = nullptr;
	}
}

void Settings::SettingsDisplaier(sf::RenderWindow& MainWin)
{
	MainWin.clear(sf::Color::White);

	// Background
	MainWin.draw(SettingsBackgroundSprite);
	MainWin.draw(SettingsIconSprite);

	// Fields
	for (int i = 0; i < 5; ++i) {
		if (i != 2 && i != 3) {
			MainWin.draw(FieldsArray[i].FieldRect);
			MainWin.draw(FieldsArray[i].FieldText.Text);
		}
	}
	SliderObject->SliderDisplaier(MainWin);

	// Linkers
	for (int i = 2; i < 4; ++i) {
		FieldsArray[i].FieldRect.setFillColor((LinkersHoverStates[i - 2]) ? FieldsArray[i].LinkerHoverFillColor : FieldsArray[i].FieldFillColor);

		FieldsArray[i].FieldText.TextPos.x = ((LinkersActiveStates[i - 2]) ? 141 : (i == 2) ? 32 : 41);
		FieldsArray[i].FieldText.TextTitle = ((LinkersActiveStates[i - 2]) ? L"Перезапустити" : (i == 2) ? L"Прив’язати файл для фонової музики в меню" : L"Прив’язати файл для фонової музики в грі");

		FieldsArray[i].FieldText.Text.setPosition(FieldsArray[i].FieldText.TextPos);
		FieldsArray[i].FieldText.Text.setString(FieldsArray[i].FieldText.TextTitle);

		MainWin.draw(FieldsArray[i].FieldRect);
		MainWin.draw(FieldsArray[i].FieldText.Text);
	}

	// Tickers
	for (int i = 0; i < 2; ++i) {
		TickersArray[i].TickerShape.setFillColor((TickersArray[i].TickerHover) ? TickersArray[i].TickerHoverFillColor : TickersArray[i].TickerFillColor);
		MainWin.draw(TickersArray[i].TickerShape);
		if (TickersArray[i].TickerActive) {
			MainWin.draw(TickersSpritesArray[i]);
		}
	}

	// Main Title
	MainWin.draw(SettingsTitle.Text);

	// Back button
	SettingsBackButton.setFillColor((SettingsBackButtonHover) ? sf::Color::White : sf::Color::Black);
	SettingsBackButtonIcon.setTexture((SettingsBackButtonHover) ? SettingsTextures[3] : SettingsTextures[2]);
	MainWin.draw(SettingsBackButton);
	MainWin.draw(SettingsBackButtonIcon);
}

bool Settings::SettingsControllerMouseMoved(sf::Vector2i mousePos)
{
	// Tickers
	for (int i = 0; i < 2; ++i) {
		if (mousePos.x > TickersArray[i].TickerPos.x && mousePos.x < (TickersArray[i].TickerPos.x + TickersArray[i].TickerRadius * 2) &&
			mousePos.y > TickersArray[i].TickerPos.y && mousePos.y < (TickersArray[i].TickerPos.y + TickersArray[i].TickerRadius * 2) &&
			TickersArray[i].TickerActive == false) {
			TickersArray[i].TickerHover = true;
		}
		else {
			TickersArray[i].TickerHover = false;
		}
	}

	// Linkers
	for (int i = 2; i < 4; ++i) {
		if (mousePos.x > FieldsArray[i].FieldPos.x && mousePos.x < (FieldsArray[i].FieldPos.x + FieldsArray[i].FieldSize.x) &&
			mousePos.y > FieldsArray[i].FieldPos.y && mousePos.y < (FieldsArray[i].FieldPos.y + FieldsArray[i].FieldSize.y)) {
			LinkersHoverStates[i - 2] = true;
		}
		else {
			LinkersHoverStates[i - 2] = false;
		}
	}

	// Back button
	if (mousePos.x > SettingsBackButton.getPosition().x && mousePos.x < (SettingsBackButton.getPosition().x + SettingsBackButton.getRadius() * 2) &&
		mousePos.y > SettingsBackButton.getPosition().y && mousePos.y < (SettingsBackButton.getPosition().y + SettingsBackButton.getRadius() * 2)) {
		SettingsBackButtonHover = true;
	}
	else {
		SettingsBackButtonHover = false;
	}

	return (TickersArray[0].TickerHover || TickersArray[1].TickerHover || LinkersHoverStates[0] || LinkersHoverStates[1]
		|| SettingsBackButtonHover || SliderObject->SliderMouseMoved(mousePos));
}

bool Settings::SettingsControllerMouseClicked(sf::Vector2i mousePos, bool& MenuPermission, bool& GamePermission, FonMusic& MenuMusic, FonMusic& GameMusic)
{
	// Back button
	if (mousePos.x > SettingsBackButton.getPosition().x && mousePos.x < (SettingsBackButton.getPosition().x + SettingsBackButton.getRadius() * 2) &&
		mousePos.y > SettingsBackButton.getPosition().y && mousePos.y < (SettingsBackButton.getPosition().y + SettingsBackButton.getRadius() * 2)) {
		return true;
	}
	else {
		// Tickers
		for (int i = 0; i < 2; ++i) {
			if (mousePos.x > TickersArray[i].TickerPos.x && mousePos.x < (TickersArray[i].TickerPos.x + TickersArray[i].TickerRadius * 2) &&
				mousePos.y > TickersArray[i].TickerPos.y && mousePos.y < (TickersArray[i].TickerPos.y + TickersArray[i].TickerRadius * 2)) {
				if (TickersArray[i].TickerActive == false) {
					TickersArray[i].TickerActive = true;
					if (i == 0) {
						MenuPermission = true;
						MenuMusic.startMusic();
					}
					else {
						GamePermission = true;
					}
				}
				else {
					TickersArray[i].TickerActive = false;
					if (i == 0) {
						MenuPermission = false;
						MenuMusic.stopMusic();
					}
					else {
						GamePermission = false;
					}
				}
			}
		}

		// Linkers
		for (int i = 2; i < 4; ++i) {
			if (mousePos.x > FieldsArray[i].FieldPos.x && mousePos.x < (FieldsArray[i].FieldPos.x + FieldsArray[i].FieldSize.x) &&
				mousePos.y > FieldsArray[i].FieldPos.y && mousePos.y < (FieldsArray[i].FieldPos.y + FieldsArray[i].FieldSize.y)) {
				if (!LinkersActiveStates[i - 2]) {
					if (i == 2 && MenuMusic.setFonMusicExplorer()) {
						LinkersActiveStates[0] = true;
						if (MenuPermission) {
							MenuMusic.stopMusic();
							MenuMusic.startMusic();
						}
					}
					else if (i == 3 && GameMusic.setFonMusicExplorer()) {
						LinkersActiveStates[1] = true;
					}
				}
				else {
					LinkersActiveStates[i - 2] = false;
					if (i == 2) {
						MenuMusic.reuploadMusic();
						if (MenuPermission) {
							MenuMusic.stopMusic();
							MenuMusic.startMusic();
						}
					}
					else {
						GameMusic.reuploadMusic();
					}
				}
			}
		}
		return false;
	}
}