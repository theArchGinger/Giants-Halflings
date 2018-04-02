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
 * make
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


#define EASY_AMOUNT 	500
#define MEDIUM_AMOUNT 	250
#define HARD_AMOUNT		100


void print_rules(void);
void test_RNG(void);
unsigned int setup_game(void);
unsigned int play_game(unsigned int start_purse, unsigned int bet, int half1, int giant, bool ask_user, bool is_splitting);
unsigned int do_win(unsigned int purse, unsigned int bet, int giant);
unsigned int do_loss(unsigned int purse, unsigned int bet);


int main(void)
{
	char selection; // user entered char to selet menu item
	bool quit_game = false;
	unsigned int prev_purse;

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
				/*do
				{*/
					prev_purse = setup_game();
					/*cout<<"Would you like to keep playing? Either enter 'y" or 'n': ";
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
		//cout<<dis(generator)<<"\n"; // uncomment to print all generated numbers
		//cout<<(int) dis(generator)<<"\n"; // uncomment to print all generated numbers cast as int
	}

	cout<<"\nResults:\n";
	for(int j=0; j<die_size; j++)
		cout<<j+1<<"s: "<<results[j]<<"\n";
}

unsigned int setup_game()
{
	unsigned int start_purse, bet, end_purse;
	int diff;
	int half1, giant;
	char again;
	bool play_again;

	std::mt19937 generator((unsigned int) time(0)); // seed number generator
	std::uniform_real_distribution<double> half_roller(1, 7);
	std::uniform_real_distribution<double> giant_roller(1, 11);

	// select difficulty (starting money (easy, medium, hard, custom))
	do
	{
		cout<<"\nInitial coin amounts per dificulty:\n";
		cout<<"Easy:    "<<EASY_AMOUNT;
		cout<<"\nMedium:  "<<MEDIUM_AMOUNT;
		cout<<"\nHard:    "<<HARD_AMOUNT;
		cout<<"\nOr a Custom Amount";
		cout<<"\n\nEnter 1 for easy, 2 for medium, 3 for hard, or 4 for a custom amount: ";
		cin>>diff;
	}while( (diff < 1) || (diff > 4) );

	switch(diff)
	{
		case(1):
			start_purse = EASY_AMOUNT;
			break;
		case(2):
			start_purse = MEDIUM_AMOUNT;
			break;
		case(3):
			start_purse = HARD_AMOUNT;
			break;
		case(4):
			cout<<"Enter a starting purse amount: ";
			cin>>start_purse;
			break;
		default:
			start_purse = EASY_AMOUNT;
			cout<<"unrecognized selection, defaulting to "<<EASY_AMOUNT<<"\n";
	}
	cout<<"You now have "<<start_purse<<" coins.";

	// start game loop
	do
	{
		// get player bet
		do
		{
			cout<<"\n\nHow many would you like to wager?\n";
			cin>>bet;
			if(bet > start_purse)
				cout<<"You don't have enough coins to wager that much.\n";
		}while(bet > start_purse);

		// roll one halfling
		half1 = (int) half_roller(generator);

		// roll giant
		giant = (int) giant_roller(generator);

		// start the rest of the game
		end_purse = play_game(start_purse, bet, half1, giant, false, false);

		// print ending
		cout<<"Your purse is now "<<end_purse<<".\n";

		do
		{
			cout<<"Would you like to play again?('y' for yes, 'n' for no)\n";
			cin>>again;
		}while( (again != 'y') && (again != 'n') );
		switch(again)
		{
			case('y'):
				play_again = true;
				break;
			case('n'):
				play_again = false;
				break;
		}
	}while(play_again);

	return end_purse;
}

unsigned int play_game(unsigned int start_purse, unsigned int bet, int half1, int giant, bool ask_user, bool is_splitting)
// recursive function to handle splitting
{
	int half2;
	unsigned int inter_purse, end_purse;

	std::mt19937 generator((unsigned int) time(0)); // seed number generator
	std::uniform_real_distribution<double> half_roller(1, 7);

	cout<<"\nThe Giant is "<<giant<<"\n";
	// check for kick
	if(giant == 1)
	{
		cout<<"The Giant kicked! House wins.";
		end_purse = do_loss(start_purse, bet);
	}
	else
	{
		// roll other halfling
		half2 = (int) half_roller(generator);
		cout<<"Halfling 1: "<<half1;
		cout<<"\nHalfling 2: "<<half2<<"\n";

		// check for snake
		if( (half1 == 1) && (half2 == 1) )
		{
			cout<<"A snake scared the Giant!\n";
			end_purse = do_win(start_purse, bet, giant);
		}
		// check for maw
		else if( (half1+half2) >= 11)
		{
			cout<<"The halflings were eaten by the Maw!\n";
			end_purse = do_loss(start_purse, bet);
		}
		// check for possible split
		else if( (half1+half2) == giant)
		{
			// check if player has enough money in purse to split
			

			cout<<"You hit the Knee exactly! Would you like to split? (y for yes, n for no): ";
			cin>>is_splitting;
			if(is_splitting)
			{
				inter_purse = (start_purse, bet, half1, giant, ask_user, is_splitting);
				cout<<"\nNow for the other half of the split";
				play_game(inter_purse, bet, half2, giant, ask_user, is_splitting);
			}
			cout<<"\n";
		}
		// check for win
		else if( (half1+half2) > giant)
		{
			cout<<"You win!\n";
			end_purse = do_win(start_purse, bet, giant);
		}
		// else loss
		else
		{
			cout<<"You lost.\n";
			end_purse = do_loss(start_purse, bet);
		}
	}

	return end_purse;
}

unsigned int do_win(unsigned int purse, unsigned int bet, int giant)
{
	return purse+(bet*giant); //TODO actually do the payout in the rules
}

unsigned int do_loss(unsigned int purse, unsigned int bet)
{
	/*unsigned int end_purse = purse - bet;
	cout<<"You now have "<<end_purse<<" coins remaining.\n";
	return end_purse;*/
	return purse-bet;
}
/*
test_game() // imagine a dark game... basicly test_RNG for play_game
{
	//play_game with an additional boolean argument for user input?
	unsigned int start_purse, bet, trials, end_purse;
	int half1;

	std::mt19937 generator((unsigned int) time(0)); // seed number generator
	std::uniform_real_distribution<double> half_roller(1, 7);
	std::uniform_real_distribution<double> giant_roller(1, 11);

	cout<<"Enter starting purse amount: ";
	cin>>start_purse;

	cout<<"\nEnter bet amount: "
	cin>>bet;

	cout<<"\nWould you like to split every ime it is possible? 'y' for yes, 'n' for no: ";
	cin>>is_splitting

	<cout<<"Wnternumberof games to play: ";
	cin>>trials;

	for(; trials>0; trials--)
	{
		// roll giant
		giant = (int) giant_roller(generator);

		// roll halfling
		half1 = (int) half_roller(generator);

		end_purse = play_game(start_purse, bet, half1, giant, false, is_splitting);
	}

	// print results
	//cout<<"\nstarting purse: "<<start_purse<<"\n";
	
	// this might have to wait for implmentation of more complex data structures
}
 */


