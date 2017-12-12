#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ConfigParser.h"

int config_get_int(char *search_section, char *search_key){
	int i;
	for(i=0; i<num; i++){
		if (!strcmp(search_section, section[i]) && !strcmp(search_key, key[i])){
			return atoi(params[i]);
		}
	}
	printf("There is no such combination of section (%s) and key(%s).\n",search_section,search_key);
	exit(1);
}

float config_get_float(char *search_section, char *search_key){
	int i;
	for(i=0; i<num; i++){
		if (!strcmp(search_section, section[i]) && !strcmp(search_key, key[i])){
			return atof(params[i]);
		}
	}
	printf("There is no such combination of section (%s) and key(%s).\n",search_section,search_key);
	exit(1);
}

char *config_get_string(char *search_section, char *search_key){
	int i;
	for(i=0; i<num; i++){
		if (!strcmp(search_section, section[i]) && !strcmp(search_key, key[i])){
			return params[i];
		}
	}
	printf("There is no such combination of section (%s) and key(%s).\n",search_section,search_key);
	exit(1);
}

int *config_get_intarr(char *search_section, char *search_key, int *ssize){
	int i,j;
	int size=0;
	for(i=0; i<num; i++){
		if (!strcmp(search_section, section[i]) && !strcmp(search_key, key[i])){
			char *token = strtok(params[i], " ,\n");
			int *arr = malloc(sizeof(int));
			while(token){
				if (arr==NULL){
					printf("Failed while allocating memory for int array\n");
					exit(1);
				}
				arr[size] = atoi(token);
				token = strtok(NULL, " ,\n");
				size++;
				arr = realloc(arr, (size+1)*sizeof(int));
			}
			*ssize = size;
			return arr;
		}
	}
	printf("There is no such combination of section (%s) and key (%s).\n",search_section,search_key);
	exit(1);
}

void read_config(char *filename){
	FILE *fp = fopen(filename,"r");
	if (fp==NULL){
		printf("%s cannot be opened.\n",filename);
		exit(1);
	}
	char * line = NULL;
	char * temp_section = malloc(1024 * sizeof(char));;
	char * temp_key = NULL;
	char * temp_params = NULL;
	ssize_t lread;
	size_t len = 0;
	num=0;
	
	section = malloc(sizeof(*section));
	key = malloc(sizeof(*key));
	params = malloc(sizeof(*params));
	section[num] = malloc(1024 * sizeof(char));
	key[num] = malloc(1024 * sizeof(char));
	params[num] = malloc(1024 * sizeof(char));
	
    while ((lread = getline(&line, &len, fp)) != -1) {
        if (!strncmp(line,"[",1)){
        	strcpy(temp_section,line);
			temp_section++;
			temp_section[strlen(temp_section)-2]=0;
        }
		if (strchr(line,'=') && strncmp(line,"#",1)){
			char *token = strtok(line, " =\n");
			temp_key = token;
			token = strtok(NULL, " =\n");
			temp_params = token;
			strcpy(section[num],temp_section);
			strcpy(key[num],temp_key);
			strcpy(params[num],temp_params);
			num++;
			section = realloc(section, (num+1)*sizeof(*section));
			key = realloc(key, (num+1)*sizeof(*key));
			params = realloc(params, (num+1)*sizeof(*params));
			section[num] = malloc(1024 * sizeof(char));
			key[num] = malloc(1024 * sizeof(char));
			params[num] = malloc(1024 * sizeof(char));
		}
    }

}