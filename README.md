# Address-Book-project

This is a simple Address Book application implemented in C that allows users to add, edit, search, delete, and display contacts. 
The contacts are stored in memory during the program execution and can also be saved to a CSV file for persistent storage. 
The program supports a maximum of 100 contacts.

# Requirements
C Compiler (like GCC)
Any standard C IDE or terminal environment

# File Details
address_book.c: The main C file containing all functionality for the address book.
addressbook.csv: A CSV file used for storing contacts persistently.

# Program Functionality
# Menu Options

# Add Contact: 
Prompts the user to enter the contact details. The phone number must be 10 digits, and the email must be a valid Gmail or Yahoo address. Duplicate names, phone numbers, or emails are not allowed.
# Edit Contacts: 
Allows editing of an existing contact’s name, phone number, or email.
# Search Contact: 
Search by name, phone, or email to find a contact.
# Display Contacts: 
Displays all saved contacts.
# Delete Contact: 
Removes a contact based on name, phone number, or email.
# Save Contacts to File: 
Saves the current list of contacts to addressbook.csv.
# Exit: 
Exits the program.

# Input/Output
# Add Contact: 
Input is required for name, phone, and email. Validation ensures that the phone number is 10 digits and the email is valid.
# Search: 
The user can search by name, phone, or email, and the matching contact will be displayed.
# Edit: 
A contact can be edited by searching first and then modifying any field.
# Delete: 
Contacts can be removed by searching for them by name, phone, or email.

# Saving and Loading Contacts
Contacts are saved to addressbook.csv in a comma-separated format (CSV) for easy reading and writing.
On startup, the program loads contacts from addressbook.csv, if it exists. 
