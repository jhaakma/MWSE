#include "TES3SoundLua.h"

#include "sol.hpp"
#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Sound.h"
#include "TES3SoundGenerator.h"

namespace mwse {
	namespace lua {
		void bindTES3Sound() {
			// Get our lua state.
			sol::state& state = LuaManager::getInstance().getState();

			// Binding for TES3::Sound.
			{
				// Start our usertype. We must finish this with state.set_usertype.
				auto usertypeDefinition = state.create_simple_usertype<TES3::Sound>();
				usertypeDefinition.set("new", sol::no_constructor);

				// Define inheritance structures. These must be defined in order from top to bottom. The complete chain must be defined.
				usertypeDefinition.set(sol::base_classes, sol::bases<TES3::BaseObject>());

				// Allow object to be converted to strings using their object ID.
				usertypeDefinition.set(sol::meta_function::to_string, &TES3::Sound::getObjectID);

				// Override the id property to use the soundgen name, rather than the vtable.
				usertypeDefinition.set("id", sol::readonly_property([](TES3::Sound& self) { return self.id; }));

				// Access to other objects that need to be packaged.
				usertypeDefinition.set("filename", sol::readonly_property([](TES3::Sound& self) { return self.filename; }));

				// Basic function binding.
				usertypeDefinition.set("play", [](TES3::Sound& self, sol::optional<sol::table> params)
				{
					TES3::Reference* reference = getOptionalParamReference(params, "reference");
					unsigned char volume = getOptionalParam<double>(params, "volume", 1.0) * 255;
					float pitch = getOptionalParam<double>(params, "pitch", 1.0);
					int flag = getOptionalParam<double>(params, "flag", 0.0);
					return self.play(reference, volume, pitch, flag);
				}
				);

				// Finish up our usertype.
				state.set_usertype("tes3sound", usertypeDefinition);
			}

			// Binding for TES3::SoundGenerator.
			{
				// Start our usertype. We must finish this with state.set_usertype.
				auto usertypeDefinition = state.create_simple_usertype<TES3::SoundGenerator>();
				usertypeDefinition.set("new", sol::no_constructor);

				// Define inheritance structures. These must be defined in order from top to bottom. The complete chain must be defined.
				usertypeDefinition.set(sol::base_classes, sol::bases<TES3::BaseObject>());

				// Allow object to be converted to strings using their object ID.
				usertypeDefinition.set(sol::meta_function::to_string, &TES3::SoundGenerator::getObjectID);

				// Basic property binding.
				usertypeDefinition.set("type", sol::readonly_property(&TES3::SoundGenerator::soundType));

				// Override the id property to use the soundgen name, rather than the vtable.
				usertypeDefinition.set("id", sol::readonly_property([](TES3::SoundGenerator& self) { return self.name; }));

				// Access to other objects that need to be packaged.
				usertypeDefinition.set("sound", sol::readonly_property([](TES3::SoundGenerator& self) { return makeLuaObject(self.sound); }));

				// Finish up our usertype.
				state.set_usertype("tes3soundGenerator", usertypeDefinition);
			}
		}
	}
}
