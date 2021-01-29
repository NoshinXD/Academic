 //%option noyywrap
 //%option yylineno
 //%option c++

%x MYSTATE
%x COMSTATE
%x MULCOMSTATE
%x STATE1
%x STATE2
%x STATE3
%x STATE4
%x ERRSTATE

%{
extern int line_count;
extern int err_count; 

#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include <fstream>
#include "1605071_symboltable.h" 
#include "y.tab.h"

//extern YYSTYPE yylval;
extern SymbolTable *table;
void yyerror(char *);

string token_str;
string log_str;
string unfin_str;
string log_com;
string log_mulcom;
int ex;
int excom;
int exmulcom;

extern int curid;

extern FILE *logout;
extern FILE *errorout;

//SymbolTable st(10); 

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
DIGIT [0-9]

 //SOMECHARLIT [\a\f\r\b\v\0]

NEWLINE \n

%%

{NEWLINE} {line_count++;}

{WHITESPACE} {}

"if"	{
        /*fprintf(tokenout,"<IF>");
	fprintf(logout,"\nLine no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);*/
        return IF;}
		
"else"	{
        /*fprintf(tokenout,"<ELSE>");
	fprintf(logout,"\nLine no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);*/
        return ELSE;}
		
"for"	{
        /*fprintf(tokenout,"<FOR>");
	fprintf(logout,"\nLine no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);*/
        return FOR;}

"while"	{
        /*fprintf(tokenout,"<WHILE>");
	fprintf(logout,"\nLine no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);*/
        return WHILE;}

"do"	{
        /*fprintf(tokenout,"<DO>");
	fprintf(logout,"\nLine no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);*/
        return DO;}

"break"	{
        /*fprintf(tokenout,"<BREAK>");
	fprintf(logout,"\nLine no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);*/
        return BREAK;}

"int"	{
        SymbolInfo *s=new SymbolInfo(string(yytext),"INT");
                        yylval.sym = s;
        return INT;}

"char"	{
        SymbolInfo *s=new SymbolInfo(string(yytext),"CHAR");
                        yylval.sym = s;
        return CHAR;}

"float"	{
        SymbolInfo *s=new SymbolInfo(string(yytext),"FLOAT");
                        yylval.sym = s;
        return FLOAT;}

"double"	{
        SymbolInfo *s=new SymbolInfo(string(yytext),"DOUBLE");
                        yylval.sym = s;
        return DOUBLE;}

"void"	{
        SymbolInfo *s=new SymbolInfo(string(yytext),"VOID");
                        yylval.sym = s;
        return VOID;}

"return"	{
        /*fprintf(tokenout,"<RETURN>");
	fprintf(logout,"\nLine no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);*/
        return RETURN;}

"switch"	{
        /*fprintf(tokenout,"<SWITCH>");
	fprintf(logout,"\nLine no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);*/
        return SWITCH;}

"case"	{
        /*fprintf(tokenout,"<CASE>");
	fprintf(logout,"\nLine no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);*/
        return CASE;}

"default"	{
        /*fprintf(tokenout,"<DEFAULT>");
	fprintf(logout,"\nLine no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);*/
        return DEFAULT;}

"continue"	{
        /*fprintf(tokenout,"<CONTINUE>");
	fprintf(logout,"\nLine no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);*/
        return CONTINUE;}

"println"	{
        SymbolInfo *s=new SymbolInfo(string(yytext),"PRINTLN");
                        yylval.sym = s;
        return PRINTLN;}


"+"		|
"-"		{
			/*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"ADDOP");
			yylval = (YYSTYPE)s;
			return ADDOP;*/
		        SymbolInfo *s=new SymbolInfo(string(yytext),"ADDOP");
                        yylval.sym = s;
                        return ADDOP;
				/*if(st.insert(si))
				st.print_cur();*/
		}
		
		
"*"		|

"/"		|
"%"		{
			/*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"MULOP");
			yylval = (YYSTYPE)s;*/
                        SymbolInfo *s=new SymbolInfo(string(yytext),"MULOP");
                        yylval.sym = s;
			return MULOP;
		}		


"++"		{
        SymbolInfo *s=new SymbolInfo(string(yytext),"INCOP");
                        yylval.sym = s;
        return INCOP;}

"--"		{
        SymbolInfo *s=new SymbolInfo(string(yytext),"DECOP");
                        yylval.sym = s;
        return DECOP;}
		
"<"		|
"<="	    	|
">"		|
">="		|
"=="		|
"!="		{
			/*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"RELOP");
		yylval = (YYSTYPE)s;*/
                        SymbolInfo *s=new SymbolInfo(string(yytext),"RELOP");
                        yylval.sym = s;
		        return RELOP;
		}
		

"="		{
        /*fprintf(tokenout," <ASSIGNOP , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <ASSIGNOP> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return ASSIGNOP;}	
		


"&&"		|

"||"		{
			/*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LOGICOP");
			yylval = (YYSTYPE)s;*/
                        SymbolInfo *s=new SymbolInfo(string(yytext),"LOGICOP");
                        yylval.sym = s;
			return LOGICOP;
		}
		
"&"		|
"|"		|
"^"		|
"<<"	|
">>"		{
			/*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"LOGICOP");
			yylval = (YYSTYPE)s;*/
                        SymbolInfo *s=new SymbolInfo(string(yytext),"BITOP");
                        yylval.sym = s;
			return BITOP;
		}
		
"!"		{	
        /*fprintf(tokenout," <NOT , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <NOT> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return NOT; }

"("		{
        /*fprintf(tokenout," <LPAREN , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <LPAREN> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return LPAREN;}
		
")"		{
        /*fprintf(tokenout," <RPAREN , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <RPAREN> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return RPAREN;}
		
"{"		{
        /*fprintf(tokenout," <LCURL , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <LCURL> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return LCURL;}

"}"		{
        /*fprintf(tokenout," <RCURL , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <RCURL> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return RCURL;}
		
"["		{
        /*fprintf(tokenout," <LTHIRD , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <LTHIRD> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return LTHIRD;}

"]"		{
        /*fprintf(tokenout," <RTHIRD , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <RTHIRD> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return RTHIRD;}
					
","		{
        /*fprintf(tokenout," <COMMA , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <COMMA> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        return COMMA;}
		
";"		{ 
        /*fprintf(tokenout," <SEMICOLON , %s> ",yytext);
	fprintf(logout,"\nLine no %d: TOKEN <SEMICOLON> Lexeme %s found\n\n",line_count,yytext);*/
        //insert in symbol table and print symbol table content(only non empty buckets)
	// There is a '|' in "+"'s rule, this means match execute the action for following rule
        SymbolInfo *s=new SymbolInfo(string(yytext),"SEMICOLON");
                        yylval.sym = s;
        return SEMICOLON;}	

		
{DIGIT}+ 	{
				/*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_INT");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_INT", "int");
                        yylval.sym = s;
				return CONST_INT;
			}	
			
({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E[+|-]?{DIGIT}+)?   	{
				/*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_FLOAT");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_FLOAT", "float");
                                yylval.sym = s;
				return CONST_FLOAT; 
			}	
			
			
(({DIGIT}*(\.+{DIGIT}+)+)|({DIGIT}*(\.+{DIGIT}+)+\.+))(E[+|-]?{DIGIT}+)?		{
//fprintf(errorout,"\nError at line no %d: Too many decimal point %s\n",line_count,yytext);        
//err_count++;
		}


({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E[+|-]?({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E[+|-]?{DIGIT}+)?)?		{
//fprintf(logout,"\nError at line no %d: Ill formed number %s\n",line_count,yytext);
//err_count++;
		}
		
    /*(\'\\\');?        	{
			//fprintf(logout,"\nError at line no %d: Unterminated character %s\n",line_count,yytext);
err_count++;
		}	*/			
	
		
\'[^\'\n\\]\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}	
										

\'\'        {
//fprintf(logout,"\nError at line no %d: Empty character eonstant error %s\n",line_count,yytext);       
//err_count++;
		}	
		
				
			
\'\\n\'         {
		                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}			
			
