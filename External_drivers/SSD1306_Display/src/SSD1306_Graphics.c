/*
 * SSD1306_Graphics.c
 *
 *  Created on: Aug 31, 2026
 *      Author: hp
 */
#include "SSD1306_Graphics.h"

void GFX_Clear(SSD1306_t *oled)
{
	// Reset all pixels to 0
	for(uint16_t i=0;i<SSD1306_FRAME_SIZE;i++)
	{
		oled->frame_buffer[i] = 0;
	}
}
void GFX_Fill(SSD1306_t *oled)
{
	// Set all pixels to 1 : set byte as 1111 1111
	for(uint16_t i=0;i<SSD1306_FRAME_SIZE;i++)
	{
		oled->frame_buffer[i] = 0xFF;
	}
}
//define API for drawing pixel with x,y coordianates
OLED_Status_t GFX_DrawPixel(SSD1306_t *oled, x_position_t x, y_position_t y, GFXPixel_t state)
{
	//validate input
	if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		return OLED_ERROR_INVALID_COORDINATE;
	}
	//find page number and bit position of the pixel
	uint8_t page = y / 8;
	uint8_t bit  = y % 8;

	//find frame buffer byte
	uint16_t byte_index = (page * SSD1306_WIDTH )+ x ;

	if(state == GFX_PIXEL_ON)
	{
		//set the bit
		oled->frame_buffer[byte_index] |= (1<< bit);
	}
	else if(state == GFX_PIXEL_OFF)
	{
		//clear the bit
		oled->frame_buffer[byte_index] &=~(1<< bit);
	}

	return OLED_OKAY;
}

GFXPixel_t GFX_GetPixel(SSD1306_t *oled, x_position_t x, y_position_t y)
{
	// validate the coordinates
	if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		return OLED_ERROR_INVALID_COORDINATE;
	}

	//find page number and bit position of the pixel
		uint8_t page = y / 8;
		uint8_t bit  = y % 8;

		//find frame buffer byte
		uint16_t byte_index = (page * SSD1306_WIDTH )+ x ;

		uint8_t byte = oled->frame_buffer[byte_index];

		//return state of pixel
		if(byte & (1<<bit))
		{
			return GFX_PIXEL_ON;
		}
		else
		{
			return GFX_PIXEL_OFF;
		}
}

OLED_Status_t GFX_DrawHorizontalLine(SSD1306_t *oled, x_position_t x, y_position_t y, uint8_t length, GFXPixel_t state )
{
	//perform validation
	if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		return OLED_ERROR_INVALID_COORDINATE;
	}
	if((uint16_t)x+length > SSD1306_WIDTH)
	{
		return OLED_ERROR_BUFFER_OVERFLOW;
	}
	//draw pixels starting from x to x + length
	for(uint16_t i= x;i< (x + length);i++)
	{
		GFX_DrawPixel(oled, i, y, state);
	}
	return OLED_OKAY;
}
OLED_Status_t GFX_DrawVerticalLine(SSD1306_t *oled, x_position_t x, y_position_t y, uint8_t length, GFXPixel_t state )
{
	//perform validation
	if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		return OLED_ERROR_INVALID_COORDINATE;
	}
	if((uint16_t)y+length > SSD1306_HEIGHT)
	{
		return OLED_ERROR_BUFFER_OVERFLOW;
	}
	//draw pixels from y to y + length
	for(uint16_t i=y;i< (y+length);i++)
	{
		GFX_DrawPixel(oled, x, i, state);
	}

	return OLED_OKAY;
}
OLED_Status_t GFX_DrawRectangle(SSD1306_t *oled, x_position_t x, y_position_t y, uint8_t length, uint8_t height, GFXPixel_t state )
{
	// prform validation first:
	if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
	{
		return OLED_ERROR_INVALID_COORDINATE;
	}
	if((uint16_t)x + length > SSD1306_WIDTH ||
	   (uint16_t)y + height > SSD1306_HEIGHT 	)
	{
		return OLED_ERROR_BUFFER_OVERFLOW;
	}

	//draw 4 lines connecting 4 coordinates:
	// - horizontal line : (x,y)           with length
	// - horizontal line : (x,y+height-1)  with length
	// - vertical line   : (x,y)           with height
	// - vertical line   : (x+length-1)    with height
                                                                                // assume length = 50, height = 20
	GFX_DrawHorizontalLine(oled, x, y, length, state);            //Top          (20, 30) (69, 30)
	GFX_DrawHorizontalLine(oled, x, (y+height-1), length, state); //Bottom       (20, 49) (69, 49)
	GFX_DrawVerticalLine(oled, x, y, height, state);              //Left         (20, 30) (20, 49)
	GFX_DrawVerticalLine(oled,(x+length-1), y, height, state);    //Right        (69, 30) (69, 49)

	return OLED_OKAY;
}

