#include <iostream>
#include <string.h>
#include <lbpch.h>
#include <stl\KVDB.h>
#include <api/Loader.h>
#include <string>
#include <JsonLoader.h>
#include <chrono>
#include <fstream>
#include <mcapi/Player.h>
#include <stl\varint.h>
#include <api\xuidreg\xuidreg.h>
#include <api\types\helper.h>
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
#include <mcapi/VanillaBlocks.h>
#include <random>
#include <windows.h>
using namespace std;
#pragma warning(disable:4996)
//煤炭
int coal_ore;
//铁
int iron_ore;
//金
int gold_ore;
//红石
int redstone_ore;
//青金石
int lapis_ore;
//下界石英
int quartz_ore;
//绿宝石
int emraid_ore;
//钻石
int diamond_ore;
//圆石
int cobblestone;

pair<int, int>  coal_ore_v;
pair<int, int>  iron_ore_v;
pair<int, int>  gold_ore_v;
pair<int, int>  redstone_ore_v;
pair<int, int>  lapis_ore_v;
pair<int, int>  quartz_ore_v;
pair<int, int>  emraid_ore_v;
pair<int, int>  diamond_ore_v;
pair<int, int>  cobblestone_v;

int rand_num;


inline string gettimenum() {
	time_t rawtime;
	tm* LocTime;
	char timestr[20];
	time(&rawtime);
	LocTime = localtime(&rawtime);

	strftime(timestr, 20, "%Y%m%d%H%M%S%U%w", LocTime);
	return string(timestr);
}
vector<pair<string, pair<int, int>>> Ores;
int total = 0;
void loadconf() {
	try {
		ifstream file("config/oregen.json");
		stringstream buffer;
		buffer << file.rdbuf();
		string data(buffer.str());
		file.close();
		rapidjson::Document doc;
		doc.Parse(data.c_str());
		int tmp = 0;
		if (doc.IsArray()) {
			for (size_t s = 0; s < doc.Size(); s++) {

				if ((doc[s]["Vaule"].IsInt() && doc[s]["Block"].IsString()) && doc[s]["Vaule"].GetInt() != 0) {
					Ores.push_back({ doc[s]["Block"].GetString() ,{tmp,tmp + doc[s]["Vaule"].GetInt()} });
					cout << "[OreGen] " << Ores[s].first << "\t[" << Ores[s].second.first << " - " << Ores[s].second.second - 1 << "]" << endl;
					tmp += doc[s]["Vaule"].GetInt();

				}
				else {
					cout << "[OreGen] Error Num,Plz check your Config File" << endl;
					Sleep(1000000);
					exit(1);
				}
			}
			total = tmp;
			cout << "[OreGen] Total Chance = " << total << endl;
		}
		else {
			cout << "[OreGen] Json Error: Json File Is Not A Array" << endl;
		}
	}
	catch (string e) {
		printf("[OreGen] JSON ERROR %s\n", e.c_str());
		Sleep(1000000);
		exit(1);
	}
}


const struct HashedString* getFullName(Block* block) {
	return (const struct HashedString*)(block + 120);
}


Block& Str2Block(string str) {
	string bstr = "?m" + str + "@VanillaBlocks@@3PEBVBlock@@EB";
	return **(Block**)dlsym_real(bstr.c_str());
}

#define setBlockSym "?setBlock@BlockSource@@QEAA_NAEBVBlockPos@@AEBVBlock@@HPEBUActorBlockSyncMessage@@@Z"
THook(bool, "?solidify@LiquidBlock@@IEBA_NAEAVBlockSource@@AEBVBlockPos@@1@Z", void* _this, BlockSource* bs, BlockPos* bpos1, BlockPos* bpos2) {
	string blname = "";
	bool vaule = original(_this, bs, bpos1, bpos2);
	if (vaule) {
		Block* pBlk = SymCall("?getBlock@BlockSource@@QEBAAEBVBlock@@AEBVBlockPos@@@Z", Block*, BlockSource*, BlockPos*)(bs, bpos1);
		blname  = getFullName(pBlk);
		//cout << bname << endl;
		if (blname == "minecraft:cobblestone") {
			random_device rd;
			rand_num = (rd() + atoi(gettimenum().c_str())) % total;
			//cout << "rand_num [" << rand_num << "]" << endl;
			for (size_t s = 0; s < Ores.size(); s++) {
				if (rand_num > Ores[s].second.first && rand_num < Ores[s].second.second) {
					SymCall(setBlockSym, bool, BlockSource*, BlockPos*, Block&, int, __int64*)(bs, bpos1, Str2Block(Ores[s].first), 3, 0i64);
					break;
				}
			}

		}
	}
	return vaule;
}
void oregen_entry() {
	rand_num = atoi(gettimenum().c_str());
	loadconf();
	cout << "[OreGen] OreGen Loaded, By WangYneos, Build Date [" << __TIMESTAMP__ << u8"] @Losenone丨洛书南 定制版" << endl;
}
