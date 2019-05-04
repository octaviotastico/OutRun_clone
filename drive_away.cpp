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

  // Set car size and position
  car_object.setPosition(355, 400);
  car_object.setScale(2.f, 2.f);

  // Everithing in screen
  vector<Line> scene;

  // Pre-render all stuff in a vector to display it later.
  fore(i, 0, draw_distance) {
    
    Line line;
    line.z = i * segment;

    // Movement in X axes
    if (i > 300 && i < 700) line.curve = 0.5;
    if (i > 700 && i < 1100) line.curve = -0.5;
    if (i > 1500 && i < 1600) line.curve = 0.5;
    if (i > 1800 && i < 2000) line.curve = -0.5;
    
    // Movement in Y axes
    // if (i > 750) line.y = sin(i / 30.0) * 1500;

    // Drawing palms
    if (i % 30 == 0) { line.spriteX = +1.3; line.sprite = palm_object; }
    if (i % 31 == 0) { line.spriteX = -2.0; line.sprite = palm_object; }

    // Put what's calculated in vector
    scene.pb(line);
  
  }

  return 0;
}
