//Ball class
#include"head.h"

Ball::Ball(int x, int y, int vel_x, int vel_y){
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

	Angle = 90;
}

int Ball::getX(){
	return mPosX;
}

int Ball::getY(){
	return mPosY;
}

void Ball::setXY(int x, int y){
	mPosX = x;
	mPosY = y;
}

//handles reset. ball only starts moving when spacebar is pressed
bool Ball::begin(SDL_Event& e){
	if(e.type == SDL_KEYDOWN && e.key.repeat==0){
		if(e.key.keysym.sym == SDLK_SPACE){
			return true;
		}
	}else if(e.type == SDL_KEYUP && e.key.repeat==0){
		if(e.key.keysym.sym == SDLK_SPACE){
			return true;
		}
	}
	return false;
}

void Ball::Set_Dimensions(int h, int w){
	OB_HEIGHT = h;
	OB_WIDTH = w;

	mCollider.w = OB_WIDTH;
	mCollider.h = OB_HEIGHT;
}

//moves ball and checks for collision. sign changes account for hitting wall or brick, and kept track of in program.
//only handles a 90 degree turn at the moment, will make it better
bool Ball::move(std::list<Brick >& bricks, int& sign_x, int& sign_y){
	std::list<Brick >::iterator lit;

	//Move the dot left or right
    mPosX += (mVelX*sign_x);
    mCollider.x = mPosX;

    //up or down
    mPosY += (mVelY*sign_y);
    mCollider.y = mPosY;

    for(lit = bricks.begin();lit != bricks.end(); lit++){

		//If the dot collided or went too far to the left or right
        if( ( mPosX < 0 ) || ( mPosX + OB_WIDTH > SCREEN_WIDTH ) || checkCollision(mCollider,*lit)){
		
			if(lit->hit==false || lit==bricks.begin()){
			
				//change direction of x velocity
				mPosX -= (mVelX*sign_x);
				mCollider.x= mPosX;
				sign_x = (sign_x *(-1));
				
				lit->takeHealth();
			
			}
		}else if((mPosY < 0) || checkCollision(mCollider, *lit) ){
               
			if((lit->hit==false || lit==bricks.begin())){
		
				//change sign of y velocity
				mPosY -= (mVelY*sign_y);
			    mCollider.y = mPosY;
			    sign_y = (sign_y *(-1));
					
				lit->takeHealth();
			}
		
		}

		
		//remove brick from the list if its lost all its health
		//this keeps glitching hard so idk maybe we can figure it out
		//if(lit->hit==true){
		//	lit = bricks.erase(lit);
		//}

		//round is lost bc you let the ball drop. litterally
		if(mPosY + OB_HEIGHT > SCREEN_HEIGHT){
			return true;
		}
        
    }

	return false;

}


void Ball::render(LTexture& gBall, SDL_Renderer* gRenderer){
	gBall.render(gRenderer,mPosX,mPosY);
}


