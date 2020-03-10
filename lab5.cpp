#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<assert.h>
using namespace std;

double week1 = 0;
double week2 = 0;
double week3 = 0;
double u = 0;

ofstream outfile;


struct Profit{
    double dollar;
    int duration;
};


class KYP{
    public:
    int total_weeks;
    double percentage;
    Profit *pp;//array of profit strucrt 
    KYP(int weeks){   //constructor to create array, set the total week
        pp = new Profit[weeks+1];
        total_weeks = weeks;
        outfile << "KYP's constructor"<<endl;

    }

    ~KYP(){
        outfile << "KYP's destructor"<<endl;
        delete[] pp;
    }

    //set the percentage fron input.txt
    void set_percentage(double per){
        percentage = per;
       
    }
    //set the average profit 
    void set_profit(int week, double money){
        Profit temp;
        temp.duration = week;
        temp.dollar = money;
        pp[week] = temp;

    }

    double get_profit(int week){
        return pp[week].dollar;
    }
};


class KWP{
    public:
    int total_weeks;
    Profit *pp;//array of profit strucrt 
    KWP(int weeks){  //constructor
        pp = new Profit[weeks+1];
        total_weeks = weeks;
        outfile<<"KWP's constructor"<<endl;

    }

    ~KWP(){      //destructor
        outfile << "KWP's destructor" <<endl;
        delete[] pp;
    }
    //set the average profit for KWP
    void set_profit(int week, double money){
        Profit temp;
        temp.duration = week;
        temp.dollar = money;
        pp[week] = temp;

    }
    //overloaded function to set each week's profit
    void set_profit(){
        for(int i = 4; i <= total_weeks; i++){
            set_profit(i,compute_profit(i)/compute_options(i));
        }

    }
    
    //compute the total number of profits in n weeks.
    double compute_profit(int n){ 
        assert (n >= 0);
        if(n == 0) return 0;
        if(n == 1) return pp[1].dollar*1;
        if(n == 2) return pp[2].dollar*2;
        if(n == 3) return pp[3].dollar*4;

        return pp[1].dollar + compute_profit(n-1) + pp[2].dollar + compute_profit(n-2) + pp[3].dollar + compute_profit(n-3);

    }

    //compute the options in w weeks.
    int compute_options(int w){
        assert (w >=0);
        if (w ==0){
            return 0;
        }
        else if (w ==1){
            return 1;
        }
        else if (w ==2){
            return 2;
        }
        else if (w ==3){
            return 4;
        }
        return (compute_options(w -3) + compute_options(w -2) + compute_options(w -1));
    }


    double get_profit(int week){
        return pp[week].dollar;

    }
};


int main(){

    cout << "how many weeks"<<endl;
    int user_week;
    cin >>user_week;
  
    ifstream infile;
    //ofstream outfile;

    infile.open("input.txt");
    outfile.open("output.txt");


    string text;
    int col = 0;
    if(infile.is_open()){
        string t,b;
        while(getline(infile,text)){
            stringstream tt(text);
            if(col == 0){
             
            }
            else if(col == 2){
                tt>>t>>b;
                week1 = stod(b);

            }
            else if (col == 4){
                tt>>t>>b;
                week2 = stod(b);
            }
            else if (col == 6){
                tt >> t >> b;
                week3 = stod(b);
            }
            else if (col == 9){
                tt >> t;
                u = stod(t);
            }
            col++;
        }
    }
    KWP kayan_profit(user_week);
    KYP koro_profit(user_week);
    
    kayan_profit.set_profit(0,0); //week o;
    kayan_profit.set_profit(1,week1);//week 1
    kayan_profit.set_profit(2,week2);//week 2
    kayan_profit.set_profit(3,week3);//week 3

    kayan_profit.set_profit();

    koro_profit.set_percentage(u);
    
    for(int i = 0; i<=user_week; i++){
        koro_profit.set_profit(i, kayan_profit.get_profit(i)*koro_profit.percentage/100);
    }
    for(int j =0; j <= user_week; j++){
        cout<< "KW's profit for " << j<<" number of weeks in average is estimated " << kayan_profit.get_profit(j)<<" out of which "
        << u <<"%, ($"<<koro_profit.get_profit(j)<<") should go to KYP"<<endl; 
    }



    return 0; 
}