#include <stdio.h>
#define N 4
#define M 3 //No of Discount Coupons

void displaymenu();
float calculate_Bill(int choice, int quantity, int prices[]);
void print_Bill(float total, float netTotal);
float discountedTotal(float total, int Coupon_mil[], int Coupon_dis[]);

int main()
{
    int prices[N] = {120,250,100,80};

    int couponDiscounts[M] = {20,40,60};
    int couponMilestones[M] = {150,300,500};

    int choice, quantity;
    float total = 0;
    float netTotal;
    char more;


    do {
        displaymenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 5)
        {
            if (choice == 5)
            {
                break;
            }

            printf("Enter Quantity: ");
            scanf("%d", &quantity);


            if (quantity > 0)
            {
                total = total + calculate_Bill(choice, quantity, prices);
            }
            else
            {
                printf("invalid quantity!\n");
            }
        }

        else
        {
           printf("invalid choice!\n");
        }

        printf("\nTotal = %.2f", total);

        netTotal = discountedTotal(total,couponMilestones,couponDiscounts);

        printf("\nDo you want to order something else? (y/n): ");
        scanf(" %c", &more);

    } while (more == 'y' || more == 'Y');

    // netTotal = discountedTotal(total,couponMilestones,couponDiscounts);

    print_Bill(total,netTotal);
    printf("Hi world\n");

    return 0;

}


void displaymenu()
{
    printf("\n========== MENU ==========\n");
    printf("1. Burger        - Rs. 120\n");
    printf("2. Pizza         - Rs. 250\n");
    printf("3. Sandwich      - Rs. 100\n");
    printf("4. French Fries  - Rs. 80\n");
    printf("5. Exit\n");
}

float calculate_Bill(int choice, int quantity, int prices[])
{
    return prices[choice-1] * quantity;
}

float discountedTotal(float total, int Coupon_mil[], int Coupon_dis[])
{
    int couponCount = 0;
    int choice;
    for(int i = 0; i < M; i++)
    {
        printf("\n%d. %d\%% Off on Orders Above %d",i+1,Coupon_dis[i],Coupon_mil[i]);
        if (total > Coupon_mil[i])
        {
            printf("\t- Elligible\n");
            couponCount++;
        }
        else
        {
            float need = (Coupon_mil[i] + 1 ) -total;

            printf("\t- Not Elligible, Add Rs. %.2f more\n",need);
        }

    }

    while(couponCount>0)
    {
      printf("Choose Coupon\n");
      scanf("%d", &choice);


      if(choice <= couponCount && choice > 0)
      {
        return total - (total * (Coupon_dis[choice-1] / 100.0f));

      }
      else
      {
          printf("Invalid Choice, try again\n");
      }

    }

    return 1;

}

void print_Bill(float total,float netTotal)
{
		  char save;

    printf("\n\n======= FINAL BILL =======\n");
    printf("SubTotal Amount : Rs.%.2f",total);
    printf(" discount %.2f \n : ",total - netTotal);
    printf("Grand Total Amount :  Rs. %.2f\nDiscount : Rs. %.2f\n", netTotal,total-netTotal);
    printf("Thank You! Visit Again!\n");
    printf("\nSave Bill? (y/n): ");
    scanf(" %c", &save);

    if(save == 'y' || save == 'Y')
    {
        FILE *bill = fopen("bills.txt","a");

        fprintf(bill,"======= FINAL BILL =======\n");
        printf("SubTotal Amount : Rs.%.2f\n",total);
        fprintf(bill,"Grand Total Amount : Rs. %.2f\nDiscount : Rs. %.2f\n", netTotal,total-netTotal);
        fprintf(bill,"Thank You! Visit Again!\n\n\n");

        fclose(bill);

        printf("\nBILL SAVED\n");
    }
}

