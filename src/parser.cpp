#include <iostream>
#include<iostream>
#include<fstream>
#include<ctype.h>
#include<string>

using namespace std;
int line_no; // global declaration of error number


//Top-down parsing; Recursive descent

enum token{
	if_keyword , else_keyword,int_keyword,float_keyword, greater_than_sy, less_than_sy, lparn_sy, rparn_sy, plus_sy, subtract_sy, id , int_sy, real_sy,lcurlybrace_sy,rcurlybrace_sy,semi_colon_sy,comma_sy,equal_op_sy,
	error_sy, end_source_sy
};

class parser{

	private:
		ifstream f;
		token curr_token;
//***************************************
		token check_reserved (string s){
			if (s=="if")
				{ 
					return if_keyword;
				}
			else if (s=="else") 
				{ 
					return else_keyword;
				}
			else if (s=="int")
				 { 
					 return  int_keyword; 
				 }
				 else if (s=="while")
				 { 
					 return  error_sy ; 
				 }


			else if (s=="float")
				 {
					  return  float_keyword;
				 }else return id;
		}
//******************************************
		token get_token(){

			char ch;
			string s;
			int state = 0;


			while(state>=0 && state <=16 && !f.eof()){

				switch(state){
					case 0:
						f.get(ch);
						if (f.eof()) return end_source_sy;
						else if (isspace(ch)) {s=ch; state = 0;}
						else if (isdigit(ch)) {s=ch; state = 1;}
						else if (ch=='.') {s=ch; state = 2;}

						else if (isalpha(ch)) {s=ch; state = 4;} 
						else if (ch=='<') state = 5;
						else if (ch=='>') state = 6;
						else if (ch=='+') state = 7;
						else if (ch=='-') state = 8;
						else if (ch=='(') state = 9;
						else if (ch==')') state = 10;
						else if (ch=='{') state = 11;
						else if (ch=='}') state = 12;
						else if (ch==',') state = 13;
						else if (ch==';') state = 14;
						else if (ch=='=') state=15;

						else state = 16;
						break;

					case 1:
						f.get(ch);	//5555
						if (isdigit(ch)) {s+=ch; state=1;}
						else if (ch=='.') state=3;
						else {f.putback(ch); return int_sy;}
						break;

					case 2:
						f.get(ch);
						if (isdigit(ch)) {s+=ch; state=2;}
						else
						{
							f.putback(ch);
							return real_sy;
						}
						break;

					case 3:
						f.get(ch);
						if (isdigit(ch)) {s+=ch; state=3;}
						else
						{
							f.putback(ch);
							return real_sy;
						}
						break;

					case 4:
						f.get(ch);
						if(isalnum(ch)) {s+=ch; state=4;}
						else
						{
							f.putback(ch); //return extracted input back to inputstring
							return check_reserved(s);

						}
						break;

					case 5:
						//f.get(ch);
						if(ch=='<') return less_than_sy;
						else return error_sy;
						break;

					case 6:
						//f.get(ch);
						if(ch=='>' ) return greater_than_sy;
						else return error_sy;
						break;

					case 7:
						return plus_sy; break;

					case 8:
						return subtract_sy; break;

					case 9:
						return lparn_sy; break;

					case 10:
						return rparn_sy; break;
					case 11:
						return lcurlybrace_sy; break;
					case 12:
						return rcurlybrace_sy; break;
					case 13:
						return comma_sy; break;
					case 14:
					     return semi_colon_sy;  
						
						 break;
						 
					case 15:
					 return equal_op_sy; break;
					
					case 16:
						
						return error_sy; break;


				}
			}
			return end_source_sy;
		}
//****************************************

	string name(token t){

		switch(t){

			case if_keyword: return "if token";break;
			case else_keyword: return "else token";break;
			case int_keyword: return "int token";break;
			case float_keyword: return "float token";break;
			case greater_than_sy: return " > logical operater";break;
			case less_than_sy: return " < logical  operater";break;
			case id: return "identifier";break;
			case int_sy: return "number";break;
			case real_sy: return "decimalno ";break;
			case plus_sy: return "+ operater ";break;
			case subtract_sy: return "- operater ";break;
			case lparn_sy: return "( delimiter";break;
			case rparn_sy: return ") delimiter";break;
			case lcurlybrace_sy: return "{ delimiter";break;
			case rcurlybrace_sy: return "} delimiter";break;
			case semi_colon_sy: return "; delimiter ";break;
			case comma_sy: return ", delimiter ";break;
			case equal_op_sy: return "= equal ";break;
			case error_sy: return "INVALID";break;
			case end_source_sy: return "End of file";break;

		}

		return "error token";
	}
//****************************************

	public:


		parser(string filename){
			f.open(filename.c_str());
		}

