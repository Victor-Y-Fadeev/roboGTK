# GTK UI for robo-football

Simple GTK user interface for tracking robo-footballers.

## Build

Required utilities:
```
$ sudo apt-get -y install git gcc g++ cmake build-essential libgtk-3-dev
```

Configure and build repository:
```
$ mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cd ..
$ cmake --build build --config Release
```
