//////////////////////////////////////////////////////////////////////////
//Project Name = Pong
//Last Editor = Brandon Foote
//Last Edit = Start menu
//
//
//I know. Too many global ints. it wont happen next time. I just really didnt want to change them all
//////////////////////////////////////////////////////////////////////////

#include "header.h"
#include "movable_sprite.h"
#include <time.h>
#include "collision.h"
#include "ints.h"
#include "title.h"
#include "VectorMath.h"

const int SPEED = 10;
const int SCREEN_X = 1280;
const int SCREEN_Y = 780;

const int PLAYER1_X = 30;
const int PLAYER1_W = 20;
const int PLAYER1_H = 150;

const int PLAYER2_X = 1250;
const int PLAYER2_W = 20;
const int PLAYER2_H = 150;

const int BALL_W = 20;
const int BALL_H = 20;

const int WIN_W = 400;
const int WIN_H = 100;

const int TWIN_W = 400;
const int TWIN_H = 100;

const int PAUSE_X = 640;
const int PAUSE_W = 400;
const int PAUSE_H = 100;

const int SCORE1_X = 540;
const int SCORE1_W = 60;
const int SCORE1_H = 60;

const int SCORE2_X = 733;
const int SCORE2_W = 60;
const int SCORE2_H = 60;

const int TITLEPADDLE_X = 30;
const int TITLEPADDLE_W = 20;
const int TITLEPADDLE_H = 150;

const int TITLEWALL_X = 1250;
const int TITLEWALL_W = 20;
const int TITLEWALL_H = 350;   // ------Will need to be changed

const int CURSOR_X = 700;  // ----------- Depends on location of title choices
const int CURSOR_W = 30;
const int CURSOR_H= 30;

const int TITLEBALL_W = 20;
const int TITLEBALL_H = 20;


int iturn = 1;
int i2turn = 1;

int iY;
int igamerun = 0;

int g_highScores[5] = {0};
bool g_gameOver = false;
bool g_title = false;
bool bgamerunning = true;

int player1Score = 0;
int player2Score = 0;
int frameCounter = 0;

movableObject player1 = {PLAYER1_X, 390, 0, 0, -1 , PLAYER1_W, PLAYER1_H};
movableObject player2 = {PLAYER2_X, 390, 0, 0, -1, PLAYER2_W, PLAYER2_H};
movableObject ball = {640, 390, 2, 1, -1, BALL_W, BALL_H}; // ball speed is 2 , 1 <----------------------------------
movableObject score1 = {SCORE1_X, 540, 0, 0, -1 , SCORE1_W, SCORE1_H};
movableObject score2 = {SCORE2_X, 733, 0, 0, -1 , SCORE2_W, SCORE2_H};

movableObject win = {640, 390, 0, 0, -1 , WIN_W, WIN_H};
movableObject twin = {640, 390, 0, 0, -1 ,TWIN_W, TWIN_H};

int back = -1;
// subtract a scalar from a vector, return the result as a new vector
vector2 vectorSubtract(vector2 &v, float s){
	vector2 result = {v.x - s, v.y - s};
	return result;
}

// adds a scalar to a vector, return the result as a new vector
vector2 vectorAdd(vector2 &v, float s){
	vector2 result = {v.x + s, v.y + s};
	return result;
}

// multiplies a vector by a scalar, returns the result as a new vector
vector2 multiplyScalar(vector2 &v, float s){
	vector2 result = {v.x * s, v.y * s};
	return result;
}

// subtract one vector from another, returns the result as a new vector
vector2 vectorSubtract(vector2 &v, vector2 &v2){
	vector2 result = {v.x - v2.x, v.y - v2.y};
	return result;
}



// get the normal of a vector, returns the result as a new vector
vector2 getNormal(vector2 &v){
	float mag = sqrt(v.x*v.x + v.y*v.y);
	vector2 result = {v.x/mag, v.y/mag};
	return result;
}

// get the magnitude of a vector
float getMagnitude(vector2 &v){
	return sqrt(v.x*v.x + v.y*v.y);
}

// will test if an object has gone outside the screen boundaries
// if the object has gone off the screen, this function will also modify
// the objects speed so that it will move back onto the screen
// returns true if the object's x or y coordinate is off the screen
bool testOnScreen(movableObject& obj){
	if(obj.position.x > SCREEN_X + 80) {
		obj.speed.x *= -1;
		return true;
	}
	if(obj.position.x < - 80) {
		obj.speed.x *= -1;
		return true;
	}
	if(obj.position.y > SCREEN_Y - 25) {
		obj.speed.y *= -1;
	}
	if(obj.position.y < 25) {
		obj.speed.y *= -1;
	}
	return false;
}

// updates the position of the ball
// adds the balls current velocity to its current position to get the 
// new position

void score(movableObject &obj)
{
	if (player1Score == 0)
		{
			score1.sprite = CreateSprite("./images/score/0.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
			
		}

		if (player1Score == 1)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/1.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}

		if (player1Score == 2)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/2.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
			
		}

		if (player1Score == 3)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/3.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}
		if (player1Score == 4)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/4.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}

		if (player1Score == 5)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/5.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}
		if (player1Score == 6)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/6.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}

		if (player1Score == 7)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/7.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}
		if (player1Score == 8)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/8.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}

		if (player1Score == 9)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/9.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}
		if (player1Score == 10)
		{
			DestroySprite(score1.sprite);
			score1.sprite = CreateSprite("./images/score/10.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score1.sprite, 550, 50);
		}


}

