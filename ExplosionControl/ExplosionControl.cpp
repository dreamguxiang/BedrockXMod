#include <lbpch.h>
#include <iostream>
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
#include <api/gui/gui.h>
#include "pch.h"
#include <api\command\commands.h>
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
	if (filen == "config\\ExplosionControl.json")
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
	ifstream in("config\\ExplosionControl.json");
	ostringstream tmp;
	tmp << in.rdbuf();
	in.close();
	string data = tmp.str();
	config.Parse(data.c_str());
	int size = config.Size();
	if (size == 0)
		cout << "[" << gettime() << u8" Error] No Member Found!!!" << endl;
}

using namespace std;
THook(void, "?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	Level* _this, BlockSource* a2, Actor* a3, Vec3* a4, float a5, bool a6, bool a7, float a8, bool a9) {
	//  level        bs					Act		 Pos		Level 		fire	 exp	max 		unk
	string actname = "";
	if (a3)
		actname = SymCall("?getActorName@CommandUtils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVActor@@@Z", string, Actor*)(a3);
	    for (auto& m : config.GetObject())
		  if (m.name.GetString() == actname) {
			a5 = config[m.name.GetString()]["explosionlevel"].GetFloat();
			a6 = config[m.name.GetString()]["onfire"].GetBool();
			a7 = config[m.name.GetString()]["destroy"].GetBool();
			a8 = config[m.name.GetString()]["MaximumExplosionResistance"].GetFloat();
			a9 = config[m.name.GetString()]["unknown"].GetBool();
			return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
		}
	return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
}


#pragma region CMDENUM
enum class expccmd :int {
	reload = 1
};
#pragma endregion 


#pragma region cmd
bool reconfig(CommandOrigin const& ori, CommandOutput& outp, MyEnum<expccmd> op) {
	switch (op)
	{
	case expccmd::reload: {
		std::cout << "[ExplosionControl] reload success" << endl;
		outp.addMessage("[ExplosionControl] reload success");
		loadconfig();
		break;
	}
	}
}

bool oncmd_expc(CommandOrigin const& ori, CommandOutput& outp, MyEnum<expccmd> op) {
	return reconfig(ori, outp, op);
}
#pragma endregion

void entry() {
	loadconfig();
	addListener([](RegisterCommandEvent&) {
		CEnum<expccmd> _1("expccmd", { "reload" });
		MakeCommand("expc", "ExplosionControl menu", 1);
		CmdOverload(expc, oncmd_expc, "op");
		});
	cout << "[ExplosionControl] ExplosionControl Loaded, By DreamGuXiang, Build Date [" << __TIMESTAMP__ << u8"] @FineServerحiFine " << endl;
}