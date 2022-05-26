#include <iostream>
#include <string>
#include <map>

// Not allowed to use !))%_^_#*@)(&)!%( Symbols in OOF SCRIPT ! Also, variable name must not start with NUMBER !
bool oof_check_token_syntax(std::string tok){
    
    if((tok[0] >= 65 && tok[0] <= 90) || (tok[0] >= 97 && tok[0] <= 122)){
        for(int i = 1; i < tok.length(); ++i){
            if((tok[i] >= 0 && tok[i] <= 47) || (tok[i] >= 58 && tok[i] <= 64) || (tok[i] >= 91 && tok[i] <= 96) || (tok[i] >= 123))
            {
                std::cout << "\nNot Allowed Syntax ! Can't use (@#%^_>?) SYMBOLS for types or variable_names !";
                return false;
            }
        }
    }
    else{
        std::cout << "\nNot Allowed Syntax ! Variable or Type name can't start with NUMBER or other (@#%^_>?) SYMBOLS !";
        return false;
    }

    return true;
}

// In OFF SCRIPT, line represents only 2 things, or it's an operation, or it's a declaration.
bool oof_line_is_declaration_or_operation(std::string tok){

    if(tok.compare("dig") == 0 || tok.compare("real") == 0 || tok.compare("struna") == 0 || tok.compare("oz") == 0){

        // declaration
        return true;
    }else{
        // operation
        return false;
    }
}

// Checking the rules of Declaration and Syntax
bool oof_line_can_be_declaration(std::string tok){

    for(int i = 0; i < tok.length(); ++i){
        if(tok[i] >= 65 && tok[i] <= 90){
            tok[i] += 32;
        }
    }

    if(tok.compare("dig") == 0 || tok.compare("struna") == 0 || tok.compare("real") == 0 || tok.compare("oz") == 0 ||
       tok.compare("con") == 0 || tok.compare("period") == 0 || tok.compare("show") == 0)
       {
           std::cout << "\nNot Allowed Syntax ! Can't use KEYWORDS for Variable Names !\n";
           return false;
       }

    return true;
}

// Checking the rules of Operation, if true -> line is assignment, if false -> line is operation
// PERIOD CON SHOW
bool oof_line_is_assignment_or_operation(std::string tok){

    // Check if Operation
    if(tok.compare("PERIOD") == 0 || tok.compare("CON") == 0 || tok.compare("SHOW") == 0){
        return false;
    }

    // Line is Assignment
    return true;
}

// Check if variable exists
bool oof_variable_name_exists(std::string var_name, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){

    for(auto i : d){
        for(auto j : i.second){
            if(j.first == var_name){
                return true;
            }
        }
    }

    std::cout << "\nThe Variable Name doesn't exists in data ! Can't do the Assignment !";
    return false;
}

// Checking if variable name exists in the current scope
bool oof_variable_name_exists_in_current_scope(std::string var_name, int current_scope, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){

    for(auto i : d){
        for(auto j : i.second){
            if(i.first == current_scope && j.first == var_name){
                std::cout << "\nNot Allowed Syntax ! You Can't create Variable Name with the same name that already exists !";
                return true;
            }
        }
    }

    return false;
}

// Find out the Type of the value
bool oof_value_is_dig(std::string tok){

    if((tok[0] < 48 || tok[0] > 57) && tok[0] != '-'){
        std::cout << "\nWrong DIG type initializing !";
        return false;
    }

    for(int i = 1; i < tok.length(); ++i){
        if(tok[i] < 48 || tok[i] > 57){
            std::cout << "\nWrong DIG type initializing !";
            return false;
        }
    }
    return true;
}
bool oof_value_is_real(std::string tok){

    if((tok[0] < 48 || tok[0] > 57) && tok[0] != '-'){
        std::cout << "\nWrong REAL type initializing !";
        return false;
    }

    if(tok[0] == '.' || tok[tok.length() - 1] == '.'){
        std::cout << "\nWrong REAL type initializing !";
        return false;
    }

    int dot_counter = 0;

    for(int i = 1; i < tok.length(); ++i){
        if((tok[i] < 48 || tok[i] > 57) && tok[i] != '.'){
            std::cout << "\nWrong REAL type initializing !";
            return false;
        }
        else if(tok[i] == '.'){
            ++dot_counter;
        }

        if(dot_counter > 1){
            std::cout << "\nWrong REAL type initializing !";
            return false;
        }
    }

    if(dot_counter == 0){
        std::cout << "\nWrong REAL type initializing !";
        return false;
    }

    return true;
}
bool oof_value_is_oz(std::string tok){
    if(tok.compare("false") == 0 || tok.compare("0") == 0){
        return false;
    }

    return true;
}
bool oof_value_is_struna(std::string tok){
    if(tok[0] == '<' && tok[tok.length() - 1] == '>' ){
        return true;
    }

    std::cout << "\nWrong STRUNA type initializing !";
    return false;
}

