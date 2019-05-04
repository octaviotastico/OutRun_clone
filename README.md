# OutRun    

OutRun was a videogame back in the 80's for Sega console.    
I wanted to draw stuff with C, and I found the [SFML Library], and I had to try it.    
I was a lot of fun, and I hope you like the result!    

### How to compile:    

First of all, you need to download the SFML Library.    

To do that from shell, you have to:    
`sudo apt-get install libsfml-dev`    
`sudo apt-get update`    
`sudo apt upgrade`    

Then, clone the repo if you haven't done that:    
`git clone https://github.com/octaviotastico/outrun_test.git`    

And finally, open the new folder and run:    
`g++ -o a drive_away.cpp -lsfml-graphics -lsfml-window -lsfml-system`    
`./a`

### Demo:

![gif](https://i.giphy.com/media/MeJEnrJZG4JladlFcp/giphy.webp)    

**Note:**    
You can **move** with **Left** and **Right** arrow keys    

[SFML Library]: https://www.sfml-dev.org/learn.php
