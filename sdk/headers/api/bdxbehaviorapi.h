// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� BDXLog_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ���Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// BDXLog_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
