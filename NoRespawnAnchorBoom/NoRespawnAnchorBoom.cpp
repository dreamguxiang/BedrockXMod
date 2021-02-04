#include "pch.h"
#include <lbpch.h>

void entry()
{
    std::cout << "[FuckRespawnAnchor] Loaded!\n";
}

using namespace std;
THook(void, "?explode@RespawnAnchorBlock@@CAXAEAVPlayer@@AEBVBlockPos@@AEAVBlockSource@@AEAVLevel@@@Z",
    Player* a1,  BlockPos* a2,  BlockSource* a3,  Level* a4) {
    return;
}