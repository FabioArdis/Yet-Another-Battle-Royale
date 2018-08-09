#include <iostream> //cout, cin...
#include <string.h> //string type...
#include <stdlib.h> //rand()...
#include <time.h>   //time()...

using namespace std;

int players = 12;           //Number of players
int playersAlive = players; //Number of players alive always equal to the players
int playersDead = 0;        //Number of dead players
int round = 1;              //What's the actual round?
int countPosition = players;//What's the position of the dead player?

string names[60] = {
	"Sam", "Jude", "Leonard", "Alicia",
	"Max", "Martha", "Alexander", "Rose",
	"Dexter", "Lauren", "Cody", "Shannon",
	"Alex", "Lara", "Jordan", "Rebecca",
	"Sean", "Bella", "Scott", "Molly",
	"Noah", "Ellie", "Zac", "Sienna",
	"Matthew", "Marianna", "Jake", "Linda",
	"Lee", "Ruby", "Kane", "Riley",
	"Nathan", "Monica", "Bobby", "Zoe",
	"Tom", "Carla", "Fabio", "Emilia",
	"Roger", "Faith", "Caleb", "Rosy",
	"Logan", "Isabella", "Josh", "Taylor",
	"Kevin", "Jasmine", "Daniel", "Lorelai",
	"Charlie", "Lydia", "Jonah", "Scarlett",
	"Paul", "Lucy", "Robert", "Autumn",
};

struct Player
{
	string name;            //Player's name
	bool isAlive = true;    //Player's status
	int position = players; //Player's position (always the last)
};

struct Player* Players = new Player[players];

void resetPlayers();
void start();
void playRound();
void playerEvent();

int main(int argc, char const *argv[])
{
	start();    //Initialize the game
	return 0;
}

void playRound()
{
	cout << "Round " << round << endl;
	cout << "Players alive: " << playersAlive << endl << endl;
	playerEvent();  //Shows what happens
	round++;        //Continues the round count
	cout << endl << endl;
	playRound();    //Recursive function
}

void playerEvent()
{
    /*
        If there's more than two players alive and if one
        of the selected players is alive and not the only alive
        then it plays a random event (dead or alive)
    */

	if(playersAlive > 1){
		for (int i = 0; i < players; ++i)
			if(Players[i].isAlive == true && playersAlive > 1)
				if((rand()%2) == 1){
					playersAlive--;
					cout << Players[i].name << " dies." << endl;
					Players[i].isAlive = false;
					Players[i].position = countPosition--;
					cout << Players[i].name << " classified " << Players[i].position << endl;
				}
	}
	else
	{
		for (int i = 0; i < players; ++i)
			if(Players[i].isAlive == true){
				int selection = 1;
				cout << Players[i].name << " wins!" << endl << endl;
				cout << "Do you want to retry?1-Yes 0-No" << endl;
				cin >> selection;
				if(selection == 1)
					start();
				else
					exit(EXIT_SUCCESS);
			}
	}
}

void start()
{
	cout << "Select Players." << endl;
	cin >> players;
	resetPlayers();
	playRound();
}

void resetPlayers()
{
    //Deletes the struct then it recreates itself.
	delete [] Players;
	struct Player* Players = new Player[players];
	//Reinitialize the values.
	for (int i = 0; i < players; ++i)
	{
		int r = (rand()%60);
		Players[i].name = names[r];
		Players[i].isAlive = true;
		Players[i].position = players;
	}
	playersAlive = players;
	playersDead = 0;
	round = 1;
	countPosition = players;
}
