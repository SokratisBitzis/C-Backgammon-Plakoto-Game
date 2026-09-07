#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "Piles.h"
#include "Dice.h"
#include "ScreenFunctions.h"
#include "MovementCollection.h"
#include "Strategy.h"

using namespace std;

void Strategy::InitializeStrategy(){//if even after the searching for the best action gives back -1 values, no action can be made
	Stage=0;
	Bchoice[0]=-1;
	Bchoice[1]=-1;
	Bchoice[2]=-1;
}

void Strategy::FindLiabilities(Piles &piles){
	int L=0;
	for(int i=0;i<12;i++){
		if(piles.GetDominance(i)==1&&piles.GetBottom(i)==2){
			L++;
		}
	}
	Liabilities=L;
}

void Strategy::FindPrisoners(Piles &piles){
	int P=0;
	for(int i=0;i<12;i++){
		if(piles.GetDominance(i)==2&&piles.GetBottom(i)==1){
			P++;
		}
	}
	Prisoners=P;
}

void Strategy::FindStage(Piles &piles){
	int n=0;
	int m=0;
	for(int i=11;i>5;i--){
		if(piles.GetDominance(i)==2){
			if(piles.GetBottom(i)==2){
				n=n+piles.GetSize(i);
			}
			else{
				n=n+piles.GetSize(i)-1;
			}
		}
		else if(piles.GetDominance(i)==1){
			if(piles.GetBottom(i)==2){
				n=n+1;
			}
		}
	}
	if(n!=0){
		Stage=1;
	}
	else{
		for(int i=5;i>2;i--){
			if(piles.GetDominance(i)==2){
				if(piles.GetBottom(i)==2){
					m=m+piles.GetSize(i);
				}
				else{
					m=m+piles.GetSize(i)-1;
				}
			}
			else if(piles.GetDominance(i)==1){
				if(piles.GetBottom(i)==2){
					m=m+1;
				}
			}
		}
		if(m!=0){
			Stage=2;
		}
		else{
			Stage=3;
		}
	}
}

void Strategy::BestChoice(Piles &piles, Dice &dice){
	InitializeStrategy();//we need to initialize otherwise the old best moves and stages might remain
	vector<array<int, 4>> Moves;//vector containing all possible moves for each time. The 3 first values are the same as the Bchoice values, but the 4th value is the actions rating from a strategic point
	Moves.push_back({-1,-1,-1,-1});//for initialisation	
	int td[4];
	td[0]=dice.GetDice(0);
	td[1]=dice.GetDice(1);
	td[2]=dice.GetDice(2);
	td[3]=dice.GetDice(3);
	int dcleft=dice.GetRemains();
	int dcdouble=dice.GetDouble();
	FindStage(piles);
	FindPrisoners(piles);
	FindLiabilities(piles);
	for(int i=11;i>-1;i--){//finding choices and rating them
		if(piles.GetDominance(i)==2){//only then can any action be made
			if(CanCollect(piles,dice,2)&&i<3){//when collection possible
				bool SpecialCollection1=(i==1&&dice.FindDice(3)&&piles.GetDominance(2)!=2);//a special case when we can collect from position 1 with dice>2
				bool SpecialCollection0=(i==0&&(dice.FindDice(3)||dice.FindDice(2))&&piles.GetDominance(1)!=2&&piles.GetDominance(2)!=2);//a special case when we can collect from position 0 with dice>1
				if(dice.FindDice(i+1)||SpecialCollection1||SpecialCollection0){//up untill this point we have ensured that we can in fact collect from this pile
					int rating=0;
					//rate collection
					rating=i+7;
					if(piles.GetBottom(i)==1){
						rating-=(7-piles.GetSize(i));
					}
					//rating complete
					Moves.push_back({1,i,13,rating});
				}
			}
			else if(CanMove(piles,dice,2)){//make sure to programm a movement that favors collection in the next round
				if(dcdouble){//for double roll
					for(int j=0;j<dcleft;j++){
						if((i-(j+1)*dcdouble)>=0&&(piles.GetDominance(i-(j+1)*dcdouble)==2||piles.GetSize(i-(j+1)*dcdouble)<2)){
							int to=i-(j+1)*dcdouble;
							int rating=30;
							//rate movement
							rating-=5*j;
							rating+=2*piles.GetSize(i);
							if(piles.GetDominance(to)==1&&piles.GetSize(to)==1){//capture
								if(to<5)rating+=15;
								else if(Stage==1)rating+=(10-Prisoners);
								else if(Stage==2)rating+=(14-Prisoners);
								else if(Stage==3)rating+=(10-Prisoners);
							}
							if(piles.GetDominance(to)==2&&piles.GetSize(to)==1){//create tower
								if(Liabilities>2)rating+=(10+Liabilities);
								else if(Stage==1)rating+=10;
								else if(Stage==2)rating+=8;
							}
							if(piles.GetSize(i)==2){//create liability on origin
								if(Liabilities>2)rating-=(13+Liabilities);
								else if(Stage==1)rating-=12;
								else if(Stage==2)rating-=10;
							}
							if(piles.GetSize(to)==0){//create liability on destination
								if(Liabilities>2)rating-=(12+Liabilities);
								else if(Stage==1)rating-=11;
								else if(Stage==2)rating-=8;
							}
							if(i<5&&piles.GetBottom(i)==1&&piles.GetSize(i)==2&&Stage<3)rating-=14;
							//rating complete
							Moves.push_back({0,i,i-(j+1)*dcdouble,rating});
						}
						else{//no movement from this point forward can be done
							j=dcleft;
						}
					}
				}
				else{//for normal roll
					for(int j=0;j<4;j++){
						int k,q;
						if(j==0&&td[0]!=0){k=0;q=2;}
						else if(j==1&&td[1]!=0){k=1;q=2;}
						else if(j==2&&td[0]!=0&&td[1]!=0){k=0;q=1;}
						else if(j==3&&td[0]!=0&&td[1]!=0){k=1;q=0;}
						else continue;
						if((i-td[k]-td[q])>=0&&(piles.GetDominance(i-td[k]-td[q])==2||piles.GetSize(i-td[k]-td[q])<2)){
							int to=i-td[k]-td[q];
							int rating=30;
							//rate movement
							if(j>1)rating-=10;
							rating+=2*piles.GetSize(i);
							if(piles.GetDominance(to)==1&&piles.GetSize(to)==1){//capture
								if(to<5)rating+=15;
								else if(Stage==1)rating+=(10-Prisoners);
								else if(Stage==2)rating+=(14-Prisoners);
								else if(Stage==3)rating+=(10-Prisoners);
							}
							if(piles.GetDominance(to)==2&&piles.GetSize(to)==1){//create tower
								if(Liabilities>2)rating+=(10+Liabilities);
								else if(Stage==1)rating+=10;
								else if(Stage==2)rating+=8;
							}
							if(piles.GetSize(i)==2){//create liability on origin
								if(Liabilities>2)rating-=(13+Liabilities);
								else if(Stage==1)rating-=12;
								else if(Stage==2)rating-=10;
							}
							if(piles.GetSize(to)==0){//create liability on destination
								if(Liabilities>2)rating-=(12+Liabilities);
								else if(Stage==1)rating-=11;
								else if(Stage==2)rating-=8;
							}
							if(i<5&&piles.GetBottom(i)==1&&piles.GetSize(i)==2&&Stage<3)rating-=14;
							//rating complete
							Moves.push_back({0,i,i-td[k]-td[q],rating});
						}
					}
				}
			}
		}
	}
	int max[2]={0,0};//[0] is the max rating, [1] is the position of the choice in the vector
	for(int i=1;i<Moves.size();i++){//selecting best choice
		if(Moves.at(i)[3]>max[0]){
			max[0]=Moves.at(i)[3];
			max[1]=i;
		}
	}	
	int j=max[1];
	Bchoice[0]=Moves.at(j)[0];
	Bchoice[1]=Moves.at(j)[1];
	Bchoice[2]=Moves.at(j)[2];
}

