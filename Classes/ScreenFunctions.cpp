#include <iostream>
#include "Piles.h"
#include "Dice.h"
#include "ScreenFunctions.h"

using namespace std;

void Wellcome(){
	cout<<"Wellcome"<<endl;
}

void Tutorial(){
	cout<<endl<<"Player 1 allways plays first, and after that the moves are alternating"<<endl;
	cout<<"Player 1 has the Q sign, while player 2 has the G sign"<<endl;
	cout<<"The goal is for each player to get to the other player's starting side and then collect all the checkers'"<<endl;
	cout<<"A lone checker can be captured by another player's checker, thus being unable to move, or be collected'"<<endl;
	cout<<"A tower of checkers cannot be captured"<<endl;
	cout<<"You can only move according to your dice"<<endl;
	cout<<"You get 2 actions each turn (move or collect) if your dice are different, or 4 if your dice are the same"<<endl;
	cout<<"Good luck"<<endl;
}

void Row(Piles &piles, int ID, int i){
	if(i==0){
		if(piles.GetBottom(ID)==1&&piles.GetSize(ID)>0)cout<<"Q";
		else if(piles.GetBottom(ID)==2&&piles.GetSize(ID)>0)cout<<"G";
		else cout<<" ";
	}
	else if(i<piles.GetSize(ID)){
		if(piles.GetDominance(ID)==1)cout<<"Q";
		else if(piles.GetDominance(ID)==2)cout<<"G";
	}else cout<<" ";
}

void Screen(Piles &piles, Dice &dice){
	cout<<endl;
	cout<<" + - + -------- + ------- +"<<endl;
	cout<<" | X | 1  2  3  | 4  5  6 |"<<endl;
	for(int i=0;i<7;i++){
		for(int j=0;j<27;j++){
			if(j==1||j==5||j==16||j==26)cout<<"|";
			else if(j==3)Row(piles,12,i);
			else if(j==7)Row(piles,0,i);
			else if(j==10)Row(piles,1,i);
			else if(j==13)Row(piles,2,i);
			else if(j==18)Row(piles,3,i);
			else if(j==21)Row(piles,4,i);
			else if(j==24)Row(piles,5,i);
			else cout<<" ";
		}
		cout<<endl;
	}
	cout<<" + - + -------- + ------- +"<<endl;
	for(int i=6;i>=0;i--){
		for(int j=0;j<27;j++){
			if(j==1||j==5||j==16||j==26)cout<<"|";
			else if(j==3)Row(piles,13,i);
			else if(j==7)Row(piles,11,i);
			else if(j==10)Row(piles,10,i);
			else if(j==13)Row(piles,9,i);
			else if(j==18)Row(piles,8,i);
			else if(j==21)Row(piles,7,i);
			else if(j==24)Row(piles,6,i);
			else cout<<" ";
		}
		cout<<endl;
	}
	cout<<" | X | 12 11 10 | 9  8  7 |"<<endl;
   	cout<<" + - + -------- + ------- +"<<endl;
	cout<<endl;
	dice.PrintDice();
}
