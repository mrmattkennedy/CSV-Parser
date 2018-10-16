
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "SuperHero.h"
#include "My_Hash.h"
#define HASH_SIZE 17011

//Function signatures
void parse_csv(std::vector<SuperHero> & superheroes);
std::vector<unsigned short int> remove_commas(std::string *line);
void add_commas(std::vector<std::string> * tokens, std::vector<unsigned short int> comma_locations);
char check_char_token(std::string token);
int check_int_token(std::string token);
int hash_one(const SuperHero & s);
int hash_two(const SuperHero & s);
int hash_three(const SuperHero & s);

int main(int argc, char** argv)
{
	/* Actual vector that holds all superheroes. */
	std::vector<SuperHero> superheroes;

	/* This is the hash file. */
	My_Hash<SuperHero> hash;

	/*Holds all collision locations. Could just as easily use an int (probably better).*/
	std::vector<int> collision_loc;
	
	/* Output stream to write to file. */
	std::ofstream results_file;

	//Parses the CSV file and populates superheroes.
	parse_csv(superheroes);

	//Open the results file.
	results_file.open("RESULTS.md");

	//Send hash_one as the hash function, and see how many collisions there are.
	for (unsigned int i = 0; i < superheroes.size(); i++)
		if (hash.insert(superheroes[i], &hash_one) == true)
			collision_loc.push_back(i);

	//Write the date for hash_one to the file.
	results_file << "int hash_one(const SuperHero & s){return abs((s.get_page_id() * 54321) %% HASH_SIZE);}\n";
	results_file << "Collisions: " << collision_loc.size();
	results_file << "\n\n\n";

	//Clear the locations from here and from the hash class, then repopulate entries.
	collision_loc.clear();
	hash.clear_data();
	for (unsigned int i = 0; i < superheroes.size(); i++)
		if (hash.insert(superheroes[i], &hash_two) == true)
			collision_loc.push_back(i);
	
	//Write data for hash_two to file.
	results_file << "int hash_two(const SuperHero & s)\n";
	results_file << "{\n";
	results_file << "\tstd::string name = s.get_name();\n";
	results_file << "\tchar eye = s.get_eye_color();\n";
	results_file << "\tchar hair = s.get_hair_color();\n";
	results_file << "\tchar sex = s.get_sex();\n";
	results_file << "\tint hash_val = 0;\n\n";
	results_file << "\tfor (unsigned int i = 0; i < name.length(); i++)\n";
	results_file << "\t\thash_val += (int)name.at(i);\n\n";
	results_file << "\thash_val *= s.get_page_id();\n";
	results_file << "\thash_val += s.get_appearances();\n";
	results_file << "\thash_val+=(int)eye;\n";
	results_file << "\thash_val+=(int)hair;\n";
	results_file << "\thash_val+=(int)sex;\n";
	results_file << "\treturn abs(hash_val % HASH_SIZE);\n";
	results_file << "}\n";
	results_file << "Collisions: " << collision_loc.size();
	results_file << "\n\n\n";
	
	//Clear the locations from here and from the hash class, then repopulate entries.
	collision_loc.clear();
	hash.clear_data();
	for (unsigned int i = 0; i < superheroes.size(); i++)
		if (hash.insert(superheroes[i], &hash_three) == true)
			collision_loc.push_back(i);

	//Write data for hash_three to file.
	results_file << "int hash_three(const SuperHero & s)\n";
	results_file << "{\n"; 
	results_file << "\tint a = 54059;\n";
	results_file << "\tint b = 74963;\n";
	results_file << "\tlong h = 37;\n";
	results_file << "\tstd::string name = s.get_name();\n";
	results_file << "\tfor (unsigned  int i = 0; i < name.length(); i++)\n";
	results_file << "\t\th = (h * a) ^ ((int)(name.at(i)) * b);\n\n";
	results_file << "\treturn abs(h % HASH_SIZE);\n";
	results_file << "}\n";
	results_file << "Collisions: " << collision_loc.size();
	results_file.close();
}

/**********************************************************************
 * Parses a CSV file. This is done by reading in a line at a time, and
 * on each line, remove all commas that are in quotes. Then, after line
 * is parsed by using ',' as delimiter, put the commas back in.
 *********************************************************************/
