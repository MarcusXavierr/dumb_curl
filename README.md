## Dumb Curl

A simple copy of curl, with some extra sauce 😎


### Building
This project depends on libcurl and SDL. So, please install theses dependencies

macOS
```bash
brew update
brew install sdl2
brew install sdl2_mixer
brew install curl
```
Ubuntu
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install curl libcurl4-openssl-dev
```
Fedora
```bash
sudo dnf update
sudo dnf install SDL2-devel
sudo dnf install SDL2_mixer-devel
sudo dnf install curl libcurl-devel
```

My makefile uses `clang` as the compiler, if your prefer to use gcc, change this on the first line of the makefile, the `CC=clang`.

After that, just run 
```bash
make
```
And then run 
```
./dumbcurl https://example.com
```
