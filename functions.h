#define FUNCTIONS

void coding 
(	char current_char ,
	char source[] ,
	std::string coding_type ) {	
		short int ones_counter = 0;
		std::bitset <7> bit7 ( current_char );
		char temp_array[7] = {0};
		std::string bit7_str = bit7.to_string();		
		std::copy ( bit7_str.begin() , bit7_str.end() , temp_array );
		for ( int i = 0; i < 7; i++ ) {
			if ( bit7[i] == 1 )	{
				ones_counter++;
			}
		source[i] = temp_array[i];
		}
		if ( coding_type == "P" ) {
			if ( ones_counter%2 == 0 ) {
				source[7] = (char) 48;
			} else {
				source[7] = (char) 49;
			}
		} else {
			 std::bitset<3> counter_3 ( ones_counter );
			 std::string counter_3_str = counter_3.to_string ();
			 char counter_array[3] = {0};
			 std::copy ( counter_3_str.begin() , counter_3_str.end() , counter_array );
			 for ( int i = 0; i < 3; i++ ) {
					source[7 + i] = counter_array [i];
			}
		}
}
void transmission 
(	char source[] ,
	char destination[] ,
	std::size_t array_size ,
	short int possibility ) {
		short int random_number;
		for( int i = 0; i < array_size; i++ ) {
			random_number = rand () % 101;
			if ( random_number > 0 && random_number <= possibility ) {
				if ( source[i] == (char) 48 ) { // 48(dec)=0(ascii) 49=1 //
					destination[i] = (char) 49;
				} else {
						destination[i] = (char) 48;
				}
			} else {
				destination[i] = source[i]; 
			} 	
		}
}
void decoding 
(	char destination[] ,
	std::size_t array_size ,
	std::string coding_type ,
	std::ofstream &output_file ,
	bool &loop ,
	char &loop_char ) {
		int ascii_decimal;
		short int ones_counter = 0;
		int pos = 6;
		std::bitset <7> ascii_binary;
		for ( int i = 0; i < 7; i++ ) {
			if ( destination[i] == (char) 49 ) {
				ascii_binary.set( pos );
				ones_counter++;
			} else {
					ascii_binary.set( pos , 0);
			}
			pos--;
		}
		ascii_decimal = (int) ( ascii_binary.to_ulong () );
		char ascii_char = ascii_decimal;
	 //if ( check ( ascii_char ) ) {  write chars which are not in range? // 
		if( coding_type == "P" ) {
			if ( ( destination[7] == (char) 49 && ones_counter % 2 == 1) ||
				 ( destination[7] == (char) 48 && ones_counter % 2 == 0 ) ) {
					output_file << ascii_char; 
					loop = false;
			    } else {
						loop = true;
				}
		} else {
				std::bitset <3> meta_binary;
				pos = 2;
				for ( int i = 7; i < 10; i++ ) {
					if ( destination[i] == (char) 49 ) {
						meta_binary.set ( pos );
					} else {
							meta_binary.set ( pos , 0 );
					}
				pos--;
				}
				int meta_decimal = (int) ( meta_binary.to_ulong () ) ;
				if ( meta_decimal == ones_counter ) {
						output_file << ascii_char;
						loop = false;
					} else {
							loop = true; 
					}
		}
		//	} else {
		//		loop = true;
		//}
		//	if ( loop ) {  // send to coding modified char or the one read? //
		//		loop_char = ascii_char; // with if-> modified char   without if-> char read from input file //
		//	}
}
double compare 
(	std::string input_directory ,
	std::string output_directory
	 ) {	
		std::ifstream input_file ( input_directory.c_str() );
		std::ifstream output_file ( output_directory.c_str() );
		char input_char;
		char output_char;
		unsigned long int same_chars = 0;
		unsigned long int total_chars = 0;
		while ( input_file.get ( input_char ) && output_file.get ( output_char ) ) {
			total_chars++;
			if( input_char == output_char ) {
				same_chars++;
			}
		}
		input_file.close();
		output_file.close();
		return ( same_chars / (double) total_chars * 100 );
}
bool check ( char char_to_check ) {
		if ( ( (int) char_to_check >= 65 && (int) char_to_check <= 90 ) ||     //    A-Z      //
			 ( (int) char_to_check >= 97 && (int) char_to_check <= 122 ) ||   //    a - z    //
			 ( (int) char_to_check >= 48 && (int) char_to_check <= 59 ) ) {	 // 0-9 and :;  //
				return true;
			} else {
					switch ( (int) char_to_check )
					{
						case 32 : /* space */
						case 33 : /* ! */
						case 34 : /* " */
						case 39 : /* ' */
						case 40 : /* ( */
						case 41 : /* ) */
						case 44 : /*  ,  */
						case 45 : /* - */ 
						case 46 : /* . */
						case 63 : /* ? */
							return true;						
						default :
							return false;					
					}
			}
}

