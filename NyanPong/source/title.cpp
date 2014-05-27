// title functions

#include "AIE.h"
#include "movable_sprite.h" 
#include "ints.h"
#include "KeyCodes.h"

#include "VectorMath.h"

// gives access to vector2 struct and movableObject struct

int titlem = -1; // sprite for title menu

// TODO OBJECTS paddle, wall, ball, cursor

movableObject titlepaddle = {
	30,			// pos x
	390,		// pos y
	0,			// spd x
	0,			// spd y
	-1 ,		// sprite
	20,			// width
	150			// height
};
movableObject titlewall = {TITLEWALL_X, 590, 0, 0, -1, 20, 150};
movableObject cursor = {CURSOR_X, 110, 0, 0, -1 , CURSOR_W, CURSOR_H};
movableObject titleball = {640, 590, 2, 1, -1, BALL_W, BALL_H};
movableObject help = {640, 390, 0, 0, -1 , 400, 320};



void cursormove(movableObject &cursor, bool &bTitleActive, bool &bgamerunning, bool &bpongrunning)
{
	static int iDelay = 0;
		
	if (iDelay == 0)
	{
		if (IsKeyDown('W') && cursor.position.y > 120)  //310 210 110
		{
			cursor.position.y = cursor.position.y - 100;
			iDelay = 100;
		}


		if (IsKeyDown('S') && cursor.position.y < 280)
		{
			cursor.position.y = cursor.position.y + 100;
			iDelay = 100;
		}
	}
	if (iDelay > 0)
	{
		iDelay = iDelay - 1;
	}

	if (IsKeyDown(GLFW_KEY_SPECIAL+38)&& cursor.position.y == 110)
	{
		bTitleActive = false;
	}

	if (IsKeyDown(GLFW_KEY_SPECIAL+38)&& cursor.position.y == 210)
	{
		DrawSprite(help.sprite);
		MoveSprite(help.sprite, 640, 535);
	}

	if (IsKeyDown(GLFW_KEY_SPECIAL+38)&& cursor.position.y == 310)
	{
		bTitleActive = false;
		bgamerunning = false;
		bpongrunning = false;

	}
}
bool testOnTitleScreen(movableObject& obj){
	if(obj.position.x >= SCREEN_X -45) {
		obj.speed.x *= -1;
		return true;
	}
	if(obj.position.x <= + 35) {
		obj.speed.x *= -1;
		return true;
	}
	if(obj.position.y <= 420) {
		obj.speed.y *= -1;
	}
	if(obj.position.y >= 770) {
		obj.speed.y *= -1;
	}
	return false;
}

void updateTitleBallPosition(movableObject &obj) 
{
	obj.position = vectorAdd(obj.position, obj.speed);
}

void initTitle()
{
	titlem = CreateSprite( "./images/start.png", SCREEN_X, SCREEN_Y, true );
	MoveSprite(titlem, SCREEN_X>>1, SCREEN_Y>>1);
	titlepaddle.sprite = CreateSprite( "./images/plyr.png", titlepaddle.width, titlepaddle.height, true);
	titlewall.sprite = CreateSprite( "./images/plyr.png", titlewall.width, titlewall.height, true );
	titleball.sprite = CreateSprite( "./images/b.png", BALL_W, BALL_H, true );
	cursor.sprite = CreateSprite( "./images/cursor.png", cursor.width, cursor.height, true );
	help.sprite = CreateSprite( "./images/help.png", 600, 360, true);
}

void destroyTitle()
{
	DestroySprite(titlem);
	DestroySprite(titlepaddle.sprite);
	DestroySprite(titlewall.sprite);
	DestroySprite(titleball.sprite);
	DestroySprite(cursor.sprite);
}

void updateTitle(bool &bTitleActive, bool &bgamerunning, bool &bpongrunning)
{
	testOnTitleScreen(titleball);
	updateTitleBallPosition(titleball);
	cursormove(cursor, bTitleActive, bgamerunning, bpongrunning);
	// titlepaddle matches ball.pos.y
	
	titlepaddle.position.y = titleball.position.y;
	titlewall.position.y = titleball.position.y;

	MoveSprite(titlepaddle.sprite, titlepaddle.position.x, titlepaddle.position.y);
	MoveSprite(titlewall.sprite, titlewall.position.x, titlewall.position.y);
	MoveSprite(titleball.sprite, titleball.position.x, titleball.position.y);
	MoveSprite(cursor.sprite, cursor.position.x, cursor.position.y);
}

void drawTitle()
{
	DrawSprite(cursor.sprite);
	DrawSprite(titlepaddle.sprite);
	DrawSprite(titlewall.sprite);
	DrawSprite(titleball.sprite);
	DrawSprite(titlem);	
}