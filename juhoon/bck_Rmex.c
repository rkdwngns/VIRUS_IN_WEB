#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void removeExtension(const char *path) {
    char newpath[1024];
    strcpy(newpath, path);
    char *ext = strrchr(newpath, '.');

    if (ext != NULL) {
        *ext = '\0';
        if (rename(path, newpath) == 0) {
            printf("확장자가 제거된 파일: %s\n", newpath);
        } else {
            printf("파일 이름 변경에 실패하였습니다.\n");
        }
    }
}

void exploreDirectory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    if ((dir = opendir(path)) == NULL) {
        printf("디렉토리를 열 수 없습니다.\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char newPath[1024];
        snprintf(newPath, sizeof(newPath), "%s\\%s", path, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (stat(newPath, &fileStat) == -1) {
            printf("파일 정보를 가져올 수 없습니다.\n");
            continue;
        }

        if (S_ISDIR(fileStat.st_mode)) {
            exploreDirectory(newPath); // 디렉토리인 경우 재귀적으로 탐색
        }

        removeExtension(newPath); // 파일이나 디렉토리의 확장자 제거
    }

    closedir(dir);
}

int main() {
    const char *directoryPath = "C:\\";

    exploreDirectory(directoryPath);

    return 0;
}