void parse_csv(std::vector<SuperHero> & superheroes)
{
	/* Used to get a single line at a time. */
	std::string line;

	/* This is a temporary holder of a deliminated "attribute" for a superhero. */
	std::string tempAtt;

	/* This is an input stream to read the file. */
	std::ifstream ifs;

	/* This is a string stream to use the convenient method "getline" on a given string. */
	std::stringstream ss;

	/* This will temporarily hold the values for a soon-to-be superhero. */
	std::vector<std::string> tokens;

	/*Vector to hold the location of the commas. */
	std::vector<unsigned short int> commas;

	//Opens up the file with the input stream
	ifs.open("marvel-data.csv");

	//Get rid of the first line.
	std::getline(ifs, line);

	while (std::getline(ifs, line))
	{
		commas.clear();
		//If there are quotes in a line, check for commas within the quotes and get rid of them.
		if (line.find("\"") != std::string::npos)
			commas = remove_commas(&line);

		//Clear the prior values out.
		tokens.clear();

		//Empty the stringstream.
		ss.clear();

		//Set the stringstream string.
		ss.str(line);
		
		//Split the string with , as a delimiter.
		while (std::getline(ss, tempAtt, ','))
			tokens.push_back(tempAtt);
		
		//Add the commas back.
		add_commas(&tokens, commas);
		
		//If there is no last value for year, only 12 values will be added instead of 13. Just add empty string to fill in.
		if (tokens.size() == 12)
			tokens.push_back("");

		superheroes.push_back(SuperHero(check_int_token(tokens[0]),
					tokens[1],
					tokens[2],
					tokens[3],
					tokens[4],
					check_char_token(tokens[5]),
					check_char_token(tokens[6]),
					check_char_token(tokens[7]),
					tokens[8],
					check_int_token(tokens[9]),
					check_int_token(tokens[10]),
					tokens[11],
					check_int_token(tokens[12])));
	}
	//Close the input stream.
	ifs.close();
}

/**********************************************************************
 * Removes the commas and saves their locations. Finds a pair of quotes,
 * saves the locations of the commas in the given substring, then
 * deletes all commas in the quotes.
 *
 * @param std::string *line pointer to the string to remove commas from.
 * @return std::vector<unsigned short int> vector containing the
 *	locations of the commas for a given line.
 *********************************************************************/
std::vector<unsigned short int> remove_commas(std::string *line)
{
	/* First of 2 ints to hold the position of the opening quotation marks. */
	int first_quote_pos = 0;

	/* Second of 2 ints to hold the position of the closing quotation marks. */
	int second_quote_pos = 0;

	/* Instead of immediately deleting values, better to store them into a vector.
	 * If chars are deleted while looping through and there are multiple commas to delete,
	 * the size of the string is shifted, and a needed comma might get accidentally deleted. */
	std::vector<unsigned short int> temp_locations;
	std::vector<unsigned short int> comma_locations;
	
	unsigned int prev_size = 0;
	//Keep going as long as opening quote is found.
	while (first_quote_pos != -1 && second_quote_pos != -1)
	{
		//Look for next opening quote after last closing quote.
		first_quote_pos = line->find("\"", second_quote_pos + 1 - temp_locations.size());

		//Look for corresponding opening quote.
		second_quote_pos = line->find("\"", first_quote_pos + 1);
	
		//Clear temp vector so other sets of quotes aren't affected.
		temp_locations.clear();

		if (first_quote_pos != -1 && second_quote_pos != -1)
		{
			//Loop through all characters in the substring and check if they are commas.
			//If commas found, store position in the vector.
			for (int i = first_quote_pos; i < second_quote_pos; i++)
				if ((*line)[i] == ',')
					temp_locations.push_back(i);
			
			//Loop through the vector backwards so positions of other commas aren't affected,
			//then delete the commas.
			for (int i = temp_locations.size() - 1; i >= 0; i--)
				line->erase(temp_locations.at(i), 1);


			//Add commas from temp vector to return vector.	
			for (unsigned int i = 0; i < temp_locations.size(); i++)
				comma_locations.push_back(temp_locations[i] + prev_size);
			
			prev_size = temp_locations.size();
			if (prev_size != 0)
				prev_size--;
		}
	}

	return comma_locations;
}