void scoretwo(movableObject &obj)
{
	if (player2Score == 0)
		{
			score2.sprite = CreateSprite("./images/score/0.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
			
		}

		if (player2Score == 1)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/1.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}

		if (player2Score == 2)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/2.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
			
		}

		if (player2Score == 3)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/3.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}
		if (player2Score == 4)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/4.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}

		if (player2Score == 5)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/5.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}
		if (player2Score == 6)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/6.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}

		if (player2Score == 7)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/7.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}
		if (player2Score == 8)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/8.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}

		if (player2Score == 9)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/9.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}
		if (player2Score == 10)
		{
			DestroySprite(score2.sprite);
			score2.sprite = CreateSprite("./images/score/10.png", SCORE1_W, SCORE1_H, true);
			MoveSprite (score2.sprite, 733, 50);
		}


}
void updateBallPosition(movableObject &obj) 
{
	obj.position = vectorAdd(obj.position, obj.speed);
}
// check if the ball has collided with the paddle
// returns true if a collision occurred
bool checkPaddleCollision(movableObject& ball, movableObject& player) {
	int speed = ball.speed.x;
	
	int ballHalfW = ball.width>>1;
	int playerHalfW = player.width>>1;
	int playerHalfH = player.height>>1;
	
	if(speed == 0)
		return false;

	if(speed < 0)
	{
		if(ball.position.x - ballHalfW < player.position.x + playerHalfW && 
			ball.position.y > player.position.y - playerHalfH &&
			ball.position.y < player.position.y + playerHalfH)
		{
				return true;
				
		}
	}
	else {
		if(ball.position.x + ballHalfW > player.position.x - playerHalfW && 
			ball.position.y > player.position.y - playerHalfH &&
			ball.position.y < player.position.y + playerHalfH){
				return true;
		}
	}
	return false;
}

	int iPlayerDirection = 0;
	void seekplayer(movableObject &player, movableObject& ball)
	{
		if (IsKeyDown('W'))
		{
			if(iturn == 1)
			{
			iPlayerDirection = 1;
			iturn = 0;
			}
		}


		if (IsKeyDown('S'))
		{
			if(iturn == 1)
			{
			iPlayerDirection = 2;
			iturn = 0;
			}
		}

		switch (iPlayerDirection)
		{
			case 0:
				break;
			case 1:
				if(player.position.y >= 0)
				{
				player1.position.y = player1.position.y - 1.35;
				}
				break;
			case 2:
				if(player.position.y <=780)
				{
				player1.position.y = player1.position.y + 1.35;
				}
				break;
		}
		
	}

	int iPlayer2Direction = 0;
	void seekplayer2(movableObject &player, movableObject& ball)
	{
		
		if (IsKeyDown(GLFW_KEY_SPECIAL+27))		
		{
			if(i2turn == 1)
			{			
					iPlayer2Direction = 1;
					i2turn = 0;		
			}
		}

		if (IsKeyDown(GLFW_KEY_SPECIAL+28))
		{
			if (i2turn == 1)
			{
					iPlayer2Direction = 2;
					i2turn = 0;
			}
		}
		switch (iPlayer2Direction)
		{
			case 0:
				break;
			case 1:
				if(player2.position.y >= 0)
				{
				player2.position.y = player2.position.y - 1.35;
				}
				break;
			case 2:
				if(player2.position.y <=780)
				{
				player2.position.y = player2.position.y + 1.35;
				}
				break;
		}
	}
// initialize all the variables in the game
	void initGame() {
	srand(time(0));
		/*DrawString("Press Enter", SCREEN_X / 2 - 60, 350);
			getchar();
			getchar();*/

	// Now load some sprites
	back = CreateSprite( "./images/back.png", SCREEN_X, SCREEN_Y, true );
	MoveSprite(back, SCREEN_X>>1, SCREEN_Y>>1);

	player1.sprite = CreateSprite( "./images/plyr.png", PLAYER1_W, PLAYER1_H, true );
	player2.sprite = CreateSprite( "./images/plyr.png", PLAYER2_W, PLAYER2_H, true ); //------------------------------------------------------------------------------------------------------IMAGES
	ball.sprite = CreateSprite( "./images/b.png", BALL_W, BALL_H, true );
	win.sprite = CreateSprite( "./images/1winner.png", WIN_W, WIN_H, true);
	twin.sprite = CreateSprite( "./images/2winner.png", WIN_W, WIN_H, true);
	score1.sprite = CreateSprite( "./images/score/0.png", WIN_W, WIN_H, true);
	score(score1);
	score2.sprite = CreateSprite( "./images/score/0.png", WIN_W, WIN_H, true);
	scoretwo(score2);
}