void Strategy::Act(Piles &piles, Dice &dice){
	cout<<endl<<"Player 2's turn"<<endl;
	cout<<endl<<"Rolling the dice . . ."<<endl<<endl;
	for(int t=0;t<222222222;t++){}
	dice.Roll();
	dice.PrintDice();
	if(!CanMove(piles,dice,2)&&!CanCollect(piles,dice,2)){
		cout<<"No action can be taken"<<endl;
		return;
	}
	else{
		cout<<endl<<"Possibility of action verified. Initializing strategic calculations . . ."<<endl;
		for(int t=0;t<222222222;t++){}
		Screen(piles,dice);
		int limit=4-dice.FindDice(0);
		for(int i=0;i<limit;i++){
			for(int t=0;t<434343434;t++){}
			BestChoice(piles,dice);
			// debugging tool cout<<endl<<endl<<"HEY"<<endl<<endl;
			if(Bchoice[0]==0){//move
				if(dice.FindDice(Bchoice[1]-Bchoice[2])){
					Move(piles,dice,2,Bchoice[1]+1,Bchoice[2]+1,1);
					dice.UseDice(Bchoice[1]-Bchoice[2]);
				}
				else{
					if(dice.GetDouble()){
						int mul=(Bchoice[1]-Bchoice[2])/dice.GetDouble();
						int orgn=Bchoice[1]+1;
						int dest=0;
						for(int k=0;k<mul;k++){
							dest=Bchoice[1]+1-(k+1)*dice.GetDouble();
							Move(piles,dice,2,orgn,dest,1);
							orgn=dest;
							dice.UseDice(dice.GetDouble());
						}
					}
					else{
						if(ValidateMovement(piles,dice,2,Bchoice[1]+1,Bchoice[1]+1-dice.GetDice(0))){
							Move(piles,dice,2,Bchoice[1]+1,Bchoice[1]+1-dice.GetDice(0),1);
							Move(piles,dice,2,Bchoice[1]+1-dice.GetDice(0),Bchoice[2]+1,1);
						}
						else{
							Move(piles,dice,2,Bchoice[1]+1,Bchoice[1]+1-dice.GetDice(1),1);
							Move(piles,dice,2,Bchoice[1]+1-dice.GetDice(1),Bchoice[2]+1,1);
						}
						dice.UseDiceByID(0);
						dice.UseDiceByID(1);
					}
				}
				Screen(piles,dice);
			}
			else if(Bchoice[0]==1){//collect
				Collect(piles,dice,2,Bchoice[1]+1);
				Screen(piles,dice);
			}
		}
	}
}

