/*

Used library:
- SFML: https://www.sfml-dev.org/documentation/2.5.1/

Compile:
- g++ -o a drive_away.cpp -lsfml-graphics -lsfml-window -lsfml-system

Execute:
- ./a

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

// Road Variables
int line_size = 3;
int road_width = 2000;
int segment = 200;

// Camera Variables
int cam_height = 1500;
int draw_distance = 2000;
float cam_depth = 1.0;

// Car Variables
int car_position = 0;
int car_speed = 200;
float car_x_axes = 0;

// Colors
Color black = Color(0, 0, 0);
Color white = Color(255, 255, 255);
Color dark_green = Color(0, 154, 0);
Color brigt_green = Color(16, 200, 16);
Color dark_gray = Color(107, 107, 107);
Color bright_gray = Color(105, 105, 105);

// Screen
RenderWindow drive(VideoMode(width, height), "where r u");

// Draw the next square
void drawQuad(Color c, int x1, int y1, int w1, int x2, int y2, int w2) {
    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1 - w1, y1));
    shape.setPoint(1, Vector2f(x2 - w2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    drive.draw(shape);
}

struct Line {
  float x, y, z; //3d center of line
  float X, Y, W; //screen coord
  float curve, spriteX, clip, scale;
  Sprite sprite;

  Line() { spriteX = curve = x = y = z = 0; }

  void project(int camX, int camY, int camZ) {
    scale = cam_depth / (z - camZ);
    X = (1 + scale * (x - camX)) * width / 2;
    Y = (1 - scale * (y - camY)) * height / 2;
    W = scale * road_width  * width / 2;
  }

  void drawSprite(RenderWindow &drive) {
    Sprite s = sprite;
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = X + scale * spriteX * width/2;
    float destY = Y + 4;
    float destW  = w * W / 266;
    float destH  = h * W / 266;

    destX += destW * spriteX; //offsetX
    destY += destH * (-1);    //offsetY

    float clipH = destY+destH-clip;
    if (clipH < 0) clipH = 0;

    if (clipH >= destH) return;
    s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
    s.setScale(destW / w, destH / h);
    s.setPosition(destX, destY);
    drive.draw(s);
  }

};


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

  // All elements in scene
  int N = scene.size();
  
  // While user doesn't close screen... Loop everything prerendered indefinitely
  while (drive.isOpen()) {
    
    Event e;
    while (drive.pollEvent(e)) {
        if (e.type == Event::Closed)
            drive.close();
    }

    // Turn left or right between the bounds, and bracking
    if (Keyboard::isKeyPressed(Keyboard::Right) && car_x_axes < 2) car_x_axes += 0.1;
    if (Keyboard::isKeyPressed(Keyboard::Left) && car_x_axes > -2) car_x_axes -= 0.1;
    if (Keyboard::isKeyPressed(Keyboard::Down)) car_speed = 100;
    if (car_x_axes < -1 or car_x_axes > 1) car_speed = 100;

    // Move forward depending on speed
    car_position += car_speed;

    // Load next segment
    while (car_position >= N * segment) car_position -= N * segment;
    while (car_position < 0) car_position += N * segment;

    // Restart everything
    drive.clear();
    drive.draw(sBackground);

    int startPos = car_position / segment;

    // Background movement
    if (car_speed > 0) sBackground.move(-scene[startPos].curve * 0.2, 0);
    if (car_speed < 0) sBackground.move( scene[startPos].curve * 0.2, 0);

    int maxy = height;
    float x = 0, dx = 0;

    // Display everything pre-rendered
    fore(i, startPos, startPos + 500) {
      Line &l = scene[i % N];
      l.project(car_x_axes * road_width - x, cam_height, startPos * segment - (i >= N ? N * segment : 0));
      x += dx;
      dx += l.curve;

      l.clip = maxy;
      if (l.Y >= maxy) continue;
      maxy = l.Y;

      Color grass  = (i / line_size) % 2 ? brigt_green : dark_green;
      Color rumble = (i / line_size) % 2 ? white : black;
      Color road   = (i / line_size) % 2 ? bright_gray : dark_gray;

      Line p = scene[(i - 1) % N];

      drawQuad(grass, 0, p.Y, width, 0, l.Y, width);
      drawQuad(rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W*1.2);
      drawQuad(road,  p.X, p.Y, p.W, l.X, l.Y, l.W);
    }

    // Draw car in middle of the screen
    drive.draw(car_object);

    // Draw all things in scene
    fore(i, 0, startPos + 500)
      scene[i % N].drawSprite(drive);
    
    // Set car speed back to normal afer bracking
    car_speed = 200;

    // Put everything in window and clear everything
    drive.display();
    scene.clear();
  }
  return 0;
}
