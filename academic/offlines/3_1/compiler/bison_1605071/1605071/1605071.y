//nanda_kore
%{	
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include <fstream>
#include<vector>
#include "1605071_symboltable.h"
//#define YYSTYPE SymbolInfo*
#define N 71

using namespace std;

vector <SymbolInfo*> variables;//declaration_list
vector <SymbolInfo*> parameters;//parameter_list
vector <SymbolInfo*> arguments;//argument_list
vector <string> spec_list;//eta na holeo cholto kintu amr offlinee age constructore shudhu name r type chilo...spec pore add korchi...spec add korar agei ei spec_list rakhchilm...change kori ny pore r
//vector <string> ret_list;
string return_type = "";//int add(){} int holo return_type
string ret_ex;//int add(int a, int b){return a+b} a+b er type holo ret_ex;
int first_param = 0;

int yyparse(void);
int yylex(void);
int curid;//eta amr scopetable gulor id
string var[26];

FILE *fp;
FILE *logout;
FILE *errorout;

extern FILE *yyin;
int line_count = 1;
int err_count = 0; 
extern int yytext;

SymbolTable *table = new SymbolTable(N);


void yyerror(char *s)
{
	//write your code
	fprintf(errorout, "\nError at line no %d : %s at %s\n", line_count, s, yytext);
	err_count++;
}


%}

//%error-verbose

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

//ami shob venge venge korchi, jmn : string temp = $$->get_name(); printf("%s",temp.c_str());

%%

start: program
	{
		//cout << "A" << endl << endl;
		//write your code in this block in all the similar blocks below
		//fprintf(logout, "\nAt line no: %d start : program\n" , line_count);
		fprintf(logout, "          symbol table:\n\n");
		table->print_all();
		fprintf(logout,"\nTotal lines : %d\n\nTotal errors : %d",line_count,err_count);
		fprintf(errorout,"\nTotal errors : %d",err_count);
	}
	;