// Return DIG from REAL
std::string oof_make_dig(std::string val){
    
    std::string new_val = "";

    for(int i = 0; i < val.length(); ++i){
        if(val[i] == '.'){
            break;
        }
        new_val += val[i];
    }
    return new_val;
}

// Return OZ from REAL
std::string oof_make_oz(std::string val){
    std::string new_val = "0";
    
    for(int i = 0; i < val.length(); ++i){
        if(val[i] == '.'){
            continue;
        }
        if(val[i] != '0'){
            new_val = "1";
            break;
        }
    }
    return new_val;
}

// Return Type of Variable in the current scope
std::string oof_variable_type_in_current_scope(std::string var_name, int current_scope, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){
    
    for(int s = current_scope; s >= 0; --s){
        for(auto i : d){
            if(i.first == s){
                for(auto j : i.second){
                    if(j.first.compare(var_name) == 0){
                        for(auto k : j.second){
                            return k.first;
                        }
                    }
                }
            }
        }
    }

    return "";
}

// Return the scope number of the first met variable_name
int oof_variable_scope_in_current_scope(std::string var_name, int current_scope, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d)
{
    for(int s = current_scope; s >= 0; --s){
        for(auto i : d){
            if(i.first == s){
                for(auto j : i.second){
                    if(j.first.compare(var_name) == 0){
                        return s;
                    }
                }
            }
        }
    }

    return 0;
}

// Check the start and the end of EXPRESSION
bool oof_check_exp_start_and_end_ff(std::string exp){
    if(exp[0] != '<' && exp[exp.length() - 1] != '>'){
        if((exp[0] >= 0 && exp[0] <= 47) || (exp[0] >= 58 && exp[0] <= 64) || (exp[0] >= 91 && exp[0] <= 96) || (exp[0] >= 123) ||
           (exp[exp.length() - 1] >= 0 && exp[exp.length() - 1] <= 47) || (exp[exp.length() - 1] >= 58 && exp[exp.length() - 1] <= 64) 
           || (exp[exp.length() - 1] >= 91 && exp[exp.length() - 1] <= 96) || (exp[exp.length() - 1] >= 123))
        {
            std::cout << "\n97__Expression has unacceptable Symbols ! Can't do the OPERATION !";
            return false;
        }
    }
    return true;
}

// Check operators for struna EXPRESSION
bool oof_check_exp_operators_for_struna_ff(std::string exp){
    bool exp_has_struna = false;
    for(int i = 0; i < exp.length(); ++i){
        if(exp_has_struna && (exp[i] == '-' || exp[i] == '/' || exp[i] == '*')){
            std::cout << "\n45__Expression has unacceptable OPERATORS for STRUNA Type ! Can't do the OPERATION !";
            return false;
        }
        if(exp[i] == '<' && !(exp_has_struna)){
            exp_has_struna = true;
            i = 0;
        }
    }
    return true;
}

// Check if next symbol is not operator
bool oof_check_symbol_is_operator_ff(char symbol){

    if(symbol == '+' || symbol == '-' || symbol == '/' || symbol == '*'){
        return true;
    }

    return false;
}

// Check closing scopes
bool oof_check_struna_close_scope_counter_ff(std::string exp, int &index){
    int struna_scopes = 1;
    for(int j = index + 1; j < exp.length(); ++j){
        if(exp[j] == '>'){
            ++struna_scopes;
            index = j;
            break;
        }
    }
    if(struna_scopes == 1){
        std::cout << "\n7__Expression has unacceptable Symbols ! There is no CLOSING > bracket for STRUNA type. Can't do the OPERATION !";
        return false;
    }
    return true;
}

// Check rules for numbers real and dig
bool oof_check_number_rules_ff(std::string exp, int &index){
    int dot_counter = 0;
    for(int k = index + 1; k < exp.length(); ++k){
        if(oof_check_symbol_is_operator_ff(exp[k])){
            index = k;
            break;
        }
        if(exp[k] == '.'){
            ++dot_counter;
            continue;
        }
        if(exp[k] < 48 || exp[k] > 57){
            std::cout << "\n55__Expression has unacceptable Symbols ! Number value can have NUMBERS or DOT only. Can't do the OPERATION !";
            return false;
        }
    }
    if(dot_counter > 1){
        std::cout << "\n1__Expression has unacceptable Symbols ! Wrong expression for REAL type numbers, too many dots. Can't do the OPERATION !";
        return false;
    }
    return true;
}

