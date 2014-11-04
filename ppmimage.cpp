#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "ppmimage.h"

//delete for submission
#include <bitset>


PPMImage::PPMImage(std::string sourceImageFilename)
{
    this->filename = sourceImageFilename;
    this->infileOpen = false;
    this->outfileOpen = false;
    loadImage();
}

PPMImage::~PPMImage()
{
    delete [] image;
    image = NULL;
}

void PPMImage::loadImage()
{

    // std::string path = "/Users/pablosettecase/Desktop/CS332C/HW3/";
    // std::string file = path.append(this->filename);
    // std::cout << "\nPath to file: " << file << "\n";
    std::string line;
    std::ifstream infile;
    infile.open(this->filename, std::ifstream::binary);
    if(infile.is_open())
    {
        infileOpen = true;

        std::cout << "\nFile successfully opened.\n";
        infile >> line;
        this->magicNumber = line;
        int readWidth, readHeight, readMaxvalue;
        infile >> readWidth;
        this->width = readWidth;
        infile >> readHeight;
        this->height = readHeight;
        infile >> readMaxvalue;

        infile.ignore();

        this->maxColorValue = readMaxvalue;

        int arrSize = width * height * 3;

        image = new char [arrSize];
        infile.read(this->image, arrSize);

        /* print the first 10 bytes as ints
        for (int i = 0 ; i < 10 ; i++) {
            std::cout << static_cast<int>(static_cast<unsigned char>(this->image[i])) << " ";
        }*/

        infile.close();
    }
    else
    {
        std::cout << "\n\tERROR: ";
        std::cout << "Unable to open " << this->filename << ".\n";
        std::cout << "\tTry typing in the full extension to the file.\n";
    }

}

void PPMImage::writeImage(std::string outputFilename)
{
    // std::string path = "/Users/pablosettecase/Desktop/CS332C/HW3/";
    // std::string file = path.append(outputFilename);
    std::ofstream outfile(outputFilename, std::ofstream::binary);

    outfile << this->magicNumber << "\n";
    outfile << this->width << " " << this->height << "\n";
    outfile << this->maxColorValue << "\n";
    outfile.write(this->image, this->width * this->height * 3);
    outfile.close();
}

void PPMImage::hideData(std::string encodeMessage)
{
    int imagePos = 0;
    char * encode = new char[encodeMessage.length()];
    std::strcpy(encode, encodeMessage.c_str());

    // cycle through each character that we will hide
    for(int i = 0; i < encodeMessage.length(); i++)
    {

        // cycle through each bit in the char
        for(unsigned int bitPos = 0; bitPos < 8; bitPos++)
        {
            //std::cout << "\nCurrent char is encode[" << i << "]: " << encode[i] << "\n";//
            //std::cout << "\nimagePos: " << imagePos << "\n";//

            // KEEP if the bit at bitPos is on, turn on LSB in image array

            // (delete this) std::cout << "\nchecking if bit " << bitPos+1 << " is OFF.\n";//
            if((encode[i] & (1 << bitPos)) == 0)
            {
                //std::cout << "\n(encode[i] & (1 << bitPos)) == 0\n";//

                // the bit at bitPos is OFF
                // now check LSB in image array
                if((image[imagePos] & 1) == 1)
                {
                    //std::cout << "\n(image[imagePos] & 1) == 1\n";//

                    // the LSB is ON, turn OFF. Flip the bit
                    image[imagePos] = image[imagePos] ^ 1;
                }
            } else
            {
                // the bit at bitPos is ON
                // check LSB of image array

                // (delete this) std::cout << "\nchecking if bit " << bitPos+1 << " is ON.\n";//
                if((image[imagePos] & 1) == 1)
                {
                    // (delete this) std::cout << "\n(image[imagePos] & 1) == 1\n";//
                    // the LSB is ON, no need to do anything
                }
                else
                {
                    // the LSB is OFF, flip the bit
                    image[imagePos] = image[imagePos] ^ 1;
                }
            }
        imagePos++;
        }
    }

    // Finished hiding the characters, insert null char
    // for the next 8 LSB in image
    for(unsigned int i = 0; i <= 8; i++)
    {
        // is LSB in image arr on?
        if((image[imagePos] & 1) == 1)
        {
            //LSB is on, we want it off. Flip the bit
            image[imagePos] = image[imagePos] ^ 1;
        }
        else
        {
            // LSB is off, don't need to do anything
        }
        imagePos++;
    }

    imagePos = 0;
    // delete the pointers below!

}

std::string PPMImage::recoverData()
{
    std::string message = "";
    char a = 0;
    //int maxSize = width * height * 3;
    int i = 0;
    int nullCount = 0;
        while(true)
        {
            if( !((image[i] & 1) == 1) && nullCount >= 7 )
            {
                // std::cout << "\nFound 8 consecutive 0 bits. End of message.\n";//
                break;
            }

            for(int bitPos = 0; bitPos < 8 ; bitPos++)
            {
                // check if LSB in image arr is ON
                if((image[i] & 1) == 1)
                {
                    nullCount = 0;
                    //std::cout << "\nimage[" << i << "]" << ", bitPos= " << bitPos << "\n";//

                    // add a 1 at the bit position
                    char temp = (1 << bitPos);

                    //std::bitset<8> tmp(temp);//
                    //std::cout << "\ntemp char (1 << bitPos): " << tmp << "\n";//
                    a = a | temp;
                    i++;
                    //std::bitset<8> aa(a);//
                    //std::cout << "\nchar a: (a = a | temp) " << aa << "\n";//
                }
                else
                {
                    // LSB is OFF, add 0 at the bit position
                    // increase null count
                    nullCount++;
                    i++;
                }

                //std::cout << "\nnullCount: " << nullCount << "\n";

            }

            // finished one char
            // check its type and append it

            // std::cout << "\nchar added: " << a;//
            // std::cout << "\nchar casted: " << static_cast<unsigned char>(static_cast<int>(a));
            message += a;
            // std::cout << "\nmessage so far: " << message;//
            a = 0;
        }

    return message;
}

// delete the function below for submission
void PPMImage::printSomeBits(int numberBytesToPrint)
{
    char a;
    std::cout << "\n\n*****Printing some bytes for testing.*****\n\n";

    for(int i = 0; i < numberBytesToPrint; i++)
    {
        a = this->image[i];
        std::bitset<8> x(a);
        std::cout << "image[" << i << "]:\t" << x << "\n";
        /*
        if((a & 1) == 1)
        {
            std::cout << "LSB is on\n";
        }
        else
        {
            std::cout << "LSB is off\n";
        }
        */
    }
    std::cout << "\n";
}

