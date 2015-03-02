#include "ConfigManager.h"
#include "engine/common/CommandSystem.h"
#include "engine/common/ConfigVar.h"
#include "engine/common/ConfigPersisterSQL.h"
#include "engine/common/ConfigPersisterNOP.h"
#include "engine/common/IBindingSpaceListener.h"
#include "engine/common/Logger.h"
#include "engine/common/LUA.h"
#include "engine/common/GLShared.h"
#include "engine/common/System.h"
#include <SDL.h>
#include <SDL_platform.h>
#include <map>
#include <cassert>

namespace {
#define CMD_LISTVARS "listvars"
#define CMD_SETVAR "set"
const char *KEY_CONFIG_KEYBINDINGS = "keybindings";
const char *KEY_CONFIG_CONTROLLERBINDINGS = "controllerbindings";
const char *KEY_CONFIG_JOYSTICKBINDINGS = "joystickbindings";
}

ConfigManager::ConfigManager() :
		_persister(nullptr), _bindingSpace(BINDINGS_UI), _bindingSpaceListener(nullptr) {
	memset(&_backendRenderer, 0, sizeof(_backendRenderer));
}

void ConfigManager::setBindingsSpace (BindingSpace bindingSpace)
{
	if (_bindingSpace == bindingSpace)
		return;

	if (_bindingSpaceListener)
		_bindingSpaceListener->resetKeyStates();
	// after the keys are reset, we can change the binding space
	_bindingSpace = bindingSpace;
}

void ConfigManager::init (IBindingSpaceListener *bindingSpaceListener, int argc, char **argv)
{
	_persister = new ConfigPersisterSQL();
	info(LOG_CONFIG, "init configmanager");

	_persister->init();

	_bindingSpaceListener = bindingSpaceListener;

	LUA lua;

	info(LOG_CONFIG, "load config lua file");
	if (!lua.load("config.lua")) {
		System.exit("could not load config", 1);
	}

	info(LOG_CONFIG, "load config values");
	getKeyValueMap(lua, _configVarMap, "settings");
	info(LOG_CONFIG, "load keybindings");
	getBindingMap(lua, _keybindings, KEY_CONFIG_KEYBINDINGS, KEYBOARD);
	info(LOG_CONFIG, "load controller bindings");
	getBindingMap(lua, _controllerBindings, KEY_CONFIG_CONTROLLERBINDINGS, CONTROLLER);
	info(LOG_CONFIG, "load joystick bindings");
	getBindingMap(lua, _joystickBindings, KEY_CONFIG_JOYSTICKBINDINGS, JOYSTICK);
	_language = getConfigValue(_configVarMap, "language", System.getLanguage());
	_joystick = getConfigValue(_configVarMap, "joystick");
	_showFPS = getConfigValue(_configVarMap, "showfps");
	_width = getConfigValue(_configVarMap, "width", "-1");
	_height = getConfigValue(_configVarMap, "height", "-1");
	_fullscreen = getConfigValue(_configVarMap, "fullscreen", "true");
	_soundEnabled = getConfigValue(_configVarMap, "sound");
	_port = getConfigValue(_configVarMap, "port", "4567");
	_debug = getConfigValue(_configVarMap, "debug", "false");
#ifdef NONETWORK
	_network = getConfigValue(_configVarMap, "network", "false");
#else
	_network = getConfigValue(_configVarMap, "network", "true");
#endif
	_vsync = getConfigValue(_configVarMap, "vsync", "true");
	_textureSize = getConfigValue(_configVarMap, "texturesize", "auto");
	_maxHitpoints = getConfigValue(_configVarMap, "maxhitpoints", "100");
	_damageThreshold = getConfigValue(_configVarMap, "damagethreshold", "0.3");
	_referenceTimeFactor = getConfigValue(_configVarMap, "referencetimefactor", "1.0");
	_fruitCollectDelayForANewLife = getConfigValue(_configVarMap, "fruitcollectdelayforanewlife", "15000");
	_amountOfFruitsForANewLife = getConfigValue(_configVarMap, "amountoffruitsforanewlife", "4");
	_fruitHitpoints = getConfigValue(_configVarMap, "fruithitpoints", "10");
	_npcFlyingSpeed = getConfigValue(_configVarMap, "npcflyingspeed", "4.0");
	_mode = getConfigValue(_configVarMap, "mode", "");
	_waterParticle = getConfigValue(_configVarMap, "waterparticle", "false", CV_READONLY);
	_shader = getConfigValue(_configVarMap, "shader", "false");
	_grabMouse = getConfigValue(_configVarMap, "grabmouse", "true");
	_soundEngine = getConfigValue(_configVarMap, "soundengine", "sdl");
	_particles = getConfigValue(_configVarMap, "particles", "0");
	_serverName = getConfigVar("servername", System.getCurrentUser());
	_name = getConfigVar("name", System.getCurrentUser());
	_amountOfFruitsForANewLife = getConfigValue(_configVarMap, "amountoffruitsforanewlife", "4");
	_debugui = getConfigVar("debugui", "false");
	getConfigVar("debugentity", "false", true);
	getConfigVar("debugui", "false", true);

	for (KeyValueMap::iterator i = _configVarMap.begin(); i != _configVarMap.end(); ++i) {
		getConfigVar(i->first, i->second, true);
	}

	std::vector<std::string> vars;
	_persister->getVars(vars);
	for (std::vector<std::string>::const_iterator i = vars.begin(); i != vars.end(); ++i) {
		getConfigVar(*i);
	}
	for (ConfigVarsMap::iterator i = _configVars.begin(); i != _configVars.end(); ++i) {
		info(LOG_CONFIG, "'" + i->first + "' with value: '" + i->second->getValue() + "'");
	}

	memset(&_debugRendererData, 0, sizeof(_debugRendererData));

	info(LOG_CONFIG, "mouse grab enabled: " + _grabMouse->getValue());
	info(LOG_CONFIG, "  joystick enabled: " + _joystick->getValue());
	info(LOG_CONFIG, "    shader enabled: " + _shader->getValue());
	info(LOG_CONFIG, "     sound enabled: " + _soundEnabled->getValue());
	info(LOG_CONFIG, "     debug enabled: " + _debug->getValue());

	CommandSystem::get().registerCommand(CMD_SETVAR, bindFunction(ConfigManager, setConfig));
	CommandSystem::get().registerCommand(CMD_LISTVARS, bindFunction(ConfigManager, listConfigVariables));

	for (int i = 0; i < argc; i++) {
		if (argv[i][0] != '-')
			continue;
		const std::string command = &argv[i][1];
		if (command != CMD_SETVAR)
			continue;
		if (i + 2 >= argc)
			continue;
		const std::string var = argv[i + 1];
		const std::string val = argv[i + 2];
		ConfigVarPtr p = getConfigVar(var);
		p->setValue(val);
		*argv[i] = *argv[i + 1] = *argv[i + 2] = '\0';
		i += 2;
	}
}