// Checks rules for variable_names
bool oof_check_variable_rules_ff(std::string exp, std::string &name, int &index, bool &l_char){
    for(int l = index + 1; l < exp.length(); ++l){
        //        std::cout << "\nvar_name:  " << var_name << " <--- 2";
        if(oof_check_symbol_is_operator_ff(exp[l])){
            index = l;
            break;
        }
        if(!((exp[l] >= 65 && exp[l] <= 90) || (exp[l] >= 97 && exp[l] <= 122))){
            std::cout << "\n0__Expression has unacceptable Symbols ! Variable_name has unacceptable @(_%*& symbsols. Can't do the OPERATION !";
            return false;
        }
        if(l == exp.length() - 1){
            l_char = true;
        }
        name += exp[l];
    }
    return true;
}

// Check if EXPRESSION is ok
bool oof_check_expression(std::string exp, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){
    
    if(!(oof_check_exp_start_and_end_ff(exp))){
        return false;
    }

    bool exp_has_struna = false;
    bool argument_struna = false;
    bool next_cant_be_operator = true;
    bool last_char = false;

    std::string var_name = "";

    if(!(oof_check_exp_operators_for_struna_ff(exp))){
        return false;
    }

    for(int i = 0; i < exp.length(); ++i){

    //    std::cout << "\nCurrent Symb:  " << exp[i];

        // Check if next symbol is not OPERATOR
        if(next_cant_be_operator && oof_check_symbol_is_operator_ff(exp[i])){
            std::cout << "\n3__Expression has unacceptable OPERATORS Order ! Can't do the OPERATION !";
            return false;
        }

        // Current Symbol is not Operator
        next_cant_be_operator = false;

        // Check Operators for STRUNA
        if(argument_struna && exp_has_struna){
            if(exp[i] == '+'){
                argument_struna = false;
                next_cant_be_operator = true;
                continue;
            }
            else{
                std::cout << "\n4__Expression has unacceptable OPERATORS for STRUNA Type ! Can't do the OPERATION !";
                return false;
            }
        }
    
        if(exp[i] == '>'){
            std::cout << "\n9__Expression has unacceptable Symbols ! Can't do the OPERATION !";
            return false;
        }
        else if(exp[i] == '<'){
            exp_has_struna = true;
            argument_struna = true;
            if(!(oof_check_struna_close_scope_counter_ff(exp, i))){
                return false;
            }
        }
        
        if(exp[i] >= 48 && exp[i] <= 57){
            if(oof_check_number_rules_ff(exp, i)){
                next_cant_be_operator = true;
            }
            else{
                return false;
            }
        }
        
        if((exp[i] >= 65 && exp[i] <= 90) || (exp[i] >= 97 && exp[i] <= 122)){
            var_name += exp[i];
        //    std::cout << "\nvar_name:  " << var_name << " <--- 1";
            if(!(oof_check_variable_rules_ff(exp, var_name, i, last_char))){
                return false;
            }
  //          std::cout << "\n                        " << var_name << "\n";
            if(oof_variable_name_exists(var_name, d)){
        //        std::cout << "\nvar_name:  " << var_name << " <--- 3";
                var_name = "";
            }
            else{
                std::cout << "\n66__Expression has not DECLARED Variables ! Can't do the OPERATION !";
                return false;
            }
            next_cant_be_operator = true;
        }
        if(last_char){
            break;
        }
    }

    return true;
}

// Check if variable name exists in the scope but for OFFFFUNCTIONS.H
bool oof_variable_name_exists_in_current_scope_ff(std::string var_name, int current_scope, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){

    for(auto i : d){
        for(auto j : i.second){
            if(i.first == current_scope && j.first == var_name){
                return true;
            }
        }
    }

    return false;
}

// Add to new_exp the character if it's not variable_name
void oof_add_to_exp_new_ff(std::string exp, std::string &exp_new, int &index){
    for(int j = index; j < exp.length(); ++j){
      //     std::cout << "\nI am here ->   2";
        exp_new += exp[j];
        if(exp[j] == '+' || exp[j] == '-' || exp[j] == '*' || exp[j] == '/'){
            index = j;
            break;
        }
        if(j == exp.length() - 1){
            index = j;
            break;
        }
    }
}

