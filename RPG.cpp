/****************************************************************
*****************************************************************
*****************************************************************
*** .--.                          .   .                       ***
*** |   )  o        o             |   |                       ***
*** |--'   .  .--.  .  .--. .-..  |---| .-. .--..-.  .-. .--. ***
*** |  \   |  `--.  |  |  |(   |  |   |(.-' |  (   )(.-' `--. ***
*** '   `-' `-`--'-' `-'  `-`-`|  '   ' `--''   `-'  `--'`--' ***
***                         ._.'                              ***
*****************************************************************
*****************************************************************
****************************************************************/

//Continue of: job description in character creation.

//Libraries
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <map>
#include "tools.h"
#include "character.h"

//Namespaces
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::stringstream;
using std::flush;


//Functions
void initialize()
{
    g_jobs.insert(std::make_pair("Knight", Attributes(
		5, 2,//STR
		10, 3,//DEF
		1, 1,//MAG
		5, 1,//AGI
		"A resistent tank, focused on survivability and blocking attacks to unleash powerful shield slams.",
		"Block: Chance to block a basic attack or a spell, based on its DEF stat.",
		"Endure: Raises DEF stat every turn, stacking up to 4 times. If it was already applied 4 times, the stacks reset in your next turn.")));
		
    g_jobs.insert(std::make_pair("Warrior", Attributes(
		8, 3,//STR
		6, 2,//DEF
		2, 1,//MAG
		6, 1,//AGI
		"An unstoppable fighter, with balanced fight skills. Long fights can make a Warrior show his true rage.",
		"Berserk: Raises ATK stat the lower his own health is",
		"Bleed: Attacks apply bleeding to the enemy, which lasts 2 turns and stacks up to 4 times. Attacking over bleeding renew the timer"
		)));
		
    g_jobs.insert(std::make_pair("Rogue", Attributes(
		5, 2,//STR
		3, 1,//DEF
		12, 3,//MAG
		1, 1,//AGI
		"Likes to walk in the shadows. He abuse of the enemy's weakness to turn fights onto his favor.",
		"Exploit: Raises ATK stat the lower the enemy's health.",
		"Double: Not Decided"
		)));
		
    g_jobs.insert(std::make_pair("Ranger", Attributes(
		5, 2,//STR
		3, 1,//DEF
		12, 3,//MAG
		1, 1,//AGI
		"Precise like a hawk. Great damage dealer while far from the enemy, keeping distance and calculating your steps are the key to be a successful Ranger.",
		"Pierce: Casting a spell reduces the enemy's DEF in the next turn.",
		"Deadly Shot: Basic attacks are more effective the greater the distance between you and your enemy."
		)));
		
    g_jobs.insert(std::make_pair("Sorcerer", Attributes(
		2, 1,//STR
		3, 1,//DEF
		12, 4,//MAG
		1, 2,//AGI
		"A deadly mage that horrifies its enemies with black magic. Purely based on inteligence, a mage can set up a colossal combo to obliterate a target.",
		"Mastermind: After casting a certain spell twice, the next cast time you cast it, it will have a bonus effect.",
		"Profanity: Aggressive spells can instant kill targets below 30% health"
		)));
		
    g_jobs.insert(std::make_pair("Spiritguard", Attributes(
		5, 2,//STR
		3, 1,//DEF
		12, 3,//MAG
		1, 1,//AGI
		"A servant of the nature. Sustained fights can go on his favor. Heals himself and deals several damage.",
		"Regeneration: Regenerates HP every turn",
		"Adaptability: Changing stances empowers the next basic attack" 	
		)));
		
    g_jobs.insert(std::make_pair("Blackbelt", Attributes(
		5, 2,//STR
		3, 1,//DEF
		12, 3,//MAG
		1, 1,//AGI
		"Calm like a breeze, his reflexes can be compared to a tiger's. Focused on evading and countering enemies' attacks.",
		"Untouchable: Chance of evading an attack and raising AGI stat.",
		"Dragon Rage: Taking damage can release a powerful attack.")));  
}

