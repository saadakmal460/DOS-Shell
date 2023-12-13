#pragma once

#include <list>

using namespace std;

class Shell
{
public:
	struct FileStructure
	{
		struct File
		{
			string name;
			string data;
			string extension;
			int size;
		};

		struct Directory
		{
			string name;
			string path;

			list<Directory> directories;
			list<File> files;
			Directory* parent;

			Directory()
			{
				name = "";
				path = "V:\\>";
				parent = nullptr;
			}

			Directory(string n, string p, Directory* par)
			{
				name = n;
				path = p;
				parent = par;
			}
		};
		Directory* rootDirectory;
		Directory* currentDirectory;

		FileStructure()
		{
			rootDirectory = new Directory();
			currentDirectory = rootDirectory;
		}
	};

	FileStructure virtualFileStructure;

	Shell()
	{
		virtualFileStructure = FileStructure();
	}

	void PrintAuthorInfo()
	{
		cout << "Authors: Mian Muhammad Ashhad, Muhammad Saad Akmal" << endl;
		cout << "Registration Numbers: 2022-CS-114, 2022-CS-148" << endl;
		cout << "Course: Data Structures and Algorithms" << endl;
		cout << endl << endl;
	}

	void DisplayCurrentPath()
	{
		cout << virtualFileStructure.currentDirectory->path;
	}

	void Help()
	{
		cout << "cd. : Displays working directory";
		cout << "pwd : Displays working directory";
	}

	void PWD()
	{
		cout << "Current Directory: \"";
		cout << virtualFileStructure.currentDirectory->path << "\"";
		cout << endl;
	}

	void ExecuteCommand(string command)
	{
		if (command == "pwd" || command == "cd.")
		{
			PWD();
		}

		else
		{
			cout << "No such command found: \"" << command << "\"";
			cout << endl;
		}
	}
};