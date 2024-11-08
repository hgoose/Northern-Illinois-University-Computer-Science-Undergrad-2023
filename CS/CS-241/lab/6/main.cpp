#include <iostream>
#include "hash_table.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

int  main()
{
    hash_table table;

    string operation;
    int key, index;
    string record, str_key, value;
    bool success;
    
    cout << "Transaction Report\n\n";
    
    // While not EOF, read the requested operation.

    while (getline(cin, operation, '|'))
    {
        switch (operation[0])
        {
            case 'A':

                // Add a record.

                // Read the key and convert it to an integer.

                getline(cin, str_key, '|');
                key = stoi(str_key);

                // Read the value for the record.

                getline(cin, value);

                // Attempt to insert the record into the table.

                success = table.insert(key, value);
                if (success)
                    cout << "ADD: Record with key " << key 
                         << " inserted with value \"" << value
                         << "\"\n";
                else
                    cout << "ADD: Unable to insert record with key " << key
                         << "; table is full\n";
                break;
                
            case 'D':

                // Delete a record.
        
                // Read the key and convert it to an integer.

                getline(cin, str_key);
                key = stoi(str_key);

                // Attempt to erase the record from the table.

                success = table.erase(key);
                if (success)
                    cout << "DELETE: Record with key " << key << " deleted\n";
                else
                    cout << "DELETE: Record with key " << key << " not found\n";
                break;
                
            case 'U':

                // Update the value for a record.
        
                // Read the key and convert it to an integer.

                getline(cin, str_key, '|');
                key = stoi(str_key);

                // Read the value for the record.

                getline(cin, value);

                // Attempt to find and update the record in the table.

                success = table.update(key, value);
                if (success)
                    cout << "UPDATE: Record with key " << key
                         << " updated with new value \"" << value << "\"\n";
                else
                    cout << "UPDATE: Record with key " << key 
                         << " not found\n";
                break;
                
            case 'F':

                // Find a record's value.
        
                // Read the key and convert it to an integer.

                getline(cin, str_key);
                key = stoi(str_key);

                // Attempt to find the record in the table.

                index = table.find(key);
                if (index != -1)
                    cout << "FIND: Record with key " << key 
                         << " found at index " << index << "\n";
                else
                    cout << "FIND: Record with key " << key << " not found\n";
                break;
                
            default:
                cout << "Invalid operation\n";
        }
    }
    
    cout << "\nHash Table Listing\n\n";
    cout << table;
    
    return 0;
}

