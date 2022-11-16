#include "Input.h"

void INPUT::Input(const char fatherPath[])
{
	vector <string> dir;
	string sonpath = "input";
	string link = "/";
	string filePath = fatherPath + link + sonpath;
	Capture_i(filePath, dir);
	for (int k = 0; k < dir.size(); ++k)
	{
		vector <string> files;
		filePath = dir[k];
		Capture_i(filePath, files);
		char file[1000] = { '\0' }, input[1000] = { '\0' };
		string in = filePath + "/" + "input.txt";
		strcpy(input, in.c_str());
		FILE* fp = fopen(input, "w");
		if (fp == NULL)
		{
			printf("Open Failed!\n");
			exit(-1);
		}
		fclose(fp);
		strcpy(file, files[0].c_str());
		srand((unsigned)time(NULL));
		for(int i = 0; i < number; ++i)
			Deal_format(file, input);
	}
}

void INPUT::Capture_i(string path, vector<string>& files)
{
    DIR *pDir;
    struct dirent *ptr;
    if (!(pDir = opendir(path.c_str()))) 
	return;
    while ((ptr = readdir(pDir)) != 0) 
	{
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) 
		{
			if (strcmp(ptr->d_name, "stdin_format.txt") == 0 || (!strstr(ptr->d_name, ".cpp") && (!strstr(ptr->d_name, ".txt")) && (!strstr(ptr->d_name, ".o")) && !strstr(ptr->d_name, ".sh")))
            	files.push_back(path + "/" + ptr->d_name);
        }
    }
    closedir(pDir);
}

void INPUT::Deal_format(const char file[], const char in[])
{
	int count = 1;
	FILE* fp;
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		printf("Open Failed!\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		char line[1000];
		int i = 0, temp;
		temp = fscanf(fp, "%s", line);
		char Format[10] = { '\0' }, a[100] = { '\0' }, b[100] = { '\0' };
		for (int j = 0; line[i] != '(' && line[i] != '\0'; ++i, ++j)
			Format[j] = line[i];
		if (line[i] != '\0')
		{
			++i;
			for (int j = 0; line[i] != ','; ++i, ++j)
				a[j] = line[i];
			++i;
			for (int j = 0; line[i] != ')'; ++i, ++j)
				b[j] = line[i];
		}
		int A = 0, B = 0;
		temp = sscanf(a, "%d", &A);
		temp = sscanf(b, "%d", &B);
		Generate_input(in, count, Format, A, B);
		++count;
	}
	fclose(fp);
	fp = fopen(in, "r+");
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "\n");
	fclose(fp);
}

void INPUT::Generate_input(const char in[], int s, char Format[], int A, int B)
{
	FILE* fp;
	fp = fopen(in, "r+");
	if (fp == NULL)
	{
		printf("Open Failed!\n");
		exit(-1);
	}
	fseek(fp, 0, SEEK_END);
	int res1;
	char res2;
	if(s != 1) fprintf(fp, " ");
	if (strcmp(Format, "int") == 0)
	{
		res1 = rand() % (B - A + 1) + A;
		fprintf(fp, "%d", res1);
	}
	else if (strcmp(Format, "char") == 0)
	{
		char flag = (rand() % 2 == 0) ? 'a' : 'A';
		res2 = flag + rand() % 26;
		fprintf(fp, "%c", res2);
	}
	else if (strcmp(Format, "string") == 0)
	{
		int len = rand() % (B - A + 1) + A;
		for (int i = 0; i < len; ++i)
		{
			char temp = (rand() % 2 == 0) ? 'a' : 'A';
			temp += rand() % 26;
			fprintf(fp, "%c", temp);
		}
	}
	fclose(fp);
}