OLED_Status_t GFX_FillRectangle(SSD1306_t *oled, x_position_t x, y_position_t y, uint8_t length, uint8_t height, GFXPixel_t state )
{
	//perform validation first:
		if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT)
		{
			return OLED_ERROR_INVALID_COORDINATE;
		}
		if((uint16_t)x + length > SSD1306_WIDTH ||
		   (uint16_t)y + height > SSD1306_HEIGHT 	)
		{
			return OLED_ERROR_BUFFER_OVERFLOW;
		}

	//this means deawing a set of horizontal lines form y to (y+height-1)
	// - from (x,y)          (x+length-1,y)
	//   to   (x,y+height-1) (x+length-1, y+height-1)
	for(uint8_t i=y;i< y+height;i++)
	{
		GFX_DrawHorizontalLine(oled, x, i, length, state);
	}

	return OLED_OKAY;
}

OLED_Status_t GFX_DrawLine(SSD1306_t *oled, x_position_t x0, y_position_t y0, x_position_t x1, y_position_t y1, GFXPixel_t state)
{
	// perform validation
	if(x0 >= SSD1306_WIDTH || x1 >= SSD1306_WIDTH || y0 >= SSD1306_HEIGHT || y1 >= SSD1306_HEIGHT)
	{
				return OLED_ERROR_INVALID_COORDINATE;
	}


	//draw first pixel
	GFX_DrawPixel(oled, x0, y0, state);

	// find next pixels

	// Use Bresenham's Algorithm:
	//
	// - first check the slope: if (dy > dx) or not
	// - calculate decision parameter (pk) depending on the slope
	// - calculate the next pixel based on the decision parameter
	// - update pk properly for finding next pixel
	// - calculate pixels till end point



	// For implementing the algorithm in all quadrants,
	// - consider the magnitude of dy and dx and ignore it's sign (use of abs function )
	// - update the value of coordinates based on direction: not just barely increment it ( use of sx and sy )

	int16_t pk;                           // decision parameter
	int16_t dy = abs(y1-y0);              // ignore the sign while measuring slope, only take the magnitude of diffrence//
	int16_t dx = abs(x1-x0);

	// using sx and sy for updating the coordinates properly based on direction of line.

	int8_t sx,sy;

	if(x0 < x1) {sx =  1;} // Updation - incrementing
	else        {sx = -1;} // Updation - deccrementing

	if(y0 < y1) {sy =  1;} // Updation - incrementing
	else        {sy = -1;} // Updation - decrementing


	//check slope
	if(dx > dy)         // m < 1 : we primarily increment x and decides whether y increments or not based on pk.
	{

		// 1. find value of pk
		pk = 2*dy - dx;

		do
		{
			// 2. decide value of y
			if(pk < 0)
			{
				// y stays same

				// 3. update pk for the next pixel
				pk = pk + (2*dy);
			}
			else //if(pk >=0)
			{
				y0 += sy;// update y

				// 3. update pk for the next pixel
				pk = pk + (2*dy) - (2*dx);
			}

			x0+=sx;// Always update x when m is < 1

			//draw the updated pixel
			GFX_DrawPixel(oled, x0, y0, state);

		}while(x0 != x1); // stop drawing when reaches the end point
	}
	else if(dy >= dx) // m >= 1: we primaritly increment y and decides whether x statys same or not based on pk.
	{                 // when m=1, we want to increment both x and y always, and algorithm handles this anuotmatically

		// 1. find value of pk
		pk = 2*dx - dy;

		do
		{

			// 2. decide value of x
			if(pk < 0)
			{
				// x stays same

				// 3. Update pk
				pk = pk+ 2*dx;
			}
			else
			{
				//update x
				x0+=sx;

				// 3. Update pk
				pk = pk+ 2*dx - (2*dy);

			}


			//Always update y when m is >=1
			y0+=sy;

			//draw the updated pixel
			GFX_DrawPixel(oled, x0, y0, state);


		}while(y0 != y1);// stop drawing when reaches the end point

	}
	return OLED_OKAY;
}