ConfigManager::~ConfigManager ()
{
	delete _persister;
}

ConfigManager& ConfigManager::get ()
{
	static ConfigManager _mgr;
	return _mgr;
}

std::string ConfigManager::getNameForKey (int key) const
{
	const SDL_Scancode scanCode = SDL_GetScancodeFromKey(key);
	return SDL_GetScancodeName(scanCode);
}

std::string ConfigManager::getNameForJoystickButton (int key) const
{
	return "JOY" + string::toString(key);
}

void ConfigManager::getKeyValueMap (LUA& lua, std::map<std::string, std::string>& map, const char *key)
{
	lua.getKeyValueMap(map, key);
}

void ConfigManager::getBindingMap (LUA& lua, std::map<std::string, std::string>* map, const char *key, BindingType type)
{
	lua.getGlobalKeyValue(key);

	while (lua.getNextKeyValue()) {
		const std::string id = lua.getKey();
		if (id.empty()) {
			lua.pop();
			continue;
		}

		lua_pushnil(lua.getState());

		std::map<std::string, std::string> strMap;
		while (lua_next(lua.getState(), -2) != 0) {
			const char *_key = lua_tostring(lua.getState(), -2);
			assert(_key);
			std::string _value;
			if (lua_isstring(lua.getState(), -1)) {
				_value = lua_tostring(lua.getState(), -1);
			} else if (lua_isnumber(lua.getState(), -1)) {
				_value = string::toString(lua_tonumber(lua.getState(), -1));
			} else if (lua_isboolean(lua.getState(), -1)) {
				_value = lua_toboolean(lua.getState(), -1) ? "true" : "false";
			}
			strMap[_key] = _value;
			lua_pop(lua.getState(), 1);
		}

		BindingSpace bindingSpace = BINDINGS_UI;
		if (id == "map")
			bindingSpace = BINDINGS_MAP;
		for (std::map<std::string, std::string>::const_iterator i = strMap.begin(); i != strMap.end(); ++i) {
			if (type == KEYBOARD) {
				map[bindingSpace][i->first] = i->second;
			} else if (type == JOYSTICK) {
				const std::string index = i->first.substr(3);
				map[bindingSpace][index] = i->second;
			} else if (type == CONTROLLER) {
				const SDL_GameControllerButton button = SDL_GameControllerGetButtonFromString(i->first.c_str());
				const char *buttonStr = SDL_GameControllerGetStringForButton(button);
				map[bindingSpace][buttonStr] = i->second;
			}
		}

		lua_pop(lua.getState(), 1);
	}
}

