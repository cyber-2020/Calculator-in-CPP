#include <iostream>
#include<iomanip>
#include <fstream>
#include <string.h>
using namespace std;

//prototypes
int sumNumbers(int [],int,int);
int productNumbers(int[],int,int);
int sumNumbersNonr(int[],int);
int productNumbersNonr(int[],int);

int sumNumbers(int sumList3[],int first,int last)
{
    if(first==last) return sumList3[first];
    else return sumList3[first]+sumNumbers(sumList3,first+1,last);    
}

int productNumbers(int productList3[],int first,int last)
{
    if(first==last) return productList3[first];
    else return productList3[first]*productNumbers(productList3,first+1,last);    
}

int sumNumbersNonr(int sumList4[],int last)
{
    int k,sum=0;
    for(k=0;k<=last;k++)
    {   sum=sum+sumList4[k];   }
    return sum;
}

int productNumbersNonr(int productList4[],int last)
{
    int k,product=1;
    for(k=0;k<=last;k++)
    {   product=product*productList4[k];   }
    return product;
}


int main(int argc,char *argv[])
{
    //Here is how to get the input
    if(argc==2)
    { /*used to get the warning off the screen*/   }
    
    string arg_2 = argv[1];
	int firstequal=arg_2.find("=");
	int semicolon=arg_2.find(";");
	string file_1=arg_2.substr(firstequal+1,semicolon-(firstequal+1));
	int secondequal=arg_2.find("=",semicolon);
	string file_2=arg_2.substr(secondequal+1,1);
    
	//create the output file
	ifstream inFile;
	ofstream outFile;
	outFile.open("calculator.txt", ios::app);
	
    
    //Declare necessary variables and arrays
	const int LENGTH = 81,ROWS=55;
	char input[LENGTH],tempinput[LENGTH],productList[LENGTH],temp[1]; //input[0...i-1],productList[0...j-1], input is i long, productList is j long
	char *plus,*invalidCheck;
	char ch;
    int i=0,j=0,s=0,m,n,p,s2,value1;
    int sumList[ROWS],sumList2[ROWS],productList2[ROWS];
    
    inFile.open(file_1.data());
         
    //Read in the input file into an array
         if(inFile.fail())
         {   
             cout << "Error opening input file!" << endl;
             outFile<<"Error opening input file!"<<endl;
             exit(1);
         }
         else
         {
             
             inFile.get(ch);
             if(ch=='*')
             {   outFile<<"INVALID SEQUENCE"<<endl;   exit(1);   }
             else if(ch=='+')
             {   outFile<<"INVALID SEQUENCE"<<endl;   exit(1);   }
             else
             {   /*do nothing*/   }
         //Now read the input file to arrays    
             while(!inFile.fail())
             {
                 if(ch==' ')
                 {   /*do nothing*/   }
                 else if(ch=='\n')
                 {   /*do nothing*/   }
                 else if(ch=='+')
                 {   
                     productList[j]='+';
                     tempinput[i]='+';//here use if((strlen(tempinput)%2)==1) outFile<<invalid sequence,exit(1)
                     j++;i++;
                 }
                 else if(ch=='*')
                 {   
                     productList[j]='*';
                     tempinput[i]='*';//here use if((strlen(tempinput)%2)==1) outFile<<invalid sequence,exit(1)
                     j++;i++;
                 }
                 else
                 {
                     temp[0]=ch;
                     tempinput[i]=temp[0];
                     i++;
                 }
                 inFile.get(ch); 
             }
             productList[j]='\0';
             tempinput[i]='\0';
             strcpy(input,tempinput);
             
             //Now check for invalid non-integer input
             m=0;
             invalidCheck=strtok(input,"1234567890*+");
             while(invalidCheck!=NULL)
             {
                 m++;
                 invalidCheck=strtok(NULL,"1234567890*+");
             }
             
             //If invalid input, output the result & exit the program
             if(m>0)
             {   outFile<<"INVALID SEQUENCE"<<endl;   exit(1);   }
         
             
             //Now check for invalid multiple * or + input
             plus=strtok(tempinput,"*+");
             while(plus!=NULL) //this loop used to build sumList array
             {
                 value1=atoi(plus);
                 sumList[s]=value1;s++;
                 plus=strtok(NULL,"*+");
             }
             
             //if multiple * or + is detected, output the result
             if((j>0)&&(j+1)!=s)
             {   outFile<<"INVALID SEQUENCE"<<endl;   exit(1);   }
               
         }   
         
         
         
         
         
         
    if(semicolon==-1)            //C A S E   1:   recursive parameter is not given
	{    //recursive=y by default
         //step1: do the multiplications now
         n=0;s2=-1;
         while(n<j)
         {
             if(productList[n]=='*')
             {
                 p=-1;
                 while((n<j)&&(productList[n]=='*'))
                 {
                     p++; 
                     productList2[p]=sumList[n];
                     n++;
                 }
                 p++;
                 productList2[p]=sumList[n];
                 s2++;
                 sumList2[s2]=productNumbers(productList2,0,p);
             }
             else 
             {   
                 if((n<j)&&(productList[n+1]=='*'))
                 {
                     p=-1;n++;
                     while((n<j)&&(productList[n]=='*'))
                     {
                         p++;
                         productList2[p]=sumList[n]; 
                         n++;
                     }
                     p++;
                     productList2[p]=sumList[n];
                     s2++;
                     sumList2[s2]=productNumbers(productList2,0,p);
                 }
                 else
                 {   s2++;n++;sumList2[s2]=sumList[n];   }
             }
         }
         if((j>0)&&(productList[0]=='+'))
         {   s2++;sumList2[s2]=sumList[0];   }
         //all multiplications executed using recursive function and sumList[] arrays decreased to sumList2[]
         
         //Now find the sum using recursive function and output the results
         if(s==0)   //if input file is empty, output 0
         {   outFile<<0<<endl;   }
         else if(s==1)   //if there is only 1 integer is stored in input file, output that integer only
         {   outFile<<sumNumbers(sumList,0,s-1)<<endl;   }
         else   //if input file is large, do: 1.multiplications 2.additions
         {   outFile<<sumNumbers(sumList2,0,s2)<<endl;   }
         
    } 
    else                    //C A S E   2: recursive parameter is given          
    {    //need to check if recursive is y or n
         
         if(file_2=="y")
         {
             //step1: do the multiplications now
             n=0;s2=-1;
             while(n<j)
             {
                 if(productList[n]=='*')
                 {
                     p=-1;
                     while((n<j)&&(productList[n]=='*'))
                     {
                         p++; 
                         productList2[p]=sumList[n];
                         n++;
                     }
                     p++;
                     productList2[p]=sumList[n];
                     s2++;
                     sumList2[s2]=productNumbers(productList2,0,p);
                 }
                 else 
                 {   
                     if((n<j)&&(productList[n+1]=='*'))
                     {
                         p=-1;n++;
                         while((n<j)&&(productList[n]=='*'))
                         {
                             p++;
                             productList2[p]=sumList[n]; 
                             n++;
                         }
                         p++;
                         productList2[p]=sumList[n];
                         s2++;
                         sumList2[s2]=productNumbers(productList2,0,p);
                     }
                     else
                     {   s2++;n++;sumList2[s2]=sumList[n];   }
                 }
             }
             if((j>0)&&(productList[0]=='+'))
             {   s2++;sumList2[s2]=sumList[0];   }
             //all multiplications executed using recursive function and sumList[] arrays decreased to sumList2[]
         
             //Now find the sum using recursive function and output the results
             if(s==0)   //if input file is empty, output 0
             {   outFile<<0<<endl;   }
             else if(s==1)   //if there is only 1 integer is stored in input file, output that integer only
             {   outFile<<sumNumbers(sumList,0,s-1)<<endl;   }
             else   //if input file is large, do: 1.multiplications 2.additions
             {   outFile<<sumNumbers(sumList2,0,s2)<<endl;   }
         }
         else   //recursive=n
         {
             //step1: do the multiplications now
             n=0;s2=-1;
             while(n<j)
             {
                 if(productList[n]=='*')
                 {
                     p=-1;
                     while((n<j)&&(productList[n]=='*'))
                     {
                         p++; 
                         productList2[p]=sumList[n];
                         n++;
                     }
                     p++;
                     productList2[p]=sumList[n];
                     s2++;
                     sumList2[s2]=productNumbersNonr(productList2,p);
                 }
                 else 
                 {   
                     if((n<j)&&(productList[n+1]=='*'))
                     {
                         p=-1;n++;
                         while((n<j)&&(productList[n]=='*'))
                         {
                             p++;
                             productList2[p]=sumList[n]; 
                             n++;
                         }
                         p++;
                         productList2[p]=sumList[n];
                         s2++;
                         sumList2[s2]=productNumbersNonr(productList2,p);
                     }
                     else
                     {   s2++;n++;sumList2[s2]=sumList[n];   }
                 }
             }
             if((j>0)&&(productList[0]=='+'))
             {   s2++;sumList2[s2]=sumList[0];   }
             //all multiplications executed using recursive function and sumList[] arrays decreased to sumList2[]
         
             //Now find the sum using recursive function and output the results
             if(s==0)   //if input file is empty, output 0
             {   outFile<<0<<endl;   }
             else if(s==1)   //if there is only 1 integer is stored in input file, output that integer only
             {   outFile<<sumNumbersNonr(sumList,s-1)<<endl;   }
             else   //if input file is large, do: 1.multiplications 2.additions
             {   outFile<<sumNumbersNonr(sumList2,s2)<<endl;   }
         } 
    }        
    
	outFile.close();
    inFile.close();
    return 0;
}
