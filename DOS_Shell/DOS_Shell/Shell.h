#pragma once

#include <list>
#include <vector>

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

			File(string Name)
			{
				name = Name;
				extension = "txt";
			}
		};

		struct Directory
		{
			string name;
			string path;

			list<Directory*> directories;
			list<File*> files;
			Directory* parent;

			Directory()
			{
				name = "";
				path = "V:";
				parent = nullptr;
			}

			Directory(string Name, string Path, Directory* Parent)
			{
				name = Name;
				path = Path;
				parent = Parent;
			}
		};
		Directory* rootDirectory;
		Directory* currentDirectory;

		FileStructure()
		{
			rootDirectory = new Directory();
			currentDirectory = rootDirectory;
		}

		void PWD()
		{
			cout << "Current Directory: \"";
			cout << currentDirectory->path << "\"";
			cout << endl;
		}

		void MoveToParentDirectory()
		{
			if (currentDirectory->parent != nullptr)
			{
				currentDirectory = currentDirectory->parent;
			}
			else
			{
				cout << "Error: No parent directory is present" << endl;
			}
		}

		void MoveToRootDirectory()
		{
			if (currentDirectory != rootDirectory)
			{
				currentDirectory = rootDirectory;
			}
			else
			{
				cout << "Error: Already in root directory" << endl;
			}
		}

		Directory* FindDirectory(string targetName)
		{
			Directory* target = nullptr;

			for (auto it = currentDirectory->directories.begin(); it != currentDirectory->directories.end(); ++it)
			{
				if ((*it)->name == targetName)
				{
					target = *it;
					break;
				}
			}
			return target;
		}

		void ChangeDirectory(Directory* dir)
		{
			currentDirectory = dir;
		}

		void CreateDirectory(string name)
		{
			Directory* directory = new Directory(name, currentDirectory->path + "\\" + name, currentDirectory);
			currentDirectory->directories.push_back(directory);
		}

		void DisplayContents()
		{
			for (auto iter = currentDirectory->directories.begin(); iter != currentDirectory->directories.end(); ++iter)
			{
				cout << "\t\t\t\t<DIR>\t" << (*iter)->name << endl;
			}

			for (auto iter = currentDirectory->files.begin(); iter != currentDirectory->files.end(); ++iter)
			{
				cout << "\t\t\t\t     \t" << (*iter)->name + "." + (*iter)->extension << endl;
			}
		}

		void CreateFile(string name)
		{
			File* file = new File(name);
			currentDirectory->files.push_back(file);
		}

		File* SearchFile(string name)
		{
			for (auto iter = currentDirectory->files.begin(); iter != currentDirectory->files.end(); ++iter)
			{
				if ((*iter)->name == name)
				{
					return *iter;
				}
			}
			return nullptr;
		}

		bool DeleteFile(string name)
		{
			File* file = SearchFile(name);
			if (file != nullptr)
			{
				currentDirectory->files.remove(file);
				return true;
			}
			else
			{
				return false;
			}
		}
	};

	FileStructure virtualFileStructure;

	Shell()
	{
		virtualFileStructure = FileStructure();
	}

	void PrintAuthorInfo()
	{
		cout << "Mian Muhammad Ashhad\t|\tMuhammad Saad Akmal" << endl;
		cout << "2022-CS-114\t\t|\t2022-CS-148" << endl;
		cout << "Data Structures and Algorithms" << endl;
		cout << endl << endl;
	}

	void Help()
	{
		cout << "cd. : Displays working directory";
		cout << "pwd : Displays working directory";
	}

	void DisplayCurrentPath()
	{
		cout << virtualFileStructure.currentDirectory->path + "\\>";
	}

	vector<string> ParseCommand(string command, string delimiter)
	{
		std::vector<std::string> result;

		size_t start = 0;
		size_t end = command.find(delimiter);

		while (end != std::string::npos)
		{
			std::string substring = command.substr(start, end - start);
			result.push_back(substring);

			start = end + delimiter.length();
			end = command.find(delimiter, start);
		}

		// Add the last substring after the last delimiter
		std::string lastSubstring = command.substr(start);
		result.push_back(lastSubstring);

		return result;
	}

	void ExecuteCommand(string command)
	{
		// Splits the input using spaces as delimiters
		vector<string> substrings = ParseCommand(command, " ");

		if (command == "pwd" || command == "cd.")
		{
			virtualFileStructure.PWD();
		}

		else if (command == "cd..")
		{
			virtualFileStructure.MoveToParentDirectory();
		}

		else if (command == "cd\\")
		{
			virtualFileStructure.MoveToRootDirectory();
		}

		else if (substrings[0] == "dir")
		{
			if (substrings.size() == 1)
			{
				virtualFileStructure.DisplayContents();
			}
			else
			{
				cout << "Error: This command does not use any parameter" << endl;
			}
		}

		else if ((substrings[0] == "cd"))
		{
			if (substrings.size() == 2)
			{
				FileStructure::Directory* directory = virtualFileStructure.FindDirectory(substrings[1]);
				if (directory != nullptr)
				{
					virtualFileStructure.ChangeDirectory(directory);
				}
				else
				{
					cout << "Error: No such directory found" << endl;
				}
			}
			else if (substrings.size() > 2)
			{
				cout << "Error: Too many parameters" << endl;
			}
			else
			{
				cout << "Error: This command needs a paramter" << endl;
			}
		}

		else if ((substrings[0] == "mkdir"))
		{
			if (substrings.size() == 2)
			{
				virtualFileStructure.CreateDirectory(substrings[1]);
				cout << "Directory Created: " << substrings[1] << endl;
			}
			else if (substrings.size() > 2)
			{
				cout << "Error: Too many parameters" << endl;
			}
			else
			{
				cout << "Error: This command needs a paramter" << endl;
			}
		}

		else if ((substrings[0] == "create"))
		{
			if (substrings.size() == 2)
			{
				virtualFileStructure.CreateFile(substrings[1]);
				cout << "File Created: " << substrings[1] << endl;
			}
			else if (substrings.size() > 2)
			{
				cout << "Error: Too many parameters" << endl;
			}
			else
			{
				cout << "Error: This command needs a paramter" << endl;
			}
		}

		else if ((substrings[0] == "del"))
		{
			if (substrings.size() == 2)
			{
				bool isDeleted = virtualFileStructure.DeleteFile(substrings[1]);
				if (isDeleted == true)
				{
					cout << "File Deleted: " << substrings[1] << endl;
				}
				else
				{
					cout << "No such file present" << endl;
				}
			}
			else if (substrings.size() > 2)
			{
				cout << "Error: Too many parameters" << endl;
			}
			else
			{
				cout << "Error: This command needs a paramter" << endl;
			}
		}

		else if (command == "exit")
		{
			exit(1);
		}

		else
		{
			cout << "No such command found: \"" << substrings[0] << "\"";
			cout << endl;
		}
	}
};