// Add to new_exp variable_name's value
void oof_add_to_exp_new_variable_value_ff(std::string exp, std::string &exp_new, int current_scope, int &index, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){

    bool data_found = false;
    bool val_found = false;

    std::string val_name = "";
    std::string temp = "";
    std::string var_type = "";
    
    //     std::cout << "\nI am here ->   4";
            for(int l = index; l < exp.length(); ++l){
                if(exp[l] == '+' || exp[l] == '-' || exp[l] == '*' || exp[l] == '/'){
                    temp = exp[l];
                    val_found = true;
        //            std::cout << "\nI am here ->   41";
         //           std::cout << "\nNAME: " << val_name;
                    index = l;
                }
                if(l == exp.length() - 1){
                    val_name += exp[l];
                    val_found = true;
         //           std::cout << "\nI am here ->   42";
         //           std::cout << "\nNAME: " << val_name;
                    index = l;
                }
                if(val_found){
         //           std::cout << "\nI am here ->   43";
                    val_found = false;
                    for(int s = current_scope; s >= 0; --s){
                        if(oof_variable_name_exists_in_current_scope_ff(val_name, s, d)){
                            var_type = oof_variable_type_in_current_scope(val_name, s, d);
                            val_name = d[s][val_name][var_type]; // value
                            data_found = true;
                        }
                        if(data_found){
                            data_found = false;
                            break;
                        }
                    }
                    break;
                }
                val_name += exp[l];
            }
            exp_new += val_name;
            exp_new += temp;
     //       std::cout << "\nexp_new: " << exp_new;
}

// Change EXPRESSION with Inserted data of the variable names
std::string oof_exp_variable_insert( std::string exp, int current_scope, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){

    std::string exp_new = "";

    for(int i = 0; i < exp.length(); ++i){

   //     std::cout << "\nexp_new: " << exp_new << "   exp " << i << " = " << exp[i];
        
        if(exp[i] == '<' || (exp[i] >= 48 && exp[i] <= 57)){
            oof_add_to_exp_new_ff(exp, exp_new, i);
        }

        // Find the first met data of the value_name
        if((exp[i] >= 65 && exp[i] <= 90) || (exp[i] >= 97 && exp[i] <= 122)){
            oof_add_to_exp_new_variable_value_ff(exp, exp_new, current_scope, i, d);
        }
    }

    return exp_new;
}

// If the expression result must be STRUNA type
bool oof_exp_result_is_struna(std::string exp){
    for(int i = 0; i < exp.length(); ++i){
        if(exp[i] == '<'){
            return true;
        }
    }

    return false;
}

// Add two STRUNAS
std::string oof_add_two_struna(std::string l, std::string r){

    std::string result = "";
    std::string left = l.erase(l.length() - 1, 1);
    std::string right = "";
    if(r[0] == '<'){
        right = r.erase(0, 1);
        right = r.erase(r.length() - 1, 1);
    }
    right = r;

    result = left + right + ">";

    return result;
}

// Do the expression for STRUNA
std::string oof_do_exp_for_struna(std::string exp){

    std::string reserve = exp;
    std::string temp = "";
    std::string left = "";
    std::string right = "";

    int left_start = 0;
    int right_end = 0;

    bool add_to_right = false;
    bool adding_done = false;

    for(int i = 0; i < reserve.length(); ++i){
   //     std::cout << "\nleft::   " << left;
   //     std::cout << "\nright::   " << right;
        if(add_to_right && (reserve[i] == '+' || i == reserve.length() - 1)){
            
            adding_done = true;
            if(i == reserve.length() - 1){
                right += reserve[i];
            }

   //         std::cout << "\noperation::left::  " << left;
   //         std::cout << "\noperation::right::  " << right;
            right_end = i;
            reserve = reserve.erase(left_start, right_end);
   //         std::cout << "\noperation::reserve::  " << reserve << " |";
            temp = oof_add_two_struna(left, right);
   //         std::cout << "\noperation::temp::  " << temp << " |";
            temp += reserve;
   //         std::cout <<"\noperation::temp::after:: " << temp << " |";
            reserve = temp;
   //         std::cout <<"\noperation::reserve::after:: " << reserve << " |";
            temp = "";
            left = "";
            right = "";
            i = -1;
            int left_start = 0;
            int right_end = 0;
            add_to_right = false;
        }
        if(add_to_right){
            right += reserve[i];
        }
        else{
            left += reserve[i];
        }
        if(reserve[i] == '>' && !(add_to_right)){
            add_to_right = true;
            ++i;
        }
    }
    
    if(adding_done){
        reserve = reserve.erase(reserve.length() - 1, 1);
    }
    return reserve;
}

// number power for 10
double num_power_of_10_ff(int num, int p){
    double sum = num;

    if( p == 0){
        return sum;
    }
    else if(p > 0){
        for(int i = 1; i < p; ++i){
            sum = sum * 10;
        }
    }

    return sum;
}

