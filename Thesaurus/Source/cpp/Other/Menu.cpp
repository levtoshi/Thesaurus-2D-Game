#include "../../header/Menu.h"

void Menu::MenuButtonStart(MenuButton& Button)
{
    // Rect
    Button.ButtonRect.setFillColor(Button.ButtonFillColor);
    Button.ButtonRect.setOutlineColor(Button.ButtonOutColor);
    Button.ButtonRect.setOutlineThickness(Button.ButtonOutThick);
    Button.ButtonRect.setSize(Button.ButtonSize);
    Button.ButtonRect.setPosition(Button.ButtonPos);

    // Text
    MenuTextStart(Button.ButtonText);
}

void Menu::MenuTextStart(MenuText& MenuText)
{
    MenuText.Text.setFont(MenuText.TextFont);
    MenuText.Text.setCharacterSize(MenuText.TextSize);
    MenuText.Text.setFillColor(MenuText.TextColor);
    MenuText.Text.setStyle(sf::Text::Bold);
    MenuText.Text.setPosition(MenuText.TextPos);
    MenuText.Text.setString(MenuText.TextTitle);
}

Menu::Menu()
{
    // Background
    MenuImages = new sf::Image[4];
    MenuTextures = new sf::Texture[4];

    MenuImages[0].loadFromFile("Game\\Texture\\Menu\\castle.png");
    MenuImages[1].loadFromFile("Game\\Texture\\Menu\\IDLE.png");
    MenuImages[2].loadFromFile("Game\\Texture\\Menu\\settings.png");
    MenuImages[3].loadFromFile("Game\\Texture\\Menu\\settings-hover.png");

    for (int i = 0; i < 4; ++i) {
        MenuTextures[i].loadFromImage(MenuImages[i]);
    }

    MenuCastleSprite.setTexture(MenuTextures[0]);
    MenuIDLESprite.setTexture(MenuTextures[1]);

    MenuCastleSprite.setPosition(400, 0);
    MenuIDLESprite.setPosition(450, 294);

    // Settings button
    MenuSettingsButtonIcon.setTexture(MenuTextures[2]);
    MenuSettingsButtonIcon.setPosition(sf::Vector2f(32, 32));
    MenuSettingsButton.setFillColor(sf::Color::Black);
    MenuSettingsButton.setOutlineColor(sf::Color::Black);
    MenuSettingsButton.setOutlineThickness(2.f);
    MenuSettingsButton.setRadius(25.f);
    MenuSettingsButton.setPosition(sf::Vector2f(20, 20));

    // Buttons
    Buttons = new MenuButton[3];
    sf::String* ButtonTitles = new sf::String[3]{ L"Ãðàòè" , L"Ñþæåò", L"Âèõ³ä" };
    sf::Vector2f* ButtonsTextPos = new sf::Vector2f[3]{ sf::Vector2f(148, 228), sf::Vector2f(134, 355), sf::Vector2f(149, 482) };

    for (int i = 0; i < 3; ++i) {
        Buttons[i].ButtonPos = sf::Vector2f(75, 212 + 127 * i);
        Buttons[i].ButtonText.TextPos = ButtonsTextPos[i];
        Buttons[i].ButtonText.TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
        Buttons[i].ButtonText.TextTitle = ButtonTitles[i];
        MenuButtonStart(Buttons[i]);
    }

    delete[] ButtonTitles;
    delete[] ButtonsTextPos;
    ButtonTitles = nullptr;
    ButtonsTextPos = nullptr;

    // Main title
    MenuTitle.TextFont.loadFromFile("Game\\Texture\\Font\\Inter-Bold.ttf");
    MenuTitle.TextColor = sf::Color::Black;
    MenuTitle.TextTitle = "Thesaurus";
    MenuTitle.TextPos = sf::Vector2f(105, 116);
    MenuTextStart(MenuTitle);
}

Menu::~Menu()
{
    if (Buttons != nullptr) {
        delete[] Buttons;
        Buttons = nullptr;
    }
    if (MenuImages != nullptr) {
        delete[] MenuImages;
        MenuImages = nullptr;
    }
    if (MenuTextures != nullptr) {
        delete[] MenuTextures;
        MenuTextures = nullptr;
    }
}


void Menu::MenuDisplaier(sf::RenderWindow& MainWin)
{
    // Background
    MainWin.clear(sf::Color::White);
    MainWin.draw(MenuCastleSprite);
    MainWin.draw(MenuIDLESprite);

    // Buttons
    for (int i = 0; i < 3; ++i) {
        Buttons[i].ButtonFillColor = ((HoverButtonsStates[i]) ? sf::Color::White : sf::Color::Black);
        Buttons[i].ButtonRect.setFillColor(Buttons[i].ButtonFillColor);
        Buttons[i].ButtonText.TextColor = ((HoverButtonsStates[i]) ? sf::Color::Black : sf::Color::White);
        Buttons[i].ButtonText.Text.setFillColor(Buttons[i].ButtonText.TextColor);
        MainWin.draw(Buttons[i].ButtonRect);
        MainWin.draw(Buttons[i].ButtonText.Text);
    }

    // Title
    MainWin.draw(MenuTitle.Text);

    // Settings button
    MenuSettingsButton.setFillColor((HoverButtonsStates[3]) ? sf::Color::White : sf::Color::Black);
    MenuSettingsButtonIcon.setTexture((HoverButtonsStates[3]) ? MenuTextures[3] : MenuTextures[2]);
    MainWin.draw(MenuSettingsButton);
    MainWin.draw(MenuSettingsButtonIcon);
}

bool Menu::MenuControllerMouseMoved(sf::Vector2i mousePos)
{
    for (int i = 0; i < 3; ++i) {
        if (mousePos.x > Buttons[i].ButtonPos.x && mousePos.x < (Buttons[i].ButtonPos.x + Buttons[i].ButtonSize.x) &&
            mousePos.y > Buttons[i].ButtonPos.y && mousePos.y < (Buttons[i].ButtonPos.y + Buttons[i].ButtonSize.y)) {
            HoverButtonsStates[i] = true;
        }
        else {
            HoverButtonsStates[i] = false;
        }
    }
    if (mousePos.x > MenuSettingsButton.getPosition().x && mousePos.x < (MenuSettingsButton.getPosition().x + MenuSettingsButton.getRadius() * 2) &&
        mousePos.y > MenuSettingsButton.getPosition().y && mousePos.y < (MenuSettingsButton.getPosition().y + MenuSettingsButton.getRadius() * 2)) {
        HoverButtonsStates[3] = true;
    }
    else {
        HoverButtonsStates[3] = false;
    }
    return (HoverButtonsStates[0] || HoverButtonsStates[1] || HoverButtonsStates[2] || HoverButtonsStates[3]);
}

int Menu::MenuControllerMouseClicked(sf::Vector2i mousePos)
{
    for (int i = 0; i < 3; ++i) {
        if (mousePos.x > Buttons[i].ButtonPos.x && mousePos.x < (Buttons[i].ButtonPos.x + Buttons[i].ButtonSize.x) &&
            mousePos.y > Buttons[i].ButtonPos.y && mousePos.y < (Buttons[i].ButtonPos.y + Buttons[i].ButtonSize.y)) {
            return i;
        }
    }
    if (mousePos.x > MenuSettingsButton.getPosition().x && mousePos.x < (MenuSettingsButton.getPosition().x + MenuSettingsButton.getRadius() * 2) &&
        mousePos.y > MenuSettingsButton.getPosition().y && mousePos.y < (MenuSettingsButton.getPosition().y + MenuSettingsButton.getRadius() * 2)) {
        return 3;
    }
    return 4;
}