#include "builtin_cmds.h"

//use coding algorithm from the book to have an equal distribution
//p.18
//8-bit: 2^8 to give 0-255 
/*
#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)
unsigned long oaat_code(char *key, unsigned long len, unsigned long bits) {
unsigned long hash, i;
for (hash = 0, i = 0; i < len; i++) {
hash += key[i];
hash += (hash << 10);
hash ^= (hash >> 6);
}
hash += (hash << 3);
hash ^= (hash >> 11);
hash += (hash << 15);
return hash & hashmask(bits);
}
*/

// int code(const char *string)
// {
//     int str_len = strlen(string);
//     int sum = 0;
     
//     for(int i = 0; i < str_len; i++)
//     {
//         sum += string[i];
//     }

//     return sum % SIZE;
// }


//check if string is in built-in function
int is_builtin(char *string){
    
}


void run_command(const char *cmd){
    
}




//echo --> print to screen... printf

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//>echo $USER 
//hanna

// void run_echo(const char *string)
//    {
//         printf("%s\n", string);
//     } 


/*
env --> prints environment
echo $HOME ...
if echo and $ then pass in HOME


int env(const char *var_str){
    if
}

*/






//cd --> chdir fn
int run_cd(const char *path){
    if(chdir(path) == 0){
        return 0;
    }
    else{
        perror("cd: no such file or directory: %s", path);
    }
    return -1;
}

//getenv???

//setenv --> set environment
//export MY_VARIABLE = "my_value"
//need to parse string

//pass entire string through with export keyword and parse so that capture variable until space 
//or '=' and then with "" capture what is inside


//int setenv(const char *envname, const char *envval, int overwrite);
//    returns 0/-1
int run_export(const char *var_str){
    int setenv(env_name, var_str, ???)
}


//unsetenv --> unsets environment
//    returns 0/-1
//unset MY_VARIABLE
//int unsetenv(const char *name);





//exit --> closes terminal... kill

//pwd --> should be getcwd & printf

//which --> needs to find $PATH location... not sure
//how to build appropriately yet


void no_command(const char *com_string){
    printf("zsh: command not found: %s", com_string);
}