grammar CScript;

program: stmt* EOF ;

stmt
    : var_decl ';'
    | enum_decl
    | func_decl
    | extern_decl
    | struct_decl
    | struct_decl ';'
    | union_decl
    | union_decl ';'
    | expr ';'
    | '*' ident '=' expr ';'
    | RETURN expr ';'
    | if_stmt
    | while_stmt
    | for_stmt
    | do_while_stmt
    | switch_stmt
    | try_catch_stmt
    | 'continue' ';'
    | 'break' ';'
    | register_callback_stmt
    | import_stmt
    | include_stmt
    ;

import_stmt: 'import' STRING ('as' ident)? ';'
           | 'import' '{' ident (',' ident)* '}' 'from' STRING ';'
           ;

include_stmt: HASH? 'include' (STRING |ANGLE_STRING) ';'
            ;

register_callback_stmt: 'register' ident 'as' ident '(' func_decl_args? ')' ';' ;

block: '{' stmt* '}' | '{' '}' ;

var_decl
    : type ident ('=' expr)?
    | type ident '[' expr ']' ('=' '{' init_list '}')?
    | type '*' ident ('=' expr)?
    | 'const' type ident ('=' expr)?
    | 'struct' ident ident ('=' expr)?
    ;

func_decl: type ident '(' func_decl_args? ')' block ;

extern_decl: 'extern' type ident '(' func_decl_args? ')' ';' ;

func_decl_args
    : var_decl (',' var_decl)*
    ;

ident: IDENTIFIER ;

type: IDENTIFIER (MUL)*
    | ENUM_KW IDENTIFIER  // 枚举类型
    ;

struct_decl: 'struct' IDENTIFIER '{' struct_members '}' ;

union_decl: 'union' IDENTIFIER '{' struct_members '}' ;

struct_members: var_decl ';' (var_decl ';')* ;

enum_decl: 'enum' IDENTIFIER? '{' enum_list '}' ';' ;

enum_list: enum_item (',' enum_item)* ;

enum_item: ident ('=' expr)? ;

init_list: expr (',' expr)* ;

expr
    : '(' type ')' expr
    | or_expr QUESTION expr ':' expr
    | primary_expr '.' ident '=' expr
    | ident '[' expr ']' '=' expr
    | ident '=' expr
    | ident '+=' expr
    | ident '-=' expr
    | ident '*=' expr
    | ident '/=' expr
    | ident '%=' expr
    | or_expr
    ;

or_expr
    : and_expr
    | or_expr OR and_expr
    ;

and_expr
    : bit_or_expr
    | and_expr AND bit_or_expr
    ;

bit_or_expr
    : bit_xor_expr
    | bit_or_expr BITOR bit_xor_expr
    ;

bit_xor_expr
    : bit_and_expr
    | bit_xor_expr XOR bit_and_expr
    ;

bit_and_expr
    : eq_expr
    | bit_and_expr BITAND eq_expr
    ;

eq_expr
    : rel_expr
    | eq_expr EQ rel_expr
    | eq_expr NEQ rel_expr
    ;

rel_expr
    : shift_expr
    | rel_expr LT shift_expr
    | rel_expr LTE shift_expr
    | rel_expr GT shift_expr
    | rel_expr GTE shift_expr
    ;

shift_expr
    : add_expr
    | shift_expr LSHIFT add_expr
    | shift_expr RSHIFT add_expr
    ;

add_expr
    : mul_expr
    | add_expr PLUS mul_expr
    | add_expr MINUS mul_expr
    ;

mul_expr
    : unary_expr
    | mul_expr MUL unary_expr
    | mul_expr DIV unary_expr
    | mul_expr MOD unary_expr
    ;

unary_expr
    : primary_expr
    | '!' unary_expr
    | '~' unary_expr
    | '&' unary_expr
    | '*' unary_expr
    | '-' unary_expr
    | '+' unary_expr
    | 'throw' expr
    | ident '++'
    | ident '--'
    ;

primary_expr
    : ident '(' call_args? ')'
    | ident '[' expr ']'
    | ident '.' ident
    | ident '::' ident
    | ident '++'
    | ident '--'
    | ident
    | numeric
    | '(' expr ')'
    ;

call_args: expr (',' expr)* ;

numeric
    : INTEGER
    | DOUBLE
    | CHAR
    | STRING
    ;

if_stmt: 'if' '(' expr ')' block ('else' block)? ;

while_stmt: 'while' '(' expr ')' block ;

for_stmt: 'for' '(' for_init? ';' for_cond? ';' for_incr? ')' block ;

for_init: var_decl | expr ;

for_cond: expr ;

for_incr: expr ;

do_while_stmt: 'do' block 'while' '(' expr ')' ;

try_catch_stmt: 'try' block catch_block+ ;
catch_block: 'catch' '(' type ident ')' block | 'catch' '(' '...' ')' block ;

switch_stmt: 'switch' '(' expr ')' '{' case_list '}' ;

case_list: case_stmt* ;

case_stmt: CASE expr ':' stmt* | DEFAULT ':' stmt* ;

// Keywords
RETURN: 'return' ;
IF: 'if' ;
ELSE: 'else' ;
WHILE: 'while' ;
FOR: 'for' ;
DO: 'do' ;
SWITCH: 'switch' ;
CASE: 'case' ;
DEFAULT: 'default' ;
CONTINUE: 'continue' ;
BREAK: 'break' ;
STRUCT_KW: 'struct' ;
UNION_KW: 'union' ;
ENUM_KW: 'enum' ;
CONST_KW: 'const' ;
EXTERN_KW: 'extern' ;
THROW: 'throw' ;

// Literals
INTEGER: [0-9]+ ;
DOUBLE: [0-9]+ '.' [0-9]+ ;
CHAR: '\'' (~['\\\r\n] | '\\' .) '\'' ;
STRING: '"' ( '\\"' | '\\n' | '\\t' | '\\r' | '\\\\' | ~["\\] )* '"' ;
ANGLE_STRING: '<' (~[>\r\n])* '>' ;
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]* ;

// Operators
PLUS: '+' ;
MINUS: '-' ;
MUL: '*' ;
DIV: '/' ;
MOD: '%' ;
EQ: '==' ;
NEQ: '!=' ;
LT: '<' ;
LTE: '<=' ;
GT: '>' ;
GTE: '>=' ;
AND: '&&' ;
OR: '||' ;
NOT: '!' ;
BITAND: '&' ;
BITOR: '|' ;
XOR: '^' ;
NOTBIT: '~' ;
LSHIFT: '<<' ;
RSHIFT: '>>' ;
QUESTION: '?' ;
COLON: ':' ;
COMMA: ',' ;
SEMI: ';' ;
LPAREN: '(' ;
RPAREN: ')' ;
LBRACE: '{' ;
RBRACE: '}' ;
LBRACKET: '[' ;
RBRACKET: ']' ;
DOT: '.' ;
ASSIGN: '=' ;
PLUS_EQ: '+=' ;
MINUS_EQ: '-=' ;
MUL_EQ: '*=' ;
DIV_EQ: '/=' ;
MOD_EQ: '%=' ;
INC: '++' ;
DEC: '--' ;
ELLIPSIS: '...' ;

// Preprocessor
HASH: '#' ;

// Skip
COMMENT: '//' ~[\r\n]* -> skip ;
MULTI_LINE_COMMENT: '/*' .*? '*/' -> skip ;
WS: [ \t\r\n]+ -> skip ;
