#pragma once
#include<lbpch.h>
#define MCAPI __declspec(dllimport)
#define MCINLINE inline
#define MCCLS
#include"mass.h"
#include<stl/Bstream.h>
enum ActorType : int;
enum class AbilitiesIndex : int;
static inline int iround(float x) {
	int r = int(x);
	if (x < 0)
		r--;
	return r;
}

class Vec3 {
public:
	float x, y, z;
	string toString() {
		return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
	}
	template<typename _TP>
	void pack(WBStreamImpl<_TP>& ws) const {
		ws.apply(x, y, z);
	}
	void unpack(RBStream& rs) {
		rs.apply(x, y, z);
	}
};
class BlockPos {
public:
	int x, y, z;
	inline bool operator==(BlockPos const& rv)const {
		return x == rv.x && y == rv.y && z == rv.z;
	}
	inline bool operator!=(BlockPos const& rv)const {
		return x != rv.x || y != rv.y || z != rv.z;
	}
	template<typename _TP>
	void pack(WBStreamImpl<_TP>& ws) const {
		ws.apply(x, y, z);
	}
	void unpack(RBStream& rs) {
		rs.apply(x, y, z);
	}
};
struct IVec2 {
	int x, z;
	IVec2(Vec3 l) {
		x = iround(l.x);
		z = iround(l.z);
	}
	IVec2(int a,int b):x(a),z(b){}
	void operator+=(int v) {
		x += v;
		z += v;
	}
};
template <typename A, typename T>
class AutomaticID {
	T id;
public:
	AutomaticID() {
		id = 0;
	}
	AutomaticID(T x) {
		id = x;
	}
	operator T() {
		return id;
	}
};
struct Tick {
	unsigned long long t;
};
struct ActorUniqueID {
	long long id;
public:
	ActorUniqueID() {
		id = -1;
	}
	ActorUniqueID(long long i) {
		id = i;
	}
	auto get() {
		return id;
	}
	operator long long() {
		return id;
	}
};
static_assert(!std::is_pod_v<ActorUniqueID>);
class ActorRuntimeID {
public:
	unsigned long long id;
	auto get() {
		return id;
	}
	operator unsigned long long() {
		return id;
	}
};
static_assert(std::is_pod_v<ActorRuntimeID>);

/*
 dq offset _ZNK17ActorDamageSource14isEntitySourceEv ; ActorDamageSource::isEntitySource(void)
.data.rel.ro:000000000AE853E8                 dq offset _ZNK17ActorDamageSource19isChildEntitySourceEv ; ActorDamageSource::isChildEntitySource(void)
.data.rel.ro:000000000AE853F0                 dq offset _ZNK17ActorDamageSource13isBlockSourceEv ; ActorDamageSource::isBlockSource(void)
.data.rel.ro:000000000AE853F8                 dq offset _ZNK17ActorDamageSource15getDeathMessageENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEP5Actor ; ActorDamageSource::getDeathMessage(std::__cxx11::basic_string<char,std::char_traits<char>,std::allocator<char>>,Actor *)
.data.rel.ro:000000000AE85400                 dq offset _ZNK17ActorDamageSource13getIsCreativeEv ; ActorDamageSource::getIsCreative(void)
.data.rel.ro:000000000AE85408                 dq offset _ZNK17ActorDamageSource17getIsWorldBuilderEv ; ActorDamageSource::getIsWorldBuilder(void)
.data.rel.ro:000000000AE85410                 dq offset _ZNK17ActorDamageSource17getEntityUniqueIDEv ; ActorDamageSource::getEntityUniqueID(void)
.data.rel.ro:000000000AE85418                 dq offset _ZNK17ActorDamageSource13getEntityTypeEv ; ActorDamageSource::getEntityType(void)
.data.rel.ro:000000000AE85420                 dq offset _ZNK17ActorDamageSource19getEntityCategoriesEv ; ActorDamageSource::getEntityCategories(void)
.data.rel.ro:000000000AE85428                 dq offset _ZNK17ActorDamageSource27getDamagingEntityIsCreativeEv ; ActorDamageSource::getDamagingEntityIsCreative(void)
.data.rel.ro:000000000AE85430                 dq offset _ZNK17ActorDamageSource31getDamagingEntityIsWorldBuilderEv ; ActorDamageSource::getDamagingEntityIsWorldBuilder(void)
.data.rel.ro:000000000AE85438                 dq offset _ZNK17ActorDamageSource25getDamagingEntityUniqueIDEv ; ActorDamageSource::getDamagingEntityUniqueID(void)
.data.rel.ro:000000000AE85440                 dq offset _ZNK17ActorDamageSource21getDamagingEntityTypeEv ; ActorDamageSource::getDamagingEntityType(void)
.data.rel.ro:000000000AE85448                 dq offset _ZNK17ActorDamageSource27getDamagingEntityCategoriesEv ; ActorDamageSource::getDamagingEntityCategories(void)
.data.rel.ro:000000000AE85450                 dq offset _ZNK17ActorDamageSource5cloneEv

*/

class ActorDamageSource {
private:
	char filler[0x10];

public:
	virtual void destruct1(unsigned int) = 0;
	virtual bool isEntitySource() const = 0;
	virtual bool isChildEntitySource() const = 0;
	virtual bool isBlockSource() const = 0;
	virtual bool isFire() const = 0;//NOTE:1.16 only
private:
	virtual void getDeathMessage() const = 0;
public:
	virtual bool isCreative() const = 0;
	virtual bool IsWorldBulider() const = 0;
	virtual ActorUniqueID getEntityUniqueID() const = 0;
	virtual int getEntityType() const = 0;
	virtual int getEntityCategories() const = 0;
	virtual bool DamagingIsCreative() const = 0;
	virtual bool DamagingIsWorldBuilder() const = 0;
	virtual ActorUniqueID getDamagingEntityUniqueID() const = 0;
	virtual int getDamagingEntityType() const = 0;
	virtual int getDamagingEntityCategories() const = 0;
};

class ChunkPos {
public:
	int x, z;
};

constexpr const int SAFE_PADDING = 0;