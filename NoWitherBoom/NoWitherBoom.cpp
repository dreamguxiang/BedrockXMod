#include <lbpch.h>
#include "pch.h"
void entry()
{
    std::cout << "[FuckWither] Loaded!\n";
}
THook(bool, "?canDestroy@WitherBoss@@SA_NAEBVBlock@@@Z", void* blockpos)
{
    return false;
}

THook(bool, "?canDestroyBlock@WitherSkull@@UEBA_NAEBVBlock@@@Z", void* thi, void* blockpos)
{
    return false;
}


using namespace std;
THook(void, "?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
    Level* _this, BlockSource* a2, Actor* a3, Vec3* a4, float a5, bool a6, bool a7, float a8, bool a9) {
    string actname = "";
    if (a3)
        actname = SymCall("?getActorName@CommandUtils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVActor@@@Z", string, Actor*)(a3);
    if (actname == "Wither Skull") {
        return original(_this, a2, a3, a4, a5, a6, 0, a8, a9);
    }
    else if (actname == "Wither") {
        return original(_this, a2, a3, a4, a5, a6, 0, a8, a9);
    }
    return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
}

