#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char **argv)
{
    int mode;
    int mode_u;
    int mode_g;
    int mode_o;
    int i;
    char *path;

    if(argc < 3)
    {
        printf("%s <mode num> <target file1> <target file2> ...\n",argv[0]);
        exit(0);
    }

    mode = atoi(argv[1]);

    if(mode > 777 || mode < 0)
    {
        printf("mode num error!\n");
        exit(0);
    }

    mode_u = mode / 100;
    mode_g = (mode % 100) / 10;
    mode_o = mode % 10;
    mode = mode_u * 8 * 8 + mode_g * 8 + mode_o;

    for(i = 2; i < argc; i++)
    {
        path = argv[i];
        if(chmod(path,mode) == -1)
        {
            printf("chmod error!\n");
            exit(1);
        }
    }

    return 0;
}
