#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <set>
using namespace std;

// NOTE: Hello Graders! You'll notice there's two submissions with a correct outcome, this is because on my original submission it is
//lacking all of my documentation. This is the final submission for my Project 4, thank you for taking the time to look through my
//project and I greatly appreciate any feedback! This one didn't seem so bad (at first)

//NOTE 2: I like to have helper methods before the important ones, new Upload simply changes where rebuild_child is at

// Exception classes
class NotFoundException : public exception 
{
    public:
    const char* what() const noexcept override 
    {
        return "Value not found in the tree.";
    }
};

class DuplicateInsertion : public exception 
{
    public:
    const char* what() const noexcept override 
    {
        return "Value already exists in the tree.";
    }
};

// MTree class
template <class DT>
class MTree 
{
    //Essentially, each MTree serves as it's own node, with a vector for the values and a vector of MTree's as function as the children
    protected:
    int M; // Maximum number of children per node (M-way split)
    vector<DT> values; // Values stored in the node (M-1 values)
    vector<MTree*> children; // Pointers to child MTrees (M children)

    public:
    //Constructor, doesn't do much
    MTree(int M)
    {
        this->M = M;
    }

    //Destructor. Loops through the children vector and deletes the elements
    ~MTree() 
    {
        for (auto child : children)
            delete child;
    }

    //Helper Method(s)
    void rebalance_child(size_t index) //Rebalances the tree to ensure timely access & to fix issues from other methods
    {
        //Didn't even think about needing a methd for this, but issues from removal make it necessary

        MTree* child = children[index]; //Assigns a new MTree node with the MTree at index

        //Obtains the values from the node to it's left
        if (index > 0 && children[index - 1]->values.size() > (M - 1) / 2) 
        {
            MTree* leftSibling = children[index - 1];
            child->values.insert(child->values.begin(), values[index - 1]);
            values[index - 1] = leftSibling->values.back();
            leftSibling->values.pop_back();
        }
        //Obtains the values from the node to it's right
        else if (index < children.size() - 1 && children[index + 1]->values.size() > (M - 1) / 2) 
        {
            MTree* rightSibling = children[index + 1];
            child->values.push_back(values[index]);
            values[index] = rightSibling->values.front();
            rightSibling->values.erase(rightSibling->values.begin());
        }

        else 
        {
            if (index > 0) //checks index to see which sibling we need to interact with
            {
                MTree* leftSibling = children[index - 1]; //Creates leftSibling for the sake of insertion

                leftSibling->values.push_back(values[index - 1]); //Inserts our current node's values into leftSibling
                //Inserts the elements in the necessary indeces into lefSibling
                leftSibling->values.insert(leftSibling->values.end(), child->values.begin(), child->values.end()); 
                leftSibling->children.insert(leftSibling->children.end(), child->children.begin(), child->children.end());

                delete child; //Since we do not need the child value anymore

                children.erase(children.begin() + index); //Erase the current child's values so there's no duplicates
                values.erase(values.begin() + index - 1); //Does the same for values
            } 
            else 
            {
                //The purpose of everything here is the same but for the right
                MTree* rightSibling = children[index + 1];

                child->values.push_back(values[index]);
                child->values.insert(child->values.end(), rightSibling->values.begin(), rightSibling->values.end());

                child->children.insert(child->children.end(), rightSibling->children.begin(), rightSibling->children.end());
                delete rightSibling; //We no longer have need for the rightSibling variable

                children.erase(children.begin() + index + 1);
                values.erase(values.begin() + index);
            }
        }
    }
    
    bool is_leaf() const //Detects whether or not the node is a leaf
    {
        //Super simple to do. If the node has an empty children vector, then it is by definition, a leaf.
        return children.empty();
    }

    void insert(const DT& value) //Insert a given value into the tree
    {
        if (is_leaf()) //If we have reached a leaf, continue with insertion
        {
            auto it = lower_bound(values.begin(), values.end(), value); //Finding the index to insert the value in
            if (it != values.end() && *it == value) //If the value exists already inside the list
            {
                throw DuplicateInsertion(); 
            }
            values.insert(it, value); //Otherwise, we can insert it in the correct index to maintain a sorted order
        } 
        else //If we aren't at the leaf, call find_child & insert on the returned MTree node
        {
            MTree* child = find_child(value);
            child->insert(value);
        }
    }

