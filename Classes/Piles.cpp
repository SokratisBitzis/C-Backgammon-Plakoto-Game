#include <iostream>
#include "Piles.h"

using namespace std;

void Piles::Initiate(){//sets the piles to starting positions
	for(int i=0;i<14;i++){
		if(i==0){
			Pile[i][0]=1;
			Pile[i][1]=1;
			Pile[i][2]=7;
		}
		else if(i==11){
			Pile[i][0]=2;
			Pile[i][1]=2;
			Pile[i][2]=7;
		}
		else if(i==12){
			Pile[i][0]=1;
			Pile[i][1]=1;
			Pile[i][2]=0;
		}
		else if(i==13){
			Pile[i][0]=2;
			Pile[i][1]=2;
			Pile[i][2]=0;
		}
		else{
			Pile[i][0]=0;
			Pile[i][1]=0;
			Pile[i][2]=0;
		}
	}
}

void Piles::Reduce(int ID){
	Pile[ID][2]--;
}

void Piles::Increase(int ID){
	Pile[ID][2]++;
}

void Piles::SetDominance(int ID, int dominance){
	Pile[ID][0]=dominance;
}

void Piles::SetBottom(int ID, int bottom){
	Pile[ID][1]=bottom;
}

void Piles::SetSize(int ID, int size){
	Pile[ID][2]=size;
}

int Piles::GetDominance(int ID){
	return Pile[ID][0];
}

int Piles::GetBottom(int ID){
	return Pile[ID][1];
}

int Piles::GetSize(int ID){
	return Pile[ID][2];
}

