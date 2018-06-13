#include "TES3StaticLua.h"

#include "sol.hpp"
#include "LuaManager.h"

#include "TES3Static.h"

namespace mwse {
	namespace lua {
		void bindTES3Static() {
			// Get our lua state.
			sol::state& state = LuaManager::getInstance().getState();

			// Start our usertype. We must finish this with state.set_usertype.
			auto usertypeDefinition = state.create_simple_usertype<TES3::Static>();
			usertypeDefinition.set("new", sol::no_constructor);

			// Define inheritance structures. These must be defined in order from top to bottom. The complete chain must be defined.
			usertypeDefinition.set(sol::base_classes, sol::bases<TES3::PhysicalObject, TES3::Object, TES3::BaseObject>());

			// Allow object to be converted to strings using their object ID.
			usertypeDefinition.set(sol::meta_function::to_string, &TES3::Static::getObjectID);

			// Functions exposed as properties.
			usertypeDefinition.set("model", sol::property(&TES3::Static::getModelPath, &TES3::Static::setModelPath));

			// Finish up our usertype.
			state.set_usertype("tes3static", usertypeDefinition);
		}
	}
}