		~parser(){
			f.close();
		}
		void match(token terminal){


			if (curr_token == terminal)
                if( name(curr_token) == "int token" )
                {
                    cout<<name(curr_token)<<" is matched >>>>> RULE: dec -> int id " << endl << endl;
                }


               else if( name(curr_token) == "float token" )
               {
                   cout<<name(curr_token)<<" is matched >>>>> RULE : dec -> float id ; >> <expr-seq>" << endl <<endl;
               }
			    else if( f.eof())
               {
                   cout<<name(curr_token)<<" PARSE ACCEPTED" << endl <<endl;
               }


				else
                {


                    // OUR RULES
                   // cout << "<id>      ::= <L> | <id><L-or-D>" << endl;
                   // cout << "<int>     ::= <D> | <int> <D>" << endl;
                    cout<<name(curr_token)<<" is matched == " << name(curr_token) <<endl <<endl;

                }


			else
				syntax_error(curr_token,line_no);
			curr_token = get_token();
		}

		void syntax_error(token terminal , int line ){
			//cout<<name(terminal)<<"  is not expected on " "[" << line << "]" " \n";
			 ReadDataFromStream(f);
			
			
			
			
			 //printf("Not logical value at line number %d in file %s\n", __LINE__, __FILE__);
		}

int getCurrentLine(std::istream& f)
{
    int lineCount = 1;
    f.clear();     // need to clear error bits otherwise tellg returns -1.
    auto originalPos = f.tellg();
    if (originalPos < 0) 
        return -1;
    f.seekg(0);
    char c;
    while ((f.tellg() < originalPos) && f.get(c))
    {
        if (c == '\n') ++lineCount;
    }
    return lineCount;
}

void ReadDataFromStream(std::istream& f)
{
   double x, y, z;
    while (!f.fail() && !f.eof())
    {
        f >> x >> y >> z;
        if (!f.fail())
            std::cout << x << "," << y << "," << z << "\n";
    }

    if (f.fail())
        std::cout << "Error at line: " << getCurrentLine(f) << " Unexpected Token" "\n";
    else
        std::cout << "Read until line: " << getCurrentLine(f) << "\n";
}

	



		void sample_parser(){
			curr_token = get_token();
			program();
			match(end_source_sy);

		}

		//<program> ::= cin  >>  <expr-seq> |  cout  << <expr-seq>

		void program(){
			if(curr_token == if_keyword){
				match(if_keyword);
				//match(greater_than_sy);
				expr_seq();
			}
			else if(curr_token == else_keyword){
				match(else_keyword);
				//match(less_than_sy);
				expr_seq();
			}
			else if(curr_token == int_keyword){
				match(int_keyword);
				//match(less_than_sy);
				expr_seq();
			}
			else if(curr_token == float_keyword){
				match(float_keyword);
				//match(less_than_sy);
				expr_seq();
			}
			else if (curr_token == id)
			{
				match(id);
				expr_seq();
			}
			
			else
				syntax_error(curr_token,line_no);
		}

		//<expr-seq>::= <expr> { <expr> }

		void expr_seq(){
			expr();
			while(curr_token == id || curr_token == int_sy || curr_token == real_sy || curr_token == lparn_sy || curr_token == rparn_sy || curr_token == semi_colon_sy || curr_token == comma_sy || curr_token == less_than_sy || curr_token == greater_than_sy || curr_token ==equal_op_sy || curr_token==else_keyword|| curr_token ==float_keyword || curr_token==if_keyword || curr_token==rcurlybrace_sy || curr_token==lcurlybrace_sy || curr_token==subtract_sy || curr_token == plus_sy) {
				expr();
			}
		}

		//<expr>    ::= <id>|<int> | <real> |  ( + <expr-seq>) | ( * <expr-seq>)

		void expr(){

			switch(curr_token){

				case id: match(id); break;
				case int_sy : match(int_sy);break;
				case real_sy : match(real_sy);break;
				case semi_colon_sy : match(semi_colon_sy);break;
				case comma_sy : match(comma_sy);break;
				case equal_op_sy : match(equal_op_sy);break;
				case float_keyword : match(float_keyword);break;
				case if_keyword : match(if_keyword);break;
				case else_keyword : match(else_keyword);break;

				case greater_than_sy : match(greater_than_sy);break;
				case less_than_sy : match(less_than_sy);break;
				case rparn_sy : match(rparn_sy); break;
				case lcurlybrace_sy : match(lcurlybrace_sy); break;
				case rcurlybrace_sy : match(rcurlybrace_sy); break;
				case subtract_sy : match(subtract_sy); break;
				case plus_sy : match(plus_sy); break;





				case lparn_sy:
					match (lparn_sy);
					if (curr_token == id){
						match (id);
						expr_seq();
						//match(rparn_sy);
					}
					// else if (curr_token == greater_than_sy){
					// 	match (greater_than_sy);
					// 	expr_seq();
					// 	//match(rparn_sy);
					// }
					else if (curr_token == real_sy){
						match (real_sy);
						expr_seq();
						//match(rparn_sy);
					}
					else{
						syntax_error(curr_token, line_no);
					}
					break;

			}


		}


};


int main()
{
    string name;
    cout<<"Enter File Name:"; cin>>name;
    parser p(name);
    p.sample_parser();
    p.~parser();
}
