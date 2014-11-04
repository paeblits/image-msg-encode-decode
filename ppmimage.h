#ifndef PPMIMAGE_H
#define PPMIMAGE_H

class PPMImage {

private:
    std::string magicNumber;
    int width;
    int height;
    int maxColorValue;
    std::string filename;
    char * image;

    void loadImage();

    bool infileOpen;
    bool outfileOpen;

public:
    PPMImage(std::string sourceImageFilename);
    ~PPMImage();

    void hideData(std::string stringToHide);
    std::string recoverData();
    void writeImage(std::string outPutImageFilename);
    // delete the function below for submission
    void printSomeBits(int numberBitsToPrint);
    bool infileIsOpen(){ return infileOpen; };
    bool outFileIsOpen(){ return outfileOpen; };
};

#endif // PPMIMAGE_H
