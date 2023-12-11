# hyev
hyprland event trigger, used for triggering custom scripts

# install
```
git clone https://github.com/DreamMaoMao/hyev.git
cd hyev
bash install.sh
```

# config example(animation sounds)
```
plugin = /usr/lib/libhyev.so

plugin {
    hyev {
        open_window = play -v 0.4 /home/wrq/.config/hypr/sound/add.wav 
        close_window = play -v 0.4 /home/wrq/.config/hypr/sound/remove.wav  
        change_workspace = play -v 0.4 /home/wrq/.config/hypr/sound/change_workspace.wav 
        fullscreen_on = play -v 0.4 /home/wrq/.config/hypr/sound/fullscreen.wav 
        fullscreen_off = play -v 0.4 /home/wrq/.config/hypr/sound/tile.wav 
        focus_window = ""
    }
}
```
