#include <stdio.h>
#include <dirent.h>
#include <string.h>
//orange fluo:\033[1;38;2;255;110;0m
//green fluo:\033[1;38;2;57;255;20m
//purple fluo:\033[1;38;2;180;40;255m
//reset color:\033[0m
//last line:\xE2\x94\x94
//last line long:\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80
//intermediate line:\xE2\x94\x9C
//intermediate line long:\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80

void print_file(const char *name, int is_dir, const char *prefix, int is_last){
    
    if(is_dir){
        if(prefix[0] == '\0'){
            if(is_last){
                printf("\033[1;38;2;57;255;20m\xE2\x94\x94\033[0m\033[1;38;2;180;40;255m%s\033[0m\n", name);
            }
            else{
                printf("\033[1;38;2;57;255;20m\xE2\x94\x9C\033[0m\033[1;38;2;180;40;255m%s\033[0m\n", name);
            }
        }
        else if(is_last){
            printf("\033[1;38;2;57;255;20m%s\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80\033[0m\033[1;38;2;180;40;255m%s\033[0m\n", prefix, name);

        }
        else{
            printf("\033[1;38;2;57;255;20m%s\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80\033[0m\033[1;38;2;180;40;255m%s\033[0m\n", prefix, name);
        }
    } 
    else{
        if(prefix[0] == '\0'){
            if(is_last){
                printf("\033[1;38;2;57;255;20m\xE2\x94\x94\033[0m\033[1;38;2;255;110;0m%s\033[0m\n", name);
            }
            else{
                printf("\033[1;38;2;57;255;20m\xE2\x94\x9C\033[0m\033[1;38;2;255;110;0m%s\033[0m\n", name);
            }
            
        }
        else if(is_last){
            printf("\033[1;38;2;57;255;20m%s\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80\033[0m\033[1;38;2;255;110;0m%s\033[0m\n", prefix, name);
        }
        else{
            printf("\033[1;38;2;57;255;20m%s\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80\033[0m\033[1;38;2;255;110;0m%s\033[0m\n", prefix, name);
        }
    }
}

int count(struct dirent *dp, DIR *dir){
    int total = 0;
     while((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..")!= 0)total++;
     }
     return total;
}

int walk(const char *path, const char *prefix){
    DIR *dir = opendir(path);
    if(!dir){
        perror("opendir");
        return 1;
    }
    struct dirent * dp;

    int counter = 0;
    dp = readdir(dir);
    if(dp == NULL) return 0;
    int count_file = count(dp, dir);
    rewinddir(dir);

    while((dp = readdir(dir)) != NULL){
        const char *name = dp->d_name;
      
        if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;
        
        counter++;
        int is_last = (counter == count_file);
        
        if(dp->d_type == DT_DIR){
            
            size_t len_new_prefix = strlen(prefix) + 4;
            char new_prefix[len_new_prefix];
            
            if(!is_last){
                snprintf(new_prefix, len_new_prefix, "%s\xE2\x94\x82  ", prefix);
            }
            else{
                snprintf(new_prefix, len_new_prefix, "%s   ", prefix);
            }
            
            print_file(name, 1, prefix, is_last);

            size_t len = strlen(path) + strlen(name) + 2;
            char sub_path[len];
            snprintf(sub_path, len, "%s/%s", path, name);
            walk(sub_path, new_prefix);
        }
        else{
            print_file(name, 0, prefix, is_last);
        }
    }
    closedir(dir);
    return 0;
}

int main(int argc, char **argv){
    const char *path = ".";
    const char *prefix = "";

    if (argc > 1){
        path = argv[1];
    }
    
    int err = walk(path, prefix);
        
    return err;
}