# Product Management System

This is a simple Product Management System implemented in C. It allows users to perform various operations such as adding, updating, searching, modifying quantities, and deleting products.

## Features

- **Add a new product:** Users can add new products to the system by providing details like product ID, name, company, price, and quantity.
- **Update a product:** Products can be updated by specifying the product ID and selecting which attribute to update.
- **Search for a product:** Users can search for products either by name or ID.
- **Modify quantity of a product:** Quantity of a product can be increased or decreased as needed.
- **Delete a product:** Products can be deleted from the system by specifying the product ID.
- **List all products:** Displays a list of all products currently in the system.

## Usage

1. Compile the program using a C compiler.
2. Run the executable.
3. Follow the on-screen menu to perform various operations.

## File Handling

The program utilizes file handling to persist product data between sessions. The product details are stored in a text file named `products.txt`.

## How to Use

- **Adding a new product:** Choose option 1 from the menu and follow the prompts to enter product details.
- **Updating a product:** Choose option 2 from the menu, enter the product ID to update, and select the attribute to update.
- **Searching for a product:** Choose option 3 from the menu and select whether to search by name or ID.
- **Modifying quantity:** Choose option 4 from the menu, enter the product ID, and specify whether to increase or decrease the quantity.
- **Deleting a product:** Choose option 5 from the menu and enter the product ID to delete.
- **Listing all products:** Choose option 6 from the menu to display a list of all products.

## File Structure

- `products.txt`: Text file containing product data.

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvement, feel free to open an issue or create a pull request.
