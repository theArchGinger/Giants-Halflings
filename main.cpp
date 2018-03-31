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
 * 	When splitting, players roll one additional die per split, normal rules apply
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


void print_rules(void);
void test_RNG(void);


int main(void)
{
	char selection; // user entered char to selet menu item
	bool quit_game = false;

	// print starting info
	cout<<"Welcome to Giants & Halflings";


	while(!quit_game)
	{
		
		// take user input
		cout<<"\n\n--------------------------------------------------\n";
		cout<<"To view the rules, enter 'v'\n";
		cout<<"To test the RNG, enter 't'\n";
		cout<<"To set up a game, enter 's'\n";
		cout<<"To quit this program, enter 'q'\n";
		cin>>selection;
		cout<<"\n";

		// respond
		switch(selection)
		{
			case('r'):
			case('v'): // view rules
				print_rules();
				break;
			case('t'): // test RNG
				test_RNG();
				break;
			case('s'):
				//has_played_game = true;
				//startGame(game_diff, purse);
				//game_diff = changeDiff(game_diff);
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
				quit_game = true;
				break;
			default:
				cout<<"no matching action found, returning to main menu...\n\n";
		}
	}

	return 0;
}

void print_rules()
{
	cout<<"The rules are as follows:\n";
	cout<<"\"Giants & Halflings\" or \"G&H\"\n";
	cout<<"Dealer rolls 1d10 or the \"Giant,\" setting target number or the \"Knee\"\n";
	cout<<"If dealer rolls a 1, the Giant \"Kicks\" and the House wins\n";
	cout<<"Player rolls 2d6 or the \"Halflings,\" trying to match or exceed the Knee\n";
	cout<<"On a double 1 roll, a snake scares the Giant and bets push\n";
	cout<<"If player rolls 11/12 or the \"Maw\", the Halflings are eaten and the House wins\n";
	cout<<"If the Knee is 2-3, House pays 1:1\n";
	cout<<"If the Knee is 4-6, House pays 2:1\n";
	cout<<"If the Knee is 7-9, House pays 3:1\n";
	cout<<"If the Knee is  10, House pays 5:1\n";
	cout<<"Players that Hit the Knee Exactly may split the dice by doubling their bet\n";
	cout<<"When splitting, players roll one additional die per split, normal rules apply\n";
	cout<<"The player may split a second time if they wish to become legendary";
}

void test_RNG()
{
	int die_size, num_trials, new_random;
	int results[die_size] = {};
	

	cout<<"Testing RNG\n";

	cout<<"Enter the number of sides on the die: ";
	cin>>die_size;
	if(die_size < 1)
		return;

	std::mt19937 generator((unsigned int) time(0)); // seed number generator
	std::uniform_real_distribution<double> dis(1, die_size+1); // define distribution, has to be after die_size init

	cout<<"\nEnter number of trials: ";
	cin>>num_trials;

	for(int i=0; i<num_trials; i++) // for the number of trials
	{
		results[((int) dis(generator))-1]++; // increment the result of the number "rolled"
		//cout<<dis(generator)<<"\n";
	}

	cout<<"\nResults:\n";
	for(int j=0; j<die_size; j++)
		cout<<j+1<<"s: "<<results[j]<<"\n";
}

/*
void setup_game()
{
	unsigned int purse, bet;
	int half1;

	std::mt19937 generator((unsigned int) time(0)); // seed number generator
	std::uniform_real_distribution<double> half_roller(1, 7);

	// select difficulty (starting money (easy, medium, hard, custom))
	

	// get player bet
	

	// roll one halfling
	half1 = (int) half_roller(generator);

	// start the rest of the game
	play_game(purse, bet, half1, false);
}

void play_game(unsigned int purse, unsigned int bet, int half1, bool ask_user) // recursive function to handle splitting
{
	bool is_splitting;
	int half2, giant;

	std::mt19937 generator((unsigned int) time(0)); // seed number generator
	std::uniform_real_distribution<double> giant_roller(1, 11);
	std::uniform_real_distribution<double> half_roller(1, 7);

	// roll giant
	giant = (int) giant_roller(generator);

	// check for kick
	

	// roll other halfling
	half2 = (int) half_roller(generator);

	// check for maw
	
	// check for snake
	
	// check for possible split
	if(half1+half2 == giant)
	{
		// check if player has enough money in purse to split
		

		cout<<"You hit the Knee exactly! Would you like to split? (y for yes, n for no): "
		cin>>is_splitting;
		if(is_splitting)
			play_game(half1);
			cout<<"\nNow for the other half of the split\n";
			play_game(half2);
	}

	// check for win
	
	// else loss
	
}

test_game() // imagine a dark game... basicly test_RNG for play_game
{
	//play_game with an additional boolean argument for user input?
	unsigned int purse, bet;
	int half1;

	std::mt19937 generator((unsigned int) time(0)); // seed number generator
	std::uniform_real_distribution<double> half_roller(1, 7);

	cout<<"Enter starting purse amount: ";
	cin>>purse;

	cout<<"\nEnter bet amount: "
	cin>>bet;

	half1 = (int) half_roller(generator);

	cout<<"\nWould you like to split every ime it is possible? 'y' for yes, 'n' for no: ";
	cin>>is_splitting

	play_game(purse, bet, half1, true);
}
 */


