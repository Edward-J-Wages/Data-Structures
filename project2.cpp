#include <iostream>
#include <string>
using namespace std;

class Chip 
{
    private:
        char chipType; // Type of the chip (A: Addition, S: Subtraction, etc.)
        string id; // Unique identifier for the chip (Ex. A100)
        Chip* input1; // Pointer to the first input chip
        Chip* input2; // Pointer to the second input chip (can be NULL)
        Chip* output; // Ptr to the output chip (is NULL for output chips)
        double inputValue; //for the input chip
    public:
        // Constructor
        Chip(char type, const string& id) : chipType(type), id(id) {}

        //Destructor
        ~Chip()
        {
            if(input1 != nullptr)
            {
                delete input1;
            }

            if(input2 != nullptr)
            {
                delete input2;
            }

            if(output != nullptr)
            {
                delete output;
            }
        }

    // Method prototypes
    void setInput1(Chip* inputChip) // Sets the first input chip
    {
        input1 = inputChip;
    }

    void setInput2(Chip* inputChip) // second input chip (can be NULL)
    {
        if(inputChip == nullptr)
        {
            return;
        }
        else
        {
            input2 = inputChip;
        }
    }

    void setOutput(Chip* outputChip) // Sets the output chip (can be NULL)
    {
        if(outputChip == nullptr)
        {
            return;
        }
        else
        {
            output = outputChip;
        }
    }

    Chip* getInput1() //Returns the first input chip
    {
        return input1;
    }

    Chip* getInput2() //Returns the second input (can be NULL)
    {
        return input2;
    }

    void setInputValue(int nput) //Sets the input value (for I chips)
    {
        inputValue = nput;
    }

    float compute() // Performs the operations based on the chip type SOME PROBLEM EXISTS
    {
        //If we make all operations call recursively, we can rout through the entire circuit & actually return the output of the
        //circuit upon arriving to the Output chip which is our base case (the 'O' case)
        switch (chipType)
        {
        case 'A': //Addition chip
            if (input1 != nullptr && input2 != nullptr) //Each statement first checks that the inputs actually exist before computing
                {
                    return input1->compute() + input2->compute(); // A + B
                }
            exit(1);
            break;

        case 'S': //Subtraction chip
            if (input1 != nullptr && input2 != nullptr) 
                {
                    return input1->compute() - input2->compute(); // A - B
                }
            exit(1);
            break;

        case 'M': //Multiplication chip
            if (input1 != nullptr && input2 != nullptr) 
                {
                    return input1->compute() * input2->compute(); //A * B
                }
            exit(1);
            break;
        case 'N': //Negation chip
            if (input1 != nullptr) 
                {
                    return -input1->compute(); // A * (-1) or simply -A
                }
            exit(1);
            break;
        case 'D': //Division chip, needs to handle a divide by zero error
            if (input1 != nullptr && input2 != nullptr) 
                {
                        return input1->compute() / input2->compute(); // A / B
                }
            exit(1);
            break;
        
        case 'I': //Input chip
            return inputValue; //Just A in this case
            break;

        case 'O': //Output chip -> This is our base case for the compute method, for which the rest of the method computes from
            cout << "The output value from this circuit is " << input1->compute() << endl;
            return 0;
            break;

        default:
            exit(1);
            break;
        }
        exit(1);
    }

    void display() const // Displays the chip's information
    {
        switch (chipType)
        {
            case 'A': //Addition display     //example: A100, Input 1 = I1, Input 2 = I2, Output = M300
            cout << id << ", Input 1 = " << input1->id << ", Input 2 = " << input2->id << ", Output = " << output->id << endl;
                break;

            case 'S': //Subtraction chip
            cout << id << ", Input 1 = " << input1->id << ", Input 2 = " << input2->id << ", Output = " << output->id << endl;
                break;

            case 'M': //Multiplication chip
            cout << id << ", Input 1 = " << input1->id << ", Input 2 = " << input2->id << ", Output = " << output->id << endl;
                break;
                
            case 'N': //Negation chip
            cout << id << ", Input 1 = " << input1->id << ", Input 2 = None" << ", Output = " << output->id << endl;
                break;

            case 'D': //Division display
            cout << id << ", Input 1 = " << input1->id << ", Input 2 = " << input2->id << ", Output = " << output->id << endl;
                break;
            
            case 'I': //Input display      //example: I6, Output = S600 --- for the input Chip
            cout << id << ", Output = " << output->id << endl;
                break;

            case 'O': //Output display    False call of the output chip to ensure it's always outputted at the end of the list
                break;
                
            default:
                break;
        }
        
    }

    void displayOutputChip() const //display of the O chip has it's own function to ensure it's called always at the end
    {
        cout << id << ", " << "Input 1 = " << input1->id << endl;
    }
    
    string getId() const // Returns the chip ID
    {
        return id;
    }

    char getChipType() const //Returns the first Char of the ID to signify the chip's operation
    {
        return chipType;
    }
};