// destroy all the sprites and clean up any memory
void destroyGame() {
	DestroySprite(back);
	DestroySprite(player1.sprite);
	DestroySprite(player2.sprite);
	DestroySprite(ball.sprite);
	}


// update the game logic here

void updateGame() 
{
	if (g_gameOver == false)
	{
			updateBallPosition(ball);



		// player 1 on auto

			seekplayer(player1, ball);

			seekplayer2(player2, ball);
			
			

		if (player1Score <= 4 || player2Score <= 4)
			if( testOnScreen(ball) ) {
			// ball hit side of screen
			if(ball.position.x < 100) {
				// player 2 score
				player2Score++;
				ball.position.x = 340;
				ball.position.y = 390;
				i2turn = 1;
				iturn = 1;
				player1.position.y = 390;
				player2.position.y = 390;
				iPlayerDirection = 0;
				iPlayer2Direction = 0;
				srand(time(NULL));
				iY = rand() % 2 + 1;
				
				if (iY == 1)
				{
					ball.speed.y = 1;
				}

				if (iY == 2)
				{
					ball.speed.y = -1;
				}
				score(score1);
				scoretwo(score2);
				for(int i= 0;i<500000000;i++);

			}
			else {
				// player 1 scored
				player1Score++;
				ball.position.x = 940;
				ball.position.y = 390;
				i2turn = 1;
				iturn = 1;
				player1.position.y = 390;
				player2.position.y = 390;
				iPlayerDirection = 0;
				iPlayer2Direction = 0;
				srand(time(NULL));
				iY = rand() % 2 + 1;

				if (iY == 1)
				{
					ball.speed.y = 1;
				}

				if (iY == 2)
				{
					ball.speed.y = -1;
				}
				score(score1);
				scoretwo(score2);
				for(int i= 0;i<500000000;i++);
			
			}
		}

		if(g_gameOver == false) 
		{
			if( player1Score == 5)
			{
				//Player 1 Wins
				g_gameOver = true;
			}
		}

		if(g_gameOver == false) 
		{
			if( player2Score == 5)
			{
				//Player 2 wins
				g_gameOver = true;
			}
		}

		if(ball.speed.x < 0) {
			if(checkPaddleCollision(ball, player1) == true)  {
				ball.speed.x *= -1;
				i2turn = 1;
			}
		}
		else {
			if(checkPaddleCollision(ball, player2) == true)  {
				ball.speed.x *= -1;
				iturn = 1;
			}
		}


		RotateSprite(player1.sprite, 0);
		MoveSprite(player1.sprite, player1.position.x, player1.position.y);

		RotateSprite(player2.sprite, 0 );
		MoveSprite(player2.sprite, player2.position.x, player2.position.y);

		MoveSprite(ball.sprite, (int)ball.position.x, (int)ball.position.y);
		}
}
// draws each frame of the game
void drawGame() {
	static char outScore1[15] = {'\n'};
	static char outScore2[15] = {'\n'};

	DrawSprite(ball.sprite);
	DrawSprite(player1.sprite);
	DrawSprite(player2.sprite);
	DrawSprite(score1.sprite);
	DrawSprite(score2.sprite);

	/*sprintf(outScore1, "%d", player1Score);
	sprintf(outScore2, "%d", player2Score);*/

	// draw the scoreslour(255,0,0,255));
	//DrawString(outScore2, 763, 30, SColour(0,255,0,255));


	if(g_gameOver == true) 
	
	{
		if (player1Score > player2Score)
		{
			//DestroySprite(ball.sprite);
			MoveSprite(ball.sprite, -100,-100);
			DrawSprite(ball.sprite);
			
			DrawSprite(win.sprite);
			MoveSprite(win.sprite, win.position.x, win.position.y);

			bgamerunning = true;
			// displays end game screen
		}
		else
		{
			//DestroySprite(ball.sprite);
			MoveSprite(ball.sprite, -100,-100);
			DrawSprite(ball.sprite);

			DrawSprite(twin.sprite);
			MoveSprite(twin.sprite, win.position.x, win.position.y);

			bgamerunning = true;
			// displays end game screen
		}
	}
		DrawSprite(back);
}

// entry point of the program
int main( int arc, char* argv[] )
{	
	bool bgame = true;
	while (bgame = true)
	{
		// First we need to create our Game Framework
		Initialise(SCREEN_X, SCREEN_Y, false );
	
		initTitle();
	
		while (bgamerunning == true)
		{
			bool bTitleActive = true;
			bool bpongrunning = true;

			do
			{
				// FrameCounting shit
				frameCounter++;
				if(frameCounter > 5000)
					frameCounter = 0;

				// Menu Stuff
				ClearScreen(); // empty the screen
				updateTitle(bTitleActive, bgamerunning, bpongrunning); // update the positions and do logical stuff
				drawTitle();   // put things on the screen

			}while (FrameworkUpdate() == false && bTitleActive == true);


			initGame();

			do
			{	
				frameCounter++;

				if(frameCounter > 5000)
					frameCounter = 0;

				ClearScreen();
		
				updateGame();

				drawGame();
			} while ( FrameworkUpdate() == false && bpongrunning == true);

			destroyGame();
	
			Shutdown();

			return 0;
		}
	}
}