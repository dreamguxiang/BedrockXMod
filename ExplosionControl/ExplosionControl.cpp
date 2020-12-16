#include <io.h>
#include <fstream>
#include "pch.h"
#include <rapidjson/document.h>
#include <lbpch.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sstream>
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
void entry() {
	loadconfig();
	std::cout << "[" << gettime() << u8" ExplosionControl] Loaded!\n";
}

using namespace std;
THook(void, "?explode@Level@@QEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
	Level* _this, BlockSource* a2, Actor* a3, Vec3* a4, float a5, bool a6, bool a7, float a8, bool a9) {
	//  level        bs					Act		 Pos		Level 		fire	 exp	max 		unk
	string actname = "";
	if (a3)
		actname = SymCall("?getActorName@CommandUtils@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVActor@@@Z", string, Actor*)(a3);
	for (size_t a = 0; a < config.Size(); a++)
		if (config[a].GetString() == actname) {
			a5 = config[config[a].GetString()]["explosionlevel"].GetFloat();
			a6 = config[config[a].GetString()]["onfire"].GetBool();
			a7 = config[config[a].GetString()]["destroy"].GetBool();
			a8 = config[config[a].GetString()]["MaximumExplosionResistance"].GetFloat();
			a9 = config[config[a].GetString()]["unknown"].GetBool();
			std::cout << actname << endl;
			return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
		}
	return original(_this, a2, a3, a4, a5, a6, a7, a8, a9);
}