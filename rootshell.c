//
//  main.c
//  rootshell
//
//  Created by huke on 10/29/16.
//  Copyright (c) 2016 com.cocoahuke. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[], const char *envp[]) {
    
    uint32_t envp_count = 0;
    int32_t envp_ins = -1;
    const char **env = envp;
    while(*env){
        if(!strcmp(*env, "PS1"))
            envp_ins = envp_count;
        envp_count++, env++;
    }
    
    void *envp_copy = malloc((envp_count + ((envp_ins!=-1)?1:2)) * sizeof(envp[0]));
    bzero(envp_copy, (envp_count + ((envp_ins!=-1)?1:2)) * sizeof(envp[0]));
    memcpy(envp_copy, envp, (envp_count+1) * sizeof(envp[0]));
    
    if(envp_ins != -1)
        ((typeof(envp))envp_copy)[envp_ins] = "PS1=rootshell-3.2# ";
    else
        ((typeof(envp))envp_copy)[envp_count++] = "PS1=rootshell-3.2# ";
    
    setuid(0);
    if(argc==1){
        envp_copy = realloc(envp_copy, (envp_count + 2 + 1) * sizeof(envp[0]));
        memmove(envp_copy + sizeof(envp[0]), envp_copy, envp_count * sizeof(envp[0]));
        ((typeof(envp))envp_copy)[0] = "/usr/bin/sudo";
        ((typeof(envp))envp_copy)[envp_count+1] = "/bin/bash";
        ((typeof(envp))envp_copy)[envp_count+2] = NULL;
        
        execv("/usr/bin/sudo", envp_copy);
    }
    else{
        envp_copy = realloc(envp_copy, (envp_count + argc + 1) * sizeof(envp[0]));
        memmove(envp_copy + sizeof(envp[0]), envp_copy, envp_count * sizeof(envp[0]));
        ((typeof(envp))envp_copy)[0] = "/usr/bin/sudo";
        memcpy(&((typeof(envp))envp_copy)[envp_count+1], &argv[1], (argc-1)*sizeof(envp[0]));
        ((typeof(envp))envp_copy)[envp_count + argc] = NULL;
        
        execv("/usr/bin/sudo", envp_copy);
    }
    return 0;
}
