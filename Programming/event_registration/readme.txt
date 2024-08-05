Bike Race Fundraising Program
Overview
This program facilitates organizing and managing bike races for fundraising purposes. It allows administrators to set up organizations, define race parameters, and track sales and charity contributions. Participants can register for races and purchase jerseys, with a portion of the proceeds going to charity.

Features:
    Administrator Setup: Admins can set up organizations, specifying race cost, distance, jersey price, and charity percentage.
    User Registration: Participants can register for races, optionally purchasing jerseys.
    Sales and Charity Tracking: The program tracks total sales, jersey sales, and the amount contributed to charity.
    Receipt Generation: Users can receive a receipt summarizing their purchases and charity contribution.
    Data Persistence: The program exports organization data to a file for record-keeping.

File Structure:
    event_reg.c: Main program file containing all the code.
    org1.txt: Output file where organization data is stored.

Functions:
    adminSetUp: Prompts the admin to set up organization details.
    getValidChar: Validates character input for size and yes/no prompts.
    getValidDouble: Validates and converts string input to double within specified range.
    updateTotals: Updates the overall sales and charity totals.
    adminLogin: Handles administrator login.
    getName: Prompts and validates participant name input.
    registrationMode: Manages the participant registration process.
    validCredit: Validates credit card input.
    theReceipt: Generates a receipt for the participant.
    initializer: Initializes variables for Holder and final structures.
    insertNode: Inserts a new organization node into the linked list.
    printList: Prints the list of organizations.
    orgzSearch: Searches for an organization in the linked list by name.
    fgetsRemoveNewLine: Removes newline character from input string.
    freeNodes: Frees allocated memory for the linked list nodes.
    fileList: Exports organization data to a file.
    finalUpdate: Updates organization data for final record.

Usage
Administrator Setup:

Run the program and enter the admin password (B!k34u).
Follow prompts to enter organization details (name, race cost, distance, jersey price, charity percentage).
Optionally, add more organizations.
Participant Registration:

Enter the name of the organization to register for.
Optionally purchase a jersey and choose the size.
Complete the registration and receive a summary of the purchase and charity contribution.
Data Export:

Organization data is exported to org1.txt after registration.