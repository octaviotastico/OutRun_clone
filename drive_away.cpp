/*

Used library:
- SFML: https://www.sfml-dev.org/documentation/2.5.1/

Compile:
- g++ -o a drive_away.cpp -lsfml-graphics -lsfml-window -lsfml-system

*/

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

#define fore(i, s, e) for(int i = s; i < e; i++)
#define pb push_back

using namespace std;
using namespace sf;

// Screen Variables
int width = 1024;
int height = 768;

// Screen
RenderWindow drive(VideoMode(width, height), "where r u");

int main() {

  // 60 FPS broder
  drive.setFramerateLimit(60);

  // All textures and sprites
  Texture palm, car, background;
  Sprite palm_object, car_object;

  // Load palm texture and creates a sprite
  palm.loadFromFile("images/palm.png");
  palm_object.setTexture(palm);

  // Load car texture and creates a sprite
  car.loadFromFile("images/car.png");
  car_object.setTexture(car);

  // Load background texture and creates a sprite
  background.loadFromFile("images/bg.jpeg");
  background.setRepeated(true);
  Sprite sBackground(background);
  sBackground.setTextureRect(IntRect(0, 300, 5000, 411));
  sBackground.setPosition(-2000, 0);

  return 0;
}
