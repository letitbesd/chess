#include "oxygine-framework.h"
#include <functional> 
#include "Actor.h"
#include <vector>
#include <ctime>
using namespace oxygine;

//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
Resources gameResources;
#include "Chess.h";
std::clock_t start;
class MainActor: public Actor
{
public:
    spTextField _text;
    spSprite    _button;
	spSprite _bg;
	spSprite _bgchess;
	const int ROW_COUNT = 10;
	const int COL_COUNT = 9;
	const PointerState* touchedBy;
	size_t size = 90;
	spSprite chesses[90];
	spSprite chesses2 [90];
	Vector2 selected;
	Vector2 PosOffset;
	char nextTurn = 'r';
    MainActor():touchedBy(0)
    {
        //create button Sprite
        spSprite button = new Sprite();
		 
		 
        //setup it:
        //set button.png image. Resource 'button' defined in 'res.xml'
        button->setResAnim(gameResources.getResAnim("button"));

        //centered button at screen
		Vector2 temppos = getStage()->getSize();
		Vector2 butsize = button->getSize();
		Vector2 pos;
		pos.x = temppos.x - butsize.x;
		pos.y = temppos.y / 2 - butsize.y / 2;
        button->setPosition(pos);

        //register  click handler to button
        EventCallback cb = CLOSURE(this, &MainActor::buttonClicked);
        button->addEventListener(TouchEvent::CLICK, cb);

#ifdef CLOSURE_FUNCTION //if your compiler supports lambda

        button->addEventListener(TouchEvent::CLICK, [](Event * e)->void
        {
            log::messageln("button clicked");
        });

#endif

        //attach button as child to current actor
        addChild(button);
        _button = button;


        //create TextField Actor
        spTextField text = new TextField();
        //attach it as child to button
        text->attachTo(button);
        //centered in button
        text->setPosition(button->getSize() / 2);

        //initialize text style
        TextStyle style = TextStyle(gameResources.getResFont("main")).withColor(Color::White).alignMiddle();
        text->setStyle(style);
        text->setText("Click\nMe!");

        _text = text;
		Vector2 pos3(0,0);
		//the game ui setup
		spSprite sprite = new Sprite;
		sprite->setResAnim(gameResources.getResAnim("bg"));
		//sprite->setAnchor(0.5f, 0.5f); 
		//sprite->setPosition(pos3); 
		addChild(sprite);
		sprite->addEventListener(TouchEvent::TOUCH_DOWN, CLOSURE(this, &MainActor::chessTouched));
		_bgchess = sprite; 

		//PosOffset.x = pos3.x - _bgchess->getWidth() * 0.5;
		//PosOffset.y = pos3.y  - _bgchess->getHeight() * 0.5;
		int chesstype=-1;
		selected.x = selected.y = -1;
		std::string resid = "";
		for (int i  = 0; i < ROW_COUNT; i ++)
			for (int j = 0; j < COL_COUNT; j++) {
				 // r n b a k c p   0 1 2 3 4 5 6 7
				if (i <1) {
					spSprite sprite = new Sprite;
					
					if (j == 0 || j == 8) {

						sprite->setResAnim(gameResources.getResAnim(resid = "br"));
					}
					else if(j == 1 || j == 7)
						sprite->setResAnim(gameResources.getResAnim(resid = "bn"));
					else if(j == 2|| j == 6)
						sprite->setResAnim(gameResources.getResAnim(resid = "bb"));

					else if(j == 3 || j == 5)
						sprite->setResAnim(gameResources.getResAnim(resid = "ba"));
					else if(j == 4)
						sprite->setResAnim(gameResources.getResAnim(resid = "bk"));
					 
					Vector2 pos2; 
					pos2.x =pos3.x + 41 * j ;
					pos2.y =pos3.y+ 41*i ;
					sprite->setPosition(pos2);  
					addChild(sprite);
					sprite->setTouchEnabled(false); 
					chesses[i * COL_COUNT + j] = (sprite); 
					addSibling(sprite, resid, i, j);
				}
				
				else if (i > 8) {
					spSprite sprite = new Sprite;
					if (j == 0 || j == 8)
						sprite->setResAnim(gameResources.getResAnim(resid = "rr"));
					else if (j == 1 || j == 7)
						sprite->setResAnim(gameResources.getResAnim(resid = "rn"));
					else if (j == 2 || j == 6)
						sprite->setResAnim(gameResources.getResAnim(resid = "rb"));

					else if (j == 3 || j == 5)
						sprite->setResAnim(gameResources.getResAnim(resid = "ra"));
					else if (j == 4)
						sprite->setResAnim(gameResources.getResAnim(resid = "rk"));
					Vector2 pos2;
					pos2.x = pos3.x + 41 * j;
					pos2.y = pos3.y + 41 * i;
					sprite->setPosition(pos2);
					addChild(sprite); 
					sprite->setTouchEnabled(false);
					chesses[i * COL_COUNT + j] = (sprite);
					addSibling(sprite, resid, i, j);
				}

				// second and seventh row
				if (i == 2)
				{
					if (j == 1 || j == 7) 
					{
						spSprite sprite = new Sprite;
						 
							sprite->setResAnim(gameResources.getResAnim(resid = "bc"));
						Vector2 pos2;
						pos2.x = pos3.x + 41 * j ;
						pos2.y = pos3.y + 41 * i ;
						sprite->setPosition(pos2);
						addChild(sprite);
						sprite->setTouchEnabled(false);
						chesses[i * COL_COUNT + j] = (sprite);
						addSibling(sprite, resid, i, j);
					}
				}
				if (i == 7)

				{
					if (j == 1 || j == 7)
					{
						spSprite sprite = new Sprite;

						sprite->setResAnim(gameResources.getResAnim(resid = "rc"));
						Vector2 pos2;
						pos2.x = pos3.x + 41 * j ;
						pos2.y = pos3.y + 41 * i ;
						sprite->setPosition(pos2);
						addChild(sprite);
						sprite->setTouchEnabled(false);
						chesses[i * COL_COUNT + j] = (sprite);
						addSibling(sprite, resid, i, j);
					}
				}
				//third and sixth row
				if (i == 3)
				{
					if (j % 2 == 0)
					{
						spSprite sprite = new Sprite;

						sprite->setResAnim(gameResources.getResAnim(resid = "bp"));
						Vector2 pos2;
						pos2.x = pos3.x + 41 * j ;
						pos2.y = pos3.y + 41 * i ;
						sprite->setPosition(pos2);
						addChild(sprite);
						sprite->setTouchEnabled(false);
						chesses[i * COL_COUNT + j] = (sprite);
						addSibling(sprite, resid, i, j);
					}
				}
				if (i == 6) {
					if (j % 2 == 0)
					{
						spSprite sprite = new Sprite;

						sprite->setResAnim(gameResources.getResAnim(resid = "rp"));
						Vector2 pos2;
						pos2.x = pos3.x + 41 * j ;
						pos2.y = pos3.y + 41 * i ;
						sprite->setPosition(pos2);
						addChild(sprite);
						sprite->setTouchEnabled(false);
						chesses[i * COL_COUNT + j] = (sprite);
						addSibling(sprite, resid, i, j);
					}
				}
			}
    }

