#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void search_in_directory(const char *dir, const char *filename) {
	struct dirent *entry;
	DIR *dp = opendir(dir);

	if (dp == NULL) {
		perror("opendir");
		return;
	}

	while ((entry = readdir(dp))) {
		if (strcmp(entry->d_name, filename) == 0) {
			printf("Found: %s/%s\n", dir, filename);
		}
	}

	closedir(dp);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "PATH environment variable not set.\n");
        return 1;
    }

    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        perror("strdup");
        return 1;
    }

    // Add your code here to use path_copy

    free(path_copy);
    return 0;
}