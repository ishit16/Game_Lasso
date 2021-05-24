#include <simplecpp>
#include <string>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include<cstdio>
#include<cstdlib>
using namespace simplecpp;

main_program {
  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  //Start Page and the instructions page of the game is created below using hide and show commands
  // the following bools are used to decide what action to take if the user presses the buttons
bool i=false;
bool j=false;
const double bIx=225, bIy=250,bSx=225,bSy=350, bWidth=150, bHeight=50;
// creation of buttons with the above dimensions

Rectangle button_inst(bIx,bIy,bWidth,bHeight);
Rectangle border_inst(bIx,bIy,bWidth+1,bHeight+1);//Creates the outline for the button
button_inst.setColor(COLOR("red")); button_inst.setFill(true);

// bSx,bXy Denote the centre coordinates of the rectangle button and similarly bWidth and bHeight denote the dimensions of the button
//t_inst is the text variable name used for writing the word "Instructions"
Rectangle button_start(bSx,bSy,bWidth,bHeight);
Rectangle border_start(bSx,bSy,bWidth+1,bHeight+1);
button_start.setColor(COLOR("green")); button_start.setFill(true);
Text t_inst(bIx,bIy,"Instructions");
Text t_start(bSx,bSy,"Start Game");

// welx and wely denote the centre coordinates of the text written under Welcome //
const double welx=226, wely=50;
Text welcome(welx,wely,"Welcome to the game Lasso!");

//Circles are drawn here (x,y,radius) these are the arguments of the struct circle//
Circle circ1(100,225,15); circ1.setColor(COLOR("blue")); circ1.setFill(true);//coin creation
Circle circ2(350,255,15); circ2.setColor(COLOR("blue")); circ2.setFill(true);//coin creation

//The following while loops are used because the user may first click somewhere else before clicking on the actual buttons
// These while loops allow the user to click multiple times
while(true){
while(true){
int clickPos;
clickPos=getClick();
int clickx=clickPos/65536;
int clicky=clickPos%65536;
if(clickx<300 && clickx>150 && clicky<275 && clicky>225){
//Hide all the buttons to go the next page
welcome.hide();
button_inst.hide();
border_inst.hide();
button_start.hide();
border_start.hide();
t_inst.hide();
t_start.hide();
circ1.hide();
circ2.hide();
i=true;
break;}
else if(clickx<300 && clickx>150 && clicky<375 && clicky>325){j=true;break;}
}
if(j==true){welcome.hide(); button_inst.hide();border_inst.hide();
button_start.hide();border_start.hide();t_inst.hide();t_start.hide();circ1.hide();circ2.hide();break;}
if(i==true){
// Below are the texts for various instructions

Text inst(250,100,"Instructions:");
Text inst1(250,150,"1. Press T to unpause the lasso, lasso starts to move.");
Text inst2(250,170,"2. Press L to loop the lasso, it tries to catch a coin,Blue coins are worth 1 point.");
Text inst3(250,190,"3. Press Y to yank the lasso, it also resets the coins.");
Text inst4(250,210,"4. Press + and - to increase/decrease the lasso speed.");
Text inst5(250,230,"5. Catch 30 coins to win the game,Yellow coin is worth two points.");
Text inst6(250,250,"6. Do not catch a bomb unless you want to loose.");
Text inst7(250,270,"7. At random times you get extra lives if you catch coins.");
Text inst8(250,290,"8. If you are unable to catch a coin, you loose a life.");
Text inst9(250,310,"9. Keep an eye on the black window for messages during the game.");
Text inst10(250,330,"11. Press Q if you want to quit in the middle of the game.");
Rectangle get_back_border(250,380,72,72);
Rectangle get_back(250,380,70,70);
get_back.setColor(COLOR(255,215,0)); get_back.setFill(true);
Text prev(250,380,"Go Back");
while(true){
int clickPos2;
clickPos2=getClick();
int clickx2=clickPos2/65536;
int clicky2=clickPos2%65536;
if(clickx2<286&&clickx2>224&&clicky2>344&&clicky2<416){
inst.hide();inst1.hide();inst2.hide();inst3.hide();inst4.hide();inst5.hide();
inst6.hide();inst7.hide();inst8.hide();inst9.hide();inst10.hide();get_back_border.hide();get_back.hide();prev.hide();
break;}
}
//show all the buttons to come back to the previous page
welcome.show();
button_inst.show();
border_inst.show();
button_start.show();
border_start.show();
t_inst.show();
t_start.show();
circ1.show();
circ2.show();
}

}



  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("green"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("green"));

  // key controls from the keyboard
  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  char lives[256];
  //Below sprintf commands are used in similar fashion to the cmd and coins number
  // Target and Lives show up on screen
  sprintf(lives, "Lives: %d",lasso.getNumlives());
  Text life(200,200,lives);
  Text target(200,220,"TARGET: 30");
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);
  // input the name of the user
  string name("ENTER YOUR NAME IN THE BLACK WINDOW: ");//user enters the name from the keyboard in the command prompt
  Text namenter(PLAY_X_START+280, PLAY_Y_HEIGHT+60, name);
  string entname; cout<<"Enter your name: "<<endl;
  getline(cin,entname);
  cout<<"Hello! Enjoy this wonderful game!"<<endl;//message in command prompt
  namenter.hide();
  Text t1(PLAY_X_START+350, PLAY_Y_HEIGHT+60, entname);



  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_angle_deg1=COIN_ANGLE_DEG+15;
  double coin_angle_deg2=COIN_ANGLE_DEG-15;
  double bomb_angle_degree=96;
  double coin_ax = 0;
  double coin_ay = COIN_G; // gravity which attracts coin
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  // creating two more coins which would go in parabolaic path
  Coin c1(coin_speed+10, coin_angle_deg1, coin_ax, coin_ay, paused, rtheta);
  c1.coin_circle.setColor(COLOR("yellow"));//high speed coin
  c1.coin_circle.setFill(true);
  Coin c2(coin_speed, coin_angle_deg2, coin_ax, coin_ay, paused, rtheta);
  //Bomb Coin creation which will appear only at specific times//
  Coin bomb(coin_speed, bomb_angle_degree,coin_ax,coin_ay+1,paused,rtheta);
  bomb.coin_circle.setColor(COLOR("black"));
  bomb.coin_circle.setFill(true);
  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit

  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char t=charFromEvent(e);
      name[100]=t;
      namenter.setMessage(name);
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	c1.resetCoin(COIN_SPEED+20,coin_angle_deg1);
	c1.coin_circle.setColor(COLOR("yellow"));//high speed coin
    c1.coin_circle.setFill(true);
    c2.resetCoin(COIN_SPEED,coin_angle_deg2);
	coin.resetCoin(COIN_SPEED,COIN_ANGLE_DEG);
	bomb.resetCoin(COIN_SPEED,bomb_angle_degree);
	break;
      case 'l':
	lasso.loopit();
	lasso.check_for_coin(&coin,&c1,&c2,&bomb);//checks for all the coins and bombs
	wait(STEP_TIME*5);
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
	exit(0);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);

    coin.nextStep(stepTime);
    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      coin.resetCoin(COIN_SPEED,COIN_ANGLE_DEG);
      last_coin_jump_end = currTime;
    }
      bomb.nextStep(stepTime);
      if(bomb.isPaused()) {
      if(lasso.getNumCoins()>=15){
      bomb.unpause();
    }
    }
    if(bomb.getYPos()>PLAY_Y_HEIGHT){
      bomb.resetCoin(COIN_SPEED,bomb_angle_degree);
      last_coin_jump_end=currTime;
    }
    c1.nextStep(stepTime);
    if(c1.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	c1.unpause();
      }
    }

    if(c1.getYPos() > PLAY_Y_HEIGHT) {
      c1.resetCoin(COIN_SPEED+10,coin_angle_deg1);
      last_coin_jump_end = currTime;
    }
    c2.nextStep(stepTime);
    if(c2.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	c2.unpause();
      }
    }

    if(c2.getYPos() > PLAY_Y_HEIGHT) {
      c2.resetCoin(COIN_SPEED,coin_angle_deg2);
      last_coin_jump_end = currTime;
    }
    if(lasso.getNumlives()==0){ settextstyle(0,0,5);
       drawText(450,250,"GAME OVER!!",COLOR("red"));
       cout<<"GAME OVER!"<<endl<<"YOUR SCORE: "<<lasso.getNumCoins();
       wait(5); exit(0);
    }
    //if the player achieves the target of 30 coins game ends with a message
    if(lasso.getNumCoins()==30){
        settextstyle(0,0,5);
        drawText(450,250,"YOU WON THE LASSO CHALLENGE!",COLOR(255,0,255));
        cout<<"Winner!"<<endl<<"TARGET ACHIEVED!"<<endl;wait(5);exit(0);
        }
    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);
    //Keeps the track of number of lives
    sprintf(lives, "Lives: %d",lasso.getNumlives());
    life.setMessage(lives);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);
  }
  // End for(;;)

  wait(3);
} // End main_program
