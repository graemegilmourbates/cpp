/*
  Author: Graeme Bates
  Date: 9/2/10
  Title: Game of Life
*/
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
using namespace std;

bool DEBUG = true;

int HEIGHT;
int WIDTH;

void log(string message){
    if(DEBUG){
      cout << message << endl;
    }
}

//display frame
void displayWorld(int **world, int height=HEIGHT, int width=WIDTH){
  system("clear");
  int x = 0;
  int y = 0;
  while(y < height){
    if(y == 0){
      int i = 0;
      cout << "  ";
      while(i < width){
        cout << " " + to_string(i);
        if(i < 10){ cout << " "; }
        i++;
      }
      cout << endl;
    }
    if(y < 10){
      cout << " ";
    }
    cout << y;
    while(x < width){
      if (world[y][x] == 0){
        cout << "   ";
      } else {
        cout << " • ";
      }
      x++;
    }
    cout << endl;
    x = 0;
    y++;
  }
}

//Set up
int** initWorld(int height=HEIGHT, int width=WIDTH){
  int **world;
  world = new int *[height];
  int x = 0;
  int y = 0;
  while(y < height){
    world[y] = new int[width];
    while(x < width){
      world[y][x] = 0;
      x++;
    }
    x = 0;
    y++;
  }
  return world;
}

//check cell
bool isCellAlive(int **world, int x, int y){
  if (world[y][x] == 1){
    return true;
  }
  return false;
}

//check above
bool isAboveAlive(int **world, int x, int y){
  if(y > 0){
    if(isCellAlive(world, x, y-1)){ return true; }
  }
  return false;
}
//below
bool isBelowAlive(int **world, int x, int y){
  if((y+1) < HEIGHT){
    if(isCellAlive(world, x, y+1)){ return true; }
  }
  return false;
}
//right
bool isRightAlive(int **world, int x, int y){
  if((x+1) < WIDTH){
    if(isCellAlive(world, x+1, y)){ return true; }
  }
  return false;
}
//left
bool isLeftAlive(int **world, int x, int y){
  if(x > 0){
    if(isCellAlive(world, x-1, y)){ return true; }
  }
  return false;
}

//top left
bool isTopLeftAlive(int **world, int x, int y){
  if(x > 0 && y > 0 ){
    if(isCellAlive(world, x-1, y-1)){ return true; }
  }
  return false;
}
//top right
bool isTopRightAlive(int **world, int x, int y){
  if(y > 0 && (x+1) < WIDTH){
    if(isCellAlive(world, x+1, y-1)){ return true; }
  }
  return false;
}
//bottom left
bool isBottomLeftAlive(int **world, int x, int y){
  if((y+1) < HEIGHT && x > 0){
    if(isCellAlive(world, x-1, y+1)){ return true; }
  }
  return false;
}
//bottom right
bool isBottomRightAlive(int **world, int x, int y){
  if( (y+1) < HEIGHT && (x+1) < WIDTH ){
     if(isCellAlive(world, x+1, y+1)){ return true; }
  }
  return false;
}

//Judge cell
//Check is cell survives next generation
bool judgeCell(int **world, int x, int y){
  int count = 0;
  if(isAboveAlive(world, x, y)){ count += 1; }
  if(isBelowAlive(world, x, y)){ count += 1; }
  if(isRightAlive(world, x, y)){ count += 1; }
  if(isTopRightAlive(world, x, y)){ count += 1; }
  if(isBottomRightAlive(world, x, y)){ count += 1; }
  if(isLeftAlive(world, x, y)){ count += 1; }
  if(isTopLeftAlive(world, x, y)){ count += 1; }
  if(isBottomLeftAlive(world, x, y)){ count += 1; }
  if(!(isCellAlive(world, x, y))){
    if(count == 3){
      return true;
    }
    return false;
  } else {
    if(count < 2 || count > 3){
      return false;
    }
    return true;
  }
}

//next frame
int** nextFrame(int **world, int height=HEIGHT, int width=WIDTH){
  int x = 0;
  int y = 0;
  int **newIteration = initWorld();
  while(y < height){
    while(x < width){
      if(judgeCell(world, x, y)){
        newIteration[y][x] = 1;
      } else {
        newIteration[y][x] = 0;
      }
      x++;
    }
    x = 0;
    y++;
  }
  return newIteration;
}

int** basicGliderSeed(){
  int **world = initWorld();
  world[2][0] = 1;
  world[2][1] = 1;
  world[2][2] = 1;
  world[1][2] = 1;
  world[0][1] = 1;
  return world;
}

int** randomSeed(){
  srand((unsigned) time(NULL));
  int **world = initWorld();
  int x,y = 0;
  while(y < HEIGHT){
    world[y] = new int[WIDTH];
    while(x < WIDTH){
      int random = rand();
      world[y][x] = 0;
      if(random%3 == 0 || random%10 == 0){
        world[y][x] = 1;
      }
      x++;
    }
    x = 0;
    y++;
  }
  return world;
}

int** lifeSeed(){
  int **world = initWorld();
  int centerX = WIDTH/2;
  int centerY = HEIGHT/2;
  int i = 1;
  while(i < 4){
    world[centerY + (i + 1)][centerX] = 1;
    world[centerY - (i + 1)][centerX] = 1;
    world[centerY][centerX + i] = 1;
    world[centerY][centerX - i] = 1;
    i++;
  }
  return world;
}

int** seedWorld(int seed=0, int height=HEIGHT, int width=WIDTH){
  if(seed==0){
    return basicGliderSeed();
  } else if(seed==1){
    return randomSeed();
  } else if(seed==2){
    return lifeSeed();
  }
  return initWorld();
}

int getUserInt(string message){
  cin.clear(); //Clearing Cin buffer
  fflush(stdin);//Flushing Cin buffer
  long long int input;
  cout << message;
  cin >> input;
  if (cin.fail()){
    cout << "Value must be an integer!" << endl;
    return getUserInt(message);
  }
  return input;
}

int main(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  HEIGHT = w.ws_row-3;
  WIDTH = (w.ws_col/3)-1;
  system("clear");
  int **world;
  int frames = 0;
  int speed = 0;
  frames = getUserInt("Frames: ");
  speed = getUserInt("Speed in semi seconds: ");
  speed = speed * 50000;
  world = seedWorld(getUserInt("Seed(0-2): "));
  int i = 0;
  while(i < frames){
    displayWorld(world);
    cout << "Frame: " + to_string(i+1) << endl;
    world = nextFrame(world);
    usleep(speed);
    i++;
  }
}
