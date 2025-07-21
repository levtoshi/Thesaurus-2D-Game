#include "../../header/Backup.h"

Backup::Backup()
{
}

Backup::~Backup()
{
}

void Backup::SaveUp(Play*& PlayObject)
{
	PlayObject->PlayHero->Save();
	PlayObject->PlayCamera->Save();
	PlayObject->ShowRelicObject->Save();
	PlayObject->PlayPassword->Save();
	PlayObject->HelperObject->Save();
	if (PlayObject->PlayFight) {
		PlayObject->PlayNPC->Save();
	}
	if (PlayObject->CurrentSection < 7) {
		PlayObject->MapKeysArr[PlayObject->CurrentSection]->Save();
	}
	PlayObject->PlayMaps[1]->Save();
	PlayObject->Save();
}

void Backup::PullUp(Play*& PlayObject)
{
	PlayObject->Pull();
	if (PlayObject->CurrentMap == START) {
		PlayObject->StaticCollision[3] = PlayObject->StaticCollision[0];
	}
	if (PlayObject->CurrentMap == GAME_MAP) {
		PlayObject->StaticCollision[3] = PlayObject->StaticCollision[1];
	}
	if (PlayObject->CurrentMap == CHESS) {
		PlayObject->StaticCollision[3] = PlayObject->StaticCollision[2];
	}

	PlayObject->PlayHero->Pull();

	PlayObject->PlayCamera->Pull();
	PlayObject->PlayCamera->CameraView.setSize(PlayObject->PlayCamera->ViewSize);
	PlayObject->PlayCamera->CameraView.setCenter(PlayObject->PlayCamera->ViewCenter);

	if (PlayObject->PlayFight) {
		PlayObject->PlayNPC = new NPC;
		PlayObject->PlayNPC->Pull();
		PlayObject->PlayNPC->NPCSprite.setPosition(PlayObject->PlayNPC->NPCCurrentPos.left, PlayObject->PlayNPC->NPCCurrentPos.top);
	}

	PlayObject->ShowRelicObject->Pull();
	PlayObject->PlayPassword->Pull();
	PlayObject->HelperObject->Pull();
	PlayObject->PlayMaps[1]->Pull();
	
	if (PlayObject->CurrentSection < 7) {
		PlayObject->MapKeysArr[PlayObject->CurrentSection]->Pull();
	}
}

void Backup::DeleteBackUp()
{
	fs::remove("Backup\\Camera.save");
	fs::remove("Backup\\Helper.save");
	fs::remove("Backup\\Hero.save");
	fs::remove("Backup\\Keys.save");
	fs::remove("Backup\\Map.save");
	fs::remove("Backup\\NPC.save");
	fs::remove("Backup\\Password.save");
	fs::remove("Backup\\Play.save");
	fs::remove("Backup\\RelicShower.save");
	fs::remove("Backup\\Camera.save");
}

void Backup::BackupUpdater()
{
	BackUpStatus = (fs::exists(FilePath)) ? true : false;
}