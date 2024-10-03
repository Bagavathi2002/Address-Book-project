#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[MAX_CONTACTS];
    int totalContacts;
};

void createContact(struct AddressBook *addressBook);
void searchContact(struct AddressBook *addressBook);
void editContact(struct AddressBook *addressBook);
void deleteContact(struct AddressBook *addressBook);
void listContacts(struct AddressBook *addressBook);
void saveContactsToFile(struct AddressBook *addressBook);
void loadContactsFromFile(struct AddressBook *addressBook);
void menu(struct AddressBook *addressBook);

int main() {
    struct AddressBook addressBook;
    addressBook.totalContacts = 0;
    
    loadContactsFromFile(&addressBook);
    listContacts(&addressBook);
    menu(&addressBook);
    return 0;
}

void menu(struct AddressBook *addressBook) {
    int choice;
    while (1) {
        printf("\nAddress Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Edit Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Display Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                createContact(addressBook); break;
            case 2:
                editContact(addressBook); break;
            case 3:
                searchContact(addressBook); break;
            case 4:
                listContacts(addressBook); break;
            case 5:
                deleteContact(addressBook); break;
            case 6:
                saveContactsToFile(addressBook); break;
            case 7:
                return;
            default: 
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void createContact(struct AddressBook *addressBook) {
    if (addressBook->totalContacts >= MAX_CONTACTS) {
        printf("Address book is full! Cannot add more contacts.\n");
        return;
    }

    struct Contact *newContact = &addressBook->contacts[addressBook->totalContacts];

    printf("Enter Name: ");
    fgets(newContact->name, sizeof(newContact->name), stdin);
    newContact->name[strcspn(newContact->name, "\n")] = '\0'; 

    printf("Enter Phone: ");
    fgets(newContact->phone, sizeof(newContact->phone), stdin);
    newContact->phone[strcspn(newContact->phone, "\n")] = '\0';
    if (strlen(newContact->phone) != 10) {
        printf("Need to enter a 10-digit mobile number!\n");
        return;
    }

    printf("Enter Email: ");
    fgets(newContact->email, sizeof(newContact->email), stdin);
    newContact->email[strcspn(newContact->email, "\n")] = '\0';

    if ((strstr(newContact->email, "@gmail.com") == NULL) && (strstr(newContact->email, "@yahoo.com") == NULL)) {
        printf("Error: Email must be a Gmail or Yahoo address!\n");
        return;
    }

    for (int i = 0; i < addressBook->totalContacts; i++) {
        struct Contact *existingContact = &addressBook->contacts[i];
        if (strcmp(existingContact->name, newContact->name) == 0) {
            printf("Error: A contact with the same name already exists!\n");
            return;
        }
        if (strcmp(existingContact->phone, newContact->phone) == 0) {
            printf("Error: A contact with the same phone number already exists!\n");
            return;
        }
        if (strcmp(existingContact->email, newContact->email) == 0) {
            printf("Error: A contact with the same email already exists!\n");
            return;
        }
    }

    addressBook->totalContacts++;
    printf("Contact added successfully.\n");
}

void listContacts(struct AddressBook *addressBook) {
    if (addressBook->totalContacts == 0) {
        printf("No contacts found!\n");
        return;
    }

    printf("\nContacts:\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("Name\t\tMobile number\t\tEmail\n");
    for (int i = 0; i < addressBook->totalContacts; i++) {
        struct Contact *contact = &addressBook->contacts[i];
        printf("%s\t\t%s\t\t%s\n", contact->name, contact->phone, contact->email);
        printf("-----------------------------------------------------------------------------\n");
    }
}

void searchContact(struct AddressBook *addressBook) {
    int choice;
    char searchQuery[50];
    
    printf("Search by: \n1. Name\n2. Phone\n3. Email\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);
    getchar(); 
    
    if (choice < 1 || choice > 3) {
        printf("Invalid choice! Please select 1, 2, or 3.\n");
        return;
    }

    printf("Enter search query: ");
    fgets(searchQuery, sizeof(searchQuery), stdin);
    searchQuery[strcspn(searchQuery, "\n")] = '\0'; 

    for (int i = 0; i < addressBook->totalContacts; i++) {
        struct Contact *contact = &addressBook->contacts[i];
        int found = 0;

        if (choice == 1 && strcmp(contact->name, searchQuery) == 0) {
            found = 1;
        } else if (choice == 2 && strcmp(contact->phone, searchQuery) == 0) {
            found = 1;
        } else if (choice == 3 && strcmp(contact->email, searchQuery) == 0) {
            found = 1;
        }

        if (found) {
            printf("Contact found: \nName: %s\nPhone: %s\nEmail: %s\n", contact->name, contact->phone, contact->email);
            return;
        }
    }

    printf("Contact not found!\n");
}


void editContact(struct AddressBook *addressBook) {
    int choice;
    printf("Search contact by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    getchar(); 

    char searchQuery[50];
    switch (choice) {
        case 1: 
            printf("Enter name of the contact to edit: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = '\0'; 
            break;

        case 2: 
            printf("Enter mobile number of the contact to edit: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = '\0';
            break;

        case 3: 
            printf("Enter email of the contact to edit: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = '\0';
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }
    for (int i = 0; i < addressBook->totalContacts; i++) {
        struct Contact *contact = &addressBook->contacts[i];
        
        if ((choice == 1 && strcmp(contact->name, searchQuery) == 0) ||
            (choice == 2 && strcmp(contact->phone, searchQuery) == 0) ||
            (choice == 3 && strcmp(contact->email, searchQuery) == 0)) {
            
            printf("Editing contact: %s\n", contact->name);
            
            printf("Enter new Name (leave blank to keep current): ");
            char newName[50];
            fgets(newName, sizeof(newName), stdin);
            if (strcmp(newName, "\n") != 0) {
                newName[strcspn(newName, "\n")] = '\0';
                strcpy(contact->name, newName);
            }

            printf("Enter new Phone (leave blank to keep current): ");
            char newPhone[15];
            fgets(newPhone, sizeof(newPhone), stdin);
            if (strcmp(newPhone, "\n") != 0) {
                newPhone[strcspn(newPhone, "\n")] = '\0';
                strcpy(contact->phone, newPhone);
            }

            printf("Enter new Email (leave blank to keep current): ");
            char newEmail[50];
            fgets(newEmail, sizeof(newEmail), stdin);
            if (strcmp(newEmail, "\n") != 0) {
                newEmail[strcspn(newEmail, "\n")] = '\0';
                strcpy(contact->email, newEmail);
            }

            printf("Contact updated successfully.\n");
            return;
        }
    }

    printf("Contact not found!\n");
}


void deleteContact(struct AddressBook *addressBook) {
    int choice;
    printf("Delete contact by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    getchar(); 
    char searchQuery[50];
    switch (choice) {
        case 1: 
            printf("Enter name of the contact to delete: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = '\0'; 
            break;

        case 2: 
            printf("Enter mobile number of the contact to delete: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = '\0';
            break;

        case 3: 
            printf("Enter email of the contact to delete: ");
            fgets(searchQuery, sizeof(searchQuery), stdin);
            searchQuery[strcspn(searchQuery, "\n")] = '\0';
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }
    for (int i = 0; i < addressBook->totalContacts; i++) {
        struct Contact *contact = &addressBook->contacts[i];
        if ((choice == 1 && strcmp(contact->name, searchQuery) == 0) ||
            (choice == 2 && strcmp(contact->phone, searchQuery) == 0) ||
            (choice == 3 && strcmp(contact->email, searchQuery) == 0)) {
            printf("Deleting contact: %s, %s, %s\n", contact->name, contact->phone, contact->email);
            for (int j = i; j < addressBook->totalContacts - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->totalContacts--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }

    printf("Contact not found!\n");
}


void saveContactsToFile(struct AddressBook *addressBook) {
    FILE *file = fopen("addressbook.csv", "w");
    if (!file) {
        printf("Error opening file for saving!\n");
        return;
    }

    for (int i = 0; i < addressBook->totalContacts; i++) {
        struct Contact *contact = &addressBook->contacts[i];
        fprintf(file, "%s,%s,%s\n", contact->name, contact->phone, contact->email);
    }

    fclose(file);
    printf("Contacts saved successfully.\n");
}

void loadContactsFromFile(struct AddressBook *addressBook) {
    FILE *file = fopen("addressbook.csv", "r");
    if (!file) {
        printf("No existing contacts file found. Starting fresh...\n");
        return;
    }

    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[addressBook->totalContacts].name, addressBook->contacts[addressBook->totalContacts].phone, addressBook->contacts[addressBook->totalContacts].email) != EOF) {
        addressBook->totalContacts++;
    }

    fclose(file);
    printf("Contacts loaded successfully.\n");
}
