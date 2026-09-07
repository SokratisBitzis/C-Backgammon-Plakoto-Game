#include <iostream>
#include "Piles.h"
#include "Dice.h"
#include "MovementCollection.h"

using namespace std;

bool CanCollect(Piles &piles, Dice &dice, int PID){//checks if a player is able to collect in general
	int count=0;
	int possibilities=0;
	if(PID==1){//for player 1
		for(int i=9;i<12;i++){//player 1 goes from 0 to 11
			if(piles.GetDominance(i)==1){//a captured checker cannot be collected
				if(piles.GetBottom(i)==1){
					count=count+piles.GetSize(i);
				}
				else{
					count=count+piles.GetSize(i)-1;
				}
				if(dice.FindDice(12-i)){//if the dice don't favor the player, no collection can be made
					possibilities++;
				}
				else if(i==10&&dice.FindDice(3)&&piles.GetDominance(9)!=1){
					possibilities++;
				}
				else if(i==11&&(dice.FindDice(3)||dice.FindDice(2))&&piles.GetDominance(9)!=1&&piles.GetDominance(10)!=1){
					possibilities++;
				}
			}
		}
	}
	else if(PID==2){//for player 2
		for(int i=0;i<3;i++){
			if(piles.GetDominance(i)==2){
				if(piles.GetBottom(i)==2){
					count=count+piles.GetSize(i);
				}
				else{
					count=count+piles.GetSize(i)-1;
				}
				if(dice.FindDice(i+1)){
					possibilities++;
				}
				else if(i==1&&dice.FindDice(3)&&piles.GetDominance(2)!=2){
					possibilities++;
				}
				else if(i==0&&(dice.FindDice(3)||dice.FindDice(2))&&piles.GetDominance(1)!=2&&piles.GetDominance(2)!=2){
					possibilities++;
				}
			}
		}
	}
	if(count==7-piles.GetSize(11+PID)&&possibilities){
		return true;
	}
	else{
		return false;
	}
}

bool CanMove(Piles &piles, Dice &dice, int PID){//checks if a player can make any sort of movement
	int counter=0;
	if(PID==1){
		for(int i=0;i<12;i++){
			if(piles.GetDominance(i)==1){
				for(int j=0;j<4;j++){
					int temp=dice.GetDice(j);
					if(temp&&i+temp<12&&(piles.GetDominance(i+temp)!=2||piles.GetSize(i+temp)<=1))counter++;
				}
			}
		}
	}
	else if(PID==2){
		for(int i=0;i<12;i++){
			if(piles.GetDominance(i)==2){
				for(int j=0;j<4;j++){
					int temp=dice.GetDice(j);
					if(temp&&i-temp>=0&&(piles.GetDominance(i-temp)!=1||piles.GetSize(i-temp)<=1))counter++;
				}
			}
		}
	}
	if(counter)return true;
	else return false;
}

void Move(Piles &piles, Dice &dice, int PID, int from, int to, int st){//makes the movement requested
	if(PID==1){
		if(piles.GetSize(to-1)==0){//the destination pile is initially empty
			piles.SetBottom(to-1,1);
			piles.SetDominance(to-1,1);
		}
		else if(piles.GetSize(to-1)==1){
			if(piles.GetDominance(to-1)==2){//the destination pile has 1 enemy checker
				piles.SetDominance(to-1,1);
			}
		}
		if(piles.GetSize(from-1)==2&&piles.GetBottom(from-1)==2){
			piles.SetDominance(from-1,2);
		}
		dice.UseDice(to-from);
	}
	else if(PID==2){
		if(piles.GetSize(to-1)==0){//the destination pile is initially empty
			piles.SetBottom(to-1,2);
			piles.SetDominance(to-1,2);
		}
		else if(piles.GetSize(to-1)==1){
			if(piles.GetDominance(to-1)==1){//the destination pile has 1 enemy checker
				piles.SetDominance(to-1,2);
			}
		}
		if(piles.GetSize(from-1)==2&&piles.GetBottom(from-1)==1){
			piles.SetDominance(from-1,1);
		}
		if(st==0)dice.UseDice(from-to);
	}
	if(piles.GetSize(from-1)==1){
		piles.SetBottom(from-1,0);
		piles.SetDominance(from-1,0);
	}
	piles.Reduce(from-1);
	piles.Increase(to-1);
}

