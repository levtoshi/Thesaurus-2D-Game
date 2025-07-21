#include "../../header/Camera.h"
#include <iostream>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::CameraZoom(float delta)
{
	if (((delta > 0) ? ViewSize.y * pow(ViewZoom, -1) : ViewSize.y * ViewZoom) <= MapSize.y) {
		if (ViewFullMap) {
			ViewFullMap = false;
		}
		if (delta > 0) {
			CameraView.zoom(pow(ViewZoom, -1));
			ViewSize.x *= pow(ViewZoom, -1);
			ViewSize.y *= pow(ViewZoom, -1);
		}
		else {
			CameraView.zoom(ViewZoom);
			ViewSize.x *= ViewZoom;
			ViewSize.y *= ViewZoom;
		}
	}
	else {
		if (!ViewFullMap) {
			if (MapSize.x >= 900 && MapSize.y >= 700) {
				ViewSize = sf::Vector2f(MapSize.x / (ViewSize.x / ViewSize.y), MapSize.y);
			}
			CameraView.setSize(ViewSize.x, ViewSize.y);
			ViewFullMap = true;
		}
	}
}

void Camera::CameraReset()
{
	CameraView.setSize(ViewSizeConst);
	ViewSize = ViewSizeConst;
}

void Camera::CameraUpdater(sf::Vector2f HeroPos)
{
	ViewCenter = sf::Vector2f((HeroPos.x + HeroSize.x / 2), (HeroPos.y + HeroSize.y / 2));
	if (MapSize.x >= 900 && MapSize.y >= 700) {
		if ((HeroPos.x + HeroSize.x / 2) - (ViewSize.x / 2) < 0) {
			ViewCenter.x = (ViewSize.x / 2);
		}
		if ((HeroPos.y + HeroSize.y / 2) - (ViewSize.y / 2) < 0) {
			ViewCenter.y = (ViewSize.y / 2);
		}
		if ((HeroPos.x + HeroSize.x / 2) + (ViewSize.x / 2) > MapSize.x) {

			ViewCenter.x = (MapSize.x - ViewSize.x / 2);
		}
		if ((HeroPos.y + HeroSize.y / 2) + (ViewSize.y / 2) > MapSize.y) {
			ViewCenter.y = (MapSize.y - ViewSize.y / 2);
		}
	}
	CameraView.setCenter(ViewCenter);
}

void Camera::Save()
{
	IOFile.open(SavePath, std::fstream::out);
	if (IOFile.is_open()) {
		IOFile << ViewSizeConst.x << "\n" << ViewSizeConst.y << std::endl;
		IOFile << ViewSize.x << "\n" << ViewSize.y << std::endl;
		IOFile << ViewCenter.x << "\n" << ViewCenter.y << std::endl;
		IOFile << HeroSize.x << "\n" << HeroSize.y << std::endl;
		IOFile << MapSize.x << "\n" << MapSize.y << std::endl;
		IOFile << (int)ViewFullMap << std::endl;
	}
	IOFile.close();
}

void Camera::Pull()
{
	IOFile.open(SavePath, std::fstream::app | std::fstream::in);
	if (IOFile.is_open()) {
		std::string temp;
		int counter = 0;
		while (getline(IOFile, temp)) {
			switch (counter) {
				case 0: ViewSizeConst.x = std::stof(temp); break;
				case 1: ViewSizeConst.y = std::stof(temp); break;
				case 2: ViewSize.x = std::stof(temp); break;
				case 3: ViewSize.y = std::stof(temp); break;
				case 4: ViewCenter.x = std::stof(temp); break;
				case 5: ViewCenter.y = std::stof(temp); break;
				case 6: HeroSize.x = std::stof(temp); break;
				case 7: HeroSize.y = std::stof(temp); break;
				case 8: MapSize.x = std::stof(temp); break;
				case 9: MapSize.y = std::stof(temp); break;
				case 10: ViewFullMap = std::stof(temp); break;
			};
			counter++;
		}
	}
	IOFile.close();
}