#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
    DIR* dir;
    struct dirent* ent;
    struct stat sb;
    struct passwd* pwd;
    struct group* grp;
    char* path;
    char date[32];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    path = argv[1];

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return 2;
    }

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_name[0] == '.') {
            continue;
        }

        char* filepath = calloc(strlen(path)+1+strlen(ent->d_name)+1, sizeof(char));
        sprintf(filepath, "%s/%s", path, ent->d_name);
        if (stat(filepath, &sb) == -1) {
            perror("stat");
            continue;
        }

        pwd = getpwuid(sb.st_uid);
        grp = getgrgid(sb.st_gid);
        strftime(date, sizeof(date), "%F %T", localtime(&sb.st_mtime));

        printf("%s – %o %s : %s – %lld – %s\n", ent->d_name, sb.st_mode & 07777, pwd->pw_name, grp->gr_name, (long long) sb.st_size, date);
    }

    closedir(dir);
    return 0;
}
