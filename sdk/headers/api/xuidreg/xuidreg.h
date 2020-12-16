#pragma once
#include<string>
#include<mcapi/Core.h>
#include<stl/optional.h>
#include<functional>
typedef unsigned long long xuid_t;
using std::string;
namespace XIDREG {
	LBAPI optional<string> id2str(xuid_t xid);
	LBAPI optional<xuid_t> str2id(string_view name);
	LBAPI void foreach (std::function<bool(xuid_t, string_view)>&&);
	void initAll();
}