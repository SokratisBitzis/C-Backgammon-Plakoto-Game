#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy
{
	private:
		int Stage;//refers to where the magority of checkers are so that a fitting strategy can be followed. There will be 3 stages according to the mass number of checkers (12-7 , 6-1 destination unfull, 3-1 destination full) and will balance between aggressiveness, carefullness and space manipulation
		int Bchoice[3];//stores the choice of each turn as an array. [0] is for the type of action (0 = move or 1 = collect), [1] is the start, [2] the destination (if there is one). -1 is used as a null value
		int Liabilities;//AI's captured checkers
		int Prisoners;//enemy's captured checkers
	public:
		
		void InitializeStrategy();
		
		void FindLiabilities(Piles &piles);//finds number of captured checkers
		
		void FindStage(Piles &piles);
		
		void FindPrisoners(Piles &piles);//finds number of enemy imprisoned checkers
		
		void BestChoice(Piles &piles, Dice &dice);
		
		void Act(Piles &piles, Dice &dice);
};

#endif
