# LVGL on Linux

Raspberry Pi : Model 3B running Rasberry PI OS (64)   
Display : Waveshare 2.8" 480x640 with Capacitive Touch


## DISPLAY SETUP
- Comment out `dtoverlay=vc4-fkms-V3D` in `/boot/config.txt`
- Add the following TFT/Touch configuration at the end of `/boot/config.txt`
```
gpio=0-9=a2
gpio=12-17=a2
gpio=20-25=a2
dtoverlay=dpi24
enable_dpi_lcd=1
display_default_lcd=1
extra_transpose_buffer=2
dpi_group=2
dpi_mode=87
dpi_output_format=0x7F216
hdmi_timings=480 0 26 16 10 640 0 25 10 15 0 0 0 60 0 32000000 1
dtoverlay=waveshare-28dpi-3b-4b
dtoverlay=waveshare-28dpi-3b
dtoverlay=waveshare-28dpi-4b
```
- Add the following for Display rotation in `/boot/config.txt`   
`display_rotate=1 #1：90；2: 180； 3: 270`


- Download and Copy 3 overlay files inside `/boot/overlays` folder
https://www.waveshare.com/wiki/File:28DPIB_DTBO.zip

## USING SDL
This works if you have Raspberry PI OS with desktop running
- Install SDL   
`sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev`
- Clone LVGL Simulator repo    
`git clone --recursive https://github.com/littlevgl/pc_simulator.git`
- Install cmake    
`sudo apt install cmake`   
- Compile and build   
`cd pc_simulator/ && mkdir build && cd build && cmake .. && make -j4`
- Run the Application built using   
`DISPLAY=:0 ./../bin/main`
- To make your app FULL SCREEN, add below line inside `lv_drv_conf.h`   
`#define SDL_FULLSCREEN  1`

## USING FRAME BUFFER /dev/fb0 
(WORK IN PROGRESS)   


### TASKS
- [ ] LVGL 8.x display  
- [ ] Touch,Mouse and Keyboard input  
- [ ] Document the sample including base setup and display setup  


### NOTE
When cloning this repository, make sure to download submodules otherwise you will be missing required components.   
`git submodule update --init --recursive`

##### References
Frame Buffer method based on (this)(https://blog.lvgl.io/2018-01-03/linux_fb) blog post.
