#pragma once

template <typename T>

class Shell
{
	struct File
	{

	};
	struct Directory
	{
		vector<Directory> dirs;
		vector<File> files;
	};
	struct FileStructure
	{
		struct Node
		{
			T data;
			vector<Node*> 
		};
	};
private:
	Node* root;
	Shell()
	{

	}
};