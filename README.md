# LVGL for frame buffer device (WORK IN PROGRESS)

LVGL configured to work with /dev/fb0 on Linux.   
Raspberry Pi : Model 3B  
Display : Waveshare 2.8" 640x480 with Capacitive Touch


## SETUP
- Install cmake `sudo apt install cmake`
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



## TASKS
- [ ] LVGL 8.x display  
- [ ] Touch,Mouse and Keyboard input  
- [ ] Document the sample including base setup and display setup  

When cloning this repository, also make sure to download submodules otherwise you will be missing key components.   
`git submodule update --init --recursive`

Based on blog here :
https://blog.lvgl.io/2018-01-03/linux_fb
