#include <iostream>
#include <cstdlib>   // for clear screen
#include <windows.h> // for Sleep
#include <string>
#include <fstream>

using namespace std;

const int MAX_USERS = 100; // maximum number of users

struct details
{
    string userID;
    int password;
    int total_reps;
};

details users[MAX_USERS];
int userCount = 0;

int level;
string difficulty, response, warm_up = "DO SOME JUMPING JACKS", cool_down = "DO SOME STRETCHES";

void display_levels()
{
    cout << "What level you wanna try\n"
         << "Type 1 for beginner\n"
         << "    / / /  \n"
         << "   ( o.o )   \n"
         << "    > ^ <\n"
         << "Type 2 for Intermediate\n"
         << "     / / /\n"
         << "    ( o.o )\n"
         << "     | ^ |\n"
         << "Type 3 for Advanced\n"
         << "     // o  //.\n"
         << "    // o  //.\n"
         << "   // ^ //.\n";
    cin >> level;
    cin.ignore(); // To ignore the newline character left in the input buffer
    switch (level)
    {
    case 1:
        difficulty = "beginner";
        response = "you should do 10-15 reps\n";
        break;
    case 2:
        difficulty = "intermediate";
        response = "you should do 3-6 reps and 2 sets\n";
        break;
    case 3:
        difficulty = "advance";
        response = "you should do 13-20 reps and 3 sets\n";
        break;
    default:
        cout << "Invalid level selected.\n";
        display_levels(); // Recursively call until a valid level is selected
        break;
    }
}

void Welcome(details &info)
{
    cout << "\n WELCOME TO THE FITNESS TRACKER PRO";
    cout << "\n * THIS INNOVATIVE PROGRAM GOES BEYOND JUST TRACKING YOUR WORKOUTS";
    cout << "\n * TRACK YOUR PROGRESS AND STAY MOTIVATED BY EARNING BADGES";
    cout << "\n * RECEIVE WARM UP AND COOL DOWN RECOMMENDATIONS";
    cout << "\n * RECEIVE EXERCISE RECOMMENDATIONS (FOR EACH LEVEL)";
    cout << "\n * CHOOSE FROM OUR LIST OF EXERCISES OR EVEN ADD EXERCISES THAT YOU LIKE";
    cout << "\n * HOW IS FITNESS TRACKER PRO UNIQUE?";
    cout << "\n * BEGINNER FRIENDLY INTERFACE WITH CLEAR INSTRUCTIONS";
    cout << "\n * USE OF ASCII ART TO MAKE IT MORE VISUALLY APPEALING";
    cout << "\n * ABILITY TO ADD YOUR OWN EXERCISES";
    cout << "\n * FUTURE ENHANCEMENT PLANNED FOR A MORE PERSONALIZED EXPERIENCE USING OBJECT ORIENTED PROGRAMMING\n";

    // Create user account
    cout << "Create your Username: ";
    cin >> info.userID;
    cout << "Create your Password: ";
    cin >> info.password;
    cin.ignore(); // To ignore the newline character
    cout << "Your account has been successfully created\n";
    Sleep(1000);
    system("cls");

    // Login process
    for (int i = 0; i < 3; i++)
    {
        string username;
        int password;

        cout << "Enter your login info\n";
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (username == info.userID && password == info.password)
        {
            cout << "Login successful\n";
            break;
        }
        else
        {
            cout << "Incorrect username or password. Try again.\n";
            Sleep(1000);
            system("cls");
            if (i == 2)
            {
                cout << "You are exiting.";
                Sleep(1000);
                exit(0);
            }
        }
    }
}

void exercise_summary(const string &name, const string &Description, const string &difficulty, const string &response)
{
    cout << "\t\t\t\t\tSummary\n";
    cout << "Name: " << name << endl;
    cout << "Description: " << Description << endl;
    cout << "Difficulty Level: " << difficulty << endl;
    cout << "Virtual Coach: " << response << endl
         << "\n";
}

void track_fitness(int level, int &totals)
{
    int reps, reps2, reps3;
    if (level == 1)
    {
        cout << "Enter reps: ";
        cin >> reps;
        totals += reps;
    }
    else if (level == 2)
    {
        cout << "Enter reps per 2 sets: ";
        cin >> reps >> reps2;
        totals += reps + reps2;
    }
    else if (level == 3)
    {
        cout << "Enter reps per 3 sets: ";
        cin >> reps >> reps2 >> reps3;
        totals += reps + reps2 + reps3;
    }

    int bronze_threshold = 75;
    int silver_threshold = 99;
    cout << "Your total number of reps are " << totals << endl;
    if (totals <= bronze_threshold)
    {
        cout << "You are in bronze league.\n"
             << "Keep pushing yourself to be in Silver League.\n";
    }
    else if (totals > bronze_threshold && totals <= silver_threshold)
    {
        cout << "Congratulations! You are promoted to silver league\n"
             << "Keep pushing yourself to be in Gold League.\n";
    }
    else
    {
        cout << "Congratulations! You are promoted to the highest league, gold league\n"
             << "Keep working hard.\n";
    }
}

