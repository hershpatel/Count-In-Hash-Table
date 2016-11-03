//
//  count.c
//  Assignment2
//
//  Created by Hersh Patel on 10/8/16.
//  Copyright © 2016 Hersh Patel. All rights reserved.
//

#include "count.h"

int main(int argc, char const *argv[]) {
	//checks if input is empty
	if(argc!=2) {
		printf("error\n");
		return 0;
	}
	
	//opens the file and checks if it exists
	FILE *f = fopen(argv[1], "r");
	if(f==NULL) {
		printf("error\n");
		return 0;
	}
	
	//checks if file is empty
	FILE *g = fopen(argv[1], "r");
	fseek(g, 0, SEEK_END);
	long a=ftell(g);
	if(a==0) {
		printf("0\n");
		fclose(g);
		return 0;
	}
	fclose(g);
	
	//inserts numbers into hash table
	char line[20];
	createHash();
	while(fgets(line,sizeof(line),f)) {
		if (filecheck(line)==0) continue;
		long int num=strtol(line, NULL, 0);
		insert(num);
	}
	fclose(f);
	free(table);
	printf("%d\n", size);
	return 0;
}
