#include <iostream>
#include <lbpch.h>
#include "pch.h"
#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <windows.h>
using namespace std;
THook(bool, "?useItem@GameMode@@UEAA_NAEAVItemStack@@@Z",
	void* _this,  ItemStack& item) {
	auto sp = *reinterpret_cast<Player**>(reinterpret_cast<unsigned long long>(_this) + 8);
		auto mstr = item.getName();
		if (mstr == "Clock" ) {
			auto pl2 = LocateS<WLevel>()->getPlayer(sp->getNameTag());
			pl2.value().runcmd("c");
			return false;
		}
	bool vaule = original(_this, item);
}