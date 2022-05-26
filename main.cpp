#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "ooffunctions.h"


int main(){

    // Preparation to open the File
    std::string path = "testing.txt";
    std::ifstream fin;

    // Scope Rules
    bool oof_started_with_scope = false;
    int open_scope_count = 0;
    int closing_scope_count = 0;
    int open_boxscope_count = 0;
    int closing_boxscope_count = 0;
    int open_roundscope_count = 0;
    int closing_roundscope_count = 0;
    char last_symbol;

    // Opening the File
    fin.open(path);

    // Checking if File is opened or Scopes Rules are passed
    if(fin.is_open()){
        
        // Start Checking Scopes Rules
        char s;

        while(fin.get(s)){

            // Checking that Code Started with {
            if(s != '{' && !(oof_started_with_scope)){
                std::cout << "\nExpected to be { at the start of the Code ! The Program will be CLOSED !\n";
                return 0;
            }

            // Starting symbol passed
            oof_started_with_scope = true;

            // Passing White spaces
            if(s == ' ' || s == '\n' || s == '\t'){
                continue;
            }
            
            // To check that the code ended with }
            last_symbol = s;

            // Counting Scopes
            if(s == '{'){
                ++open_scope_count;
            }
            else if(s == '}'){
                ++closing_scope_count;
            }

            if(s == '['){
                ++open_boxscope_count;
            }
            else if(s == ']'){
                ++closing_boxscope_count;
            }

            if(s == '('){
                ++open_roundscope_count;
            }
            else if(s == ')'){
                ++closing_roundscope_count;
            }
        }
        
        // Checking last Symbol, must be }
        if(last_symbol == '}'){
            if((open_scope_count == closing_scope_count) && (open_boxscope_count == closing_boxscope_count) && (open_roundscope_count == closing_roundscope_count)){
                std::cout << "\nScope Rules passed, starting to initialize the code !\n\n";
            }
            else{
                std::cout << "\nScope Rules failed ! The Program will be CLOSED !\n";
                return 0;
            }

        }
        else{
            std::cout << "\nExpected to be } at the end of the Code ! The Program will be CLOSED !\n";
            return 0;
        }

    }
    else{
        //File Not Found
        std::cout << "\nCan't open the File ! The Program will be CLOSED ! \n";
        return 0;
    }

    // Closing the File to reopen again
    fin.close();


    /////////////////////////////////////////////////////////
    /* START OF OOF SCRIPT */
    /////////////////////////////////////////////////////////

    // Opening the File again
    fin.open(path);
    
    // Creating Data Storage (SCOPE, VARIABLE_NAME, VARIABLE_TYPE, VARIABLE_VALUE)
    std::map <int, std::map <std::string, std::map <std::string, std::string >>> data;
    // To delete storage, when out of visibility Scope
    std::map <int, std::map <std::string, std::map <std::string, std::string >>>::iterator scope_finder;

    // Scope Vision for Data
    int scope_vision = -1;

    // Tokening
    std::string token = "";
    int var_scope = 0;
    std::string var_name_token = "";
    std::string var_type_token = "";
    std::string var_value_token = "";
    std::string token_line[10];

    // Line
    std::string line = "";
    int line_counter = 1;

    // Declaration
    bool line_is_declaration = false;
    bool line_is_declaration_initialization = false;
    bool line_token_is_init_equal_symbol = false; // Means that next token must be '='

    // Assignment
    bool line_is_assignment = false;
    bool line_token_is_assign_equal_symbol = false;
    bool start_the_assign = false;

    // Expression for Assignment and Operation
    std::string exp = "";
    bool line_token_is_exp = false;

    // Expression for CON
    std::string con_exp = "";
    bool line_token_is_con_exp = false;
    bool line_is_con_oper = false;
    bool con_else_statement = false;
    bool con_true_statement = false;
    bool con_checking_true_statement = false;
    bool con_checking_false_statement = false;

    // Expression for SHOW
    std::string show_exp = "";
    bool line_token_is_show_exp = false;
    bool line_print_the_show_exp = false;

    // Expression for PERIOD
    std::string period_exp = "";
    std::string period_exp_after_insert = "";
    std::string period_tokens = "";
    std::string reserve_period_tokens = "";
    int loop_scope_counter = 0;
    int period_lines = 0;
    bool line_token_is_period_exp = false;
    bool period_condition = false;
    bool pass_period_scopes = false;
    bool start_the_loop = false;

    ///////////////////////////////////////////// Execution of the code ////////////////////////////////////////////////////

    // Start
    while(!(fin.eof())){

        // Empty the token
        token = "";

        // Read file by token
        fin >> token;
  
        line = line + " ____ " + token;
   
        // Do the LOOP if condition for PERIOD = TRUE
        if(period_condition){
            if(token.compare("@") == 0){
                ++loop_scope_counter;
                ++period_lines;
            }
            if(loop_scope_counter == 2){
                start_the_loop = true;
                loop_scope_counter = 0;
            }

            period_tokens += token + " ";

            if(start_the_loop){
                line_counter = period_lines;
                reserve_period_tokens = period_tokens;
                reserve_period_tokens = reserve_period_tokens.erase(0, 2);
                reserve_period_tokens = reserve_period_tokens.erase(reserve_period_tokens.length() - 3, 3);
                token = "";
                
                /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                /// SHAT VAT TEXA MTNELU HAMAR CHARJI !
                while(oof_give_con_exp_result(period_exp_after_insert)){
                    for(int t = 0; t < reserve_period_tokens.length(); ++t){
                        if(reserve_period_tokens[t] == ' ' || t == reserve_period_tokens.length() - 1){
                            if(t == reserve_period_tokens.length() - 1){
                                token += reserve_period_tokens[t];
                            }

                            // Fill the Expression with token and check for PERIOD
                            if(line_token_is_period_exp){
                                period_exp = token;
                                if(oof_check_con_exp(period_exp)){
                                    period_exp_after_insert = oof_insert_values_of_con_exp(period_exp, scope_vision, data);
                                    if(oof_give_con_exp_result(period_exp_after_insert)){
                                        period_condition = true;
                                        ++scope_vision;
                                        period_lines = line_counter;

                                    }
                                    else{
                                        pass_period_scopes = true;
                                        period_exp_after_insert = "";

                                    }
                                    
                                    line_token_is_period_exp = false;
                                    ++line_counter;
                                    token = "";
                                    continue;
                                }
                                else{
                                    std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 699_Wrong Syntax !\n";
                                    return 0;
                                }
                            }

                            // If the CON TRUE statement
                            if(line_is_con_oper && con_checking_true_statement){
                                if(con_true_statement){
                                    if(token.compare("[") == 0){
                                        ++scope_vision;
                                        ++line_counter;
                                        token = "";
                                        continue;
                                    }
                                }
                                else if(con_else_statement && token.compare("]") != 0){
                                    if(token.compare(";") == 0 || token[token.length() - 1] == ')'){
                                        ++line_counter;
                                    }
                                    if(token.compare("[") == 0 || token.compare("{") == 0 || token.compare("}") == 0){
                                        ++scope_vision;
                                        ++line_counter;
                                    }
                                    if(token.compare("}") == 0){
                                        --scope_vision;
                                        ++line_counter;
                                    }
                                    token = "";
                                    continue;
                                }
                                if(token.compare("]") == 0){
                                    con_checking_true_statement = false;
                                    line_is_con_oper = false;
                                    ++line_counter;
                                    --scope_vision;
                                    token = "";
                                    continue;
                                }
                            }
                            
                            // If the CON TRUE statement passed, check if next token is ELSE
                            if(token.compare("ELSE") == 0){
                                line_is_con_oper = true;
                                con_checking_false_statement = true;
                                ++line_counter;
                                token = "";
                                continue;
                            }

                            // Fill Expression with token and check the SHOW
                            if(line_token_is_show_exp && token.compare("[") == 0){
                                show_exp += token;
                                token = "";
                                continue;
                            }
                            if(line_token_is_show_exp && token[token.length() - 1] == ';'){
                                show_exp += token.erase(token.length() - 1, 1);
                                line_token_is_show_exp = false;
                                line_print_the_show_exp = true;
                                ++line_counter;
                                token = "";
                                continue;
                            }
                            if(line_token_is_show_exp){
                                show_exp += token;
                                token = "";
                                continue;
                            }

                            // PRINT the SHOW expression
                            if(line_print_the_show_exp){
                                if(oof_check_show_exp(show_exp, data)){

                                    show_exp = show_exp.erase(0,1);
                                    show_exp = show_exp.erase(show_exp.length() - 1,1);
                                    show_exp = oof_exp_variable_insert(show_exp, scope_vision, data);
                                    show_exp = oof_do_expression_result(show_exp);
                                    std::cout << "\nTHIS_IS_YOUR_COUT>>>>>>>>   " << show_exp << "    <<<<<<<\n";
                                    line_print_the_show_exp = false;
                                    show_exp = "";
                                }
                                else{
                                    std::cout << "\nWrong SHOW Operation is performed !\nError at line: " << line_counter << " ->  " << show_exp << "  <- 656_Wrong Syntax !\n";
                                    return 0;
                                }
                            }

                            // If There is ELSE, check the CON FALSE statement
                            if(line_is_con_oper && con_checking_false_statement){
                                if(con_true_statement && token.compare("]") != 0){
                                    if(token.compare(";") == 0 || token[token.length() - 1] == ')'){
                                        ++line_counter;
                                    }
                                    if(token.compare("[") == 0 || token.compare("{") == 0){
                                        ++scope_vision;
                                        ++line_counter;
                                    }
                                    if(token.compare("}") == 0){
                                        --scope_vision;
                                        ++line_counter;
                                    }
                                    token = "";
                                    continue;
                                }
                                else if(con_else_statement){
                                    if(token.compare("[") == 0){
                                        ++scope_vision;
                                        ++line_counter;
                                        token = "";
                                        continue;
                                    }
                                }
                                if(token.compare("]") == 0){
                                    con_checking_false_statement = false;
                                    line_is_con_oper = false;
                                    con_else_statement = false;
                                    con_true_statement = false;
                                    --scope_vision;
                                    ++line_counter;
                                    token = "";
                                    continue;
                                }
                            }

                            // Fill Expression with token and check the CON
                            if(line_token_is_con_exp){
                                con_exp = token;
                                if(oof_check_con_exp(con_exp)){
                                    con_exp = oof_insert_values_of_con_exp(con_exp, scope_vision, data);
                                    if(oof_give_con_exp_result(con_exp)){
                                        con_true_statement = true;

                                    }
                                    else{
                                        con_else_statement = true;

                                    }
                                    line_is_con_oper = true;
                                    con_checking_true_statement = true;
                                    line_token_is_con_exp = false;
                                    ++line_counter;
                                    token = "";
                                    continue;
                                }
                                else{
                                    std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 699_Wrong Syntax !\n";
                                    return 0;
                                }
                            }

                            // Fill Expression with tokens for ASSIGNMENT
                            if(token[token.length() - 1] == ';' && line_token_is_exp && line_is_assignment){
                                exp += token.erase(token.length() - 1, 1);
                                if(oof_check_expression(exp, data)){

                                    exp = oof_exp_variable_insert(exp, scope_vision, data);

                                    if(var_type_token.compare("struna") == 0){

                                        if(oof_exp_result_is_struna(exp)){
                                            var_value_token = oof_do_expression_result(exp);
                                            data[var_scope][var_name_token][var_type_token] = var_value_token;
                                        }
                                        else{
                                           std::cout <<"\nWrong Assignment is performed ! The expression result is not STRUNA !" 
                                          <<"\nError at line: " << line_counter << " ->  " << exp << "  <- 299_Wrong Syntax !\n";
                                        }
                                    }
                                    else if(var_type_token.compare("real") == 0){

                                        var_value_token = oof_arithmetic_exp_operation(exp);
                                        data[var_scope][var_name_token][var_type_token] = var_value_token;
                                    }
                                    else if(var_type_token.compare("dig") == 0){

                                        var_value_token = oof_arithmetic_exp_operation(exp);
                                        var_value_token = oof_make_dig(var_value_token);
                                        data[var_scope][var_name_token][var_type_token] = var_value_token;
                                    }
                                    else if(var_type_token.compare("oz") == 0){

                                        var_value_token = oof_arithmetic_exp_operation(exp);
                                        var_value_token = oof_make_oz(var_value_token);
                                        data[var_scope][var_name_token][var_type_token] = var_value_token;
                                    }

                                    line_token_is_exp = false;
                                    line_is_assignment = false;
                                    ++line_counter;
                                    exp = "";
                                    var_scope = 0;
                                    var_name_token = "";
                                    var_type_token = "";
                                    var_value_token = "";
                                    token = "";
                                    continue;
                                }
                                else{
                                    std::cout << "\nWrong Assignment is performed !\nError at line: " << line_counter << " ->  " << exp << "  <- 251_Wrong Syntax !\n";
                                    return 0;
                                }
                            }

                            if(line_token_is_exp && line_is_assignment){
                                exp += token;
                                token = "";
                                continue;
                            }

                            // Check if opening { and closing } scope
                            if(token.compare("{") == 0){
                                ++scope_vision;

                                ++line_counter;
                                data[scope_vision]["main"]["scope"] = "open";
                                token = "";
                                continue;
                            }
                            else if(token.compare("}") == 0){
                                scope_finder = data.find(scope_vision);
                                data.erase(scope_finder);
                                --scope_vision;

                                ++line_counter;
                                token = "";
                                continue;
                            }



                            // Token must be = for Assignment
                            if(token.compare("=") == 0 && line_token_is_assign_equal_symbol){
                                line_is_assignment = true;
                                line_token_is_exp = true;
                                line_token_is_assign_equal_symbol = false;
                                token = "";
                                continue;
                            }

                            // If Previous Token was not = for assignment
                            if(line_token_is_assign_equal_symbol && !(line_is_assignment)){
                                std::cout << "\nWrong Initialization is performed !\nError at line: " << line_counter << " -> " << token << " <- 211_Wrong Syntax !\n";
                                return 0;
                            }

                            // Token must be = for initialization
                            if(token.compare("=") == 0 && line_token_is_init_equal_symbol){
                                line_is_declaration_initialization = true;
                                line_token_is_init_equal_symbol = false;
                                token = "";
                                continue;
                            }
                            // If Previous Token was not = for initialization
                            if(line_token_is_init_equal_symbol && !(line_is_declaration_initialization)){
                                std::cout << "\nWrong Initialization is performed !\nError at line: " << line_counter << " -> " << token << " <- 2_Wrong Syntax !\n";
                                return 0;
                            }

                            if((token[token.length() - 1] == ';') && line_is_declaration_initialization){
                                // Line is Declaration With Initialization
                                var_value_token = token.erase(token.length() - 1, 1);

                                if(oof_variable_name_exists_in_current_scope(var_name_token, scope_vision, data)){
                                            std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 1_Wrong Syntax !\n";    /// 2
                                            return 0;
                                }
                                else{
                                    if(var_type_token.compare("dig") == 0 && oof_value_is_dig(var_value_token)){
                                        data[scope_vision][var_name_token][var_type_token] = var_value_token;
                                    }
                                    else if(var_type_token.compare("real") == 0 && oof_value_is_real(var_value_token)){
                                        data[scope_vision][var_name_token][var_type_token] = var_value_token;
                                    }
                                    else if(var_type_token.compare("struna") == 0 && oof_value_is_struna(var_value_token)){
                                        data[scope_vision][var_name_token][var_type_token] = var_value_token;
                                    }
                                    else if(var_type_token.compare("oz") == 0){
                                        if(oof_value_is_oz(var_value_token)){
                                            data[scope_vision][var_name_token][var_type_token] = "1";
                                        }
                                        else{
                                            data[scope_vision][var_name_token][var_type_token] = "0";
                                        }
                                    }
                                    else{
                                        std::cout << "\nWrong Assignment ! Types are different !\n" << "\nError at line: " 
                                                << line_counter << " -> " << token << " <- 295_Wrong Syntax !\n";            /// 295
                                        return 0;
                                    }
                                }

                                // Empty all tokens
                                var_value_token = "";
                                var_type_token = "";
                                var_name_token = "";
                                // Declaration With Initialization Done !
                                line_is_declaration_initialization = false;
                                ++line_counter;
                                token = "";
                                continue;
                            }
                            else if((token[token.length() - 1] == ';') && line_is_declaration){
                                // Line is just Declaration
                                var_name_token = token.erase(token.length() - 1, 1);

                                if(oof_check_token_syntax(var_name_token)){
                                    // Checking Declaration syntax
                                    if(oof_line_can_be_declaration(var_name_token)){
                                        // Checking if Variabale name already exists
                                        if(oof_variable_name_exists_in_current_scope(var_name_token, scope_vision, data)){
                                            std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 2_Wrong Syntax !\n";    /// 2
                                            return 0;
                                        }
                                        else{
                                            // Create Variable name in the current scope
                                            if(var_type_token.compare("dig") == 0){
                                                // For DIG type
                                                data[scope_vision][var_name_token][var_type_token] = "0";
                                            }
                                            else if(var_type_token.compare("struna") == 0){
                                                // for STRUNA type
                                                data[scope_vision][var_name_token][var_type_token] = "<>";
                                            }
                                            else if(var_type_token.compare("real") == 0){
                                                // for REAL type
                                                data[scope_vision][var_name_token][var_type_token] = "0.0";
                                            }
                                            else if(var_type_token.compare("oz") == 0){
                                                // for OZ type
                                                data[scope_vision][var_name_token][var_type_token] = "false";
                                            }
                                            
                                            // Empty all tokens
                                            var_value_token = "";
                                            var_type_token = "";
                                            var_name_token = "";
                                            // Declaration Done !
                                            line_is_declaration = false;
                                            ++line_counter;
                                            token = "";
                                            continue;
                                        }
                                    }
                                    else{
                                        std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 3_Wrong Syntax !\n";   /// 3
                                        return 0;
                                    }
                                }
                                else{
                                    std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 4_Wrong Syntax !\n";  /// 4
                                    return 0;
                                }
                            }
                            else if(token[token.length() - 1] == ';'){
                                ++line_counter;
                                token = "";
                                continue;
                            }
                            
                            // Checking the start of the line, it's can be Declaration or Operation
                            // Check if Token Syntax is ok                                           // WrongSyntax:    6   65
                            if(oof_check_token_syntax(token)){
                                
                                // if True, line is Declaration, if False, line is Operation
                                if(oof_line_is_declaration_or_operation(token)){
                                    
                                    // If Declaration
                                    var_type_token = token;
                                    // Next Token must be variable_name !
                                    line_is_declaration = true;
                                    token = "";
                                    continue;
                                }
                                else if(!(oof_line_is_declaration_or_operation(token)) && line_is_declaration){
                                    // Line is Declaration with Initialization
                                    var_name_token = token;
                                    line_token_is_init_equal_symbol = true;
                                    line_is_declaration = false;

                                    token = "";
                                    continue;
                                }
                                else{
                                    // Operation Logic Checking
                                    if(oof_line_is_assignment_or_operation(token)){
                                        // Operation is ASSIGNMENT
                                        var_name_token = token;
                                        // Check if data exists
                                        if(oof_variable_name_exists(var_name_token, data)){
                   
                                            line_token_is_assign_equal_symbol = true;

                                                var_type_token = oof_variable_type_in_current_scope(var_name_token, scope_vision, data);
                                                var_scope = oof_variable_scope_in_current_scope(var_name_token, scope_vision, data);
                  
                                        }
                                        else{
                                            std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 65_Wrong Syntax !\n";  /// 65
                                            return 0;
                                        }
                                    }
                                    else{
                                        // Operation is CON, PERIOD, SHOW
                                        if(token.compare("CON") == 0){
                                            // Operation is CON

                                            line_token_is_con_exp = true;
                                            token = "";
                                            continue;
                                        }
                                        else if(token.compare("SHOW") == 0){
                                            // Operation is SHOW

                                            line_token_is_show_exp = true;
                                            token = "";
                                            continue;
                                        }
                                        else if(token.compare("PERIOD") == 0){
                                            // Operation is PERIOD

                                            line_token_is_period_exp = true;
                                            token = "";
                                            continue;
                                        }

                                        token = "";
                                        continue;
                                    }
                                }
                            }
                            else{
                                std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 6_Wrong Syntax !\n";  /// 6
                                return 0;
                            }

                            token = "";
                            continue;
                        }
                        token += reserve_period_tokens[t];
                    }


                    period_exp_after_insert = oof_insert_values_of_con_exp(period_exp, scope_vision, data);
                    line_counter = period_lines;
                }
                
                loop_scope_counter = 0;
                period_condition = false;
                start_the_loop = false;
                line_counter += period_lines;
                reserve_period_tokens = "";
                period_tokens = "";
            }
            token = "";
            continue;
        }
        else if(pass_period_scopes){

            if(token.compare("[") == 0 || token.compare("]") == 0 || token.compare("{") == 0 || token.compare("}") == 0 || token.compare("]") == 0 || token[token.length() - 1] == ';'){
                ++line_counter;
            }
            if(token.compare("@") == 0){
                ++loop_scope_counter;
            }
            if(loop_scope_counter == 2){
                pass_period_scopes = false;
                loop_scope_counter = 0;
            }
            continue;
        }









//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////







        // PRINT the SHOW expression
        if(line_print_the_show_exp){
            if(oof_check_show_exp(show_exp, data)){

                show_exp = show_exp.erase(0,1);
                show_exp = show_exp.erase(show_exp.length() - 1,1);
                show_exp = oof_exp_variable_insert(show_exp, scope_vision, data);
                show_exp = oof_do_expression_result(show_exp);
                std::cout << "\nTHIS_IS_YOUR_COUT>>>>>>>>   " << show_exp << "    <<<<<<<\n";
                line_print_the_show_exp = false;
                show_exp = "";
            }
            else{
                std::cout << "\nWrong SHOW Operation is performed !\nError at line: " << line_counter << " ->  " << show_exp << "  <- 656_Wrong Syntax !\n";
                return 0;
            }
        }

        // Fill the Expression with token and check for PERIOD
        if(line_token_is_period_exp){
            period_exp = token;
            if(oof_check_con_exp(period_exp)){
                period_exp_after_insert = oof_insert_values_of_con_exp(period_exp, scope_vision, data);
                if(oof_give_con_exp_result(period_exp_after_insert)){
                    period_condition = true;
                    ++scope_vision;
                    period_lines = line_counter;

                }
                else{
                    pass_period_scopes = true;
                    period_exp_after_insert = "";

                }
                
                line_token_is_period_exp = false;
                ++line_counter;
                token = "";
                continue;
            }
            else{
                std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 699_Wrong Syntax !\n";
                return 0;
            }
        }
        // If the CON TRUE statement
        if(line_is_con_oper && con_checking_true_statement){
            if(con_true_statement){
                if(token.compare("[") == 0){
                    ++scope_vision;
                    ++line_counter;
                    continue;
                }
            }
            else if(con_else_statement && token.compare("]") != 0){
                if(token.compare(";") == 0 || token[token.length() - 1] == ')'){
                    ++line_counter;
                }
                if(token.compare("[") == 0 || token.compare("{") == 0 || token.compare("}") == 0){
                    ++scope_vision;
                    ++line_counter;
                }
                if(token.compare("}") == 0){
                    --scope_vision;
                    ++line_counter;
                }
                continue;
            }
            if(token.compare("]") == 0){
                con_checking_true_statement = false;
                line_is_con_oper = false;
                ++line_counter;
                --scope_vision;
                continue;
            }
        }
        
        // If the CON TRUE statement passed, check if next token is ELSE
        if(token.compare("ELSE") == 0){
            line_is_con_oper = true;
            con_checking_false_statement = true;
            ++line_counter;
            continue;
        }

        // Fill Expression with token and check the SHOW
        if(line_token_is_show_exp && token.compare("[") == 0){
            show_exp += token;
            continue;
        }
        if(line_token_is_show_exp && token[token.length() - 1] == ';'){
            show_exp += token.erase(token.length() - 1, 1);
            line_token_is_show_exp = false;
            line_print_the_show_exp = true;
            ++line_counter;
            continue;
        }
        if(line_token_is_show_exp){
            show_exp += token;
            continue;
        }

        // If There is ELSE, check the CON FALSE statement
        if(line_is_con_oper && con_checking_false_statement){
            if(con_true_statement && token.compare("]") != 0){
                if(token.compare(";") == 0 || token[token.length() - 1] == ')'){
                    ++line_counter;
                }
                if(token.compare("[") == 0 || token.compare("{") == 0){
                    ++scope_vision;
                    ++line_counter;
                }
                if(token.compare("}") == 0){
                    --scope_vision;
                    ++line_counter;
                }
                continue;
            }
            else if(con_else_statement){
                if(token.compare("[") == 0){
                    ++scope_vision;
                    ++line_counter;
                    continue;
                }
            }
            if(token.compare("]") == 0){
                con_checking_false_statement = false;
                line_is_con_oper = false;
                con_else_statement = false;
                con_true_statement = false;
                --scope_vision;
                ++line_counter;
                continue;
            }
        }

        // Fill Expression with token and check the CON
        if(line_token_is_con_exp){
            con_exp = token;
            if(oof_check_con_exp(con_exp)){
                con_exp = oof_insert_values_of_con_exp(con_exp, scope_vision, data);
                if(oof_give_con_exp_result(con_exp)){
                    con_true_statement = true;

                }
                else{
                    con_else_statement = true;

                }
                line_is_con_oper = true;
                con_checking_true_statement = true;
                line_token_is_con_exp = false;
                ++line_counter;
                token = "";
                continue;
            }
            else{
                std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 699_Wrong Syntax !\n";
                return 0;
            }
        }

        // Fill Expression with tokens for ASSIGNMENT
        if(token[token.length() - 1] == ';' && line_token_is_exp && line_is_assignment){
            exp += token.erase(token.length() - 1, 1);
            if(oof_check_expression(exp, data)){

                exp = oof_exp_variable_insert(exp, scope_vision, data);

                if(var_type_token.compare("struna") == 0){

                    if(oof_exp_result_is_struna(exp)){
                        var_value_token = oof_do_expression_result(exp);
                        data[var_scope][var_name_token][var_type_token] = var_value_token;
                    }
                    else{
                        std::cout <<"\nWrong Assignment is performed ! The expression result is not STRUNA !" 
                        <<"\nError at line: " << line_counter << " ->  " << exp << "  <- 299_Wrong Syntax !\n";
                    }
                }
                else if(var_type_token.compare("real") == 0){

                    var_value_token = oof_arithmetic_exp_operation(exp);
                    data[var_scope][var_name_token][var_type_token] = var_value_token;
                }
                else if(var_type_token.compare("dig") == 0){

                    var_value_token = oof_arithmetic_exp_operation(exp);
                    var_value_token = oof_make_dig(var_value_token);
                    data[var_scope][var_name_token][var_type_token] = var_value_token;
                }
                else if(var_type_token.compare("oz") == 0){

                    var_value_token = oof_arithmetic_exp_operation(exp);
                    var_value_token = oof_make_oz(var_value_token);
                    data[var_scope][var_name_token][var_type_token] = var_value_token;
                }

                line_token_is_exp = false;
                line_is_assignment = false;
                ++line_counter;
                exp = "";
                var_scope = 0;
                var_name_token = "";
                var_type_token = "";
                var_value_token = "";
                token = "";
                continue;
            }
            else{
                std::cout << "\nWrong Assignment is performed !\nError at line: " << line_counter << " ->  " << exp << "  <- 251_Wrong Syntax !\n";
                return 0;
            }
        }

        if(line_token_is_exp && line_is_assignment){
            exp += token;
            continue;
        }

        // Check if opening { and closing } scope
        if(token.compare("{") == 0){
            ++scope_vision;

            ++line_counter;
            data[scope_vision]["main"]["scope"] = "open";
            continue;
        }
        else if(token.compare("}") == 0){
            scope_finder = data.find(scope_vision);
            data.erase(scope_finder);
            --scope_vision;
            ++line_counter;
            continue;
        }

        // Token must be = for Assignment
        if(token.compare("=") == 0 && line_token_is_assign_equal_symbol){
            line_is_assignment = true;
            line_token_is_exp = true;
            line_token_is_assign_equal_symbol = false;
            continue;
        }

        // If Previous Token was not = for assignment
        if(line_token_is_assign_equal_symbol && !(line_is_assignment)){
            std::cout << "\nWrong Initialization is performed !\nError at line: " << line_counter << " -> " << token << " <- 211_Wrong Syntax !\n";
            return 0;
        }

        // Token must be = for initialization
        if(token.compare("=") == 0 && line_token_is_init_equal_symbol){
            line_is_declaration_initialization = true;
            line_token_is_init_equal_symbol = false;
            continue;
        }
        // If Previous Token was not = for initialization
        if(line_token_is_init_equal_symbol && !(line_is_declaration_initialization)){
            std::cout << "\nWrong Initialization is performed !\nError at line: " << line_counter << " -> " << token << " <- 2_Wrong Syntax !\n";
            return 0;
        }

        if((token[token.length() - 1] == ';') && line_is_declaration_initialization){
            // Line is Declaration With Initialization
            var_value_token = token.erase(token.length() - 1, 1);

            if(oof_variable_name_exists_in_current_scope(var_name_token, scope_vision, data)){
                        std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 1_Wrong Syntax !\n";    /// 2
                        return 0;
            }
            else{
                if(var_type_token.compare("dig") == 0 && oof_value_is_dig(var_value_token)){
                    data[scope_vision][var_name_token][var_type_token] = var_value_token;
                }
                else if(var_type_token.compare("real") == 0 && oof_value_is_real(var_value_token)){
                    data[scope_vision][var_name_token][var_type_token] = var_value_token;
                }
                else if(var_type_token.compare("struna") == 0 && oof_value_is_struna(var_value_token)){
                    data[scope_vision][var_name_token][var_type_token] = var_value_token;
                }
                else if(var_type_token.compare("oz") == 0){
                    if(oof_value_is_oz(var_value_token)){
                        data[scope_vision][var_name_token][var_type_token] = "1";
                    }
                    else{
                        data[scope_vision][var_name_token][var_type_token] = "0";
                    }
                }
                else{
                    std::cout << "\nWrong Assignment ! Types are different !\n" << "\nError at line: " 
                            << line_counter << " -> " << token << " <- 295_Wrong Syntax !\n";            /// 295
                    return 0;
                }
            }

            // Empty all tokens
            var_value_token = "";
            var_type_token = "";
            var_name_token = "";
            // Declaration With Initialization Done !
            line_is_declaration_initialization = false;
            ++line_counter;
            continue;
        }
        else if((token[token.length() - 1] == ';') && line_is_declaration){
            // Line is just Declaration
            var_name_token = token.erase(token.length() - 1, 1);
            if(oof_check_token_syntax(var_name_token)){
                // Checking Declaration syntax
                if(oof_line_can_be_declaration(var_name_token)){
                    // Checking if Variabale name already exists
                    if(oof_variable_name_exists_in_current_scope(var_name_token, scope_vision, data)){
                        std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 2_Wrong Syntax !\n";    /// 2
                        return 0;
                    }
                    else{
                        // Create Variable name in the current scope
                        if(var_type_token.compare("dig") == 0){
                            // For DIG type
                            data[scope_vision][var_name_token][var_type_token] = "0";
                        }
                        else if(var_type_token.compare("struna") == 0){
                            // for STRUNA type
                            data[scope_vision][var_name_token][var_type_token] = "<>";
                        }
                        else if(var_type_token.compare("real") == 0){
                            // for REAL type
                            data[scope_vision][var_name_token][var_type_token] = "0.0";
                        }
                        else if(var_type_token.compare("oz") == 0){
                            // for OZ type
                            data[scope_vision][var_name_token][var_type_token] = "false";
                        }
                        
                        // Empty all tokens
                        var_value_token = "";
                        var_type_token = "";
                        var_name_token = "";
                        // Declaration Done !
                        line_is_declaration = false;
                        ++line_counter;
                        continue;
                    }
                }
                else{
                    std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 3_Wrong Syntax !\n";   /// 3
                    return 0;
                }
            }
            else{
                std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 4_Wrong Syntax !\n";  /// 4
                return 0;
            }
        }
        else if(token[token.length() - 1] == ';'){
            ++line_counter;
            continue;
        }
        
        // Checking the start of the line, it's can be Declaration or Operation
        // Check if Token Syntax is ok                                           // WrongSyntax:    6   65
        if(oof_check_token_syntax(token)){
            
            // if True, line is Declaration, if False, line is Operation
            if(oof_line_is_declaration_or_operation(token)){
                
                // If Declaration
                var_type_token = token;
                // Next Token must be variable_name !
                line_is_declaration = true;
                continue;
            }
            else if(line_is_declaration){
                // Line is Declaration with Initialization
                var_name_token = token;
                line_token_is_init_equal_symbol = true;
                line_is_declaration = false;


                continue;
            }
            else{
                // Operation Logic Checking
                if(oof_line_is_assignment_or_operation(token)){
                    // Operation is ASSIGNMENT

                    var_name_token = token;

                    // Check if data exists
                    if(oof_variable_name_exists(var_name_token, data)){

                        line_token_is_assign_equal_symbol = true;

                            var_type_token = oof_variable_type_in_current_scope(var_name_token, scope_vision, data);
                            var_scope = oof_variable_scope_in_current_scope(var_name_token, scope_vision, data);
                    }
                    else{
                        std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 65_Wrong Syntax !\n";  /// 65
                        return 0;
                    }
                }
                else{
                    // Operation is CON, PERIOD, SHOW
                    if(token.compare("CON") == 0){
                        // Operation is CON
                        line_token_is_con_exp = true;
                        continue;
                    }
                    else if(token.compare("SHOW") == 0){
                        // Operation is SHOW
                        line_token_is_show_exp = true;
                        continue;
                    }
                    else if(token.compare("PERIOD") == 0){
                        // Operation is PERIOD
                        line_token_is_period_exp = true;
                        continue;
                    }
                    continue;
                }
            }
        }
        else{
            std::cout << "\nError at line: " << line_counter << " -> " << token << " <- 6_Wrong Syntax !\n";  /// 6
            return 0;
        }

    }


    std::cout << "\n\nProgram run SUCCESS !\n\n";
    return 0;
}