#pragma once
struct WPlayer;
#include<string>
#include<stl\useful.h>
class NetworkIdentifier;
namespace BDX {
	using std::string;
	LBAPI bool runcmd(const string& cmd);
	LBAPI bool runcmdAs(WPlayer, const string& cmd);
	LBAPI std::pair<bool, string> runcmdEx(const string& cmd);
	LBAPI bool runcmd(string&& cmd);
	LBAPI bool runcmdAs(WPlayer, string&& cmd);
	LBAPI std::pair<bool, string> runcmdEx(string&& cmd);
	LBAPI string getIP(NetworkIdentifier&);
	template<typename T>
	static inline void APPEND(string& r,T&& x) {
		r.append(S(std::forward<T>(x)));
		r.push_back(' ');
	}
	template<typename... T>
	static inline bool runcmdA(T&&... a) {
		string s;
		(APPEND(s,std::forward<T>(a)), ...);
		return runcmd(std::move(s));
	}
	template<typename N,typename... T>
	static inline bool runcmdAsA(N p,T&&... a) {
		string s;
		(APPEND(s, std::forward<T>(a)), ...);
		return runcmdAs(p, std::move(s));
	}
};