
#include <stdio.h>

int main() {
    if (remove(filename) == 0) {
        printf("파일이 성공적으로 삭제되었습니다.\n");
    } else {
        printf("파일 삭제에 실패하였습니다.\n");
    }

    return 0;
}

