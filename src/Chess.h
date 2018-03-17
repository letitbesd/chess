#ifndef _CHESS_H_
#define _CHESS_H_
#endif // _CHESS_H_
using namespace std;
using namespace oxygine;

class Chess : public oxygine::Actor
{
public:
	string id;
	//static Resources & theGameResources;
	Chess(string pid) ;
	bool Select(bool selected);
	int		getChessType() const { return _chesstype; } 
	int		getChessTeam() const { return _chessteam; } 
private:
	oxygine::spSprite _sprite;
	oxygine::spSprite _sprite2;
	int _chesstype;
	int _chessteam;
};