\'\\t\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}
			
\'\\\\\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}
			
\'\\\"\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}								
			
			
\'\\a\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}	
			
\'\\f\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}
			
\'\\r\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}
			
\'\\b\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}
			
\'\\v\'        {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}
			
\'\\0\'         {
                                /*SymbolInfo *s= new  SymbolInfo(yytext, (char *)"CONST_CHAR");
				yylval = (YYSTYPE)s;*/
                                SymbolInfo *s=new SymbolInfo(string(yytext),"CONST_CHAR");
                                yylval.sym = s;
				return CONST_CHAR;
			}
			
'(.)(.)*[^\\\n\']'		{
//fprintf(logout,"\nError at line no %d: Multi character constant error %s\n",line_count,yytext);        
//err_count++;
		}			
			
\'([^'\n]|\\\')*        	{
//fprintf(logout,"\nError at line no %d: Unterminated character %s\n",line_count,yytext);
//err_count++;
		}												
														
			
{DIGIT}+[a-zA-Z_0-9]*	{
//fprintf(logout,"\nError at line no %d: Invalid suffix on numeric constant or invalid prefix on identifier %s\n",line_count,yytext);        
//err_count++;
		}
			
			
\"      {
         BEGIN MYSTATE;
         token_str = "";
         //token_str = yytext;
         log_str = yytext;
         unfin_str = yytext;
         ex = 0;
         }

