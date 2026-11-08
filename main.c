/* This file uses some code from the nxdk samples for SDL and winapi */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <nxdk/mount.h>
#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"

#define MAX_XBE_COUNT   ( 10 )
#define MAX_XBE_LENGTH  ( 200 )

char namearray[MAX_XBE_COUNT][MAX_XBE_LENGTH];
char listbuffer[100];
char selectbuffer[50];
char path[255];
int target_xbe = 0;
char ascii_title[41];
char ascii_region[30];
bool choicefilefound = false;
int dbgflag = 0;

int parse_choicefile(void)
{
    int retval = false;
    FILE *fptr = NULL;
    char buffer[128];
    int len = 0;
    int read = 0;
    int i = 0;
    int num = 0;

    //attempt to open choice txt file
    fptr = fopen("d:\\choice.txt", "r");

    if( NULL != fptr )
    {
        choicefilefound = true;

        while ((fgets(buffer, 128, fptr)) != NULL) 
        {
            if(buffer[0] == '&')
            {
                num = snprintf(&namearray[i][0], (MAX_XBE_LENGTH - 1), "%s", &buffer[1]);
                namearray[i][num-1] = '\0'; //remove '\n'
                i++;
            }
            else if(buffer[0] == '!')
            {
                target_xbe = atoi(&buffer[1]);
            }
            else if(buffer[0] == '*')
            {
                dbgflag = 1;
            }            
            else
            {
                /* Do nothing */
            }
        }
        
        fclose(fptr);

        retval = true;
    }

    return(retval);
}


int main(void)
{
    uint8_t y,j,numchoices;
    uint8_t count = 0U;

    XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);

    //check to see is a choice file exists and parse if it does
    (void)parse_choicefile();
    
    //Create a string of discovered files
    y = 0;
    j = 0;
    numchoices = 0;
    for(y=0; y<10; y++){
        if(namearray[y][0] != '\0'){
            j += sprintf(listbuffer + j, "%d : %s\n", y, &namearray[y][0]);
            numchoices++;
        }
    }

    strcat(path, &namearray[target_xbe][0]);

    if(dbgflag)
    {        
        while(count < 5) {
            debugPrint(path);
            Sleep(2000);
            count++;
        }
        
    }
    
    /* Launch the selected xbe */
    XLaunchXBE(path);
    
    exit(1);
}