	void addSibling(spSprite chess, std::string id, int i,int j) {
		spSprite sbling = new Sprite;
		sbling->setResAnim(gameResources.getResAnim(id + "s"));
		int chesstype = -1; 
		// r n b a k c p   0 1 2 3 4 5 6 7 
		char typec = id[1];
		char teamc = id[0];
		
		sbling->setPosition(chess->getPosition());  
		sbling->setTouchEnabled(false); 
		chesses2[i * COL_COUNT + j] = sbling;
		chess->setChessType(typec);
		chess->setChessTeam(teamc);
	}

	void select(int c, int r) {
		for (int i = 0; i < ROW_COUNT; i++) 
		{
			for (int j = 0; j < COL_COUNT; j++)
			{
				if (chesses[i*COL_COUNT + j]) {
					if (i == r && j == c) {
						//same chess
					}
					else {
						chesses[i*COL_COUNT + j]->attachTo(this);
						chesses2[i*COL_COUNT + j]->detach();
					}

				} 
			}
		}
			
		if (1) {
			int i = r; 
			int j = c;
			if ((chesses[r*COL_COUNT + c])) {
				if (selected.x >= 0 && selected.y >= 0)
				{
					//check if can eat 
					spSprite sp = chesses[(int)(selected.x * COL_COUNT + selected.y)];
					char teamc = chesses[(int)(selected.x * COL_COUNT + selected.y)]->getChessTeam();
					char teamc2 = chesses[(int)(r * COL_COUNT + c)]->getChessTeam();
					if (teamc != teamc2) {
						if (isPosValid(sp, i, j,true)) {
							char diechess = chesses[(int)(r * COL_COUNT + c)]->getChessType();
							updatePosition(selected.x, selected.y, i, j, true);
							if (diechess == 'k') {
								//gameover;
								_text->setText(teamc == 'b' ? "Black Win" : "Red Win");
								if (teamc == 'r')
									start = std::clock() + CLOCKS_PER_SEC * 3;
								else
									_text->setText("Game Over");
								
							}
						} 
					}
					else {
						chesses2[i*COL_COUNT + j]->attachTo(this);
						chesses[i*COL_COUNT + j]->detach();
						selected.x = i;
						selected.y = j;
					}
				}
				else
				{
					chesses2[i*COL_COUNT + j]->attachTo(this);
					chesses[i*COL_COUNT + j]->detach();
					selected.x = i;
					selected.y = j;
				}

			}
			else {

				if (selected.x >= 0 && selected.y >= 0) {
					//move to new position
					spSprite sp = chesses[(int)(selected.x * COL_COUNT + selected.y)];
					if (isPosValid(sp, i, j)) {
						updatePosition(selected.x, selected.y, i, j);
					 }

				}
				else {
					selected.x = -1;
					selected.y = -1;
				}

			}

		}
	}

