#include "Execute.h"

void EXECUTE::Execute(const char fatherPath[])
{
    vector <string> dir;
	string sonpath = "input";
	string link = "/";
	string filePath = fatherPath + link + sonpath;
    Capture_e(filePath, dir);
	for (int k = 0; k < dir.size(); ++k)
	{
        vector <string> files;
		filePath = dir[k];
		Capture_e(filePath, files);
        for(int i = 0; i < files.size(); ++i)
        {
            string name;
            Get_name(filePath, files[i], &name);
            string temppath = filePath + link;
            string command = "g++ -o " + temppath + name + ".o " + temppath + name + ".cpp";
            system(command.c_str());
            Write_sh(filePath, name);
            Compile(filePath, name);
        }
    }
}

void EXECUTE::Capture_e(string path, vector<string>& files)
{
    DIR *pDir;
    struct dirent *ptr;
    if (!(pDir = opendir(path.c_str()))) 
	return;
    while ((ptr = readdir(pDir)) != 0) 
	{
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) 
		{
			if (strstr(ptr->d_name, ".cpp"))
            	files.push_back(path + "/" + ptr->d_name);
            else if(!strstr(ptr->d_name, ".cpp") && !strstr(ptr->d_name, ".txt") && !strstr(ptr->d_name, ".o"))
            	files.push_back(path + "/" + ptr->d_name);
        }
    }
    closedir(pDir);
}

void EXECUTE::Get_name(string fatherPath, string file, string* name)
{
    string link = "/";
	string ftp = fatherPath + link;
    char Name[1000] = {'\0'};
    int k = 0;
    for(int i = ftp.size(); file[i] != '\0'; ++i, ++k)
        Name[k] = file[i];
    Name[k - 4] = '\0';
    *name = Name;
}

void EXECUTE::Write_sh(string path, string name)
{
    string link = "/";
    string open = path + link + name + ".o";
    string in = path + link + "input.txt";
    string out = path + link + name + ".txt";
    string shell = path + link + name + ".sh";
    char Shell[1000] = { '\0' };
	strcpy(Shell, shell.c_str());
    FILE* fp = fopen(Shell, "w");
	if (fp == NULL)
	{
		printf("Open Failed!\n");
		exit(-1);
	}
    char Open[1000] = {'\0'}, input[1000] = {'\0'}, output[1000] = {'\0'};
    strcpy(Open, open.c_str());
	strcpy(input, in.c_str());
    strcpy(output, out.c_str());
    fprintf(fp, "#!/bin/bash\n");
    fprintf(fp, "while read line\n");
    fprintf(fp, "do\n");
    fprintf(fp, "	printf \"%%s\" \"$line\" | %s\n", Open);
    fprintf(fp, "	echo\n");
    fprintf(fp, "done < %s  > %s", input, output);
    fclose(fp);
}

void EXECUTE::Compile(string path, string name)
{
    /*string link = "/";
    string open = path + link + name + ".sh";
    string in = path + link + "input.txt";
    string out = path + link + name + ".txt";
    string command = open + " < " + in + " > " + out;
    system(command.c_str());*/
    string link = "/";
    string open = path + link + name + ".sh";
    string command = "chmod +x " + open;
    system(command.c_str());
    command = open;
    system(command.c_str());
}