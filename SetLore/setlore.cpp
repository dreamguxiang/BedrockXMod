#include <iostream>
#include <lbpch.h>
#include "pch.h"
#include <api/Loader.h>
#include <api/MC.h>
#include <mcapi/Player.h>
#include <string>
#include <vector>
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
	set = 1
};
bool onCMDSl(CommandOrigin const& ori, CommandOutput& outp, MyEnum<slcmd> op, string& name) {
	switch (op)
	{
	case slcmd::set: {
		auto sp = MakeSP(ori);
		vector<string> v2;
		v2.push_back(name);
		if (!sp) return false;
		auto item = sp->getSelectedItem();
		auto itemname = item.getName();
		item.setCustomLore(v2);
		//sp->SymCall("?forceBalanceTransaction@InventoryTransactionManager@@QEAAXXZ",void*);
		outp.addMessage(u8"成功");
		break;
	}
	}
}
bool onCMD_Sl(CommandOrigin const& ori, CommandOutput& outp, MyEnum<slcmd> op, string& name) {
	return onCMDSl(ori, outp, op, name);
}
enum class slcmd1 :int {
	rawset = 1
};

bool onCMDSll(CommandOrigin const& ori, CommandOutput& outp, MyEnum<slcmd1> op, string& name) {
	switch (op)
	{
	case slcmd1::rawset: {
		vector<string> lores;
		rapidjson::Document json;
		auto sp = MakeSP(ori);
		json.Parse(name.c_str());
		auto lore = json["text"].GetArray();
		for (auto i = lore.begin(); i != lore.end(); i++) lores.push_back(i->GetString());
		auto item = sp->getSelectedItem();
		item.setCustomLore(lores);
		outp.addMessage(u8"成功");
		break;
	}
	}
}
bool onCMD_Sll(CommandOrigin const& ori, CommandOutput& outp, MyEnum<slcmd1> op, string& name) {
	return onCMDSll(ori,  outp,  op, name);
}
void entry() {
	loadconfig();
	addListener([](RegisterCommandEvent&) {
		CEnum<slcmd> _1("slcmd", {"set"});
		CEnum<slcmd1> _2("slcmd1", {"rawset" });
		MakeCommand("lore", "lore menu", 1);
		CmdOverload(lore, onCMD_Sl, "op","name");
		MakeCommand("lore", "lore menu", 1);
		CmdOverload(lore, onCMD_Sll, "op", "json");
		});
}

