/************************************************************************
	
	xPow.cpp - Copyright (c) 2008 The MWSE Project
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

#include <math.h>

using namespace mwse;

namespace mwse
{
	class xPow : mwse::InstructionInterface_t
	{
	public:
		xPow();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xPowOpcode = 0x383A;
	static xPow xPowInstance;

	xPow::xPow() : mwse::InstructionInterface_t(xPowOpcode) {}

	void xPow::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xPow::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		if (mwse::Stack::getInstance().size() != 2) {
			return 0;
		}

		mwFloat_t base = mwse::Stack::getInstance().popFloat();
		mwFloat_t exponent = mwse::Stack::getInstance().popFloat();

		mwse::Stack::getInstance().pushFloat(std::powf(base, exponent));

		return 0.0;
	}
}