OLED_Status_t GFX_DrawTriangle(SSD1306_t *oled, x_position_t x0, y_position_t y0, x_position_t x1, y_position_t y1, x_position_t x2, y_position_t y2 ,GFXPixel_t state)
{

	//perform validation first:
	if(x0 >= SSD1306_WIDTH || x1 >= SSD1306_WIDTH || y0 >= SSD1306_HEIGHT || y1 >= SSD1306_HEIGHT
			|| x2 >= SSD1306_WIDTH || y2 >= SSD1306_HEIGHT)
	{
		return OLED_ERROR_INVALID_COORDINATE;
	}
	//draw 3 lines connecting the 3 coordinates to draw the triangle

	GFX_DrawLine(oled, x0, y0, x1, y1, state);
	GFX_DrawLine(oled, x1, y1, x2, y2, state);
	GFX_DrawLine(oled, x0, y0, x2, y2, state);

	return OLED_OKAY;
}
//define helper functions
static uint8_t smallest(uint8_t a, uint8_t b, uint8_t c)
{
	if(a <b && a<c)
	{
		return a;
	}
	else
	if(b<a && b<c)
	{
		return b;
	}
	else
		return c;
}
static uint8_t largest(uint8_t a, uint8_t b, uint8_t c)
{
	if(a > b && a > c)
	{
		return a;
	}
	else
	if(b > a && b > c)
	{
		return b;
	}
	else
		return c;
}
OLED_Status_t GFX_FillTriangle(SSD1306_t *oled, x_position_t x0, y_position_t y0, x_position_t x1, y_position_t y1, x_position_t x2, y_position_t y2 ,GFXPixel_t state)
{
	// validate the coordinates
	if(x0 >= SSD1306_WIDTH || x1 >= SSD1306_WIDTH || y0 >= SSD1306_HEIGHT || y1 >= SSD1306_HEIGHT
			|| x2 >= SSD1306_WIDTH || y2 >= SSD1306_HEIGHT)
	{
		return OLED_ERROR_INVALID_COORDINATE;
	}

	//first draw the triangle
	GFX_DrawTriangle(oled, x0, y0, x1, y1, x2, y2, state);

	//find top and bottom rows
	uint8_t y_top    = smallest(y0, y1, y2);
	uint8_t y_bottom = largest(y0, y1, y2);

	//loop through each rows and turn on pixels between two ON pixels

	uint8_t y_current = y_top;



	while(y_current <= y_bottom)
	{
		uint8_t flag=0, x_first, x_second;

		//loop through each columns (x values)
		for (uint8_t x_current = 0;x_current < SSD1306_WIDTH;x_current++)
		{
			if(GFX_GetPixel(oled, x_current, y_current) == state && flag == 0)
			{
				x_first = x_current;

				flag=1;
			}
			else
				if(GFX_GetPixel(oled, x_current, y_current) == state && flag == 1)
				{
					x_second = x_current;

					flag=0;

					//Draw line when second pixel is found
					//fill row between two x points
							GFX_DrawLine(oled, x_first, y_current, x_second, y_current, state);
				}

		}


		y_current++;
	}




	return OLED_OKAY;
}