void exit_message ( int value ) {
	switch ( value ) {
		case 1:
			std::cout << "Syntax error/Invalid number of arguments. " << std::endl;
			std::cout << "		[input_file] [output_file] [encoding] [possibility]" << std::endl;
			std::cout << "		[*.txt] [*.txt] [P (Parity) / B (Berger)] [0-100]" << std::endl;
			break;
		case 2:
			std::cout << "Error opening input/output file." << std::endl;
			break;
		default:
			break;
	}
	
}
bool check_arguments 
( 	int argc ,
	char** argv ) {
		if( argc!=5 ) {
			return true;
		}
		std::string directory_1 = std::string ( argv[1] );
		std::string directory_2 = std::string ( argv[2] );
		std::string coding = std::string ( argv[3] );
		int pos = atoi ( std::string ( argv[4] ).c_str() );
		directory_1.erase ( directory_1.begin () , directory_1.end () - 4 );
		directory_2.erase ( directory_2.begin () , directory_2.end () - 4 );
		if  (  directory_1 != ".txt"  ||
			   directory_2 != ".txt"  ||
			  ( coding != "P" && coding != "B" ) ||
			  ( pos < 0 || pos > 100 ) ) {
				return true;
		}
		return ( false );
}
void print_results
(	char** argv ,
	std::string encoding,
	unsigned long int total_loops,
	double success_rate) {
	std::cout << "Input file: " << (char) 34 << argv[1] << (char) 34 << std::endl 
			  << "Output File: " << (char) 34 << argv[2] << (char) 34 << std::endl 
			  << "Encoding: " << encoding << std::endl 
			  << "Repeats: " << total_loops << std::endl 
			  << "Possibility: " << argv[4] << std::endl
			  << "Success rate: " << std::setprecision(3) <<  success_rate << "%" << std::endl;  
	}

void create_statistics ( char** argv ) {
		char answer;    
			do{
				std::cout << std::endl << "Create statistics for " << (char) 34 << argv[1] << (char) 34 << " ? (Y/N): ";    
				std::cin >> answer;
				}while( toupper( answer ) != (char) 89 && toupper( answer ) != (char) 78 );
		if ( toupper( answer ) == (char) 89 ){
			const std::size_t percentage_range = 101;
			char source_buffer [11] = {0};  // 11 for both parity & berger //
			char destination_buffer [11] = {0};
			double success_parity [percentage_range] = {0}; 
			int loops_parity [percentage_range] = {0};
			double success_berger [percentage_range] = {0};
			int loops_berger [percentage_range] = {0};
			std::ifstream input_statistics;
			std::ofstream output_statistics;
			bool need_repeat=false;
			char filechar;
			for ( int i = 0; i < percentage_range; i++ ) {		
				for ( int j = 0; j < 2; j++ ) {
					input_statistics.open ( argv[1] );
					output_statistics.open ( "temp.txt" );
					while ( input_statistics.get ( filechar ) ) {	
							if ( check ( filechar ) ) {
									if ( j == 0 ) {
										do {
											loops_parity[i]++;
											coding ( filechar , source_buffer , "P" );
											transmission ( source_buffer , destination_buffer , 9 , i );
											decoding ( destination_buffer , 9 , "P" , output_statistics , need_repeat , filechar );
											} while ( need_repeat );
									} else {
											do {
												loops_berger[i]++;
												coding( filechar , source_buffer , "B" );
												transmission( source_buffer , destination_buffer , 11 , i );
												decoding( destination_buffer , 11 , "B" , output_statistics , need_repeat , filechar );
												} while( need_repeat );
									}
							} else {
									output_statistics << filechar;
							}
					}
					input_statistics.close();
					output_statistics.close();
					if ( j == 0 ) {
							success_parity[i] = compare ( std::string( argv[1] ), "temp.txt" );
					} else {
							success_berger[i] = compare ( std::string( argv[1] ) , "temp.txt" );
					}
					remove ( "temp.txt" );
				}
			}
			std::ofstream file_statistics ( "Statistics.csv" ); 
			file_statistics << "Input File,Possibility,Encoding,Repeats,Success Rate,Encoding,Repeats,Success Rate" << std::endl << std::endl;
			for ( int i = 0; i < percentage_range; i++ ) {
				file_statistics << argv[1] << "," << i << "%," << "Parity" << "," << loops_parity[i] << "," << success_parity[i] << "%," << "Berger," << loops_berger[i] << "," << success_berger[i] << "%" << std::endl;
			}
			file_statistics.close();
		}
		std::cout << "File was created.";
}
