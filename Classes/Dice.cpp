#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include "Dice.h"

using namespace std;

void Dice::Initiate(){//sets all dice to 0
	DoubleDc=0;
	Remains=0;
	Dc[0]=0;
	Dc[1]=0;
	Dc[2]=0;
	Dc[3]=0;
}

int Dice::GetDice(int ID){
	return Dc[ID];
}

int Dice::GetDouble(){
	return DoubleDc;
}

int Dice::GetRemains(){
	return DoubleDc;
}

void Dice::Roll(){
	int r1,r2;
	srand(time(0));
	r1=(rand()%8);
	if(r1==2){//if r1==2 make sure the roll is double
		for(int i=0;i>-1;i++){
			r2=(rand()%100);
			if(r2==1||r2==2||r2==3){
				Dc[0]=r2;
				Dc[1]=r2;
				Dc[2]=r2;
				Dc[3]=r2;
				DoubleDc=r2;
				Remains=4;
				i=-10;
			}
		}
	}
	else{//if r1!=2 make sure the roll is normal
		int temp;
		for(int i=0;i>-1;i++){
			r2=(rand()%100);
			if(r2==1||r2==2||r2==3){
				Dc[0]=r2;
				temp=r2;
				i=-10;
			}
		}
		for(int i=0;i>-1;i++){
			r2=(rand()%100);
			if(r2!=temp){
				if(r2==1||r2==2||r2==3){
				Dc[1]=r2;
				i=-10;
				}
			}
		}
		Dc[2]=0;
		Dc[3]=0;
		DoubleDc=0;
		Remains=2;
	}	
}

int Dice::FindDice(int x){//returns 0-false if the dice number requested doesn't exist, and if the number does exist, it returns the number of dice with it
	int counter=0;
	for(int i=0;i<4;i++){
		if(Dc[i]==x){
			counter++;
		}
	}
	return counter;
}

void Dice::UseDice(int x){//when a dice is to be used, the first dice to match the request is set back to zero
	for(int i=0;i<4;i++){
		if(Dc[i]==x){
			Dc[i]=0;
			i=4;
		}
	}
	Remains--;
}

void Dice::UseDiceByID(int x){
	Dc[x]=0;
	Remains--;
}

void Dice::PrintDice(){
	bool temp=false;
	if(Dc[0]||Dc[1]||Dc[2]||Dc[3]){
		temp=true;
	}
	for(int i=0;i<4;i++){
		if(temp&&i==0)cout<<" ";
		if(Dc[i]){
			cout<<"+ - ";
		}
		if(temp&&i==3)cout<<"+";
	}if(temp)cout<<endl;
	for(int i=0;i<4;i++){
		if(temp&&i==0)cout<<" ";
		if(Dc[i]){
			cout<<"| "<<Dc[i]<<" ";
		}
		if(temp&&i==3)cout<<"|";
	}if(temp)cout<<endl;
	for(int i=0;i<4;i++){
		if(temp&&i==0)cout<<" ";
		if(Dc[i]){
			cout<<"+ - ";
		}
		if(temp&&i==3)cout<<"+";
	}if(temp)cout<<endl;
}
