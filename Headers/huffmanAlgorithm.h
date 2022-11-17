#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <queue>
#include <vector>


//Global Variables:
// To store the frequency of character of the input data 
std::map<char,int> frequency;
// To store character and huffman code assigned to each character.
std::map<char, std::string> binaryCode;
//Compressed size vairable value
int compressedSize = 0;

//Single Node of Huffman Tree;
class minHeapNode {
    public:
    char ele;
    int freq;
    minHeapNode *left; //left edge = 0;
    minHeapNode *right; //right edge = 0;

    minHeapNode(char ele,int freq){
        this->ele = ele;
        this->freq = freq;
        left = nullptr;
        right = nullptr;
    }
};

//Comparator
struct compare 
{ 
	bool operator()(minHeapNode* a, minHeapNode* b) 
	{ 
		return (a->freq > b->freq); 
	} 
}; 

//Priotity queue to store in minheap format and merger two samllest one
std::priority_queue<minHeapNode*, std::vector<minHeapNode*>, compare> pq; 

//store leaf ele and their binary representation
void charAndbinaryCode(minHeapNode *root , std::string s){
    if(!root)
        return;

    if(root->ele != '$'){
        binaryCode[root->ele] = s;
    }

    charAndbinaryCode(root->left,s+"0");
    charAndbinaryCode(root->right,s+"1");
}

void buildHuffmanTree(int size){
    // To generate a priority queue to merge to small nodes
    for(auto &it : frequency){
        pq.push(new minHeapNode(it.first,it.second));
    }

    //Now generate Tree by merging teh two top small nodes and sum them do this step until one node is left

    minHeapNode *left = nullptr ,*right = nullptr ,*mergedNode = nullptr;

    //Tree step
    while(pq.size()!=1){
        //pick top most two small nodes mergem 
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();

        //mergedNode
        //'$' is a special value for internal nodes, not used case:
        mergedNode =  new minHeapNode('$' , left->freq + right->freq);

        mergedNode->left = left;
        mergedNode->right = right;

        pq.push(mergedNode);
    }

    charAndbinaryCode(pq.top(),"");
}

//encoded Huffman string
void encodedString(std::string &encodedStr,std::string &input){
    for(auto &c : input){
        encodedStr += binaryCode[c];
        compressedSize += binaryCode[c].size();
    }
    std::cout << "\nEncoded Huffman data:\n";
    std::cout<<encodedStr<<"\n";
}

//Decoded Huffman String
void decodedHuffmanstr(minHeapNode* root, std::string s)
{
    std::string ans = "";
    minHeapNode* curr = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
        curr = curr->left;
        else
        curr = curr->right;
 
        // reached leaf node
        if (curr->left==NULL && curr->right==NULL)
        {
            ans += curr->ele;
            curr = root;
        }
    }
    std::cout << "\nDecoded Huffman Data:\n";
    std::cout<<"\n"<<ans<<"\n";
}

//Build HuffMan tree and Decode!!
void Huffman(std::string input){

    //store the frequency in the map
    for(auto &c : input){
        frequency[c]++;
    }

    //Huffman Tree Building
    int size = input.size();
    buildHuffmanTree(size);

    //Print curr Char and there compressed Binary Code
    for(auto &it : binaryCode){
        std::cout<<it.first<<" "<<it.second<<"\n";
    }

    std::cout<<"\n";
    
    //Printing Encoded String
    std::string encodedStr = "";
    encodedString(encodedStr,input);

    //Finally print the Output string lol!!
    decodedHuffmanstr(pq.top(),encodedStr);

    //size
    std::cout<<"\nOld Size : = "<<(size*8)<<"\n"; //as our code runs for ascii only each char 128 takes maximum 8 bits
    std::cout<<"\nNew Size : = "<<compressedSize<<"\n";

}