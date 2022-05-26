#include "ooffunctions.h"
#include <string>
#include <map>

/* 46 functions and 47th is the main.cpp, which must be updated !

data - the RAM where declared variables info is storted
token - the current string in file that is being checked
ff - means "for functions". If the function name ends with ff, means it was not used in main.cpp. It's used in some functions in ooffunctions.h

*/

// Checking the syntax of token. Token can't have @)^_&*$ symbols in it. Function will return false if the syntax is not correct, and the program will be closed !
// Token Can't start with number or Symbols. Also the token can't contain symbols too.
// Some tokens don't reach to the function like = [ ] { }
bool oof_check_token_syntax(std::string);


// Used after oof_check_token_syntax.
// In OOF SCRIPT, line is declaration or operation, function returns true if the line is DECLARATION and false if OPERATION.
// For Declaration the line starts with - dig, real, struna or oz.
// For Operation any other cases.
bool oof_line_is_declaration_or_operation(std::string);


// Used after oof_check_token_syntax.
// When the line is set to be declaration, next token must be checked if the name of the variable has KEYWORDS. Variable can't have names like: real, struna, SHOW,
// ReAl, shoW or other stuff. Returns true if syntax is ok, if the token has keywords returns false with error message.
bool oof_line_can_be_declaration(std::string);


// Used after oof_check_token_syntax.
// If the line is not DECLARATION, means it is operation. There is also two types of operation in OOF SCRIPT, line is assignment operation or other operation.
// If token has names like: SHOW, PERIOD or CON function will return false and the line is other operation. If it returns true, the line is assignment.
bool oof_line_is_assignment_or_operation(std::string);


// By Iteration, checks data, if the variable (variable_name) exists in the data.
// If doesn't exists, returns false with error message, true if it was found.
bool oof_variable_name_exists(std::string, std::map <int, std::map <std::string, std::map <std::string, std::string >>>);


// By Iteration, checks data, if the variable (variable_name) exists in current scope ({}).
/* Example: {
                dig a = 6; // a is created in first scope
                {
                    dig a = 4; // a is created in second scope, but it's not the same a like in first scope
                }
                a    // a is called in first scope, means first scope must have a. Even if in first scope a was not declared but was declared in second scope,
                     // function will return false
            }
*/
// If variable already exists, returns true with error message. Else if it doesn't exists returnse false
bool oof_variable_name_exists_in_current_scope(std::string, int, std::map <int, std::map <std::string, std::map <std::string, std::string >>>);


// By Iteration, checks data and returns the type of the variable_name in the current scope. Return is "dig", "real", "struna" or "oz". In other cases will return "". 
// The function is used or called whenever the variable_name declaration rules are passed (in main code), so it will never get to return "", 
// means it will be one of four data types.
std::string oof_variable_type_in_current_scope(std::string ,int , std::map <int, std::map <std::string, std::map <std::string, std::string >>>);


// By Iteration, checks data and returns the scope number (the scope where the variable was declared or located). Return is from 0 to infinite INT type number.
// In other cases will return 0 (which won't happen in main code).
int oof_variable_scope_in_current_scope(std::string, int, std::map <int, std::map <std::string, std::map <std::string, std::string >>>);


// Returns true if the token value type is dig, else returns false.
bool oof_value_is_dig(std::string);
// Returns true if the token value type is real, else returns false.
bool oof_value_is_real(std::string);
// Returns true if the token value type is oz, else returns false.
bool oof_value_is_oz(std::string);
// Returns true if the token value type is struna, else returns false.
bool oof_value_is_struna(std::string);


// Makes real type value into dig type. Mostly used for after doing assignment operation, when the expression value is real type, but the variable is dig type.
std::string oof_make_dig(std::string);


// Makes all types into oz type. 0.0 or 0 is going to be FALSE ("0"), all other cases will be turned into TRUE ("1")
std::string oof_make_oz(std::string);




/////////////////// EXPRESSION CHECKING FUNCTIONS start ///////////////////////////////////

// Check the expression start and end, if exp[start] and exp[end] are not < or > and contains random (#*^_!* symbol, it will return false with error message.
bool oof_check_exp_start_and_end_ff(std::string);

// Check the expression for struna, struna can't do / * - operations, returns false if it meets one of them.
// !!!!!!!!!!!!!!!!!!!!!!!!!! The funcion is not perfect yet, needs an update for better checking.
// !!!!!!!!!!!!!!!!!!!!!!!!!! Example: <alo> + b/2 is error, <al/o> + b is error  <--------------- these cases must be ignored and not return false
bool oof_check_exp_operators_for_struna_ff(std::string);