<MYSTATE>\\     {
        log_str = log_str + yytext;
        unfin_str = unfin_str + yytext;
        //ex++;
        BEGIN STATE1;
}   

<MYSTATE><<EOF>>      {
        //line_count--;
        unfin_str = unfin_str + yytext;
        //fprintf(logout,"\nError at line no %d: Unterminated string %s\n",line_count,unfin_str.c_str()); 
           //err_count++;
           line_count = line_count + ex;
           BEGIN INITIAL;
}	

<STATE1>{NEWLINE}   {
    log_str = log_str + yytext;
    unfin_str = unfin_str + yytext;
    ex++;
    BEGIN MYSTATE;
}



<MYSTATE>[^"\n\r] {
        token_str = token_str + yytext;
        log_str = log_str + yytext;
        unfin_str = unfin_str + yytext;
}  		
			
<MYSTATE>\"     {
        //token_str = token_str + yytext;
//fprintf(tokenout," <STRING , %s> ",token_str.c_str());
        log_str = log_str + yytext;
		//fprintf(logout,"\nLine no %d: TOKEN <STRING> Lexeme %s found\n",line_count,log_str.c_str());
line_count = line_count + ex;
        BEGIN INITIAL;
}

<STATE1>[^"\n\r] {
        token_str = token_str + yytext;
        log_str = log_str + yytext;
        unfin_str = unfin_str + yytext;
        BEGIN MYSTATE;
}  	

<MYSTATE>"\\n"      {
        log_str = log_str + yytext;
        token_str = token_str + '\n';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\t"      {
        log_str = log_str + yytext;
        token_str = token_str + '\t';
        unfin_str = unfin_str + yytext;
} 

