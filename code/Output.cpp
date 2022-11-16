#include "Output.h"

void OUTPUT::Output(const char fatherPath[])
{
	string sonpath = "output";
	string link = "/";
	string filePath = fatherPath + link + sonpath;
	string command;
	command = "mkdir -p " + filePath;
	system(command.c_str());
	string out1 = filePath + "/" + "equal.csv";
	string out2 = filePath + "/" + "inequal.csv";
	char output1[1000] = { '\0' }, output2[1000] = { '\0' };
	strcpy(output1, out1.c_str());
	strcpy(output2, out2.c_str());
	FILE* fp = fopen(output1, "w");
	if (fp == NULL)
	{
		printf("Open Failed!\n");
		exit(-1);
	}
	fclose(fp);
	fp = fp = fopen(output2, "w");
	if (fp == NULL)
	{
		printf("Open Failed!\n");
		exit(-1);
	}
	fclose(fp);
	vector <string> dir;
	sonpath = "input";
	filePath = fatherPath + link + sonpath;
	Capture_o(filePath, dir);
	for (int k = 0; k < dir.size(); ++k)
	{
		vector <string> files;
		filePath = dir[k];
		Capture_o(filePath, files);
		for (int i = 0; i < files.size(); ++i)
			for (int j = i + 1; j < files.size(); ++j)
			{
				char file1[1000] = { '\0' }, file2[1000] = { '\0' };
				strcpy(file1, files[i].c_str());
				strcpy(file2, files[j].c_str());
				bool res = Compare(file1, file2);
				Store(fatherPath, file1, file2, res, output1, output2);
			}
	}
}

void OUTPUT::Capture_o(string path, vector<string>& files)
{
    DIR *pDir;
    struct dirent *ptr;
    if (!(pDir = opendir(path.c_str()))) 
	return;
    while ((ptr = readdir(pDir)) != 0) 
	{
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) 
		{
			if (strcmp(ptr->d_name, "input.txt") != 0 && strcmp(ptr->d_name, "stdin_format.txt") != 0)
					if (strstr(ptr->d_name, ".txt") || (!strstr(ptr->d_name, ".cpp") && !strstr(ptr->d_name, ".o") && !strstr(ptr->d_name, ".sh")))
            			files.push_back(path + "/" + ptr->d_name);
        }
    }
    closedir(pDir);
}

bool OUTPUT::Compare(const char file1[], const char file2[])
{
	string ans1, ans2;
	char c;
	FILE* fp1 = freopen(file1, "r", stdin);
	while (scanf("%c", &c) != EOF) ans1 += c;
	fclose(stdin);
	FILE* fp2 = freopen(file2, "r", stdin);
	while (scanf("%c", &c) != EOF) ans2 += c;
	fclose(stdin);
	if (ans1.size() != ans2.size()) 
		return false;
	for (int i = 0; i < ans1.size(); ++i)
		if (ans1[i] != ans2[i]) return false;
	return true;
}

void OUTPUT::Store(const char fatherPath[], char file1[], char file2[], bool res, const char equal[], const char inequal[])
{
	FILE* fp;
	if (res == true)
		fp = fopen(equal, "r+");
	else
		fp = fopen(inequal, "r+");
	fseek(fp, 0, SEEK_END);
	char f1[1000] = { '\0' }, f2[1000] = { '\0' };
	string link = "/";
	string ftp = fatherPath + link;
	int k = 0;
	for (int i = ftp.size(); file1[i] != '\0'; ++i, ++k)
		f1[k] = file1[i];
	if (k > 3)
	{f1[k - 1] = 'p'; f1[k - 2] = 'p'; f1[k - 3] = 'c';}
	k = 0;
	for (int i = ftp.size(); file2[i] != '\0'; ++i, ++k)
		f2[k] = file2[i];
	if (k > 3)
	{f2[k - 1] = 'p'; f2[k - 2] = 'p'; f2[k - 3] = 'c';}
	fprintf(fp, "%s,%s,\n", f1, f2);
	fclose(fp);
}
