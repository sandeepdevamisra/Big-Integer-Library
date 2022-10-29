#include<iostream>
#include<string>
#include<sstream>
#include <chrono>
#define MAX 1000
using namespace std;
using namespace std::chrono;

int top1 = -1;
int top2 = -1;

char stack1[MAX];
string stack2[MAX];

bool stack1_empty()
{
    if(top1 == - 1) return true; 
    return false;
}

bool stack1_full()
{
    if(top1 == MAX - 1) return true;
    return false;
}

void stack1_push(char c)
{
    if(!stack1_full())
    {
        top1++;
        stack1[top1] = c; 
    }
    else cout << "Overflow" << endl;
}

char stack1_pop()
{
    if(!stack1_empty())
    {
        char temp = stack1[top1];
        top1--;
        return temp; 
    }
    else
    {
        cout << "Underflow" << endl;
        return ' ';
    }
}

bool stack2_empty()
{
    if(top2 == - 1) return true; 
    return false;
}

bool stack2_full()
{
    if(top2 == MAX - 1) return true;
    return false;
}

void stack2_push(string s)
{
    if(!stack2_full()) 
    {
        top2++;
        stack2[top2] = s;
    } 
    else cout << "Overflow" << endl;
}

string stack2_pop()
{
    if(!stack2_empty())
    {
        string temp = stack2[top2];
        top2--;
        return temp; 
    }
    else
    {
        cout << "Underflow" << endl;
        return "";
    }
}


