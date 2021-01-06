# X330 FHD/2K Linux brightness adjustment
## agan FHD/2K kit brightness adjustment

GPL licensed

A work-in-progress.
Planning to implement this with a simple script and install as a systemd service. As such, other systemd-less init distros will not be supported. Then again if you're running without systemd you'll know what you're doing ;) 

Programme is written using native USB HID library so no driver is needed. All modern distros should be able to compile normally (macOS probably works as well, not sure how well it runs though). 

Simple explanation:
Programme interfaces with the onboard USB HID device. Commands are sent to the USB HID device to adjust brightness. 

一个非常简单的亮度调节程序，基于系统自带library。只在linux测试，黑苹果应该也可以，但本人没测试过不知道能不能用。以后还会加入systemd自动生成脚本，以及inotify来实现快捷键调节。
使用非常简单：

To use 使用:
```C
make
```
```bash
./script //change brightness to 15 (max) 亮度调至最高
./script 0 //change brightness to 0 (lowest brightness level) 亮度调至0（最低亮度）
./script 15 //change brightness to 15 (highest brightness level) 亮度调至15（最高亮度）
```

To-do:
* Implement inotify to listen for changes in brightness
* Write an installation script to install this as a systemd service
