/************************************************************************
	
	xGetEnchantInfo.cpp - Copyright (c) 2008 The MWSE Project
	http://www.sourceforge.net/projects/mwse

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"

using namespace mwse;

namespace mwse
{
	class xGetEnchantInfo : mwse::InstructionInterface_t
	{
	public:
		xGetEnchantInfo();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xGetEnchantInfoOpcode = 0x3929;
	static xGetEnchantInfo xGetEnchantInfoInstance;

	xGetEnchantInfo::xGetEnchantInfo() : mwse::InstructionInterface_t(xGetEnchantInfoOpcode) {}

	void xGetEnchantInfo::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xGetEnchantInfo::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Get parameters.
		mwseString_t enchantId = virtualMachine.getString(Stack::getInstance().popLong());

		// Return values.
		mwShort_t type = 0;
		mwShort_t cost = 0;
		mwLong_t maxCharge = 0;
		mwShort_t effects = 0;
		mwLong_t autocalc = 0;

		// Validate effect index.
		ENCHRecord_t* enchantment = tes3::getEnchantRecordById(enchantId);
		if (enchantment) {
			type = enchantment->type;
			cost = enchantment->cost;
			maxCharge = enchantment->charge;
			effects = tes3::getEffectCount(enchantment->effects);
			autocalc = enchantment->autocalc;
		}

		mwse::Stack::getInstance().pushLong(autocalc);
		mwse::Stack::getInstance().pushLong(effects);
		mwse::Stack::getInstance().pushLong(maxCharge);
		mwse::Stack::getInstance().pushLong(cost);
		mwse::Stack::getInstance().pushLong(type);

		return 0.0f;
	}
}