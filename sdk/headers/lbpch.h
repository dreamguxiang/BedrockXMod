#ifndef  LBPCH_H
#define LBPCH_H
#include <stl/Logger.h>
#ifdef LIGHTBASE_EXPORTS
extern Logger<stdio_commit> LOG;
#endif
#include<cstdio>
#include<cstring>
#include<string>
#include<string_view>
#include<memory>

using std::string, std::string_view,std::shared_ptr,std::unique_ptr;
using namespace std::string_literals;
using std::make_shared, std::make_unique;

#include"api/hash.h"
#include"api/lightbase.h"
#include"api/hook.h"
#include"api/Loader.h"
#include<mcapi/Core.h>
#include<api/serviceLocate.h>
#include<stl/views.h>
#include<api/types/types.h>
#include<api/event/event_pch.h>

#include<stl\useful.h>
#include<debug/WatchDog.h>

#endif