//Initialization
int main()
{
	// -- Variables --
	//General or that will be used more than once
		Character ch = Character();
		bool gameLoop;
		std::stringstream sstm;
		string msg;
		int a=0, b=0, c=0;
		
	//Related to the New Game/Load Menu
		int mainMenuOption;
		
	//Related to Character Creation
		int jobOption, confirmJobOption;
		string newchar_name, newchar_job;
		string job_desc, passive1_desc, passive2_desc;
		JobList::iterator it_joblist;
	
	//Related to Character Load
		string loadchar_name;
		bool foundSave = false;
			
	//Start
	initialize();
	
	do{//GameLoop
		if(ch.get_name() == "")
		do{
			cout << "Please choose an option.\n1. New Game\n2. Load Game\n\nOption: " << flush;
			cin >> mainMenuOption;
			
			switch(mainMenuOption){
				case 1://New Game
					clearScreen();
					cout << "- Hey kid, it's a good day here in Naive City, isn't it? What is your name?" << endl;
					do{
						cin >> newchar_name;
						if(newchar_name.length() < 3){
							cout << "- This name is too short. Please pick a bigger one." << endl;
							newchar_name.clear();
						}
						if(newchar_name.length() > 15){
							cout << "- This name is too long. Please pick a shorter one." << endl;
							newchar_name.clear();
						}
					}while(newchar_name == "");
					cout << "- It's a pleasure to meet you, " << newchar_name << "." << endl;
					do{
						cout << "- Every kid has a dream, you know. What do you aspire to be in your future?\n1. Knight\n2. Warrior\n3. Rogue\n4. Ranger\n5. Sorcerer\n6. Spiritguard\n7. Blackbelt\n\nOption: " << flush;
						cin >> jobOption;
						if (jobOption >= 1 and jobOption <= 7){	
							a = 0;
							for (it_joblist = g_jobs.begin(); it_joblist != g_jobs.end(); ++it_joblist){
								cout << it_joblist->first;
								if (jobOption == a){
									newchar_job = it_joblist->first;
									sstm.clear();
									sstm << "-----------\nChosen job: " << newchar_job << "\n\n" << it_joblist->second.general_desc << "\n\nPassive 1: " << it_joblist->second.passive1_desc << "\nPassive 2: " << it_joblist->second.passive2_desc <<
									 "\n\nStats\nSTR:" << it_joblist->second.base_STR << " (+" << it_joblist->second.scaling_STR << " per level)" << "\nDEF:" << it_joblist->second.base_DEF << " (+" <<
									  it_joblist->second.scaling_DEF << " per level)" << "\nMAG:" << it_joblist->second.base_MAG << " (+" << it_joblist->second.scaling_MAG << " per level)" <<
									  "\nAGI:" << it_joblist->second.base_AGI << " (+" << it_joblist->second.scaling_AGI << " per level)" << "\n\nAre you sure you want to be a " << newchar_job << "?\n\n1.Yes\n2.No\n\nOption: " << flush;
									break;
								}	
								a++;
							}
							msg = sstm.str();
						 	cout << msg;
							cin >> confirmJobOption;
							if(confirmJobOption != 1){
								newchar_job.clear();
								clearScreen();
							}
						} 
						else
							cout << "- This is not a valid choice, child." << endl;

					}while(newchar_job == "" && confirmJobOption != 1);
					ch = create_new_character(newchar_name, newchar_job);
					sstm << ch.get_name() << "\n" << ch.get_job() << "\n" << ch.get_level() << "\n" << ch.get_exp() << "\n" << ch.get_money() << "\n" << ch.get_str() << "\n" << ch.get_def() << "\n" << ch.get_mag() << "\n" << ch.get_agi() << "\n";
					msg = sstm.str();
					cout << msg;
					break;
					
				case 2://Load Game				
					clearScreen();
					cout << "What is the name of your saved character?" << endl;
					cin >> newchar_name;
					break;
					
				default:
					cout << "Invalid option." << endl;
			}
			
			clearScreen();
			if(mainMenuOption == 2 && foundSave == false){
				cout << "There is no save file with such name. Please input a valid character name." << endl;
			}
		}while((mainMenuOption != 2 && foundSave == true) && mainMenuOption != 1);
		
		cout << "Fate established.";
		cin >> b;
	}while(gameLoop);
}