void bubble_sort(details arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].total_reps < arr[j + 1].total_reps)
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void save_leaderboard_to_file()
{
    bubble_sort(users, userCount);
    ofstream leaderboardFile("leaderboard.txt", ios::app);
    if (leaderboardFile.is_open())
    {
        leaderboardFile << "Si.No\tUsername\tTotal Reps\tLeague\n";
        for (int i = 0; i < userCount; i++)
        {
            string league;
            if (users[i].total_reps <= 75)
            {
                league = "Bronze";
            }
            else if (users[i].total_reps > 75 && users[i].total_reps <= 99)
            {
                league = "Silver";
            }
            else
            {
                league = "Gold";
            }
            leaderboardFile << (i + 1) << "\t" << users[i].userID << "\t\t  " << users[i].total_reps << "\t\t" << league << "\n";
        }
        leaderboardFile.close();
        cout << "Your Rank has been saved to leaderboard.txt.\n";
    }
    else
    {
        cout << "Unable to open the leaderboard file.\n";
    }
}

void Selecting_badging_adding(details &current_user)
{
    int totals = 0, choice;
    string name, Description, add_new_exercise, new_exercise, new_exercise_desc, continue_program;

    while (true)
    {
        // Warm-up recommendation
        cout << "* BEFORE STARTING YOUR EXERCISE YOUR VIRTUAL COACH RECOMMENDS YOU TO " << warm_up << endl;

        cout << "Menu" << endl
             << "Type 1 for Pushup" << endl
             << "Type 2 for Pullup" << endl
             << "Type 3 for Plank" << endl;

        cout << "Would you like to add a new exercise? Type Y for yes and N for no (Y/N): ";
        cin >> add_new_exercise;
        cin.ignore(); // To ignore the newline character left in the input buffer

        if (add_new_exercise == "Y" || add_new_exercise == "y")
        {
            cout << "Name of Exercise: ";
            getline(cin, new_exercise);
            cout << "Description of Exercise: ";
            getline(cin, new_exercise_desc);

            cout << "\t\t\t\t\tYou have added a new Exercise\n";
            cout << "Name: " << new_exercise << endl
                 << "Description: " << new_exercise_desc << endl;

            display_levels();
            exercise_summary(new_exercise, new_exercise_desc, difficulty, response);
        }
        else
        {
            cout << "Enter your choice from above menu: ";
            cin >> choice;
            cin.ignore(); // To ignore the newline character

            switch (choice)
            {
            case 1:
                name = "Pushups";
                Description = "A bodyweight exercise targeting the upper body by lowering and raising the body using arm strength.";
                break;
            case 2:
                name = "Pullups";
                Description = "An upper-body exercise where you lift your body to a bar, engaging the back, arms, and shoulders.";
                break;
            case 3:
                name = "Planks";
                Description = "A core-strengthening exercise involving holding a straight body position supported by the forearms and toes.";
                break;
            default:
                cout << "Invalid Choice, Select from the given options.\n";
                continue;
            }

            cout << "\t\t\t\t\tSummary\n";
            cout << "Name: " << name << endl;
            cout << "Description: " << Description << endl;
            display_levels();
            exercise_summary(name, Description, difficulty, response);
        }

        track_fitness(level, totals);

        cout << "Do you want to continue your workout? Type Y for yes or N for no: ";
        cin >> continue_program;
        if (continue_program == "N" || continue_program == "n")
        {
            // Cool-down recommendation
            cout << "\n\n * NOW YOU HAVE DONE YOUR EXERCISE SESSION, DON'T FORGET TO " << cool_down;
            "\n\n * HAPPY DAY AND DON'T FORGET GOOD RESULTS ARE WORTH THE STRUGGLE \n";
            Sleep(2000); // taking break of 2 seconds
            system("cls");
            break;
        }
        system("cls");
    }

    // Add user total reps to the leaderboard
    current_user.total_reps = totals;
    users[userCount++] = current_user;
    // Calling the function to save leaderboard data to file
    save_leaderboard_to_file();
}

int main()
{
    string next_User;
    details logging;
    for (int i; i <= 100; i++)
    {
        Welcome(logging);
        system("cls");
        Selecting_badging_adding(logging);
        cout << "Any other User? ";
        cin >> next_User;
        if (next_User == "N" || next_User == "n")
        {
            break;
        }
    }
    return 0;
}
