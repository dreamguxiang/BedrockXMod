#include <iostream>
#include <lbpch.h>
#include "pch.h"
#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <mcapi/Actor.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <streambuf>
#include <api/command/commands.h>
#include <api/types/types.h>

using namespace std;

bool onCMDSl(CommandOrigin const& ori, CommandOutput& outp, string& name) {
		auto sp = MakeSP(ori);
		auto item = sp->getSelectedItem();
		auto itemname = item.getName();
		vector<string> v2;
		v2.push_back(name);
		item.setCustomLore(v2);
		SymCall("?updateInventoryTransactions@Player@@QEAAXXZ",void, Player*)(sp);
		outp.addMessage(u8"³É¹¦");
		return false;
}
bool onCMD_Sl(CommandOrigin const& ori, CommandOutput& outp, string& name) {
	return onCMDSl(ori, outp, name);
}

void entry() {
	addListener([](RegisterCommandEvent&) {
		MakeCommand("setlore", u8"ÉèÖÃlore", 1);
		CmdOverload(setlore, onCMD_Sl, "name");
		});
}

THook(bool, "?attack@GameMode@@UEAA_NAEAVActor@@@Z", 
	void* _this,  Actor* a2) {
	


	return original(_this,a2);
}
short ticks = 0;

THook(void, "?normalTick@Player@@UEAAXXZ", Player* player) {
	ticks++;
	if (ticks == 20) {
		WPlayer wp = WPlayer(*player);
		auto aa = player->getArmor();
		ticks = 0;
	}
	return original(player);
}