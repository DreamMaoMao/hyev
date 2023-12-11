
#include <hyprland/src/Compositor.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include "globals.hpp"

uint64_t shell_execr(std::string args) {
    hyev_log(LOG, "Executing {}", args);

    int socket[2];
    if (pipe(socket) != 0) {
        Debug::log(LOG, "Unable to create pipe for fork");
    }

    pid_t child, grandchild;
    child = fork();
    if (child < 0) {
        close(socket[0]);
        close(socket[1]);
        Debug::log(LOG, "Fail to create the first fork");
        return 0;
    }
    if (child == 0) {
        // run in child

        sigset_t set;
        sigemptyset(&set);
        sigprocmask(SIG_SETMASK, &set, NULL);

        grandchild = fork();
        if (grandchild == 0) {
            // run in grandchild
            close(socket[0]);
            close(socket[1]);
            execl("/bin/sh", "/bin/sh", "-c", args.c_str(), nullptr);
            // exit grandchild
            _exit(0);
        }
        close(socket[0]);
        write(socket[1], &grandchild, sizeof(grandchild));
        close(socket[1]);
        // exit child
        _exit(0);
    }
    // run in parent
    close(socket[1]);
    read(socket[0], &grandchild, sizeof(grandchild));
    close(socket[0]);
    // clear child and leave child to init
    waitpid(child, NULL, 0);
    if (child < 0) {
        Debug::log(LOG, "Fail to create the second fork");
        return 0;
    }

    hyev_log(LOG, "Process Created with pid {}", grandchild);

    return grandchild;
}


void openWindowHook(void* self, SCallbackInfo &info, std::any data) {
    auto* const pWindow = std::any_cast<CWindow*>(data);
    hyev_log(LOG,"openWindowHook trigger command:{}",g_open_window);
    if (pWindow->m_bIsX11 && (pWindow->m_bX11DoesntWantBorders || pWindow->m_iX11Type == 2))
        return; // not a x11 toplevel
    shell_execr(g_open_window);
}

void closeWindowHook(void* self, SCallbackInfo &info, std::any data) {
    auto* const pWindow = std::any_cast<CWindow*>(data);
    hyev_log(LOG,"closeWindowHook trigger command:{}",g_close_window);
    if (pWindow->m_bIsX11 && (pWindow->m_bX11DoesntWantBorders || pWindow->m_iX11Type == 2))
        return; // not a x11 toplevel
    shell_execr(g_close_window);
}

void activeWindowHook(void* self, SCallbackInfo &info, std::any data) {
    auto* const pWindow = std::any_cast<CWindow*>(data);
    hyev_log(LOG,"activeWindowHook trigger command:{}",g_focus_window);
    if(!pWindow)
        return;
    if (pWindow->m_bIsX11 && (pWindow->m_bX11DoesntWantBorders || pWindow->m_iX11Type == 2))
        return; // not a x11 toplevel
    shell_execr(g_focus_window);
}

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
    auto curren_layout = g_pLayoutManager->getCurrentLayout();
    
    hyev_log(LOG,"changeWorkspaceHook trigger command:{}",g_change_workspace);
    shell_execr(g_change_workspace);
}


void registerGlobalEventHook()
{

  HyprlandAPI::registerCallbackDynamic(PHANDLE, "openWindow", [&](void* self, SCallbackInfo& info, std::any data) { openWindowHook(self, info, data); });
  HyprlandAPI::registerCallbackDynamic(PHANDLE, "closeWindow", [&](void* self, SCallbackInfo& info, std::any data) { closeWindowHook(self, info, data); });
  HyprlandAPI::registerCallbackDynamic(PHANDLE, "workspace", [&](void* self, SCallbackInfo& info, std::any data) { changeWorkspaceHook(self, info, data); });
  HyprlandAPI::registerCallbackDynamic(PHANDLE, "activeWindow", [&](void* self, SCallbackInfo& info, std::any data) { activeWindowHook(self, info, data); });
  HyprlandAPI::registerCallbackDynamic(PHANDLE, "fullscreen", [&](void* self, SCallbackInfo& info, std::any data) { fullscreenHook(self, info, data); });

}
