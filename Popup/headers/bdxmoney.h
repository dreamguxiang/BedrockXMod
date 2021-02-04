// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BDXMONEY_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BDXMONEY_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef BDXMONEY_EXPORTS
#define BDXMONEY_API __declspec(dllexport)
#else
#define BDXMONEY_API __declspec(dllimport)
#endif
typedef long long money_t;
typedef unsigned long long xuid_t;
namespace Money {
	BDXMONEY_API money_t getMoney(xuid_t xuid);
	BDXMONEY_API string getTransHist(xuid_t xuid, int timediff = 24 * 60 * 60);
	BDXMONEY_API bool createTrans(xuid_t from, xuid_t to, money_t val, string const& note = "");
	BDXMONEY_API bool setMoney(xuid_t xuid, money_t money);
	BDXMONEY_API bool reduceMoney(xuid_t xuid, money_t money);
	BDXMONEY_API void purgeHist(int difftime=0);
};
