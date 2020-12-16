#include "pch.h"
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

void entry()
{
    std::cout << "[FuckRespawnAnchor] Loaded!\n";
}

using namespace std;
THook(bool, "?trySetSpawn@RespawnAnchorBlock@@CA_NAEAVPlayer@@AEBVBlockPos@@AEAVBlockSource@@AEAVLevel@@@Z",
    Player* pl, BlockPos* bpos) {
    if (pl->getDimensionId() != 1) {
        return false;
    }
    return original(pl, bpos);
}
