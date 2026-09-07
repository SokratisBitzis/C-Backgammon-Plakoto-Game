#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include <ctime>
#include "Piles.h"
#include "Dice.h"
#include "ScreenFunctions.h"
#include "MovementCollection.h"
#include "Strategy.h"

using namespace std;

int PlayerChoice(Piles &piles, Dice &dice, int PID){//receives player's input and acts on it
	cout<<endl<<"Player "<<PID<<"'s turn"<<endl;
	for(int i=0;i>-1;i++){
		cout<<"Press e to exit or any other key to roll the dice"<<endl;
		string temp;
		getline(cin,temp);
		if(temp=="e"){
			return 1;
		}
		else if(temp!="e"){
			dice.Roll();
			i=-10;
		}
	}
	Screen(piles,dice);
	int limit=4-dice.FindDice(0);
	for(int i=0;i<limit;i++){
		if(!CanMove(piles,dice,PID)&&!CanCollect(piles,dice,PID)){
			cout<<"No action can be taken"<<endl;
			return 2;
		}
		string input;
		if(CanCollect(piles,dice,PID)){
			cout<<endl<<"Press C to collect or any other key to make a move"<<endl;
			getline(cin,input);
			if(input=="C"){
				for(int j=0;j>-1;j++){
					cout<<"Enter the position you want to collect from"<<endl;
					string target;
					getline(cin,target);
					if(target!="1"&&target!="2"&&target!="3"&&target!="4"&&target!="5"&&target!="6"&&target!="7"&&target!="8"&&target!="9"&&target!="10"&&target!="11"&&target!="12"){
						cout<<"No can do"<<endl;
					}
					else if(!ValidateCollection(piles,dice,PID,stoi(target))){
						cout<<"Don't touch that!"<<endl;
					}
					else if(ValidateCollection(piles,dice,PID,stoi(target))){
						Collect(piles,dice,PID,stoi(target));
						Screen(piles,dice);
						j=-10;
					}
				}
				continue;
			}
		}
		if(CanMove(piles,dice,PID)){
			for(int j=0;j>-1;j++){
				string from, to;
				for(int k=0;k>-1;k++){
					cout<<"Enter the position you want to start from"<<endl;
					getline(cin,from);
					if((from!="1"&&from!="2"&&from!="3"&&from!="4"&&from!="5"&&from!="6"&&from!="7"&&from!="8"&&from!="9"&&from!="10"&&from!="11"&&from!="12")||piles.GetDominance(stoi(from)-1)!=PID){
						cout<<"No can do"<<endl;
					}
					else break;
				}
				for(int g=0;g>-1;g++){
					cout<<"Enter the position you want to end to"<<endl;
					getline(cin,to);
					if((to!="1"&&to!="2"&&to!="3"&&to!="4"&&to!="5"&&to!="6"&&to!="7"&&to!="8"&&to!="9"&&to!="10"&&to!="11"&&to!="12")||(to==from)){
						cout<<"No can do"<<endl;
					}
					else break;
				}
				if(!ValidateMovement(piles,dice,PID,stoi(from),stoi(to))){
					cout<<"You can't make that movement"<<endl;
				}
				else if(ValidateMovement(piles,dice,PID,stoi(from),stoi(to))){
					Move(piles,dice,PID,stoi(from),stoi(to),0);
					Screen(piles,dice);
					break;
				}
			}
		}
	}
	return 0;
}

void MultiPlayer(Piles &piles, Dice &dice){
	for(int i=0;i>-1;i++){
		if(piles.GetSize(12)==7){
			if(piles.GetSize(12)==7&&piles.GetSize(13)==0){
				cout<<endl<<"Player 1 won before player 2 collected, what more is there to say?"<<endl;
				i=-10;
				break;	
			}
			else{
				cout<<endl<<"Player 1 won, sucks to be you player 2"<<endl;
				i=-10;
				break;
			}
		}
		else if(piles.GetSize(13)==7){
			if(piles.GetSize(13)==7&&piles.GetSize(12)==0){
				cout<<endl<<"Player 2 won before player 1 collected, what more is there to say?"<<endl;
				i=-10;
				break;
			}
			else{
				cout<<endl<<"Player 2 won, sucks to be you player 1"<<endl;
				i=-10;
				break;	
			}
		}
		if(i%2==0&&i>-1){//call player 1
			int temp1;
			temp1=PlayerChoice(piles,dice,1);
			if(temp1==1)break;//in case a player wants to terminate the game midway
		}
		else if(i%2==1&&i>-1){//call player 2
			int temp2;
			temp2=PlayerChoice(piles,dice,2);
			if(temp2==1)break;
		}
	}
}

void SinglePlayer(Piles &piles, Dice &dice, Strategy &strategy){
	for(int i=0;i>-1;i++){
		if(piles.GetSize(12)==7){
			if(piles.GetSize(12)==7&&piles.GetSize(13)==0){
				cout<<endl<<"Player 1 won before player 2 collected, what more is there to say?"<<endl;
				i=-10;
				break;	
			}
			else{
				cout<<endl<<"Player 1 won, sucks to be you player 2"<<endl;
				i=-10;
				break;
			}
		}
		else if(piles.GetSize(13)==7){
			if(piles.GetSize(13)==7&&piles.GetSize(12)==0){
				cout<<endl<<"Player 2 won before player 1 collected, what more is there to say?"<<endl;
				i=-10;
				break;
			}
			else{
				cout<<endl<<"Player 2 won, sucks to be you player 1"<<endl;
				i=-10;
				break;	
			}
		}
		if(i%2==0&&i>-1){//call player 1
			int temp1;
			temp1=PlayerChoice(piles,dice,1);
			if(temp1==1)break;//in case a player wants to terminate the game midway
		}
		else if(i%2==1&&i>-1){//call player 2
			strategy.Act(piles,dice);
		}
	}
}

int main(){
	
	Wellcome(); 
	
	Piles piles;
	Dice dice;
	Strategy strategy;
	string Command;
	
	do{
		piles.Initiate();
		dice.Initiate();
		cout<<endl<<"Press 1 to play single player, 2 to play multiplayer, 3 to read the tutorial and 4 to terminate the program"<<endl;
		getline(cin,Command);
		if(Command=="1"){
			SinglePlayer(piles,dice,strategy);
		}
		else if(Command=="2"){
			MultiPlayer(piles,dice);
		}
		else if(Command=="3"){
			Tutorial();
		}
		else if(Command=="4"){
			cout<<endl<<"Goodbye"<<endl;
			break;
		}
		else {
			cout<<"You've done goofed"<<endl;
		}
	}while(Command!="4");
	
	return 0;
}
