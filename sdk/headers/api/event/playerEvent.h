#pragma once
#include "eventBase.h"
#include "../types/types.h"
class PlayerChatEvent : public IGenericPlayerEvent<PlayerChatEvent> {
public:
	string& _chat;
	PlayerChatEvent(ServerPlayer& sp, string& chat) : IGenericPlayerEvent(sp), _chat(chat) {}
	const string& getChat() {
		return _chat;
	}
};
class PlayerCMDEvent : public IGenericPlayerEvent<PlayerCMDEvent> {
public:
	string_view _cmd;
	PlayerCMDEvent(ServerPlayer& sp, string_view cmd) : IGenericPlayerEvent(sp), _cmd(cmd) {}
	string_view getCMD() {
		return _cmd;
	}
};
class PlayerChangeDimEvent : public IEventBase<PlayerChangeDimEvent>,public IPlayerEvent {
public:
	int DstDim,SrcDim;
	PlayerChangeDimEvent(ServerPlayer& sp,int src,int dst):IPlayerEvent(sp) {
		DstDim = dst;
		SrcDim = src;
	}
};
class PlayerPreJoinEvent : public IEventBase<PlayerPreJoinEvent> {
public:
	class Certificate& cert;
	class NetworkIdentifier& neti;
	PlayerPreJoinEvent(class Certificate& a, class NetworkIdentifier& b) : cert(a), neti(b) {}
};
class PlayerJoinEvent : public IEventBase<PlayerJoinEvent>, public IPlayerEvent {
public:
	using IPlayerEvent::IPlayerEvent;
};
class PlayerLeftEvent : public IEventBase<PlayerLeftEvent>, public IPlayerEvent {
public:
	using IPlayerEvent::IPlayerEvent;
};
class PlayerDeathEvent : public IEventBase<PlayerDeathEvent>, public IPlayerEvent {
public:
	using IPlayerEvent::IPlayerEvent;
};

class PlayerDestroyEvent : public IGenericPlayerEvent<PlayerDestroyEvent> {
public:
	BlockPos& pos;
	PlayerDestroyEvent(ServerPlayer& sp, BlockPos& _pos) : IGenericPlayerEvent(sp), pos(_pos) {}
	const BlockPos& getPos() {
		return pos;
	}
};
class PlayerUseItemOnEntityEvent : public IGenericPlayerEvent<PlayerUseItemOnEntityEvent> {
public:
	class ActorRuntimeID rtid;
	Actor* victim;
	enum class TransType:char {
		INTERACT=0,
		ATTACK=1
	} type;
	LBAPI PlayerUseItemOnEntityEvent(ServerPlayer& sp, ActorRuntimeID rti, int _type);
	bool isAttack() {
		return type == TransType::ATTACK;
	}
};
class PlayerUseItemOnEvent : public IGenericPlayerEvent<PlayerUseItemOnEvent> {
public:
	BlockPos& pos;
	uchar side;
	WItem item;
	bool maySpam;
	PlayerUseItemOnEvent(ServerPlayer& sp, BlockPos& _pos,WItem _item, uchar _side,bool _spam) : IGenericPlayerEvent(sp), pos(_pos), side(_side),item(_item),maySpam(_spam) {}
	BlockPos& getPos() {
		return pos;
	}
	BlockPos getPlacePos() {
		const int Z[] = { 0, 0, -1, 1, 0, 0 };
		const int X[] = { 0, 0, 0, 0, -1, 1 };
		const int Y[] = { -1, 1, 0, 0, 0, 0 };
		BlockPos dpos = { pos.x + X[side], pos.y + Y[side], pos.z + Z[side] };
		return dpos;
	}
	uchar getSide() {
		return side;
	}
	WItem getItemInHand() {
		return item;
	}
};
class PlayerUseItemEvent : public IGenericPlayerEvent<PlayerUseItemEvent> {
public:
	WItem item;
	PlayerUseItemEvent(ServerPlayer& sp,WItem _item) : IGenericPlayerEvent(sp), item(_item) {}
	WItem getItem() {
		return item;
	}
};
