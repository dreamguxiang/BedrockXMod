#include <iostream>
#include <lbpch.h>
#include "pch.h"
#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <streambuf>
#include <api/command/commands.h>
#include <api/types/types.h>
#include "Helper.h"
#include <iostream>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
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
	if (filen == "config\\Motd.json")
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
using namespace rapidjson;
rapidjson::Document config;
void loadconfig() {
	ifstream in("config\\Motd.json");
	ostringstream tmp;
	tmp << in.rdbuf();
	in.close();
	string data = tmp.str();
	config.Parse(data.c_str());
	int size = config.Size();
	if (size == 0)
		cout << "[" << gettime() << u8" Error] No Member Found!!!" << endl;
}

short ticks = 0;
THook(void, "?onTick@ServerNetworkHandler@@UEAAXXZ", ServerNetworkHandler* _this) {
	ticks++;
	if (ticks <= 1) {
		for (auto& m : config.GetObject()){
			std::thread t([&]{
				motd::setServerMotd(_this, "aaaaa", true);
				std::this_thread::sleep_for(std::chrono::seconds(5));
				});
			t.detach();
		}
	}	

}
void entry() {
	loadconfig();
};