	bool isPosValid(spSprite sp, int i, int j, bool eat=false) {
		char typec = sp->getChessType();
		char teamc = sp->getChessTeam();
		bool isblack = teamc == 'b';
		switch (typec)
		{
		case 'r':
			if (selected.x == i || selected.y == j)
			{
				bool issamerow = selected.x == i;
				bool issamecol = selected.y == j;
				if (issamerow) {
					if (isBlockedC_Horizontal(i, selected.y, j) != 0) {
						return false;
					}
				}
				else if (issamecol) {
					if (isBlockedC(j, selected.x, i) != 0) {
						return false;
					}
				}
				else
					return false;
				return true;
				 
			}
			break;
		case 'n':
			if (abs(selected.x - i) + abs(selected.y - j) == 3)
			{
				//check if n is blocked
				if (!isBlockedN(selected.x, selected.y, i, j)) {
					return true;
					 
				}

			}
			break;
		case 'b':
			if (((int)(selected.x + selected.y) - (i + j)) % 4 == 0)
			{
				if (!isBlckedB(selected.x, selected.y, i, j))
				{ 
					//black row index is from 0 - 4, red is 5 - 9
					if (isblack && i >= 5)
						return false;
					if (!isblack && i < 5)
						return false;
					return true;
					 
				}
			}
			break;
		case 'a':
			//shi is in index 3 4, 5 only. 
			if (abs(selected.x - i) == 1 && abs(selected.y - j) == 1)
			{
				if (3 <= j && j <= 5)
				{
					return true;
					 
				}

			}
			break;
		case 'k':
			if (abs(selected.x - i) + abs(selected.y - j) == 1) {
				if (3 <= j && j <= 5)
				{
					
					return true;
					 
				}
			}else if(eat) {
				spSprite sp = chesses[i*COL_COUNT + j];
				if (sp->getChessType() == 'k') {
					if (abs(selected.y - j) == 0) {
						if (isBlockedC(j, i, selected.x) == 0)
							return true;
					}
				}
			}
			break;
		case 'c':
			 //pao is able to jump one target. d
			
			if (eat) {
				bool issamerow = selected.x == i;
				bool issamecol = selected.y == j;
				if (issamerow) {
					if (isBlockedC_Horizontal(i, selected.y, j) != 1) {
						return false;
					}
				}
				else if (issamecol) {
					if (isBlockedC(j, selected.x, i) != 1) {
						return false;
					}
				}
				else
					return false;
			}
			else { 
				bool issamerow = selected.x == i;
				bool issamecol = selected.y == j;
				if (issamerow) { 
					if (isBlockedC_Horizontal(i, selected.y, j)!= 0) {
						return false;
					}
				}
				else if (issamecol) {
					if (isBlockedC(j, selected.x, i) != 0) {
						return false;
					}
				}
				else
					return false;
			}
			return true;
			break;
		case 'p':
			if (abs(selected.x - i) + abs(selected.y - j) == 1)
			{ 
				if (isblack)
				{
					if (i <= 4 && abs(selected.y - j) == 1)
						return false;
					if (i < selected.x)
						return false;
				}
				else
				{
					if (i >=5 && abs(selected.y - j) == 1)
						return false;
					if (i > selected.x)
						return false;
				}  
				return true;
			}
			break;
		default:
			return false;
			break;
		}
		return false;
	}
	int isBlockedC_Horizontal(int row, int sc, int ec)
	{
		int change = abs(sc - ec);
		if (change <= 1)
			return false;
		int inc = sc < ec ? 1 : -1;
		int count = 0;
		for (int k = sc + inc, i = 0; i < change - 1; k += inc)
		{
			i++;
			count += chesses[row*COL_COUNT + k] == NULL ? 0 : 1;
		}

		return count ;
	}
	int isBlockedC(int col, int sr, int er) {
		int change = abs(sr - er);
		if (change <= 1)
			return false;
		int inc = sr < er ? 1 : -1;
		int count = 0; 
		for (int k = sr+inc, i=0; i < change-1; k += inc)
		{
			i++; 
			count += chesses[k*COL_COUNT + col] == NULL ? 0 : 1;
		}
			
		return count;
	}
	///pass in value is: x is row num, y is col num
	bool isBlockedN(int oldx, int oldy, int newx, int newy) 
	{
		int diry = abs(oldx - newx);
		int dirx = abs(oldy - newy);
		if (dirx < diry) //virtical jump
		{
			if (oldx < newx)
				oldx += 1;
			else
				oldx -= 1;

			return chesses[(int)(oldx*COL_COUNT + oldy)] != NULL;
		}
		else //horizonary jump
		{
			if (oldy < newy)
				oldy++;
			else
				oldy--;
			return chesses[(int)(oldx*COL_COUNT + oldy)] != NULL;
		}
	}
	bool isBlckedB(int oldx, int oldy, int newx, int newy)
	{
		oldx = (oldx + newx) / 2;
		oldy = (oldy + newy) / 2;
		return chesses[(int)(oldx*COL_COUNT + oldy)] != NULL;
	}
	bool updatePosition(int oldx, int oldy, int newx, int newy, bool eat = false) {
		spSprite sprite =		chesses[(int)(oldx*COL_COUNT + oldy)];
		selected.x = selected.y = -1;
		if (sprite->getChessTeam() != nextTurn)
			return false;
		nextTurn = nextTurn == 'r' ? 'b' : 'r';

		if (eat) {
			int i = newx;
			int j = newy;
			chesses[(int)(i * COL_COUNT + j)]->detach();
			chesses2[(int)(i * COL_COUNT + j)]->detach();
			chesses[(int)(i * COL_COUNT + j)] = NULL;
			chesses2[(int)(i * COL_COUNT + j)] = NULL;
		}
		Vector2 newpos = Vector2(PosOffset.x + newy * 41, PosOffset.y + newx * 41);

		chesses[(int)(newx*COL_COUNT + newy)] = chesses[(int)(oldx*COL_COUNT + oldy)];
		chesses2[(int)(newx*COL_COUNT + newy)] = chesses2[(int)(oldx*COL_COUNT + oldy)];
		chesses[(int)(newx*COL_COUNT + newy)]->setPosition(newpos);
		chesses2[(int)(newx*COL_COUNT + newy)]->setPosition(newpos);

		chesses[(int)(oldx*COL_COUNT + oldy)] = NULL;
		chesses2[(int)(oldx*COL_COUNT + oldy)] = NULL;
		return true;
	}
	 
