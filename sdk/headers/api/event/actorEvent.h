#pragma once
#include"eventBase.h"
class MobDeathEvent : public IMobEvent, public IEventBase<MobDeathEvent> {
	ActorDamageSource* src;
public:
	MobDeathEvent(Mob& _ac, ActorDamageSource* _src) : IMobEvent(_ac), src(_src) {}
	ActorDamageSource& getSource() {
		return *src;
	}
};
class MobHurtedEvent : public IMobEvent, public IGenericEvent < MobHurtedEvent >{
	ActorDamageSource* src;
	int& damage;
public:
	MobHurtedEvent(Mob& _ac, ActorDamageSource* _src, int& _dam) : IMobEvent(_ac), src(_src), damage(_dam) {}
	ActorDamageSource& getSource() {
		return *src;
	}
	int& getDamage() {
		return damage;
	}
};