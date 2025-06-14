/*
 * ui.c
 *
 *  Created on: Jun 14, 2025
 *      Author: ebokm
 */

#include "ui.h"          // Include the corresponding header for declarations
#include "16x2_screen.h" // For LCD screen functions (cursor_pos, write_to_screen etc.)
#include "max3485.h"     // For access to rs485 (already in ui.h, but good to be explicit)
#include <string.h>      // Required for strcmp


// Define the global variables declared in ui.h.
// These are the single, authoritative definitions for these variables in your project.
volatile uint8_t page = 1;
uint8_t menu = 1;
volatile uint8_t select = 1;
volatile uint8_t conf = 0;

volatile uint8_t update = 0;

volatile int16_t max_well_level = 170;
volatile int16_t min_well_level = 0;
volatile int16_t max_level = 160;
volatile int16_t min_level = 50;

volatile float diameter = 184;
volatile uint16_t X = 200;
volatile uint16_t Y = 200;

volatile uint8_t brightness = 10; //0-255

const char *form = "cy"; // The string literal "cy" is also defined here once.

// The implementation of the UI function.
/**
 * @brief Manages the user interface logic, including menu navigation and display updates.
 * This function implements a state machine based on 'menu' and 'page' variables.
 */
void ui(void){
    // This entire function body remains the same as your original,
    // just moved from the .h file to the .c file.
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
	 switch(menu){
		case 1: //tutorial
			switch(page){
				case 1:
					 cursor_pos(1, 1);
					 write_to_screen("     Welkom!    ");
					 cursor_pos(2, 1);
					 write_to_screen("press o for next");
				break;
				case 2:
					 cursor_pos(1, 1);
					 write_to_screen("    this is a   ");
					 cursor_pos(2, 1);
					 write_to_screen("    tutorial    ");
					 if(conf == 1){
						 menu = 2;
						 conf = 0;
						 select = 1;
						 page = 1;
						 update = 1;
					 }
				break;
				case 3:
					 cursor_pos(1, 1);
					 write_to_screen("   o is to go   ");
					 cursor_pos(2, 1);
					 write_to_screen("to the next page");
				break;
				case 4:
					 cursor_pos(1, 1);
					 write_to_screen(" and x is to go ");
					 cursor_pos(2, 1);
					 write_to_screen(" back a page    ");
				break;
				case 5:
					 cursor_pos(1, 1);
					 write_to_screen(" ^ is to select ");
					 cursor_pos(2, 1);
					 write_to_screen("  your choice   ");
				break;
				case 6:
					 cursor_pos(1, 1);
					 write_to_screen("and also to     ");
					 cursor_pos(2, 1);
					 write_to_screen("increase a value");
				break;
				case 7:
					 cursor_pos(1, 1);
					 write_to_screen(" ");
					 send_to_screen(0b11011011, 'b', 'd'); // This looks like a custom character or a specific symbol.
					 write_to_screen(" is used to    ");
					 cursor_pos(2, 1);
					 write_to_screen("confirm a choice");
				break;
				case 8:
					 cursor_pos(1, 1);
					 write_to_screen("and also to     ");
					 cursor_pos(2, 1);
					 write_to_screen("decrease a value");
				break;
				default:
					 menu = 2;
					 page = 1;
					 conf = 0;
					 select = 1;
					 update = 1;
				break;
			}
		break;
//---------------------------------------------------------------------------------------------------------------------------------------------------------
		case 2: //menu selecter
			switch(page){
				case 1:
					 cursor_pos(1, 1);
					 write_to_screen("Setting Displays");
					 cursor_pos(2, 1);
					 write_to_screen("    Tutorial    ");
					 switch(select){
						case 1: // "Setting Displays" option
							 cursor_pos(1, 1); // This seems to just re-set the cursor, doesn't draw a selector.
                                             // You might want to display a ">" or some other indicator here.
							 if(conf == 1){
								 menu = 3; // Go to settings menu
								 conf = 0;
								 select = 1;
								 page = 2; // Start settings menu on the second page (Min/Max Well)
								 update = 1;
							 }
						break;

						case 2: // "Displays" option (assuming this is for the second option on line 1)
							 cursor_pos(1, 9); // This seems to just re-set the cursor.
                                             // This might intend to point at "Displays" which is not explicitly written.
                                             // Given the next 'if' condition, it seems like the "Displays" text
                                             // is implicitly understood from the first line's "Setting Displays".
                                             // It's more likely that the options are:
                                             // Option 1: "Settings" (implicit at 1,1)
                                             // Option 2: "Displays" (implicit at 1,9)
                                             // Option 3: "Tutorial" (explicit at 2,5)
                                             // Re-check your physical layout.
							 if(conf == 1){
								 menu = 4; // Go to displays menu
								 conf = 0;
								 select = 1;
								 page = 2; // Start displays menu on the second page (water level)
								 update = 1;
								 send_to_screen(0b00001100, 'b', 'c'); // Turn cursor off
							 }
						break;

						case 3: // "Tutorial" option
							 cursor_pos(2, 5); // This seems to just re-set the cursor.
							 if(conf == 1){
								 menu = 1; // Go back to tutorial
								 conf = 0;
								 select = 1;
								 page = 1;
								 update = 1;
							 }
						break;

						default: // Fallback for 'select'
							select = 1;
							update = 1;
						break;
					}
				break;

				default: // Fallback for 'page' in menu 2
					page = 1;
					update = 1;
				break;
			}
		break;
//---------------------------------------------------------------------------------------------------------------------------------------------------------
		case 3: //settings selector
			switch(page){

				case 1: // Go back to menu selector
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen(" menu selector  ");
					 if(conf == 1){
						 menu = 2;
						 conf = 0;
						 select = 1;
						 page = 1;
						 update = 1;
					 }
				break;

				case 2: // Min/Max Well & Min/Max Limit options
					cursor_pos(1, 1);
					write_to_screen("  Min/Max Well  ");
					cursor_pos(2, 1);
					write_to_screen("  Min/Max Limit ");
					switch(select){
						case 1: // "Min/Max Well" option
							 cursor_pos(1, 3); // This seems to just re-set the cursor.
							 if(conf == 1){
								 menu = 5; // Go to well level settings
								 conf = 0;
								 select = 1;
								 page = 2; // Start well level settings on intro page 2
								 update = 1;
								 send_to_screen(0b00001100, 'b', 'c'); // Turn cursor off
							 }
						break;

						case 2: // "Min/Max Limit" option
							 cursor_pos(2, 3); // This seems to just re-set the cursor.
							 if(conf == 1){
								 menu = 6; // Go to limit level settings
								 conf = 0;
								 select = 1;
								 page = 2; // Start limit level settings on intro page 2
								 update = 1;
								 send_to_screen(0b00001100, 'b', 'c'); // Turn cursor off
						 }
							 break;

						default: // Fallback for 'select'
							select = 1;
							update = 1;
						break;
				}
				break;

				case 3: // Well form & Well dimensions options
					cursor_pos(1, 1);
					write_to_screen(" Well form      ");
					cursor_pos(2, 1);
					write_to_screen(" Well dimensions");
					switch(select){
						case 1: // "Well form" option
							 cursor_pos(1, 2); // This seems to just re-set the cursor.
							 if(conf == 1){
								 menu = 7; // Go to form selector
								 conf = 0;
								 select = 1;
								 page = 2; // Start form selector on intro page 2
								 update = 1;
							 }
						break;

						case 2: // "Well dimensions" option
							 cursor_pos(2, 2); // This seems to just re-set the cursor.
							 if(conf == 1){
								 menu = 8; // Go to dimensions selector
								 conf = 0;
								 select = 1;
								 page = 2; // Start dimensions selector on intro page 2
								 update = 1;
						 }
							 break;

						default: // Fallback for 'select'
							select = 1;
							update = 1;
						break;
				}
				break;

				case 4: // Go back to menu selector (duplicate of page 1, consider consolidating if possible)
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen(" menu selector  ");
					 if(conf == 1){
						 menu = 2;
						 conf = 0;
						 select = 1;
						 page = 1;
						 update = 1;
					 }
				break;

				default: // Fallback for 'page' in menu 3
					page = 2;
					update = 1;
				break;
			}
		break;
//---------------------------------------------------------------------------------------------------------------------------------------------------------
		case 4: //displays
			switch(page){

				case 1: // Go back to menu selector
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen(" menu selector  ");
					 if(conf == 1){
						 menu = 2;
						 conf = 0;
						 select = 1;
						 page = 1;
						 update = 1;
						 send_to_screen(0b00001111, 'b', 'c'); // Turn cursor ON (seems like this is intended to re-enable)
					 }
				break;

				case 2: // Display water level
					 cursor_pos(1, 1);
					 write_to_screen("  water level   ");
					 cursor_pos(2, 1);
					 write_to_screen("  ");
					 float_to_screen(rs485); // Display current RS485 (water level) value
					 write_to_screen(" cm             ");
					 update = 1; // Always mark for update, as value can change
				break;

				case 3: // Display water volume
					float volume = 0;

					if(strcmp(form, "cy") == 0){ // Cylinder volume calculation
						volume = ((diameter/2) * (diameter/2) * 3.14159f * rs485) / 1000.0f; // Division by 1000 to get Liters from cm^3
					}
					else{ // Cuboid volume calculation
						volume = (X * Y * rs485) / 1000.0f; // Division by 1000 to get Liters from cm^3
					}

					 cursor_pos(1, 1);
					 write_to_screen("  water volume  ");
					 cursor_pos(2, 1);
					 write_to_screen("  ");
					 float_to_screen(volume);
					 write_to_screen(" L              ");
					 update = 1; // Always mark for update
				break;

				case 4: // Go back to menu selector (duplicate of page 1, consider consolidating if possible)
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen(" menu selector  ");
					 if(conf == 1){
						 menu = 2;
						 conf = 0;
						 select = 1;
						 page = 1;
						 update = 1;
						 send_to_screen(0b00001111, 'b', 'c'); // Turn cursor ON
					 }
				break;

				default: // Fallback for 'page' in menu 4
					page = 2;
					update = 1;
				break;
			}
		break;
//---------------------------------------------------------------------------------------------------------------------------------------------------------
		case 5: //well level settings (min/max well)
			switch(page){

				case 1: // Go back to settings selector
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen("setting selector");
					 if(conf == 1){
						 menu = 3;
						 conf = 0;
						 select = 1;
						 page = 2; // Return to min/max well/limit page in settings
						 update = 1;
						 send_to_screen(0b00001111, 'b', 'c'); // Turn cursor ON
					 }
				break;

				case 2: // Intro page for well level settings
					cursor_pos(1, 1);
					 write_to_screen("Here you set the");
					 cursor_pos(2, 1);
					 write_to_screen("max and min    >");
				break;

				case 3: // Continuation of intro page for well level settings
					cursor_pos(1, 1);
					 write_to_screen("  of the well.  ");
					 cursor_pos(2, 1);
					 write_to_screen("                ");
				break;

				case 4: // Set Max well level
					cursor_pos(1, 1);
					 write_to_screen(" Max level well ");
					 cursor_pos(2, 1);
					 digit_to_screen(max_well_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){ // Increment max_well_level if 'select' button pressed
						 max_well_level++;
						 select = 1; // Reset select
						 update = 1;
					 }
					 if(conf == 1){ // Decrement max_well_level if 'conf' button pressed
						 max_well_level--;
						 conf = 0; // Reset conf
						 update = 1;
					 }
				break;

				case 5: // Set Min well level
					cursor_pos(1, 1);
					 write_to_screen(" Min level well ");
					 cursor_pos(2, 1);
					 digit_to_screen(min_well_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){ // Increment min_well_level
						 min_well_level++;
						 select = 1;
						 update = 1;
					 }
					 if(conf == 1){ // Decrement min_well_level
						 min_well_level--;
						 conf = 0;
						 update = 1;
					 }
				break;

				case 6: // Go back to settings selector (duplicate of page 1)
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen("setting selector");
					 if(conf == 1){
						 menu = 3;
						 conf = 0;
						 select = 1;
						 page = 2;
						 update = 1;
						 send_to_screen(0b00001111, 'b', 'c'); // Turn cursor ON
					 }
				break;

				default: // Fallback for 'page' in menu 5
					page = 2;
					update = 1;
				break;
		}
		break;
//---------------------------------------------------------------------------------------------------------------------------------------------------------
		case 6: //limit level settings (max/min level for automation)
			switch(page){

				case 1: // Go back to settings selector
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen("setting selector");
					 if(conf == 1){
						 menu = 3;
						 conf = 0;
						 select = 1;
						 page = 2; // Return to min/max well/limit page in settings
						 update = 1;
						 send_to_screen(0b00001111, 'b', 'c'); // Turn cursor ON
					 }
				break;

				case 2: // Intro page for limit level settings
					cursor_pos(1, 1);
					 write_to_screen("Here you set the");
					 cursor_pos(2, 1);
					 write_to_screen("max and min    >");
				break;

				case 3: // Continuation of intro page for limit level settings
					cursor_pos(1, 1);
					 write_to_screen(" for the water  ");
					 cursor_pos(2, 1);
					 write_to_screen(" level you want.");
				break;

				case 4: // Set Max limit
					cursor_pos(1, 1);
					 write_to_screen("   Max limit    ");
					 cursor_pos(2, 1);
					 digit_to_screen(max_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){
						 max_level++;

						 // Cap max_level to prevent going too close to well top
						 if(max_level >= max_well_level - 5){
							 max_level = max_well_level - 5;
						 }

						 select = 1;
						 update = 1;
					 }
					 if(conf == 1){
						 max_level--;

						 // Cap max_level to prevent going below min_level + 10
						 if(max_level <= min_level + 10){
							 max_level = min_level + 10;
						 }

						 conf = 0;
						 update = 1;
					 }
				break;

				case 5: // Set Min limit
					cursor_pos(1, 1);
					 write_to_screen("   Min limit    ");
					 cursor_pos(2, 1);
					 digit_to_screen(min_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){
						 min_level++;

						 // Cap min_level to prevent going too close to max_level
						 if(min_level >= max_level - 10){
							 min_level = max_level - 10;
						 }

						 select = 1;
						 update = 1;
					 }
					 if(conf == 1){
						 min_level--;
						 conf = 0;
						 update = 1;

						 // Cap min_level to prevent going below 5cm
						 if(min_level <= 5){
							 min_level = 5;
						 }
					 }
				break;

				case 6: // Go back to settings selector (duplicate of page 1)
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen("setting selector");
					 if(conf == 1){
						 menu = 3;
						 conf = 0;
						 select = 1;
						 page = 2;
						 update = 1;
						 send_to_screen(0b00001111, 'b', 'c'); // Turn cursor ON
					 }
				break;

				default: // Fallback for 'page' in menu 6
					page = 2;
					update = 1;
				break;
		}
		break;
//---------------------------------------------------------------------------------------------------------------------------------------------------------
		case 7: //form selector (Cylinder/Cuboid)
			switch(page){

				case 1: // Go back to settings selector
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen("setting selector");
					 if(conf == 1){
						 menu = 3;
						 conf = 0;
						 select = 1;
						 page = 3; // Return to well form/dimensions page in settings
						 update = 1;
					 }
				break;

				case 2: // Intro page for form selector
					 cursor_pos(1, 1);
					 write_to_screen("Here you select ");
					 cursor_pos(2, 1);
					 write_to_screen("the form off   >");
				break;

				case 3: // Continuation of intro page for form selector
					 cursor_pos(1, 1);
					 write_to_screen("   the well.    ");
					 cursor_pos(2, 1);
					 write_to_screen("                ");
				break;

				case 4: // Select Cylinder or Cuboid
					 cursor_pos(1, 1);

					 if(strcmp(form, "cy") == 0){ // If form is Cylinder, show filled 'O'
						 write_to_screen("   ");
						 send_to_screen(0b11111111 ,'b', 'd'); // This byte might be a custom character for a filled circle/square
					 }
					 else{ // If form is not Cylinder, show empty 'O'
						 write_to_screen("   O");
					 }

					 write_to_screen(" cylinder       ");
					 cursor_pos(2, 1);

					 if(strcmp(form, "cu") == 0){ // If form is Cuboid, show filled 'O'
						 write_to_screen("   ");
						 send_to_screen(0b11111111 ,'b', 'd');
					 }
					 else{ // If form is not Cuboid, show empty 'O'
						 write_to_screen("   O");
					 }

					 write_to_screen(" cuboid         ");

					 switch(select){
						case 1: // Select Cylinder
							 cursor_pos(1, 3); // Position cursor to indicate selection
							 if(conf == 1){
								 conf = 0;
								 form = "cy"; // Set form to cylinder
								 update = 1;
							 }
						break;

						case 2: // Select Cuboid
							 cursor_pos(2, 3); // Position cursor to indicate selection
							 if(conf == 1){
								 conf = 0;
								 form = "cu"; // Set form to cuboid
								 update = 1;
						 }
						 break;

						default: // Fallback for 'select'
							select = 1;
							update = 1;
						break;
					 }
				break;

				case 5: // Go back to settings selector (duplicate of page 1)
					cursor_pos(1, 1);
					 write_to_screen(" Go back to the ");
					 cursor_pos(2, 1);
					 write_to_screen("setting selector");
					 if(conf == 1){
						 menu = 3;
						 conf = 0;
						 select = 1;
						 page = 3;
						 update = 1;
					 }
				break;

				default: // Fallback for 'page' in menu 7
					page = 2;
					update = 1;
				break;
			}
			break;
//---------------------------------------------------------------------------------------------------------------------------------------------------------
			case 8: //dimensions selector
				switch(page){

					case 1: // Go back to settings selector
						cursor_pos(1, 1);
						 write_to_screen(" Go back to the ");
						 cursor_pos(2, 1);
						 write_to_screen("setting selector");
						 if(conf == 1){
							 menu = 3;
							 conf = 0;
							 select = 1;
							 page = 3; // Return to well form/dimensions page in settings
							 update = 1;
						 }
					break;

					case 2: // Intro page for dimensions selector
						 cursor_pos(1, 1);
						 write_to_screen("Here you give   ");
						 cursor_pos(2, 1);
						 write_to_screen("the dimensions >");
					break;

					case 3: // Continuation of intro page for dimensions selector
						 cursor_pos(1, 1);
						 write_to_screen(" off the well.  ");
						 cursor_pos(2, 1);
						 write_to_screen("                ");
					break;

					case 4: // Set diameter (if cylinder) or X (if cuboid)
						if (strcmp(form, "cy") == 0) { // Cylinder
							cursor_pos(1, 1);
							write_to_screen("   diameter:    ");
							cursor_pos(2, 1);
							write_to_screen("   ");
							digit_to_screen(diameter);
							write_to_screen(" cm             ");
							 if(select >= 2){ // Increment diameter
								 diameter++;
								 select = 1;
								 update = 1;
							 }
							 if(conf == 1){ // Decrement diameter
								 diameter--;
								 conf = 0;
								 update = 1;
							 }
						}
						else { // Cuboid (setting X dimension)
							cursor_pos(1, 1);
							write_to_screen("X:              ");
							cursor_pos(2, 1);
							digit_to_screen(X);
							write_to_screen(" cm             ");
							 if(select >= 2){ // Increment X
								 X++;
								 select = 1;
								 update = 1;
							 }
							 if(conf == 1){ // Decrement X
								 X--;
								 conf = 0;
								 update = 1;
							 }
						}
					break;

					case 5: // If cylinder, this page is "Go back". If cuboid, this page is Y dimension.
						if (strcmp(form, "cy") == 0) { // Cylinder (only one dimension needed)
							 cursor_pos(1, 1);
							 write_to_screen(" Go back to the ");
							 cursor_pos(2, 1);
							 write_to_screen("setting selector");
							 if(conf == 1){
								 menu = 3;
								 conf = 0;
								 select = 1;
								 page = 3; // Return to well form/dimensions page in settings
								 update = 1;
							 }
						}
						else { // Cuboid (setting Y dimension)
							cursor_pos(1, 1);
							write_to_screen("Y:              ");
							cursor_pos(2, 1);
							digit_to_screen(Y);
							write_to_screen(" cm             ");
							 if(select >= 2){ // Increment Y
								 Y++;
								 select = 1;
								 update = 1;
							 }
							 if(conf == 1){ // Decrement Y
								 Y--;
								 conf = 0;
								 update = 1;
							 }
						}
					break;

					case 6: // This page is only reached for Cuboid, to "Go back"
						if (strcmp(form, "cy") == 0) {
							// If cylinder, page 5 is the "Go back" page, so page 6 should not be reached normally.
							// This seems like a slight logical inconsistency in page flow if only
							// 'page' increments from the button presses. This default needs careful checking.
							page = 5; // Direct to the "go back" page for cylinder
						}
						else { // Cuboid
							 cursor_pos(1, 1);
							 write_to_screen(" Go back to the ");
							 cursor_pos(2, 1);
							 write_to_screen("setting selector");
							 if(conf == 1){
								 menu = 3;
								 conf = 0;
								 select = 1;
								 page = 3; // Return to well form/dimensions page in settings
								 update = 1;
							 }
						}
					break;

					default: // Fallback for 'page' in menu 8
						page = 2;
						update = 1;
					break;
				}
				break;

		default: // Fallback for 'menu'
			menu = 2; // Default to main menu selector
		break;
	}
}
