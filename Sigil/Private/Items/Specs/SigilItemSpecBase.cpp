// Copyright © 2025 Hard Edge Games. All Rights Reserved.


#include "Items/Specs/SigilItemSpecBase.h"

#include "Items/InstanceObjects/SigilItemInstanceBase.h"

USigilItemInstanceBase* USigilItemSpecBase::CreateItemInstance(UObject* Outer) const
{
	 return NewObject<USigilItemInstanceBase>(Outer);	
}
