#pragma once

#include <Spore\BasicIncludes.h>

#define cImprCombManagerPtr intrusive_ptr<cImprCombManager>

class cImprCombManager 
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{
public:
	static const uint32_t TYPE = id("cImprCombManager");
	
	cImprCombManager();
	~cImprCombManager();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	void Update() override;
};
