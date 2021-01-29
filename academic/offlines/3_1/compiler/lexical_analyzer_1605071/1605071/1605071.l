%option noyywrap
%option yylineno
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
int line_count=1;
int err_count=0; 

#include "1605071_symboltable.h" 
SymbolTable st(10); 

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
			fprintf(tokenout,"<IF>");
			fprintf(logout,"\nLine no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);
		}
		
"else"	{
			fprintf(tokenout,"<ELSE>");
			fprintf(logout,"\nLine no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);
		}
		
"for"	{
			fprintf(tokenout,"<FOR>");
			fprintf(logout,"\nLine no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);
		}

"while"	{
			fprintf(tokenout,"<WHILE>");
			fprintf(logout,"\nLine no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);
		}

"do"	{
			fprintf(tokenout,"<DO>");
			fprintf(logout,"\nLine no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);
		}

"break"	{
			fprintf(tokenout,"<BREAK>");
			fprintf(logout,"\nLine no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);
		}

"int"	{
			fprintf(tokenout,"<INT>");
			fprintf(logout,"\nLine no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);
		}

"char"	{
			fprintf(tokenout,"<CHAR>");
			fprintf(logout,"\nLine no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);
		}

"float"	{
			fprintf(tokenout,"<FLOAT>");
			fprintf(logout,"\nLine no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);
		}

"double"	{
			fprintf(tokenout,"<DOUBLE>");
			fprintf(logout,"\nLine no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);
		}

"void"	{
			fprintf(tokenout,"<VOID>");
			fprintf(logout,"\nLine no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);
		}

"return"	{
			fprintf(tokenout,"<RETURN>");
			fprintf(logout,"\nLine no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);
		}

"switch"	{
			fprintf(tokenout,"<SWITCH>");
			fprintf(logout,"\nLine no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);
		}

"case"	{
			fprintf(tokenout,"<CASE>");
			fprintf(logout,"\nLine no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);
		}

"default"	{
			fprintf(tokenout,"<DEFAULT>");
			fprintf(logout,"\nLine no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);
		}

"continue"	{
			fprintf(tokenout,"<CONTINUE>");
			fprintf(logout,"\nLine no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);
		}


"+"		|

"-"		{
			fprintf(tokenout," <ADDOP , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <ADDOP> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
		SymbolInfo *si=new SymbolInfo(string(yytext),"ADDOP");
				if(st.insert(si))
				st.print_cur();
		}
		
		
"*"		|

"/"		|
"%"		{
			fprintf(tokenout," <MULOP , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <MULOP> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"MULOP");
				if(st.insert(si))
				st.print_cur();
		}		


"++"		|

"--"		{
			fprintf(tokenout," <INCOP , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <INCOP> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"INCOP");
				if(st.insert(si))
				st.print_cur();
		}
		
"<"		    |
"<="	    |
">"		    |
">="		|
"=="		|
"!="		{
			fprintf(tokenout," <RELOP , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <RELOP> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"RELOP");
				if(st.insert(si))
				st.print_cur();
		}
		

"="		{
			fprintf(tokenout," <ASSIGNOP , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <ASSIGNOP> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"ASSIGNOP");
				if(st.insert(si))
				st.print_cur();
		}		
		


"&&"		|

"||"		{
			fprintf(tokenout," <LOGICOP , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <LOGICOP> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"LOGICOP");
				if(st.insert(si))
				st.print_cur();
		}
		
"&"		|
"|"		|
"^"		|
"<<"	|
">>"		{
			fprintf(tokenout," <BITOP , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <BITOP> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"BITOP");
				if(st.insert(si))
				st.print_cur();
		}
		
"!"		{
			fprintf(tokenout," <NOT , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <NOT> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"NOT");
				if(st.insert(si))
				st.print_cur();
		}


"("		{
			fprintf(tokenout," <LPAREN , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <LPAREN> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"LPAREN");
				if(st.insert(si))
				st.print_cur();
		}
		
")"		{
			fprintf(tokenout," <RPAREN , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <RPAREN> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"RPAREN");
				if(st.insert(si))
				st.print_cur();
		}
		
"{"		{
			fprintf(tokenout," <LCURL , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <LCURL> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"LCURL");
				if(st.insert(si))
				st.print_cur();
		}

"}"		{
			fprintf(tokenout," <RCURL , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <RCURL> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"RCURL");
				if(st.insert(si))
				st.print_cur();
		}
		
"["		{
			fprintf(tokenout," <LTHIRD , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <LTHIRD> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"LTHIRD");
				if(st.insert(si))
				st.print_cur();
		}

"]"		{
			fprintf(tokenout," <RTHIRD , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <RTHIRD> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"RTHIRD");
				if(st.insert(si))
				st.print_cur();
		}	
					
","		{
			fprintf(tokenout," <COMMA , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <COMMA> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"COMMA");
				if(st.insert(si))
				st.print_cur();
		}
		
";"		{
			fprintf(tokenout," <SEMICOLON , %s> ",yytext);
			fprintf(logout,"\nLine no %d: TOKEN <SEMICOLON> Lexeme %s found\n\n",line_count,yytext);
			//insert in symbol table and print symbol table content(only non empty buckets)
			// There is a '|' in "+"'s rule, this means match execute the action for following rule
SymbolInfo *si=new SymbolInfo(string(yytext),"SEMICOLON");
				if(st.insert(si))
				st.print_cur();
		}		

		
{DIGIT}+ 	{
				fprintf(tokenout," <CONST_INT , %s> ",yytext);
				fprintf(logout,"\nLine no %d: TOKEN <CONST_INT> Lexeme %s found\n\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo(string(yytext),"CONST_INT");
				if(st.insert(si))
				st.print_cur();
			}	
			
({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E[+|-]?{DIGIT}+)?   	{
				fprintf(tokenout," <CONST_FLOAT , %s> ",yytext);
				fprintf(logout,"\nLine no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo(string(yytext),"CONST_FLOAT");
				if(st.insert(si))
				st.print_cur();
			}	
			
			
(({DIGIT}*(\.+{DIGIT}+)+)|({DIGIT}*(\.+{DIGIT}+)+\.+))(E[+|-]?{DIGIT}+)?		{
			fprintf(logout,"\nError at line no %d: Too many decimal point %s\n",line_count,yytext);
err_count++;
		}


({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E[+|-]?({DIGIT}*\.?{DIGIT}+|{DIGIT}+\.)(E[+|-]?{DIGIT}+)?)?		{
			fprintf(logout,"\nError at line no %d: Ill formed number %s\n",line_count,yytext);
err_count++;
		}
		
    /*(\'\\\');?        	{
			fprintf(logout,"\nError at line no %d: Unterminated character %s\n",line_count,yytext);
err_count++;
		}	*/			
	
		
\'[^\'\n\\]\'         {
                fprintf(tokenout," <CONST_CHAR , %c> ",yytext[1]);
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}	
										

\'\'        {
			fprintf(logout,"\nError at line no %d: Empty character eonstant error %s\n",line_count,yytext);
err_count++;
		}	
		
				
			
\'\\n\'         {
                fprintf(tokenout," <CONST_CHAR , \n> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}			
			
\'\\t\'         {
                fprintf(tokenout," <CONST_CHAR , \t> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}
			
\'\\\\\'         {
                fprintf(tokenout," <CONST_CHAR , \\> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}
			
\'\\\"\'         {
                fprintf(tokenout," <CONST_CHAR , \"> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}								
			
			
\'\\a\'         {
                fprintf(tokenout," <CONST_CHAR , \a> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}	
			
\'\\f\'         {
                fprintf(tokenout," <CONST_CHAR , \f> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}
			
\'\\r\'         {
                fprintf(tokenout," <CONST_CHAR , \r> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				st.insert(si);
				st.print_cur();
			}
			
\'\\b\'         {
                fprintf(tokenout," <CONST_CHAR , \b> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}
			
\'\\v\'        {
                fprintf(tokenout," <CONST_CHAR , \v> ");
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}
			
\'\\0\'         {
                fprintf(tokenout," <CONST_CHAR , %c> ",'\0');
				fprintf(logout,"\nLine no %d: TOKEN <CONST_CHAR> Lexeme %s found\n\n",line_count,yytext);
				SymbolInfo *si=new SymbolInfo(yytext,"CONST_CHAR");
				if(st.insert(si))
				st.print_cur();
			}
			
'(.)(.)*[^\\\n\']'		{
			fprintf(logout,"\nError at line no %d: Multi character constant error %s\n",line_count,yytext);
err_count++;
		}			
			
\'([^'\n]|\\\')*        	{
			fprintf(logout,"\nError at line no %d: Unterminated character %s\n",line_count,yytext);
err_count++;
		}												
														
			
{DIGIT}+[a-zA-Z_0-9]*	{
			fprintf(logout,"\nError at line no %d: Invalid suffix on numeric constant or invalid prefix on identifier %s\n",line_count,yytext);
err_count++;
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
        fprintf(logout,"\nError at line no %d: Unterminated string %s\n",line_count,unfin_str.c_str()); 
           err_count++;
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
fprintf(tokenout," <STRING , %s> ",token_str.c_str());
        log_str = log_str + yytext;
		fprintf(logout,"\nLine no %d: TOKEN <STRING> Lexeme %s found\n",line_count,log_str.c_str());
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
           fprintf(logout,"\nError at line no %d: Unterminated string %s\n",line_count,unfin_str.c_str()); 
           err_count++;
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
        fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count, log_com.c_str());
        line_count = line_count + excom;
        BEGIN INITIAL;
}

<COMSTATE>(\r)     {
        fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count, log_com.c_str());
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
           fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count,log_com.c_str()); 
           //err_count++;
           line_count = line_count + excom;
}

<COMSTATE>[^\n\r]    {
            log_com = log_com + yytext;
}


    /*"//".*        {
            fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count, yytext);
}*/


"\/\*"  {
        BEGIN MULCOMSTATE;
        exmulcom = 0;
        log_mulcom = yytext;
}

<MULCOMSTATE>{NEWLINE}  {
          log_mulcom = log_mulcom + yytext;
          exmulcom++; 
          //fprintf(logout,"line_count here eof :%d\n",line_count+exmulcom);
}

<MULCOMSTATE><<EOF>>    {
           //exmulcom++;
           fprintf(logout,"\nError at line no %d: Unterminated comment %s\n",line_count,log_mulcom.c_str()); 
           err_count++;
           line_count = line_count + exmulcom;
           //fprintf(logout,"line_count here eof :%d\n",line_count);
           BEGIN INITIAL;
}

<MULCOMSTATE>"\*\/"  {
           log_mulcom = log_mulcom + yytext;
           //exmulcom++;
           fprintf(logout,"\nLine no %d: TOKEN <COMMENT> Lexeme %s found\n",line_count,log_mulcom.c_str());
           line_count = line_count + exmulcom;
           BEGIN INITIAL;
}

<MULCOMSTATE>[^\n] {
        log_mulcom = log_mulcom + yytext;
}  

[a-zA-Z_][a-zA-Z_0-9]* 	    {
				fprintf(tokenout," <ID , %s> ",yytext);
				fprintf(logout,"\nLine no %d: TOKEN <ID> Lexeme %s found\n\n",line_count,yytext);
				//insert in symbol table and print symbol table content(only non empty buckets)
				SymbolInfo *si=new SymbolInfo(string(yytext),"ID");
				if(st.insert(si))
				st.print_cur();
			}	
		
.		{
			fprintf(logout,"\nError at line no %d: Unrecognize character %s\n",line_count,yytext);
err_count++;
		}         
		
<<EOF>>		{
            line_count--;
            /*printf("Total lines : %d\nTotal errors : %d\n",line_count,err_count);*/
            st.print_cur();
			fprintf(logout,"\nTotal lines : %d\nTotal errors : %d",line_count,err_count);
			
            return 0;
		}	

%%

int main(int argc,char *argv[]){
	
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout= fopen("1605071_log.txt","w");
	tokenout= fopen("1605071_token.txt","w");

	yyin= fin;
	yylex();
	/*fprintf(logout,"Total lines : %d\nTotal errors : %d\n",line_count-1,err_count);*/
	//st.print_cur();
	fclose(yyin);
	fclose(tokenout);
	fclose(logout);
	return 0;
}