// Real number's left part maker
double struna_left_real_maker(std::string r, int counter){

    std::string temp = "";

    double left = 0;
    double num = 0;

    for(int i = 0; i < r.length(); ++i){
        if(r[i] == '.'){
            break;
        }

        temp += r[i];
  //      std::cout << "\ntemp:: " << temp;
        num = std::stod(temp);
  //      std::cout << "\nnum:: " << num;
        left += num_power_of_10_ff(num, counter);
  //      std::cout << "\nleft:: " << left;
        --counter;
  //      std::cout << "\nleft_counter:: " << counter_left;
        temp = "";
    }

    return left;
}

// Real number's right part maker
double struna_right_real_maker(std::string r, int counter){

    double right = 0;
    double num = 0;

    std::string temp = "";

    for(int i = r.length() - 1; i >= 0; --i){
        if(r[i] == '.'){
            break;
        }

        temp += r[i];
  //      std::cout << "\ntemp:: " << temp;
        num = std::stod(temp);
  //      std::cout << "\nnum:: " << num;
        // 0.342
        right += num/num_power_of_10_ff(10, counter - 1);
 //       std::cout << "\nright:: " << right;
        --counter;
  //      std::cout << "\nright_counter:: " << counter_right;
        temp = "";
    }

    return right;
}

// Make string to real
double make_struna_to_real(std::string r){

    std::string real = r;
//    std::cout << "\nMAKING REAL_______________ " << r << "\n";
    double result;

    int counter_left = 0;
    int counter_right = 0;

    bool dot_met = false;

    for(int i = 0; i < r.length(); ++i){
        if(r[i] == '.'){
            dot_met = true;
        }
        if(dot_met){
            ++counter_right;
        }
        else{
            ++counter_left;
        }
    }

 //   std::cout << "\ncounter_left_____ " << counter_left;
 //   std::cout << "\ncounter_right_____ " << counter_right;

    double left = struna_left_real_maker(r, counter_left);
    double right = struna_right_real_maker(r, counter_right);
    
    result = left + right;

 //   std::cout << "\nresult::____ " << result;

    return result;
}

// Returns true if the value has . (means it's real type)
bool oof_value_is_real_ff(std::string val){
    for(int i = 0; i < val.length(); ++i){
        if(val[i] == '.'){
            return true;
        }
    }
    return false;
}

// Remove 0s from right side of real type
void oof_floating_0_remove_ff(std::string &val){
    int float_point_counter = 0;
    for(int i = val.length() - 1; i >= 0; --i){
        if(val[i] != '0'){
            val = val.erase(i + 1, float_point_counter);
            break;
        }
        ++float_point_counter;
    }

    if(val[val.length() - 1] == '.'){
        val += "0";
    }
}

// Operation for two REALS (can be for DIG and OZ too)
std::string oof_arithmetic_two_real(std::string l, std::string r, char oper){
    
    std::string left = l;
    std::string right = r;

    double result;

    bool left_is_real = oof_value_is_real_ff(l);
    bool right_is_real = oof_value_is_real_ff(r);

    if(left_is_real && right_is_real){
   //     std::cout << "\nIam55\n";
       switch(oper){
           case '+':
           result = make_struna_to_real(left) + make_struna_to_real(right);
           break;
           case '-':
           result = make_struna_to_real(left) - make_struna_to_real(right);
           break;
           case '/':
           result = make_struna_to_real(left) / make_struna_to_real(right);
           break;
           case '*':
           result = make_struna_to_real(left) * make_struna_to_real(right);
           break;
        }
    }
    else if(left_is_real){
   //     std::cout << "\nIam66\n";
        switch(oper){
           case '+':
           result = make_struna_to_real(left) + std::stod(right);
           break;
           case '-':
           result = make_struna_to_real(left) - std::stod(right);
           break;
           case '/':
           result = make_struna_to_real(left) / std::stod(right);
           break;
           case '*':
           result = make_struna_to_real(left) * std::stod(right);
           break;
        }
    }
    else if(right_is_real){
  //      std::cout << "\nIam77\n";
        switch(oper){
           case '+':
           result = std::stod(left) + make_struna_to_real(right);
           break;
           case '-':
           result = std::stod(left) - make_struna_to_real(right);
           break;
           case '/':
           result = std::stod(left) / make_struna_to_real(right);
           break;
           case '*':
           result = std::stod(left) * make_struna_to_real(right);
           break;
        }
    }
    else{
  //      std::cout << "\nIam88\n";
        switch(oper){
           case '+':
           result = std::stod(left) + std::stod(right);
           break;
           case '-':
           result = std::stod(left) - std::stod(right);
           break;
           case '/':
           result = std::stod(left) / std::stod(right);
           break;
           case '*':
           result = std::stod(left) * std::stod(right);
           break;
        }
    }
    
    std::string str_result = std::to_string(result);

    oof_floating_0_remove_ff(str_result);

    return str_result;
}