OLED_Status_t GFX_DrawCircle(SSD1306_t *oled, x_position_t xc, y_position_t yc, uint8_t radius, GFXPixel_t state)
{
	//perform validations

	if(xc+radius >= SSD1306_WIDTH || yc+radius >= SSD1306_HEIGHT

			|| xc<radius || yc<radius)
	{
		return OLED_ERROR_BUFFER_OVERFLOW;
	}

	// Calculate pixels for one octant and use 8-way symmetry
	// to generate the 7 remaining points.
	//
	// For a point (x0,y0) relative to the center,the other symmetric points are:
	// ( x0, y0), ( x0,-y0), (-x0, y0), (-x0,-y0)
	// ( y0, x0), ( y0,-x0), (-y0, x0), (-y0,-x0)
	//
	// Assume the circle center is origin, start at the top of the circle: (0,radius).
	// x is incremented at every step.
	// The decision parameter determines whether y should also decrease.
	// Octant is complete when x0 equals y0
	// Convert local coordinates (x0,y0) to OLED coordinates
	// by adding the circle center (x,y).

	// set starting point as (0, radius)
	int8_t x0 = 0, y0 = radius;

	// Initialize decision parameter
	int16_t pk = 3 - 2*radius;

	do{

		//draw pixels on 8 coordinates: centre is at (x,y)
			GFX_DrawPixel(oled, xc+x0, yc+y0, state);
			GFX_DrawPixel(oled, xc+x0, yc-y0, state);
			GFX_DrawPixel(oled, xc-x0, yc+y0, state);
			GFX_DrawPixel(oled, xc-x0, yc-y0, state);

			GFX_DrawPixel(oled, xc+y0, yc+x0, state);
			GFX_DrawPixel(oled, xc-y0, yc+x0, state);
			GFX_DrawPixel(oled, xc+y0, yc-x0, state);
			GFX_DrawPixel(oled, xc-y0, yc-x0, state);

			//find next coordinate using decision parameter

		if(pk < 0)
			{
			    pk = pk + 4*x0 + 6; // Update pk for next point

				                   // y stays same
				x0++;	           // x always increments

			}
			else
				if(pk >= 0)
				{
					pk = pk + 4*(x0-y0) + 10; // Update pk for next point

					y0--;                   // y decrements
					x0++;                   // x always increments

				}

	}while(x0!=y0);// loop till octant is complete

	return OLED_OKAY;
}

OLED_Status_t GFX_FillCircle(SSD1306_t *oled, x_position_t xc, y_position_t yc, uint8_t radius, GFXPixel_t state)
{
	//perform validations

	if(xc+radius >= SSD1306_WIDTH || yc+radius >= SSD1306_HEIGHT
				|| xc<radius || yc<radius)
	{
		return OLED_ERROR_BUFFER_OVERFLOW;
	}

	// for FillCrcle, find each coordinates in the octant, therby getting 7 other points,
	// instaed of drawing pixels on 8 points, draw 4 lines connecting 2 points

	// set starting point as (0, radius)
		int8_t x0 = 0, y0 = radius;

		// Initialize decision parameter
		int16_t pk = 3 - 2*radius;

		do{

			//draw line b/w 2 coordinates: centre is at (xc,yc)
			GFX_DrawLine(oled, xc+x0, yc+y0, xc+x0, yc-y0, state);

			GFX_DrawLine(oled, xc-x0, yc+y0, xc-x0, yc-y0, state);

			GFX_DrawLine(oled, xc+y0, yc+x0, xc-y0, yc+x0, state);

			GFX_DrawLine(oled, xc+y0, yc-x0, xc-y0, yc-x0, state);


				//find next coordinate using decision parameter

			if(pk < 0)
				{
				    pk = pk + 4*x0 + 6; // Update pk for next point

					                   // y stays same
					x0++;	           // x always increments

				}
				else
					if(pk >= 0)
					{
						pk = pk + 4*(x0-y0) + 10; // Update pk for next point

						y0--;                   // y decrements
						x0++;                   // x always increments

					}

		}while(x0<=y0);// loop till octant is complete

		return OLED_OKAY;


}






