void reverse(string &s)
{
    int i=0, j=s.length()-1;
    char temp;
    while(i<=j)
    {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}

bool smaller(string s1, string s2)
{
    if(s1.length() < s2.length()) return true;
    if(s1.length() > s2.length()) return false;
    if(s1.length() == s2.length())
    {
        int i=0;
        while(i<s1.length())
        {
            if((s1[i]-'0') < (s2[i]-'0')) return true;
            else if((s1[i]-'0') > (s2[i]-'0')) return false;
            else i++;
        }
    }

    return false;
}

string add(string s1, string s2)
{
    int sum, carry=0, i=s1.length()-1, j=s2.length()-1;
    string result = "";
    
    while(i>=0 && j>=0)
    {
        sum = (s1[i] - '0') + (s2[j] - '0') + carry;
        carry=0;
        if(sum>9)
        {
            sum-=10; 
            carry=1;
        }
        result += (sum + '0');  
        i--;
        j--;
    }

    while(i>=0)
    {
        sum = (s1[i] - '0') + carry;
        carry=0;
        if(sum>9)
        {
            sum-=10; 
            carry=1;
        }
        result += (sum + '0');  
        i--;
    }

    while(j>=0)
    {
        sum = (s2[j] - '0') + carry;
        carry=0;
        if(sum>9)
        {
            sum-=10; 
            carry=1;
        }
        result += (sum + '0'); 
        
        j--;
    }

    if(carry==1) result += (carry + '0');
    
    reverse(result);

    return result; 
}

string substract(string s1, string s2)
{
    if(s2.length() > s1.length())
    {
        string temp = s1;
        s1 = s2;
        s2 = temp;
    }

    int i=s1.length()-1, j=s2.length()-1, subs, zero_count=0;
    string result = "";


    while(i>=0 && j>=0)
    {
        
        if((s1[i] - '0') < (s2[j] - '0'))
        {
            subs = ((s1[i] - '0') + 10) - (s2[j] - '0');
            if(subs==0) zero_count++;
            int k=i-1;
            while(k>=0 && (s1[k] - '0')==0) 
            {
                if((s1[k] - '0')==0) s1[k]='9';
                k--;
            }
            s1[k] = ((s1[k] - '0') - 1) + '0';
        }

        else
        {
            subs = (s1[i] - '0') - (s2[j] - '0');
            if(subs==0) zero_count++;
        }
        result += (subs + '0');
        i--;
        j--;
    }

    while(i>=0)
    {
        if((s1[i] - '0')==0) zero_count++;
        result += s1[i]; 
        i--;
    }

    if(result.length() == zero_count) return "0";

    reverse(result);
    i=0;
    while(i<result.length() && (result[i] - '0')==0) i++;
    result.erase(result.begin() + 0, result.begin() + i);
    return result;

}

string multiply(string s1, string s2)
{
    if(s2.length() > s1.length())
    {
        string temp = s1;
        s1 = s2;
        s2 = temp;
    }

    int i, j=s2.length()-1, product, carry=0, count=0;
    string result = "", temp;
    
    while(j>=0)
    {
        if(s2[j]==0) temp = "";
        
        else
        {
            i=s1.length()-1;
            temp = "";
            while(i>=0)
            {
                product = (s1[i] - '0')*(s2[j] - '0') + carry;
                carry=0;
                if(product > 9)
                {
                    carry = product/10; 
                    product = product%10;
                }
                temp += (product + '0');
                i--;
            }

            if(carry!=0) 
            {
                temp += (carry + '0');
                carry=0;
            }

            reverse(temp);


            int k = count;
            while(k>0)
            {
                temp += '0';
                k--;
            }
        }
        
        result = add(result, temp);
        count++;
        j--;

    }
    
    return result;
}

string factorial(string s)
{
    if(s == "0") return "1";
    string p = s;
    while(s != "1")
    {
        s = substract(s, "1");
        p = multiply(p, s);
    }

    return p;
}

string exponent(string base, string exp)
{
    string result = base;
    stringstream ss(exp);
    long long int x = 0;
    ss >> x;
    if(x==0) return "1";
    else
    {
        x--;
        
        while(x>0)
        {
            result = multiply(result, base);
            x--;
        }

        return result;
    }

}

string divide(string num, string divisor)
{
    string result = "";
    if(smaller(num, divisor)) return "0";
    while(!smaller(num, divisor))
    {
        num = substract(num, divisor);
        result = add(result, "1");
    }

    return result;

}

string gcd(string a, string b)
{
    string quotient, rem, product; 

    while(true)
    {
        if(b != "0") quotient = divide(a, b);
        product = multiply(quotient, b);
        if(!smaller(a, product)) rem = substract(a, product);
        a = b;
        b = rem;
        if(b == "0") break;
    }

    return a; 
    
}

int precedence(char op)
{
    switch(op)
    {
        case '+':
        case '-': 
            return 1;
        case 'x': 
            return 2;
        default: 
            return -1;
    }
}

string calculator(string s)
{
    
    int k=0;
    string st = "";
    while(k<s.length())
    {
        if(s[k] != '+' && s[k] != 'x' && s[k] != '-') st += s[k];
        if(k==s.length()-1) stack2_push(st);
        if(s[k] == '+' || s[k] == 'x' || s[k] == '-') 
        {
            stack2_push(st);
            st = "";
            if(stack1_empty()) stack1_push(s[k]);
            else if(!stack1_empty())
            {
                if(precedence(s[k]) > precedence(stack1[top1])) stack1_push(s[k]);
         
                else
                {
                    while(!stack1_empty() && (precedence(s[k]) <= precedence(stack1[top1])))
                    {
                        string f_val, s_val;
                        char op;
                        if(!stack2_empty()) s_val = stack2_pop();
                        if(!stack2_empty()) f_val = stack2_pop();
                        op = stack1_pop();
                        if(op == '+') stack2_push(add(f_val, s_val));
                        else if(op == '-') stack2_push(substract(f_val, s_val));
                        else if(op == 'x') stack2_push(multiply(f_val, s_val));
                    }

                    stack1_push(s[k]);
                }
            }
        }

        k++;
    }

    while(!stack1_empty())
    {
        string f_val, s_val;
        char op;
        if(!stack2_empty()) s_val = stack2_pop();
        if(!stack2_empty()) f_val = stack2_pop();
        op = stack1_pop();
        if(op == '+') stack2_push(add(f_val, s_val));
        else if(op == '-') stack2_push(substract(f_val, s_val));
        else if(op == 'x') stack2_push(multiply(f_val, s_val));
    }
    
   return stack2[top2];
}

int main()
{
    string n, input; 
    cin >> n; 
    cin.ignore();
    getline(cin, input);
    stringstream sstream1(n);
    int x = 0;
    sstream1 >> x;

    stringstream sstream2(input); 
    
   if(x==1)
   {
       string s1, s2; 
       sstream2 >> s1;
       sstream2 >> s2;
       cout << exponent(s1, s2);
   }
   else if(x==2)
   {
       string s1, s2; 
       sstream2 >> s1;
       sstream2 >> s2;
       cout << gcd(s1, s2);
   }
   else if(x==3)
   {
       string s; 
       sstream2 >> s;
       cout << factorial(s);
   }

   else if(x==4)
   {
       string s;
       sstream2 >> s; 
       cout << calculator(s);
   }

    

 
}