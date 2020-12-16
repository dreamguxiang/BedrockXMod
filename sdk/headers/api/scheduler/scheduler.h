#pragma once
#include<lbpch.h>
#include "../serviceLocate.h"
#include <api/lightbase.h>
typedef unsigned long long tick_t;
typedef unsigned int taskid_t;
namespace Handler {
	extern LIGHTBASE_API tick_t ticknow;
	extern LIGHTBASE_API taskid_t gtaskid;
	//#ifdef LIGHTBASE_EXPORTS
	extern LIGHTBASE_API tick_t _tick;
	//#endif
	struct ITaskBase {
		tick_t schedule_time;
		tick_t interval;
		taskid_t taskid;
		function<void(void)> cb;
		ITaskBase(function<void(void)>&& fn, tick_t time_diff, tick_t interval, taskid_t tid) : schedule_time(Handler::ticknow + time_diff), interval(interval), taskid(tid), cb(std::move(fn)) {}
	};
	LIGHTBASE_API bool cancel(taskid_t id);
	LIGHTBASE_API taskid_t schedule(ITaskBase&& task);
	LIGHTBASE_API void scheduleNext(function<void()>&& fn);
};

struct DelayedTask:Handler::ITaskBase {
	DelayedTask(function<void(void)>&& fn, tick_t time_diff) : Handler::ITaskBase(std::move(fn),time_diff,0,++Handler::gtaskid) {}
};
struct RepeatingTask : Handler::ITaskBase {
	RepeatingTask(function<void(void)>&& fn, tick_t interval) : Handler::ITaskBase(std::move(fn), 0, interval, ++Handler::gtaskid) {}
};
struct DelayedRepeatingTask : Handler::ITaskBase {
	DelayedRepeatingTask(function<void(void)>&& fn, tick_t time_diff, tick_t interval) : Handler::ITaskBase(std::move(fn), time_diff, interval, ++Handler::gtaskid) {}
};


