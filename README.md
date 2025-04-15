# Project Magic

Magic is a simple programming object oriented language

## Grammar

### Main definitions

```txt
program = "class" identifier "{" class_body "}";

class_body = field_declarations method_declarations constructor;
```

### Constructors declarations

```txt
constructor_declaration = identifier "(" parameters ")" constructor_body;

constructor_body = '{' constructor_statements '}' statement_no_return ';';

constructor_statements = statement_no_return constructor_statements | statement_no_return;
```

### Methods and fields declarations

```txt
field_declarations = field_declaration field_declarations | '';

field_declaration = access_modifier modifiers declaration;

method_declarations = method_declaration method_declarations | ''; 

method_declaration = access_modifier modifiers type identifier '(' parameters ')' code_block;
```

### Declarations and initializers

```txt
declarations = declaration declarations | '';

declaration = type identifier initializer ';';

initializer = '=' expression | '';
```

### Blocks and code blocks

```txt
code_block = '{' statements '}' | statement ';';

statements = statement statements | statement;

statement = statement_no_return | return_statement;

statement_no_return = expressions_statement | if_else_statement | while_statement | for_statement;

return_statement = "return" expression ';';
```

### Control structures

```txt
if_else_statement = if_statement | if_statement else_statement;

if_statement = "if" '(' expression ')' code_block;

else_statement = "else" code_block;

while_statement = "while" '(' expression ')' code_block;

for_statement = "for" '(' for_parameters ')' code_block;

for_parameters = expression ';' expression ';' expression;
```

### Expressions

```txt
expressions_statement = expression ';' | method_call ';' | member_access ';';

expression = assignment_expression
          | addition_expression
          | subtraction_expression
          | multiplication_expression
          | division_expression
          | or_expression
          | and_expression
          | not_expression
          | equals_expression
          | method_call
          | member_access;
```

### Operators and methods calls

```txt
assignment_expression = identifier '=' expression;

addition_expression = expression '+' expression;

subtraction_expression = expression '-' expression;

multiplication_expression = expression '*' expression;

or_expression = expression '||' expression;

and_expression = expression '&&' expression;

not_expression = '!' expression;

equals_expression = expression '==' expression;

method_call = object_instance '.' identifier '(' parameters ')';

member_access = object_instance '.' identifier;

object_instance = identifier | "this" | "super";
```

### Params and arguments

```txt
parameters = parameter | parameter ',' parameters | '';

parameter = type identifier;

arguments = argument | argument ',' arguments;

argument = integer_literal
         | float_literal
         | char_literal
         | string_literal
         | array_literal
         | object_literal
         | '';
```

### Types and modifiers

```txt
access_modifier = "public" | "private" | "protected" | '';

modifiers = "static" | "abstract" | "readonly" | "override" | "final" | '';

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

null_literal = "null";

float_literal = double_literal float_indicator;

double_literal = integer fractional_part exponent_part; 

integer_literal = digits | '-' digits; string_literal = '"'

characters '"'; char_literal = "'" character "'";
```

### Literals details and auxiliary

```txt
float_indicator = 'f' | 'F' | '';

exponent_part = 'e' exponent_sign digits 
                | 'E' exponent_sign digits
                | '';
                
fractional_part = '.' digits | '';

exponent_sign = '' | '-' | '+';

characters = character | character characters;

character = [a-zA-Z0-9_!@#$%^&*(){}[];:'",.<>?/\`~];

digits = digit digits; digit = [0-9];
```
