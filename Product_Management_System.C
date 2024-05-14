#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct item {
    char productname[400];
    char productcomp[400];
    int productid;
    int price;
    int Qnt;
};

void addProduct(struct item products[], int *count);
void listProducts(struct item products[], int count);
void updateProduct(struct item products[], int count);
void searchProduct(struct item products[], int count);
void modifyQuantity(struct item products[], int count, int isIncrease);
void deleteProduct(struct item products[], int *count);

int main() {
    struct item products[100];
    int count = 0;
    int choice;

    FILE *fp = fopen("products.txt", "a");
    if (fp != NULL) {
        while (fscanf(fp, "%d %s %s %d %d", &products[count].productid, products[count].productname,
                      products[count].productcomp, &products[count].price, &products[count].Qnt) != EOF) {
            count++;
        }
        fclose(fp);
    }
    while(1) {
        printf("\n======================== Product Management System ========================");
        printf("                                                                                          ");
        printf("\n1. Add a new product");
        printf("\n2. Update a product");
        printf("\n3. Search for product with name");
        printf("\n4. Modify quantity of a product");
        printf("\n5. Delete a product");
        printf("\n6. List all products");
        printf("\n7. Exit / Quit the program\n");
        printf("\nEnter your choice[1-6] : ");
        scanf("%d", &choice);
        printf("\n");

        switch(choice) {
            case 1:
                addProduct(products, &count);
                break;
            case 2:
                updateProduct(products, count);
                break;
            case 3:
                searchProduct(products, count);
                break;
            case 4:
                modifyQuantity(products, count, 1);
                break;
            case 5:
                deleteProduct(products, &count);
                break;
            case 6:
                listProducts(products, count);
                break;
            case 7:
                printf("Exiting the program.\n");

                fp = fopen("products.txt", "w");
                if (fp != NULL) {
                    for (int i = 0; i < count; i++) {
                        fprintf(fp, "%d %s %s %d %d\n", products[i].productid, products[i].productname,
                                products[i].productcomp, products[i].price, products[i].Qnt);
                    }
                    fclose(fp);
                } else {
                    printf("Error opening file for writing!\n");
                }
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}

void addProduct(struct item products[], int *count) {
    char choice;
    int validChoice;

    FILE *fp = fopen("products.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    do {
        printf("Enter product details:\n");
        printf("Product ID(Only Number): ");
        scanf("%d", &products[*count].productid);
        printf("Product Name: ");
        scanf("%s", products[*count].productname);
        printf("Product Company: ");
        scanf("%s", products[*count].productcomp);
        printf("Product Price(Only Number): ");
        scanf("%d", &products[*count].price);
        printf("Product Quantity(Only Number): ");
        scanf("%d", &products[*count].Qnt);

        fprintf(fp, "%d %s %s %d %d\n", products[*count].productid, products[*count].productname,
                products[*count].productcomp, products[*count].price, products[*count].Qnt);

        (*count)++;

        do {
            printf("Do you want to add another product? (y for yes, n for no): ");
            scanf(" %c", &choice);
            validChoice = (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N');
            if (!validChoice) {
                printf("Invalid choice! Please enter 'y' or 'n'.\n");
            }
        } while (!validChoice);

    } while (choice == 'y' || choice == 'Y');

    fclose(fp);
}

void listProducts(struct item products[], int count) {
    FILE *fp = fopen("products.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("----------------------------------------------------------------------------------------------------\n");
    printf("%-20s%-15s%-20s%-20s%-20s\n", "Product ID", "Product Name", "Product Company", "Product Price", "Product Quantity");
    printf("----------------------------------------------------------------------------------------------------\n");


    struct item product;
    while (fscanf(fp, "%d %s %s %d %d", &product.productid, product.productname,
                  product.productcomp, &product.price, &product.Qnt) != EOF) {
        printf("%-20d%-20s%-20s%-15d%-15d\n",
               product.productid,
               product.productname,
               product.productcomp,
               product.price,
               product.Qnt);
    }
    fclose(fp);
}

void updateProduct(struct item products[], int count) {
    int id;
    printf("Enter product ID to update (Only Number): ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (products[i].productid == id) {
            found = 1;
            int choice;
            printf("What do you want to update?\n");
            printf("1. Product ID\n");
            printf("2. Product Name\n");
            printf("3. Product Company\n");
            printf("4. Product Price\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch(choice) {
                case 1:
                    printf("Enter new product ID (Only Number): ");
                    scanf("%d", &products[i].productid);
                    break;
                case 2:
                    printf("Enter new product name: ");
                    scanf("%s", products[i].productname);
                    break;
                case 3:
                    printf("Enter new product company: ");
                    scanf("%s", products[i].productcomp);
                    break;
                case 4:
                    printf("Enter new product price (Only Number): ");
                    scanf("%d", &products[i].price);
                    break;
                default:
                    printf("Invalid choice!\n");
            }

            printf("Product updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found.\n", id);
        return;
    }

    FILE *fp = fopen("products.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %d %d\n", products[i].productid, products[i].productname,
                products[i].productcomp, products[i].price, products[i].Qnt);
    }

    fclose(fp);
}

void searchProduct(struct item products[], int count) {
    int choice;
    printf("Search by:\n");
    printf("1. Product Name\n");
    printf("2. Product ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        char name[40];
        printf("Enter product name to search: ");
        scanf("%s", name);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(products[i].productname, name) == 0) {
                printf("Product found:\n");
                printf("Name: %s, Company: %s, ID: %d, Price: %d, Quantity: %d\n",
                       products[i].productname, products[i].productcomp,
                       products[i].productid, products[i].price, products[i].Qnt);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Product with name %s not found.\n", name);
        }
    } else if (choice == 2) {
        int id;
        printf("Enter product ID to search: ");
        scanf("%d", &id);

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (products[i].productid == id) {
                printf("Product found:\n");
                printf("Name: %s, Company: %s, ID: %d, Price: %d, Quantity: %d\n",
                       products[i].productname, products[i].productcomp,
                       products[i].productid, products[i].price, products[i].Qnt);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Product with ID %d not found.\n", id);
        }
    } else {
        printf("Invalid choice!\n");
    }
}

void modifyQuantity(struct item products[], int count, int isIncrease) {
    int id, amount;
    const char *action = isIncrease ? "increase" : "decrease";
    printf("Enter product ID to %s quantity: ", action);
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (products[i].productid == id) {
            printf("Enter quantity to %s: ", action);
            scanf("%d", &amount);
            if (isIncrease) {
                products[i].Qnt += amount;
            } else {
                if (products[i].Qnt < amount) {
                    printf("Error: Insufficient quantity.\n");
                } else {
                    products[i].Qnt -= amount;
                }
            }
            printf("Quantity %sed successfully.\n", action);
            return;
        }
    }

    printf("Product with ID %d not found.\n", id);
}

void deleteProduct(struct item products[], int *count) {
    int id;
    printf("Enter product ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (products[i].productid == id) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                products[j] = products[j + 1];
            }
            (*count)--;
            printf("Product with ID %d deleted successfully.\n", id);
            break;
        }
    }

    if (!found) {
        printf("Product with ID %d not found.\n", id);
    }
    FILE *fp = fopen("products.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < *count; i++) {
        fprintf(fp, "%d %s %s %d %d\n", products[i].productid, products[i].productname,
                products[i].productcomp, products[i].price, products[i].Qnt);
    }

    fclose(fp);
}
