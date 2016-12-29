//
//  main.c
//  rootshell
//
//  Created by huke on 10/29/16.
//  Copyright (c) 2016 com.cocoahuke. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    setuid(0);
    if(argc==1){
        setenv("PS1","rootshell-3.2# ",1);
        char *shargv[]={"/usr/bin/sudo","-E","/bin/sh",NULL};
        execv("/usr/bin/sudo",shargv);
    }
    else{
        char *shargv[argc+2];
        for(int i=0;i<argc;i++){
            shargv[i+1] = (char *)argv[i];
        }
        shargv[0] = "/usr/bin/sudo";
        shargv[1] = "-E";
        shargv[argc+1] = NULL;

        execv("/usr/bin/sudo",shargv);
    }
    return 0;
}