program: program unit
	{
		//cout << "B" << endl << endl;
		fprintf(logout, "\nAt line no %d :program : program unit\n" , line_count);
		string strg = $1->get_name() + $2->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"Program1"); // spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());
	}
	| unit
	{
		//cout << "C" << endl << endl;
		fprintf(logout, "\nAt line no %d :program : unit\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
	;
	
unit: var_declaration
	{
		//cout << "D" << endl << endl;
		fprintf(logout, "\nAt line no %d :unit : var_declaration\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}		
     | func_declaration
	 {
		 //cout << "E" << endl << endl;
		fprintf(logout, "\nAt line no %d :unit : func_declaration\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}	
     | func_definition
	 {
		 //cout << "F" << endl << endl;
		fprintf(logout, "\nAt line no %d : unit : func_definition\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
     ;
     
func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
	{
		//cout << "G" << endl << endl;
		fprintf(logout, "\nAt line no %d : func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + "(" + $4->get_name() + ")" + ";\n";

		string cfg_spec = $1->get_name();

		SymbolInfo *s = new SymbolInfo(strg,"func_declaration1", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str()); //ok

		string temp = $2->get_name();
		SymbolInfo *isFound = table->lookup(temp);

		//cout << temp << endl;

		if(isFound != 0) //jodi sym tablee age thekei thk 
		{
			//if(isFound->get_type() == "FUNC_ID" &&  isFound->get_check_func() == 1)
			if(isFound->get_type() == "FUNC_ID")
			{
				/*if(isFound->get_check_func() == 1)
				{
					fprintf(errorout, "\nError at line no %d : Multiple Declaration of function %s\n", line_count, $2->get_name().c_str());
					err_count++;
				}*/

				if(isFound->get_check_func() != 1)
				{
					vector<string> temp_name = isFound->get_savedname();
					vector<string> temp_spec = isFound->get_savedspec();

				//isFound->set_para_list_size(temp_spec);
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
							//fprintf(errorout, "\nError at line no %d : func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n", line_count);
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
				
			}
			/*else if(isFound->get_type() == "FUNC_ID" && isFound->get_def_func() == 1)
			{
				string cur_ret = $1->get_name();
				if(cur_ret != isFound->get_ret_type())
				{
					fprintf(errorout, "\nError at line no %d : Return Type Mismatch\n", line_count);
					err_count++;
				}
			}*/
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
			//cout << strg << endl;
			vector<string> temp_spec = isFound->get_savedspec();

			isFound->set_para_list_size(temp_spec);
		}

		parameters.clear();
		spec_list.clear();
	}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		
		{
			//cout << "H" << endl << endl;
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
			//if(isFound->get_type() == "FUNC_ID" &&  isFound->get_check_func() == 1)
			if(isFound->get_type() == "FUNC_ID")
			{
				int psize = isFound->get_para_list_size();
				/*if(isFound->get_check_func() == 1)
				{
					fprintf(errorout, "\nError at line no %d : Multiple Declaration of function %s\n", line_count, $2->get_name().c_str());
					err_count++;
				}*/
				
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
			/*else if(isFound->get_type() == "FUNC_ID" && isFound->get_def_func() == 1)
			{
				string cur_ret = $1->get_name();
				if(cur_ret != isFound->get_ret_type())
				{
					fprintf(errorout, "\nError at line no %d : Return Type Mismatch\n", line_count);
					err_count++;
				}
			}*/
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
{		//cout << "I" << endl << endl;	

		string temp = $2->get_name();
        SymbolInfo *isFound = table->lookup(temp);

        if(isFound != 0 && isFound->get_type() == "FUNC_ID")//jodi khuje pay
        {	
			if(isFound->get_def_func() == 1)
			{
				fprintf(errorout, "\nError at line no %d : Multiple definition of function %s\n", line_count, temp.c_str());
				err_count++;
			}
			//ekhan thk comment out korbo
			else if(isFound->get_def_func() != 1)
			{
				vector<string> temp_name = isFound->get_savedname();
				vector<string> temp_spec = isFound->get_savedspec();

            //isFound->set_para_list_size(temp_spec);
				int psize = isFound->get_para_list_size();

            	string cur_ret = $1->get_name();
				//cout << "psize " << psize << endl;
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
						//fprintf(errorout, "\nError at line no %d : func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n", line_count);
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
            
        }
		else if(isFound != 0 && isFound->get_type() != "FUNC_ID")
		{
			fprintf(errorout, "\nError at line no %d : %s is of different type\n", line_count, $2->get_name().c_str());
			err_count++;
		}
        else //jodi khuje na pay
        {
			//cout << "in func_def : khuje pay ny var prothome" << endl;
			string spec = $1->get_name();
            SymbolInfo *newnode = new SymbolInfo(temp, "FUNC_ID", spec);
			table->insert(newnode);

            isFound = table->lookup(temp);
			//isFound->set_check_func(1);
			isFound->set_def_func(1);
			isFound->set_ret_type($1->get_name());

			//cout << "Parameters size : (ekhane jhamela)  " << parameters.size() << endl;
			//cout << "spec list size: " << spec_list.size() << endl;

            int i = 0;
			while(i != parameters.size())
			{
				//cout << "HERE" << endl;
				string name = parameters[i]->get_name();
				string type = parameters[i]->get_type();
				string spec = spec_list[i];

				isFound->set_savedparam(name, spec);

				i++;
			}
			vector<string> temp_spec = isFound->get_savedspec();

			isFound->set_para_list_size(temp_spec);
        }
		//parameters.clear();
		//spec_list.clear();
		return_type = $1->get_name();

}		compound_statement
		{
			fprintf(logout, "\nAt line no %d : func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement\n" , line_count);
			string strg = $1->get_name() + " " + $2->get_name() + " " + "(" + $4->get_name() + ")" + $7->get_name();

			string cfg_spec = $1->get_name();

			SymbolInfo *s = new SymbolInfo(strg,"func_definition1", cfg_spec);
			$$ = s;
			string news = $$->get_name();
			fprintf(logout, "\n%s\n", news.c_str()); //ok
		}

		| type_specifier ID LPAREN RPAREN//etay jhamela thakte pare
		{
			//cout << "J" << endl << endl;
		
			string temp = $2->get_name();
        	SymbolInfo *isFound = table->lookup(temp);

			if(isFound != 0 && isFound->get_type() == "FUNC_ID")//jodi khuje pay tablee func_id hishebe
			{
				int psize = isFound->get_para_list_size();
				//cout << "psize " << psize << endl;
				//cout << "cur_ret " << cur_ret << endl;
				//cout << "get_ret_type " << isFound->get_ret_type() << endl;
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
				//isFound->set_check_func(1);
				isFound->set_def_func(1);
				isFound->set_ret_type($1->get_name());
			}
			return_type = $1->get_name();
		}compound_statement
		{
			fprintf(logout, "\nAt line no %d : func_definition : type_specifier ID LPAREN RPAREN compound_statement\n" , line_count);
			string strg = $1->get_name() + " " + $2->get_name() + " " + "(" + ")" + $6->get_name();

			string cfg_spec = $1->get_name();

			SymbolInfo *s = new SymbolInfo(strg,"func_definition2", cfg_spec);
			$$ = s;
			string news = $$->get_name();
			fprintf(logout, "\n%s\n", news.c_str());

		}
 		;				


parameter_list: parameter_list COMMA type_specifier ID
	{
		//cout << "K" << endl << endl;
		fprintf(logout, "\nAt line no %d : parameter_list  : parameter_list COMMA type_specifier ID\n" , line_count);
		string strg = $1->get_name() + " " + "," + " " + $3->get_name() + " " + $4->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"parameter_list1");
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		//printf("\n%s\n", news.c_str());

		//cout << "HERE " << endl;

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
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
			parameters.push_back(para);
			spec_list.push_back(spec);
		}

		/*SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
		parameters.push_back(para);
		spec_list.push_back(spec);

		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : parameter can not be void type\n",line_count);
			err_count++;
		}*/
		
	}
	| parameter_list COMMA type_specifier
	{
				//cout << "L" << endl << endl;
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
		//else
		//{
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
			parameters.push_back(para);
			spec_list.push_back(spec);

		//}
		first_param = 0;

		/*SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
		parameters.push_back(para);
		spec_list.push_back(spec);

		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : parameter can not be void type\n",line_count);
			err_count++;
		}*/
	}
 	| type_specifier ID
	{
			 //cout << $1->get_name() << endl;
			 //cout << "M" << endl << endl;
		fprintf(logout, "\nAt line no %d : parameter_list  : type_specifier ID\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name();

		string cfg_spec = $1->get_name();

		SymbolInfo *s = new SymbolInfo(strg,"parameter_list3", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok
		//cout << $$->get_spec() << endl;

		//cout << strg << endl;

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
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
			parameters.push_back(para);
			spec_list.push_back(spec);
		}

		/*SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
		parameters.push_back(para);
		spec_list.push_back(spec);

		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : parameter can not be void type\n",line_count);
			err_count++;
		}*/

	}
		| type_specifier
	{
		//cout << "N" << endl << endl;
		fprintf(logout, "\nAt line no %d : parameter_list  : type_specifier\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());//ok

		string spec = $1->get_name();	
		string temp = "";

		/*if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : parameter can not be void type\n",line_count);
			err_count++;
		}*/
		//else
		//{
		if(spec != "void")	
		{
			SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
			parameters.push_back(para);
			spec_list.push_back(spec);
			
		}
		else if(spec == "void")
		{
			first_param = 1;
		}	
		//}

		/*SymbolInfo *para = new SymbolInfo(temp, "ID", spec); 
		parameters.push_back(para);
		spec_list.push_back(spec);
		
		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : parameter can not be void type\n",line_count);
			err_count++;
		}*/
	}	
 		;

 		
compound_statement: LCURL
{
	table->enter_Scope();
	
	int i = 0;
	while(i != parameters.size())
	{
		string temp = parameters[i]->get_name();
		string spec = spec_list[i];
		//cout << "i "<< spec << endl;

		SymbolInfo *newnode = new SymbolInfo(temp, "ID", spec);
		table->insert(newnode);

		i++;
	}
	parameters.clear();
	spec_list.clear();
} statements RCURL	
	{
		//cout << "O" << endl << endl;
		fprintf(logout, "\nAt line no %d : compound_statement : LCURL statements RCURL\n" , line_count);

		string strg = "{\n" + $3->get_name() + "\n}";
		SymbolInfo *s = new SymbolInfo(strg,"compound_statement1"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		
		fprintf(logout, "\n%s\n", news.c_str());//ok

		//return_type = "";
		table->print_all();
		table->exit_Scope();
	}
 		    | LCURL
			{
				table->enter_Scope();

				int i = 0;
				while(i != parameters.size())
				{
					string temp = parameters[i]->get_name();
					string spec = spec_list[i];

					SymbolInfo *newnode = new SymbolInfo(temp, "ID", spec);
					table->insert(newnode);
		
					i++;
				}
				parameters.clear();
				spec_list.clear();
			} RCURL
			 	{
					 //cout << "P" << endl << endl;
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
		//cout << "Q" << endl << endl;
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
					/*if(variables[i]->get_type() == "ARRAY_ID")
					{

					}*/
					//else
					//{
                    	string name = variables[i]->get_name();
                    	string type = variables[i]->get_type();
                    	string spec = $1->get_name();

                    	SymbolInfo *newnode = new SymbolInfo(name, type, spec);
                    	table->insert(newnode);
					//}
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
		//cout << "R" << endl << endl;
		fprintf(logout, "\nAt line no %d : declaration_list : declaration_list COMMA ID\n" , line_count);
		string strg = $1->get_name() + "," + $3->get_name();

		string cfg_spec = $3->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"declaration_list1", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $3->get_name();
		string spec = $3->get_spec();
		SymbolInfo *si = new SymbolInfo(temp, "ID", spec);
		variables.push_back(si);
	}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		{
			//cout << "S" << endl << endl;
		fprintf(logout, "\nAt line no %d : declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n" , line_count);
		string strg = $1->get_name() + "," + $3->get_name() + "[" + $5->get_name() + "]";

		string cfg_spec = $3->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"declaration_list2", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $3->get_name();
		string spec = $3->get_spec();
		SymbolInfo *si = new SymbolInfo(temp, "ARRAY_ID", spec);
		variables.push_back(si);
	}	   
 		  | ID
	{
		//cout << "T" << endl << endl;
		fprintf(logout, "\nAt line no %d : declaration_list : ID\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		string spec = $$->get_spec();
		fprintf(logout, "\n%s\n", strg.c_str());

		SymbolInfo *si = new SymbolInfo(strg, "ID", spec);
		variables.push_back(si);
	}		   
 		  | ID LTHIRD CONST_INT RTHIRD
		   {
			   //cout << "U" << endl << endl;
		fprintf(logout, "\nAt line no %d : declaration_list : ID LTHIRD CONST_INT RTHIRD\n" , line_count);
		string strg = $1->get_name() + "[" + $3->get_name() + "]";

		string cfg_spec = $1->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"declaration_list4", cfg_spec);
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $1->get_name();
		string spec = $1->get_spec();
		SymbolInfo *si = new SymbolInfo(temp, "ARRAY_ID", spec);
		variables.push_back(si);
	}
 		  ;
 		  
statements: statement
	{
		fprintf(logout, "\nAt line no %d : statements : statement\n" , line_count);
		$$ = $1;
		string news = $$->get_name();
		//cout << "AGIAN " << news << endl;
		fprintf(logout, "\n%s\n", news.c_str());
	}
	   | statements statement
	   {
		fprintf(logout, "\nAt line no %d : statements : statements statement\n" , line_count);
		string strg = $1->get_name() + $2->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"statements2"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());
	}
		| error SEMICOLON
		{
			fprintf(logout, "\nAt line no %d : statements : error SEMICOLON\n" , line_count);
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
			fprintf(logout, "\nAt line no %d : statements : error SEMICOLON\n" , line_count);
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

			//cout << "line " << line_count << " " << spec1 << " -- " << spec2 << " -- " << spec3 << endl;

			if(spec2 == "void")
			{
			//fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, $3->get_name().c_str());
				fprintf(errorout, "\nError at line no %d : Invalid expression in for\n", line_count);
				err_count++;
			}
	  }
	  statement
		{
		fprintf(logout, "\nAt line no %d : statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n" , line_count);
		string strg = "\nfor(" + $3->get_name() + $4->get_name() + $5->get_name() + ")\n" + $8->get_name();
		//cout << "HERE2 " << $4->get_name() << endl;
		SymbolInfo *s = new SymbolInfo(strg,"statements4");//spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());
		
		/*string spec = $3->get_spec();

		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, $3->get_name());
			err_count++;
		}*/
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

		/*string spec = $3->get_spec();
		if(spec == "void")
		{
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, $3->get_name().c_str());
			err_count++;
		}*/
	}  
	  | PRINTLN LPAREN ID RPAREN SEMICOLON 
		{
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
	}  
	  | RETURN expression SEMICOLON //return 0;
		{
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
			//cout << "HERE" << endl;
			//cout << "global return type " << return_type << endl;
			//cout << "$2->get spec " << $2->get_spec() << endl;
			fprintf(errorout, "\nError at line no %d : Return Type Mismatch\n", line_count);
			err_count++;
		}
		return_type = "";
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
	}		
			;
	  
variable: ID // a
	{	
		fprintf(logout, "\nAt line no %d : variable : ID\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
		
		//cout << $$->get_name() << "  " << $$->get_spec() << "  type"<< endl;

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
				//fprintf(errorout, "\nError at line at %d : variable : ID\n", line_count, temp.c_str());
				
				fprintf(errorout, "\nError at line at %d : Type Mismatch\n", line_count, temp.c_str());
				err_count++;
			}
			else if(isFound->get_type() == "FUNC_ID")
			{
				fprintf(errorout, "\nError at line at %d : Type Mismatch\n", line_count, temp.c_str());
				err_count++;
			}
			else if(isFound->get_spec() == "void")
			{
				fprintf(errorout, "\nError at line no %d : %s is of Void type\n", line_count,isFound->get_name());
				err_count++;
			}
			
			$$->set_spec(isFound->get_spec());
			
		}
	}		
	 | ID LTHIRD expression RTHIRD //a[10]
	{
		//cout << "W" << endl << endl;
		fprintf(logout, "\nAt line no %d : variable : ID LTHIRD expression RTHIRD\n" , line_count);
		string strg = $1->get_name() + "[" + $3->get_name() + "]";

		string cfg_spec = $1->get_spec();

		SymbolInfo *s = new SymbolInfo(strg,"variable2", cfg_spec);
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
				//fprintf(errorout, "\nError at line no %d : ID LTHIRD expression RTHIRD\n", line_count);
				fprintf(errorout, "\nError at line no %d : %s is of Void type\n", line_count,isFound->get_name());
				err_count++;
			}
			$$->set_spec(isFound->get_spec());
		}
		if(spec != "int")
		{
			fprintf(errorout, "\nError at line no %d : Non-integer Array Index\n", line_count);
			err_count++;
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
		//cout << "HERE1 " << spec << endl;
	}	
	   | variable ASSIGNOP logic_expression 	
	{
		//cout << "W" << endl << endl;
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
				//cout << spec2 << endl;
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
			// ekhane kar spec set korbo? $3 naki $$?
		}
		else if(spec1 == "")
		{
			//cout << $1->get_name() << "  spec " << $1->get_spec() << "  type " << endl;
			//cout << "\nForcefully set korchi" << endl;
			$1->set_spec(spec2);
			$$->set_spec(spec2);
		}
		else if(spec1 != spec2 || (isFound != 0 && isFound->get_spec() != spec2))
		{
			//cout << $1->get_name() << "  spec " << $1->get_spec() << "  type " << endl;
			//cout << $3->get_name() << "  spec " << $3->get_spec() << "  type " << endl;
			//fprintf(errorout, "\nError at line no %d : variable ASSIGNOP logic_expression \n", line_count);
			fprintf(errorout, "\nError at line no %d : Type Mismatch\n", line_count);
			err_count++;
			//cout << "forcefully set korechi" << endl;
			$$->set_spec(spec1);
		}
		else
		{
			$$->set_spec(spec1);
		}
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
	}	
		 | rel_expression LOGICOP rel_expression 	
		 {
			 //cout << "X" << endl << endl;
		fprintf(logout, "\nAt line no %d : logic_expression : rel_expression LOGICOP rel_expression\n" , line_count);
		string strg = $1->get_name() + "" + $2->get_name() + " " + $3->get_name();
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
	} 
		| simple_expression RELOP simple_expression	
	{
		//cout << "Y" << endl << endl;
		fprintf(logout, "\nAt line no %d : rel_expression	: simple_expression RELOP simple_expression\n" , line_count);
		string strg = $1->get_name() + "" + $2->get_name() + " " + $3->get_name();
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
	} 
		  | simple_expression ADDOP term 
	{
		//cout << "Z" << endl << endl;
		fprintf(logout, "\nAt line no %d : simple_expression : simple_expression ADDOP term\n" , line_count);
		string strg = $1->get_name() + " " + $2->get_name() + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"simple_expression2");
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());//ok

		string spec1 = $1->get_spec();
		string spec2 = $3->get_spec();

		//cout << spec1 << " " << $1->get_name() << endl;
		//cout << spec2 << " " << $3->get_name() << endl;

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
	} 
     |  term MULOP unary_expression
	 {
		 //cout << "ene" << endl << endl;
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

		//cout << "kon cond ta age hbe?" << endl;

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
				//cout << "egulo ki int set kora lagbe?\n" << endl;
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
	}
     ;

unary_expression: ADDOP unary_expression  
	{
		//cout << "eme" << endl << endl;
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
			//fprintf(errorout, "\nError at line no %d : ADDOP unary_expression\n", line_count);
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count, $2->get_name().c_str());
			err_count++;
			$$->set_spec("int");
		}
	}
		 | NOT unary_expression 
	{
		//cout << "pe" << endl << endl;
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
			//fprintf(errorout, "\nError at line no %d : NOT unary_expression\n", line_count);
			fprintf(errorout, "\nError at line no %d : %s is of void type\n", line_count,$2->get_name().c_str());
			err_count++;
		}
		$$->set_spec("int");
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

		//cout << "name  " << $$->get_name() << "  spec  " << $$->get_spec() << endl;
	}	 
		 ;
	
factor: variable 
	{
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
	}
	| ID LPAREN argument_list RPAREN
	{
		//cout << "qu" << endl << endl;
		//cout << line_count << endl;
		fprintf(logout, "\nAt line no %d : factor	: ID LPAREN argument_list RPAREN\n" , line_count);
		string strg;
		if($3 == NULL)
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
		//cout << "HERE " << $1->get_spec() << endl;
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
	}
	| CONST_INT 
	{
		fprintf(logout, "\nAt line no %d : factor	: CONST_INT\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		$$->set_spec("int");
	}
	| CONST_FLOAT
	{
		fprintf(logout, "\nAt line no %d : factor	: CONST_FLOAT\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		$$->set_spec("float");
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
	}
	;
	
argument_list: arguments
	{
		//cout << "iie" << endl << endl;
		fprintf(logout, "\nAt line no %d : argument_list : arguments\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());
	}
			  |
	{
		fprintf(logout, "\nAt line no %d : argument_list : \n" , line_count);
		$$ = NULL;
	}		  
			  ;
	
arguments: arguments COMMA logic_expression
	{
		//cout << "shi" << endl << endl;
		fprintf(logout, "\nAt line no %d : arguments : arguments COMMA logic_expression\n" , line_count);
		string strg = $1->get_name() + " " + "," + " " + $3->get_name();
		SymbolInfo *s = new SymbolInfo(strg,"arguments1"); //spec kichu lagbe?
		$$ = s;
		string news = $$->get_name();
		fprintf(logout, "\n%s\n", news.c_str());

		string temp = $3->get_name();
		string type = $3->get_type();
		string spec = $3->get_spec();
		SymbolInfo *arg = new SymbolInfo(temp, type, spec); 
		arguments.push_back(arg);
	}
	      | logic_expression
	{
		//cout << "shu" << endl << endl;
		fprintf(logout, "\nAt line no %d : arguments : logic_expression\n" , line_count);
		$$ = $1;
		string strg = $$->get_name();
		fprintf(logout, "\n%s\n", strg.c_str());

		string temp = $1->get_name();
		string type = $1->get_type();
		string spec = $1->get_spec();
		SymbolInfo *arg = new SymbolInfo(temp, type, spec); 
		arguments.push_back(arg);
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

	//SymbolInfo *p=new SymbolInfo("n","p");
	//cout<<p->get_name() <<endl;

	logout= fopen("1605071_log.txt","w");
	errorout= fopen("1605071_error.txt","w");
	

	yyin=fp;
	yyparse();
	/*do yyparse();
	while(!feof(yyin));*/
	//fprintf(errorout,"\n\nTotal errors : %d",err_count);
	
	fclose(logout);
	fclose(errorout);
	fclose(yyin);
	
	return 0;
}
