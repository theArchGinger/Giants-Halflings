/*
 * Giants & Halflings
 * 
 * The rules are as follows:
 * 	"Giants & Halflings" or "G&H"
 * 	Dealer rolls 1d10 or the "Giant," setting target number or the "Knee"
 * 	If dealer rolls a 1, the Giant "Kicks" and the House wins
 * 	Player rolls 2d6 or the "Halflings," trying to match or exceed the Knee
 * 	On a double 1 roll, a snake scares the Giant and bets push
 * 	If player rolls 11/12 or the "Maw", the Halflings are eaten and the House wins
 * 	If the Knee is 2-3, House pays 1:1
 * 	If the Knee is 4-6, House pays 2:1
 * 	If the Knee is 7-9, House pays 3:1
 * 	If the Knee is 10, House pays 5:1
 * 	Players that Hit the Knee Exactly may split the dice by doubling their bet
 * 	When splitting,players roll one additional die per split, normal rules apply
 * 	The player may split a second time if they wish to become legendary
 */

/*
 * Assuming you're using a UNIX system with g++ installed
 * to compile:
 * g++ main.cpp -o gnh -std=c++11
 * 
 * to run:
 * ./gnh
 */

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>


using std::cout;
using std::cin;

int main(void)
{
	char selection; // user entered char to selet menu item
	
	// print starting info
	cout<<"Welcome to Giants & Halflings\n";
	
	// take user input
	cout<<"To set up a game, enter 's'\n";
	cout<<"To quit this program, enter 'q'\n";
	cin>>selection;
	cout<<"\n";
	
	// respond
	switch(selection)
	{
		case('r'):
		case('v'): // view rules
			//printRules();
			break;
		case('t'): // test RNG
			//testRNG();
			break;
		case('c'):
			//game_diff = changeDiff(game_diff);
			break;
		case('s'):
			//has_played_game = true;
			//startGame(game_diff, purse);
			/*do
			{
				startGame(game_diff);
				cout<<"Would you like to keep playing? Either enter a bet, or 'n': ";
				cin>>keep_playing;
			}while(keep_playing != 'n');*/
			break;
		case('g'):
			//testGame();
			break;
		case('q'):
			break;
		default:
			cout<<"no matching action found, returning to main menu...\n\n";
	}
	
	return 0;
}
