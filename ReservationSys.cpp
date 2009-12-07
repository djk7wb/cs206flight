
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
  for(int i=0; i<(int)groups.size(); i++)
  {
    delete groups[i];
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
  int bestPossible=0;

  switch (newGroup.type)
  {
    case BUSINESS:
    bestPossible = SMOKE_VALUE;
    break;
    case TOURISTS:
    bestPossible = ADJACENT_VALUE + COL_VALUE;
    break;
    case FAMILY:
    bestPossible = ADJACENT_VALUE + COL_VALUE*min(2, aislesAvailable());
  }

  //Try adjacent seating only
  for (int i = 0; i < int(newGroup.members.size()); i++)
  {
    chosenSeatNums.push_back(i);
  }
  while ((chosenSeatNums[0] <= ROWS*COLS - int(newGroup.members.size()))
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
  if (newGroup.type == TOURISTS)
  {
    bestPossible = -ADJACENT_VALUE + 2*COL_VALUE;
  }
  else if(newGroup.type == FAMILY)
  {
    bestPossible = -ADJACENT_VALUE
    + COL_VALUE*min(int(newGroup.members.size()), aislesAvailable());
  }
  chosenSeatNums.clear();
  for (int i = 0; i < int(newGroup.members.size()); i++)
  {
    chosenSeatNums.push_back(i);
  }
  while ((chosenSeatNums[0] <= ROWS*COLS - int(newGroup.members.size()))
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

    incrementSeatNums(chosenSeatNums, int(chosenSeatNums.size())-1);
  };

  if (bestValue != INVALID)
  {
    newGroup.satisfaction = bestValue;
    Group *tmpGroup = new Group;
    tmpGroup->groupID = newGroup.groupID;
    for (int i = 0; i < (int)newGroup.members.size(); i++)
    {
      tmpGroup->addPerson(*(newGroup.members[i]));
    }
    tmpGroup->type = newGroup.type;
    tmpGroup->smokingPreference = newGroup.smokingPreference;
    tmpGroup->satisfaction = newGroup.satisfaction;
    groups.push_back(tmpGroup);

    for (int i = 0; i < int(bestSeats.size()); i++)
    {
      int seatNum = bestSeats[i];
      Group *tmpGroup = groups.back();
      seats[seatNum/COLS][seatNum%COLS] = tmpGroup->members[i];
      seats[seatNum/COLS][seatNum%COLS]->row = seatNum/COLS;
      seats[seatNum/COLS][seatNum%COLS]->col = seatNum%COLS;
    }
  }
  return (bestValue != INVALID);
}

int ReservationSys::aislesAvailable()
{
  int numAvail = 0;
  for (int row = 0; row < ROWS; row++)
  {
    if (seats[row][COLS/2] == NULL)
    {
      numAvail+=1;
    }
    if (seats[row][COLS/2 -1] == NULL)
    {
      numAvail+=1;
    }
  }
  return numAvail;
}

//chosenSeatNums becomes the seat numbers associated with the next combination
// with a higher value of chosenSeatNums[index]
void ReservationSys::incrementSeatNums(vector<int>& chosenSeatNums, int index)
{
  do
  {
    //Increment the selected seat number
    chosenSeatNums[index] += 1;
    if (chosenSeatNums[0] > ROWS*COLS-int(chosenSeatNums.size()))
    {
      break;
    }

    //Reset all following seat numbers to their lowest possible value
    for (int j = index+1; j < int(chosenSeatNums.size()); j++)
    {
      chosenSeatNums[j] = chosenSeatNums[j-1] + 1;
    }

    //If any seat numbers after the first are now too large, increment
    // the seat number before it.
    index = -1;
    for (int i = 1; index==-1 && i < int(chosenSeatNums.size()); i++)
    {
      if (chosenSeatNums[i] > ROWS*COLS-int(chosenSeatNums.size())+i)
      {
        index = i-1;
      }
    }

    //If any seat number is occupied, increment it.
    for (int i = 0; index==-1 && i < int(chosenSeatNums.size()); i++)
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
  for (int i = 0; i < int(chosenSeatNums.size())-1; i++)
  {
    //Check for duplicates
    for (int j = i+1; j < int(chosenSeatNums.size()); j++)
    {
      if (chosenSeatNums[i] == chosenSeatNums[j])
      {
        cout << "?" << endl;
        valid = false;
      }
    }
  }

  //Check occupied seats
  for (int i = 0; i < int(chosenSeatNums.size()); i++)
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

  bool adjacent = true;
  int prevRow = -1;
  for (int i = 0; i < int(chosenSeatNums.size()); i++)
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

  if (adjacent && int(chosenSeatNums.size())>1)
  {
    value += ADJACENT_VALUE;
  }
  else if (!adjacent  && int(chosenSeatNums.size())>1)
  {
    value -= ADJACENT_VALUE;
  }

  return value;
}

bool ReservationSys::removeGroup(Group *oldGroup)
{
  int targetIndex = -1;
  for (int i = 0; i < int(groups.size()); i++)
  {
    if (groups[i]->groupID == oldGroup->groupID)
    {
      targetIndex = i;
    }
  }

  if (targetIndex > -1)
  {
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLS; j++)
      {
        if (seats[i][j] && seats[i][j]->groupID == oldGroup->groupID)
        {
          seats[i][j] = NULL;
        }
      }
    }
    groups.erase(groups.begin()+targetIndex);
  }

  return true;
}

Group* ReservationSys::getGroup(int row, int col)
{
  int myGroupID = -1;
  if (seats[row][col] != NULL) {
    Person *tmpPerson = seats[row][col];
    myGroupID = tmpPerson->groupID;
    for (int i=0; i<(int)groups.size(); i++) {
      if (groups[i]->groupID == myGroupID) {
        return groups[i];
      }
    }
  }

  return NULL;
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

vector<Group*> ReservationSys::polledGroups()
{
  const int NUM_POLLED = 10;
  vector<Group*> polled = groups;
  srand((unsigned int)time(NULL));
  while ((int)polled.size() > NUM_POLLED)
  {
    int target = rand()%( (int)polled.size());
    polled.erase(polled.begin()+target);
  }
  return polled;
}


