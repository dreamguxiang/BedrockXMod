#include <lbpch.h>
#include <iostream>
#include <bdxland.h>
#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <filesystem>
#include <api\myPacket.h>
#include <stl\varint.h>
#include <api\xuidreg\xuidreg.h>
#include <api\types\helper.h>
#include <api\command\commands.h>
#include <mcapi/Core.h>
#include <mcapi/Actor.h>
#include <mcapi/Level.h>
#include <mcapi/Certificate.h>
#include <mcapi/BlockSource.h>
#include <mcapi/core.h>
#include <mcapi/mass.h>
#include <mcapi/Block.h>
#include <mcapi/Item.h>
#include <stl\langPack.h>
#include <functional>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "shared.h"
#include "pch.h"

unsigned int ticks = 0;
using namespace std;

THook(void, "?normalTick@Player@@UEAAXXZ", Player* pl) {
	ticks++;
	auto wp = WPlayer(*(Player*)pl);
	if (ticks == 40) {
		IVec2 pos1(pl->getPos());
		getLandIDAt(pos1, wp.getDimID());
	}
	return original(pl);
}
