# hyev
hyprland event trigger, used for triggering custom scripts with a animation sounds example



https://github.com/DreamMaoMao/hyev/assets/30348075/f84ae9a1-7378-44ec-be10-5cbb6556d438



# install
```
git clone https://github.com/DreamMaoMao/hyev.git
cd hyev
bash install.sh
```

# animation sounds example(animation sounds)
## copy sound file
```
cd hyev
cp ./sound -r /home/wrq/.config/hypr/
```

## edit hyprland.conf
```
plugin = /usr/lib/libhyev.so

plugin {
    hyev {
        open_window = play -v 0.4 /home/wrq/.config/hypr/sound/add.wav 
        close_window = play -v 0.4 /home/wrq/.config/hypr/sound/remove.wav  
        change_workspace = play -v 0.3 /home/wrq/.config/hypr/sound/change_workspace.wav 
        fullscreen_on = play -v 0.4 /home/wrq/.config/hypr/sound/fullscreen.wav 
        fullscreen_off = play -v 0.4 /home/wrq/.config/hypr/sound/tile.wav 
        focus_window = ""
    }
}
```
