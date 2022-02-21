# OpenGL Boilerplate

Install these libraries (instructions for ubuntu):

```
sudo apt-get update
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt-get install libfreetype-dev libfreetype6 libfreetype6-dev
```
Change the absolute paths used in the project.
If you are using VSCode, press `Ctrl+Shift+I`. search for '/home/zed/Desktop/Study/Computer Graphics/Assignment 1' and replace with the directory structure on your setup.

Instructions to test:

(Delete build if already exists)

```
mkdir build
cd build
cmake ..
make -j
```
