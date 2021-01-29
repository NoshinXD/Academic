//nanda_kore
%{	
#include<iostream>
#include<cstdlib>
#include<cstring>
//#include<string>
#include<cmath>
#include <fstream>
#include<vector>
#include<sstream>
#include "1605071_symboltable.h"
//#define YYSTYPE SymbolInfo*
#define N 71

using namespace std;

vector <SymbolInfo*> variables;//declaration_list
vector <SymbolInfo*> parameters;//parameter_list
vector <SymbolInfo*> arguments;//argument_list
vector <string> nameid_list;

vector <string> spec_list;//eta na holeo cholto kintu amr offlinee age constructore shudhu name r type chilo...spec pore add korchi...spec add korar agei ei spec_list rakhchilm...change kori ny pore r
//vector <string> ret_list;
string return_type = "";//int add(){} int holo return_type
int retflag = 0;
string ret_ex;//int add(int a, int b){return a+b} a+b er type holo ret_ex;
int first_param = 0;

string func_name;

vector<string> unicvar;
vector<string> unicarr;
vector<string> unicarrsize;
vector<string> unicfuncvar;
vector<string> tempusedvar;

int yyparse(void);
int yylex(void);
int curid;//eta amr scopetable gulor id
string var[26];

FILE *fp;
FILE *logout;
FILE *errorout;
FILE *codeout;
FILE *optout;

extern FILE *yyin;
int line_count = 1;
int err_count = 0; 
extern int yytext;

bool ifPrint = false;

int labelCount=0;
int tempCount=0;


char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

SymbolTable *table = new SymbolTable(N);


void yyerror(const char *s)
{
	//write your code
	fprintf(errorout, "\nError at line no %d : %s at %s\n", line_count, s, yytext);
	err_count++;
}

string printCode()
{
	string printc = "\nprintln PROC\n";
	/*printc = printc + "mov bp, sp\n";
	printc = printc + "mov bx, [bp+2]\n";
	printc = printc + "cmp bx, 0\n";
	printc = printc + "jl negative\n";
	printc = printc + "jmp positive\n";
	printc = printc + "negative:\n";
	printc = printc + "mov ah, 2\n";
	printc = printc + "mov dl, \"-\"\n";
	printc = printc + "int 21h\n";
	printc = printc + "neg bx\n";
	printc = printc + "positive:\n";
	printc = printc + "mov ax, bx\n";
	printc = printc + "xor cx, cx\n";
	printc = printc + "mov bx, 10\n";
	printc = printc + "extract:\n";
	printc = printc + "xor dx, dx\n";
	printc = printc + "div bx\n";
	printc = printc + "push dx\n";
	printc = printc + "inc cx\n";
	printc = printc + "or ax, ax\n";
	printc = printc + "jne extract\n";
	printc = printc + "mov ah, 2\n";
	printc = printc + "show:\n";
	printc = printc + "pop dx\n";
	printc = printc + "or dl, 30h\n";
	printc = printc + "int 21h\n";
	printc = printc + "loop show\n";
	printc = printc + "mov ah, 2\n";
	printc = printc + "mov dl, 0dh\n";
	printc = printc + "int 21h\n";
	printc = printc + "mov dl, 0ah\n";
	printc = printc + "RET\n";*/

	printc = printc + "PUSH AX\n";
	printc = printc + "PUSH BX\n";
	printc = printc + "PUSH CX\n";
	printc = printc + "PUSH DX\n";

	printc = printc + "\nOR AX, AX\n";
	printc = printc + "JGE END_IF1\n";

	printc = printc + "PUSH AX\n";
	printc = printc + "MOV DL, \'-\'\n";
	printc = printc + "MOV AH, 2\n";
	printc = printc + "INT 21H\n";
	printc = printc + "POP AX\n";
	printc = printc + "NEG AX\n";

	printc = printc + "\nEND_IF1:\n";
	printc = printc + "XOR CX, CX\n";
	printc = printc + "MOV BX, 10\n";

	printc = printc + "\nREPEAT1:\n";
	printc = printc + "XOR DX, DX\n";
	printc = printc + "DIV BX\n";
	printc = printc + "PUSH DX\n";
	printc = printc + "INC CX\n";
	printc = printc + "OR AX, AX\n";
	printc = printc + "JNE REPEAT1\n";
	printc = printc + "MOV AH, 2\n";

	printc = printc + "\nPRINT_LOOP:\n";
	printc = printc + "POP DX\n";
	printc = printc + "OR DL, 30H\n";
	printc = printc + "INT 21H\n";
	printc = printc + "LOOP PRINT_LOOP\n";

	printc = printc + "MOV AH, 2\n";
	printc = printc + "MOV DL, 0DH\n";
	printc = printc + "INT 21H\n";
	printc = printc + "MOV DL, 0AH\n";
	printc = printc + "INT 21H\n";

	printc = printc + "\nPOP DX\n";
	printc = printc + "POP CX\n";
	printc = printc + "POP BX\n";
	printc = printc + "POP AX\n";

	printc = printc + "RET\n";
	printc = printc + "println ENDP\n";

	return printc;
}


%}

%error-verbose

%union
{
	int isym;
	float fsym;
	SymbolInfo* sym; 
}

%token <sym> CONST_INT CONST_FLOAT CONST_CHAR ID

%type <sym> start program unit var_declaration func_declaration func_definition type_specifier parameter_list compound_statement statements declaration_list statement expression_statement logic_expression rel_expression simple_expression term unary_expression factor variable argument_list arguments expression

%token MAIN LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD  

%token FOR IF WHILE RETURN DO BREAK SWITCH CASE DEFAULT CONTINUE 

%token <sym> PRINTLN SEMICOLON

%token <sym> INCOP DECOP

%token <sym> INT CHAR FLOAT DOUBLE VOID

%left <sym> ADDOP 
%left <sym> MULOP LOGICOP RELOP BITOP 
%left NOT COMMA

%right ASSIGNOP 

%nonassoc IFX
%nonassoc ELSE

%%

start: program
	{
		//write your code in this block in all the similar blocks below
		//fprintf(logout, "          symbol table:\n\n");
		//table->print_all();
		fprintf(logout,"\nTotal lines : %d\n\nTotal errors : %d",line_count+1,err_count);
		fprintf(errorout,"\nTotal lines : %d\n\nTotal errors : %d",line_count+1,err_count);
		//fprintf(errorout,"\nTotal errors : %d",err_count);

		if(err_count == 0)
		{
			string tempcode = ".MODEL SMALL\n";
			tempcode = tempcode + ".STACK 200H\n";
			tempcode = tempcode + ".DATA\n";

			int i=0;
			while(i != unicvar.size())
			{
				tempcode = tempcode + unicvar[i] + " dw ?\n";
				i++;
			}

			i=0;
			while(i != unicarr.size())
			{
				tempcode = tempcode + unicarr[i] + " dw " + unicarrsize[i] + " DUP(?)\n";
				i++;
			}

			string printcode = "";

			if(ifPrint == true)
			{
				printcode = printCode();
			}

			/*if($$->code == $1->code)
				cout << "HERE1" << endl;
			else
				cout << "HERE2" << endl;*/

			tempcode = tempcode + "\n.CODE\n";
			tempcode = tempcode + printcode;
			tempcode = tempcode + $1->code;
			$$->code = tempcode;
		//ekhane baki ache
			fprintf(codeout, "%s\n", $$->code.c_str());

			/*if($$->code == $1->code)
				cout << "HERE3" << endl;
			else
				cout << "HERE4" << endl;*/

			//optimization shuru
			istringstream ss($$->code);
		
			vector<string> fileline;
			string temptoken;

			while(getline(ss, temptoken, '\n'))
			{
				if(temptoken != "")
					fileline.push_back(temptoken);
			}

			i=0;
			while(i != fileline.size()-1)
			{
				string s1 = fileline[i];
        		string s2 = fileline[i+1];

				bool ifsame = false;


				if(s1.length() == s2.length())
				{
					istringstream ss1(s1);
        			istringstream ss2(s2);

        			vector<string> tempstr1, tempstr2, tempstr3, tempstr4;
        			string temptoken1, temptoken2, temptoken3, temptoken4;

					while(getline(ss1, temptoken1, ' '))
        			{
           				tempstr1.push_back(temptoken1);
        			}
        			while(getline(ss2, temptoken2, ' '))
        			{
            			tempstr2.push_back(temptoken2);
        			}

					if((tempstr1[0] == "MOV" || tempstr1[0] == "mov") && (tempstr2[0] == "MOV" || tempstr2[0] == "mov"))
					{
						istringstream ss3(tempstr1[1]);
            			istringstream ss4(tempstr2[1]);

						while(getline(ss3, temptoken3, ','))
            			{
                			tempstr3.push_back(temptoken3);
            			}
            			while(getline(ss4, temptoken4, ','))
            			{
                			tempstr4.push_back(temptoken4);
            			}

						string src1 = tempstr3[0];
            			string dest1 = tempstr3[1];

            			string src2 = tempstr4[0];
            			string dest2 = tempstr4[1];

						if(src1 == dest2 && src2 == dest1)
            			{
            				ifsame = true;
            			}
					}
				}
				fprintf(optout, "%s\n", s1.c_str());

				if(ifsame == true)
        		{
            		i = i+2;
     			}
        		else
        		{
            		i++;
        		}	
			
			}
			fprintf(optout, "%s\n", fileline.back().c_str());

		}	
	}
	;