int main () 
{
    //**** ALL THE VARIABLES YOU NEED FOR THIS MAIN FUNCTION *****//
    int numChips;
    Chip** allChips;
    int numCommands;
    cin >> numChips;

    //create an array Chip objects pointers
    allChips = new Chip*[numChips];
    //each array location is a pointer to a Chip Object

    //This for loop is to create the allChips array
    for (int i=0; i < numChips; i++) 
    {
        //read the chip ID based on the first letter to determine its type
        string temp_id;
        cin >> temp_id;
        char type = temp_id.at(0); //First char of the id, being the chip's type
        string id = temp_id.substr(0); //The reminder of the temp id, being it's numbers
        
        //create the chip object and initialize it appropriately
        Chip* newChip = new Chip(type, id);
        
        //store the chip object in the allChips array
        allChips[i] = newChip;
    }

    cin >> numCommands;

    for (int i=0; i < numCommands; i++) 
    {
        char firstLetter;
        string firstChip;
        string secondChip;
        // read from input the links and make the appropriate connections. You may need to search the array allChips
        //to find the chip that is referred and connect.
        cin >> firstLetter >> firstChip >> secondChip; //Reads the line from input. Need to find the chip in array that matches each
        
        // If the first letter is an O, then execute the compute method on the object referred.
        if(firstLetter == 'O') //'O' case
        {
            for(int i = 0; i < numChips; i++) //Loop through allChips to find the O chip
            {
                if (allChips[i]->getId() == firstChip)
                {
                    cout << "Computation Starts" << endl;
                    allChips[i]->compute(); //Call compute on output chip once found
                }
            }
        }

        //if the letter is I, then we need to store the value of the input chip
        else if (firstLetter == 'I') //'I' case
        {
            for(int i = 0; i < numChips; i++) //Loop through allChips to find the I chip
            {
                if (allChips[i]->getId() == firstChip)
                {
                    allChips[i]->setInputValue(stoi(secondChip)); //Assigns the value in "secondChip" (the value of inputValue in this
                                                                  //case) to the associated input chip 
                }
            }
        }
        //The only other case is A, so we are fine to simply make an else statement for the remainder
        else //'A' Case
        {
            for(int i = 0; i < numChips; i++) //Loop through allChips to find the associated chip
            {
                if (allChips[i]->getId() == secondChip) //Checks to see if the Id of the chip is equal to the one in the array
                {
                    //Find the firstChip in the array & set the input to that one. Need a second if to determine which input to set
                    for(int k = 0; k < numChips; k++)
                    {
                        if (allChips[k]->getId() == firstChip)
                        {
                            if(allChips[i]->getInput1() == nullptr) //Checks to see if first input is empty so we don't re-initialize
                            {
                                allChips[i]->setInput1(allChips[k]);
                            }
                            else //If the first input has already been set we need to set the second
                            {
                                allChips[i]->setInput2(allChips[k]);
                            }
                            allChips[k]->setOutput(allChips[i]); //sets the output of the first chip to the second chip

                        }
                    }
                }
            }
        }
    }

    cout << "***** Showing the connections that were established" << endl;
    
    //for each component created call the display () method
    for(int i = 0; i < numChips; i++) //For loop to call display on every chip, which also skips the O chip to be called later
    {
        allChips[i]->display();
    }

    for(int i = 0; i < numChips; i++) //A second for loop is made at the end specifically for displayOutputChip.
                                      //This is so it can always be guaranteed to be called last to satisfy the third test case
    {
        if(allChips[i]->getChipType() == 'O')
        {
            allChips[i]->displayOutputChip();
        }
    }
    cout << endl; //Extra newline for the purpose of matching up with output tests

    return 0;
}

/*
    *****DOCUMENTATION*****

    AI USAGE:
    I did not use AI throughout the development of Project 2.

    DEBUGGING & TESTING PLAN:
    The first issue I ran into was figuring out how to determine between the different chip types from input.
        For my solution to this problem, I realized we can simply take a substring of the input to determine the chip type with the
        first char of the id.

    My next largest issue, I struggled with how to correctly implement the compute() method. Specifically, the initially given
    return type made it so that we could not easily call the next chip recursively and so on
        For my solution, I tried changing the return type of compute to a float, and that seemed not produce errors in the editor

    Upon finishing all of the methods and attempting to run the input tests for the first time, I found that it ran without producing
    any output; which I am currently unsure how that is happening.
        Since this issue is much larger than the others; I will list my steps testing it as I go
            1. Wrote a temporary print statement just after numChips is read to ensure that we are getting the file
                This worked & gave us the expected value, so the issue must lie further in
                1a. Did the same thing after numCommands assignment with success, issues lies further in
            2. Found the issue! using the sizeOf() function for the allChips array caused a series of issues, as well as a stray id
            pointer in the display() method which also caused massive output errors. sizeOf() has been replaced by numChips in all spots
            throughout the code, and the id pointer has been removed. 
    
    Testing all 3 given input files reveals that for some reason the end result is inconsistent. I can run it with the same input file
    multiple times and end with either a matching result OR the code executes before it prints the output value. Need to investigate
        1. Problem lies somewhere in the compute method, as when the program fails it stops at "The output value from this circuit is "
           And terminates after a while
        2. I believe the issue was due to not having exit statement in my compute() method. Will add them and run through autograder

    I also encountered a bug where the output was needing to be the last chip outputted regardless of it's order in the input, which I
    simply fixed by making the O chip it's own display function to ensure it is printed at the end


*/