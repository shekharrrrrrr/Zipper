#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../Headers/huffmanAlgorithm.h"

int main(){

    //Note:This program can compress and decompress text file consisting of 128 ASCII characters.

    std::cout<<"\n[Type File to read a file] --- \n";
    std::cout<<"\n[Use 'No' to compress your given input Msg -> (Huffman Algorithm...)]\n";

    //read the input to complete one of the above following command
    std::string input;
    std::cin>>input;

    //Read a File
    if(input == "File"){
        std::string file;
        std::string str;
        std::ifstream myfile;

        myfile.open("../External Files/Txtfile.txt");

        std::cout<<"\nTxtFile content: \n";

        if ( myfile.is_open() ) {
            while ( myfile ) {
                std::getline (myfile, file);
                std::cout << file << '\n';
                //storing the text content file in string str
                str += file;
            }
        }

        //Pass the text to get compressed :)
        Huffman(str);
    }
    //give Input
    else if(input == "No"){
        
        std::string str;
        std::cout << "\nInput a message to get compressed\n";
        std::cin.ignore(); //basically, cin>> doesn't remove new lines from the buffer when the user presses enter.
        std::getline(std::cin, str);
        std::cout<<"\n*********************************************************************\n";

        //Pass the text to get compressed :)
        Huffman(str);
 
    }
    //Error!!!
    else{
        std::cout<<"Ahoh!! Please write a proper command :(\n";
    }

    return 0;
}