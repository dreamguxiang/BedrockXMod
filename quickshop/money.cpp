#include "pch.h"
#include <rapidjson/document.h>
#include<streambuf>
#include<api/command/commands.h>
#include<api/types/types.h>
#include<api/event/event_pch.h>
#include <api/gui/gui.h>
#include <iostream>
#include <lbpch.h>
#include "pch.h"
#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <windows.h>
#include <bdxmoney.h>


int _access(const char
	* path, int mode);

using namespace std;
#pragma warning(disable:4996)
inline string gettime() {
	time_t rawtime;
	tm* LocTime;
	char timestr[20];
	time(&rawtime);
	LocTime = localtime(&rawtime);
	strftime(timestr, 20, "%Y%m%d%H%M%S%U%w", LocTime);
	return string(timestr);
}

inline void fw(const string& filen, const string& instr)
{
	if (filen == "config/QuickShop.json")
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
	ifstream in("config/QuickShop.json");
	ostringstream tmp;
	tmp << in.rdbuf();
	in.close();
	string data = tmp.str();
	config.Parse(data.c_str());
	int size = config.Size();
	if (size == 0)
		cout << "[" << gettime() << u8" Error] No Member Found!!!" << endl;
	exit(1);

}


void Join() {
	addListener([](PlayerJoinEvent& event) {

		event.getPlayer();
		event.getPlayer().getName();
		auto p_xuid = event.getPlayer().getXuid();

		});
}

THook(void, "?onScoreChanged@ServerScoreboard@@UEAAXAEBUScoreboardId@@AEBVObjective@@@Z",
	void* _this, const struct ScoreboardId* a2, const struct Objective* a3) {
	if (a3)
		std::cout << a2 << endl;
	    std::cout << a3 << endl;
		return original(_this, a2, a3);
}

void entry()
{
	std::cout << "[fuck] Loaded!\n";
}