void Collect(Piles &piles, Dice &dice, int PID, int what){//makes the collection requested
	if(PID==1){
		if(piles.GetSize(what-1)==2&&piles.GetBottom(what-1)==2){
			piles.SetDominance(what-1,2);
		}
		if(dice.FindDice(13-what)){
			dice.UseDice(13-what);
		}
		else{
			if(what==11&&piles.GetDominance(10-1)!=1){
				dice.UseDice(3);
			}
			else if(what==12&&piles.GetDominance(10-1)!=1&&piles.GetDominance(11-1)!=1){
				if(dice.FindDice(3)){
					dice.UseDice(3);
				}
				else if(dice.FindDice(2)){
					dice.UseDice(2);
				}
			}		
		}
		piles.Increase(12);
		if(piles.GetSize(what-1)==2&&piles.GetBottom(what-1)==2){
			piles.SetDominance(what-1,2);
		}
	}
	else if(PID==2){
		if(piles.GetSize(what-1)==2&&piles.GetBottom(what-1)==1){
			piles.SetDominance(what-1,1);
		}
		if(dice.FindDice(what)){
			dice.UseDice(what);
		}
		else{
			if(what==2&&piles.GetDominance(3-1)!=2){
				dice.UseDice(3);
			}
			else if(what==1&&piles.GetDominance(2-1)!=2&&piles.GetDominance(3-1)!=2){
				if(dice.FindDice(3)){
					dice.UseDice(3);
				}
				else if(dice.FindDice(2)){
					dice.UseDice(2);
				}
			}	
		}
		piles.Increase(13);
		if(piles.GetSize(what-1)==2&&piles.GetBottom(what-1)==1){
			piles.SetDominance(what-1,1);
		}
	}
	if(piles.GetSize(what-1)==1){
		piles.SetBottom(what-1,0);
		piles.SetDominance(what-1,0);
	}
	piles.Reduce(what-1);
}

bool ValidateMovement(Piles &piles, Dice &dice, int PID, int from, int to){//checks if the movement requested is valid
	if(PID==1){
		if(dice.FindDice((to-from))&&piles.GetDominance(from-1)==1){//player 1 moves from 0 to 11
			if(piles.GetDominance(to-1)!=2||piles.GetSize(to-1)<=1){
				return true;
			}else return false;
		}else return false;
	}
	else if(PID==2){
		if(dice.FindDice((from-to))&&piles.GetDominance(from-1)==2){//player 2 moves from 11 to 0
			if(piles.GetDominance(to-1)!=1||piles.GetSize(to-1)<=1){
				return true;
			}else return false;
		}else return false;
	}
}

bool ValidateCollection(Piles &piles, Dice &dice, int PID, int what){//checks if the collection requested is valid
	if(PID==1){
		if(dice.FindDice(13-what)&&piles.GetDominance(what-1)==1){//the piles will appear to start from 1, not 0
			return true;
		}
		else if(piles.GetDominance(what-1)==1){
			if(what==11&&dice.FindDice(3)&&piles.GetDominance(10-1)!=1){
				return true;
			}
			else if(what==12&&(dice.FindDice(3)||dice.FindDice(2))&&piles.GetDominance(10-1)!=1&&piles.GetDominance(11-1)!=1){
				return true;
			}
		}
		else return false;
	}
	else if(PID==2){
		if(dice.FindDice(what)&&piles.GetDominance(what-1)==2){
			return true;
		}
		else if(piles.GetDominance(what-1)==2){
			if(what==2&&dice.FindDice(3)&&piles.GetDominance(3-1)!=2){
				return true;
			}
			else if(what==1&&(dice.FindDice(3)||dice.FindDice(2))&&piles.GetDominance(2-1)!=2&&piles.GetDominance(3-1)!=2){
				return true;
			}
		}
		else return false;
	}
}
