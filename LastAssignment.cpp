/*******************************************************
Student Name:           Dhruv Patel
Student No:				040-997-897
Assignment name:		Memory Game
Assignment Number:      3
Course Name and Number:	CST8219 c++ Programming
Lab Section:			302
Due Date:				16 April 2021
Submission Date:		16 April 2021
*******************************************************/

#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/widgets/picture.hpp>
#include <nana/audio/player.hpp>
#include <nana/threads/pool.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <string>
#include <list>
#include <map>
#include <vector>
#include<stdio.h>
#include <iostream>
#include <algorithm>

/********************************
Function name:		main
Purpose:			Memory Game
Author Name:		Dhruv Patel
********************************/
int main()
{
	using namespace nana;

	/* Image vector for all colors */
	std::vector<paint::image> images = { nana::paint::image("black.bmp"), nana::paint::image("grey.bmp"), 
		nana::paint::image("blue.bmp"), nana::paint::image("yellow.bmp"), nana::paint::image("brown.bmp"), 
		nana::paint::image("green.bmp"), nana::paint::image("purple.bmp"), nana::paint::image("orange.bmp"), 
		nana::paint::image("white.bmp"), nana::paint::image("pink.bmp"), nana::paint::image("black.bmp"), 
		nana::paint::image("grey.bmp"), nana::paint::image("blue.bmp"), nana::paint::image("yellow.bmp"), 
		nana::paint::image("brown.bmp"), nana::paint::image("green.bmp"), nana::paint::image("purple.bmp"), 
		nana::paint::image("orange.bmp"), nana::paint::image("white.bmp"), nana::paint::image("pink.bmp") };

	/* Image vector for back side which is common for all*/
	paint::image back;

	/* Audio Initialization */
	audio::player click("can_pop.wav");
	audio::player match("boxing_bell.wav");
	audio::player nonMatch("blip.wav");
	audio::player success("charge.wav");

	threads::pool pool(1);

	/* Window */
	form window{ API::make_center(850,550) };

	/* Window caption that is shown at the top*/
	window.caption("Memory Game");
	static place setWindow(window);
	drawing draw(window);

	/* Making Grids for all cards */
	setWindow.div("<Mycard grid=[5, 4] margin=[5,110,5,110] gap=20>");

	static std::map<char, button*> cardsArray;
	std::list<button> buttons;
	
	/* Calling image for back which is common while starting */
	back = nana::paint::image("front.bmp");

	/* Vector to locating, managing and displaying all color image*/
	std::vector<int> cardNumber = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };

	/* For random generation of card at starting of the game */
	srand((unsigned int)std::time(0));
	random_shuffle(cardNumber.begin(), cardNumber.end());

	/* Initializing local variable */
	int clickCount = 0, previousNumber = -1, compareNumber = -1, winCount = 0;
	bool isClicked = false, additionalCheck = false;

	/* Initializing label to print at the end to display message of game finish */
	label endlabel(window, nana::rectangle(0, 0, 100, 20));
	nana::msgbox quitMessage(window, "Play Again / Quit", nana::msgbox::yes_no);

	/* Loop to keep track of each card */
	for (auto count : cardNumber) {

		buttons.emplace_front((window).handle());

		auto& cardAsButton = buttons.front();
		cardsArray[count] = &cardAsButton;

		/* Setting back image that is common for all card at the begining */
		cardAsButton.icon(back);

		setWindow["Mycard"] << cardAsButton;

			/* Event when the card is click to have to analyse the output */
			cardAsButton.events().click(pool_push(pool, [&, count]()
			{
				
				/* This if statement works when there is second click the second time*/
				if (isClicked) {
					/* This if/else set the compareNumber to mactch the current number */
					if (previousNumber <= 9) {
						compareNumber = previousNumber + 10;
					}
					else {
						compareNumber = previousNumber - 10;
					}
				}

				cardAsButton.icon(images[count]);
				click.play();
				clickCount++; /* To count number of turns */

				/* This if statement is for Winning*/
				if (isClicked && count == compareNumber) {
					cardsArray[count]->hide();
					cardsArray[previousNumber]->hide();
					match.play();
					isClicked = false;
					compareNumber = -1;
					previousNumber = -1;
					additionalCheck = true;
					winCount++;
					std::cout << "Win count: " << winCount << std::endl;
				} /* This else if statement is foe Lossing */
				else if (isClicked && count != compareNumber) {
					cardsArray[count]->icon(back);
					cardsArray[previousNumber]->icon(back);
					nonMatch.play();
					isClicked = false;
					compareNumber = -1;
					previousNumber = -1;
					additionalCheck = true;
				}

				/* This is for the first click of the game when comparing from two clicks*/
				if (!isClicked) {
					isClicked = true;
					previousNumber = count;
				}

				/* This is to reset the booleans after the second check from two clicks are done to reset it for starting from first click again */
				if (additionalCheck) {
					isClicked = false;
					additionalCheck = false;
				}

				/* This is for the end of game message */
				if (winCount == 10) {
					success.play();
					std::cout << "Number of Turns: " << clickCount << std::endl;
					quitMessage << "Game Over" << std::endl;
					quitMessage << "Number of Turns: " << clickCount << std::endl;
					quitMessage << "Are you sure you want to exit if not click NO to play again ?" << std::endl;
					quitMessage();
				}
			}));		
	}
	setWindow.collocate();
	window.show();
	exec();
}
