#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: "); // obtain card number

            //declaring variables required for checksum
    long sum1=0;
    long sum2=0;
    long i=0;
    long m=0;
    long h = 0;
    long x = 0;
    int j =0;
    long div = 1;
    float final = 2;
    long y = 1;
    int digit =0;
    bool checksum = false;
    bool amex1 = false;
    bool amex2 = false;
    bool master1 = false;
    bool master2 = false;
    bool visa = false;


    //Start checksum operation

    do
    {

        div = div*10;
        i = number % div;
        h = div/10;
        m = (i-x)/h;
        x = i;
        final = number / div;

        if ( y % 2 == 0)
        {
            long k = 2 * m ;
            if ( k >=10)
            {
                j=k%10;
                sum1= sum1+j;
                j= ( (k%100)-j )/10;
                sum1= sum1+j;

            } else
            {
                sum1 = sum1 + k;
            }

        } else
        {
            sum2 = sum2 + m;
        }

     //check for amex
        if ( y == 15 && m==3)
        {
            amex1 = true ;

        }
        if ( y == 14 && ( m==4 || m== 7 ) )
        {
            amex2 = true ;

        }
        //check for Mastercard
        if ( y == 16 && m == 5)
        {
            master1 = true ;

        }
        if ( y == 15 && ( m == 1 || m == 2 || m == 3 || m == 4 || m == 5 ) )
        {
            master2 = true ;

        }
        //check for Visa
        if ( ( y == 13  )  && m == 4 )
        {
            visa = true ;

        }
        if ( ( y == 16  )  && m == 4 )
        {
            visa = true ;

        }
        y++;
    }while (final >= 1);


    //obtaining checksum result
    int final_total = sum1 + sum2;
    if ( final_total % 10 == 0 )
    {
        checksum = true;

    }else{
        checksum = false;

    }
    //End of checksum operation

    //output
    if ( checksum == true && ( amex1 == true && amex2 == true))
    {
        printf ( "AMEX\n" ) ;

    } else if ( checksum == true && ( master1 == true && master2 == true))
    {
        printf ( "MASTERCARD\n" ) ;
    } else if ( checksum == true && ( visa == true))
    {
        printf ( "VISA\n" ) ;
    } else {
        printf ( "INVALID\n" ) ;
    }
    //end of output

}