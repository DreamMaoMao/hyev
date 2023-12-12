
#include "globaleventhook.hpp"
#include <hyprland/src/SharedDefs.hpp>

void shell_execr(std::string args) {
    g_pKeybindManager->spawn(args);
}


void openWindowHook(void* self, SCallbackInfo &info, std::any data) {
    auto* const pWindow = std::any_cast<CWindow*>(data);
    if (pWindow->m_bIsX11 && (pWindow->m_bX11DoesntWantBorders || pWindow->m_iX11Type == 2))
        return; // not a toplevel
    hyev_log(LOG,"openWindowHook trigger command:{}",g_open_window);
    shell_execr(g_open_window);
}

void closeWindowHook(void* self, SCallbackInfo &info, std::any data) {
    auto* const pWindow = std::any_cast<CWindow*>(data);
    if (pWindow->m_bIsX11 && (pWindow->m_bX11DoesntWantBorders || pWindow->m_iX11Type == 2))
        return; // not a toplevel
    hyev_log(LOG,"closeWindowHook trigger command:{}",g_close_window);
    shell_execr(g_close_window);
}

// void activeWindowHook(void* self, SCallbackInfo &info, std::any data) {
//     auto* const pWindow = std::any_cast<CWindow*>(data);
//     if(!pWindow)
//         return;
//     if (pWindow->m_bIsX11 && (pWindow->m_bX11DoesntWantBorders || pWindow->m_iX11Type == 2))
//         return; // not a toplevel
//     hyev_log(LOG,"activeWindowHook trigger command:{}",g_focus_window);
//     shell_execr(g_focus_window);
// }

void fullscreenHook(void* self, SCallbackInfo &info, std::any data) {
    auto* const pWindow = std::any_cast<CWindow*>(data);
    if(!pWindow) {
        return;
    }
    if(pWindow->m_bIsFullscreen) {
        hyev_log(LOG,"fullscreenHook trigger command:{}",g_fullscreen_off);
        shell_execr(g_fullscreen_off);
    } else {
        hyev_log(LOG,"fullscreenHook trigger command:{}",g_fullscreen_on);
        shell_execr(g_fullscreen_on);        
    }
}


void changeWorkspaceHook(void* self, SCallbackInfo &info, std::any data) {
    auto curren_layout_name = g_pLayoutManager->getCurrentLayout()->getLayoutName();
    if(!boost::iequals(curren_layout_name,g_default_layout_name)) {
        return;
    }
    hyev_log(LOG,"changeWorkspaceHook trigger command:{}",g_change_workspace);
    shell_execr(g_change_workspace);
}


void registerGlobalEventHook()
{

    HyprlandAPI::registerCallbackDynamic(PHANDLE, "openWindow", [&](void* self, SCallbackInfo& info, std::any data) { openWindowHook(self, info, data); });
    HyprlandAPI::registerCallbackDynamic(PHANDLE, "closeWindow", [&](void* self, SCallbackInfo& info, std::any data) { closeWindowHook(self, info, data); });
    HyprlandAPI::registerCallbackDynamic(PHANDLE, "workspace", [&](void* self, SCallbackInfo& info, std::any data) { changeWorkspaceHook(self, info, data); });
    HyprlandAPI::registerCallbackDynamic(PHANDLE, "fullscreen", [&](void* self, SCallbackInfo& info, std::any data) { fullscreenHook(self, info, data); });
    // HyprlandAPI::registerCallbackDynamic(PHANDLE, "activeWindow", [&](void* self, SCallbackInfo& info, std::any data) { activeWindowHook(self, info, data); });

}
