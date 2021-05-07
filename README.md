# What's this

Call Wireshark libraries in my own code to understand it.

See [my articles](https://www.yuque.com/zzqcn/opensource) about Wireshark to get more information.

# Build

This project uses [Meson build system](https://mesonbuild.com/).

First you should get Wireshark code and build it, see [my article](https://www.yuque.com/zzqcn/opensource/pylrcy) for details. Second set your Wireshark source and build directory in `meson_options.txt`.

**NOTE: I have changed some wireshark code for some reason, e.g. calling some API which was NOT exported by libwireshark.so. So you should use [Wireshark code in my branch](https://github.com/zzqcn/wireshark/tree/zzqcn) to build this project successfully.**

Then run commands below to build:
```c
$ meson <YOUR BUILD DIR>
$ cd <YOUR BUILD DIR>
$ ninja
```

# Run

After building, you can run executables in your build directory, for example:
```
$ cd <YOUR BUIILD DIR>
$ cd hello_wireshark/
$ LD_LIBRARY_PATH=/home/zzq/dev/wireshark_build/run ./hello_wireshark                        
hello wireshark 3.5.0
```

Here `/home/zzq/dev/wireshark_build` is my Wireshark build directory, and because it is not in system PATH so I set the `LD_LIBRARY_PATH` to that.