//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DemoScreenPhysicsActor.h"
#include <stdio.h>
#include <cstdlib>
#include <utils.h>
#include "Actors\FlowerActor.h"
#include "HoneyBee\FlowerMessage.h"
#include <cstring>
//might need to hook it up with a file path
DemoScreenPhysicsActor::DemoScreenPhysicsActor()
{
}

void DemoScreenPhysicsActor::Start()
{
	loadFile(fopen("setup.txt", "r+"));
	score = 0;
	inc = 0;
	incText = "0";
	scoreText = "Score: 0";
	incrementing = false;
	questionTime = false;
	displayTime();
	theSwitchboard.SubscribeTo(this, "QuestionTime");
	p1 = new PhysicsActor();
	//PhysicsActors have all the same attributes as regular ones...
	p1->SetSize(1.0f);
	//p1->SetColor(1.0f, 0.0f, 1.0f);
	//...but with a little bit of magic pixie dust
	p1->SetDensity(0.1f);
	p1->SetFriction(0.5f);
	p1->SetRestitution(0.0f);
	p1->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	p1->SetPosition(*(new Vector2(5, 5)));
	//added this image
	p1->SetSprite("Resources/Images/bee.png");
	p1->InitPhysics(); // Note that none of the actor's physics are being
	                   //  simulated until this call.
	theCamera.LockTo(p1, true, false, false);
	//That's the basics of what we've exposed from Box2d. There's lots
	//  more to it, though, and we encourage you to check out their
	//  documentation. http://box2d.org

	PhysicsActor *p2 = new PhysicsActor();
	p2->SetPosition(0.0f, -11.0f);
	p2->SetSize(30.0f, 5.0f);
	p2->SetColor(0.0f, 1.0f, 0.0f);
	p2->SetDensity(0); //no density (static)
	p2->SetFriction(0.9f); //little friction
	p2->InitPhysics(); 
	
	//PhysicsActor *p = (PhysicsActor*)PhysicsActor::Create("FlowerActor");
	//std::cout << p->GetSize().X;
	//FlowerActor *flower = (FlowerActor*)Actor::Create("FlowerActor");
	//std::cout << flower->GetSize().X;
	//FlowerActor *flower = new FlowerActor("123456789012345678901234567890123465789012345678901234567890", "Flower");
	//flower->SetPosition(7, 7);
	//flower->SetSize(2, 2);
	//flower->SetColor(0, 1, 0);
	//flower->SetIsSensor(true);
	//flower->SetDensity(0);
	//flower->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	//flower->InitPhysics();
	//NOTE: After you call InitPhysics, you can't directly set an Actor's
	// position or rotation -- you've turned those over to the physics engine.
	// You can't change the size, either, since that would mess up the simulation.
	vector = new Vector2(0, 100.0f);
	//theWorld.Add(flower);
	theWorld.Add(p1);
	theWorld.Add(p2);
	HUDActor *act = new HUDActor();
	//Demo housekeeping below this point.
	startTime = theWorld.GetCurrentTimeSeconds();
	#pragma region Demo Housekeeping
	TextActor *fileLoc = new TextActor("ConsoleSmall", "DemoScreenPhysicsActor.cpp");
	fileLoc->SetPosition(MathUtil::ScreenToWorld(5, 763));
	fileLoc->SetColor(.3f, .3f, .3f);
	theWorld.Add(fileLoc);
	_objects.push_back(fileLoc);
	//_objects.push_back(flower);
	_objects.push_back(p1);
	_objects.push_back(p2);
	#pragma endregion
}
void DemoScreenPhysicsActor::Update(float dt)
{
		if (theWorld.GetTimeSinceSeconds(startTime) > 5)
		theSwitchboard.Broadcast(new Message("MoveForwards"));
		displayTime();
		displayScore();
	p1->StopRotation();
	if (incrementing)
	{
		if (slower == 0)
		{
			setScore(score + 1);
			inc--;
			slower = 32;
			updateInc();
			incrementing = inc != 0;
		}
		slower--;
	}
	if (questionTime)
	{
		displayQuestion();
		if (theInput.IsKeyDown('1'))
		{
			curFlower->answered();
			if (curFlower->answer)
			{
				inc = 50;
				slower = 2048;
				updateInc();
				incrementing = true;
			}
			questionTime = false;
			p1->unfreeze();
		}
		else if (theInput.IsKeyDown('2'))
		{
			curFlower->answered();
			if (!curFlower->answer)
			{
				inc = 50;
				updateInc();
				slower = 2048;
				incrementing = true;
			}
			questionTime = false;
			p1->unfreeze();
		}
	}
	else
	{
		if (theInput.IsKeyDown('d'))
		{
			p1->ApplyForce(Vector2(50*dt, 0), Vector2(0.0));
			if (p1->GetRotation()>-45)
				p1->ApplyTorque(-.1);
			//vector = &(vector->Rotate(*vector, 3.1415926));
			//std::cout << "x= "<< vector->X << "\ny= " << vector->Y;
			//free(temp);
		}
		if (theInput.IsKeyDown('a'))
		{
			//	Vector2 *temp = vector;
			p1->ApplyForce(Vector2(-50*dt, 0), Vector2(0.0));
			if (p1->GetRotation() < 45)
				p1->ApplyTorque(.1);
			//vector = &(vector->Rotate(*vector, -(.01*dt)));
			//std::cout << "x= " << vector->X << "\ny= " << vector->Y << "\n";
			//	free(temp);
		}
		if (theInput.IsKeyDown('w'))
		{
			//punch it upwards
			p1->ApplyForce(*vector * dt, Vector2());
		}
	}
}
void DemoScreenPhysicsActor::ReceiveMessage(Message* message)
{
	FlowerMessage *mess = (FlowerMessage*)message;
	question.clear();
	question.append(mess->question);
	questionTime = true;
	curFlower = mess->flower;
	p1->freeze();
}
void DemoScreenPhysicsActor::setScore(int i)
{
	scoreText.empty();
	scoreText = "Score: ";
	score = i;
	char p[10] = { 0 };
	_itoa_s(score, p, 10);
	scoreText.append(p);
}
void DemoScreenPhysicsActor::updateInc()
{
	incText.clear();
	incText.append("+");
	char p[10] = { 0 };
	_itoa_s(inc, p, 10);
	incText.append(p);
}
void DemoScreenPhysicsActor::displayScore()
{
	DrawGameText(scoreText, "Console", theCamera.GetWindowWidth()-150, 50, 0);
	if (incrementing)
	{
		DrawGameText(incText, "Console", theCamera.GetWindowWidth() - 78, 75, 0);
	}
}
void DemoScreenPhysicsActor::displayTime()
{
	char p[15] = { 0 };
	_itoa_s(120 - theWorld.GetTimeSinceSeconds(startTime), p, 10);
	DrawGameText(p, "Console", 50, 50, 0);
}
void DemoScreenPhysicsActor::displayQuestion()
{
	DrawGameText(question, "Console", theCamera.GetWindowWidth() / 2 - question.length()*6, 100, 0);
}
void DemoScreenPhysicsActor::loadFile(FILE *infile)
{
	//std::cout << "loading";
	int temp = 1, temp2 = 1, numStuff=0;
	String s = "";
	FlowerActor *f;
	char *taco = new char[20];
	if (infile == nullptr)
		std::cout << "failed to load config.txt";
	else
	{
		fscanf(infile, "%d", &numStuff);
		//std::cout << numStuff;
		for (int i = 0; i < numStuff; i++)
		{
			s.clear();
			free(taco);
			taco = new char[20];
			//fprintf(infile, "fuck you");
			fscanf(infile, "%s", taco);
			while (*taco != '~')
			{
				s.append(taco);
				s.append(" ");
				free(taco);
				taco = new char[30];
				fscanf(infile, "%s", taco);
			}
			//std::cout << s << "\n";
				f = new FlowerActor(s.c_str(), "Flower");
				fscanf(infile, "%s", taco);
				free(taco);
				taco = new char[30];
				fscanf(infile, "%d", &temp);
				f->SetAnswer(temp);
				fscanf(infile, "%s", taco);
				free(taco);
				taco = new char[30];
				fscanf(infile, "%d", &temp);
				fscanf(infile, "%d", &temp2);
				//std::cout << "\nsize" << temp << " " << temp2;
				f->SetSize(temp, temp2);
				fscanf(infile, "%s", taco);
				free(taco);
				taco = new char[30];
				fscanf(infile, "%d", &temp);
				fscanf(infile, "%d", &temp2);
				f->SetPosition(temp, temp2);
				f->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
				f->SetDensity(0);
				f->SetIsSensor(true);
				fscanf(infile, "%s", taco);
				free(taco);
				taco = new char[30];
				fscanf(infile, "%s", taco);
				//std::cout << taco;
				f->SetSprite(taco);
				//std::cout << f->question;
				f->InitPhysics();
				_objects.push_back(f);
				theWorld.Add(f);
		}
	}
}