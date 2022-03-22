# X330 X230 agan FHD/2K Linux brightness adjustment 
# X330 X230 FHD/2K 阿甘套件 亮度调节linux程序

GPL licensed

A work-in-progress.

Programme is written using native USB HID library available since probably since the inception of the Linux kernel so no driver is needed. All modern distros should be able to compile normally (macOS probably works as well, not sure how well it runs though). 

Simple explanation:
Programme interfaces with the onboard USB HID device. Commands are sent to the USB HID device to adjust brightness. Programme is fully commented.

一个非常简单的亮度调节程序，基于系统自带USB library。只在linux测试，黑苹果应该也可以，但本人没测试过不知道能不能用。以后还会加入systemd自动生成脚本，以及inotify来实现快捷键调节。
使用非常简单：

Compile it first先编译:
```C
make
```
Run it运行:
```bash
sudo ./script //change brightness to 15 (max) 亮度调至最高
sudo ./script 0 //change brightness to 0 (lowest brightness level) 亮度调至0（最低亮度）
sudo ./script 15 //change brightness to 15 (highest brightness level) 亮度调至15（最高亮度）
```

To-do:
* Implement this with ACPI calls so the script can be as portable as possible.