// Do * and / in expression
std::string oof_do_mul_or_div_ff(std::string exp){

    std::string reserve = exp;
    std::string reserve_left = "";
    std::string reserve_right = "";
    std::string temp = "";
    std::string left = "";
    std::string right = "";

    char oper;

    int left_start = 0;
    int right_end = 0;

    bool add_to_right = false;

    for(int i = 0; i < reserve.length(); ++i){
      //  std::cout << "\nleft::   " << left;
     //   std::cout << "\nright::   " << right;

        if((reserve[i] == '+' || reserve[i] == '-' || reserve[i] == '*' || reserve[i] == '/' || i == reserve.length() - 1) && add_to_right){
            
            if(i == reserve.length() - 1){
                right += reserve[i];
            }

            right_end = i;
       //     std::cout << "\nleft_start:: " << left_start;
       //     std::cout << "\nright_end:: " << right_end;
       //     std::cout << "\noperation::left::  " << left;
       //     std::cout << "\noperation::right::  " << right;
       //     std::cout << "\noper: " << oper << "\n";

            if(i == reserve.length() - 1){
                reserve_right = "";
            }
            else{
                reserve_right = reserve.erase(0, right_end);
            }
            
         //   std::cout << "\noperation::reserve_right:: " << reserve_right << " |";
       //     std::cout << "\noperation::reserve_left:: " << reserve_left << " |";

            reserve = left + oper + right;
       //     std::cout << "\noperation::reserve::  " << reserve << " |";

            temp = oof_arithmetic_two_real(left, right, oper);
      //      std::cout << "\noperation::temp::  " << temp << " |";
            reserve = reserve_left;
            reserve += temp;
            reserve += reserve_right;
       //     std::cout <<"\noperation::reserve::after:: " << reserve << " |\n";
            i = 0;
            reserve_left = "";
            reserve_right = "";
            left_start = 0;
            right_end = 0;
            left = "";
            right = "";
            temp = "";
            add_to_right = false;
        }

        if(reserve[i] == '+' || reserve[i] == '-'){
            left += reserve[i];
            reserve_left += left;
            left = "";
            left_start = 0;
            continue;
        }

        if((reserve[i] == '*' || reserve[i] == '/') && !(add_to_right)){
            add_to_right = true;
            oper = reserve[i];
            right_end = left_start;
            left_start = i - left_start;
            continue;
        }

        if(add_to_right){
            right += reserve[i];
            ++right_end;
        }
        else{
            left += reserve[i];
            ++left_start;
        }

    }

    return reserve;
}

// Do + and - in epxression
std::string oof_do_add_or_sub_ff(std::string exp){

    std::string reserve = exp;
    std::string reserve_left = "";
    std::string reserve_right = "";
    std::string temp = "";
    std::string left = "";
    std::string right = "";
    
    char oper;

    int left_start = 0;
    int right_end = 0;

    bool add_to_right = false;

    for(int i = 0; i < reserve.length(); ++i){
   //     std::cout << "\nleft::   " << left;
   //     std::cout << "\nright::   " << right;

        if((reserve[i] == '+' || reserve[i] == '-') && !(add_to_right)){
            add_to_right = true;
            oper = reserve[i];
            right_end = left_start;
            left_start = i - left_start;
            continue;
        }

        if((reserve[i] == '+' || reserve[i] == '-' || i == reserve.length() - 1) && add_to_right){
            
            if(i == reserve.length() - 1){
                right += reserve[i];
            }

            right_end = i;
    //        std::cout << "\nleft_start:: " << left_start;
    //        std::cout << "\nright_end:: " << right_end;
    //        std::cout << "\noperation::left::  " << left;
    //        std::cout << "\noperation::right::  " << right;
    //        std::cout << "\noper: " << oper << "\n";

            if(i == reserve.length() - 1){
                reserve_right = "";
            }
            else{
                reserve_right = reserve.erase(0, right_end);
            }
            
      //      std::cout << "\noperation::reserve_right:: " << reserve_right << " |";
     //       std::cout << "\noperation::reserve_left:: " << reserve_left << " |";

            reserve = left + oper + right;
     //       std::cout << "\noperation::reserve::  " << reserve << " |";

            temp = oof_arithmetic_two_real(left, right, oper);
    //        std::cout << "\noperation::temp::  " << temp << " |";
            reserve = reserve_left;
            reserve += temp;
            reserve += reserve_right;
     //       std::cout <<"\noperation::reserve::after:: " << reserve << " |\n";
            i = 0;
            reserve_left = "";
            reserve_right = "";
            left_start = 0;
            right_end = 0;
            left = "";
            right = "";
            temp = "";
            add_to_right = false;
        }

        if(add_to_right){
            right += reserve[i];
            ++right_end;
        }
        else{
            left += reserve[i];
            ++left_start;
        }

    }

    return reserve;
}

