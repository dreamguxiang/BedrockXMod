#include "pch.h"

unsigned int ticks = 0;
std::string scoreboard, item1, item2, item3, item4;
bool debug = false;

void entry() {
	std::cout << "[ItemCheck] loading\n";
	std::ifstream fs;
	fs.open("config\\item.json");
	std::string json;
	char buf[1024];
	while (fs.getline(buf, 1024))
	{
		json.append(buf);
	}
	rapidjson::Document document;
	document.Parse(json.c_str());
	scoreboard = document["scoreboard"].GetString();
	debug = document["debug"].GetBool();
	item1 = document["item1"].GetString();
	item2 = document["item2"].GetString();
	item3 = document["item3"].GetString();
	item4 = document["item4"].GetString();
	std::cout << "[ItemCheck] loaded\n";
}

THook(void, "?normalTick@Player@@UEAAXXZ", Player* player) {
	ticks++;
	if (ticks == 40) {
		ItemStack *itemStack = SymCall("?getSelectedItem@Player@@QEBAAEBVItemStack@@XZ", ItemStack*, Player*)(player);
		std::string itemName = itemStack->getName();
		std::string playerName = player->getNameTag();
		//WPlayer wPlayer{*player};
		bool noItem = true;
		if (itemName == item1) {
			//wPlayer.sendText(u8"你拿着泥土");
			//player->addTag(u8"泥土");
			BDX::runcmdEx("scoreboard players set \"" + playerName + "\" " + scoreboard.c_str() + " 1");
			noItem = false;
		}
		if (itemName == item2) {
			//wPlayer.sendText(u8"你拿着泥土");
			//player->addTag(u8"泥土");
			BDX::runcmdEx("scoreboard players set \"" + playerName + "\" " + scoreboard.c_str() + " 2");
			noItem = false;
		}
		if (itemName == item3) {
			//wPlayer.sendText(u8"你拿着泥土");
			//player->addTag(u8"泥土");
			BDX::runcmdEx("scoreboard players set \"" + playerName + "\" " + scoreboard.c_str() + " 3");
			noItem = false;
		}
		if (itemName == item4) {
			//wPlayer.sendText(u8"你拿着钻石剑");
			//player->addTag(u8"钻石");
			BDX::runcmdEx("scoreboard players set \"" + playerName + "\" " + scoreboard.c_str() + " 4");
			noItem = false;
		}
		if (noItem) {
			//wPlayer.sendText(u8"你没有拿着指定物品");
			BDX::runcmdEx("scoreboard players set \"" + playerName + "\" " + scoreboard.c_str() + " 0");
		};
		if(debug) std::cout << u8"玩家: " << playerName << u8" 物品: " << itemName.c_str() <<  "\n";
		ticks = 0;
	}
	return original(player);
}