// Returns true if operator (+ - * /), other cases returns false
bool oof_check_symbol_is_operator_ff(char);

// If Expression has struna it must be opened by < and be closed by > brackets. Expression has struna if it finds <, function returns true if it found closing >
// bracket, returns false with error message if there is none.
// !!!!!!!!!!!!!!!!!!!!!!!!!! The funcion is not perfect yet, needs an update for better checking.
// !!!!!!!!!!!!!!!!!!!!!!!!!! Example: <Your_b_in_false<+b+<aloi> no error which is right, but b must not be variable, should be struna/
bool oof_check_struna_close_scope_counter_ff(std::string, int &);

// Checks number rules for dig and real. In number can't be symbols, if it finds some, will return false. Exception is dot '.' , when it counters dot one time,
// there can't be more then one dot, will return false if it finds more then 1 dots. Other cases means all is good, returns true.
bool oof_check_number_rules_ff(std::string, int &);

// Checks the rules for variable_name, the checking is about adding to var_name (in function) if the next character is ok. Means if the next character is symbol,
// like (@(%)^*! it will return false. Else variable_name is ok and returns true. Checking if the var_name exists is in other function, this function just checks
// the variable_name rules. 
bool oof_check_variable_rules_ff(std::string, std::string &, int &, bool &);

// Checks expression rules. As it has oof_check_exp_operators_for_struna_ff and oof_check_struna_close_scope_counter_ff functions, it must be updated too.
// Also the function checks data, if the variable_name in expression exists.
bool oof_check_expression(std::string, std::map <int, std::map <std::string, std::map <std::string, std::string >>>);

/////////////////// EXPRESSION CHECKING FUNCTIONS end ///////////////////////////////////




/////////////////// EXPRESSION INSERTING VARIABLES VALUES FUNCTIONS start ///////////////////////////////////

// Does the same thing as oof_variable_name_exists_in_current_scope, but it's only checking existence of the data in current scope and is used for offfunctions.h. 
// This is not the function in main.cpp which stops the program. Just the same function but without error message.
bool oof_variable_name_exists_in_current_scope_ff(std::string, int, std::map <int, std::map <std::string, std::map <std::string, std::string >>>);

// After checking expression, the next step is to insert variables values. Bur first, let's do the function for struna type and numbers. If the next token is struna or
// number or operator, just add to the new expression.
void oof_add_to_exp_new_ff(std::string, std::string &, int &);

// After checking expression, the next step is to insert variables values. When there is an character which is not starting with < and is not number, it must be variable.
// There is not need to check variable rules again, as this funcion starts it's logic after expression check. The function checks the last scope, in which the variable
// was created and adds the variable's value to the new expression.
// Example: a = 23
// <alo> + a + 34  --> after function -->  <alo>+23+32
void oof_add_to_exp_new_variable_value_ff(std::string, std::string &, int, int &, std::map <int, std::map <std::string, std::map <std::string, std::string >>>);

// Function that inserts values to the expression and returns new expression with inserted values.
// Struna or Numbers or Operators are just being added, variable_names are becoming values. Variable value will be the first met value in the current scope.
std::string oof_exp_variable_insert(std::string, int , std::map <int, std::map <std::string, std::map <std::string, std::string >>>);

/////////////////// EXPRESSION INSERTING VARIABLES VALUES FUNCTIONS end ///////////////////////////////////




/////////////////// EXPRESSION EVALUATION FUNCTIONS start ///////////////////////////////////

// Check if the expression result is struna. If there is any <, will return true, means expression's result will be struna, else false.
bool oof_exp_result_is_struna(std::string);

// Add and return the result of adding two strunas (strings), just add left part and right part together.
std::string oof_add_two_struna(std::string, std::string);

// Do the expression (evaluation) for struna and returns the result. If the result of expression is expected to be struna type, 
// this function is called and the expression is doing the operation of struna type values.
std::string oof_do_exp_for_struna(std::string);

// Simple function of number's power. Just returns num^p result in double type.
double num_power_of_10_ff(int, int);

// Real number has two parts left part (integer part) and right part (floating point part) and between them is dot '.', left part maker makes struna to double for
// integer part and right part maker makes struna to double for floating point part.
double struna_left_real_maker(std::string, int);
double struna_right_real_maker(std::string, int);

