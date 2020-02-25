#include<iostream>
#include<fstream>

using namespace std;

class Matrix{

    public:
        ifstream infile;
        ofstream outfile;
        int value[20][10];
        int list[10];
        int iteration_linear;
        int iteration_binary;

        int linearsearch();
        void sort_row(int length);
        int binarySearch(int left_arry, int right_array);
        int filltoarray(int r);
        void write_to_input();

};

//liear search for first number, return the row number
int Matrix::linearsearch(){ 
    int firstNum = value[0][0];
    for(int i = 0; i<20; i++){
       for(int j =0; j<10; j++){
           iteration_linear++;
           //if the 99 = value[i][j], and the iteration is bigger than 1 (to avoid the return after compare with itself)
           if ((value[i][j] == firstNum)&&(iteration_linear >1))
            return i;
       }
   }
   return 0;
     
} 
 
//once found that row, stor that entire row into array, list
int Matrix::filltoarray(int row){
    for(int i = 0; i<10; i++){
        list[i] = value[row][i];
    }
    return 0;
}

//sort the array named list, using recurcive. 
void Matrix::sort_row(int n){
    int temp;
    //base case
   if(n == 1)
        return;
    //recursive case
    for(int i = 0; i <n-1; i++){
        if(list[i] > list[i+1]){
            temp = list[i];
            list[i] = list[i+1];
            list[i+1] = temp; 
        }    
    }
    sort_row(n-1);
}
           
int Matrix::binarySearch(int l, int r) 
{ 
   while (l <= r) 
  { 
    int m = l + (r-l)/2; 
    iteration_binary++;

    // Check if first-number is present at mid 
    if (list[m] == value[0][0])  
        return m;   
  
    // If first-number greater, ignore left half   
    if (list[m] < value[0][0])  
        l = m + 1;  
  
    // If first-number is smaller, ignore right half  
    else 
         r = m - 1;  
  } 
  // if we reach here, then element was not present 
  return -1;   
} 


//write all result into the input.txt file
void Matrix::write_to_input(){

    int rows =linearsearch(); 
    
    filltoarray(rows);

    outfile << iteration_linear <<endl;
        
    sort_row(10);

    for(int i = 0; i <10; i++)
        outfile <<list[i] <<" ";

    int result = binarySearch(0, 10);
    outfile<<endl;
    outfile <<result <<endl;
    outfile << iteration_binary <<endl;
} 


int main(){
    Matrix item;

    item.infile.open("input.txt");
    item.outfile.open("output.txt");
    item.iteration_linear = 0;
    item.iteration_binary = 0;
  
    if(!item.infile)
        cout<< "Error opening file" << endl;
    else
    {
        while(!item.infile.eof())
        {
            for(int row = 0; row < 20; row++){
                for(int col = 0; col < 10; col++){
                    int x;
                    item.infile >> x;
                    item.value[row][col] = x;

                }
            }
        }
    }

    item.write_to_input();

    item.infile.close();
    item.outfile.close();
}





