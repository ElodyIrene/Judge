#include "Input.h"
#include "Execute.h"
#include "Output.h"

int main()
{
	char path[1000];
	getcwd(path, 1000);
	INPUT in;
	EXECUTE exe;
	OUTPUT out;
	in.Input(path);
	exe.Execute(path);
	out.Output(path);
	return 0;
}
