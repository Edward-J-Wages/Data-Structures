#include <iostream>
using namespace std;

//define all your classes here (as given above)
//write the methods after the class definition

int main () 
{
    int n, m, cv, noNSV;
    SparseMatrix* temp;

    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);

    //Write the Statements to read in the first matrix

    cin >> n >> m >> cv >> noNSV;
    SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);

    //Write the Statements to read in the second matrix

    cout << “First one in matrix format” << endl;
    (*firstOne).displayMatrix();

    cout << “First one in sparse matrix format” << endl;
    cout << (*firstOne);

    cout << “Second one in matrix format” << endl;
    (*secondOne).displayMatrix();

    cout << “Second one in sparse matrix format” << endl;
    cout << (*secondOne);

    cout << “Transpose of the first one in matrix” << endl;
    cout << (*(*firstOne).Transpose());

    cout << “Matrix Addition Result” << endl;

    temp = (*(*firstOne).Addition(secondOne));
    cout << temp;
    (*temp).displayMatrix();

    cout << “Matrix Multiplication Result” << endl;
    
    temp = (*(*firstOne).Multiply(secondOne));
    cout << temp;
    (*temp).displayMatrix();
}
