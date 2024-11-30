#include"pctl2.h"

int main(int argc, char *argv[]) {
    int i;
    pid_t pid_ls, pid_ps; // 存放子进程号
    int status_ls, status_ps;
    char *args_ls[] = {"/bin/ls", "-a", NULL}; // 子进程要执行的ls命令
    char *args_ps[] = {"/bin/ps", "-l", NULL}; // 子进程要执行的ps命令
    
    signal(SIGINT, sigcat); // 注册一个本进程处理键盘中断的函数

    // 设置循环终止条件，例如循环10次
    for (i = 0; i < 10; i++) {
        // 创建第一个子进程，执行ls命令
        pid_ls = fork();
        if (pid_ls < 0) {
            printf("Create first child process fail!\n");
            exit(EXIT_FAILURE);
        }
        if (pid_ls == 0) { // 第一个子进程执行代码段
            printf("I am first child process (ls) %d, My father is %d\n", getpid(), getppid());
	    sleep(1);
            for (i = 0; args_ls[i] != NULL; i++)
                printf("%s ", args_ls[i]); printf("\n");
            execve(args_ls[0], args_ls, NULL); // 执行完后不会回到该调用进程
            printf("Exec ls failed!\n");
            exit(EXIT_FAILURE);
        }

        // 创建第二个子进程，执行ps命令
        pid_ps = fork();
        if (pid_ps < 0) {
            printf("Create second child process fail!\n");
            exit(EXIT_FAILURE);
        }
        if (pid_ps == 0) { // 第二个子进程执行代码段
            printf("I am second child process (ps) %d, My father is %d\n", getpid(), getppid());
            for (i = 0; args_ps[i] != NULL; i++)
                printf("%s ", args_ps[i]); printf("\n");
            execve(args_ps[0], args_ps, NULL);
            printf("Exec ps failed!\n");
            exit(EXIT_FAILURE);
        }

        // 等待执行ps命令的子进程结束
        printf("\nI am Parent process %d, I am waiting for ps child process %d done.\n", getpid(), pid_ps);
        waitpid(pid_ps, &status_ps, 0);
        if (WIFEXITED(status_ps)) {
            printf("PS command executed.\n");
        } else {
            printf("The ps child is done abnormally.\n");
        }

        // 等待执行ls命令的子进程结束
        printf("\nI am Parent process %d, I am waiting for ls child process %d done.\n", getpid(), pid_ls);
        waitpid(pid_ls, &status_ls, 0);
        if (WIFEXITED(status_ls)) {
            printf("LS command executed.\n");
        } else {
            printf("The ls child is done abnormally.\n");
        }

        // 打印信息，表示一轮子进程执行完毕
        printf("%d Round %d done.\n\n", getpid(), i + 1);

        // 暂停3秒
        sleep(3);
    }

    printf("%d All tasks done.\n\n", getpid());
    return EXIT_SUCCESS;
}
