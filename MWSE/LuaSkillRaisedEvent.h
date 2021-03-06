#pragma once

#include "LuaGenericEvent.h"
#include "LuaDisableableEvent.h"

namespace mwse {
	namespace lua {
		namespace event {
			class SkillRaisedEvent : public GenericEvent, public DisableableEvent<SkillRaisedEvent> {
			public:
				SkillRaisedEvent(int skillId, float newLevel);
				sol::table createEventTable();
				sol::object getEventOptions();

			protected:
				int m_Skill;
				float m_NewLevel;
			};
		}
	}
}
