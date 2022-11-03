
/*
Written by: Islam Kemelov
Capstone
*/

//how to compile : g++ main.cpp -l sqlite3

#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <regex>
#include <map>

using namespace std;
 

void printManas();
bool valid_alphabet(string u_input);
bool isEN(string u_input);
bool isKG(string u_input);

int main(int argc, char** argv)
{
    
    // Printing graphic manas dictionary on the screen
    printManas();
    
    
/*================================================================*/
    // Opening the database
    // Creating a SQLITE stmt
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open_v2("words_test5.db", &DB, SQLITE_OPEN_READONLY,0);
    string data("CALLBACK FUNCTION");

    sqlite3_stmt* stmt;
    int cnt = 0;
    
/*================================================================*/
    
    
/*================================================================*/
    // Handling user input
    // making sure that user input is all alphabetic characters
    
    string u_input;
    while(true){
        cout << "Enter your word here: ";
        getline(cin, u_input);
        
        bool valid_alpha = true;
        
        valid_alpha = valid_alphabet(u_input);
        
        if(valid_alpha != true){
            break;
        }else{
            cout << "Something is wrong! Please, enter alphabetic character: " <<endl;
            continue;
        }
    }
/*================================================================*/
    
    
/*================================================================*/
    // Search Algorythm
    
    char first_char_of_u_input = u_input[0];
    int id_of_first;
    int id_of_second;
    
    // creating hashmap for the index
    map <char, int> EN_range_ID;
    
    EN_range_ID.insert(pair <char, int>('a',1));
    EN_range_ID.insert(pair <char, int>('b',7));
    EN_range_ID.insert(pair <char, int>('c',14));
    EN_range_ID.insert(pair <char, int>('d',21));
    EN_range_ID.insert(pair <char, int>('e',34));
    EN_range_ID.insert(pair <char, int>('f',38));
    EN_range_ID.insert(pair <char, int>('g',47));
    EN_range_ID.insert(pair <char, int>('h',49));
    EN_range_ID.insert(pair <char, int>('i',58));
    EN_range_ID.insert(pair <char, int>('j',60));
    EN_range_ID.insert(pair <char, int>('k',63));
    EN_range_ID.insert(pair <char, int>('l',66));
    EN_range_ID.insert(pair <char, int>('m',70));
    EN_range_ID.insert(pair <char, int>('n',79));
    EN_range_ID.insert(pair <char, int>('o',84));
    EN_range_ID.insert(pair <char, int>('p',85));
    //EN_range_ID.insert(pair <char, int>("q","0")); There is no word starting with q in the dictionary yet
    EN_range_ID.insert(pair <char, int>('r',92));
    EN_range_ID.insert(pair <char, int>('s',96));
    EN_range_ID.insert(pair <char, int>('t',106));
    //EN_range_ID.insert(pair <char, int>("u","0"));
    EN_range_ID.insert(pair <char, int>('v',118));
    EN_range_ID.insert(pair <char, int>('w',119));
    //EN_range_ID.insert(pair <char, int>("x","0"));
    EN_range_ID.insert(pair <char, int>('y',126));
    //EN_range_ID.insert(pair <char, int>("z","0"));
  
    
    if(first_char_of_u_input != 'y'){
        id_of_first = EN_range_ID.find(first_char_of_u_input)->second;
        id_of_second = EN_range_ID.find(first_char_of_u_input + 1)->second;
        id_of_second = id_of_second - 1;
    }else{
        id_of_first = EN_range_ID.find(first_char_of_u_input)->second;
        id_of_second = 126; // 126 is ID of the last word
    }
/*================================================================*/
    
    
    
/*================================================================*/
    // Identifying the language
    
    bool isEnglish = true;
    bool isKyrgyz = true;
    string final_stmt;
    
    isEnglish = isEN(u_input);
    
    if(isEnglish != true){
        
        //SELECT EN, KG FROM TRANSLATIONS WHERE ID BETWEEN 1 AND 6 AND EN LIKE  'a%' COLLATE NOCASE ORDER BY EN ASC LIMIT 5;
        
        string s_id_of_first = to_string(id_of_first);
        string s_id_of_second = to_string(id_of_second);
        
        string s_and = " AND ";
        
        string part1 = "SELECT EN, KG FROM TRANSLATIONS WHERE ID BETWEEN ";
        string part2 = "EN LIKE '";
        string part3 = "%' COLLATE NOCASE ORDER BY EN ASC LIMIT 10;";
        
        final_stmt = part1 + s_id_of_first + s_and + s_id_of_second + s_and + part2 + u_input + part3;
        
        
    }else{
        isKyrgyz = isKG(u_input);
        if(isKyrgyz != true){
            
            string KG_part1 = "SELECT KG, EN FROM TRANSLATIONS WHERE KG LIKE '";
            string KG_part2 = "%' COLLATE NOCASE ORDER BY EN ASC LIMIT 10;";
            
            final_stmt = KG_part1 + u_input + KG_part2;
            
        }else{
            cout << "Not english or kyrgyz!" <<endl;
        }
    }
 
    
/*================================================================*/
    
    
    

    const char *c = final_stmt.c_str();
    
    //const char* sql = "SELECT EN, KG FROM TRANSLATIONS WHERE EN LIKE 't%' COLLATE NOCASE";

    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
  		
	int rc = sqlite3_prepare_v2(DB, c , -1, &stmt, NULL);
    
   // sqlite3_bind_text(stmt, 1, s, -1, SQLITE_TRANSIENT);

    if (rc != SQLITE_OK){
        cerr << "Error SELECT" << endl;
	}


    cout << "\n";
    cout << "       - - - Results: - - - " << endl;
    cout << endl;

	const unsigned char* answer;		
	const unsigned char* answer1;
	//int a=0;

	while(sqlite3_step(stmt) != SQLITE_DONE){

		
		answer = sqlite3_column_text(stmt, 0);
        answer1 = sqlite3_column_text(stmt, 1);
        
        
        cout << "     " << answer <<" ----> " << " " << answer1 <<endl;
	}

    cout << endl;
	sqlite3_finalize(stmt);


    sqlite3_close(DB);
    
    
    return (0);
}

