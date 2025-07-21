#pragma once
#include "SFML\Graphics.hpp"
#include <cmath>
#include <fstream>

namespace fs = std::filesystem;

class Camera
{
public:
	sf::View CameraView;
	sf::Vector2f ViewSizeConst;
	sf::Vector2f ViewSize;
	sf::Vector2f ViewCenter;

	sf::Vector2f HeroSize;
	sf::Vector2f MapSize;

	float ViewZoom = 0.8f;
	bool ViewFullMap = false;

	Camera();
	~Camera();

	void CameraZoom(float);
	void CameraUpdater(sf::Vector2f);
	void CameraReset();
	
	// Save
	std::string SavePath = "Backup\\Camera.save";
	std::fstream IOFile;
	void Save();
	void Pull();
};