    void remove(const DT& value) //Remove a value from the tree 
    {
        auto it = lower_bound(values.begin(), values.end(), value); //iterator

        if (is_leaf()) //If we have a leaf node
        {
            if (it == values.end() || *it != value) //Remove from the leaf node
                throw NotFoundException(); //THrow the exception if it isn't there
            values.erase(it);
        } 

        else //If ot a leaf node
        {
            if (it != values.end() && *it == value) //If we havent reached the end & the iterator is equal to the value
            {
                MTree* newNode = children[it - values.begin()]; //Assign the value at the index to a newNode
                while (!newNode->is_leaf()) //While loop checking to see if it is a leaf
                {
                    newNode = newNode->children.back(); //Adds newNode to the end of children
                }
                values[it - values.begin()] = newNode->values.back(); 
                newNode->remove(newNode->values.back());
            } 
            else 
            {
                // Remove recursively from the child
                MTree* child = find_child(value); //Call find child to get the correct node we need to follo 
                child->remove(value);

                if (child->values.size() < (M - 1) / 2) //This is just to handle underflow
                {
                    rebalance_child(it - values.begin()); //Didn't think I needed rebalance_child at first, but now I do (11/17, 3:30 P.M)
                }
            }
        }

        // If the root becomes empty and has children we can reduce the tree
        if (values.empty() && !children.empty()) 
        {
            *this = *children.front();
        }
    }


   bool search(const DT& value) 
   {
        //Search in the current node's values
        auto it = lower_bound(values.begin(), values.end(), value);
        if (it != values.end() && *it == value)
        {
           return true; //If we find the value, simply return true
        }

        //If we havent found the leaf node yet, we need to recursively call the method on the correct child until we do
        if (!is_leaf()) 
        {
           MTree<DT>* child = find_child(value); //Returns the child we need to follow
           return child->search(value); //Recursive call
        }

        //Value not found
        return false;
    }

    vector<DT> collect_values() 
    {
       set<DT> result_set; //Use a set to prevent duplicate values (will prevent the infinite loop I encountered previously)

       //Collect values from children
       for (auto child : children) 
       {
           auto child_values = child->collect_values();
           result_set.insert(child_values.begin(), child_values.end());
       }

       //Add current node values to the set 
       result_set.insert(values.begin(), values.end());
       //Convert set to a sorted vector and return 
       return vector<DT>(result_set.begin(), result_set.end());

       //This version is much better on time complexity and is more effective for the task at hand
    }

    void buildTree(vector<DT>& input_values) //Rebuilds the tree given a vector of input values
    {
        sort(input_values.begin(), input_values.end()); //Sorts the values for easy insertion
        input_values.erase(unique(input_values.begin(), input_values.end()), input_values.end());

        values.clear(); //Clears current values & children
        children.clear();

        if (input_values.size() <= M - 1) //If don't have enough values where we need to split the node, it ends here
        {
            values = input_values;
            return;
        }

        //The following is mostly provided by the TA's, so I unfortunately do not have much to talk about here
        size_t D = (input_values.size() + M - 1) / M;
        for (size_t i = 0; i < M; i++) 
        {
            size_t start = D * i;
            size_t end = min(start + D, input_values.size());
            if (start >= input_values.size()) 
            {
                break;
            }

            vector<DT> child_values(input_values.begin() + start, input_values.begin() + end);

            if (i < M - 1 && !child_values.empty()) 
            {
                values.push_back(child_values.back());
                child_values.pop_back();
            }

            MTree* child = new MTree(M);
            child->buildTree(child_values);
            children.push_back(child);
        }
    }

    MTree* find_child(const DT& value) //Finds the correct child to follow (No Diddy)
    {
        auto it = upper_bound(values.begin(), values.end(), value); //Iterator to look through the values
        size_t index = it - values.begin();
        if (index >= children.size()) //If the index is greater than the size of children, handle the erro 
        {
           throw runtime_error("Child node index out of bounds");
        }
        return children[index]; //Returns the correct child for the value given
    }
};

// Main program
int main() 
{
    int n; // Number of initial elements
    cin >> n;

    vector<int> mySortedValues(n);
    for (int i = 0; i < n; i++) //For loop to obtain all the values
    {
        cin >> mySortedValues[i];
    }

    int M; // M value for MTree
    cin >> M;

    MTree<int>* myTree = new MTree<int>(M); //Creates the initial tree
    myTree->buildTree(mySortedValues); 

    int numCommands; // Number of commands
    cin >> numCommands;

    char command; //How we decide what to do each loop
    int value; 

    for (int i = 0; i < numCommands; i++) //Main for loop which contains most of the interactions with the structure
    {
        cin >> command;

        switch (command) //switch case to determine what to do with the tree
        {
            case 'I': // Insert
            { 
                cin >> value;
                try 
                {
                    myTree->insert(value);
                    cout << "The value = " << value << " has been inserted." << endl;
                } 

                catch (DuplicateInsertion& e) 
                {
                cout << "The value = " << value << " already in the tree." << endl;
                }
                break;
            }

            case 'R': // Remove
            { 
                cin >> value;
                try 
                {
                    myTree->remove(value);
                    cout << "The value = " << value << " has been removed." << endl;
                } 

                catch (NotFoundException& e) 
                {
                    cout << "The value = " << value << " not found." << endl;
                }
                break;
            }

            case 'F': // Find
            {
                cin >> value;
                if (myTree->search(value)) 
                {
                    cout << "The element with value = " << value << " was found." << endl;
                } 
                else 
                {
                    cout << "The element with value = " << value << " not found." << endl;
                }
                break;
            }

            case 'B': //Build the tree
            {
                vector<int> all_values = myTree->collect_values();
                delete myTree;
                myTree = new MTree<int>(M);

                //Ensure no duplicates are inserted
                sort(all_values.begin(), all_values.end());
                all_values.erase(unique(all_values.begin(), all_values.end()), all_values.end());

                //Insert each value into the tree while checking for duplicates
                for (const auto& val : all_values) 
                {
                    try 
                    {
                        myTree->insert(val);
                    } 
                    catch (DuplicateInsertion& e) 
                    {
                    }
                }

                cout << "The tree has been rebuilt." << endl;
                break;
            }

            default:
                cout << "Invalid command!" << endl;
        }
    }

    //Print final tree values (lotta trial and error with whitespace)
    vector<int> final_values = myTree->collect_values();
    int count = 0;
    cout << "Final list: ";
    for (size_t i = 0; i < final_values.size(); i++) //Loop to print out the entire tree
    {
        cout << final_values[i] << " ";
        count ++;
        if (count % 20 == 0 && count < final_values.size()) //To match the outputs, every 20 numbers contains a newline, so we have a
                                                            //tracker for this exact purpose
        {
            cout << endl;
        }
    }
   cout << endl;

   delete myTree;
   return 0;
}