/**********************************************************************
 * Adds commas back into a vector of tokens, which result from splitting
 * a string by delimiting commas.
 *
 * @param std::vector<std::string> * tokens This is a reference to the
 * 	tokens vector to edit.
 * @param std::vector<unsigned short int> comma_locations This is the
 * 	vector containing the locations of the commas.
 *********************************************************************/
void add_commas(std::vector<std::string> * tokens, std::vector<unsigned short int> comma_locations)
{
	//Current token looking at.
	int currTok;

	//Current size of all previous tokens.
	int currSize;
	
	for (unsigned int i = 0; i < comma_locations.size(); i++)
	{
		currTok = -1;
		currSize = 0;
		
		//Keep adding sizes together until size is greater than or equal to comma location.
		while (currSize < comma_locations[i])
		{
		       currTok++;
		       currSize += (*tokens)[currTok].size();
		}
		
		//Insert a comma at the vector pointer at a specific location.	
		tokens->at(currTok).insert(comma_locations[i] - (currSize - tokens->at(currTok).size()) - 1, 1, ',');
	}
	
}

/**********************************************************************
 * Checks a given string to see what the value is, and returns a
 * corresponding char value.
 *
 * @param std::string token The string to check.
 * @return char The char value to return based on token.
 *********************************************************************/
char check_char_token(std::string token)
{
	if (!token.empty())
	{
		
		if (token.find("Red") != std::string::npos)
			return 'R';
		else if (token.find("Orange") != std::string::npos)
			return 'O';
		else if (token.find("Yellow") != std::string::npos)
			return 'Y';
		else if (token.find("Green") != std::string::npos)
			return 'G';
		else if (token.find("Blue") != std::string::npos)
			return 'B';
		else if (token.find("Purple") != std::string::npos)
			return 'P';
		else if (token.find("Violet") != std::string::npos)
			return 'V';
		else if (token.find("Gold") != std::string::npos)
			return 'D';
		else if (token.find("Brown") != std::string::npos)
			return 'R';
		else if (token.find("Black") != std::string::npos)
			return 'L';
		return token.at(0);
	}
	return '\0';
}

/**********************************************************************
 * Checks a given string to see what the value is, and returns a
 * corresponding int value.
 *
 * @param std::string token The string to check.
 * @return int The int value to return based on token.
 *********************************************************************/
int check_int_token(std::string token)
{
	if (!token.empty())
	{
		if (token == "Living Characters") 
			return 1;
		else if (token == "Deceased Characters")
			return 0;
		else
			try {
				return std::stoi(token);
			} catch (const std::exception& e) {
				return -1;
			}
	}
	return -1;	

}

/**********************************************************************
 * First hashing function. Just takes the page_id, gets abs value, and
 * multiplies by 54321.
 *
 * @param const Superhero & s The superhero object to give a hash value
 * 	to.
 * @return int The hash id.
 *********************************************************************/
int hash_one(const SuperHero & s){return abs((s.get_page_id() * 54321) % HASH_SIZE);}

/**********************************************************************
 * Second hashing function. Adds the name, then multiplies by appearance,
 * then adds eye, hair, and sex.
 *
 * @param const Superhero & s The superhero object to give a hash value
 * 	to.
 * @return int The hash id.
 *********************************************************************/
int hash_two(const SuperHero & s)
{
	std::string name = s.get_name();
	char eye = s.get_eye_color();
	char hair = s.get_hair_color();
	char sex = s.get_sex();
	int hash_val = 0;

	for (unsigned int i = 0; i < name.length(); i++)
		hash_val += (int)name.at(i);
	hash_val *= s.get_page_id();
	hash_val += s.get_appearances();
	hash_val+=(int)eye;
	hash_val+=(int)hair;
	hash_val+=(int)sex;
	return abs(hash_val % HASH_SIZE);
}

/**********************************************************************
 * Third hashing function. Takes a given name for a superhero, then
 * does h * a to the power of the char in name * b.
 *
 * @param const Superhero & s The superhero object to give a hash value
 * 	to.
 * @return int The hash id.
 *********************************************************************/
int hash_three(const SuperHero & s)
{
	int a = 54059;
	int b = 74963;
	long h = 37;
	std::string name = s.get_name();
	for (unsigned  int i = 0; i < name.length(); i++) 
		h = (h * a) ^ ((int)(name.at(i)) * b);

	return abs(h % HASH_SIZE);
}
