/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : 
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int cost(int a, int b)
{
  //find change in elevation
  int cost = a - b;
  return abs(cost);
}

int min(int a, int b, int c)
{
  if(a < b) 
    {
      //first number smaller than second, compare to third
      if(a < c)
	{
	  //first number smallest
	  return 0;
	}
      else
	{
	  //third number smallest
	  return 2;
	}
    }
  else
    {
      //second number smaller than first, compare to third
      if(b <= c)
	{
	  //second number smallest
	  return 1;
	}
      else
	{
	  //third number smalelst
	  return 2;
	}
    }
}

int path(int mode, int row, int width, int height, int data[width][height])
{
  int totalCost = 0;
  int elevation = data[0][row];
  int j = row;
  if(mode)
    {
      printf("(0,%d) %d", j, elevation);
    }
  for(int i = 1; i < width; i++)
    {
      int forward = data[i][j];
      
      //if you can't go up or down, the variables need to
      //be set to a flag value
      int up = INT_MIN;
      int down = INT_MIN;
      if(j > 0)
	{
	  up = data[i][j - 1];
	}
      if(j < height - 1)
	{
	  down = data[i][j + 1];
	}

      int fcost = cost(elevation, forward);

      //if either up or down elevation is still at a flag
      //value, then you can't go up or down. if the cost for
      //that choice is at the int max value, then the min
      //function will not choose that value
      int ucost = INT_MAX;
      int dcost = INT_MAX;
      if(up != INT_MIN)
	{
	  ucost = cost(elevation, up);
	}
      if(down != INT_MIN)
	{
	  dcost = cost(elevation, down);
	}

      //select the minimum of the three costs
      int selection = min(ucost, fcost, dcost);

      //for each selection, tally elevation cost, change selected elevation, and change j if necessary
      if(selection == 0) //up direction picked
	{
	  j--;
	  totalCost += ucost;
	  elevation = up;
	  if(mode)
	    {
	      printf(" U, ");
	    }
	}
      else if(selection == 1) //forward direction picked
	{
	  totalCost += fcost;
	  elevation = forward;
	  if(mode)
	    {
	  printf(" F, ");
	    }
	}
      else //downward direction picked
	{
	  j++;
	  totalCost += dcost;
	  elevation = down;
	  if(mode)
	    {
	      printf(" D, ");
	    }
	}
      if(mode)
	{
	  printf("(%d,%d) %d", i, j, elevation);
	}
    }
  if(mode)
    {
      printf(", cost %d\n", totalCost);
    }
  return totalCost;
}

void greedy(int mode, int width, int height, int data[width][height])
{
  int bestCost = INT_MAX;
  int bestRow = -1;
  for(int i = 0; i < height; i++)
    {
      int cost = path(mode, i, width, height, data);
      if(cost < bestCost)
	{
	  bestCost = cost;
	  bestRow = i;
	}
    }
  printf("Best: row %d, cost %d\n", bestRow, bestCost);
}

int main(int argc, char** argv)
{
  int mode = 0;
  if(argc >= 2)
    {
      mode = atoi(argv[1]);
    }

  int width = 0;
  int height = 0;
  scanf("%d %d", &width, &height);
  int dataPoints = width * height;
  int data[width][height];
  
  int max = INT_MIN;
  int min = INT_MAX;
  double avg = 0;
  for(int i = 0, j = 0, k = 0; k < dataPoints; k++)
    {
      int elevation = 0;
      scanf("%d", &elevation);
      data[i][j] = elevation;
      avg += elevation;
      if(max < elevation)
	{
	  max = elevation;
	}
      if(min > elevation)
	{
	  min = elevation;
	}
      i++;
      if(i == width)
      {
	j++;
	i = 0;
      }
    }
  avg /= dataPoints;
  printf("Data points: %d\n", dataPoints);
  printf("Avg elevation: %.2f\n", avg);
  printf("Min elevation: %d\n", min);
  printf("Max elevation: %d\n", max);
  
  greedy(mode, width, height, data);
  return 0;
}





