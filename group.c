#include<stdio.h>
#include<stdlib.h>
#include<time.h>
char fnclosure(char op,intvalues,int a[],int m);
char fnassociative(char op,intvalues,int a[],int m);
int fnidentity(char op,intvalues,int a[],int m);
char fninverse(char op,intn,int a[],int m,int c3);
int search(int val,intn,int a[]);
int order(char op,intn,intmod,int c3);


int main()
{
	char op,c1,c2,c4;
	int i,m,c3;
	int flag=0;
	int values;
clock_tstart,end;
	printf("Enter + or * Operator=");
	scanf("%c",&op);

	printf("Enter Number of Values You Want To Insert=");
	scanf("%d",&values);

    int a[values],o[values];
    double tot_time=0.0;
	for(i=0;i<values;i++)
	{
		printf("Enter %d Value=",i+1);
		scanf("%d",&a[i]);
		if(a[i]==0 && op=='*')
        {
printf("Cannot use 0 with '*' binary operation!");
exit(-1);
        }
	}
printf("Enter modulo value:");
scanf("%d",&m);
    start=clock();    //start time clock to find execution time of code
	c1=fnclosure(op,values,a,m);     //checking whether given set satisfies closure property
	if(c1=='y')
    {
        c2=fnassociative(op,values,a,m);//checking whether given set satisfies associative property
        if(c2=='y')
        {
            c3=fnidentity(op,values,a,m);//checking whether identity element is found or not
            c4=fninverse(op,values,a,m,c3);//checking whether given set satisfies inverse property
            if(c4=='y')
            {
printf("-----------------");
printf("\n\nThe given set is a group!\n\n");
for(int k=0;k<values;k++)
                    {
                        o[k]=order(op,a[k],m,c3);     /if all the properties are satisfied we find the order of each element of the given group/
printf("Order of %d is:%d\n",a[k],o[k]);
                    }
printf("\n*-----------------*");
                }
        }
        else
        {
printf("Associative property not satisfied... Hence Not a group!");
exit(-1);
        }
    }
    else
    {
printf("------------------\n\n");
printf("Not a group!!");     //If any of the property is not satisfied then the set is not a group
printf("\n\n*------------------*");
    }
    end=clock();    //stop the clock time
tot_time=((double)(end-start))/CLOCKS_PER_SEC; //Time taken to execute the code 
printf("\nTime taken to execute is:%f\n",tot_time);
}

char fnclosure(char op,intvalues,int a[],int mod)
{
	char r='y';
	int c;
	if(op=='+')
	{
		for(int i=0;i<values;i++)
		{
			for(int j=0;j<values;j++)
			{
				c=(a[i]+a[j])%mod;
				c=search(c,values,a);
				if(c==0)
				{
					r='n';
					break;
				}
			}
		}
		return r;
	}
	if(op=='*')
	{
		for(int i=0;i<values;i++)
		{
			for(int j=0;j<values;j++)
			{
				c=(a[i]*a[j])%mod;
				c=search(c,values,a);
				if(c==0)
				{
					r='n';
					break;
				}
			}
		}
		return r;
	}
}
char fnassociative(char op,intvalues,int a[],int mod)
{
	char g='y';

	if(op=='+')
	{
		for(int i=0;i<values;i++)
		{
			for(int j=i+1;j<values;j++)
			{
				for(int h=j+1;h<values;h++)
				{
					int result1=(a[i]+((a[j]+a[h])%mod))%mod;
					int result2=(((a[i]+a[j])%mod)+a[h])%mod;

					if(result1==result2)
					{
						int r1=search(result1,values,a);

						if(r1==0)
						{
							g='n';
							break;
						}
					}
				}
			}
		}
		return g;
	}
	if(op=='*')
	{
		for(int i=0;i<values;i++)
		{
			for(int j=i+1;j<values;j++)
			{
				for(int h=j+1;h<values;h++)
				{
					int result1=(a[i]*((a[j]*a[h])%mod))%mod;
					int result2=(((a[i]*a[j])%mod)*a[h])%mod;
					if(result1==result2)
					{
						int r1=search(result1,values,a);
						if(r1==0)
						{
							g='n';
							break;
						}
					}
				}
			}
		}
		return g;
	}
}

int fnidentity(char op,intvalues,int a[],int mod)
{
    int c[values][values],id,count=0;
	if(op=='+')
	{
		for(int i=0;i<values;i++)
		{
			for(int j=0;j<values;j++)
			{
				c[i][j]=(a[i]+a[j])%mod;
			}
		}
		for(int i=0;i<values;i++)
        {
            count=0;
for(int j=0;j<values;j++)
            {
                if(a[j]==c[i][j])
                {
                    count++;
                }
                if(count==values)
                    return a[i];
            }
        }
        if(count!=values)
        {
printf("Identity element not found... Hence Not a group!");
exit(-1);
        }
	}
	if(op=='*')
	{
	for(int i=0;i<values;i++)
		{
			for(int j=0;j<values;j++)
			{
				c[i][j]=(a[i]*a[j])%mod;
			}
		}
		for(int i=0;i<values;i++)
        {
            count=0;
for(int j=0;j<values;j++)
            {
                if(a[j]==c[i][j])
                {
                    count++;
                }
                if(count==values)
                    return a[i];
            }
        }
        if(count!=values)
        {
printf("Identity element not found... Hence Not a group!");
exit(-1);
        }
	}
}
char fninverse(char op,intn,int a[],int mod,int c3)
{
    char r='y';
    if(op=='+')
    {
for(int i=0;i<n;i++)
        {
for(int j=0;j<n;j++)
            {
                int v=(a[i]+a[j])%mod;
                if(v==c3)
                {
                    r='y';
                    break;
                }
                else
                {
                    r='n';
                }
                if(j==n)
                {
printf("Inverse not found !");
                    return 'n';
                }
            }
        }
    }
    if(op=='*')
    {
for(int i=0;i<n;i++)
        {
for(int j=0;j<n;j++)
            {
                int v=(a[i]*a[j])%mod;
                if(v==c3)
                {
                    r='y';
                    break;
                }
                else
                {
                    r='n';
                }
                if(j==n)
                {
printf("Inverse not found !");
                    return 'n';
                }
            }
        }
    }
    return r;
}

int search(int val,intn,int a[])
{
	int r=0;
	int i;
	for(i=0;i<n;i++)
	{
		if(a[i]==val)
		{
			r=1;
			break;
		}
	}

	if(r==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int order(char op,intn,intmod,int c3)
{
    int r,o,i=1,q;
    o=r=n;
    if(op=='+')
    {
        while(r!=c3)
        {
i++;
            o=o+n;
            r=o%mod;
        }
        q=i;
    }
    if(op=='*')
    {
        while(r!=c3)
        {
i++;
            o=o*n;
            r=o%mod;
        }
        q=i;
    }
    return q;
}