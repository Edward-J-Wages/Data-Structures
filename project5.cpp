#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

int main () 
{
    ifstream reader;
    //read the name of the file ./a.out < filename.txt
    string filename;
    cin >> filename;
    //Open the file
    reader.open(filename);


    map<string, int> words;
    string token;
    //get each token and store them in the unordered_map (or map) increment
    //its frequencies. You MAY be able to do myTokens[aToken]++. Work on this.
    while(!reader.eof())
    {
        //Read the next word & add it to words. Increment key value if this is a repeat word
    }

    //close the file (filename.txt)
    reader.close();

    //sort the myTokens in the decreasing order of VALUE which is frequencies
        //Can you sort a map or is this referring to a vector?
    //print the KEYS in myTokens (which has been sorted)separated by a space.
        //Output we're looking for

    //after you printed the KEYS Do this
    cout << endl;
    cout << "********" << endl;

    //Now open the filename.text file again for reading
    reader.open(filename);
    //Read token by token as you have done this before
    while(!reader.eof())
    {
    //each time you get a token, find its position in the myTokens (sorted data structure) and print the position followed by space

    }
    
    cout << endl;
}

/*
BONUS: For 30% extra credit, write another program, name your program as Project-5-
decompress.cpp that takes the output of the above program and produces text.
Constraints
1. You are allowed to use only the libraries given above.
2. You need to work individually in this project.
3. Any use of internet’s resources need to be cited in your code.
Project Submission Requirements:
1. Code Development (75%): Implement the provided classes and the required methods
Your implementation must be fully compatible with the main program provided. Your code
*/