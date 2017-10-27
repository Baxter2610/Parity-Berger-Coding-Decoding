/* Coding.cpp */

#include <iostream>
#include <fstream>  // ifstream , ofstream//
#include <bitset>   //bitset//  
#include <stdlib.h> // rand,srand //
#include <time.h>  // time //
#include <iomanip> // setprecision //
#include <ctype.h> // toupper //
#include <stdio.h> // remove //
#include "functions.h" // check_arguments,coding,transmission,decoding,compare,print_reuslts,create_statistics //

int main (int argc , char** argv) {
	
		if ( check_arguments( argc , argv ) ) {
			exit_message( 1 );
			return( 1 );
		}
		std::size_t array_size;
		std::string encoding;
		if ( std::string ( argv[3] ) == "P" ) {
			array_size = 9;
			encoding = "Parity";
		} else {
				array_size = 11;
				encoding = "Berger";
		}
		char source_buffer [array_size] = {0};
		char destination_buffer [array_size] = {0};
		unsigned long int total_loops = 0;
		bool need_repeat = false;
		char filechar;
		srand ( time ( NULL ) );
		std::ifstream input_file ( argv[1] );
		std::ofstream output_file ( argv[2] );
		if ( input_file.is_open() && output_file.is_open() ) {
			while ( input_file.get(filechar) ) {
			 	if ( check(filechar) ){
			 		do {
						 total_loops++;
						 coding( filechar , source_buffer , std::string ( argv[3] ) );
						 transmission( source_buffer , destination_buffer , array_size , atoi( std::string( argv[4] ).c_str() ) );
						 decoding( destination_buffer , array_size , std::string( argv[3] ) , output_file , need_repeat , filechar );
						}while( need_repeat );
			  	} else {
						output_file << filechar; // when the program reads a invalid char , it simply writes it to the output file to keep the file lenghth the same //
			    }		
			}
		} else {
				exit_message( 2 );
				return ( 2 );
		}
		output_file.close();
		input_file.close();		  	 
		double success_rate = compare ( std::string( argv[1] ) , std::string( argv[2]) );
		print_results( argv , encoding , total_loops , success_rate );
		create_statistics( argv );	
		return ( 0 );
}
