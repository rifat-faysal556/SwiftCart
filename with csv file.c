#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_USERS 10
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"
#define CART_SIZE 10
#define MAX_ADDRESS_LENGTH 100
#define MAX_MOBILE_LENGTH 15
#define MAX_EMAIL_LENGTH 50

struct Product {
    char name[50];
    float price;
};

struct User {
    char username[50];
    char password[50];
    struct Product cart[CART_SIZE];
    int cartSize;
    char address[MAX_ADDRESS_LENGTH];
    char mobile[MAX_MOBILE_LENGTH];
    char email[MAX_EMAIL_LENGTH];
};

struct Product products[MAX_PRODUCTS];
struct User users[MAX_USERS];
int numProducts = 0;
int numUsers = 0;

void addProduct() {
    if (numProducts >= MAX_PRODUCTS) {
        printf("                                           Cannot add more products. Maximum limit reached.\n");
        return;
    }

    printf("                                                       Enter product name: ");
    scanf("%s", &products[numProducts].name);
    printf("                                                       Enter product price: ");
    scanf("%f", &products[numProducts].price);
    numProducts++;
    printf("\n                                                      Product added successfully!\n");
}

void displayProducts() {

    printf("\n                                                       Products available:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("                                                       %d. %s - $%.2f\n", i + 1, products[i].name, products[i].price);
    }
    FILE *pf = fopen("C:\\Users\\ASUS\\Desktop\\project code\\Test.txt", "r");
char buffer[200];
if(pf==NULL){
    printf("unable to open file");
}
else{
    while(fgets(buffer, 255, pf)!= NULL){
printf("                                                       %s", buffer);
}
}
fclose(pf);
}

void addToCart(struct User *user, int productIndex) {
    if (user->cartSize >= CART_SIZE) {
        printf("                                           Cart is full. Cannot add more products.\n");
        return;
    }
    user->cart[user->cartSize++] = products[productIndex];
    printf("                                                    %s added to cart successfully.\n", products[productIndex].name);
}

void removeFromCart(struct User *user, int productIndex) {
    if (productIndex < 0 || productIndex >= user->cartSize) {
        printf("Invalid product index.\n");
        return;
    }

    printf("                                                    %s removed from cart successfully.\n", user->cart[productIndex].name);
    for (int i = productIndex; i < user->cartSize - 1; i++) {
        user->cart[i] = user->cart[i + 1];
    }
    user->cartSize--;
}

void checkout(struct User *user) {
    printf("                                                      Enter your address: ");
    scanf("                                                     %[^\n]", user->address);
    printf("                                                      Enter your mobile number: ");
    scanf("                                                     %s", user->mobile);
    printf("                                                      Enter your email address: ");
    scanf("                                                     %s", user->email);

    printf("\n                                                      Order confirmed!\n");
    printf("                                                      Your order will be shipped to:\n");
    printf("                                                      Address: %s\n", user->address);
    printf("                                                      Mobile: %s\n", user->mobile);
    printf("                                                      Email: %s\n", user->email);
}

void userLogin() {
    char username[50], password[50];
    printf("                                                      Enter username: ");
    scanf("%s", username);
    printf("                                                      Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        {
            printf("\n                                                         Welcome, %s!\n", username);
            int option, productIndex;
            do {
                printf("\n                                                      1. Display products\n");
                printf("                                                      2. Add product to cart\n");
                printf("                                                      3. Remove product from cart\n");
                printf("                                                      4. View cart\n");
                printf("                                                      5. Checkout\n");
                printf("                                                      6. Logout\n");
                printf("                                                      Enter your choice: ");
                scanf("%d", &option);

                switch (option) {
                    case 1:
                        displayProducts();
                        break;
                    case 2:
                        printf("                                               Enter the product number to add to cart: ");
                        scanf("%d", &productIndex);
                        if (productIndex > 0 && productIndex <= numProducts)
                            addToCart(&users[i], productIndex - 1);
                        else
                            printf("                                                    Invalid product number.\n");
                        break;
                    case 3:
                        printf("                                            Enter the product number to remove from cart: ");
                        scanf("%d", &productIndex);
                        if (productIndex > 0 && productIndex <= users[i].cartSize)
                            removeFromCart(&users[i], productIndex - 1);
                        else
                            printf("                                                    Invalid product number.\n");
                        break;
                    case 4:
                        printf("                                                            Your cart:\n");
                        for (int j = 0; j < users[i].cartSize; j++) {
                            printf("                                                %d. %s - $%.2f\n", j + 1, users[i].cart[j].name, users[i].cart[j].price);
                        }
                        break;
                    case 5:
                        checkout(&users[i]);
                        break;
                    case 6:
                        printf("                                                        Exiting user panel.\n");
                        break;
                    default:
                        printf("                                                Invalid choice. Please try again.\n");
                }
            } while (option != 6);
            return;
        }
    }
    printf("Invalid username or password.\n");
}
void removeProduct() {
    printf("\n                                                       Products available for removal:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("                                                       %d. %s - $%.2f\n", i + 1, products[i].name, products[i].price);
    }

    int productIndex;
    printf("                                                      Enter the index of the product to remove: ");
    scanf("%d", &productIndex);
    productIndex--;

    if (productIndex >= 0 && productIndex < numProducts) {
        for (int i = productIndex; i < numProducts - 1; i++) {
            products[i] = products[i + 1];
        }
        numProducts--;
        printf("                                                      Product removed successfully.\n");
    } else {
        printf("                                                      Invalid product index.\n");
    }
}
void adminLogin() {
    char username[50], password[50];
    printf("                                                     Enter Admin Username: ");
    scanf("%s", username);
    printf("                                                     Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("\n                                                       Welcome, Admin!\n");
        int choice;
        do {
            printf("\n                                                       1. Add product\n");
            printf("                                                       2. Remove product\n");
            printf("                                                       3. Display products\n");
            printf("                                                       4. Logout\n");
            printf("                                                       Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addProduct();
                    break;
                case 2:
                    removeProduct();
                    break;
                case 3:
                    displayProducts();
                    break;
                case 4:
                    printf("\n                                                       Exiting Admin Panel.\n");
                    break;
                default:
                    printf("\n                                                   Invalid choice. Please try again.\n");
            }
        } while (choice != 4);
    } else {
        printf("                                                                 Invalid Admin username or password.\n");
    }
}

int main() {

    system("COLOR BC");
    strcpy(users[numUsers].username, ADMIN_USERNAME);
    strcpy(users[numUsers].password, ADMIN_PASSWORD);
    numUsers++;

    int option;
    do {
        printf("                                        --------***Welcome To SwiftCart!***--------\n");
        printf("                                                       1. User Login\n");
        printf("                                                       2. Admin Login\n");
        printf("                                                      Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                userLogin();
                break;
            case 2:
                adminLogin();
                break;
            default:
                printf("\n                                              Invalid choice. Please try again.\n");
        }
    } while (option != 4);

    return 0;
}
