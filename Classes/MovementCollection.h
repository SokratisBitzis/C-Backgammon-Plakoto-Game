#ifndef MOVEMENTCOLLECTION_H
#define MOVEMENTCOLLECTION_H

bool CanCollect(Piles &piles, Dice &dice, int PID);

bool CanMove(Piles &piles, Dice &dice, int PID);

void Move(Piles &piles, Dice &dice, int PID, int from, int to, int st);

void Collect(Piles &piles, Dice &dice, int PID, int what);

bool ValidateMovement(Piles &piles, Dice &dice, int PID, int from, int to);

bool ValidateCollection(Piles &piles, Dice &dice, int PID, int what);

#endif
