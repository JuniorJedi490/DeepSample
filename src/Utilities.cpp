/* 
 *  File:    Utilities.cpp
 *  Author:  Hue Truong and Andrew Moore
 *
 *  Created: February 23, 2020, 3:25 PM
 */

/**************************************Change Log *******************************/

// Created source file for utilities - A.M. Feb 23 2020
// Added in the printer function definition - A.M. Feb 23 2020
// Added vector normalization function - A.M. Feb 28 2020

/**************************************End Change Log ***************************/

/**************************************To Do List ******************************/

/**************************************End To Do List **************************/

#include "../include/Utilities.h"

// Function printer
// Inputs:  
//        fileName - A string containing the name of the output file.
//        value - A string to be addd to the output file.
//        algo - An integer specifying the algorithm that called the printer.
//        begin - An integer describing the beginning of the printed range.
//        end - An integer describing the end of the printed range.
// Outputs:  None
// Purpose:  Formats and outputs text to a file.
void printer (string fileName, vector<string> value, int algo, int begin, int end)
{
    ofstream outFile;                // Points to user specified output file
    stringstream stringBuilder;      // This will be used to create the output string
    string line;                     // Stores the line as the string is built

    outFile.open(fileName, ios::app);

    switch (algo)  // Switch to determine which algorithm we are using.
    {
        case 0:  // ZeroShift algorithm
        {
            for (int i = 0; i < value.size() - 1; i++)
            {
                if (i == 0)
                    line = "Iteration:";
                if (i == 1)
                    line = "Real I [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 2)
                    line = "Real I+1 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 3)
                    line = "Sign 1 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 4)
                    line = "Sign 2 [" + to_string(begin) + " - " + to_string(end) + "]:";
                if (i == 5)
                    line = "ZeroCross [" + to_string(begin) + " - " + to_string(end) + "]:";

                outFile << line << setiosflags(ios_base::left) << setw(30-line.length()) << " "
                        << resetiosflags(ios_base::left) << setiosflags(ios_base::right) << value[i]
                        << resetiosflags(ios_base::right) << endl << endl;

            }
           
            for (int i = 0; i < 100; i++)
                outFile << "_";

            outFile << endl << endl;
 
            break;
        } // End ZeroShift algorithm

        case 2:  // Spectrum Flux algorithm
        {
            break;
        }  // End Spectrum Flux algorithm

        case 3:  // Cepstral algorithm
        {
            break;
        }  // End Cepstral algorithm

        case 4:  // Complex Cepstral algorithm
        {
            break;
        }  // End Complex Cepstral algorithm

        default:
            break;
    }

    outFile.close();
}

// Function createString (int version)
// Inputs:
//       data - An integer to be converted to a string.
//       fieldWidth - An integer specifying the width of the data field.
// Outputs:  
//       newString - The string version of the input
// Purpose:  Generate strings from given input
string createString(int data, int fieldWidth)
{
    stringstream stringBuilder;
            
    stringBuilder << setiosflags(ios_base::left) << setw(fieldWidth) << to_string(data) + "  " << resetiosflags(ios_base::left);

    return stringBuilder.str();
}

// Function createString (double version)
// Inputs:
//       data - A double to be converted to a string.
//       fieldWidth - An integer specifying the width of the data field.
// Outputs:
//       newString - The string version of the input
// Purpose:  Generate strings from given input
string createString(double data, int fieldWidth)
{
    stringstream stringBuilder;

    stringBuilder << setiosflags(ios_base::left) << setw(fieldWidth) << to_string(data) + " " << resetiosflags(ios_base::left);

    return stringBuilder.str();
}

// Function createString (boolean version)
// Inputs:
//       data - A boolean to be converted to a string.
//       fieldWidth - An integer specifying the width of the data field.
// Outputs:
//       newString - The string version of the input.
// Purpose:  Generate strings from given input
string createString(bool data, int fieldWidth)
{
    stringstream stringBuilder;
 
    stringBuilder << setiosflags(ios_base::left) << setw(fieldWidth) << to_string(data) + " " << resetiosflags(ios_base::left);

    return stringBuilder.str();
}

// Function normalize
// Inputs:
//       data - A vector of complex doubles describing an audiowave.
//       frames - An integer describing the number of frames to break wave into.
//       normals - A vector of doubles that will contain the normalized vector
//       channel - An integer describing the channel we are normalizing.
//       debug - A flag that controls debug output.
//       path - A string describing the output directory
// Outputs: None
// Purpose:  This is a function that normalizes a vector
void normalize(vector<complex<double> > data,vector<double> &normals,int frames,int channel, bool debug,string path)
{
    double mag;           // Will hold the magnitude of the vector
    int step;             // Used to calculate beginning of next frame.
    string fileName;      // Will contain the file and path for debug output
    ofstream outfile;     // Stream pointer for debug output

    // Clear out the normals vector
    normals.clear();

    if (debug)
    {
        fileName = path + "/normals.txt";

        outfile.open(fileName.c_str(), ios::app);

        outfile << "Frames = " << frames << endl;

        if (channel == 1)
            outfile << "Left Channel Normals:" <<  endl;
        else if (channel == 2)
            outfile << "Right Channel Normals:" << endl;
    }

    mag = 0;
    step = frames;

    for (int i = 0; i <= data.size() - 1; i += step)
    {
        double tempMag = 0;

        if ((i+step) >= data.size())
            step = (i + step) - data.size();
    
        // Calculate the inside of the magnitude
        for (int j = i; j <= step; j++)
        {
            tempMag += real(data[j]) * real(data[j]);
        }

        // Calculate the magnitude
        mag = sqrt(tempMag);

        // Calculate normals of the window
        for (int j = i; j <= step; j++)
        {
            normals.push_back((real(data[j]) / mag));
        }

        if ( (step >= 1) && ((i + frames-1) < data.size() -1))
            step = frames-1;
        else if (step != 1)
            step = 1;
    }

    if (debug)
    {
        outfile << "Total Elements = " << normals.size() << endl;
   
        outfile << "[" << endl;

        for (int i = 0; i <= normals.size() - 1; i++)
        {
            outfile << normals[i] << " ";
 
            if (((i % 10) == 0) && (i != 0))
                outfile << endl;
        }

        outfile << endl << "]" << endl << endl;
 
        for (int i = 0; i < 100; i++)
            outfile << "*";

        outfile << endl << endl;

        outfile.close();
    }

    return;
}
