/*
 * ui.h
 *
 *  Created on: May 4, 2025
 *      Author: ebokm
 */

#ifndef INC_UI_H_
#define INC_UI_H_

#include "max3485.h"

volatile  uint8_t page = 1;
uint8_t menu = 1;
volatile  uint8_t select = 1;
volatile  uint8_t conf = 0;

extern volatile float rs485;

volatile uint8_t update = 0;

volatile  int16_t max_well_level = 20;
volatile  int16_t min_well_level = 0;
volatile  int16_t max_level = 18;
volatile  int16_t min_level = 10;

volatile float diameter = 28;
volatile uint16_t X = 200;
volatile uint16_t Y = 200;

volatile uint8_t brightness = 10; //0-255

const char *form = "cy";

void ui(void){

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
					 send_to_screen(0b11011011, 'b', 'd');
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

		case 2: //menu selecter
			switch(page){
				case 1:
					 cursor_pos(1, 1);
					 write_to_screen("Setting Displays");
					 cursor_pos(2, 1);
					 write_to_screen("    Tutorial    ");
					 switch(select){
						case 1:
							 cursor_pos(1, 1);
							 if(conf == 1){
								 menu = 3;
								 conf = 0;
								 select = 1;
								 page = 2;
								 update = 1;
							 }
						break;

						case 2:
							 cursor_pos(1, 9);
							 if(conf == 1){
								 menu = 4;
								 conf = 0;
								 select = 1;
								 page = 2;
								 update = 1;
							 }
						break;

						case 3:
							 cursor_pos(2, 5);
							 if(conf == 1){
								 menu = 1;
								 conf = 0;
								 select = 1;
								 page = 1;
								 update = 1;
							 }
						break;

						default:
							select = 1;
							update = 1;
						break;
					}
				break;

				default:
					page = 1;
					update = 1;
				break;
			}
		break;

		case 3: //settings selector
			switch(page){

				case 1:
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

				case 2:
					cursor_pos(1, 1);
					write_to_screen("  Min/Max Well  ");
					cursor_pos(2, 1);
					write_to_screen("  Min/Max Limit ");
					switch(select){
						case 1:
							 cursor_pos(1, 3);
							 if(conf == 1){
								 menu = 5;
								 conf = 0;
								 select = 1;
								 page = 2;
								 update = 1;
							 }
						break;

						case 2:
							 cursor_pos(2, 3);
							 if(conf == 1){
								 menu = 6;
								 conf = 0;
								 select = 1;
								 page = 2;
								 update = 1;
						 }
							 break;

						default:
							select = 1;
							update = 1;
						break;
				}
				break;

				case 3:
					cursor_pos(1, 1);
					write_to_screen(" Well form      ");
					cursor_pos(2, 1);
					write_to_screen(" Well dimensions");
					switch(select){
						case 1:
							 cursor_pos(1, 2);
							 if(conf == 1){
								 menu = 7;
								 conf = 0;
								 select = 1;
								 page = 2;
								 update = 1;
							 }
						break;

						case 2:
							 cursor_pos(2, 2);
							 if(conf == 1){
								 menu = 8;
								 conf = 0;
								 select = 1;
								 page = 2;
								 update = 1;
						 }
							 break;

						default:
							select = 1;
							update = 1;
						break;
				}
				break;

				case 4:
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

				default:
					page = 2;
					update = 1;
				break;
			}
		break;

		case 4: //displays
			switch(page){

				case 1:
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

				case 2:

					 cursor_pos(1, 1);
					 write_to_screen("  water level   ");
					 cursor_pos(2, 1);
					 write_to_screen("  ");
					 float_to_screen(rs485);
					 write_to_screen(" cm             ");
					 update = 1;
				break;

				case 3:

					float volume = 0;

					if(strcmp(form, "cy") == 0){
						volume = ((diameter/2) * (diameter/2) * 3.14159 * rs485) / 1000.0f;
					}
					else{
						volume = (X * Y * rs485) / 1000.0f;
					}

					 cursor_pos(1, 1);
					 write_to_screen("  water volume  ");
					 cursor_pos(2, 1);
					 write_to_screen("  ");
					 float_to_screen(volume);
					 write_to_screen(" L              ");
					 update = 1;
				break;

				case 4:
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

				default:
					page = 2;
					update = 1;
				break;
			}
		break;

		case 5: //well level
			switch(page){

				case 1:
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
					 }
				break;

				case 2:
					cursor_pos(1, 1);
					 write_to_screen("Here you set the");
					 cursor_pos(2, 1);
					 write_to_screen("max and min    >");
				break;

				case 3:
					cursor_pos(1, 1);
					 write_to_screen("  of the well.  ");
					 cursor_pos(2, 1);
					 write_to_screen("                ");
				break;

				case 4:
					cursor_pos(1, 1);
					 write_to_screen(" Max level well ");
					 cursor_pos(2, 1);
					 digit_to_screen(max_well_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){
						 max_well_level++;
						 select = 1;
						 update = 1;
					 }
					 if(conf == 1){
						 max_well_level--;
						 conf = 0;
						 update = 1;
					 }
				break;

				case 5:
					cursor_pos(1, 1);
					 write_to_screen(" Min level well ");
					 cursor_pos(2, 1);
					 digit_to_screen(min_well_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){
						 min_well_level++;
						 select = 1;
						 update = 1;
					 }
					 if(conf == 1){
						 min_well_level--;
						 conf = 0;
						 update = 1;
					 }
				break;

				case 6:
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
					 }
				break;

				default:
					page = 2;
					update = 1;
				break;
		}
		break;

		case 6: //limit level
			switch(page){

				case 1:
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
					 }
				break;

				case 2:
					cursor_pos(1, 1);
					 write_to_screen("Here you set the");
					 cursor_pos(2, 1);
					 write_to_screen("max and min    >");
				break;

				case 3:
					cursor_pos(1, 1);
					 write_to_screen(" for the water  ");
					 cursor_pos(2, 1);
					 write_to_screen(" level you want.");
				break;

				case 4:
					cursor_pos(1, 1);
					 write_to_screen("   Max limit    ");
					 cursor_pos(2, 1);
					 digit_to_screen(max_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){
						 max_level++;
						 select = 1;
						 update = 1;
					 }
					 if(conf == 1){
						 max_level--;
						 conf = 0;
						 update = 1;
					 }
				break;

				case 5:
					cursor_pos(1, 1);
					 write_to_screen("   Min limit    ");
					 cursor_pos(2, 1);
					 digit_to_screen(min_level);
					 write_to_screen(" cm             ");
					 if(select >= 2){
						 min_level++;
						 select = 1;
						 update = 1;
					 }
					 if(conf == 1){
						 min_level--;
						 conf = 0;
						 update = 1;
					 }
				break;

				case 6:
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
					 }
				break;

				default:
					page = 2;
					update = 1;
				break;
		}
		break;

		case 7: //form selector
			switch(page){

				case 1:
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

				case 2:
					 cursor_pos(1, 1);
					 write_to_screen("Here you select ");
					 cursor_pos(2, 1);
					 write_to_screen("the form off   >");
				break;

				case 3:
					 cursor_pos(1, 1);
					 write_to_screen("   the well.    ");
					 cursor_pos(2, 1);
					 write_to_screen("                ");
				break;

				case 4:
					 cursor_pos(1, 1);

					 if(strcmp(form, "cy") == 0){
						 write_to_screen("   ");
						 send_to_screen(0b11111111 ,'b', 'd');
					 }
					 else{
						 write_to_screen("   O");
					 }

					 write_to_screen(" cylinder       ");
					 cursor_pos(2, 1);

					 if(strcmp(form, "cu") == 0){
						 write_to_screen("   ");
						 send_to_screen(0b11111111 ,'b', 'd');
					 }
					 else{
						 write_to_screen("   O");
					 }

					 write_to_screen(" cuboid         ");

					 switch(select){
						case 1:
							 cursor_pos(1, 3);
							 if(conf == 1){
								 conf = 0;
								 form = "cy";
								 update = 1;
							 }
						break;

						case 2:
							 cursor_pos(2, 3);
							 if(conf == 1){
								 conf = 0;
								 form = "cu";
								 update = 1;
						 }
						 break;

						default:
							select = 1;
							update = 1;
						break;
					 }
				break;

				case 5:
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

				default:
					page = 2;
					update = 1;
				break;
			}
			break;

			case 8: //dimensions selector
				switch(page){

					case 1:
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

					case 2:
						 cursor_pos(1, 1);
						 write_to_screen("Here you give   ");
						 cursor_pos(2, 1);
						 write_to_screen("the dimensions >");
					break;

					case 3:
						 cursor_pos(1, 1);
						 write_to_screen(" off the well.  ");
						 cursor_pos(2, 1);
						 write_to_screen("                ");
					break;

					case 4:
						if (strcmp(form, "cy") == 0) {
							cursor_pos(1, 1);
							write_to_screen("   diameter:    ");
							cursor_pos(2, 1);
							write_to_screen("   ");
							digit_to_screen(diameter);
							write_to_screen(" cm             ");
							 if(select >= 2){
								 diameter++;
								 select = 1;
								 update = 1;
							 }
							 if(conf == 1){
								 diameter--;
								 conf = 0;
								 update = 1;
							 }
						}

						else {
							cursor_pos(1, 1);
							write_to_screen("X:              ");
							cursor_pos(2, 1);
							digit_to_screen(X);
							write_to_screen(" cm             ");
							 if(select >= 2){
								 X++;
								 select = 1;
								 update = 1;
							 }
							 if(conf == 1){
								 X--;
								 conf = 0;
								 update = 1;
							 }
						}
					break;

					case 5:
						if (strcmp(form, "cy") == 0) {
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
						}

						else {
							cursor_pos(1, 1);
							write_to_screen("Y:              ");
							cursor_pos(2, 1);
							digit_to_screen(Y);
							write_to_screen(" cm             ");
							 if(select >= 2){
								 Y++;
								 select = 1;
								 update = 1;
							 }
							 if(conf == 1){
								 Y--;
								 conf = 0;
								 update = 1;
							 }
						}
					break;

					case 6:
						if (strcmp(form, "cy") == 0) {
							page = 5;
						}

						else {
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
						}
					break;

					default:
						page = 2;
						update = 1;
					break;
				}
				break;

		default:
			menu = 2;
		break;
	}

}

#endif /* INC_UI_H_ */
