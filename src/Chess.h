#ifndef _CHESS_H_
#define _CHESS_H_
#endif // _CHESS_H_



class Chess : public oxygine::Sprite
{
public:
	Chess(std::string id);
protected:
	oxygine::spSprite _sprite;
	oxygine::spSprite _sprite2;
};