<MYSTATE>"\\\\"      {
        log_str = log_str + yytext;
        token_str = token_str + '\\';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\\""      {
        log_str = log_str + yytext;
        token_str = token_str + '\"';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\a"      {
        log_str = log_str + yytext;
        token_str = token_str + '\a';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\f"      {
        log_str = log_str + yytext;
        token_str = token_str + '\f';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\r"      {
        log_str = log_str + yytext;
        token_str = token_str + '\r';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\b"      {
        log_str = log_str + yytext;
        token_str = token_str + '\b';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\v"      {
        log_str = log_str + yytext;
        token_str = token_str + '\v';
        unfin_str = unfin_str + yytext;
}

<MYSTATE>"\\0"      {
        log_str = log_str + yytext;
        token_str = token_str + '\0';
        unfin_str = unfin_str + yytext;
}



<MYSTATE>{NEWLINE}  {
           ex++;
           //fprintf(logout,"\nError at line no %d: Unterminated string %s\n",line_count,unfin_str.c_str()); 
           //err_count++;
           line_count = line_count + ex;
           BEGIN INITIAL;
}
				

	

\/\/      {
            BEGIN COMSTATE;
            excom = 0;
            log_com = yytext;
}

<COMSTATE>\\    {
            log_com = log_com + yytext;
            BEGIN STATE2;
}

<COMSTATE>({NEWLINE})     {
        excom++;
        //fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count, log_com.c_str());
        line_count = line_count + excom;
        BEGIN INITIAL;
}

<COMSTATE>(\r)     {
        //fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count, log_com.c_str());
        line_count = line_count + excom;
        BEGIN INITIAL;
}

<STATE2>{NEWLINE}   {
            excom++;
            log_com = log_com + yytext;
            BEGIN COMSTATE;
}

<STATE2>[^\n\r\\]   {
            log_com = log_com + yytext;
            BEGIN COMSTATE;
}

<STATE2>\\   {
            log_com = log_com + yytext;
}


<COMSTATE><<EOF>>       {
        //line_count--;
    BEGIN INITIAL;
           //fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count,log_com.c_str()); 
           //err_count++;
           line_count = line_count + excom;
}

<COMSTATE>[^\n\r]    {
            log_com = log_com + yytext;
}


    /*"//".*        {
            //fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count, yytext);
}*/


"\/\*"  {
        BEGIN MULCOMSTATE;
        exmulcom = 0;
        log_mulcom = yytext;
}

<MULCOMSTATE>{NEWLINE}  {
          log_mulcom = log_mulcom + yytext;
          exmulcom++; 
          ////fprintf(logout,"line_count here eof :%d\n",line_count+exmulcom);
}

<MULCOMSTATE><<EOF>>    {
           //exmulcom++;
           //fprintf(logout,"\nError at line no %d: Unterminated comment %s\n",line_count,log_mulcom.c_str()); 
           //err_count++;
           line_count = line_count + exmulcom;
           ////fprintf(logout,"line_count here eof :%d\n",line_count);
           BEGIN INITIAL;
}

<MULCOMSTATE>"\*\/"  {
           log_mulcom = log_mulcom + yytext;
           //exmulcom++;
           //fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count,log_mulcom.c_str());
           line_count = line_count + exmulcom;
           BEGIN INITIAL;
}

<MULCOMSTATE>[^\n] {
        log_mulcom = log_mulcom + yytext;
}  

[a-zA-Z_][a-zA-Z_0-9]* 	    {
				
				SymbolInfo *s= table->lookup(yytext);
				if(s==NULL)
				{					
					//s= new SymbolInfo(yytext, (char *)"ID");
                                        s=new SymbolInfo(string(yytext),"ID");
				}
				//yylval = (YYSTYPE)s;
                                yylval.sym = s;
							
				return ID;
			}	
		
.		{
//fprintf(logout,"\nError at line no %d: Unrecognize character %s\n",line_count,yytext);        
//err_count++;
		}         
		
<<EOF>>		{
            line_count--;
            /*printf("Total lines : %d\nTotal errors : %d\n",line_count,err_count);*/
            //st.print_cur();
			//fprintf(logout,"\nTotal lines : %d\nTotal errors : %d",line_count,err_count);
			
            return 0;
		}	

%%

int yywrap(void)
{
	return 1;
}
