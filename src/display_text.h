/*
 ============================================================================
 Name        : display_text.h
 Author      : Jie Liu
 Version     : 1.0 (header file)
 Copyright   : Jie Liu, Lehigh University
 Maintenance : Jie Liu, jie.liu@lehigh.edu
 Created on  : Sep 9, 2015
 ============================================================================
 Description : This is a header file that includes the display functions
   for fmt commands. Fucntions available are (1) function displaying
   contents in an input file with specified width and uniform
   spacing; (2) funtion displaying help information; (3) function
   displaying version information
 ============================================================================
 */


// include all necessary libraries
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#ifndef DISPLAY_TEXT_H_
#define DISPLAY_TEXT_H_

// define some useful macros: limits for line width and word width
#define MAXLINE 10000
#define MAXWORD 1000

/* function to display the input file with a specified width and uniform spacing */
void display_setwidth(const char *filename, const int width, const int u)
{
	/* check if formatting width exceeds MAXLINE */
	if (width>MAXLINE){
		perror("Value for the option width '-w' exceeds 10000, the maximum number that can be set!");
	}

	/* declare and initial necessary variables */
	FILE *file;
	char c = '\0', d= '\0', line[MAXLINE+2], word[MAXWORD+2];
	int line_pos = 0, word_pos = 0, word_pos_prev = 0, status = 0;    // line position pointer and word position pointer


	file = fopen(filename,"rb");     // open input file
	// check if the input file exists
	if (file==NULL) perror ("Error opening file: this file does not exist!");

	/* loops over characters to check and format required file */
	while (1) {
		d = c;
		c = getc(file);

		/* check if we do uniform spacing */
		if(u){
			/* double spaces between sentences: after . ? !*/
			if(d=='.' || d=='!' || d=='?'){
				line[line_pos++] = ' ';
				line[line_pos++] = ' ';
				word_pos = 0;
				d = ' ';
			}

			/* single space between different words: remove redundant whitespaces*/
			if(isspace(d) && isspace(c)){
				if (d=='\n' && c=='\n'){
					word_pos = 0;
					line[line_pos] = '\0';
					printf("%s\n\n",line);
					line_pos = word_pos;
					continue;
				}

				continue;}
		}


		/* check if reach the end of the file */
		if (c == EOF) {
			if (line_pos > 0) {
				line[line_pos] = '\0';
				printf("%s\n", line);
			}
			break;
		}



		//		if (c == '\r') // control for carriage return
		//			continue;
		/* replace original newline operator with a whitespace;
		 * if comes with two \n, then it is paragraph, so we keep the two \n */
		if (c == '\n') {
			if(!status){
				c = ' ';
			}
			else{
				word_pos = 0;
				line[line_pos] = '\0';
				printf("%s\n\n",line);
				line_pos = word_pos;
				continue;
			}
			status = 1;
		}else{
			status = 0;
		}



		/* remove spaces at the beginning of each line */
		if(!line_pos && isspace(c)){
			continue;
		}






		/* update word pointer position to 0 if there is a whitespace
		 * (starting a new word */
		if (isspace(c)){
			word_pos_prev = word_pos;
			word_pos = 0;
			/* model the case where word length >= width print the word as whole
			 * line in this case */
			if((word_pos_prev >= width)&&(word_pos_prev==line_pos)){
				line[line_pos] = '\0';
				printf("%s\n",line);
				line_pos = word_pos;
				continue;
			}
		}else{
			/* update character in a currently working word if c is non-whitespace */
			word[word_pos++] = c;
		}

		/* update character in a currently working line position */
		line[line_pos++] = c;

		/* check if word length exceeds maximum word length allowed */
		if (word_pos > MAXWORD) {
			word[word_pos] = '\0';
			printf("ERROR: \"%s\" exceeds maximum word length (%d)\n",
					word, MAXWORD);
			break;
		}

		/* check if the line is filled up with width when line has more than one word */
		if ((line_pos > width) &&(line_pos > word_pos)) {
			line_pos -= word_pos;
			while (isspace(line[--line_pos]) && line[line_pos] != '\n');
			/* terminate the line and print this line out
			 * when it is filled up with specific width */
			line[line_pos+1] = '\0';
			printf("%s\n", line);
			/* update excessive word to a newline when the line is filled up with width */
			strncpy(line, word, word_pos+1);
			/* reset the position for a new line */
			line_pos = word_pos;
		}
	}

	fclose(file);     // close input file

}


/* display help information: how to use fmt in command line */
void display_help(void)
{
	printf( "\nUsage: fmt [OPTION]... [FILE]...\n"
			"Reformat each paragraph in the FILE(s), printing out results.\n"
			"Mandatory arguments to long options are mandatory for short options too.\n"
			"  -u, --uniform-spacing     one space between words, two after sentences\n"
			"  -w, --width=WIDTH         maximum line width (default of 75 columns)\n"
			"      --help     display this help documentation.\n"
			"      --version  output version information.\n"
			"The largest value for -w to be set is 10000. \n"
			"Note also that the largest number of characters in a word is 1000.\n"
			"With no FILE, print error message indicating that input does not exist.\n"
			"Report fmt bugs to jie.liu@lehigh.edu\n"
			"For complete documentation, please refer to readme.md.\n\n");
}

/* display version information of fmt */
void display_version(void)
{
	printf( "\nfmt 1.0 written in C\n"
				"Copyright (C) 2015 Jie Liu, Lehigh University.\n"
				"License: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n"
				"This is free software: you are free to change and redistribute it.\n"
				"There is NO WARRANTY, to the extent permitted by law.\n"
				"Written by Jie Liu.\n\n");
}




#endif /* DISPLAY_TEXT_H_ */