// The function returns the double type of the struna (string). std::stod could be used, but there was some issue with the correction of numbers so make_struna_to_real
// function was created.
// !!!!!!!!!!!!!!!!!!!!!!!!!! The funcion is not perfect yet, needs an update for better result.
// !!!!!!!!!!!!!!!!!!!!!!!!!! issue is that after dote you won't get correct answer. Example: If result was 23.444212132425252 you will get 23.444212 only.
double make_struna_to_real(std::string);

// Returns true if value has '.' in it, means it's real type, else returns false. Used for real type arithmetic function.
bool oof_value_is_real_ff(std::string);

// Removes 0s from right side of Real type. Example: result is 5.30000, after function -> 5.3. Also if the result is for Example: 5.00000 -> 5. adds 0 from right also
// and final result for 5.00000 is 5.0
void oof_floating_0_remove_ff(std::string);

// After taking two parts of expression for Example: a + b. a is left and b is right, the function does the operation of given operation (+ - * /) for real type numbers.
// All numbers in OOF_Script are represented as real types when doing expression. After operation, they will be always show real type result. But when expression is done
// and it's time to assign the result, the result will turn into dig, struna, oz or stay real considering to what type it was assigned to.
// Example: assigning to DIG type ->   result = 5.32 so assign will get 5, it means that 0.32 is not the part of DIG it's only for REAL TYPE
std::string oof_arithmetic_two_real(std::string, std::string, char);

// Function returns new expression, in which all * and / (muls and divs) are done and only + and - left (if there are any of them)
std::string oof_do_mul_or_div_ff(std::string);

// Function returns new expression, in which all + and - (adds and subs) are done. And this function is always called after oof_do_mul_or_div_ff. Because after this function
// there is only left one value, which is the final result of the Expression
std::string oof_do_add_or_sub_ff(std::string);

// Function returns the final result of the expression, in which all values are added, subed, muled or dived. First it does * and / and then + and -. Final result as we told
// is represented in Real type !
std::string oof_arithmetic_exp_operation(std::string);

// Checks the expression, if the expression result is struna, does operation for STRUNA types, else arithmetic operation for expression. Then it returns the final result.
std::string oof_do_expression_result(std::string);

/////////////////// EXPRESSION EVALUATION FUNCTIONS end ///////////////////////////////////




/////////////////// EXPRESSION FOR BOOLEAN start ///////////////////////////////////

// In OOF Script, you can use CON operation (which is "if" in C++). The function takes the con_expression, which must have only one of these symbols " || && <= >= < > == != ".
// The CON operation takes left side and the right side of the symols mentioned and does the boolean operation in which the result will be "1" (true) or "0" (false).
// !!!!!!!!!!!!!!!!!!!!!!!!!! The funcion is not perfect yet, needs an update for better result.
// !!!!!!!!!!!!!!!!!!!!!!!!!! Example: a||b is ok, but you can't do a || b, with spaces. a||b&&c can't do, too much symbols for boolean operation. a+b>b/c can't do, too much symbols.

// Check the expression for CON operation. Checks if the rules are ok for symbols || && <= >= < > == !=. 
// As mentioned in previous line, you can't do long line expression (chain) or use more symbols in expression, function may return wrong result or not even work.
// !!!!!!!!!!!!!!!!!!!!!!!!!! The funcion is not perfect yet, needs an update for better result.
// !!!!!!!!!!!!!!!!!!!!!!!!!! The function does not check if the variables exists in data.
bool oof_check_con_exp(std::string);

// Seperates values or variables and operation. For example a||b, after function left = a right = b oper = ||
void oof_con_exp_left_right_oper_separation_ff(std::string, std::string, std::string, std::string);

// After separation finds the left and right variables values and inserts them in to new expression with the operation symbol.
// Returns result after after inserting values from data in the current scope.
std::string oof_insert_values_of_con_exp(std::string ,int ,std::map <int, std::map <std::string, std::map <std::string, std::string >>>);

// Same as previous mentioned separation function, but for expression after insert.
void oof_con_exp_left_right_oper_separation_after_insert_ff(std::string , std::string ,std::string ,std::string);

// Do the operation for boolean expression and return the result.
bool oof_con_operation(std::string ,std::string ,std::string );

// Final boolean operation result of expression.
bool oof_give_con_exp_result(std::string exp);

/////////////////// EXPRESSION FOR BOOLEAN end ///////////////////////////////////



// SHOW operation (std::cout in C++), which checks the rules of operation (must use [ ]) and check if the variable names exist or the expression is ok,
// to complete SHOW operation.
bool oof_check_show_exp(std::string, std::map <int, std::map <std::string, std::map <std::string, std::string >>>);