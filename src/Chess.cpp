#include "oxygine-framework.h"
#include <functional> 
#include "Actor.h"
#include <stdio.h>
#include "Chess.h"
using namespace oxygine;
	Chess:Chess(const std::string & id)
	{
		std::string  id2 = id + "s";
		_sprite = new  Sprite;
		_sprite2 = new Sprite;
		//_sprite->setResAnim(gameResources.getResAnim(id));
		addChild(_sprite);
		//_sprite2->setResAnim(gameResources.getResAnim(id2));
		addChild(_sprite2);
		_sprite2->setVisible(false);


		//EventCallback cb = CLOSURE(this, &MainActor::buttonClicked);
		//addEventListener(TouchEvent::CLICK, cb);

#ifdef CLOSURE_FUNCTION //if your compiler supports lambda

		addEventListener(TouchEvent::CLICK, [](Event * e)->void
		{
			log::messageln(" clicked");
		});
#endif
	} 