#pragma once
#include "eventBase.h"
class LevelExplodeEvent : public IEventBase<LevelExplodeEvent>,public ICancellableEvent {
public:
	WExplosion& exp;
	LevelExplodeEvent(WExplosion& _exp) : exp(_exp) {}
};