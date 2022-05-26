OOF-Script
Interpretator

<h4>Introduction</h4>
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
OOF-Script is an interpretator which has some several commands needed to do some programming task. It's not a perfect interpretator yet, it has some borders and rules that can't be passed or be ignored as we would like to do in other advanced languages. There are functions which needs a little update or adjustment too, so the program will run or do additional tasks without any issues. OOF-Script provides function prototypes, where functions descriptions are represented too.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------


<h4>Key Words</h4>
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
Data types like: dig (int), real (float), struna (string) and oz (bool).

Operation/Commands: + - * /, CON/ELSE (if/else), SHOW (cout), PERIOD (while).
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------


<h4>Using Rules</h4>
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
You must open txt file and put it in the same folder where the main.cpp with hpp files is placed. The name of txt file must be "testing.txt" or you can change it by going into the main.cpp code. Aftering writing code (Which must follow rules of OOF Script), run main.cpp and see results in (THIS_IS_YOUR_COUT >>>> <<<<) field.
 
 
 
The start of the program must always start with '{' opening scope and end with '}' closing scope. After opening the code field you can use {} wherever you want and also they will work like they do in other advanced languages, they show and make border for vision fields of your code, means if you want to reach data from other scope in the code, you will get an error, as it's out of the vision. Example:
{
  dig a = 10;
  {
    dig b = 15;
  }
  a = b; // ERROR, b is not visible on this field.
}


You can declare type or declared with initialization (when initializing, you can't do expression initializing or multiple declarations) Example:
{
  dig a;
  real b = 5.5;
  dig a1, a2, a3; // ERROR
  real c = a + b; // ERROR
}

You can do assigning operation and use chain operations too, but opening ( and ) closing brackets are not supported yet, which must be updated Example:
{
  dig a = 5;
  a = 6;
  a = 10 + 2/5 * 4;
  real b;
  b = a/10 + 23*0.4;
}

Strings are supported too.
{
  struna d = "hell";
  d = d + "o";
}

By the way, there is no ' ' space symbol in Interpretator, so for space symbol use '_' this, to avoid errors.




You can use SHOW operation which is cout << in C++. You must have space between brackets and write expression or text (in <> brackets) in [] scopes Example:
{
  SHOW [<hello>];
  SHOW[<hello>]; // ERROR
}

Chain expressions are supported too Example:
{
  SHOW [a+b/2];
  SHOW [<This_is_your_number> a];
}
  
  
  
You can use CON operation which is condition if in C++. You can't have chain operation in opening and closing () scopes, only one expression with boolean operations.
After CON you must always continue with space and write the code jointly in brackets Example:
CON (a>b) // OK
CON(a>b) // ERROR
CON ( a > b ) // ERROR

After expression you must start a new line with opening and closing scopes [] Example:
CON (a>b)
[
  // Code
]

You can also use ELSE operation too after CON operation, ELSE will work if the statement in CON operation is false Example:
CON (a>b)
[
  // Code
]
ELSE
[
  // Code
]
  
  
  
You can use PERIOD opretaion which is while() in C++. The rules are totaly same as the CON, except you must use @ @ brackets instead Example:
PERIOD (a>b)
@
  // Code
@
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  <h4>Hope you will appreciate the program, it's not the best and not usable I know, but at least you can do something in it :)</h4>