// Do the expression for REAL
std::string oof_arithmetic_exp_operation(std::string exp){

    std::string reserve = exp;

    // First do * and /
    reserve = oof_do_mul_or_div_ff(reserve);
    
    // Then do + and -
    reserve = oof_do_add_or_sub_ff(reserve);

    return reserve;
}

// Complete the EXPRESSION
std::string oof_do_expression_result(std::string exp){

    std::string new_exp = exp;

    if(oof_exp_result_is_struna(exp)){
        // result is STRUNA
        new_exp = oof_do_exp_for_struna(exp);
    }
    else{
        // result for REAL, DIG, OZ
        new_exp = oof_arithmetic_exp_operation(exp);
    }

    return new_exp;
}

// Boolean EXPRESSION
bool oof_check_con_exp(std::string exp){

    if(exp[0] != '(' && exp[0] != ')'){
        std::cout << "\nWront Syntax for CON operation ! Can't check the condition !\n";
        return false;
    }

    // Check for || && < > <= >= == !=
    for(int i = 1; i < exp.length() - 1; ++i){
        if(exp[i] == '|'){
            if(exp[i + 1] != '|'){
                std::cout << "\n2.3_Wrong CON expression ! Can't check the condition !\n";
                return false;
            }
            ++i;
        }
        if(exp[i] == '&'){
            if(exp[i + 1] != '&'){
                std::cout << "\n2.1_Wrong CON expression ! Can't check the condition !\n";
                return false;
            }
            ++i;
        }
        /* must be updated !
        if(exp[i] == '=' && (exp[i-1] != '<' || exp[i-1] != '>')){
            if(exp[i + 1] != '='){
                std::cout << "\n2.2_Wrong CON expression ! Can't check the condition !\n";
                return false;
            }
            ++i;
        }
        */
        if(exp[i] == '!'){
            if(exp[i + 1] != '='){
                std::cout << "\n2.4_Wrong CON expression ! Can't check the condition !\n";
                return false;
            }
            ++i;
        }
    }
    
    return true;
}

// Separate left, right and operation_symbol
void oof_con_exp_left_right_oper_separation_ff(std::string exp, std::string &left, std::string &right, std::string &oper){

    bool add_to_right = false;

    for(int i = 1; i < exp.length() - 1; ++i){

 //       std::cout << "\nleft:: " << left;
 //       std::cout << "\nright:: " << left;

        if(exp[i] == '|' || exp[i] == '&' || exp[i] == '!' || exp[i] == '='){
            oper += exp[i];
            oper += exp[i+1];
 //           std::cout << "\noperator:: " << oper;
            add_to_right = true;
            ++i;
            continue;
        }

        if(exp[i] == '>' || exp[i] == '<'){
            oper += exp[i];
            if(exp[i+1] == '='){
                oper += exp[i + 1];
                ++i;
            }
  //          std::cout << "\noperator:: " << oper;
            add_to_right = true;
            continue;
        }

        if(add_to_right){
            right += exp[i];
        }
        else{
            left += exp[i];
        }
    }
}

// Insert variable values for expression
std::string oof_insert_values_of_con_exp(std::string exp, int current_scope, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){

    std::string res = exp;
    std::string left = "";
    std::string right = "";
    std::string left_type = "";
    std::string right_type = "";
    std::string oper = "";

    oof_con_exp_left_right_oper_separation_ff(res, left, right, oper);

    bool data_found_left = false;
    bool data_found_right = false;

 //   std::cout << "\nleft::after " << left;
 //   std::cout << "\nright::after " << right;
 //   std::cout << "\noper:: " << oper;

    for(int s = current_scope; s >= 0; --s){
        if(oof_variable_name_exists_in_current_scope_ff(left, s, d) && !(data_found_left)){
            left_type = oof_variable_type_in_current_scope(left, s, d);
            left = d[s][left][left_type]; // value
            data_found_left= true;
        }

        if(oof_variable_name_exists_in_current_scope_ff(right, s, d) && !(data_found_right)){
            right_type = oof_variable_type_in_current_scope(right, s, d);
            right = d[s][right][right_type]; // value
            data_found_right= true;
        }
    }

    res = "";
    res += left + oper + right;

    return res;
}

