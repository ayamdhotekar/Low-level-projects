#include <stdio.h>
#include <stdlib.h>
#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_or_dir>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_EVTONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    int kq = kqueue();
    if (kq < 0) {
        perror("kqueue");
        return 1;
    }

    struct kevent change;
    EV_SET(&change, fd, EVFILT_VNODE,
           EV_ADD | EV_ENABLE | EV_CLEAR,
           NOTE_WRITE | NOTE_DELETE | NOTE_RENAME,
           0, NULL);

    struct kevent event;

    printf("Watching %s...\n", argv[1]);

    while (1) {
        int nev = kevent(kq, &change, 1, &event, 1, NULL);
        if (nev < 0) {
            perror("kevent");
            break;
        }

        if (event.fflags & NOTE_WRITE)
            printf("File modified\n");

        if (event.fflags & NOTE_DELETE)
            printf("File deleted\n");

        if (event.fflags & NOTE_RENAME)
            printf("File renamed\n");
    }

    close(fd);
    return 0;
}
