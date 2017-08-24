#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>
using namespace std;

//Goal: To create Temp and Energy/atom columns for each cycle files
int main()
{
    string line_;
    ifstream infile;
    ofstream outfile;
    int count = 0; //2
    
    double potE = 0.0;
    int locationPt;
    int locate=0;
    
    //arrays for the different compositions
    string compCu[6] = { "0","28","46","64","80","100" };
    string coolingRate[5] = { "1001","1010","11","011","101" };
    
    //to get heat files and cool files change the last section of infile.open and outfile.open
    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 5; y++)
        {
            infile.open("/Users/peiping_2000/Desktop/c50/" + compCu[2] + "/cool.dat");
                        outfile.open("/Users/peiping_2000/Desktop/c50/" + compCu[2] + "/coolPerAtom2.txt");
                        if (infile.is_open())
                        {
                            while (getline(infile, line_)) // checks if there are still lines
                            {
                                for (int i = 0; i < line_.length(); i++)
                                {
                                    if (line_[i] != ' ' && count == 1) // first column
                                        outfile << line_[i];
                                    else if (count == 2 && line_[i] == '-') //when it hits the negative sign for the potential
                                        outfile << line_[i];
                                    else if (line_[i] != ' ' && count == 2 && line_[i] != '-') // second column
                                    {
                                        for (int k = i; locate < 15; k++)
                                        {
                                            if (line_[k] == '.')
                                                locationPt = locate;
                                            else
                                            {
                                                setprecision(14);
                                                potE += (line_[k] - '0')*pow(10, 14 - locate);
                                                locate++;
                                                
                                            }
                                        }
                                        potE = potE / pow(10, 15 - locationPt);
                                        outfile << setprecision(14) << potE / 3000 * 96.4869 << endl;;
                                        i = line_.length();
                                    }
                                    else if (line_[i] == ' ')
                                    {
                                        outfile << ' ';
                                        count++;
                                    }
                                    
                                    
                                }
                                count = 0;
                                potE = 0.0;
                                locate = 0;
                            }
                            infile.close();
                            outfile.close();
                        }
                        else
                        {
                            cout << "something's wrong. File not open";
                        }
                        }
                        }
                        return 0;
                        
                        }
