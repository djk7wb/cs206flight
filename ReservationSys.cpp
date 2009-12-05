
#include "ReservationSys.h"

ReservationSys::ReservationSys()
{
  seats = new Person**[ROWS];
  for (int i = 0; i < ROWS; i++)
  {
    *(seats+i) = new Person*[COLS];
  }
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      seats[i][j] = NULL;
    }
  }
}

ReservationSys::~ReservationSys()
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      delete seats[i][j];
    }
  }
  for (int i = 0; i < ROWS; i++)
  {
    delete [] *(seats+i);
  }
  delete [] seats;
}

bool ReservationSys::addGroup(Group newGroup)
{
  const int INVALID = -9999;
  int bestValue = INVALID;
  vector<int> chosenSeatNums;
  vector<int> bestSeats;
  int newValue;
  int bestPossible;

  switch (newGroup.type)
  {
    case BUSINESS:
    bestPossible = SMOKE_VALUE;
    break;
    case TOURISTS:
    bestPossible = ADJACENT_VALUE + COL_VALUE;
    break;
    case FAMILY:
    bestPossible = ADJACENT_VALUE + COL_VALUE*2;
  }

  //Try adjacent seating only
  for (int i = 0; i < newGroup.members.size(); i++)
  {
    chosenSeatNums.push_back(i);
  }
  while ((chosenSeatNums[0] <= ROWS*COLS - newGroup.members.size())
          && bestValue < bestPossible)
  {
    if (validSeating(chosenSeatNums))
    {
      newValue = seatingValue(newGroup, chosenSeatNums);
      if (newValue > bestValue)
      {
        bestValue = newValue;
        bestSeats = chosenSeatNums;
      }
    }

    incrementSeatNums(chosenSeatNums, 0);
  };


  //Try all possible seating
  chosenSeatNums.clear();
  for (int i = 0; i < newGroup.members.size(); i++)
  {
    chosenSeatNums.push_back(i);
  }
  while ((chosenSeatNums[0] <= ROWS*COLS - newGroup.members.size())
          && bestValue < bestPossible)
  {
    if (validSeating(chosenSeatNums))
    {
      newValue = seatingValue(newGroup, chosenSeatNums);
      if (newValue > bestValue)
      {
        bestValue = newValue;
        bestSeats = chosenSeatNums;
      }
    }

    incrementSeatNums(chosenSeatNums, chosenSeatNums.size()-1);
  };

  if (bestValue != INVALID)
  {
    for (int i = 0; i < bestSeats.size(); i++)
    {
      int seatNum = bestSeats[i];
      seats[seatNum/COLS][seatNum%COLS] = new Person;
      *(seats[seatNum/COLS][seatNum%COLS]) = newGroup.members[i];
    }
    newGroup.satisfaction = bestValue;
  }
  return (bestValue != INVALID);
}

//chosenSeatNums becomes the seat numbers associated with the next combination
// with a higher value of chosenSeatNums[index]
void ReservationSys::incrementSeatNums(vector<int>& chosenSeatNums, int index)
{
  do
  {
    //Increment the selected seat number
    chosenSeatNums[index] += 1;
    if (chosenSeatNums[0] > ROWS*COLS-chosenSeatNums.size())
    {
      break;
    }

    //Reset all following seat numbers to their lowest possible value
    for (int j = index+1; j < chosenSeatNums.size(); j++)
    {
      chosenSeatNums[j] = chosenSeatNums[j-1] + 1;
    }

    //If any seat numbers after the first are now too large, increment
    // the seat number before it.
    index = -1;
    for (int i = 1; index==-1 && i < chosenSeatNums.size(); i++)
    {
      if (chosenSeatNums[i] > ROWS*COLS-chosenSeatNums.size()+i)
      {
        index = i-1;
      }
    }

    //If any seat number is occupied, increment it.
    for (int i = 0; index==-1 && i < chosenSeatNums.size(); i++)
    {
      if (seats[chosenSeatNums[i]/COLS][chosenSeatNums[i]%COLS] != NULL)
      {
        index = i;
      }
    }

  } while (index != -1);
}

bool ReservationSys::validSeating(vector<int> chosenSeatNums)
{
  bool valid = true;
  //Check for duplicates
  for (int i = 0; i < chosenSeatNums.size()-1; i++)
  {
    //Check for duplicates
    for (int j = i+1; j < chosenSeatNums.size(); j++)
    {
      if (chosenSeatNums[i] == chosenSeatNums[j])
      {
        cout << "?" << endl;
        valid = false;
      }
    }
  }

  //Check occupied seats
  for (int i = 0; i < chosenSeatNums.size(); i++)
  {
    if (seats[chosenSeatNums[i]/COLS][chosenSeatNums[i]%COLS] != NULL)
    {
      valid = false;
    }
  }

  return valid;
}

int ReservationSys::seatingValue(Group g, vector<int> chosenSeatNums)
{
  int value = 0;

  sort(chosenSeatNums.begin(), chosenSeatNums.end());

  bool adjacent = true;
  int prevRow = -1;
  for (int i = 0; i < chosenSeatNums.size(); i++)
  {
    int seatNum = chosenSeatNums[i];
    int row = seatNum/COLS;
    int col = seatNum%COLS;
    bool aisle = (col==COLS/2 || col == COLS/2 -1);
    bool window = (col==0 || col == COLS-1);
    if (i > 0)
    {
      if (seatNum != chosenSeatNums[i-1]+1)
      {
        adjacent = false;
      }
      if (row != prevRow)
      {
        adjacent = false;
      }
    }
    prevRow = row;
    if (g.type==BUSINESS)
    {
      if (g.smokingPreference == (row >= ROWS-SMOKE_ROWS))
      {
        value += SMOKE_VALUE;
      }
      else
      {
        value -= SMOKE_VALUE;
      }
    }
    if (g.type==FAMILY && aisle)
    {
      value += COL_VALUE;
    }
    if (g.type==TOURISTS && window)
    {
      value += COL_VALUE;
    }
  }

  if (adjacent && chosenSeatNums.size()>1)
  {
    value += ADJACENT_VALUE;
  }
  else if (!adjacent  && chosenSeatNums.size()>1)
  {
    value -= ADJACENT_VALUE;
  }

  return value;
}

ostream& operator<<(ostream& out, ReservationSys& rhs)
{
  for (int i = 0; i < rhs.ROWS; i++)
  {
    if (i == rhs.ROWS - rhs.SMOKE_ROWS)
    {
      out << "   Smoking\n";
    }
    for (int j = 0; j < rhs.COLS; j++)
    {
      if (j == rhs.COLS/2)
      {
        out << " ";
      }
      if (rhs.seats[i][j] == NULL)
      {
        out << "_ ";
      }
      else
      {
        out << "X ";
      }
    }
    out << "\n";
  }
  return out;
}

