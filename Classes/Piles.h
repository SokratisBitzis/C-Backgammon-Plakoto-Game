#ifndef PILES_H
#define PILES_H

class Piles{
	private:
		int Pile[14][3];
		//Pile[ID][0] is Dominance, 1 for player 1, 2 for player 2 and 0 for being empty
		//Pile[ID][1] is Bottom Checker, 1 for player 1, 2 for player 2 and 0 for being empty
		//Pile[ID][2] is Size, number of checkers the pile has
	public:
		
		void Initiate();//sets the piles to starting positions
		
		void Reduce(int ID);
		
		void Increase(int ID);
		 
		void SetDominance(int ID, int dominance);
		
		void SetBottom(int ID, int bottom);
		
		void SetSize(int ID, int size);
		
		int GetDominance(int ID);
		
		int GetBottom(int ID);
		
		int GetSize(int ID);
		
};

#endif
