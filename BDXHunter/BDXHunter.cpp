#include <lbpch.h>
#include <iostream>
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
#include "pch.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "Helper.h"
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
void entry() {
	loadconfig();
	std::cout << "[" << gettime() << u8" BDXHunter] Loaded!\n";
}

THook(void, "?die@Mob@@UEAAXAEBVActorDamageSource@@@Z", Mob* _this, ActorDamageSource* a2) {
	    string Mob_name = _this->getNameTag();
	    string Mob_type_name = SymCommandUtils::getActorName(_this);
		string Mob_name2 = SymCall("?EntityTypeToString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4ActorType@@W4ActorTypeNamespaceRules@@@Z", string, int, int)(_this->getEntityTypeId(), 1);
		ActorUniqueID src_id = a2->getEntityUniqueID();
		Actor* Src = LocateS<ServerLevel>()->fetchEntity(src_id, false);
		int srccode = dAccess<int>(a2, 8);
		string cause_n = SymActorDamageSource::lookupCauseName(srccode);
		string src_name, mob_name, Src_type_name, Src_name;
		if (Src) {
			Src_name = Src->getNameTag();
			Src_type_name = SymCommandUtils::getActorName(Src);
			if (!Mob_type_name.empty()) {
				if (Mob_name == Mob_type_name) {
					mob_name = Mob_name;
				}
				else {
					mob_name = Mob_name;
				}
			}
			if (!Src_type_name.empty()) {
				if (!Src_name.empty())
					src_name = Src_name;
				else
					src_name = Src_type_name;
			}
			else {
				src_name = "unknow";
			}
		}
		else {
			if (!Mob_type_name.empty()) {
				if (Mob_name == Mob_type_name) {
					mob_name = Mob_name;
					
				}
				else {
					mob_name = Mob_type_name;
				}
			}
			src_name = "unknow";
				}
		if (srccode == 2 || srccode == 3) {
			Player* spl = _this->getLastHurtByPlayer();
			auto pl = WPlayer(*(ServerPlayer*)spl);
			for (size_t a = 0; a < config.Size(); a++) {
				if (config[a].GetString() == Mob_name2)
				{
					long money = Money::getMoney(pl.getXuid());
					int max = config[config[a].GetString()]["max"].GetInt();
					int min = config[config[a].GetString()]["min"].GetInt();
					auto num1 = min + (int)max * rand() / (RAND_MAX + 1);
					Money::createTrans(0, pl.getXuid(), num1);
					pl.sendText(u8"成功击杀" + mob_name + u8" 获得了" + std::to_string(num1) + config["coinname"].GetString() + u8" 当前余额:" + std::to_string(money + num1), TIP);
				}
			}
		}
		original(_this, a2);
			
}

