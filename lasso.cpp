#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "lives.h"
#include "coin_comparison.h"
using namespace simplecpp;

double coin_x;
void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

// initial lasso traits
void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR(255,215,0));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin = NULL;
  num_coins = 0;
  num_lives=8; // initial number of lives have been set to 8

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR(139,69,19));

  lasso_band.setColor(COLOR(169,169,169));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin != NULL) {
  // Position Dependent Resetting of Coin On Looping //
  num_coins++;
    if(num_coins==15){Text lev2(350,200,"Level 2 Begins!!");
    wait(3);}
  }
  // if the lasso returns as NULL lives will decrease
  if(the_coin==NULL){
    num_lives--;
    }
// The next statement is very precious, in the original game the lasso on being yanked increased the coin count
// Because the coin pointer contained the orginal coin only
// Foloowing statment sets the coin pointer to NULL on being yanked
    the_coin=NULL;

} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped) { return; } // Already looped
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
  lasso_looped = true;
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT) { yank(); }
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

//Check for coin member function has been changed so that it catches the coin which is closest to lasso
//Bomb catching is given the least priority
//Pointers to Coin and bombs have been created in header file
void Lasso::check_for_coin(Coin *coinPtr1, Coin *coinPtr2, Coin *coinPtr3, Coin *bomb) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bomb_x  = bomb->getXPos();
  double bomb_y  = bomb->getYPos();
  double coin_x  = coinPtr1->getXPos();
  double coin_y  = coinPtr1->getYPos();
  double coin_x2 = coinPtr2->getXPos();
  double coin_y2 = coinPtr2->getYPos();
  double coin_x3 = coinPtr3->getXPos();
  double coin_y3 = coinPtr3->getYPos();
  double x1diff  = (lasso_x - coin_x);
  double y1diff  = (lasso_y - coin_y);
  double x2diff  = (lasso_x - coin_x2);
  double y2diff  = (lasso_y - coin_y2);
  double x3diff  = (lasso_x - coin_x3);
  double y3diff  = (lasso_y - coin_y3);
  double x4diff  = (lasso_x - bomb_x) ;
  double y4diff  = (lasso_y - bomb_y) ;
  double distance1 = sqrt((x1diff*x1diff)+(y1diff*y1diff));
  double distance2 = sqrt((x2diff*x2diff)+(y2diff*y2diff));
  double distance3 = sqrt((x3diff*x3diff)+(y3diff*y3diff));
  double distance4 = sqrt((x4diff*x4diff)+(y4diff*y4diff));
    if(distance1 <= LASSO_RADIUS && distance2 <= LASSO_RADIUS && distance3 <=LASSO_RADIUS) {
        if(minimum_three(distance1, distance2, distance3)==distance1){
        the_coin = coinPtr1;the_coin->getAttachedTo(this);
        }
        else if(minimum_three(distance1, distance2, distance3)==distance2){
        the_coin = coinPtr2;if(distance2>=3){num_coins++;}the_coin->getAttachedTo(this);}
        else {the_coin=coinPtr3;the_coin->getAttachedTo(this);}
    }
  else if(distance1<=LASSO_RADIUS && distance2<= LASSO_RADIUS){
        if(distance1<=distance2) {the_coin=coinPtr1;the_coin->getAttachedTo(this);}
        else {the_coin=coinPtr2;if(distance2>=3){num_coins++;}the_coin->getAttachedTo(this);}
    }
  else if(distance1<=LASSO_RADIUS && distance3<=LASSO_RADIUS){
        if(distance1<=distance3) {the_coin=coinPtr1;the_coin->getAttachedTo(this);}
        else {the_coin=coinPtr3;the_coin->getAttachedTo(this);}
    }
 else if(distance2<=LASSO_RADIUS && distance3<=LASSO_RADIUS){
        if(distance2<=distance3) {the_coin=coinPtr2;if(distance2>=3){num_coins++;}the_coin->getAttachedTo(this);}
        else {the_coin=coinPtr3;the_coin->getAttachedTo(this);}
    }
 else if(distance1<=LASSO_RADIUS){the_coin=coinPtr1;the_coin->getAttachedTo(this);}
 else if(distance2<=LASSO_RADIUS){the_coin=coinPtr2;if(distance2>=3){num_coins++;}the_coin->getAttachedTo(this);}
 else if(distance3<=LASSO_RADIUS){the_coin=coinPtr3;the_coin->getAttachedTo(this);}
 else if(distance4<=LASSO_RADIUS){the_coin=bomb;the_coin->getAttachedTo(this);}
// check if the number of coins in prime, accordingly give a life!
// displays a text on the canvas regarding extra life
// changes the color of the coin caught temporarily to yellow
  if(the_coin==bomb){num_lives=0;
  drawText(300,300,"You Caught a Bomb!!",COLOR(210,105,30));wait(2);
  }
  if(the_coin==coinPtr2 && x2diff>=10E-4)num_coins++;
  if(primes(num_coins)==true && the_coin!=coinPtr2){
    if(the_coin!=NULL && the_coin!=bomb){
    the_coin->coin_circle.setColor(COLOR(255,105,180)); the_coin->coin_circle.setFill(true);
    drawText(lasso_x,lasso_y-20,"You Get A Life!!",COLOR("green")); num_lives++;
    wait(3);
    if(the_coin==coinPtr1||the_coin==coinPtr3){the_coin->coin_circle.setColor(COLOR("blue")); the_coin->coin_circle.setFill(true);}
    else the_coin->coin_circle.setColor(COLOR("yellow"));the_coin->coin_circle.setFill(true);}
    }
    }
// life checking ends//


// End Lasso::check_for_coin()