    void buttonClicked(Event* event)
    {
        //user clicked to button

        //animate button by chaning color
        _button->setColor(Color::White);
        _button->addTween(Sprite::TweenColor(Color::Green), 500, 1, true);

        //animate text by scaling
        _text->setScale(1.0f);
        _text->addTween(Actor::TweenScale(1.1f), 500, 1, true);

        //and change text
        _text->setText("Clicked!");

        
    }

	void chessTouched(Event* e)
	{
		 
		log::messageln("xx clicked");
		//e->userData
		TouchEvent* te = safeCast<TouchEvent*>(e);
		int col = (int)(te->position.x / 41);
		int row = (int)(te->position.y / 41);
		//check radius
		Vector2 *pos = new Vector2(te->position.x, te->position.y);

		float dist = pos->distance( Vector2(col * 41+20.5, row * 41 + 20.5));
		delete pos;
		if (dist > 20.5)
			return;
		log::messageln("xx col, row:");
		select(col, row);


	}
};
//declare spMainActor as intrusive_ptr holder of MainActor
typedef oxygine::intrusive_ptr<MainActor> spMainActor;
//you could use DECLARE_SMART preprocessor definition it does the same:
//DECLARE_SMART(MainActor, spMainActor)

void example_preinit() {

	
}

void GameStart() {
	spMainActor actor = new MainActor;
	actor->setAnchorInPixels(Vector2(0, 0));
	//actor->setScale(Vector2(1.5, 1.5));
	actor->setPosition(Vector2(0, 0));
	//and add it to Stage as child
	getStage()->addChild(actor);
}
//called from main.cpp
void example_init()
{
    //load xml file with resources definition


    //lets create our client code simple actor
    //spMainActor was defined above as smart intrusive pointer (read more: http://www.boost.org/doc/libs/1_60_0/libs/smart_ptr/intrusive_ptr.html)
	gameResources.loadXML("res.xml");

	GameStart();

}




//called each frame from main.cpp
void example_update()
{
	if (start > 0 &&  std::clock() - start > 0)
	{
		 
		getStage()->removeChildren();
		GameStart();
		start = 0;
	}
}

//called each frame from main.cpp
void example_destroy()
{
    //free previously loaded resources
    gameResources.free();
}
