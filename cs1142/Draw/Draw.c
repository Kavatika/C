/**
 * Name        : Evan Overweg
 * Username    : ejoverwe
 * Description : A program that reads a specialized text file and draws ASCII art according to that file. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// TODO: add a parameter list and the implementation for the following 6 functions:

/**
 * Initializes all elements in the given image to 0.0
 */
void initImage(int width, int height, double image[width][height]) 
{
  for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
	{
	  image[i][j] = 0.0;
	}
    }
}

/**
 * Converts the given color into the corresponding ASCII value. 
 */
char convertColor(double color)
{
  char c;
  if(color < .2)
    {
      c = ' ';
    }
  else if(color < .4)
    {
      c = '.';
    }
  else if(color < .6)
    {
      c = 'o';
    }
  else if(color < .8)
    {
      c = 'O';
    }
  else
    {
      c = '@';
    }
  return c;
}

/**
 * Prints out the given image. 
 */
void printImage(int width, int height, double image[width][height]) 
{
  printf("+");
  for(int i = 0; i < width; i++)
    {
      printf("-");
    }
  printf("+\n");

  for(int j = 0; j < height; j++)
    {
      printf("|");
      for(int i = 0; i < width; i++)
	{
	  printf("%c", convertColor(image[i][j]));
	}
      printf("|\n");
    }
  printf("+");

  for(int i = 0; i < width; i++)
    {
      printf("-");
    }
  printf("+\n");
}

/**
 * Draws the given color at the given point in the image.
 */
void drawPoint(int width, int height, double image[width][height], int x, int y, double color) 
{
  if((x >= 0) && (x < width) && (y >= 0) && (y < height))
    image[x][y] = color;
  return;
} 

/**
 * Draws a rectangle of the given size and color at the given point in the image. 
 */
void drawRectangle(int width, int height, double image[width][height], int left, int top, int rectangleWidth, int rectangleHeight, double color) 
{
  for(int i = 0; i < rectangleWidth; i++)
    {
      for(int j = 0; j < rectangleHeight; j++)
	{
	  drawPoint(width, height, image, i+left, j+top, color);
	}
    }
    return;
}

/**
 * Calculates the darkest, lightest, and average color of the given image. 
 */
void getImageStats(int width, int height, double image[width][height], double* minColor, double* maxColor, double* avgColor) 
{
  double min = DBL_MAX;
  double max = -DBL_MAX;
  double avg = 0;
  for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
	{
	  double selectedColor = image[i][j];
	  if(selectedColor < min)
	    {
	      min = selectedColor;
	    }
	  if(selectedColor > max)
	    {
	      max = selectedColor;
	    }
	  avg+= selectedColor;
	}
    }
  avg = avg / (width * height);
  *minColor = min;
  *maxColor = max;
  *avgColor = avg;
}

/**
 * Flood fills the given color starting at the given point. 
 */
void floodFill(int width, int height, double image[width][height], int x, int y, double color) 
{
  if((x >= 0) && (y >= 0) && (x < width) && (y < height))
    {
      if(image[x][y] < color)
	{
	  drawPoint(width, height, image, x, y, color);
	  floodFill(width, height, image, x+1, y, color);
	  floodFill(width, height, image, x-1, y, color);
	  floodFill(width, height, image, x, y+1, color);
	  floodFill(width, height, image, x, y-1, color);
	}
    }
    return;
}

// Read in a set of drawing instructions from standard input.
// Print the resulting greyscale image as ASCII art. 
// DO NOT MODIFY!
int main(void)
{
   // Read in the size of the drawing canvas
   int width = 0;
   int height = 0;
   int result = scanf("%d %d", &width, &height);
   
   // Program only supports images that are 1x1 or bigger
   if ((width <= 0) || (height <= 0) || (result != 2))
   {
      printf("Failed to read a valid width and height from standard input!\n");
      return 0;
   }
   
   // Create the 2D arary and initialize all the greyscale values to 0.0
   double image[width][height];
   initImage(width, height, image);
   
   char command = '\0';
   double color = 0.0;
   
   // Keep reading in drawing commands until we reach the end of the input
   while (scanf(" %c", &command) == 1)
   {
      switch (command)
      {		
         case 'p': 	
         {
            // Draw a point, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid point command!\n");
               return 0;
            }
            
            drawPoint(width, height, image, x, y, color);
            break;
         }

         case 'r': 	
         {
            // Draw a rectangle, read in: x, y, w, h, color
            int left = 0;
            int top = 0;
            int rectangleWidth = 0;
            int rectangleHeight = 0;
            result = scanf("%d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color);
            if (result != 5)
            {
               printf("Invalid rectangle command!\n");
               return 0;
            }
         
            drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
            break;
         }

         case 'f':
         {
            // Flood fill a color in, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid flood fill command!\n");
               return 0;
            }
            
            floodFill(width, height, image, x, y, color);
            break;
         }

         default:
         {
            printf("Unknown command!\n");
            return 0;
         }
      }
   }
   
   // Print the final image
   printImage(width, height, image);
   
   // Finally display some statistics about the image
   double minColor = 0.0;
   double maxColor = 0.0;
   double avgColor = 0.0;
   getImageStats(width, height, image, &minColor, &maxColor, &avgColor);
   printf("Color range [%.2f, %.2f], average %.4f\n", minColor, maxColor, avgColor);
}