program: program unit
	{
		fprintf(logout, "\nAt line no %d :program : program unit\n" , line_count);
		string strg = $1->get_name() + $2->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"Program1"); // spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string tempcode = $1->code + $2->code;
		$$->code = tempcode;
		//fprintf(codeout, "\n%s\n", $$->code.c_str());
	}
	| unit
	{
		fprintf(logout, "\nAt line no %d :program : unit\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
	;
	
unit: var_declaration
	{
		fprintf(logout, "\nAt line no %d :unit : var_declaration\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		unicfuncvar.clear();
	}		
     | func_declaration
	 {
		fprintf(logout, "\nAt line no %d :unit : func_declaration\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}	
     | func_definition
	 {
		fprintf(logout, "\nAt line no %d : unit : func_definition\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
     ;
     
func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
	{
		fprintf(logout, "\nAt line no %d : func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + "(" + $4->get_name() + ")" + ";\n";

		string cfg_spec = $1->get_name();

		SymbolInfo *s = new SymbolInfo(strg,"func_declaration1", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str()); //ok

		string temp = $2->get_name();
		SymbolInfo *isFound = table->lookup(temp);

		if(isFound != 0) //jodi sym tablee age thekei thk 
		{
			if(isFound->get_type() == "FUNC_ID")
			{
				if(isFound->get_check_func() != 1)
				{
					vector<string> temp_name = isFound->get_savedname();
					vector<string> temp_spec = isFound->get_savedspec();

					int psize = isFound->get_para_list_size();

					string cur_ret = $1->get_name();

					if(cur_ret != isFound->get_ret_type())
					{
					
						fprintf(errorout, "\nError at line no %d : Return Type mismatch\n", line_count);
						err_count++;
					}

					else if(psize == parameters.size())
					{
						int i = 0;
					
						while(i != parameters.size())
						{
							if(spec_list[i] != temp_spec[i])
							{
								fprintf(errorout, "\nError at line no %d : Type Mismatch\n", line_count);
								err_count++;
								break;
							}

							i++;
						}	
					}
					else if(psize != parameters.size())
					{
						fprintf(errorout, "\nError at line no %d : Number of parameters mismatched with previous declaration\n", line_count);
						err_count++;
					}
				}
				
			}
			else if(isFound->get_type() != "FUNC_ID")
			{
				fprintf(errorout, "\nError at line no %d : %s is of different type\n", line_count, $2->get_name().c_str());
				err_count++;
			}
        }
		else //jodi sym tablee khuje na pay
		{
			string spec = $1->get_name();
			SymbolInfo *newnode = new SymbolInfo(temp, "FUNC_ID", spec);
			table->insert(newnode);

			isFound = table->lookup(temp);
			isFound->set_check_func(1);
			isFound->set_ret_type($1->get_name());

			int i = 0;
			while(i != parameters.size())
			{
				string name = parameters[i]->get_name();	
				string type = parameters[i]->get_type();
				string spec = spec_list[i];

				isFound->set_savedparam(name, spec); //shobgulo parameter save kore rakhlm jodi pore lage

				i++;
			}
			vector<string> temp_spec = isFound->get_savedspec();

			isFound->set_para_list_size(temp_spec);
		}

		parameters.clear();
		spec_list.clear();
	}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		
		{
		fprintf(logout, "\nAt line no %d : func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + "(" + ")" + ";\n";

		string cfg_spec = $1->get_name();

		SymbolInfo *s = new SymbolInfo(strg,"func_declaration2", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		string temp = $2->get_name();
		SymbolInfo *isFound = table->lookup(temp);

		if(isFound != 0) //jodi sym tablee age thekei thk
		{
			if(isFound->get_type() == "FUNC_ID")
			{
				int psize = isFound->get_para_list_size();
				
				if(isFound->get_check_func() != 1)
				{
					string cur_ret = $1->get_name();

					if(cur_ret != isFound->get_ret_type())
					{
					
						fprintf(errorout, "\nError at line no %d : Return Type mismatch\n", line_count);
						err_count++;
					}

					else if(parameters.size() != psize)
					{	//works
						fprintf(errorout, "\nError at line no %d : Number of parameters mismatched with previous declaration\n", line_count);
						err_count++;
					}
				}
			}
			else if(isFound->get_type() != "FUNC_ID")
			{
				fprintf(errorout, "\nError at line no %d : %s is of different type\n", line_count, $2->get_name().c_str());
				err_count++;
			}
        }
		else //jodi khuje na pay
		{
			string spec = $1->get_name();
			SymbolInfo *newnode = new SymbolInfo(temp, "FUNC_ID", spec);
			table->insert(newnode);

			isFound = table->lookup(temp);
			isFound->set_check_func(1);
			isFound->set_ret_type($1->get_name());
		}
	}
	;
		 
func_definition: type_specifier ID LPAREN parameter_list RPAREN
{	
		string temp = $2->get_name();
        SymbolInfo *isFound = table->lookup(temp);

        if(isFound != 0 && isFound->get_type() == "FUNC_ID")//jodi khuje pay
        {	
			if(isFound->get_def_func() == 1)
			{
				fprintf(errorout, "\nError at line no %d : Multiple definition of function %s\n", line_count, temp.c_str());
				err_count++;
			}
			
			else if(isFound->get_def_func() != 1)
			{
				vector<string> temp_name = isFound->get_savedname();
				vector<string> temp_spec = isFound->get_savedspec();

				int psize = isFound->get_para_list_size();

            	string cur_ret = $1->get_name();
			
				if(cur_ret == isFound->get_ret_type() && psize == parameters.size())
				{
					int flag = 0;
					int i = 0;
					
					while(i != parameters.size())
					{	
						if(spec_list[i] != temp_spec[i])
						{
							flag = 1;//params mile ny
							break;
						}

						i++;
					}
					if(flag == 0)
					{
						isFound->set_def_func(1);
					}
				}
				if(cur_ret != isFound->get_ret_type())
				{
				
					fprintf(errorout, "\nError at line no %d : Return Type mismatch\n", line_count);
					err_count++;
				}

            	else if(psize == parameters.size())
				{
					int i = 0;
				
					while(i != parameters.size())
					{
						if(spec_list[i] != temp_spec[i])
						{
							fprintf(errorout, "\nError at line no %d : Type Mismatch\n", line_count);
							err_count++;
							break;
						}

						i++;
					}	
				}
           	 	else if(psize != parameters.size())
				{	//works
					fprintf(errorout, "\nError at line no %d : Number of parameters mismatched with previous declaration\n", line_count);
					err_count++;
				}
			}
            isFound->clearvector();
			int i = 0;
			//cout << parameters.size() << endl;
			while(i != parameters.size())
			{
				//cout << parameters[i]->get_name() << endl;
				string name = parameters[i]->get_name();
				string type = parameters[i]->get_type();
				string spec = spec_list[i];

				//new start
				stringstream ss;
    			ss << curid + 1;
    			string sid=ss.str();
			    string unicname = name + sid;

				isFound->set_savedparam(unicname, spec);
				isFound->set_savedsid(curid+1);

				i++;
			}
			vector<string> temp_spec = isFound->get_savedspec();

			isFound->set_para_list_size(temp_spec);
			//cout << isFound->get_para_list_size() << endl;
        }
		else if(isFound != 0 && isFound->get_type() != "FUNC_ID")
		{
			fprintf(errorout, "\nError at line no %d : %s is of different type\n", line_count, $2->get_name().c_str());
			err_count++;
		}
        else //jodi khuje na pay
        {
			string spec = $1->get_name();
            SymbolInfo *newnode = new SymbolInfo(temp, "FUNC_ID", spec);
			table->insert(newnode);

            isFound = table->lookup(temp);
			
			isFound->set_def_func(1);
			isFound->set_ret_type($1->get_name());

            int i = 0;
			while(i != parameters.size())
			{
				string name = parameters[i]->get_name();
				string type = parameters[i]->get_type();
				string spec = spec_list[i];

				stringstream ss;
    			ss << curid + 1;
    			string sid=ss.str();
			    string unicname = name + sid;

				isFound->set_savedparam(unicname, spec);
				isFound->set_savedsid(curid+1);

				i++;
			}
			vector<string> temp_spec = isFound->get_savedspec();

			isFound->set_para_list_size(temp_spec);
			//cout << isFound->get_para_list_size() << endl;
        }
		return_type = $1->get_name();

		unicvar.push_back($2->get_name() + "ret");

		func_name = $2->get_name();
		

}		compound_statement
		{
			fprintf(logout, "\nAt line no %d : func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n" , line_count);
			string strg = $1->get_name() + " " + $2->get_name() + " " + "(" + $4->get_name() + ")" + $7->get_name();

			string cfg_spec = $1->get_name();

			SymbolInfo *s = new SymbolInfo(strg,"func_definition1", cfg_spec);
			$$ = s;
			string news = $$->get_name();
			fprintf(logout, "\n%s\n", news.c_str()); //ok

			return_type = "";

			$$->code = "\n" + $2->get_name() + " PROC\n\n";

			if($2->get_name() != "main")
			{
				string tempid = $2->get_name();
				SymbolInfo *isFound = table->lookup(tempid);

				int i = 0;
				while(i != unicfuncvar.size())
				{
					isFound->set_unic_savedfunc_var(unicfuncvar[i]);

					i++;
				}
				unicfuncvar.clear();

				$$->code = $$->code + "\nPUSH AX\n";
				$$->code = $$->code + "PUSH BX\n";
				$$->code = $$->code + "PUSH CX\n";
				$$->code = $$->code + "PUSH DX\n";

				//cout << "HERE " << endl;
				$$->code = $$->code + $7->code;
				$$->code = $$->code + "labret" + $2->get_name() + ":\n";

				$$->code = $$->code + "\nPOP DX\n";
				$$->code = $$->code + "POP CX\n";
				$$->code = $$->code + "POP BX\n";
				$$->code = $$->code + "POP AX\n";
				$$->code = $$->code + "RET\n";
				$$->code = $$->code + $2->get_name() + " ENDP\n";
			}
			else//jodi main hoy
			{
				$$->code = $$->code + "MOV AX, @DATA\n";
				$$->code = $$->code + "MOV DS, AX\n\n";
				$$->code = $$->code + $7->code;
				$$->code = $$->code + "labret" + $2->get_name();
				$$->code = $$->code + ":\nMOV AH, 4CH\n";
				$$->code = $$->code + "INT 21H\n"; 
				$$->code = $$->code + $2->get_name() + " ENDP\n";//ei lineta hbe kina sure na
				$$->code = $$->code + "END main\n";
			}

			tempusedvar.clear();
		}

		| type_specifier ID LPAREN RPAREN//etay jhamela thakte pare
		{
			
			string temp = $2->get_name();
        	SymbolInfo *isFound = table->lookup(temp);

			if(isFound != 0 && isFound->get_type() == "FUNC_ID")//jodi khuje pay tablee func_id hishebe
			{
				int psize = isFound->get_para_list_size();
				
				if(isFound->get_def_func() == 1)
				{
					fprintf(errorout, "\nError at line no %d : Multiple Definition of function %s\n", line_count, $2->get_name().c_str());
					err_count++;
				}
				else if(isFound->get_def_func() != 1)
				{
					string cur_ret = $1->get_name();

					if(cur_ret == isFound->get_ret_type() && psize == parameters.size() && parameters.size() == 0)
					{
						
						isFound->set_def_func(1);
					}
					if(cur_ret != isFound->get_ret_type())
					{
				
						fprintf(errorout, "\nError at line no %d : Return Type Mismatch\n", line_count);
						err_count++;
					}
					else if(parameters.size() != psize)
					{
						fprintf(errorout, "\nError at line no %d : Number of parameters mismatched with previous declaration\n", line_count);
						err_count++;
					}
				}	
			}
			else if(isFound != 0 && isFound->get_type() != "FUNC_ID")
			{
				fprintf(errorout, "\nError at line no %d : %s is of different type\n", line_count, $2->get_name().c_str());
				err_count++;
			}
			else //jodi khuje na pay
			{
				string spec = $1->get_name();
				SymbolInfo *newnode = new SymbolInfo(temp, "FUNC_ID", spec);
				table->insert(newnode);

				isFound = table->lookup(temp);
				
				isFound->set_def_func(1);
				isFound->set_ret_type($1->get_name());
			}
			return_type = $1->get_name();

			unicvar.push_back($2->get_name() + "ret");

			func_name = $2->get_name();

			//cout << "cing1" << endl;

		}compound_statement
		{
			//cout << "cing2" << endl;
			//cout << $$->code << endl;
			//cout << $6->code << endl;
			fprintf(logout, "\nAt line no %d : func_definition : type_specifier ID LPAREN RPAREN compound_statement\n" , line_count);
			string strg = $1->get_name() + " " + $2->get_name() + " " + "(" + ")" + $6->get_name();

			string cfg_spec = $1->get_name();

			SymbolInfo *s = new SymbolInfo(strg,"func_definition2", cfg_spec);
			$$ = s;
			string news = $$->get_name();
			fprintf(logout, "\n%s\n", news.c_str());

			return_type = "";

			$$->code = "\n" + $2->get_name() + " PROC\n";

			if($2->get_name() != "main")
			{
				string tempid = $2->get_name();
				SymbolInfo *isFound = table->lookup(tempid);

				int i = 0;
				while(i != unicfuncvar.size())
				{
					isFound->set_unic_savedfunc_var(unicfuncvar[i]);

					i++;
				}
				unicfuncvar.clear();

				$$->code = $$->code + "\nPUSH AX\n";
				$$->code = $$->code + "PUSH BX\n";
				$$->code = $$->code + "PUSH CX\n";
				$$->code = $$->code + "PUSH DX\n";

				$$->code = $$->code + $6->code;
				//cout << $$->code << endl;
				$$->code = $$->code + "labret" + $2->get_name() + ":\n";

				$$->code = $$->code + "\nPOP DX\n";
				$$->code = $$->code + "POP CX\n";
				$$->code = $$->code + "POP BX\n";
				$$->code = $$->code + "POP AX\n";
				$$->code = $$->code + "RET\n";
				$$->code = $$->code + $2->get_name() + " ENDP\n";
			}
			else
			{
				$$->code = $$->code + "MOV AX, @DATA\n";
				$$->code = $$->code + "MOV DS, AX\n";
				$$->code = $$->code + $6->code;
				$$->code = $$->code + "labret" + $2->get_name();
				$$->code = $$->code + ":\nMOV AH, 4CH\n";
				$$->code = $$->code + "INT 21H\n"; 
				$$->code = $$->code + $2->get_name() + " ENDP\n";//ei lineta hbe kina sure na
				$$->code = $$->code + "END main\n";
			}
			//cout << $$->code << endl;
			tempusedvar.clear();
		}
 		;				


parameter_list: parameter_list COMMA type_specifier ID
	{
		fprintf(logout, "\nAt line no %d : parameter_list  : parameter_list COMMA type_specifier ID\n" , line_count);
		string strg = $1->get_name() + " " + "," + " " + $3->get_name() + " " + $4->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"parameter_list1");
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		string spec = $3->get_name();
		string temp = $4->get_name();

		int i=0;
		int flag = 0;
		while(i != parameters.size())
		{
			if(parameters[i]->get_name() == temp)
			{
				flag = 1;
				break;
			}
			i++;
		}

		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : Parameter can note be of void type\n",line_count);
			err_count++;
		}
		if(flag == 1)
		{
			fprintf(errorout, "\nError at line no %d : Redefinition of %s\n", line_count, temp.c_str());
			err_count++;
		}
		if(spec != "void" && flag != 1)
		{
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec, "", curid+1); 
			parameters.push_back(para);
			spec_list.push_back(spec);
		}
	}
	| parameter_list COMMA type_specifier
	{
		fprintf(logout, "\nAt line no %d : parameter_list  : parameter_list COMMA type_specifier\n" , line_count);
		string strg = $1->get_name() + " " + "," + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"parameter_list2");
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		string spec = $3->get_name();	
		string temp = "";

		if(spec == "void" || first_param == 1)
		{
			fprintf(errorout, "\nError at line no %d : Void must be the only parameter\n",line_count);
			err_count++;
		}
		
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec, "", curid+1); 
			parameters.push_back(para);
			spec_list.push_back(spec);

		first_param = 0;
	}
 	| type_specifier ID
	{
		fprintf(logout, "\nAt line no %d : parameter_list  : type_specifier ID\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name();

		string cfg_spec = $1->get_name();

		SymbolInfo *s = new SymbolInfo(strg,"parameter_list3", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		string spec = $1->get_name();
		string temp = $2->get_name();

		int i=0;
		int flag = 0;
		while(i != parameters.size())
		{
			if(parameters[i]->get_name() == temp)
			{
				flag = 1;
				break;
			}
			i++;
		}

		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : parameter can not be void type\n",line_count);
			err_count++;
		}
		if(flag == 1)
		{
			fprintf(errorout, "\nError at line no %d : Redefinition of %s\n", line_count, temp.c_str());
			err_count++;
		}
		if(spec != "void" && flag != 1)
		{
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec, "", curid+1); 
			parameters.push_back(para);
			spec_list.push_back(spec);
		}
	}
		| type_specifier
	{
		fprintf(logout, "\nAt line no %d : parameter_list  : type_specifier\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());//ok

		string spec = $1->get_name();	
		string temp = "";

		if(spec != "void")	
		{
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec, "", curid+1); 
			parameters.push_back(para);
			spec_list.push_back(spec);
			
		}
		else if(spec == "void")
		{
			first_param = 1;
		}	
	}	
 		;

 		
compound_statement: LCURL
{
	//cout << "HERE " << endl;
	table->enter_Scope();
	
	int i = 0;
	while(i != parameters.size())
	{
		string temp = parameters[i]->get_name();
		int temp_sid = parameters[i]->get_varid();

		//cout << temp << temp_sid << endl;
		
		/*stringstream ss;
    	ss << curid;
    	string sid=ss.str();
		string unicid = temp + sid;*/

		string spec = spec_list[i];

		SymbolInfo *newnode = new SymbolInfo(temp, "ID", spec, "", temp_sid);
		table->insert(newnode);

		SymbolInfo *isFound = table->current_t_lookup(temp);
		isFound->set_varid(temp_sid);

		stringstream ss;
    	ss << curid;
    	string sid=ss.str();
		string unicid = temp + sid;
		unicvar.push_back(unicid);

		i++;
	}
	parameters.clear();
	spec_list.clear();

	//cout << "bing1" << endl;
    //cout << "return_type--" << return_type << endl;
} statements RCURL	
	{
		//cout << "bing2 " << endl;
		fprintf(logout, "\nAt line no %d : compound_statement : LCURL statements RCURL\n" , line_count);

		string strg = "{\n" + $3->get_name() + "\n}";
		SymbolInfo *s = new SymbolInfo(strg,"compound_statement1"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		
		fprintf(logout, "\n%s\n", news.c_str());//ok

		$$->code = $3->code;

        /*if(retflag == 1)
		    return_type = "";*/

		table->print_all();
		table->exit_Scope();

		//cout << $$->code << endl;
	}
 		    | LCURL
			{
				table->enter_Scope();

				int i = 0;
				while(i != parameters.size())
				{
					string temp = parameters[i]->get_name();
					int temp_sid = parameters[i]->get_varid();
					string spec = spec_list[i];

					SymbolInfo *newnode = new SymbolInfo(temp, "ID", spec, "", temp_sid);
					table->insert(newnode);

					SymbolInfo *isFound = table->current_t_lookup(temp);
					isFound->set_varid(temp_sid);

					stringstream ss;
    				ss << curid;
    				string sid=ss.str();
					string unicid = temp + sid;
					unicvar.push_back(unicid);
		
					i++;
				}
				parameters.clear();
				spec_list.clear();
			} RCURL
			 	{
		fprintf(logout, "\nAt line no %d : compound_statement : LCURL RCURL\n" , line_count);

		string strg = "{\n}";
		SymbolInfo *s = new SymbolInfo(strg,"compound_statement2"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		//return_type = "";

		table->print_all();
		table->exit_Scope();
	}
 		    ;
 		    
var_declaration: type_specifier declaration_list SEMICOLON
	{
		fprintf(logout, "\nAt line no %d : var_declaration : type_specifier declaration_list SEMICOLON\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + ";\n";

		string cfg_spec = $1->get_name();

		SymbolInfo *s = new SymbolInfo(strg,"var_declaration1", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		string spec = $1->get_name();
        if(spec != "void")
        {
            int i = 0;
            while(i != variables.size())
            {
                string temp = variables[i]->get_name();
                SymbolInfo *isFound = table->current_t_lookup(temp);
                if(isFound != 0)
                {
					if(isFound->get_type() == "FUNC_ID")
					{
						fprintf(errorout, "\nError at line no %d : %s is of different type\n", line_count, temp.c_str());
						err_count++;
					}
					else
					{
                    	fprintf(errorout, "\nError at line no %d : Multiple Declaration of %s\n", line_count, temp.c_str());
                    	err_count++;
					}
                }
                else
                {
                    	string name = variables[i]->get_name();//name r temp eki
                    	string type = variables[i]->get_type();
                    	string spec = $1->get_name();
						int vid = variables[i]->get_varid();
						//cout << vid << endl;

						string temparrsize = "";
						if(type == "ARRAY_ID")
						{
							temparrsize = variables[i]->arrsize;
						}

                    	SymbolInfo *newnode = new SymbolInfo(name, type, spec, "0", vid);
                    	table->insert(newnode);

						isFound = table->current_t_lookup(temp);
						//cout << isFound->get_varid() << endl;
						isFound->set_varid(vid);
						//cout << isFound->get_varid() << endl;

						if(isFound->get_type() == "ARRAY_ID")
						{
							stringstream ss;
    						//ss << isFound->get_varid();
							ss << curid;
    						string sid=ss.str();
							string unicid = temp + sid;
							//cout << unicid << endl;
							unicarr.push_back(unicid);
							unicarrsize.push_back(temparrsize);
							//cout << temparrsize << endl;
						}
						else if(isFound->get_type() == "ID")
						{
							//cout << curid << endl;
    						stringstream ss;
    						//ss << isFound->get_varid();
							ss << curid;
    						string sid=ss.str();
							string unicid = temp + sid;
							//cout << unicid << endl;
							unicfuncvar.push_back(unicid);
							unicvar.push_back(unicid);
						}
                }
                i++;
            }
            
        }
        else
        {
            fprintf(errorout, "\nError at line no %d : No type specifier can be void\n", line_count);
            err_count++;
			
        }
		variables.clear();
	}
 		 ;
 		 
type_specifier: INT
	{
		fprintf(logout, "\nAt line no %d : type_specifier	: INT\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
 		| FLOAT
	{
		fprintf(logout, "\nAt line no %d : type_specifier	: FLOAT\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}		 
 		| VOID
		 	{
		fprintf(logout, "\nAt line no %d : type_specifier	: VOID\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
 		;
 		
declaration_list: declaration_list COMMA ID
	{
		fprintf(logout, "\nAt line no %d : declaration_list : declaration_list COMMA ID\n" , line_count);
		string strg = $1->get_name() + "," + $3->get_name();

		string cfg_spec = $3->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"declaration_list1", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $3->get_name();
		string spec = $3->get_spec();
		SymbolInfo *si = new SymbolInfo(temp, "ID", spec, "0", curid);
		//cout << curid << endl;
		variables.push_back(si);
	}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
		fprintf(logout, "\nAt line no %d : declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n" , line_count);
		string strg = $1->get_name() + "," + $3->get_name() + "[" + $5->get_name() + "]";

		string cfg_spec = $3->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"declaration_list2", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		//cout << $5->get_name() << endl;

		string temp = $3->get_name();
		string spec = $3->get_spec();
		SymbolInfo *si = new SymbolInfo(temp, "ARRAY_ID", spec, $5->get_name(), curid);
		//cout << si->arrsize << endl;
		variables.push_back(si);
	}	   
 		  | ID
	{
		fprintf(logout, "\nAt line no %d : declaration_list : ID\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		string spec = $$->get_spec();
		fprintf(logout, "\n%s\n", strg.c_str());

		SymbolInfo *si = new SymbolInfo(strg, "ID", spec, "0", curid);
		variables.push_back(si);
	}		   
 		  | ID LTHIRD CONST_INT RTHIRD
		   {
		fprintf(logout, "\nAt line no %d : declaration_list : ID LTHIRD CONST_INT RTHIRD\n" , line_count);
		string strg = $1->get_name() + "[" + $3->get_name() + "]";

		string cfg_spec = $1->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"declaration_list4", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());
		string temp = $1->get_name();
		string spec = $1->get_spec();
		SymbolInfo *si = new SymbolInfo(temp, "ARRAY_ID", spec, $3->get_name(), curid);
		variables.push_back(si);
	}
 		  ;
 		  
statements: statement
	{
		fprintf(logout, "\nAt line no %d : statements : statement\n" , line_count);
		$$ = $1;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());
		//cout << $$->code << endl;
	}
	   | statements statement
	   {
		fprintf(logout, "\nAt line no %d : statements : statements statement\n" , line_count);
		string strg = $1->get_name() + $2->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"statements2"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		/*string tempcode = $1->code + $2->code;
		$$->code = tempcode;*/
		$$->code = $1->code;
		$$->code += $2->code;
	}
		| error SEMICOLON
		{
			//fprintf(logout, "\nAt line no %d : statements : error SEMICOLON\n" , line_count);
			string strg = "";
			SymbolInfo *s = new SymbolInfo(strg, "error1");
			$$ = s;
			string news = $$->get_name();
			yyclearin;
			yyerrok;
			fprintf(logout, "\n%s\n", news.c_str());
		}
		| error RCURL
		{
			//fprintf(logout, "\nAt line no %d : statements : error SEMICOLON\n" , line_count);
			string strg = "";
			SymbolInfo *s = new SymbolInfo(strg, "error2");
			$$ = s;
			string news = $$->get_name();
			yyclearin;
			yyerrok;
			fprintf(logout, "\n%s\n", news.c_str());
		}
	   ;
	   
statement: var_declaration
	{
		fprintf(logout, "\nAt line no %d : statement : var_declaration\n" , line_count);
		$$ = $1;
		string news = $$->get_name();
		
		fprintf(logout, "\n%s\n", news.c_str());
	}
	  | expression_statement
		{
		fprintf(logout, "\nAt line no %d : statement : expression_statement\n" , line_count);
		$$ = $1;
		string news = $$->get_name();
		
		fprintf(logout, "\n%s\n", news.c_str());

		//cout << $$->code << endl;
	}  
	  | compound_statement
		{
		fprintf(logout, "\nAt line no %d : statement : compound_statement\n" , line_count);
		$$ = $1;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());
	}  
	  | FOR LPAREN expression_statement expression_statement expression RPAREN 
	  {
		  	string spec1 = $3->get_spec();
			string spec2 = $4->get_spec();
			string spec3 = $5->get_spec();

			if(spec2 == "void")
			{
				fprintf(errorout, "\nError at line no %d : Invalid expression in for\n", line_count);
				err_count++;
			}
	  }
	  statement
		{
		fprintf(logout, "\nAt line no %d : statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n" , line_count);
		string strg = "\nfor(" + $3->get_name() + $4->get_name() + $5->get_name() + ")\n" + $8->get_name();
		
		SymbolInfo *s = new SymbolInfo(strg,"statements4");//spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		//$$->code = $3->code;
		char *label1 = newLabel();
		char *label2 = newLabel();

		string templabel1 = string(label1);
		string templabel2 = string(label2);

		$$->code = $3->code;
		$$->code = $$->code + templabel1 + ":\n";
		$$->code = $$->code + $4->code;

		$$->code = $$->code + "\nmov ax," + $4->namewidid + "\n";//ekhane direct $4 hbe na?
		//cout << $4->get_name() << endl;
		$$->code = $$->code + "cmp ax, 0\n";
		//cout << "HERE1--" << templabel2 <<  endl;
		$$->code = $$->code + "je " + templabel2 + "\n";

		$$->code = $$->code + $8->code;
		$$->code = $$->code + $5->code;

		//cout << "HERE2--" << templabel1 <<  endl;
		$$->code = $$->code + "jmp " + templabel1 + "\n";
		$$->code = $$->code + templabel2 + ":\n";
	}  
	  | IF LPAREN expression RPAREN statement %prec IFX
		{
		fprintf(logout, "\nAt line no %d : statement : IF LPAREN expression RPAREN statement\n" , line_count);
		string strg = "\nif(" + $3->get_name() + ")\n" + $5->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"statements5");//spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec = $3->get_spec();
		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d :(inside if) %s is of void type\n", line_count, $3->get_name().c_str());
			err_count++;
		}

		//$$->code = $3->code;

		char *label = newLabel();
		
		$$->code = $3->code;
		$$->code = $$->code + "mov ax," + $3->namewidid + "\n";
		//cout << $3->get_namewidid() << endl;
		$$->code = $$->code + "cmp ax, 0\n";
		//cout << "HERE3--" << string(label) <<  endl;
		$$->code = $$->code + "je " + string(label) + "\n";
		$$->code = $$->code + $5->code;
		$$->code = $$->code + string(label) + ":\n";
	}  
	  | IF LPAREN expression RPAREN statement ELSE statement 
		{
		fprintf(logout, "\nAt line no %d : statement : IF LPAREN expression RPAREN statement ELSE statement\n" , line_count);
		string strg = "\nif(" + $3->get_name() + ")\n" + $5->get_name() + "\nelse\n" + " " + $7->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"statements6");//spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec = $3->get_spec();
		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d :(inside if-else) %s is of void type\n", line_count, $3->get_name().c_str());
			err_count++;
		}

		//$$->code = $3->code;

		char *label1 = newLabel();
		char *label2 = newLabel();

		string templabel1 = string(label1);
		string templabel2 = string(label2);

		$$->code = $3->code;
		$$->code = $$->code + "mov ax," + $3->namewidid + "\n";
		$$->code = $$->code + "cmp ax, 0\n";
		//cout << "HERE4--" << templabel1 <<  endl;
		$$->code = $$->code + "je " + templabel1 + "\n";
		$$->code = $$->code + $5->code + "\n";
		//cout << "HERE5--" << templabel2 <<  endl;
		$$->code = $$->code + "jmp " + templabel2 + "\n";
		$$->code = $$->code + templabel1 + ":\n";
		$$->code = $$->code + $7->code + "\n";
		$$->code = $$->code + templabel2 + ":\n";
	}
	  | WHILE LPAREN expression RPAREN 
	  {
		  	string spec = $3->get_spec();
			if(spec == "void")
			{
				fprintf(errorout, "\nError at line no %d : (inside while)%s is of void type\n", line_count, $3->get_name().c_str());
				err_count++;
			}
	  }
	  statement 
		{
		fprintf(logout, "\nAt line no %d : statement : WHILE LPAREN expression RPAREN statement\n" , line_count);
		string strg = "\nwhile(" + $3->get_name() + ")\n" + $6->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"statements7");//spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		//$$->code = $3->code + "\n";

		char *label1 = newLabel();
		char *label2 = newLabel();

		string templabel1 = (string)label1;
		string templabel2 = (string)label2;

		$$->code = templabel1 + ":\n";
		$$->code = $$->code + $3->code;
		$$->code = $$->code + "mov ax," + $3->namewidid + "\n"; 
		$$->code = $$->code + "cmp ax, 0\n";
		//cout << "HERE6--" << templabel2 <<  endl;
		$$->code = $$->code + "je " + templabel2 + "\n";
		$$->code = $$->code + $6->code;
		//cout << "HERE7--" << templabel1 <<  endl;
		$$->code = $$->code + "jmp " + templabel1 + "\n";
		$$->code = $$->code + templabel2 + ":\n";
	}  
	  | PRINTLN LPAREN ID RPAREN SEMICOLON 
		{
			ifPrint = true;
		fprintf(logout, "\nAt line no %d : statement : PRINTLN LPAREN ID RPAREN SEMICOLON\n" , line_count);
		string strg = $1->get_name() + " " + "(" + $3->get_name() + ")" + ";\n";
		SymbolInfo *s = new SymbolInfo(strg,"statements8"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $3->get_name();
		SymbolInfo *isFound = table->lookup(temp);

		string spec = $3->get_spec();

		if(spec == "void" || (isFound != 0 && isFound->get_spec() == "void"))
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, temp.c_str());
			err_count++;
		}

		if(isFound == 0)
		{
			fprintf(errorout, "\nError at line no %d : Undeclared Variable %s\n", line_count, temp.c_str());
			err_count++;
		}

		stringstream ss;
    	ss << $3->get_varid();
		//cout << "HERE" << table->find_sid($3->get_name()) << endl;
		//cout << "THERE" << $3->get_varid() << endl;
    	string sid=ss.str();
		string unicid = $3->get_name() + sid;

		$$->code = "mov ax," + unicid;
		//$$->code = $$->code + "\npush ax\n";
		$$->code = $$->code + "\ncall println\n";

	}  
	  | RETURN expression SEMICOLON //return 0;
		{
            retflag = 1;
			//cout << "aing" << endl;
			//cout << "V" << endl << endl;
		fprintf(logout, "\nAt line no %d : statement : RETURN expression SEMICOLON\n" , line_count);
		string strg = "\nreturn " + $2->get_name() + ";\n";

		string cfg_spec = $2->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"statements8", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec = $2->get_spec();
		/*if(spec == "void" && return_type != "void")
		{
			fprintf(errorout, "\nError at line no %d : (%s is of void type) Return Type Mismatch\n", line_count, $2->get_name().c_str());
			err_count++;
		}*/

		 if(return_type != $2->get_spec())
		{
			cout << "HERE" << endl;
			cout << "global return type-- " << return_type << endl;
			cout << "$2->get spec-- " << $2->get_spec() << endl;
			fprintf(errorout, "\nError at line no %d : Return Type Mismatch\n", line_count);
			err_count++;
		}
		//return_type = "";

		$$->code = $2->code;
		$$->code = $$->code + "mov ax," + $2->namewidid + "\n";
		$$->code = $$->code + "mov " + func_name + "ret,ax\n";
		$$->code = $$->code + "jmp labret" + func_name + "\n";
	} 
	  ;
	  
expression_statement: SEMICOLON	
	{
		fprintf(logout, "\nAt line no %d : expression_statement : SEMICOLON	\n" , line_count);
		$$ = $1;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		//fprintf(logout, ";\n");
	}		
			| expression SEMICOLON 
		{
		fprintf(logout, "\nAt line no %d : expression_statement 	: expression SEMICOLON	\n" , line_count);
		string strg = $1->get_name() + ";\n";

		string cfg_spec = $1->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"expression_statement2", cfg_spec); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		
		fprintf(logout, "\n%s\n", news.c_str());

		$$->code = $1->code;

		$$->namewidid = $1->namewidid;
		//cout << $$->code << endl;
	}		
			;
	  
variable: ID // a
	{	
		fprintf(logout, "\nAt line no %d : variable : ID\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		string temp = $1->get_name();
		SymbolInfo *isFound = table->lookup(temp);

		if(isFound == 0)
		{
			fprintf(errorout, "\nError at line at %d : Undeclared Variable %s\n", line_count, temp.c_str());
			err_count++;
			SymbolInfo *undefvar = new SymbolInfo(temp, "ID", "undefined");
		}
		else
		{
			if(isFound->get_type() == "ARRAY_ID")
			{
				fprintf(errorout, "\nError at line at %d : Type Mismatch\n", line_count);//, temp.c_str()
				err_count++;
			}
			else if(isFound->get_type() == "FUNC_ID")
			{
				fprintf(errorout, "\nError at line at %d : Type Mismatch\n", line_count);//, temp.c_str()
				err_count++;
			}
			else if(isFound->get_spec() == "void")
			{
				fprintf(errorout, "\nError at line no %d : %s is of Void type\n", line_count, isFound->get_name().c_str());
				err_count++;
			}
			
			$$->set_spec(isFound->get_spec());
			
			stringstream ss;
    		//ss << $1->get_varid();
			int tempsid = table->find_sid($1->get_name());
			ss << tempsid;
    		string sid=ss.str();
			string unicid = $1->get_name() + sid;
			$$->namewidid = unicid;
			//cout << $$->get_namewidid() << endl;
			//cout << "HERE 2" << endl;
		}
	}		
	 | ID LTHIRD expression RTHIRD //a[10]
	{
		fprintf(logout, "\nAt line no %d : variable : ID LTHIRD expression RTHIRD\n" , line_count);
		string strg = $1->get_name() + "[" + $3->get_name() + "]";

		string cfg_spec = $1->get_spec();

		//SymbolInfo *s = new SymbolInfo(strg,"variable2", cfg_spec);
		SymbolInfo *s = new SymbolInfo(strg,"ARRAY_ID", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $1->get_name();
		string spec = $3->get_spec();
		SymbolInfo *isFound = table->lookup(temp);

		if(isFound == 0)
		{
			fprintf(errorout, "\nError at line no %d : Undeclared Variable\n", line_count);
			err_count++;
		}
		else
		{
			if(isFound->get_type() != "ARRAY_ID")
			{
				fprintf(errorout, "\nError at line no %d : %s is not an array\n", line_count, temp.c_str());
				err_count++;
			}
			else if(isFound->get_spec() == "void")
			{
				fprintf(errorout, "\nError at line no %d : %s is of Void type\n", line_count,isFound->get_name().c_str());
				err_count++;
			}
			$$->set_spec(isFound->get_spec());

			stringstream ss;
    		ss << $1->get_varid();
    		string sid=ss.str();
			string unicid = $1->get_name() + sid;
			$$->namewidid = unicid;
			
			$$->code = $3->code;
			$$->code = $$->code + "mov bx," + $3->namewidid + "\n";

			$$->code = $$->code + "add bx, bx\n";
		}
		if(spec != "int")
		{
			fprintf(errorout, "\nError at line no %d : Non-integer Array Index\n", line_count);
			err_count++;

			stringstream ss;
    		ss << $1->get_varid();
    		string sid=ss.str();
			string unicid = $1->get_name() + sid;
			$$->namewidid = unicid;
		}
		

	}	 
	 ;
	 
 expression: logic_expression
 	{
		fprintf(logout, "\nAt line no %d : expression : logic_expression\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		string spec = $1->get_spec();
		$$->set_spec(spec);
		//cout << $$->code << endl;
		//$$->namewidid = $1->namewidid;
	}	
	   | variable ASSIGNOP logic_expression 	
	{
		//cout << $1->get_varid() << endl;
		//cout << $3->get_code() << endl;
		fprintf(logout, "\nAt line no %d : expression : variable ASSIGNOP logic_expression\n" , line_count);
		string strg = $1->get_name() + " " + "=" + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"expression2"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec1 = $1->get_spec();
		string spec2 = $3->get_spec();

		SymbolInfo *isFound = table->lookup($1->get_name());

		if(spec1 == "void" || spec2 == "void")
		{
			string name1 = $1->get_name();
			string name2 = $3->get_name();

			if(spec1 == "void" && spec2 == "void")
			{
				fprintf(errorout, "\nError at line no %d : void type data can not assign or can not be assigned\n", line_count);
				err_count++;
			}
			else if(spec1 == "void")
			{
				fprintf(errorout, "\nError at line no %d : void type data can not assign\n", line_count);
				err_count++;
			}
			else if(spec2 == "void")
			{
				fprintf(errorout, "\nError at line no %d : void type data can not be assigned\n", line_count);
				err_count++;
			}
			
			if(spec2 != "void")
			{
				$$->set_spec(spec2);
			}
			else
			{
				$$->set_spec(spec1);
			}
		}
		else if(spec1 == "")
		{
			$1->set_spec(spec2);
			$$->set_spec(spec2);
			$$->namewidid = $1->namewidid;
		}
		else if(spec1 != spec2 || (isFound != 0 && isFound->get_spec() != spec2))
		{
			fprintf(errorout, "\nError at line no %d : Type Mismatch\n", line_count);
			err_count++;
			$$->set_spec(spec1);
			$$->namewidid = $1->namewidid;
		}
		else
		{
			$$->set_spec(spec1);
			$$->namewidid = $1->namewidid;
		}
		$$->code = $1->code;

        char *temp = newTemp();
        string heretemp = (string)temp;

        if($1->get_type() == "ARRAY_ID")
        {
            $$->code = $$->code + "mov " + heretemp + ",bx\n";
        }

		$$->code = $$->code + $3->code + "\n";
		$$->code = $$->code + "mov ax," + $3->namewidid + "\n";

        //cout << $3->code << endl;
		
		if($1->get_type() == "ARRAY_ID")
		{
            $$->code = $$->code + "mov bx," + heretemp + "\n"; 
			$$->code = $$->code + "mov " + $1->namewidid + "[bx],ax\n";
            //$$->code = $$->code + "add bx, bx\n";

            unicvar.push_back(heretemp);
			tempusedvar.push_back(heretemp);
		}

		if($1->get_type() == "ID")
		{
			$$->code = $$->code + "mov " + $1->namewidid + ",ax\n"; 
		}

        

		//cout << $3->get_name() << endl;
 
		//cout << $$->code << endl;
	}   
	   ;
			
logic_expression: rel_expression 	
	{
		fprintf(logout, "\nAt line no %d : logic_expression : rel_expression \n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		if($1->get_spec() == "")
		{
			$1->set_spec("int");
		}

		string spec = $1->get_spec();
		$$->set_spec(spec);
		//cout << $$->code << endl;
		$$->set_code($1->get_code());
		//$$->namewidid = $1->namewidid;
	}	
		 | rel_expression LOGICOP rel_expression 	
		 {
			 
		fprintf(logout, "\nAt line no %d : logic_expression : rel_expression LOGICOP rel_expression\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"expression2"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec1 = $1->get_spec();
		string spec2 = $3->get_spec();

		string name1 = $1->get_name();
		string name2 = $3->get_name();

		if(spec1 == "void" && spec2 == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s and %s are of void type\n", line_count, name1.c_str(), name2.c_str());
			err_count++;
		}
		else if(spec1 == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, name1.c_str());
			err_count++;
		}
		else if(spec2 == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, name2.c_str());
			err_count++;
		}

		if(($1->get_type() == "ARRAY_ID" && $3->get_type() != "ARRAY_ID") || ($1->get_type() != "ARRAY_ID" && $3->get_type() == "ARRAY_ID"))
		{
			fprintf(errorout, "\nError at line no %d : Type Mismatch\n",line_count);
			err_count++;
		}

        $$->set_spec("int");

		//$$->code = $1->code;
		//$$->code = $$->code + $3->code;

		char *label1 = newLabel();
		char *label2 = newLabel();
		char *label3 = newLabel();

		string templabel1 = (string)label1;
		string templabel2 = (string)label2;
		string templabel3 = (string)label3;

		char *temp = newTemp();
		string heretemp = (string)temp;

		$$->code = $1->code;
		$$->code = $$->code + $3->code + "\n";
		$$->code = $$->code + "mov ax," + $1->namewidid + "\n";
		$$->code = $$->code + "cmp ax, 0\n";

		if($2->get_name() == "&&")
		{
			//cout << "HERE8--" << templabel2 <<  endl;
			$$->code = $$->code + "je " + templabel2 + "\n";
			$$->code = $$->code + "mov ax," + $3->namewidid + "\n";
			$$->code = $$->code + "cmp ax, 0\n";
			//cout << "HERE9--" << templabel2 <<  endl;
			$$->code = $$->code + "je " + templabel2 + "\n";
			//cout << "HERE10--" << templabel1 <<  endl;
			$$->code = $$->code + templabel1 + ":\n";
			$$->code = $$->code + "mov " + heretemp + ",1\n";
			//cout << "HERE11--" << templabel3 <<  endl;
			$$->code = $$->code + "jmp " + templabel3 + "\n";
			//cout << "HERE12--" << templabel2 <<  endl;
			$$->code = $$->code + templabel2 + ":\n";
			$$->code = $$->code + "mov " + heretemp + ",0\n";
		}
		else if($2->get_name() == "||")
		{
			//cout << "HERE13--" << templabel2 <<  endl;
			$$->code = $$->code + "jne " + templabel2 + "\n";
			$$->code = $$->code + "mov ax," + $3->namewidid + "\n";
			$$->code = $$->code + "cmp ax, 0\n";
			//cout << "HERE14--" << templabel2 <<  endl;
			$$->code = $$->code + "jne " + templabel2 + "\n";
			//cout << "HERE15--" << templabel1 <<  endl;
			$$->code = $$->code + templabel1 + ":\n";
			$$->code = $$->code + "mov " + heretemp + ",0\n";
			$$->code = $$->code + "jmp " + templabel3 + "\n";
			//cout << "HERE16--" << templabel2 <<  endl;
			$$->code = $$->code + templabel2 + ":\n";
			$$->code = $$->code + "mov " + heretemp + ",1\n";
		}
		//cout << "HERE17--" << templabel3 <<  endl;
		$$->code = $$->code + templabel3 + ":\n";

		$$->namewidid = heretemp;

		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
	}
		 ;
			
rel_expression: simple_expression
	{
		fprintf(logout, "\nAt line no %d : rel_expression	: simple_expression\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		if($1->get_spec() == "")
		{
			$1->set_spec("int");
		}

		string spec = $1->get_spec();
		$$->set_spec(spec);
		//cout << $$->code << endl;
		//$$->namewidid = $1->namewidid;
	} 
		| simple_expression RELOP simple_expression	
	{
		//cout << $1->get_name() << endl;
		//cout << $3->get_name() << endl;
		fprintf(logout, "\nAt line no %d : rel_expression	: simple_expression RELOP simple_expression\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"rel_expression2"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec1 = $1->get_spec();
		string spec2 = $3->get_spec();

		string name1 = $1->get_name();
		string name2 = $2->get_name();

		if(spec1 == "void" && spec2 == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s and %s are of void type\n", line_count, name1.c_str(), name2.c_str());
			err_count++;
		}
		else if(spec1 == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, name1.c_str());
			err_count++;
		}
		else if(spec2 == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, name2.c_str());
			err_count++;
		}

		if(($1->get_type() == "ARRAY_ID" && $3->get_type() != "ARRAY_ID") || ($1->get_type() != "ARRAY_ID" && $3->get_type() == "ARRAY_ID"))
		{
			fprintf(errorout, "\nError at line no %d : Type Mismatch\n",line_count);
			err_count++;
		}

		$$->set_spec("int");

		$$->code = $1->code;
		$$->code = $$->code + $3->code;
		$$->code = $$->code + "mov ax," + $1->namewidid + "\n";
		$$->code = $$->code + "cmp ax," + $3->namewidid + "\n";

		char *temp = newTemp();
		string heretemp = (string)temp;

		char *label1 = newLabel();
		char *label2 = newLabel();
		string templabel1 = (string)label1;
		string templabel2 = (string)label2;

		if($2->get_name() == "<")
		{
			//cout << "HERE20--" << templabel1 <<  endl;
			$$->code = $$->code + "jl " + templabel1 + "\n";
		}
		else if($2->get_name() == "<=")
		{
			//cout << "HERE21--" << templabel1 <<  endl;
			$$->code = $$->code + "jle " + templabel1 + "\n";
		}
		else if($2->get_name() == ">")
		{
			//cout << "HERE22--" << templabel1 <<  endl;
			$$->code = $$->code + "jg " + templabel1 + "\n";
		}
		else if($2->get_name() == ">=")
		{
			//cout << "HERE23--" << templabel1 <<  endl;
			$$->code = $$->code + "jge " + templabel1 + "\n";
		}
		else if($2->get_name() == "==")
		{
			//cout << "HERE24--" << templabel1 <<  endl;
			$$->code = $$->code + "je " + templabel1 + "\n";
		}
		else if($2->get_name() == "==")
		{
			//cout << "HERE25--" << templabel1 <<  endl;
			$$->code = $$->code + "jne " + templabel1 + "\n";
		}
		$$->code = $$->code + "mov " + heretemp + ",0\n";
		//cout << "HERE26--" << templabel2 <<  endl;
		$$->code = $$->code + "jmp " + templabel2 + "\n";
		//cout << "HERE27--" << templabel1 <<  endl;
		$$->code = $$->code + templabel1 + ":\n";
		$$->code = $$->code + "mov " + heretemp + ",1\n";
		//cout << "HERE28--" << templabel2 <<  endl;
		$$->code = $$->code + templabel2 + ":\n";

		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
		$$->namewidid = heretemp;

	} 	
		;
				
simple_expression: term 
	{
		fprintf(logout, "\nAt line no %d : simple_expression : term\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		if($1->get_spec() == "")
		{
			$1->set_spec("int");
		}

		string spec = $1->get_spec();
		$$->set_spec(spec);
		//cout << "simple_exp : term" << endl;
		//if(line_count == 7) cout << $$->code << endl;;
		//$$->namewidid = $1->namewidid;
	} 
		  | simple_expression ADDOP term 
	{
		fprintf(logout, "\nAt line no %d : simple_expression : simple_expression ADDOP term\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"simple_expression2");
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		string spec1 = $1->get_spec();
		string spec2 = $3->get_spec();

		if(spec1 == "")
		{
			$1->set_spec("int");
			spec1 = "int";
		}
		else if(spec2 == "")
		{
			$1->set_spec("int");
			spec2 = "int";
		}

		if(spec1 == "void" || spec2 == "void")
		{
			fprintf(errorout, "\nError at line no %d : Void type can not be added or subtructed\n", line_count);
			err_count++;
			if(spec1 != "void") 
			{
				$$->set_spec(spec1);
			}
			else if(spec2 != "void") 
			{
				$$->set_spec(spec2);
			}
			else 
			{
				$$->set_spec("int");
			}
		}
		else
		{
			if(spec1 == "float" || spec2 == "float")
			{
				$$->set_spec("float");
			}
			else
			{
				$$->set_spec(spec1);
			}
		}

		$$->code = $1->code;
		$$->code = $$->code + $3->code;

		$$->code = $$->code + "mov ax," + $1->namewidid + "\n";

		char *temp = newTemp();
		string heretemp = (string)temp;

		if($2->get_name() == "+")
		{
			$$->code = $$->code + "add ax, " + $3->namewidid + "\n";
		}
		else
		{
			$$->code = $$->code + "sub ax, " + $3->namewidid + "\n";
		}

		$$->code = $$->code + "mov " + temp + ",ax\n";

		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
		$$->namewidid = heretemp;
	}	  
		  ;
					
term:	unary_expression
	{
		fprintf(logout, "\nAt line no %d : term :	unary_expression\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		if($1->get_spec() == "")
		{
			$1->set_spec("int");
		}

		string spec = $1->get_spec();
		$$->set_spec(spec);
		//cout << "term : unary_exp" << endl;
		//cout << $$->code << endl;
		//$$->namewidid = $1->namewidid;
	} 
     |  term MULOP unary_expression
	 {
		//cout << "HERE line count " << line_count <<  endl;
		fprintf(logout, "\nAt line no %d : term :	term MULOP unary_expression\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + $3->get_name();
		
		string cfg_spec1 = $1->get_spec();
		string cfg_spec2 = $3->get_spec();
		string cfg_spec = "";
		
		SymbolInfo *s = new SymbolInfo(strg,"term2", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec1 = $1->get_spec();
		string spec2 = $3->get_spec();

		string opt = $2->get_name();

		if(spec1 == "")
		{
			$1->set_spec("int");
			spec1 = "int";
		}
		else if(spec2 == "")
		{
			$1->set_spec("int");
			spec2 = "int";
		}

		if(opt == "%")
		{
			if((spec1 != "int" || spec2 != "int"))
			{
				fprintf(errorout, "\nError at line no %d : Non-integer operand on modulus operator\n", line_count);
				err_count++;
			}
			$$->set_spec("int");
		}
		else
		{
			if(spec1 == "void" || spec2 == "void")
			{
				fprintf(errorout, "\nError at line no %d : Void type can not be multipled or divided\n", line_count);
				err_count++;
				if(spec1 != "void") 
				{
					$$->set_spec(spec1);
				}
				else if(spec2 != "void") 
				{
					$$->set_spec(spec2);
				}
				else 
				{
					$$->set_spec("int");
				}
			}
			else
			{
				if(spec1 == "float" || spec2 == "float")
				{
					$$->set_spec("float");
				}
				else
				{
					$$->set_spec(spec1);//basically int
				}
			}
		}

		$$->code = $1->code;
		$$->code = $$->code + $3->code; 
		$$->code = $$->code + "mov ax," + $1->namewidid + "\n";
		//cout << $$->code << endl;
		$$->code = $$->code + "mov bx," + $3->namewidid + "\n";
		//cout << $3->namewidid << endl;
		
		//cout << $1->get_name() << " HERE1 " << $1->namewidid << endl;
		//cout << $3->get_name() << " HERE2 " << $3->namewidid << endl;

		char *temp = newTemp();
		string heretemp = (string)temp;
		//cout << "temp1--" << heretemp << endl;

		if($2->get_name() == "*")
		{
			$$->code = $$->code + "mul bx\n";
			$$->code = $$->code + "mov " + heretemp + ",ax\n";
		}
		else if($2->get_name() == "/")
		{
			$$->code = $$->code + "xor dx, dx\n";
			$$->code = $$->code + "div bx\n";
			$$->code = $$->code + "mov " + heretemp + ",ax\n";
		}
		else
		{
			$$->code = $$->code + "xor dx, dx\n";
			$$->code = $$->code + "div bx\n";
			$$->code = $$->code + "mov " + heretemp + ",dx\n";
		}
		$$->namewidid = heretemp;
		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
		//cout << $$->get_namewidid() << endl;
		//cout << $$->code << endl;
	}
     ;

unary_expression: ADDOP unary_expression  
	{
		fprintf(logout, "\nAt line no %d : unary_expression : ADDOP unary_expression \n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name();

		string cfg_spec = $2->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"unary_expression1",cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		if($2->get_spec() == "")
		{
			$2->set_spec("int");
			$$->set_spec("int");
		}

		string spec = $2->get_spec();

		if(spec != "void")
		{
			$$->set_spec(spec);
		}
		else
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, $2->get_name().c_str());
			err_count++;
			$$->set_spec("int");
		}
		$$->namewidid = $2->namewidid;

		$$->code = $2->code;

		if($1->get_name() == "-")
		{
			$$->code = $$->code + "mov ax," + $2->namewidid + "\n";
			$$->code = $$->code + "neg ax\n";
			$$->code = $$->code + "mov " + $2->namewidid + ",ax\n";
		}
	}
		 | NOT unary_expression 
	{
		fprintf(logout, "\nAt line no %d : unary_expression : NOT unary_expression\n" , line_count);
		string strg = "!" + $2->get_name();

		string cfg_spec = $2->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"unary_expression2");//spec pore set korechi
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		if($2->get_spec() == "")
		{
			$2->set_spec("int");
		}

		string spec = $2->get_spec();

		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count,$2->get_name().c_str());
			err_count++;
		}
		$$->set_spec("int");
		$$->namewidid = $2->namewidid;

		$$->code = $2->code;//ei line ki hbe? hbe ja mone hocche

		/*char *temp = newTemp();
		string heretemp = (string)temp;*/

		$$->code = $$->code + "mov ax," + $2->namewidid + "\n";
		$$->code = $$->code + "not ax\n";
		$$->code = $$->code + "mov " + $2->namewidid + ",ax\n";
	}	 
		 | factor 
	{
		fprintf(logout, "\nAt line no %d : unary_expression : factor\n" , line_count);

		if($1->get_spec() == "")
		{
			$1->set_spec("int");
		}

		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
		//cout << $$->code << endl;
		//$$->namewidid = $1->namewidid;
		//cout << $$->namewidid << endl;
	}	 
		 ;
	
factor: variable 
	{
		//cout << "HERE" << endl;
		//cout << $1->get_type() << endl;
		fprintf(logout, "\nAt line no %d : factor	: variable\n" , line_count);
		
		if($1->get_spec() == "")
		{
			$1->set_spec("int");
		}
		
		$$ = $1;
		
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		string cfg_spec = $1->get_spec();
		$$->set_spec(cfg_spec);

		$$->code = $1->code;

		if($1->get_type() == "ID")
		{
			$$->namewidid = $1->namewidid;
			//cout << $$->namewidid << endl;
		}
		else if($1->get_type() == "ARRAY_ID")
		{
			//cout << "HERE" << endl;
			char *temp = newTemp();
			string heretemp = (string)temp;

			//cout << "temp2--" << heretemp << endl;

			$$->code = $$->code + "mov ax," + $1->namewidid + "[bx]\n";
			$$->code = $$->code + "mov " + heretemp + ",ax\n";
			unicvar.push_back(heretemp);
			tempusedvar.push_back(heretemp);
			$$->namewidid = heretemp;
		}
		 
	}
	| ID LPAREN argument_list RPAREN
	{
		//cout << "HERE" << endl;
		fprintf(logout, "\nAt line no %d : factor	: ID LPAREN argument_list RPAREN\n" , line_count);
		string strg;
		if($3 == NULL)//eta dekhte hbe
		{
			strg = $1->get_name() + "()";
		}
		else
		{
			strg = $1->get_name() + "(" + $3->get_name() + ")";
		}

		if($1->get_spec() == "")
		{
			$1->set_spec("int");
		}
		string cfg_spec = $1->get_spec();
		SymbolInfo *s = new SymbolInfo(strg,"factor2", cfg_spec);
		$$ = s;
		
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $1->get_name();
		SymbolInfo *isFound = table->lookup(temp);

		if(isFound != 0)//jodi khuje pay symbol tablee
		{
			if(isFound->get_type() == "FUNC_ID")
			{
				vector<string> temp_name = isFound->get_savedname();
				vector<string> temp_spec = isFound->get_savedspec();

				int asize = isFound->get_para_list_size();

				if(isFound->get_check_func() == 1 && isFound->get_def_func() != 1)
				{
					if(arguments.size() == 0 && asize != 0)
					{
						fprintf(errorout,"\nError at line no %d: No of arguments mismatched\n",line_count);
						err_count++;
					}
					else
					{
						fprintf(errorout,"\nError at line no %d: Undefined function %s\n",line_count, temp.c_str());
						err_count++;
					}
				}
				else if(isFound->get_def_func() == 1)
				{
					if(asize != arguments.size() == 1)
					{
						fprintf(errorout, "\nError at line no %d : Number of arguments mismatched with previous declaration\n", line_count);
						err_count++;
					}
					else if(asize == arguments.size())
					{
						int i = 0;
						while(i != arguments.size())
						{
							if(arguments[i]->get_spec() != temp_spec[i])
							{
								fprintf(errorout, "\nError at line no %d : Type mismatch\n", line_count);
								err_count++;
								break;
							}

							i++;
						}
					}
				}

				//cout << "HERE" << endl;

				if($3 != NULL) $$->code = $3->code;
				else $$->code = "";

				vector<string> temp_param = isFound->get_savedname();//parametergulo ache temp_parame
				vector<int> temp_sid = isFound->get_savedsid();
				vector<string> temp_funcvar = isFound->get_unic_savedfunc_var();//functionr variables rakhlm

				//cout << "HERE " << endl;

				int i=0;
				while(i != tempusedvar.size())
				{
					$$->code = $$->code + "\nPUSH " + tempusedvar[i] + "\n";
					i++;
				}

				i=0;
				while(i != temp_param.size())
				{
					//tempcode = tempcode + temp_param[i] +"\n";

					$$->code = $$->code + "PUSH " + temp_param[i] + "\n";
					i++;
				}

				i=0;
				while(i != temp_funcvar.size())
				{
					$$->code = $$->code + "PUSH " + temp_funcvar[i] + "\n";
					i++;
				}

				

				i=0;
				while(i != arguments.size())
				{
					/*stringstream ss;
    				ss << arguments[i]->varid;
    				string sid=ss.str();
					string unicid = arguments[i]->get_name() + sid;*/
					string unicid = nameid_list[i];
					$$->code = $$->code + "mov ax," + unicid + "\n";
					//cout << unicid << endl;
					/*stringstream ss2;
					ss2 << parameters[i]->varid;
    				string sid2 = ss.str();
					string unicid2 = parameters[i]->get_name() + sid2;*/
					string unicid2 = temp_name[i];
					$$->code = $$->code + "mov " + unicid2 + ",ax\n";
					//cout << unicid2 << endl;
					i++;
					//ekhane baki ache
				}


				$$->code = $$->code + "call " + $1->get_name() + "\n";

				

				i = temp_funcvar.size() - 1;
				while(i != -1)
				{
					$$->code = $$->code + "\nPOP " + temp_funcvar[i] + "\n";
					i--;
				}

				//cout << "HERE " << endl;

				i = temp_param.size() - 1;
				//cout << "HERE " << endl;
				while(i != -1)
				{
					$$->code = $$->code + "POP " + temp_param[i] + "\n";
					i--;
				}

				i = tempusedvar.size() - 1;
				while(i != -1)
				{
					$$->code = $$->code + "POP " + tempusedvar[i] + "\n";
					i--;
				}

				//tempusedvar.clear();

				$$->code = $$->code + "mov ax," + $1->get_name() + "ret\n";
				char *temp = newTemp();
				string heretemp = (string)temp;

				//cout << "temp3--" << heretemp << endl;
				$$->code = $$->code + "mov " + heretemp + ",ax\n";

				$$->namewidid = temp;
				unicvar.push_back(heretemp);
				tempusedvar.push_back(heretemp);

			}
			else if(isFound->get_type() != "FUNC_ID")
			{
				fprintf(errorout, "\nError at line no %d : Not a function\n", line_count);
				err_count++;
			}
		}
		else//jodi tablee khuje na pay
		{
			fprintf(errorout, "\nError at line no %d : Undefined or Undeclared function %s\n", line_count, temp.c_str());
			err_count++;
		}
		arguments.clear();
		nameid_list.clear();
	}
	| LPAREN expression RPAREN
	{
		fprintf(logout, "\nAt line no %d : factor	: LPAREN expression RPAREN\n" , line_count);
		string strg = "(" + $2->get_name() + ")";

		string cfg_spec = $2->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"factor3", cfg_spec); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		$$->code = $2->code;

		$$->namewidid = $2->namewidid;
	}
	| CONST_INT 
	{
		fprintf(logout, "\nAt line no %d : factor	: CONST_INT\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		$$->set_spec("int");

		char *temp = newTemp();
		string heretemp = (string)temp;
		//cout << "temp4--" << heretemp << endl;
		$$->code = "mov " + heretemp + "," + $1->get_name() + "\n";
		$$->namewidid = heretemp;

		//cout << $$->code << endl;

		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
	}
	| CONST_FLOAT
	{
		fprintf(logout, "\nAt line no %d : factor	: CONST_FLOAT\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		$$->set_spec("float");

		char *temp = newTemp();
		string heretemp = (string)temp;
		//cout << "temp5--" << heretemp << endl;
		$$->code = "mov " + heretemp + "," + $1->get_name() + "\n";
		$$->namewidid = heretemp;

		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
	}
	| variable INCOP 
	{
		fprintf(logout, "\nAt line no %d : factor	: variable INCOP\n" , line_count);
		string strg = $1->get_name() + $2->get_name();

		string cfg_spec = $1->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"factor6", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec = $1->get_spec();
		if(spec != "void")
		{
			$$->set_spec(spec);
		}
		else
		{
			fprintf(errorout, "\nError at line no %d : %s is of Void type\n", line_count, $1->get_name().c_str());
			err_count++;
			$$->set_spec("int");
		}

		char *temp = newTemp();
		string heretemp = (string)temp;
		//cout << "temp6--" << heretemp << endl;

		if($1->get_type() == "ID")
		{
			$$->code = "mov ax," + $1->namewidid + "\n";
			$$->code = $$->code + "mov " + heretemp + ",ax\n";

			$$->code = $$->code + "inc " + $1->namewidid + "\n";
			//$$->code = $$->code + "dec " + $1->namewidid + "\n";
			//$$->code = $$->code + "mov " + $1->namewidid + ",ax\n";
		}
		else if($1->get_type() == "ARRAY_ID")
		{
			$$->code = "mov ax," + $1->namewidid + "[bx]\n";
			$$->code = $$->code + "mov " + heretemp + ",ax\n";
			
			$$->code = $$->code + "mov ax," + $1->namewidid + "[bx]\n";
			$$->code = $$->code + "inc ax\n";
			$$->code = $$->code + "mov " + $1->namewidid + "[bx],ax\n";
		}
		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
		$$->namewidid = heretemp; 
	}
	| variable DECOP
	{
		fprintf(logout, "\nAt line no %d : factor	: variable DECOP\n" , line_count);
		string strg = $1->get_name() + $2->get_name();

		string cfg_spec = $1->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"factor7", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string spec = $1->get_spec();
		if(spec != "void")
		{
			$$->set_spec(spec);
		}
		else
		{
			fprintf(errorout, "\nError at line no %d : %s is of Void type\n", line_count, $1->get_name().c_str());
			err_count++;
			$$->set_spec("int");
		}

		char *temp = newTemp();
		string heretemp = (string)temp;
		//cout << "temp7--" << heretemp << endl;

		if($1->get_type() == "ID")
		{
			$$->code = "mov ax," + $1->namewidid + "\n";
			$$->code = $$->code + "mov " + heretemp + ",ax\n";
			$$->code = $$->code + "dec " + $1->namewidid + "\n";
			//$$->code = $$->code + "dec " + $1->namewidid + "\n";
			//$$->code = $$->code + "mov " + $1->namewidid + ",ax\n";
		}
		else if($1->get_type() == "ARRAY_ID")
		{
			$$->code = "mov ax," + $1->namewidid + "[bx]\n";
			$$->code = $$->code + "mov " + heretemp + ",ax\n";
			$$->code = $$->code + "mov ax," + $1->namewidid + "[bx]\n";
			$$->code = $$->code + "dec ax\n";
			$$->code = $$->code + "mov " + $1->namewidid + "[bx],ax\n";
		}
		unicvar.push_back(heretemp);
		tempusedvar.push_back(heretemp);
		$$->namewidid = heretemp; 
	}
	;
	
argument_list: arguments
	{
		fprintf(logout, "\nAt line no %d : argument_list : arguments\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
			  |
	{
		//cout << "HERE" << endl;
		fprintf(logout, "\nAt line no %d : argument_list : \n" , line_count);
		$$ = NULL;
	}		  
			  ;
	
arguments: arguments COMMA logic_expression
	{
		fprintf(logout, "\nAt line no %d : arguments : arguments COMMA logic_expression\n" , line_count);
		string strg = $1->get_name() + " " + "," + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"arguments1"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $3->get_name();
		string type = $3->get_type();
		string spec = $3->get_spec();
		int tempsid = table->find_sid($3->get_name()); 
		SymbolInfo *arg = new SymbolInfo(temp, type, spec, "", tempsid); 
		arguments.push_back(arg);
		nameid_list.push_back($3->namewidid);

		/*string tempcode = $1->code + $3->code;
		$$->code = tempcode;*/

		$$->code = $1->code;
		$$->code = $$->code + $3->code;
	}
	      | logic_expression
	{
		fprintf(logout, "\nAt line no %d : arguments : logic_expression\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		string temp = $1->get_name();
		string type = $1->get_type();
		string spec = $1->get_spec();
		int tempsid = table->find_sid($1->get_name());
		SymbolInfo *arg = new SymbolInfo(temp, type, spec, "", tempsid); 
		arguments.push_back(arg);
		nameid_list.push_back($1->namewidid);
	}	  
	      ;
 

%%
int main(int argc,char *argv[])
{
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	errorout= fopen("1605071_log.txt","w");
	logout= fopen("1605071_error.txt","w");
	codeout= fopen("1605071_code.asm","w");
	optout= fopen("1605071_optimizedCode.asm","w");
	

	yyin=fp;
	yyparse();
	
	fclose(logout);
	fclose(errorout);
	fclose(codeout);
	fclose(optout);
	fclose(yyin);

	remove("1605071_error.txt");
	
	return 0;
}