void ConfigManager::getBindingMap (LUA& lua, std::map<int, std::string>* map, const char *key, BindingType type)
{
	if (type == CONTROLLER)
		return;

	lua.getGlobalKeyValue(key);

	while (lua.getNextKeyValue()) {
		const std::string id = lua.getKey();
		if (id.empty()) {
			lua.pop();
			continue;
		}

		lua_pushnil(lua.getState());

		std::map<std::string, std::string> strMap;
		while (lua_next(lua.getState(), -2) != 0) {
			const char *_key = lua_tostring(lua.getState(), -2);
			assert(_key);
			std::string _value;
			if (lua_isstring(lua.getState(), -1)) {
				_value = lua_tostring(lua.getState(), -1);
			} else if (lua_isnumber(lua.getState(), -1)) {
				_value = string::toString(lua_tonumber(lua.getState(), -1));
			} else if (lua_isboolean(lua.getState(), -1)) {
				_value = lua_toboolean(lua.getState(), -1) ? "true" : "false";
			}
			strMap[_key] = _value;
			lua_pop(lua.getState(), 1);
		}

		BindingSpace bindingSpace = BINDINGS_UI;
		if (id == "map")
			bindingSpace = BINDINGS_MAP;
		for (std::map<std::string, std::string>::const_iterator i = strMap.begin(); i != strMap.end(); ++i) {
			if (type == KEYBOARD) {
				map[bindingSpace][mapKey(i->first)] = i->second;
			} else if (type == JOYSTICK) {
				const std::string index = i->first.substr(3);
				map[bindingSpace][string::toInt(index)] = i->second;
			}
		}

		lua_pop(lua.getState(), 1);
	}
}

void ConfigManager::autoComplete (const std::string& input, std::vector<std::string>& matches)
{
	const String tmp(input + "*");
	for (ConfigVarsMapConstIter i = _configVars.begin(); i != _configVars.end(); ++i) {
		if (!tmp.matches(i->first))
			continue;
		matches.push_back(i->first);
	}
}

void ConfigManager::listConfigVariables (const ICommand::Args& args)
{
	if (!args.empty()) {
		const String tmp(args[0] + "*");
		for (ConfigVarsMapConstIter i = _configVars.begin(); i != _configVars.end(); ++i) {
			if (!tmp.matches(i->first))
				continue;
			const ConfigVarPtr& c = i->second;
			info(LOG_CONFIG, c->getName() + " " + c->getValue());
		}
	} else {
		for (ConfigVarsMapConstIter i = _configVars.begin(); i != _configVars.end(); ++i) {
			const ConfigVarPtr& c = i->second;
			info(LOG_CONFIG, c->getName() + " " + c->getValue());
		}
	}
}

void ConfigManager::setConfig (const ICommand::Args& args)
{
	if (args.size() != 2) {
		error(LOG_CONFIG, "parameters: the config key");
		return;
	}

	info(LOG_CONFIG, "set " + args[0] + " to " + args[1]);

	ConfigVarPtr p = getConfigVar(args[0]);
	p->setValue(args[1]);
}

int ConfigManager::mapModifier (const std::string& name)
{
	const std::string converted = string::replaceAll(name, "_", " ");
	const SDL_Keycode keycode = SDL_GetKeyFromName(converted.c_str());
	if (keycode & KMOD_SHIFT) {
		return KMOD_SHIFT;
	} else if (keycode & KMOD_ALT) {
		return KMOD_ALT;
	} else if (keycode & KMOD_CTRL) {
		return KMOD_CTRL;
	}
	return KMOD_NONE;
}

int ConfigManager::mapKey (const std::string& name)
{
	const std::string converted = string::replaceAll(name, "_", " ");
	const SDL_Keycode keycode = SDL_GetKeyFromName(converted.c_str());
	if (keycode == 0)
		return -1;
	return keycode;
}

void ConfigManager::shutdown ()
{
	info(LOG_CONFIG, "shutdown config manager");
	_persister->save(_configVars);
}

ConfigVarPtr ConfigManager::getConfigVar (const std::string& name, const std::string& value, bool create, unsigned int flags)
{
	ConfigVarsMapIter i = _configVars.find(name);
	if (i == _configVars.end()) {
		if (!create)
			return ConfigVarPtr();
		std::string v = _persister->getValue(name);
		if (v.empty())
			v = value;
		ConfigVarPtr p(new ConfigVar(name, v, flags));
		_configVars[name] = p;
		return p;
	}
	return i->second;
}

ConfigVarPtr ConfigManager::getConfigValue (KeyValueMap &map, const std::string& name, const std::string& defaultValue, unsigned int flags)
{
	const std::string& savedValue = _persister->getValue(name);
	std::string val = savedValue;
	if (val.empty()) {
		KeyValueMap::iterator i = map.find(name);
		if (i != map.end()) {
			val = i->second;
			map.erase(i);
		}
	}
	if (val.empty())
		val = defaultValue;

	if (!savedValue.empty())
		info(LOG_CONFIG, "use stored value '" + val + "' for key '" + name + "'");
	else
		info(LOG_CONFIG, "use value '" + val + "' for key '" + name + "'");
	const ConfigVarPtr& p = getConfigVar(name, val, true, flags);
	return p;
}
