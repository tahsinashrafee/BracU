#include <stdio.h>

int main() {    
    int paratha_quantity, paratha_price;
    int veg_quantity, veg_price;
    int m_water_quantity, m_water_price;
    int no_of_people;

    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha_quantity);
    printf("Unit price: ");
    scanf("%d", &paratha_price);

    printf("Quantity of Vegetables: ");
    scanf("%d", &veg_quantity);
    printf("Unit price: ");
    scanf("%d", &veg_price);

    printf("Quantity of Mineral Water: ");
    scanf("%d", &m_water_quantity);
    printf("Unit price: ");
    scanf("%d", &m_water_price);
 
    printf("Number of People: ");
    scanf("%d", &no_of_people);

    int total = (paratha_quantity * paratha_price) + (veg_quantity * veg_price) + (m_water_quantity * m_water_price);
    float pay = total / (float)no_of_people;

    printf("Individual people will pay: %.2f tk \n", pay);

    return 0;
}

