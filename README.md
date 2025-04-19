# Project Magic

Magic is a simple programming object-oriented language

## Grammar

### Main definitions

```txt
program = class_declaration

class_declaration = "class" identifier class_body;

class_body = "{" attribute_declarations constructor method_declarations "}";
```

### Constructors declarations

```txt
constructor_declaration = constructor_signature constructor_body;

constructor_signature = identifier "(" parameters ")" 

constructor_body = '{' constructor_statements '}' statement_without_return ';';

constructor_statements = statement_without_return constructor_statements | statement_without_return;
```

### Methods and Attributes declarations

```txt
attribute_declarations = attribute_declaration attribute_declarations | empty;

attribute_declaration = access_modifier modifiers declaration;

method_declarations = method_declaration method_declarations | empty; 

method_declaration = method_signature method_body;

method_signature = access_modifier modifiers type identifier '(' parameters ')'

method_body = '{' statements '}'
```

### Declarations and initializers

```txt
declarations = declaration declarations | empty;

declaration = type identifier initializer ';';

initializer = '=' expression | empty;
```

### Blocks and code blocks

```txt
code_block = '{' statements '}' | statement ';';

statements = statement statements | statement;

statement = statement_without_return | return_statement;

statement_without_return = expressions
                        | if_else_statement
                        | while_statement
                        | for_statement;

return_statement = "return" expression ';';
```

### Control structures

```txt
if_else_statement = if_statement | if_statement else_statement;

if_statement = "if" '(' relational_expression ')' code_block;

else_statement = "else" code_block;

while_statement = "while" '(' relational_expression ')' code_block;

for_statement = "for" '(' for_parameters ')' code_block;

for_parameters = for_initialization ';' relational_expression ';' for_increment;

for_initialization = type identifier '=' expression

for_increment = assignment_expression;
```

### Expressions

```txt

expressions = expression expressions | expressions;

expression = assignment_expression
            | addition_expression
            | multiplication_expression
            | priority_expression
            | relational_expression
            | method_call
            | member_access;
            | object_instance
```

### Operators and methods calls

```txt
assignment_expression = identifier '=' expression;

priority_expression = '(' expression ')'

addition_expression = expression term_operator expression;

multiplication_expression = expression factor_operator expression;

relational_expression = expression relational_operator expression;

method_call = object_instance '.' identifier '(' parameters ')';

member_access = object_instance '.' identifier;

object_instance = identifier | "this" | "super";
```

### Params and arguments

```txt
parameters = parameter | parameter ',' parameters | empty;

parameter = type identifier;

arguments = argument | argument ',' arguments;

argument = integer_literal
         | float_literal
         | double_literal
         | char_literal
         | string_literal
         | bool_literal
         | array_literal
         | object_literal
         | empty;
```

### Types and modifiers

```txt
access_modifier = "public"
                  | "private" 
                  | "protected"
                  | empty;

modifiers = "static" 
            | "abstract"
            | "readonly"
            | "override"
            | "final"
            | empty;

type = "int"
      | "string"
      | "bool"
      | "float"
      | "double"
      | "char"
      | identifier;
```

### Literals

```txt
array_literal = '{' arguments '}';

object_literal = "new" identifier '(' arguments ')' | null_literal;

bool_literal = "true" | "false" | 0 | 1 | "on" | "off" 

null_literal = "null";

float_literal = double_literal float_indicator;

double_literal = integer fractional_part exponent_part; 

integer_literal = digits | '-'digits;

string_literal = '"' characters '"';

char_literal = "'" character "'";
```

### Literals details and auxiliary

```txt
factor_operator = '*' | '/';

term_operator = '+' | '-';

identifier = [a-zA-Z_][a-zA-Z0-9_]*

relational_operator = "==" | "!=" | "<" | ">" | "<=" | ">=";

float_indicator = 'f' | 'F' | empty;

exponent_part = 'e' exponent_sign digits 
                | 'E' exponent_sign digits
                | empty;
                
fractional_part = '.' digits | empty;

exponent_sign = '' | '-' | '+';

characters = character | character characters;

character = [a-zA-Z0-9_!@#$%^&*(){}[];:'",.<>?/\`~];

digits = digit digits; digit = [0-9];
```
