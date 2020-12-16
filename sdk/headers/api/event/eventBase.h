#pragma once
#include<lbpch.h>
#include<variant>
#include<api/types/types.h>
#include<I18N.h>
#include<debug/WatchDog.h>
#include<functional>
using std::string, std::function,std::variant;
enum class EvPrio:int
{
	LOW = 0,
	MEDUIM = 1,
	HIGH = 2
};
LIGHTBASE_API int newListenerID();
template<typename T>
struct LInfo {
	int id=-1;
};
class ICancellableEvent {
	bool cancelled;
public:
	bool isCancelled() {
		return cancelled;
	}
	operator bool() {
		return !isCancelled();
	}
	void setCancelled(bool c = true) {
		cancelled = c;
	}
	ICancellableEvent() :cancelled(false) {}
};
#include<stl\CBStorage.h>
template<class T>
struct CallBackStorage {
	CBStorage<T> data;
	LInfo<T> id;
#ifdef TRACING_ENABLED
	string note;
#endif
	#ifdef TRACING_ENABLED
		#define CBINFO ,string&& note_
	#else
		#define CBINFO 
	#endif
	operator bool() {
		return id.id!=-1;
	}
	void operator()(T& arg) {
		data(arg);
	}
	CallBackStorage() {
		id.id = -1;
	}
	CallBackStorage(CBStorage<T>&& fun, LInfo<T> lf CBINFO) : data(std ::move(fun)),
															  id(lf)
	{
		#ifdef TRACING_ENABLED
		note = std::move(note_);
		#endif
	}
};
#ifdef LIGHTBASE_EXPORTS
static inline void logError(const char* e,const char* T) {
	char ebuf[1024];
	snprintf(ebuf, 1024, I18N::EVENT_EXCEPTION_S.c_str(), e, T);
	LOG.l<LOGLVL::Error>(ebuf);
}
#else
static inline void logError(const char* e, const char* T) {
	printf(I18N::EVENT_EXCEPTION_S.c_str(), e, T);
}
#endif
#include<debug/WatchDog.h>
template <class T>
class EventCaller {
	 LIGHTBASE_API static std::list<CallBackStorage<T>> listener;
public:
	template<typename... P>
	static auto _call(P&&... args) {
		T ev(std::forward<P>(args)...);
		try {
			for (auto& i : EventCaller<T>::listener) {
				if (!i)
					continue;
				WATCH_ME(string("call event ") + typeid(T).name() + "\n at " + i.note);
					i(ev);
				if (ev.isAborted()) break;
			}
		}
		catch (std::exception e) {
			logError(e.what(), typeid(T).name());
		}
		catch (string e) {
			logError(e.c_str(), typeid(T).name());
		}
		catch (...) {
			logError("unk error", typeid(T).name());
		}
		if constexpr (std::is_base_of<ICancellableEvent, T>())
			return !ev.isCancelled();
		else
			return;
	}
	static void _removeall() {
		listener.clear();
	}
	template<typename... TP>
	static LInfo<T> _reg(CBStorage<T>&& cb, EvPrio prio,TP&&... args) {
		LInfo<T> lf;
		lf.id = newListenerID();
		if (prio == EvPrio::HIGH) {
			listener.emplace_front(std::move(cb), lf, std::forward<TP>(args)...);
			return lf;
		}
		if (prio == EvPrio::LOW) {
			listener.emplace_back(std::move(cb), lf, std::forward<TP>(args)...);
			return lf;
		}
		for (auto it = listener.begin(); it != listener.end(); ++it) {
			if (!(*it)) {
				//flag
				listener.emplace(it, std::move(cb), lf, std::forward<TP>(args)...);
				return lf;
			}
		}
		printf("[Event] Failed to register %s ,Dont use PRIO_MEDIUM when server started!!!\n",typeid(T).name());
		return { -1 };
	}
	static auto _remove(LInfo<T> lf) {
		return listener.remove_if([lf](auto& elem) -> bool { return elem.id.id == lf.id; });
	}
	static void _cleanup() {
		listener.remove_if([](auto& elem) -> bool { return !elem; });
	}
};

class IAbortableEvent {
	bool aborted;
public:
	void setAborted(bool c = true) {
		aborted = c;
	}
	bool isAborted() {
		return aborted;
	}
	IAbortableEvent() :aborted(false) {}
};
class ServerPlayer;
class IPlayerEvent {
	WPlayer sp;
public:
	WPlayer getPlayer() {
		return sp;
	}
	IPlayerEvent(ServerPlayer& s) :sp(s) {}
};
class IActorEvent {
	WActor sp;

public:
	WActor getActor() {
		return sp;
	}
	IActorEvent(Actor& s) : sp(s) {}
};
class IMobEvent {
	WMob sp;

public:
	WMob getMob() {
		return sp;
	}
	IMobEvent(Mob& s) : sp(s) {}
};
template<typename T>
class IEventBase :public EventCaller<T>, public IAbortableEvent {

};
template<class T>
class IGenericEvent :public IEventBase<T>, public ICancellableEvent {};
template<class T>
class IGenericPlayerEvent :public IGenericEvent<T>, public IPlayerEvent {
public:
	IGenericPlayerEvent(ServerPlayer& sp) :IPlayerEvent(sp) {}
};

template<class T>
class IGenericActorEvent : public IGenericEvent<T>, public IActorEvent {
public:
	IGenericActorEvent(Actor& sp) : IActorEvent(sp) {}
};

template<class T>
class INotifyEvent :public IEventBase<T> {};
template<class T>
class INotifyPlayerEvent :public INotifyEvent<T>, public IPlayerEvent {
public:
	INotifyPlayerEvent(ServerPlayer& sp) :IPlayerEvent(sp) {}
};



template<class T>
void removeListener(LInfo<T> lf) {
	T::_remove(lf);
}

struct addListener_caller {
	#ifdef TRACING_ENABLED
	string note;
	#endif
	addListener_caller(string&& n) {
		#ifdef TRACING_ENABLED
		note = std::forward<string>(n);
		#endif
	}
	template<typename T>
	auto realAddListener(CBStorage<T>&& cb, EvPrio prio) {
	#ifdef TRACING_ENABLED
		return T::_reg(std::move(cb), prio, std::move(note));
	#else
		return T::_reg(std::move(cb), prio);
	#endif
	}
	template<typename T>
	auto operator()(T&& cb,EvPrio prio=EvPrio::MEDUIM) {
		return realAddListener(MakeCB(cb), prio);
	}
};
#define addListener addListener_caller(std::to_string(__LINE__)+" :: "+__FILE__)