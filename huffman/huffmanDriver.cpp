#include "huffman.h"


void main()
{
	huffman huffman1;
	string command = "";
	cout << "Enter Help as a command for a list of commands and what they do." << endl;

	while(command != "Quit")
	{
		cout << "Enter a command: ";
		cin >> command;
		if(command == "Encode")
		{
			cin.sync();
			cin.clear();
			string input;
			cout << "Input the string to be encoded: ";
			getline(cin, input);
			huffman1.MakeTree(input);
			huffman1.breadthFirstPrint();
			cout << endl;
			huffman1.EnCode(cout, input);
			cout << endl;
		}
		else if (command == "Decode")
		{
			if(!huffman1.isEmpty())
			{
				cin.sync();
				cin.clear();
				string input;
				cout << "Input the string to be encoded: ";
				getline(cin, input);
				huffman1.DeCode(cout, input);
				cout << endl;
			}
			else
			{
				cout << "No tree to decode with." << endl;
			}
		}
		else if (command == "Help")
		{
			cout << "The Encode command will build a tree and encode the input string." << endl;
			cout << "The Decode command will decode the given string" << endl;
		}
	}
}