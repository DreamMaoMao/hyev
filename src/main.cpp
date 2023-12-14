
#include "dispatchers.hpp"
#include "globaleventhook.hpp"

APICALL EXPORT std::string PLUGIN_API_VERSION() { return HYPRLAND_API_VERSION; }

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle)
{
	PHANDLE = handle;

#define CONF(NAME, TYPE, VALUE) \
	HyprlandAPI::addConfigValue(PHANDLE, "plugin:hyev:" NAME, SConfigValue{.TYPE##Value = VALUE})
	CONF("open_window", str, "echo hycov > /dev/null");
	CONF("close_window", str, "echo hycov > /dev/null");
	CONF("change_workspace", str, "echo hycov > /dev/null");
	// CONF("focus_window", str, "echo hycov > /dev/null");
	CONF("fullscreen_on", str, "echo hycov > /dev/null");
	CONF("fullscreen_off", str, "echo hycov > /dev/null");
#undef CONF

	std::string *configLayoutName = &HyprlandAPI::getConfigValue(PHANDLE, "general:layout")->strValue;
	g_default_layout_name = *configLayoutName;

	static const auto* pOpen_window_config =
	    &HyprlandAPI::getConfigValue(PHANDLE, "plugin:hyev:open_window")->strValue;
	static const auto* pClose_window_config =
	    &HyprlandAPI::getConfigValue(PHANDLE, "plugin:hyev:close_window")->strValue;
	static const auto* pChange_workspace_config =
	    &HyprlandAPI::getConfigValue(PHANDLE, "plugin:hyev:change_workspace")->strValue;
	static const auto* pFullscreen_on_config =
	    &HyprlandAPI::getConfigValue(PHANDLE, "plugin:hyev:fullscreen_on")->strValue;
	static const auto* pFullscreen_off_config =
	    &HyprlandAPI::getConfigValue(PHANDLE, "plugin:hyev:fullscreen_off")->strValue;
	// static const auto* pFocus_window_config =
	//     &HyprlandAPI::getConfigValue(PHANDLE, "plugin:hyev:focus_window")->strValue;


	g_open_window = *pOpen_window_config;
	g_close_window = *pClose_window_config;
	g_change_workspace = *pChange_workspace_config;
	g_fullscreen_on = *pFullscreen_on_config;
	g_fullscreen_off = *pFullscreen_off_config;
	// g_focus_window = *pFocus_window_config;


	registerGlobalEventHook();
	registerDispatchers();
	
	return {"hyev", "hyprland event trigger", "DreamMaoMao", "0.1"};
}

APICALL EXPORT void PLUGIN_EXIT() {}
