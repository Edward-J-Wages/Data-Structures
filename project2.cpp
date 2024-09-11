#include <iostream>
using namespace std;

class Chip 
{
    private:
        char chipType; // Type of the chip (A: Addition, S: Subtraction, etc.)
        string id; // Unique identifier for the chip
        Chip* input1; // Pointer to the first input chip
        Chip* input2; // Pointer to the second input chip (can be NULL)
        Chip* output; // Ptr to the output chip (is NULL for output chips)
        double inputValue; //for the input chip
    public:
        // Constructor
        Chip(char type, const string& id) : chipType(type), id(id) {}

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

    void compute() // Performs the operation based on the chip type
    {
        switch (chipType)
        {
        case 'A': //Addition chip
            
            break;
        case 'S': //Subtraction chip
            /* code */
        case 'M': //Multiplication chip
            /* code */
        case 'N': //Negation chip
            /* code */
        case 'D': //Division chip? Ask for clarification, was not specified
        
        default:
            break;
        }
    }

    void display() const // Displays the chip's information
    {
        cout << chipType << ", ";  //Start the output, needs finishing based on what type of chip it is
        if ()
    }

    //example: I6, Output = S600 --- for the input Chip
    //example: O50, Input 1 = S600 --- for the output Chip
    //example: A100, Input 1 = I1, Input 2 = I2, Output = M300
    
    string getId() const // Returns the chip ID
    {
        return id;
    }
    //****** OTHER METHODS AS NECESSARY ************//

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
    for (int i=0; i < numChips; i++) 
    {
        //read the chip ID based on the first letter to determine its type
        
        //create the chip object and initialize it appropriately
        
        //store the chip object in the allChips array
        allChips[i] = 
    }

    for (int i=0; i < numCommands; i++) 
    {
        // read from input the links and make the appropriate
        //connections. You may need to search the array allChips
        //to find the chip that is referred and connect.
        // If the first letter is an O, then execute the compute method
        // on the object referred.
    }

    cout << "***** Showing the connections that were established" << endl;
    //for each component created call the display () method
    return 0;
}

/*
    *****DOCUMENTATION*****

*/
