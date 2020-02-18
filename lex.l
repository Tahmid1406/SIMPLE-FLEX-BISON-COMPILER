%{
#include <stdio.h>
%}
ws		  [ \t\n]
digit     [0-9]
literal    [A-Za-z]
othreValid  [#|@|!|&|~|,]

%%
{ws}*				{printf("space\n");}
"if"							{ printf("IF: %s\n", yytext);}
"else"							{ printf("ELSE: %s\n", yytext);}
"int"							{ printf("INT: %s\n", yytext);}
"real"							{ printf("REAL: %s\n", yytext);}
"void"							{ printf("VOID: %s\n", yytext);}
"while"							{ printf("WHILE: %s\n", yytext);}

{digit}+  						 {printf("ILIT:%s\n",yytext);}
{digit}+\.{digit}+				 { printf("RLIT: %s\n", yytext);}
{literal}                        { printf("CLIT: %s\n", yytext);}
{literal}{literal}+               { printf("SLIT: %s\n", yytext);}


{literal}({literal}|{digit})*       { printf("ID: %s\n", yytext);}

"(" 								 { printf("LPT: %s\n", yytext);}
")" 								 { printf("RPT: %s\n", yytext);}
"{" 								 { printf("LCB: %s\n", yytext);}
"}" 								 { printf("RCB: %s\n", yytext);}
"[" 								 { printf("LSB: %s\n", yytext);}
"]" 								 { printf("RSB: %s\n", yytext);}
";"	                             { printf("SEMI: %s\n", yytext);}


"+"	                             { printf("PLUS: %s\n", yytext);}
"-"	                             { printf("MINUS: %s\n", yytext);}
"*"	                             { printf("PROD: %s\n", yytext);}
"/"	                             { printf("DIV: %s\n", yytext);}
"%"	                             { printf("REM: %s\n", yytext);}
":="	                         { printf("ASSIGN: %s\n", yytext);}

"<="	                         { printf("LE: %s\n", yytext);}
">="							 { printf("GE: %s\n", yytext);}
"<>"							 { printf("NE: %s\n", yytext);}

"<"	                             { printf("LT: %s\n", yytext);}
">"	                             { printf("GT: %s\n", yytext);}
"="	                             { printf("EQ: %s\n", yytext);}

<<EOF>>			                 { printf("EOF:\n"); return 0;}
.				                 { printf("ERROR: %s\n", yytext);}
{othreValid}+                    {;}
%%

int yywrap(void)
{  
   return 1;
}

int yyerror(void)
{
    printf("Error\n");
    exit(1);
}

int main()
{ 
	yylex(); 
}

