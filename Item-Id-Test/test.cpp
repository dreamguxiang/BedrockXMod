#include <iostream>
#include <lbpch.h>
#include "pch.h"
#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <rapidjson/document.h>
#include<streambuf>
#include<api/command/commands.h>
#include<api/types/types.h>
#include<api/event/event_pch.h>
bool kg;
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
rapidjson::Document config;
void loadconfig()
{
	std::string config_file = "config\\Id-Test.json";
	ifstream fs("config\\Id-Test.json", std::ios::in);
	ostringstream tmp;
	if (!fs)
	{
		cout << "[" << gettime() <<u8" INFO] " << config_file << " not found, creating file(default value used)\n";
		std::ofstream of(config_file);
		if (of)
		{
			of << "{\"kg\":false}";
		}
		else
		{
			cout << "[" << gettime() << u8" INFO] " << "config file creation failed, plase create \"config\" folder\n";
		}
	}
	else
	{
		tmp << fs.rdbuf();
		fs.close();
		string data = tmp.str();
		config.Parse(data.c_str());
	}
	std::cout << "[" << gettime() << u8" Id-Test] Loaded!By:DreamGuXiang\n"<<endl;
}


using namespace std;
THook(bool, "?useItem@GameMode@@UEAA_NAEAVItemStack@@@Z",
	void* _this, ItemStack& item) {
	auto sp = *reinterpret_cast<Player**>(reinterpret_cast<unsigned long long>(_this) + 8);
	if (config["kg"].GetBool() == true) {
		auto mstr = item.getId();
		if (mstr != 0) {
			auto mstr1 = item.getId();
			auto mstr2 = item.toString();
			std::cout << u8"[Id-Test]使用触发者:" << sp->getNameTag() << u8"|物品名称:" << mstr2 << u8"|物品id:" << mstr1 << endl;
			return false;
		}
	}
	bool vaule = original(_this, item);
}

THook(bool, "?attack@GameMode@@UEAA_NAEAVActor@@@Z", void* _this, Actor* ac) {
	if (ac) {
		string name;
		auto sp = *reinterpret_cast<Player**>(reinterpret_cast<unsigned long long>(_this) + 8);
		name = SymCall("?EntityTypeToString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4ActorType@@W4ActorTypeNamespaceRules@@@Z", string, int, int)(ac->getEntityTypeId(), 1);
		std::cout << u8"[Id-Test]使用触发者:" << sp->getNameTag() << u8"|生物名称:" << name << u8"|生物id:" << ac->getEntityTypeId() << endl;
	}
	return original(_this, ac);
}

#pragma region CMDENUM
enum class iitcmd :int {
	open = 1,
	close = 2
};
#pragma endregion 


#pragma region iitcmd
bool reconfig(CommandOrigin const& ori, CommandOutput& outp, MyEnum<iitcmd> op) {
	switch (op)
	{
	case iitcmd::open: {
		fstream fs("config\\Id-Test.json",ios::out);
		ostringstream tmp;
		tmp << fs.rdbuf();
		fs.write("{\"kg\":true}", 11);
		fs.close();
		std::cout << "[Id-Test] open now" << endl;
		outp.addMessage("[Id-Test] iit open");
		loadconfig();
		break;
	}
	case iitcmd::close: {
		fstream fs("config\\Id-Test.json", ios::out);
		ostringstream tmp;
		tmp << fs.rdbuf();
		fs.write("{\"kg\":false}",12);
		fs.close();
		std::cout << "[Id-Test] close now" << endl;
		outp.addMessage("[Id-Test] iit close");
		loadconfig();
		break;
	}
	}
}

bool oncmd_iit(CommandOrigin const& ori, CommandOutput & outp, MyEnum<iitcmd> op) {
	return reconfig(ori, outp, op);
}
#pragma endregion

void entry() {
	loadconfig();
	addListener([](RegisterCommandEvent&) {
		CEnum<iitcmd> _1("iitcmd", { "open","close" });
		MakeCommand("iit", "iit menu", 0);
		CmdOverload(iit, oncmd_iit, "op");
		});
}
