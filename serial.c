#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/wait.h>
using namespace std;

int main()
{
	ifstream url_file;
	url_file.open("urls.txt");
	int count=0;
	string temp;

	while (getline(url_file, temp))
		count++;
	cout << count << endl;
	url_file.close();
	string* urls = new string[count];
	count = 0;
	
	url_file.open("urls.txt");
	while (getline(url_file, temp))
		urls[count++] = temp;	

	url_file.close();
	pid_t pid;
	int status=0;	
	int n=0;
	while (n < count)
	{
		pid = fork();
		if (pid < 0) perror("fork error!");
		else if (pid==0)
		{
			execlp("wget","wget", urls[n].c_str(), NULL);
			_exit(1);
		}
		else
		{
			cout << "waiting.." << endl;
			wait(&status);
			n++;
		}
	}

	delete[] urls;
	return 0;

}
