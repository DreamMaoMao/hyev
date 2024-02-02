# hyev
a hyprland plugin for Animation sound


https://github.com/DreamMaoMao/hyev/assets/30348075/f84ae9a1-7378-44ec-be10-5cbb6556d438


# Installation (Recommended)
```
sudo pacman -S sox boost boost-libs
hyprpm add https://github.com/DreamMaoMao/hyev
hyprpm enable hyev
```
# Installation (Old)
```
sudo pacman -S sox boost boost-libs
git clone https://github.com/DreamMaoMao/hyev.git
cd hyev
bash install.sh
```

# Example sounds
## Copy sound files
```
cd hyev
cp ./sound -r /home/wrq/.config/hypr/
```

## Edit hyprland.conf
```
#plugin = /usr/lib/libhyev.so #Uncomment if installed with old method

plugin {
    hyev {
        open_window = play -v 0.4 /home/wrq/.config/hypr/sound/add.wav 
        close_window = play -v 0.4 /home/wrq/.config/hypr/sound/remove.wav  
        change_workspace = play -v 0.3 /home/wrq/.config/hypr/sound/change_workspace.wav 
        fullscreen_on = play -v 0.4 /home/wrq/.config/hypr/sound/fullscreen.wav 
        fullscreen_off = play -v 0.4 /home/wrq/.config/hypr/sound/tile.wav 
    }
}
```
