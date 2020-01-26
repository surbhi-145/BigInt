/**
   4.Multiply
   5. Switch case in main
   6. Exception handling
   **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef enum
{
    FAILURE,
    SUCCESS
} statuscode;

typedef struct bigInt
{
    int *data;
    char number[INT_MAX];
    int sign; //1 for positive ,-1 for negative

} bigInt;

void print(bigInt **a)
{
    printf("---------------------------------\n");
    printf("Stored String-\n");
    printf("%s\n", (*a)->number);

    printf("Reconstructed number-\n");
    int i = 0;
     int x=strlen((*a)->number);
    if ((*a)->sign == -1)
    {
        printf("%c", '-');
        x-=1;
    }

   

    for (; i <x ; i++)
    {
        printf("%d", *(((*a)->data) + i));
    }
    printf("\n");
    printf("Sign-\n");
    printf("%d\n", (*a)->sign);
    printf("---------------------------------\n");
}

statuscode charToInt(bigInt **a)
{
    statuscode sc = SUCCESS;

    free((*a)->data);
    int x=strlen((*a)->number);

    if(*((*a)->number)=='-')
    x-=1;

    (*a)->data = (int *)malloc(sizeof(int) * x);

    if ((*a)->data == NULL)
    {
        sc = FAILURE;
    }

    else
    {
        int i = 0;
        int j=0;
        if (*((*a)->number)=='-' )
        {
            i = 1;
            (*a)->sign=-1;
        }
            
        for (; j<x; i += 1, j+=1)
        {
            char c=*(((*a)->number) + i);
            *(((*a)->data) + j) = (int)c;
            *(((*a)->data) + j) -= 48;
        }
    }

    if(*((*a)->number)!='-')
    {
        (*a)->sign=1;
    }

    return sc;
}

void intToChar(bigInt **a, int length)
{

        int i = 0,j=0;
        if ((*a)->sign == -1)
        {   
            i = 1;
            *((*a)->number)='-';
        }

        for (; j < length; j += 1,i+=1)
        {
            int n=*((*a)->data+j);
            n+=48;
            *((*a)->number+i)=n;
        }

        *((*a)->number+i)='\0';
    
}

statuscode input(bigInt **a)
{
    statuscode sc = SUCCESS;
    printf("Enter the number:\n");
    scanf("%s", (*a)->number);

    if (*((*a)->number) == '-')
    {
        (*a)->sign = -1;
    }

    else
    {
        (*a)->sign = 1;
    }

    sc = charToInt(a);

    return sc;
}

statuscode initialize(bigInt **a)
{
    statuscode sc = SUCCESS;
    *a = (bigInt *)malloc(sizeof(bigInt));
    if (*a == NULL)
    {
        sc = FAILURE;
    }

    return sc;
}

statuscode valid(bigInt** a)
{
    statuscode sc=SUCCESS;

    for (int i = 0; i < strlen((*a)->number) && sc==1; i++)
    {
        if (*(((*a)->number) + i)<'0' || *(((*a)->number) + i)>'9')
        {
            if (*(((*a)->number) + i)!='-')
            {
                sc=FAILURE;
                printf("Please enter a valid number.\n");
            }

            else 
            {
                if (strlen((*a)->number)==1 || (strlen((*a)->number)==2 && *(((*a)->number) + 1)=='0') || i!=0)
                {
                    sc=FAILURE;
                    printf("Please enter a valid number.\n");
                }
            }
            
        }
    }

    return sc;
    
}

void reverse(bigInt** a)
{
    int n=strlen((*a)->number);
    if(*((*a)->number)=='-')
    n-=1;

    for (int i = 0; i < n/2; i++)
    {
        int temp=*((*a)->data+i);
        *((*a)->data+i)=*((*a)->data+n-1-i);
        *((*a)->data+n-1-i)=temp;

        //printf("%d\n",*((*a)->data+i));
    }
}

int cmp(bigInt*a ,bigInt*b)
{
    int ans;

    int x1=strlen(a->number);
    int x2=strlen(b->number);

    if(*(a->number)=='-')
    x1-=1;

    if(*(b->number)=='-')
    x2-=1;

    if(x1>x2)
    {
        ans=1;
    }

    else if (x1<x2)
    {
        ans=-1;
    }

    else
    {
        int flag=0;
        int i=0;
        while(flag==0 && i<x1)
        {
            //printf("%d %d\n",*(a->data+i),*(b->data+i));
            if(*(a->data+i)>*(b->data+i))
            {
                ans=1;
                flag=1;
            }

            else if (*(a->data+i)<*(b->data+i))
            {
                ans=-1;
                flag=1;
            }

            i+=1;
        }

        if (flag==0)
        {
            ans=0;
        }
    }

    return ans;
}

statuscode subtract(bigInt* a, bigInt* b, bigInt** ans);

statuscode add( bigInt* a, bigInt* b, bigInt** ans)
{
    statuscode sc=SUCCESS;
    int max=strlen(a->number)>strlen(b->number)?strlen(a->number):strlen(b->number);
    if(a->sign==b->sign)
    {
        if(*(a->number)!='-' && *(b->number)!='-')
        max+=1;
        if(a->sign==-1)
        max-=1;
        (*ans)->data=(int*)malloc(sizeof(int)*max);
        if ((*ans)->data==NULL)
        {
            sc=FAILURE;
        }
        
        else
        {
            int carry=0;
            (*ans)->sign=a->sign;
            reverse(&a);
            reverse(&b);

            int i=0;

            int x1=strlen((a)->number);
            if(*(a->number)=='-')
            x1-=1;
            int x2=strlen((b)->number);
            if(*(b->number)=='-')
            x2-=1;
            
            while (i<x1 && i<x2)
            {
                int sum=0;

                sum=sum+*((a)->data+i)+*((b)->data+i)+carry;

                if(sum>9)
                {
                    carry=sum/10;
                    sum=sum%10;

                }

                else
                {
                    carry=0;
                }

                *((*ans)->data+i)=sum;
                i+=1;
            }

            while (i<x1)
            {
                int sum=0;

                sum=(*((a)->data+i));
                sum+=carry;

                if(sum>9)
                {
                    carry=sum/10;
                    sum=sum%10;

                }

                else
                {
                    carry=0;
                }

                *((*ans)->data+i)=sum;

                i+=1;
            }
            
            while (i<x2)
            {
                int sum=0;

                sum+=*((b)->data+i)+carry;

                if(sum>9)
                {
                    carry=sum/10;
                    sum=sum%10;

                }

                else
                {
                    carry=0;
                }

                *((*ans)->data+i)=sum;

                i+=1;
            }


            if(carry!=0)
            {
                *((*ans)->data+i)=carry;
                
            }
            
            
            intToChar(ans,i);
            reverse(ans);
            intToChar(ans,i);
            //sc=charToInt(ans);
        }


    }

    else
    {

        if(a->sign==-1)
        {
            a->sign=1;
            sc=subtract(b,a,ans);
        }

        else
        {
            b->sign=1;
            sc=subtract(a,b,ans);
        }
        
    }
    
    return sc;
}

void AminusB(bigInt**a, bigInt** b, bigInt** ans)
{
    reverse(a);
    reverse(b);

    int x1=strlen((*a)->number);
    int x2=strlen((*b)->number);

    if(*((*a)->number)=='-')
    {
        x1-=1;
    }

    if(*((*b)->number)=='-')
    {
        x2-=1;
    }


    int i=0;
    while (i<x1 && i<x2)
    {
        //printf(" %d %d\n", *((*a)->data+i),*((*b)->data+i));
        if (*((*a)->data+i) >= *((*b)->data+i) )
        {
            *((*ans)->data+i)=*((*a)->data+i) - *((*b)->data+i);
        }

        else
        {
            *((*a)->data+i)+=10;
            *((*a)->data+i+1)-=1;

            *((*ans)->data+i)=*((*a)->data+i) - *((*b)->data+i);
        }

        i+=1;
    }

    while (i<x1)
    {
        //printf(" %d %d\n", *((*a)->data+i),*((*b)->data+i));
        if(*((*a)->data+i)==-1)
        {
             *((*a)->data+i)+=10;
            *((*a)->data+i+1)-=1;

        }
        *((*ans)->data+i)=*((*a)->data+i);
        i+=1;
    }

    //printf("%d\n",*((*ans)->data));

    //reverse(ans);

        int j=i-1;

        while (*((*ans)->data+j)==0)
        {
            j-=1;
        }

        //(*ans)->data+=j;
        
        
        intToChar(ans,i);

        reverse(ans);

        int k=i-j-1;
        if(k!=0)
        (*ans)->data=(*ans)->data+k;

        j+=1;
        intToChar(ans,j);

       
    
}

statuscode subtract(bigInt* a, bigInt* b, bigInt** ans)
{
    statuscode sc=SUCCESS;
    int max=strlen(a->number)>strlen(b->number)?strlen(a->number):strlen(b->number);

    if(a->sign==b->sign)
    {
        if(*(a->number)=='-' || *(b->number)=='-')
        max-=1;
        //printf("%d\n",max);
        (*ans)->data=(int*)malloc(sizeof(int)*max);
        if ((*ans)->data==NULL)
        {
            sc=FAILURE;
        }
        
        else
        {

            if(a->sign==1)
            {
                int sign=cmp(a,b);

                if(sign==0)
                {
                    *((*ans)->data)=0;
                    *((*ans)->number)='0';
                    *((*ans)->number+1)='\0';
                    (*ans)->sign=1;
                }

                else
                {
                    (*ans)->sign=sign;

                    if (sign==1)
                    {
                        //printf("%s\n",(a)->number);
                        //printf("%s\n",(b)->number);
                         AminusB(&a,&b,ans);           
                         //printf("%s\n",(*ans)->number);
                    }

                    else
                    {
                         AminusB(&b,&a,ans);
                    }
                    
                }    
                
            }

            else
            {
                int sign=cmp(b,a);
                
                if (sign==0)
                {
                    (*ans)->data=0;
                    (*ans)->sign=1;
                }

                else
                {
                    (*ans)->sign=sign;

                    if (sign==1)
                    {
                         AminusB(&b,&a,ans);           
                    }

                    else
                    {
                         AminusB(&a,&b,ans);
                    }
                }
                
            }
            
        }


    }

    else
    {

        if(a->sign==-1)
        {
            b->sign=-1;
            sc=add(b,a,ans);
        }

        else
        {
            b->sign=1;
            sc=add(a,b,ans);
        }
        
    }

    return sc;

}

statuscode multiply(bigInt* a, bigInt* b, bigInt** ans)
{
    statuscode sc=SUCCESS;
   
   int x1=strlen((a)->number);
    if(*(a->number)=='-')
    x1-=1;
    int x2=strlen((b)->number);
    if(*(b->number)=='-')
    x2-=1;

    int length =x1+x2;
    //printf("%d\n",length);

    (*ans)->data=(int*)malloc(length*sizeof(int));

    for (int i = 0; i < length; i++)
    {
        *((*ans)->data+i)=0;
    }
    

    if ((a->sign==-1 && b->sign==-1) || (a->sign==1 && b->sign==1))
    {
       (*ans)->sign=1;
    }

    else
    {
        (*ans)->sign=-1;
    }
    
    x1-=1;
    x2-=1;
    int k=length-1;
    int i=x1;
    int j=x2;
    int carry=0, push_left=0,tmp;

    //printf("%d %d\n",x1,x2);
    while (i>=0)
    {
        j=x2;
        k=length-1-push_left++;

        while (j>=0 || carry>0)
        {
           // printf("%d\n",x2);
            if(j >= 0) 
            {
                int n1=a->data[i];
                int n2=b->data[j];
                tmp = n1*n2 ;
            } 
            else
            {
                tmp = 0;
            }
            tmp += carry;
            carry = tmp / 10;
            (*ans)->data[k] += tmp % 10;
            carry += (*ans)->data[k] / 10;
            (*ans)->data[k] = (*ans)->data[k] % 10;
            

           //printf("%d %d %d %d %d %d\n",x1,x2,a->data[x1], b->data[x2],(*ans)->data[k],k);

           j-=1, k-=1;
        }
        
        i-=1;
    }
    
    k+=1;
    (*ans)->data+=k;
    
    intToChar(ans,length-k);

    return sc;
}

void main()
{
    bigInt *a;
    bigInt *b;
    statuscode sc;

    printf("Number 1-\n");
    sc = initialize(&a);

    sc=FAILURE;
    while (sc==0)
    {
        sc = input(&a);
        sc=valid(&a);
    }
    
    printf("Number 2-\n");
    sc = initialize(&b);

    sc=FAILURE;
    while (sc==0)
    {
        sc = input(&b);
        sc=valid(&b);
    }
    print(&a);
    print(&b);
    bigInt* s;
    sc=initialize(&s);

    printf("SUBTRACTION\n");
    sc=subtract(a,b,&s);
    print(&s);
    sc=charToInt(&a);
    sc=charToInt(&b);

    printf("ADDITION\n");
    sc=add(a,b,&s);
    print(&s);
    sc=charToInt(&a);
    sc=charToInt(&b);

    printf("MULTIPLICATION\n");
    sc=multiply(a,b,&s);
    print(&s);
    sc=charToInt(&a);
    sc=charToInt(&b);
}
