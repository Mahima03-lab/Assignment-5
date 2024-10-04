#include<iostream>
#include<string>
#include<stack>
#include<cmath>


class Expr{
    private:
    std::string expression;//stores the given expression
    
    //checking operator
    bool isOperator(char c)
    {
        if(c=='^'||c=='/'||c=='*'||c=='+'||c=='-')
        return true;
        else
        return false;
    }

    //checking operand
    bool isOperand(char ch)
    {
        if(ch>='0' && ch<='9')
        return true;
        else
        return false;
    }

    //explining precednce
    int precedence(char c)
    {
        if(c=='^')
        return 3 ;
        else if(c=='/'||c=='*')
        return 2 ;
        else if(c=='+'||c=='-')
        return 1 ;
        else
        return -1;
    }

    //evaluating value when given an operator between two operators
    int evaluate(int a,int b, char c)
    {
        if(c=='^')
        return std:: pow(a,b);
        else if(c=='*')
        return a*b;
        else if(c=='/')
        return a/b;
    else if(c=='+')
        return a+b;
    else if(c=='-')
        return a-b;
    }

   //converting given expression to postfix 
   std::string InfixToPostfix(const std::string&  inf)
    {
        std::stack<char> s;
        std::string pof;
        for(int i=0;i<inf.length();i++)
        {
            if((inf[i]>='a'&& inf[i]<='z')||(inf[i]>='A'&&inf[i]<='Z') || (inf[i]>='0' && inf[i]<='9'))
            {
                pof+=inf[i];
            }
            else if(inf[i]=='(')
            {
                s.push(inf[i]);
            }
            else if(inf[i]==')')
            {
                while((s.top()!='(') && (!s.empty()))
                {
                    char temp=s.top();
                    pof+=temp;
                    s.pop();
                }
               
                    s.pop(); 
            }
            else if(isOperator(inf[i]))
            {
                if(s.empty())
                {
                    s.push(inf[i]);
                }
                else
                {
                    if(precedence(inf[i])>precedence(s.top()))
                    {
                        s.push(inf[i]);
                    }
                    else if(precedence(inf[i])==precedence(s.top()) && inf[i]=='^')
                    {
                        s.push(inf[i]);
                    }
                    else
                    {
                        while((!s.empty()) && (precedence(inf[i])<=precedence(s.top())))
                        {
                            char temp=s.top();
                            pof+=temp;
                            s.pop();
                        }
                        s.push(inf[i]);
                    }
                }
            }

            else if(inf[i]==' ')
            {
               continue;
            }
        }
        
        while(!s.empty())
        {
            pof+=s.top();
            s.pop();
        }
       
        return pof;
    }


    //evaluating the postfix expression
    int eval_pof(const std::string&  pof)
    {
        std::stack<int> s;
        for(int i=0;i<pof.length();i++)
        {
            
            if(isOperand(pof[i]))
            {
                s.push(pof[i] - '0');
                
            }
            else if (isOperator(pof[i]))
            {
                int a=s.top();
                s.pop();
                int b=s.top();
                s.pop();
                if(a==0 && pof[i]== '/')
                 std::cout<<"Cannot divide an integer by 0!!\nINVALID INPUT!!";
                else
                {
                    int val=evaluate(b,a,pof[i]);
                    s.push(val);
                }
            }
            else
            {
                std::cout<<"INVALID INPUT!!";
            }
        }

        return s.top();
        
    }


    public:
    // Constructor to initialize the expression
    Expr(const char* expr)  {
        expression = std::string(expr); 
    }

    // Function to evaluate the expression
    int eval() {
        std::string postfix = InfixToPostfix(expression); // Convert to postfix
        return eval_pof(postfix);             // Evaluate postfix
    }

    // Function to print the original expression
    void print() {
        std::cout << "Expression: " << expression <<std:: endl;
    }
};


int main()
{
   
     char user_expr[100];  
    std::cout << "Enter an arithmetic expression: ";
    std::cin.getline(user_expr, 100);  
    Expr value(user_expr);
    value.print();
    std::cout << "REQUIRED RESULT  = " << value.eval() << "\n";
    return 0;
}
   
   
       
     
