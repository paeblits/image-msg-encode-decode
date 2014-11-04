#include <iostream>
#include <string>
#include "ppmimage.h"

/**
  * HW 3: Steganography
  *
  * By Pablo Settecase
  *
  * NOTE: Please remember, I'm a mac user!
  * You have had trouble compiling my code before
  *
**/

void hideSecretMessage();
void recoverSecretMessage();
void printBits();
void testReadWrite();

int main()
{
    int input = 9;
    while(input != 3)
    {
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "\t1) HIDE a secret message\n";
        std::cout << "\t2) RECOVER a secret message\n";
        std::cout << "\t3) EXIT\n\n";

        // delete the options below for submission
        std::cout << "\t8) TEST: print some bytes\n";
        std::cout << "\t9) TEST: read and write\n";
        std::cout << "\nYour selection: ";
        std::cin >> input;

        switch(input)
        {
        case 1:
            hideSecretMessage();
            break;
        case 2:
            recoverSecretMessage();
            break;
        case 3:
            break;
        case 8:
            printBits();
            break;
        case 9:
            testReadWrite();
            break;
        }// end of switch
    }// end of while

    return 0;
}

void hideSecretMessage()
{
    std::string readFilename, writeFilename, encodeMessage;

    std::cout << "\nPlease specify the SOURCE file name: ";
    std::cin >> readFilename;
    PPMImage p1(readFilename);
    std::cout << "\nThank you. Please specify the DESTINATION file name: ";
    std::cin >> writeFilename;
    if(writeFilename == readFilename)
    {
        std::cout << "\nDESTINATION file name and SOURCE filename are the same.\n";
        std::cout << "\nPlease choose a different file name for your DESTINATION file.\n";
    }
    else
    {
        std::cout << "\nThank you. Please specify a secret message to encode. \nYour message: ";
        std::cin.ignore();
        std::getline(std::cin, encodeMessage);
        p1.hideData(encodeMessage);
        p1.writeImage(writeFilename);
        std::cout << "\nThe message: \"" << encodeMessage << "\" has been added to the file: ";
        std::cout << writeFilename << "\n";
    }

    // call destructor

}

void recoverSecretMessage()
{
    std::string filename;

    std::cout << "\nPlease specify the SOURCE file name with the secret message: ";
    std::cin >> filename;
    PPMImage * p1 = new PPMImage(filename);
    std::string message = p1->recoverData();
    std::cout << "\nThe SECRET message is: ";
    std::cout << message << "\n\n";

    // we need to call destructor here, we used new
    delete p1;
    p1 = NULL;
}

// delete this function for submission
void printBits()
{
    std::string readFilename;
    int numberBytesToPrint;

    std::cout << "\nPlease specify the SOURCE file name to print some bits: ";
    std::cin >> readFilename;
    PPMImage p(readFilename);
    std::cout << "\nHow many bytes do you want to print out? ";
    std::cin >> numberBytesToPrint;
    p.printSomeBits(numberBytesToPrint);

    // this is ok
    // destructor implicitly called after block
}

void testReadWrite()
{
    std::string readFilename, writeFilename;

    std::cout << "\nPlease specify the SOURCE file name: ";
    std::cin >> readFilename;
    PPMImage p2(readFilename);

    // check if the file opened successfully
    if(p2.infileIsOpen())
    {
        std::cout << "\nThank you. Please select the DESTINATION file name: ";
        std::cin >> writeFilename;
        if(writeFilename == readFilename)
        {
            std::cout << "\nDESTINATION file name and SOURCE filename are the same.\n";
            std::cout << "\nPlease choose a different file name for your DESTINATION file.\n";
        }
        else
        {
            // file is open and outfile name different than infile name
            p2.writeImage(writeFilename);
        }
    }
    else
    {
        // infile failed to open
    }


    // call destructor
}
