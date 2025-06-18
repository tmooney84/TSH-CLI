

int main(void){
//type_prompt();
//read_command(command, parameter);

if (is_builtin(command)) {
    handle_builtin(command, args);
} else {
    pid_t pid = fork();
    if (pid == 0) {
        // child process
        execvp(command, args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        // parent process
        waitpid(pid, NULL, 0);
    }
}
}

