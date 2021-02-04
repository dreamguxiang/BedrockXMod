#include <lbpch.h>
#include <iostream>


#include "pch.h"
#include <bdxmoney.h>

#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <filesystem>
#include <api\myPacket.h>
#include <mcapi/Player.h>
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
#include <mcapi/BlockSource.h>
#include <mcapi/Block.h>
#include <mcapi/Item.h>
#include <stl\langPack.h>
#include <functional>
#include "Helper.h"
#include "random"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
int _access(const char
	* path, int mode);

using namespace std;
#pragma warning(disable:4996)

inline string gettime()
{
	time_t rawtime;
	tm* LocTime;
	char timestr[20];
	time(&rawtime);
	LocTime = localtime(&rawtime);
	strftime(timestr, 20, "%Y-%m-%d %H:%M:%S", LocTime);
	return string(timestr);
}

inline void fw(const string& filen, const string& instr)
{
	if (filen == "config\\BDXHunter.json")
		return;
	if ((_access(filen.c_str(), 0)) != -1)
	{
		ofstream outfile;
		outfile.open(filen, ios::app);
		if (!outfile)
		{
			cout << "[" << gettime() << u8" INFO] FileWriteFailed!!!" << endl;
		}
		outfile << instr << endl;
		outfile.close();
	}
	else
	{
		std::ofstream outfile(filen);
		if (!outfile)
		{
			cout << "[" << gettime() << u8" INFO] FileWriteFailed!!!" << endl;
		}
		unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
		outfile.write((char*)bom, sizeof(bom));
		outfile.close();
		fw(filen, instr);
	}
}

rapidjson::Document config;
void loadconfig() {
	ifstream in("config\\BDXHunter.json");
	ostringstream tmp;
	tmp << in.rdbuf();
	in.close();
	string data = tmp.str();
	config.Parse(data.c_str());
	int size = config.Size();
	if (size == 0)
		cout << "[" << gettime() << u8" Error] No Member Found!!!" << endl;
}

THook(void, "?die@Mob@@UEAAXAEBVActorDamageSource@@@Z", Mob* _this, ActorDamageSource* a2) {
	    string Mob_name = _this->getNameTag();
		string Mob_name2 = SymCall("?EntityTypeToString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4ActorType@@W4ActorTypeNamespaceRules@@@Z", string, int, int)(_this->getEntityTypeId(), 1);
		int srccode = dAccess<int>(a2, 8);
		if (srccode == 2 || srccode == 3) {
			Player* spl = _this->getLastHurtByPlayer();
			auto pl = WPlayer(*(ServerPlayer*)spl);
			for (auto& m : config.GetObject())
				if(m.name.GetString() == Mob_name2)
				{
					long money = Money::getMoney(pl.getXuid());
					int max = config[m.name.GetString()]["max"].GetInt();
					int min = config[m.name.GetString()]["min"].GetInt();
					auto num1 = rand() % (max - min + 1) + min;
					Money::createTrans(0, pl.getXuid(), num1);
					string zhname = config[m.name.GetString()]["name"].GetString();
					if (config[m.name.GetString()]["serverallplayers"].GetBool() == false)
					{
						pl.sendText(u8"§6成功击杀§d " + zhname + u8" §6获得了§e" + std::to_string(num1) + config["coinname"].GetString() + u8" §6当前余额:§b" + std::to_string(money + num1)  + config["coinname"].GetString(), TIP);
					}
					else
					{
						BDX::runcmdEx("title @a title §6玩家§b " + spl->getNameTag() +" §6成功击杀 §c" + zhname + " §6获得§e" + std::to_string(num1) + config["coinname"].GetString());
						pl.sendText(u8"§6成功击杀§d " + zhname + u8" §6获得了§e" + std::to_string(num1)  + config["coinname"].GetString() + u8" §6当前余额:§b" + std::to_string(money + num1) + config["coinname"].GetString(), TIP);
					}
				}
			}
		original(_this, a2);			
}


#pragma region CMDENUM
enum class huntercmd :int {
	reload = 1
};
#pragma endregion 


#pragma region cmd
bool reconfig(CommandOrigin const& ori, CommandOutput& outp, MyEnum<huntercmd> op) {
	switch (op)
	{
	case huntercmd::reload: {
		std::cout << "[Hunter] reload success" << endl;
		outp.addMessage("[Hunter] reload success");
		loadconfig();
		break;
	}
	}
}

bool oncmd_hunter(CommandOrigin const& ori, CommandOutput& outp, MyEnum<huntercmd> op) {
	return reconfig(ori, outp, op);
}
#pragma endregion

void entry() {
	loadconfig();
	addListener([](RegisterCommandEvent&) {
		CEnum<huntercmd> _1("Huntercmd", { "reload" });
		MakeCommand("hunter", "hunter menu", 1);
		CmdOverload(hunter, oncmd_hunter, "op");
		});
	cout << "[BDXHunter] BDXHunter Loaded, By DreamGuXiang, Build Date [" << __TIMESTAMP__ << u8"] @FineServer丨iFine " << endl;
}