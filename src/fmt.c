/*
 ============================================================================
 Name        : fmt.c
 Author      : Jie Liu
 Version     : 1.0
 Copyright   : Jie Liu, Lehigh University
 Maintenance : Jie Liu, jie.liu@lehigh.edu
 Created on  : Sep 9, 2015
 ============================================================================
 Description : This a program display a target file with specified width and
   uniform spacing.
 ============================================================================
 */


// include all necessary libraries or headers
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "display_text.h"


// structure for command line arguments
struct global_args {
    int unifSpace;                /* -u option : uniform space */
    int width;                    /* -w option : printing width */
    int help;                     /* --help option : help info */
    int version;                  /* --version option : software version info */
    char *filename;               /* input filename */
} arguments;

// option string
static const char *optString = "uw:";

// long options with --
static const struct option longOpts[] = {
    { "uniform-spacing", no_argument, NULL, 'u' },  /* --uniform-spacing option: same as -u */
    { "width", required_argument, NULL, 'w' },      /* --width option: same as -w */
    { "version", no_argument, NULL, 'v' },          /* --version option */
    { "help", no_argument, NULL, 'h' },             /* --help option */
    { NULL, no_argument, NULL, 0 }
};


int main(int argc, char *argv[]) {
	// initial useful variables
	int opt = 0;
	int longIndex = 0;
	char * pEnd;

	/* Initialize globalArgs before we get to work. */
	arguments.unifSpace = 0;     /* default false for uniform space */
	arguments.width = 75;        /* default 75 for width */
	arguments.help = 0;          /* default false for showing help */
	arguments.version = 0;       /* default false for showing version */

	// initial getopt
	opt = getopt_long( argc, argv, optString, longOpts, &longIndex );
	// loops over different arguments
	while( opt != -1 ) {
		switch( opt ) {
		case 'u':     /* -u: uniform space */
			arguments.unifSpace = 1; /* true */
			break;
		case 'w':     /* -w: printing width */
			arguments.width = strtol(optarg,&pEnd,10);
			if (!pEnd){
				exit(0);
			}
			break;

		case 'h':     /* -h: help info */
			arguments.help = 1;
			display_help();
			break;

		case 'v':     /* -v: software version info */
			arguments.version = 1;
			display_version();
			break;

		case 0:       /* long option without a short arg */
			//do something
			break;

		default:
			/* You won't actually get here. */
			break;
		}
		// loops over getopt
		opt = getopt_long( argc, argv, optString, longOpts, &longIndex);
	}

	/* check for the argument of input filename */
	if (optind < argc)
	{
	    do
	    {
	        arguments.filename = argv[optind];
	    }
	    while ( ++optind < argc);
	}

	/* check for arguments */
	if (!arguments.filename && !arguments.help && !arguments.version){
		/* missing input filename as an argument + no help option + no version option */
		perror("The input file does not exist!\n");
	}else if (arguments.filename){
		/* format the input file by using options */
		display_setwidth(arguments.filename,arguments.width,arguments.unifSpace);
	}

	return EXIT_SUCCESS;
}

