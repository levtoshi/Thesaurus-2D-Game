#pragma once
#include <SFML\Graphics.hpp>
#include <filesystem>
#include <fstream>
#include "Play.h"

namespace fs = std::filesystem;

class Backup
{
public:
	std::fstream IOFile;
	std::string FilePath = "Backup\\Play.save";

	Backup();
	~Backup();

	bool BackUpStatus = false;

	void SaveUp(Play*& PlayObject);
	void PullUp(Play*& PlayObject);;
	void DeleteBackUp();
	void BackupUpdater();
};