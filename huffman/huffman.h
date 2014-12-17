#include <cstdio>
#include "pQueue.h"
#include <string>
#include <fstream>
#include <sstream>


struct TreeNode
{
	char data;//char
	int NodeNum;
	TreeNode* left;
	TreeNode* right;
};


class huffman
{
public:
	huffman();
	//Pre-Condition:
	//Function: Class constructor
	//Post-Condition: Root is set to NULL, outFile is opened

	~huffman();
	//Pre-Condition:
	//Function: Deconstructor (calls destroySubTree on the root node)
	//Post-Condition: All content is deleted, out file is closed

	void MakeTree(string input);
	//Pre-Conditions: huffman is initialized
	//Function: The makeTree function takes a string and makes a huffman tree out of it.
	//PostCondition: The huffman tree is made with the more frequent data toward the top of the tree.

	void EnCode(ostream& outstream, string input);
	//PreConditions: the huffman tree has been made
	//Function: the encode function uses the tree to turn the data into 1's andd 0'1
	//PostCondition: returns the fully encoded string

	void DeCode(ostream& outStream, string input);
	//PreConditions: the huffman tree has been made
	//Function: the decode function takes a string of 1's and 0's and decodes them to the data in the tree
	//PostCondition: returns a string of the data

	void breadthFirstPrint();
	//PreConditions: none
	//Function: prints out the huffman tree ith no spaces between the data
	//PostCondition: the tree is printed out (degree signs show none leaf nodes for the huffman tree and squares are filler for a dummy node)

	int getHeight(TreeNode* &tPtr);
	//Pre-Condition: 
	//Function: finds the Height of a node
	//Post-Condition: returns the Height of the node

	ostream& print(ostream& outStream, string data);
	//Pre-Condition: 
	//Function: Prints out the data in the node
	//Post-Condition: node data is output

	void exportToFile(string data);
	//Pre-Condition: 
	//Function: Prints out the data to a file
	//Post-Condition: data is output

	string importFromFile();
	//Pre-Condition: 
	//Function: takes data in from a file
	//Post-Condition: data is input

	bool isEmpty();
	//Pre-Condition: 
	//Function: Checks if root == NULL
	//Post-Condition: Returns true if tree is empty

	void destroySubTree(TreeNode* &tPtr);
	//Pre-Condition: 
	//Function: destroys node and all its desendants
	//Post-Condition: the node and everything below it no longer exist

private:
	TreeNode* root;
	ofstream outFile;      // file containing output

	void search(ostream& outStream, char hunt, string input, TreeNode* tPtr);
	//Pre-Condition: huffman tree is made
	//Function: finds the node and path when encodeing
	//Post-Condition: prints out encoded string to file and screen
	
};

huffman::huffman()
{
	root = NULL;
	outFile.open("huffOut.txt");
	
}
huffman::~huffman()
{
	destroySubTree(root);
	outFile.close();
}

bool huffman::isEmpty()
{
	return(root == NULL);
}

void huffman::destroySubTree(TreeNode* &tPtr)
{
	if(tPtr != NULL)
	{
		destroySubTree(tPtr->left);
		destroySubTree(tPtr->right);
	}
	delete tPtr;
}

void huffman::MakeTree(string input)
{
	const int A_SIZE = 255;
	int cArray[A_SIZE];////
	for(int i = 0; i < A_SIZE; i++)
	{
		cArray[i] = 0;
	}

	unsigned int index = 0;
	while(index < input.length())
	{
		char temp = input[index];

		cArray[temp] = cArray[temp] + 1;
		index++;
		
	}

	Queue<TreeNode*> pQueue1;
	for( int i = 0; i < A_SIZE; i++)////
	{
		cout << cArray[i] << " ";/////////////debug//////////////////
		if(cArray[i] == 0)
		{

		}
		else
		{
			TreeNode* newNode = new TreeNode;
			newNode->data = i;
			newNode->NodeNum = cArray[i];
			newNode->left = NULL;
			newNode->right = NULL;
			pQueue1.EnQueue(newNode, newNode->NodeNum);
		}
	}
	cout << endl;
	
	while(pQueue1.LengthIs() > 1)
	{
		
		TreeNode* temp1;
		TreeNode* temp2;
		pQueue1.DeQueue(temp1);
		pQueue1.DeQueue(temp2);

		TreeNode* newNode = new TreeNode;
		newNode->data = 248;//number if the filler nodes display //248 is a small circle/degree sign
		newNode->NodeNum = (temp1->NodeNum + temp2->NodeNum);
		cout << newNode->NodeNum << "|";//////////////debug
		newNode->left = temp1;
		newNode->right = temp2;

		pQueue1.EnQueue(newNode, newNode->NodeNum);
		cout << pQueue1.LengthIs() << " ";///////////debug
	}
	pQueue1.DeQueue(root);
}

