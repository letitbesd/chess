#include "oxygine-framework.h"
#include <functional> 
#include "Actor.h"
#include <stdio.h>
#include "Chess.h"
using namespace oxygine;
using namespace std;
extern Resources gameResources;
Chess::Chess(string pid):id(pid) {
	_sprite = new Sprite;
	_sprite->setResAnim((gameResources).getResAnim(pid));
	addChild(_sprite);
	setTouchChildrenEnabled(false);
	_sprite2 = new Sprite;
	_sprite2->setResAnim(gameResources.getResAnim(pid + "s"));
	addChild(_sprite2);
	Select(false);
	char typec = id[1];
	char teamc = id[0];
	_chessteam = teamc;
	_chesstype = typec;

 }

bool Chess::Select(bool selected)
{
	if (!selected) {
		_sprite->setVisible(true);
		_sprite2->setVisible(false);
	}
	else {
		_sprite->setVisible(false);
		_sprite2->setVisible(true);
	}
	return true;
}
