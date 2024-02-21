/***************************************
Memory Game
Author: Dominik Pantaleoni
Date Completed: 2/18/2024
Description: A program that lets the user play a solo game of Memory
***************************************/

#include <iostream>
#include <string>
#include <array>
#include <cstdlib>
#include "RandomInt.hpp"
using namespace std;

//custom data type Card
struct Card {
    string Phrase="";
    bool Matched=false;
};

//non member function that takes both members of the Card struct
Card buildCard(string phrase, bool matched) {
    Card a;
    a.Phrase = phrase;
    a.Matched = matched;
    return a;
};

//non-member function that randomly shuffles the pointer locations
void buildRandomCardPointerArray(array<Card, 4> &arrayParam, array<Card*, 8> &ptrsParam) {
    Random::RandomInt randomIntGenerator(0, 3, 2);

    int randomInteger1 = randomIntGenerator.get();
    int randomInteger2 = randomIntGenerator.get();
    int randomInteger3 = randomIntGenerator.get();
    int randomInteger4 = randomIntGenerator.get();
    int randomInteger5 = randomIntGenerator.get();
    int randomInteger6 = randomIntGenerator.get();
    int randomInteger7 = randomIntGenerator.get();
    int randomInteger8 = randomIntGenerator.get();

    ptrsParam.at(0) = &arrayParam.at(randomInteger1);
    ptrsParam.at(1) = &arrayParam.at(randomInteger2);
    ptrsParam.at(2) = &arrayParam.at(randomInteger3);
    ptrsParam.at(3) = &arrayParam.at(randomInteger4);
    ptrsParam.at(4) = &arrayParam.at(randomInteger5);
    ptrsParam.at(5) = &arrayParam.at(randomInteger6);
    ptrsParam.at(6) = &arrayParam.at(randomInteger7);
    ptrsParam.at(7) = &arrayParam.at(randomInteger8);

};

//non-member function that returns true if all cards are matched
bool allCardsMatched(array<Card, 4> &arrayParam) {
    for (int i=0; i<4; i++) {
        if (!arrayParam.at(i).Matched) {
            return false;
        } else if (i == 3) {
            return true;
        };
    };
    return false;
};

//non-member function that shows player the game board (the state of every card is put into CLI)
void displayGameBoard(array<Card*, 8> &ptrsParam) {

    //loop through pointers and display to CLI if each is matched or not
    for (int i=0; i<8; i++) {
        if (ptrsParam.at(i)->Matched==true) {
            cout<<"Card "<<i+1<<": "<<ptrsParam.at(i)->Phrase<<endl;
        } else {
            cout<<"Card "<<i+1<<": ?"<<endl;
        };
    };
};

int main()
{
   //create array of the four Card objects
   array<Card, 4> cardArray;

   cardArray.at(0) = buildCard("Flying Monkey", false);
   cardArray.at(1) = buildCard("Mad Cow", false);
   cardArray.at(2) = buildCard("Magic Genie", false);
   cardArray.at(3) = buildCard("Great Pumpkin", false);

   //create array of 8 pointers (2 for each Card)
   array <Card*, 8> ptrArray;

   buildRandomCardPointerArray(cardArray, ptrArray);

   cout<<"Welcome to Memory Game!\n\n";

   //initiate 2 integers that user will assign through input each round
   int selectionOne = 0;
   int selectionTwo = 0;
   //initiate an integer that keeps count of total number of guesses so far
   int totalGuesses = 0;

   //display gameboard each round, updating to show current state
   while (!allCardsMatched(cardArray)) {

        cout<<"Total Guesses: "<<totalGuesses<<endl<<endl;
        totalGuesses += 1;
        displayGameBoard(ptrArray);
        cout<<"\nSelect two different cards between 1 and 8:\n";
        cin>>selectionOne>>selectionTwo;

        //set Card* selected to be Matched if Matched correctly
        if (ptrArray.at(selectionOne-1)->Phrase == ptrArray.at(selectionTwo-1)->Phrase) {
            ptrArray.at(selectionOne-1)->Matched=true;
            cout<<"You found a matching pair!\n";
            cout<<"Both cards say \""<<ptrArray.at(selectionOne-1)->Phrase<<"\""<<endl; 
        } else {
            cout<<"The cards don't match\n";
            cout<<"First card says \""<<ptrArray.at(selectionOne-1)->Phrase<<"\""<<endl;
            cout<<"Second card says \""<<ptrArray.at(selectionTwo-1)->Phrase<<"\""<<endl;
        };
        cout<<"PRESS ENTER KEY TO CONTINUE...\n";
        cin.ignore();
        while (cin.get() != '\n');
        system("cls||clear");
   };

    cout<<"Total Guesses: "<<totalGuesses<<endl<<endl;
    displayGameBoard(ptrArray);
    cout<<"\nYou matched all of the cards! Game over.\n";

   

   return 0;
}
