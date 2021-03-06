# GTK UI for robo-football
Simple [GTK](https://www.gtk.org/) + [Cairo](https://www.cairographics.org/) user interface for tracking robo-footballers.

## Ubuntu
Required utilities:
```
$ sudo apt-get -y install git gcc g++ cmake build-essential libgtk-3-dev
```

Configure and build repository:
```
$ mkdir -p build && cd build && cmake .. && cd ..
$ cmake --build build --config Release
```

## macOS
Open terminal and install:
```
$ brew install pkg-config
$ brew install gtk+3
```

Set project to use with Xcode:
```
$ cmake . -G Xcode
```
If you get `--   No package 'gtk+-3.0' found`, set:
```
$ export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
```

Choose `roboGTK` target and build project.

## Windows
Download and install [MSYS2](https://www.msys2.org/), type to shell:
```
$ pacman -S git gcc make cmake pkg-config mingw-w64-x86_64-gtk3
$ export PKG_CONFIG_PATH=/mingw64/lib/pkgconfig
```

Open `Control Panel` -> `Advanced system settings` -> `Environment Variables`, select `PATH` and add:
```
C:\msys64\mingw64\bin
C:\msys64\usr\bin
```

Build repository by the same commands as Ubuntu.
