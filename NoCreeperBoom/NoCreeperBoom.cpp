#include <lbpch.h>
#include <stl\KVDB.h>
#include <mcapi/Player.h>
#include <stl\varint.h>
#include <api\types\helper.h>
#include <api\command\commands.h>
#include <mcapi/Core.h>
#include <mcapi/Actor.h>
#include <mcapi/Level.h>
#include <mcapi/BlockSource.h>
#include <mcapi/core.h>
#include <mcapi/BlockSource.h>
#include "pch.h"

void entry()
{
    std::cout << "[FuckCreeper] Loaded!\n";
}

using namespace std;
THook(void, "?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
    Level* _this, BlockSource* a2, Actor* a3, Vec3* a4, float a5, bool a6, bool a7, float a8, bool a9) {
    string actname = "";
    if (a3)
        actname = SymCall("?getActorName@CommandUtils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVActor@@@Z", string, Actor*)(a3);
    if (actname == "Wither") {
        return;
    }
    else {
        return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
    }
}