// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BDXLog_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BDXLog_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#include <string>
#include <iostream>
#include <functional>
using namespace std;
typedef unsigned long long xuid_t;
#define BDXLog_API __declspec(dllexport)
class Vec3 {
public:
	float x, y, z;
	string toString() {
		return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
	}
};
class JoinEV {
public:
	string playername;
	int DimId;
	string IP;
	xuid_t xuid;
};
class ContainerInEV {
public:
	string playername;
	int DimId;
	int slot;
	int Count;
	string object_name;
};
class ContainerOutEV {
public:
	string playername;
	int DimId;
	int slot;
};
class MobDieEV {
public:
	string SrcTypeName;
	string SrcNameTag;
	string TargetTypeName;
	string TargetNameTag;
	string DieReason;
	string DieCode;
	Vec3 Pos;
};
class ItemDropEV {
public:
	string playername;
	string ItemName;
	string DropCount;
	Vec3 Pos;
	int DimId;
};
class ItemTakeEV {
public:
	string playername;
	string ItemName;
	Vec3 Pos;
	int DimId;
};
namespace BLogApi {
	BDXLog_API void addBehavorListener(function<void(JoinEV)> callback);
	BDXLog_API void addBehavorListener(function<void(ContainerOutEV)> callback);
	BDXLog_API void addBehavorListener(function<void(ContainerInEV)> callback);
	BDXLog_API void addBehavorListener(function<void(MobDieEV)> callback);
	BDXLog_API void addBehavorListener(function<void(ItemDropEV)> callback);
	BDXLog_API void addBehavorListener(function<void(ItemTakeEV)> callback);
};
