#include "pipex.h"




int main(int argc,char *argv[],char **envp)
{
	int fd[2];
		if (pipe(fd) == -1)
			error_msg("pipe");
    return (0);
}
