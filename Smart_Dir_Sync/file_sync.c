#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_PATH 1024

void argument_varification(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_directory> <destination_directory>\n", argv[0]);
        exit(1);
    }

    if (access(argv[1], F_OK) == -1) {
        fprintf(stderr, "Error: Source directory '%s' does not exist.\n", argv[1]);
        exit(1);
    }

    if (access(argv[2], F_OK) == -1) {
        if (mkdir(argv[2], 0755) != 0) {
            fprintf(stderr, "Error: Cannot create destination directory '%s'.\n", argv[2]);
            exit(1);
        }
        printf("Created destination directory '%s'.\n", argv[2]);
    }
}

void initialize(int argc, char *argv[]) {
    char path[MAX_PATH];
    if (getcwd(path, MAX_PATH) == NULL) {
        perror("Error: Cannot get current working directory");
        exit(1);
    }
    printf("Current working directory: %s\n", path);
}

void copy_file(const char* src, const char* dst) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("cp", "cp", "-f", src, dst, NULL);
        perror("cp failed");
        exit(1);
    }
    wait(NULL);
}

int compare_files(const char* src, const char* dst) {
    pid_t pid = fork();
    if (pid == 0) {
        int is_source_newer(const char* src, const char* dst) {
    struct stat src_stat, dst_stat;

    if (stat(src, &src_stat) == -1 || stat(dst, &dst_stat) == -1) {
        perror("stat failed");
        return -1;
    }

    return src_stat.st_mtime > dst_stat.st_mtime;
}
int null_fd = open("/dev/null", O_WRONLY);
dup2(null_fd, STDOUT_FILENO);
close(null_fd);

        execlp("diff", "diff", src, dst, NULL);
        perror("diff failed");
        exit(1);
    }

    int status;
    wait(&status);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}

int is_source_newer(const char* src, const char* dst) {
    struct stat src_stat, dst_stat;

    if (stat(src, &src_stat) == -1 || stat(dst, &dst_stat) == -1) {
        perror("stat failed");
        return -1;
    }

    return src_stat.st_mtime > dst_stat.st_mtime;
}

void handle_file_sync(const char* src_dir, const char* filename, const char* dst) {
    char src_file[MAX_PATH];
    strcpy(src_file, src_dir);
    strcat(src_file, "/");
    strcat(src_file, filename);

    char dst_file[MAX_PATH];
    strcpy(dst_file, dst);
    strcat(dst_file, "/");
    strcat(dst_file, filename);

    if (access(dst_file, F_OK) == -1) {
        copy_file(src_file, dst_file);
        printf("New file found: %s\n", filename);
        return;
    }

    int diff_result = compare_files(src_file, dst_file);

    if (diff_result == 0) {
        printf("File %s is identical. Skipping...\n", filename);
    } else if (diff_result == 1) {
        int newer = is_source_newer(src_file, dst_file);
        if (newer == -1) return;

        if (newer) {
            copy_file(src_file, dst_file);
            printf("File %s is newer in source. Updating...\n", filename);
        } else {
            printf("File %s is newer in destination. Skipping...\n", filename);
        }
    } else {
        printf("Error: diff failed on file %s\n", filename);
    }
}

void file_sync(char *src, char *dst) {
    DIR *dir = opendir(src);
    if (!dir) {
        perror("Cannot open source directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type != DT_REG)
            continue;

        handle_file_sync(src, entry->d_name, dst);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    argument_varification(argc, argv);
    initialize(argc, argv);
    file_sync(argv[1], argv[2]);
    return 0;
}
