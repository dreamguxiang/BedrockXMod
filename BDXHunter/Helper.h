#include <api\Loader.h>
#include <mcapi/BlockSource.h>
#include <mcapi/Block.h>
#include <string>
//offset Based on 1.16.200, Edited in 2020-12-19

using namespace std;
namespace SymCommandUtils {
	string getActorName(Actor* mob) {
		return SymCall("?getActorName@CommandUtils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVActor@@@Z", string, Actor*)(mob);
	}
}
namespace SymBlock {
	inline string getFullName(void* Block) {
		string ret = "";
		SymCall("?getFullName@Block@@QEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", void, void*, string*)(Block, &ret);
		return ret;
	}
	inline BlockLegacy* getLegacyBlock(Block* block) {
		return SymCall("?getLegacyBlock@Block@@QEBAAEBVBlockLegacy@@XZ", BlockLegacy*, Block*)(block);
	}
}
namespace SymActorDamageSource {
	inline string lookupCauseName(unsigned int code) {
		string* cause_n = SymCall("?lookupCauseName@ActorDamageSource@@SAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4ActorDamageCause@@@Z", string*, unsigned int)(code);
		return *cause_n;
	}
}
namespace SymBlockSource {
	inline Block* getBlock(BlockSource* bs, BlockPos* bpos) {
		return SymCall("?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z", Block*, BlockSource*, BlockPos*)(bs, bpos);
	}
}
namespace offBlockLegacy {
	inline auto getBlockItemId(BlockLegacy* a1) {
		short v3 = *(short*)((__int64)a1 + 268);
		if (v3 < 0x100) {
			return v3;
		}
		return (short)(255 - v3);
	}
	string getFullName(BlockLegacy* Bl) {
		return  *(std::string*)((__int64)Bl + 128);
	}
}
namespace offBlock {
	string getFullName(Block* Bl) {
		return  *(string*)((void*)(SymBlock::getLegacyBlock(Bl) + 128));
	}
}
namespace offGameMode {
	inline Player* getPlayer(void* Gamemode) {
		return dAccess<Player*, 8>(Gamemode);
	}
}
namespace offCommandBlockUpdatePacket {
	inline BlockPos getBlockPos(void* CmdBlockUpdatePk) {
		return dAccess<BlockPos, 40>(CmdBlockUpdatePk);
	}
	inline string getCommand(void* CmdBlockUpdatePk) {
		return dAccess<string, 64>(CmdBlockUpdatePk);
	}
	inline bool isBlock(void* CmdBlockUpdatePk) {
		return (bool)dAccess<byte, 166>(CmdBlockUpdatePk);
	}
}
namespace offLevelContainerModel {
	inline BlockPos* getBlockPos(void* LCM) {
		return (BlockPos*)((char*)LCM + 216);
	}
	inline Player* getPlayer(void* LCM) {
		return ((Player**)LCM)[26];
	}
}
namespace offItemStack {
	inline int getCount(ItemStack* a1) {
		return *((char*)a1 + 34);
		//LevelContainerModel::_getContainer
	}
}