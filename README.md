# snake

Classic snake game written in C using ncurses library. It was made for a programming class.
Try to eat the Apple by changing snakes direction using WASD-keys. If you eat the Apple you're snake grows longer. 
Game ends if you hit the walls or if the snake hits itself. Try to get as long as you can!

Click the image below to see a demo video

[![ScreenShot](http://img.youtube.com/vi/adk_jzfPVnA/0.jpg)](https://youtu.be/adk_jzfPVnA)

# compiling

Mac:

Mac OS should have ncurses headers already so this should work:
```
gcc snake_v3.c -o snake -lncurses
```

Linux:

If your linux distro does not have the headers you need to get them first:
```
sudo apt-get install libncurses5-dev
```
Then you should be able to compile with:
```
gcc snake_v3.c -o snake -lncurses
```
