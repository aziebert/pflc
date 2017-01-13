#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main (int argc, char *argv[]){

int i=0;
int file=0;
int format=0;
int frame=1;
double frametime=0;
double avgframetime=0;
char line[255];
char filename[255];
char write[30];
char *word;
char *test;
FILE *sFile;
FILE *dFile;

// check if a filename was given as argument
if(argv[1]!=NULL){file=1;}
else{printf("No file was loaded...\n");}


// check if the file is in the right format
if (file==1){
	sFile=fopen(argv[1],"r");
	if(fgets(line,sizeof line,sFile) != NULL){
		word=strtok(line,",");
		for(i=0;i<10;i++){ word=strtok(NULL,","); }
		if (strcmp(word,"MsBetweenPresents")==0){format=1;}
		else{printf("This is not a Presentmon log...\n");}
		}
}


//if the file is in the correct format, start processing
if(file==1&format==1){	
	
	printf("\nPresentmon to Fraps Log Converter v0.8 BETA by Alexandre Ziebert\n\n");
	printf("Reading File: %s\n",argv[1]);
		
	test=strncpy(filename,argv[1],(strlen(argv[1])-4));
	
	test=strcat(filename,"_fraps.csv");
	dFile=fopen(filename,"w");	
	
	printf ("Writing file: %s\n\n",filename);
	//printf("Frame, Time (ms)\n");
	fprintf(dFile,"Frame, Time (ms)\n");
	
	while (fgets(line,sizeof line,sFile)	!= NULL){
		word=strtok(line,",");
		for(i=0;i<9;i++){word=strtok(NULL,",");}
		frametime=(strtof(word,NULL)*1000);
		avgframetime=avgframetime+frametime;
//		printf("%5d, %9.3f\n",frame,frametime);
		fprintf(dFile,"%5d, %9.3f\n",frame,frametime);
		frame++;
	}
	fclose(dFile);
	fclose(sFile);
	
	printf("Done!\n\n");
	
}


system("pause");

}

