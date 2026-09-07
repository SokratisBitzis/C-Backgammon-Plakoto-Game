#ifndef DICE_H
#define DICE_H

class Dice{
	private:
		int Dc[4];//contains each dice's number
		int DoubleDc;//shows if the roll is double or not and if it is, it show what the double dice are (eg. 2 if the double roll is 2)
		int Remains;//shows how many non 0 dice there are
	public:
		
		void Initiate();//sets all dice to 0
		
		int GetDice(int ID);
		
		int GetDouble();
		
		int GetRemains();
		
		void Roll();
		
		int FindDice(int x);//returns 0-false if the dice number requested doesn't exist, and if the number does exist, it returns the number of dice with it
		
		void UseDice(int x);//when a dice is to be used, the first dice to match the request is set back to zero
		
		void UseDiceByID(int x);
		
		void PrintDice();
		
};

#endif
