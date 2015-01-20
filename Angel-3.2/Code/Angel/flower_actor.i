%module angel
%{
#include "../../Actors/FlowerActor.h"
%}

class FlowerActor : public PhysicsActor
{
public:
	FlowerActor();
	~FlowerActor();
	FlowerActor(char *q, char *name);
	void answered();
	void ReceiveMessage(Message *m);
	void SetQuestion(char *q);
	void SetAnswer(bool b);
	char *question;
	bool answer;
};
