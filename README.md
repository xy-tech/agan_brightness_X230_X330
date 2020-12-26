# X330 FHD/2K brightness adjustment
## agan FHD/2K kit brightness adjustment

A work-in-progress.
Planning to implement this with a simple script and install as a systemd service. As such, other systemd-less init distros will not be supported. Then again if you're running without systemd you'll know what you're doing ;) 

Programme is written using native USB HID library so no driver is needed. All modern distros should be able to compile and generate the binary OOTB.

To run:
```C
make
```
```bash
./script
```

To-do:
* Implement inotify to listen for changes in brightness
* Write an installation script to install this as a systemd service
