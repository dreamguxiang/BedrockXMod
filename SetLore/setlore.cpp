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
	if (filen == "config/setlore.json")
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
	ifstream in("config/setlore.json");
	ostringstream tmp;
	tmp << in.rdbuf();
	in.close();
	string data = tmp.str();
	config.Parse(data.c_str());
	int size = config.Size();
	cout << "[" << gettime() << u8" SetLore] loaded!!!" << endl;
	if (size == 0)
		cout << "[" << gettime() << u8" Error] No Member Found!!!" << endl;
}



enum class slcmd :int {
	set = 1,
	remove = 2,
	reload = 3
};


bool onCMD_Sl(CommandOrigin const& ori, CommandOutput& outp, MyEnum<slcmd> op , optional<string>& name) {
	switch (op)
	{
	case slcmd::set: {
		auto& str = name.val();
		for (int i = 0; i < str.size(); ++i) {
			if (str[i] == '^') str[i] = '\n';
		}
		auto sp = MakeSP(ori);
		if (!sp) return false;
		WPlayer wp{ *sp };
		if (ori.getPermissionsLevel() < 1) {
			return false;
		}
		auto item = sp->getSelectedItem();
		item.setCustomLore(     );
		outp.addMessage(u8"成功");
		break;
	}
	case slcmd::remove: {
		if (ori.getPermissionsLevel() < 1) {
			return false;
		}
		outp.addMessage(u8"失败");
		break;
	}
	case slcmd::reload: {
		if (ori.getPermissionsLevel() < 1) {
			return false;
		}
		loadconfig();
		outp.addMessage(u8"重载成功");
	}
	}
}


void entry() {
	loadconfig();
	addListener([](RegisterCommandEvent&) {
		CEnum<slcmd> _1("slcmd", { "set","remove","reload"});
		MakeCommand("lore", "lore menu", 1);
		CmdOverload(lore, onCMD_Sl, "op","name");
		});
}