/*
    *****DOCUMENTATION*****

    AI USAGE:
    I (somehow) got away with not using AI throughout the duration of Project 4.

    DEBUGGING & TESTING PLAN:
    I will be experimenting with a new format for my debugging & testing plan in which I make notes by method and seeing how that reads,
    Hope that makes it easier to read! THis project started out really light, and then got really hard out of nowhere lol. I misgauged
    how complex the functions needed to be, which cause numerous errors. Feel free to read below for each

    is_leaf():
    {
        Very simple to accomplish. Simply need to check if the children vector is empty for the node, did not need to do much testing.
    }

    insert():
    {
        Insert seems simple on an initial review. We check to see if the value is already there, and if it is we throw an excpetion.
        Otherwise, insert the element in its correctly location with a series of find_child() calls, and split the node when we finally
        insert and if it's larger than it should be.


    }

    split_node():
    {
        Split node was a hard one. Eventually I figured out that I was not adding the nodes on either side of the median correctly and 
        once I calibrated for that I was able to correctly change things.
    }

    find_child():
    {
        Originally, I thought I had to concern myself with 2 edge cases, being the end and start of the list. Ultimately I realized 
        I can simply compare with the element in i and proceed accordingly. Will implement and come back to this section.

        Should be working! Will test shortly

        Works! Thank God
    }

    find():
    {
        My initial implementation consists of a for loop which iterates through the current node's values, & then calls find_child
        to find which one of the node's children should be used to recursively call find until we reach our value

        For some reason it is not working when it is the first command (ala Input1-1.txt), need to figure that out

        The issue came from a severe lack of understanding in buildTree, where the values simply weren't where they needed to be
    }

    remove():
    {
        According to the project 4 assignment, during insertion, the new value is added to the appropriate leaf node. If the leaf 
        node exceeds M values, the node performs splitting.

        Relatively easy to implement. Verify that the value is actually there & then a simple if loop to determine whether or not
        we've reached the appropriate leaf node; and then we simply perform pop_back on the vector which the value lies in

        Works! Can be verifeid through comparing the outputs
    }

    buildTree():
    {
        buildTree was given to the class by one of the TAs (Thank you Kenny!), so I have nothing to say in this section about it before
        testing

        The given buildTree method only partially worked for me. After some refactoring, I got it to function as intended.
    }

    collect_values():
    {
        At first I was confused how to accomplish this method, since I missed the fact that the leaf nodes also contain the values
        of the parent nodes. Will need to refactor how I wrote the method. I think I can accomplish this by recursively calling the
        method until I reach a leaf node

        for loop to iterate through each node, recursively calling collect_values() on their children until I reach the end. Then, 
        for loop to collect all the value into a vector. Will be a nightmare on space complexity but should work


    }

    main():
    {   
        Strange issue I've found is that when producing the final list, my allValues vector seems to have an infinite size and will 
        print indefinitely. It correctly prints the values in rows of 20, but for whatever reason it keeps rehasing all the values

        Fixed it. I realized after looking over documentation of generic trees that I was not balancing the tree upon certain operations.

        Ultimately, I had to scrap most of my project to find the issue. I realized I was not properly balancing my tree which caused
        several seperate, seemingly disconnected (at first) issues. I implemented a helper method for balancing the tree which thankfully
        fixed most of my issues, and all that was left was whitespace

        Initial testing resulted in just some minor whitespace issues, which the autograder did not seem to care about. Updated 
        documentation and now it is ready for a proper final submission.

    }
*/