// Separate left, right and operation_symbol after insert
void oof_con_exp_left_right_oper_separation_after_insert_ff(std::string exp, std::string &left, std::string &right, std::string &oper){

    bool add_to_right = false;

    for(int i = 0; i < exp.length(); ++i){

 //       std::cout << "\nleft:: " << left;
 //       std::cout << "\nright:: " << left;

        if(exp[i] == '|' || exp[i] == '&' || exp[i] == '!' || exp[i] == '='){
            oper += exp[i];
            oper += exp[i+1];
 //           std::cout << "\noperator:: " << oper;
            add_to_right = true;
            ++i;
            continue;
        }

        if(exp[i] == '>' || exp[i] == '<'){
            oper += exp[i];
            if(exp[i+1] == '='){
                oper += exp[i + 1];
                ++i;
            }
  //          std::cout << "\noperator:: " << oper;
            add_to_right = true;
            continue;
        }

        if(add_to_right){
            right += exp[i];
        }
        else{
            left += exp[i];
        }
    }
}

// Result of boolean operation
bool oof_con_operation(std::string l, std::string r, std::string oper){

    std::string result = "";
    std::string left = l;
    std::string right = r;
    
    // || && < > <= >= == !=
    if(l[0] == '<' || r[r.length() - 1] == '>'){
        if(oper.compare("||") == 0){
            return true;
        }
        else if(oper.compare("&&") == 0){
            return true;
        }
        else if(oper.compare("<=") == 0){
            if(l.length() <= r.length() || l.compare(r) == 0){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare(">=") == 0){
            if((l.length() >= r.length()) || l.compare(r) == 0){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare("!=") == 0){
            if(l.compare(r) != 0){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare("==") == 0){
            if(l.compare(r) == 0){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare("<") == 0){
            if(l.length() < r.length()){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare(">") == 0){
            if(l.length() > r.length()){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return true;
        }
    }
    else{

        bool l_val_real = false;
        bool r_val_real = false;

  //      std::cout << "\nI AM HERE_____\n";

        for(int i = 0; i < l.length(); ++i){
            if(l[i] == '.'){
                l_val_real = true;
                break;
            }
        }
        for(int i = 0; i < r.length(); ++i){
            if(r[i] == '.'){
                r_val_real = true;
                break;
            }
        }

        double l_val;
        double r_val;

        if(l_val_real){
            l_val = make_struna_to_real(l);
        }
        else{
            l_val = std::stod(l);
        }
        
        if(r_val_real){
            r_val = make_struna_to_real(r);
        }
        else{
            r_val = std::stod(r);
        }

 //       std::cout << "\nleft_val:: " << l_val;
  //      std::cout << "\nright_val:: " << r_val;

        if(oper.compare("||") == 0){
            if((l.compare("0") == 0 || l.compare("0.0") == 0) && (r.compare("0") == 0 || r.compare("0.0") == 0))
            {
                return false;
            }
            else{
                return true;
            }
        }
        else if(oper.compare("&&") == 0){
            if((l.compare("0") == 0 || l.compare("0.0") == 0) || (r.compare("0") == 0 || r.compare("0.0") == 0))
            {
                return false;
            }
            else{
                return true;
            }
        }
        else if(oper.compare("<=") == 0){
            if(l_val <= r_val){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare(">=") == 0){
            if(l_val >= r_val){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare("!=") == 0){
            if(l_val != r_val){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare("==") == 0){
            if(l_val == r_val){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare("<") == 0){
            if(l_val < r_val){
                return true;
            }
            else{
                return false;
            }
        }
        else if(oper.compare(">") == 0){
            if(l_val > r_val){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return true;
        }
    }
}

// Final result for expression
bool oof_give_con_exp_result(std::string exp){

    std::string res = exp;
    std::string left = "";
    std::string right = "";
    std::string oper = "";

    bool result = false;

    oof_con_exp_left_right_oper_separation_after_insert_ff(res, left, right, oper);
 //   std::cout << "\nleft::after " << left;
//   std::cout << "\nright::after " << right;
 //   std::cout << "\noper:: " << oper;
//    std::cout << "\n-----------------------------------------------------\n";
    result = oof_con_operation(left, right, oper);
    
    return result;
}

// Show [expresison]
bool oof_check_show_exp(std::string exp, std::map <int, std::map <std::string, std::map <std::string, std::string >>> d){
    if(exp[0] != '[' && exp[exp.length() - 1] != ']'){
        std::cout << "\nExpression in SHOW operation doesn't start with [ or end with ] !";
        return false;
    }

    std::string res = "";
    res = exp.erase(0,1);
    res = res.erase(res.length() - 1, 1);

    if(oof_check_expression(res, d)){
        return true;
    }
    else{
        std::cout << "\nWrong Syntax for SHOW operation !\n";
        return false;
    }

    return true;
}