void printManas(){
    
    cout << "\n";
    cout << "*===================================*" << endl;
    
    int n = 3;
    int i, j;
         
        // This is upper half of pattern
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= (2 * n); j++)
            {
                // Left part of pattern
                if (i < j)
                    cout << " ";
                else
                    cout << "manas";
                 
                // Right part of pattern
                if (i <= ((2 * n) - j))
                    cout << " ";
                else
                    cout << "сөздүк";
            }
            cout << "\n";
        }
         
        // This is lower half of pattern
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= (2 * n); j++)
            {
                // Left part of pattern
                if (i > (n - j + 1))
                    cout <<" ";
                else
                    cout <<"манас";
                     
                // Right part of pattern
                if ((i + n) > j)
                    cout << " ";
                else
                    cout << "dictionary";
            }
            cout << "\n";
        }
    
    cout << "*===================================*" <<  endl;
    cout << "\n";
}



// Function for SQLITE exec call
static int callback(void* data, int argc, char** argv, char** azColName)
{
   
        fprintf(stderr, "%s: ", (const char*)data);

     for(int i = 0; i < argc; i++) {
        
            // Show column name, value, and newline
            cout << argv[i] << endl;
    
        }
 
        printf("\n");
        return 0;
}



bool valid_alphabet(string u_input){
    string EN_alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string KG_alphabet = "ячсмитьбюфывапроөлджэйцуүкенңгшщзхъЯЧСМИТЬБЮФЫВАПРОӨЛДЖЭЙЦУҮКЕНҢГШЩЗХЪ";
    string EN_and_KG_alphaabet = EN_alphabet + KG_alphabet;
    
    bool contains_non_alpha = u_input.find_first_not_of(EN_and_KG_alphaabet) != std::string::npos;
    
    return contains_non_alpha;
}




bool isEN(string u_input){
    
    string EN_alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    bool isEnglish = u_input.find_first_not_of(EN_alphabet) != std::string::npos;
    
    return isEnglish;
    
}



bool isKG(string u_input){
    
    string KG_alphabet = "ячсмитьбюфывапроөлджэйцуүкенңгшщзхъЯЧСМИТЬБЮФЫВАПРОӨЛДЖЭЙЦУҮКЕНҢГШЩЗХЪ";
    bool isKyrgyz = u_input.find_first_not_of(KG_alphabet) != std::string::npos;
    
    return isKyrgyz;
    
}
