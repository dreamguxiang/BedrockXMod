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

THook(bool, "?useItemOn@GameMode@@UEAA_NAEAVItemStack@@AEBVBlockPos@@EAEBVVec3@@PEBVBlock@@@Z",
	void* _this, ItemStack* item, BlockPos* blkpos, unsigned __int8 a4, void* v5, Block* a6){
	auto sp = *reinterpret_cast<Player**>(reinterpret_cast<unsigned long long>(_this) + 8);
	auto mstr = item->getId();
	if (mstr == 0) {
		auto pl2 = LocateS<WLevel>()->getPlayer(sp->getNameTag());
	std:cout<<"aaaaaaaaaaaa"<<endl;
		return false;
	}
	bool vaule = original(_this, item, blkpos ,a4,v5,a6);
}