//Paddle class
#include"head.h"

Paddle::Paddle(int x, int y, int vel_x, int vel_y){
	OB_HEIGHT = 0;
	OB_WIDTH = 0;
    //Initialize the offsets
	mPosX = x;
	mPosY = y;

    //Set collision box dimension
    mCollider.w = OB_WIDTH;
    mCollider.h = OB_HEIGHT;

    //Initialize the velocity
    mVelX = vel_x;
    mVelY = vel_y;
}

int Paddle::getX(){
	return mPosX;
}

int Paddle::getY(){
	return mPosY;
}

void Paddle::setXY(int x, int y){
	mPosX = x;
	mPosY = y;
}


//controlls paddle with arrow keys
void Paddle::handleEvent(SDL_Event& e){
	//if a key was pressed
	if(e.type == SDL_KEYDOWN && e.key.repeat==0){
		//adjust velocity
		switch(e.key.keysym.sym){
			case SDLK_UP:
				mVelY -= OB_VEL;
				break;
			case SDLK_DOWN:
				mVelY += OB_VEL;
				break;
			case SDLK_LEFT:
				mVelX -= OB_VEL;
				break;
			case SDLK_RIGHT:
				mVelX += OB_VEL;
				break;
		}
	}else if(e.type == SDL_KEYUP && e.key.repeat==0){
		switch(e.key.keysym.sym){
			case SDLK_UP:
				mVelY += OB_VEL;
				break;
			case SDLK_DOWN:
				mVelY -= OB_VEL;
				break;
			case SDLK_LEFT:
				mVelX += OB_VEL;
				break;
			case SDLK_RIGHT:
				mVelX -= OB_VEL;
				break;
		}
	}
}

void Paddle::Set_Dimensions(int h, int w){
	OB_HEIGHT = h;
	OB_WIDTH = w;

	mCollider.w = OB_WIDTH;
	mCollider.h = OB_HEIGHT;
}

void Paddle::move(){
    //Move the dot left or right
    mPosX += mVelX;
    mCollider.x = mPosX;

	//for(int i=0;i<wall.size();i++){
	    //If the dot collided or went too far to the left or right
	    if( ( mPosX < 0 ) || ( mPosX + OB_WIDTH > SCREEN_WIDTH ))
	    {
			//Move back
		    mPosX -= mVelX;
	        mCollider.x = mPosX;
		}
	
}

//I put the renderer in manually in case we want to do multiple windows for some reason 
void Paddle::render(LTexture& gPaddle, SDL_Renderer* gRenderer){
	gPaddle.render(gRenderer,mPosX,mPosY);
}

