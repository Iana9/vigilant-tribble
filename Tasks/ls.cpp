#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <iomanip>


static const char* humanSize(uint64_t bytes)
{
	std::vector<const char*> suffix = {"B", "K", "M", "G", "T"};
	char length = sizeof(suffix) / sizeof(suffix[0]);

	int i = 0;
	double dblBytes = bytes;

	if (bytes > 1024) {
		for (i = 0; (bytes / 1024) > 0 && i<length-1; i++, bytes /= 1024)
			dblBytes = bytes / 1024.0;
	}

	static char output[200];
	sprintf(output, "%.01lf%s", dblBytes, suffix[i]);
	return output;
}


void print_information(const std::string filename, const struct stat& fileStat, const bool arg, const bool arg_l, const bool arg_h) {
    if (arg_l) {

        std::string permission = "----------";
        if (S_ISDIR(fileStat.st_mode)) permission[0] = 'd';
        if (fileStat.st_mode & S_IRUSR) permission[1] = 'r'; 
        if (fileStat.st_mode & S_IWUSR) permission[2] = 'w'; 
        if (fileStat.st_mode & S_IXUSR) permission[3] = 'x'; 
        if (fileStat.st_mode & S_IRGRP) permission[4] = 'r';
        if (fileStat.st_mode & S_IWGRP) permission[5] = 'w'; 
        if (fileStat.st_mode & S_IXGRP) permission[6] = 'x'; 
        if (fileStat.st_mode & S_IROTH) permission[7] = 'r'; 
        if (fileStat.st_mode & S_IWOTH) permission[8] = 'w'; 
        if (fileStat.st_mode & S_IXOTH) permission[9] = 'x'; 

        struct passwd* pwd;
        pwd = getpwuid(fileStat.st_uid);

        struct group* grp;
        grp = getgrgid(fileStat.st_gid);

        uint64_t size = fileStat.st_size;
        std::string timeStr = ctime(&fileStat.st_mtime);
        timeStr.erase(timeStr.find('\n'));

        std::cout << std::left << std::setw(12) << permission
                << std::setw(10) << pwd->pw_name
                << std::setw(10) << grp->gr_name
                << std::setw(10) << ((arg_h) ? humanSize(size) : std::to_string(size).c_str())
                << timeStr << " ";
    } 
    std::cout << filename << "\n";
    
};

int main(int argc, char** argv) {
    int opt;
    bool arg_l = false;
    bool arg_r = true;
    bool arg_h = false;
    
    while ( (opt = getopt(argc, argv, "lrh")) != -1 ) {

            switch ( opt ) {
                case 'l': {
                    arg_l = true;
                    break;
                    }
                case 'r': {
                    arg_r = true;
                    break;
                    }
                case 'h': {
                    arg_h = true;
                    break;
                    }
                case '?':
                {
                    std::cerr << "Got unknown option. " << strerror(errno) << std::endl;
                    break;
                }
            }
    }

    DIR *directory;
    const char *dirPath;

    if (optind < argc) {
        dirPath = argv[optind]; 
    } else {
        dirPath = "."; 
    }

    struct stat sb;

    directory = opendir(dirPath);
    std::vector<std::string> files;
    
    if (directory != NULL) {
        struct dirent *ent;
        while ((ent = readdir(directory)) != NULL) {
            files.push_back(std::string(ent->d_name));
        }
        closedir(directory); 
    } else {
        std::cerr << "Error opening directory: " << strerror(errno) << std::endl;
        return EXIT_FAILURE; 
    }

    std::sort(files.begin(), files.end(), [arg_r](std::string f1, std::string f2) { 
        if (arg_r) {
            return f1 > f2;
        } else 
        {   return f1 < f2; }
        });

    for (std::string f : files) {
        std::string fullPath = std::string(dirPath) + "/" + std::string(f);
        if (stat(fullPath.c_str(), &sb) < 0) {
            std::cerr << "Error getting file status: " << strerror(errno) << std::endl;
            return EXIT_FAILURE;
            }
        else {
        print_information(f, sb, arg_l | arg_h, arg_l, arg_h);
        }
    }

    return EXIT_SUCCESS;
}
