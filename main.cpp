#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <algorithm>
using namespace std;

class Spyfall {
private:
    string playerNames[20];
    int numOfPlayers;
    int roundTime;
    string item;
public:

void message(string message) {
    cout << message;
    cin.ignore();
}

void topScreen() {
    for(int i = 0; i < 120; i++) {
        cout << "~";
    }
    cout << endl;
}

void mainScreen() {
    topScreen();
    cout << "\t\t\t\t " << "---------------------------------------------------------" << endl
         << "\t\t\t\t\t\t\t  " << "Spyfall" << endl
         << "\t\t\t\t " << "---------------------------------------------------------" << "\n\n\n";
}

void rules() {
    mainScreen();
    cout << "The Rules" << endl
         << "=========" << endl;
    cout << " Starting Phase: " << endl
         << " 1. Players choose a category, such as a location or food." << endl
         << " 2. One player is randomly assigned the role of the 'spy', while the others receive a location or food." << "\n\n";
    cout << " Questioning Phase:" << endl
         << " 1. Players take turns asking each other yes or no questions about the location or item." << endl
         << " 2. The goal is for the non-spy players to figure out who the spy is based on their answers." << endl
         << " 3. The spy tries to blend in and guess the location or item without revealing their identity." << "\n\n";
    cout << " Voting Phase:" << endl
         << " After a set amount of time or when players feel ready, they enter the voting phase." << endl
         << " 1. Each player secretly votes for who they believe the spy is." << endl
         << " 2. The player with the most votes is accused of being the spy." << endl
         << " 3. If the spy receives the most votes, they reveal their role. If a non-spy receives the most votes, the spy wins." << "\n\n";

    system("pause");
}

int number_Of_Players() {
    system("cls");
    mainScreen();
    do {
        cout << "Enter number of players: ";
        cin >> numOfPlayers;
        if(numOfPlayers < 3)
            cout << "Not enough players; the minimum number required is 3." << "\n\n";
    }while(numOfPlayers < 3);

    return numOfPlayers;
}

void set_Player_Names() {
    cout << "Enter the names of the players: " << endl;
    for(int i = 0; i < numOfPlayers; i++) {
        cout << i+1 << "- ";
        cin >> playerNames[i];
    }
}

int timer() {
    system("cls");
    mainScreen();

    do{
        cout << "Set the duration of the round (in minutes <= 10): ";
        cin >> roundTime;
    }while(roundTime < 1 || roundTime > 10);

    system("cls");

    roundTime = roundTime * 60;

    return roundTime;
}

void count_Down(int timing) {
    while(timing > 0) {
        system("cls");
        mainScreen();
        cout << "\nQuestion phase in progress:" << endl;
        cout << "You have: "<< timing << " secs left.";
        --timing;
        Sleep(1000);
    }
}

string places_Category() {
    string place;

    srand(time(NULL));
    int random = rand() % 6 + 1;

    switch(random) {
        case 1: {
            place = "Barber Shop";
            break;
        }
        case 2: {
            place = "Church";
            break;
        }
        case 3: {
            place = "Library";
            break;
        }
        case 4: {
            place = "Beauty Salon";
            break;
        }
        case 5: {
            place = "School";
            break;
        }
        case 6: {
            place = "Pharmacy";
            break;
        }
    }

    return place;
}

string foods_Category() {
    string food;

    srand(time(NULL));
    int random = rand() % 6 + 1;

    switch(random) {
        case 1: {
            food = "Fool";
            break;
        }
        case 2: {
            food = "Fries";
            break;
        }
        case 3: {
            food = "Eggs";
            break;
        }
        case 4: {
            food = "Cake";
            break;
        }
        case 5: {
            food = "Ice Cream";
            break;
        }
        case 6: {
            food = "Chips";
            break;
        }
    }

    return food;
}

string choose_Category() {
    int choice;

    mainScreen();

    do {
        cout << "Choose a category: " << endl
             << "(1) Foods" << endl
             << "(2) Location" << endl
             << "Choice: ";
        cin >> choice;
        cout << endl;
    }while(choice < 1 || choice > 2);

    if(choice == 1) {
        item = foods_Category();
    } else {
        item = places_Category();
    }

    return item;
}

int view_Role(int iterations, string item) {
    srand(time(NULL));

    int spy = rand() % iterations + 1;

    message("Press 'Enter' to view roles...");
    system("cls");
    mainScreen();

    for(int i = 1; i <= iterations; i++) {
        cout << "Pass the phone to " << playerNames[i-1];
        message("...");
        system("cls");
        mainScreen();

        if(spy == i) {
            spy = i-1;
            cout << "You're the spy!" << endl;
            message("Continue...");
            system("cls");
            mainScreen();
        } else {
            cout << "The item is: " << item << endl;
            message("Continue...");
            system("cls");
            mainScreen();
        }
    }

    return spy;
}

int voting_Phase() {
    int choice;
    int votes[numOfPlayers] = {0};

    message("Press 'Enter' to start voting phase...");
    system("cls");

    for(int i = 1; i <= numOfPlayers; i++) {
        mainScreen();
        cout << "Pass the phone to " << playerNames[i-1]<< endl;
        system("pause");

        system("cls");
        mainScreen();

        for(int i = 0; i < numOfPlayers; i++) {
            cout << i+1 << ") " << playerNames[i] << endl;
        }
        cout << "Who do you think is the spy: ";
        cin >> choice;

        votes[choice - 1] += 1;

        system("cls");
    }

    sort(votes, votes + numOfPlayers);

    for(int i = 0; i < numOfPlayers; i++) {
        cout << votes[i] << " ";
    }
    system("pause");

    return votes[numOfPlayers-1];
}

void game_Play() {
    char option;
    rules();

    do {
        int numOfPlayers = number_Of_Players();
        set_Player_Names();
        int roundTime = timer();
        string item = choose_Category();

        int spy = view_Role(numOfPlayers, item);

        mainScreen();
        count_Down(3);

        system("cls");
        mainScreen();

        int mostVotes = voting_Phase();
        message("Press 'Enter' to see who was voted out...");

        if(playerNames[spy] == playerNames[mostVotes]) {
           cout << playerNames[mostVotes] << " was voted out" << endl;
           cout << "You voted right!";
        } else {
            cout << playerNames[mostVotes] << " was wrongfully voted out!";
        }

        system("pause");

        system("cls");
        mainScreen();

        cout << "\nDo you want to play another round (y/n): ";
        cin >> option;
    }while(option == 'y' || option == 'Y');

    system("cls");
    mainScreen();
    cout << "\t\t\t\t\t\t     " << "Thanks For Playing" << endl
         << "\t\t\t\t\t\t     " << "==================" << "\n\n\n\n\n";
}

};

int main()
{
    Spyfall theGame;
    theGame.game_Play();

    return 0;
}