void huffman::EnCode(ostream& outStream, string input)
{
	string eLetter = "";
	for(unsigned int i = 0; i < input.length(); i++)
	{
		search(outStream, input[i], eLetter, root);
	}
}

void huffman::search(ostream& outStream, char hunt, string input, TreeNode* tPtr)
{
	if(tPtr != NULL)
	{
		if(hunt == tPtr->data)
		{
			print(outStream, input);
			exportToFile(input);
		}
		else
		{
			string temp = input;
			input.append("0");
			search(outStream, hunt, input, tPtr->left);
			temp.append("1");
			search(outStream, hunt, temp, tPtr->right);
		}
	}
}

void huffman::breadthFirstPrint()

{
	Queue<TreeNode*> Que1;//make a queue

	if(root != NULL)
	{
		Que1.EnQueue(root, 0);
	}

	TreeNode* dummy = new TreeNode;
	dummy->left = NULL;
	dummy->right = NULL;
	dummy->data = 254;//change for other datatypes +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	TreeNode* temp;

	int count = 0;
	int row = 0;
	while(!Que1.IsEmpty() && count < (pow((double)2, (int)(getHeight(root))) - 1))//makes it print full rows but stops it from indefinite looping
	{
		if(count == pow((double)2, (int)row) - 1)//finds when a new row is needed
		{
			cout << endl;
			for( int i = ((int)pow((double)2, (int)getHeight(root) - 1) - ((int)pow((double)2, (int)row))) / 2; i > 0; i--)
			{//this loop adds spaces to make the tree display look pretty! //remove this for statement to left align the tree
				cout << " ";
			}
			row++;//tracks the row we are on
		}
		count++;//tracks the number of items displayed (tree items + dummyFillers)

		Que1.DeQueue(temp);
		if(temp->data != 254)//adds either node data or a dummy filler //change for other datatypes +++++++++++++++++++++++++++++
		{
			cout << temp->data << "";
		}
		else
		{
			cout << "X ";
		}

		if(temp->left != NULL)//queues the left node or a dummy if left is NULL
		{
			Que1.EnQueue(temp->left, 0);
		}
		else
		{
			Que1.EnQueue(dummy, 0);
		}

		if(temp->right != NULL)//queues the right node or a dummy if right is NULL
		{
			Que1.EnQueue(temp->right, 0);
		}
		else
		{
			Que1.EnQueue(dummy, 0);
		}

	}//end while Queue !isempty
	cout << endl;
	Que1.~Queue();
}//end breadth first print

int huffman::getHeight(TreeNode* &tPtr)
{
	if(tPtr != NULL)
	{
		int LHeight = getHeight(tPtr->left);
		int RHeight = getHeight(tPtr->right);

		if(LHeight > RHeight)
		{
			return(1 + LHeight);
		}
		else //(Lhiehgt <= RHeight)
		{
			return(1 + RHeight);
		}
	}
	else
	{
		return(0);
	}
}

void huffman::DeCode(ostream& outStream, string input)
{
	TreeNode* tPtr = root;
	for(unsigned int i = 0; i <= input.length(); i++)
	{
		if(tPtr->left == NULL && tPtr->right == NULL)
		{
			outStream << tPtr->data;
			tPtr = root;
			i--;
		}
		else if(i < input.length() && input[i] == '0')
		{
			tPtr = tPtr->left;
		}
		else if(i < input.length() && input[i] == '1')
		{
			tPtr = tPtr->right;
		}
		else if(i == input.length())
		{
			break;
		}
		else
		{
			cout << " ERROR! ";
		}
	}
}

ostream& huffman::print(ostream& outStream, string data)
{
	outStream << data << "";
	return outStream;
}

void huffman::exportToFile(string data)
{
	outFile << data;
}

string huffman::importFromFile()
{

	string line;
	ifstream inFile ("huffOut.txt");

	if (inFile.is_open())
	{
	    while ( inFile.good() )
		{
			getline (inFile,line);
			cout << line << endl;
		}
    inFile.close();
	}

	return line;
}