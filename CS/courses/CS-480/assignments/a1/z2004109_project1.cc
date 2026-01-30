/********************************************************************
CSCI 480 - Assignment 1 - Spring 2026
Programmer: Nate Warner
Section: 1
TA: 
Date Due: 01/28/2026
Purpose: Write C++ to read various files under /proc, and output formatted information 
         about things found there.
*********************************************************************/

#include <iostream> 
#include <iomanip> 
#include <vector>
#include <cstdlib> 
#include <cstdint> 
#include <unistd.h>
#include <typeinfo>
#include <cctype> 
#include <algorithm>
#include <iterator>
#include <string> 
#include <fstream>
#include <sstream>
#include <unordered_set>

// Using
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

const int SECONDS_IN_DAY = 3600*24;
const int SECONDS_IN_HOUR = 3600;
const int SECONDS_IN_MIN = 60;

const int JIFFY = 100;

const int KB_PER_MB = 1024;

// Helper function to processor lines in /proc/cpuinfo, 
// grabs everything in a line after a colon
string grab_after_colon(string& s) { return s.substr(s.find(":")+2); }

// Helper function to separate address sizes in the address sizes
// line in /proc/cpuinfo
std::pair<string,string> separate_addr_sizes(const string& s) {
    int delim_pos = s.find(","); 
    return std::make_pair(s.substr(0,delim_pos), s.substr(delim_pos+2));
}

// Finds the hostname from /proc/sys/kernel/hostname
string get_hostname() {
    // Open file for reading
    std::ifstream input("/proc/sys/kernel/hostname");

    // Create return string
    string host_name = "";

    // Grab the hostname from the file
    getline(input, host_name);

    // Close file
    input.close();
    
    // Return hostname
    return host_name;
}

// Finds the ostype from /proc/sys/kernel/ostype
string get_ostype() {
    // Open file for reading
    std::ifstream input("/proc/sys/kernel/ostype");
    
    // Create return string
    string os_type = "";

    // Grab the ostype from the file
    getline(input, os_type);

    // Close file
    input.close();

    // Return ostype string
    return os_type;
}

// Finds the osrelease from /proc/sys/kernel/osrelease
string get_osrelease() {
    // Open file for reading
    std::ifstream input("/proc/sys/kernel/osrelease");

    // Create return string
    string osrelease = "";
    
    // Grab osrelease info from file
    getline(input, osrelease);

    // Close file
    input.close();

    // Return osrelease
    return osrelease;
}

// Finds the version from /proc/sys/kernel/version
string get_version() {
    // Open file for reading
    std::ifstream input("/proc/sys/kernel/version");

    // Create return string
    string version = "";

    // Grab version from file
    getline(input, version);

    // Close input
    input.close();

    // Return version info
    return version;
}

// Outputs information about the OS
void osinfo_out() {
    string host_name = get_hostname(), 
           ostype = get_ostype(), 
           osrelease = get_osrelease(), 
           version = get_version();

    cout << "A: Questions about " << get_hostname() << "'s OS:" << endl;
    cout << "1. The host name is " << host_name << endl 
        << "2. The ostype is " << ostype << endl 
        << "3. The osrelease is " << osrelease << endl 
        << "4. The version is " << version << endl << endl;
}

// The number of multi-core chips is given by the number of unique physical id's.
// Thus, we count how many distinct physical id's exist in /proc/cpuinfo
std::pair<int,int> get_chip_quantity_and_cores() {
    // ret
    int chip_quantity = 0;
    std::unordered_set<int> physical_ids;

    int cores = 0;

    // Open file for reading
    std::ifstream input("/proc/cpuinfo");

    // For each line in the file
    string line;

    bool inquire_cores = false;
    while (getline(input, line)) {
        // If we want to inquire about the number of cores
        if (inquire_cores) {
            // Find the line that has the number of cores
            if (line.find("cpu cores") != string::npos) {
                // Stream to read each word in line
                std::istringstream word_reader(line);

                // For each word
                string word{};

                // Start reading each word in line
                while (word_reader >> word) {
                    // Found the number of cores
                    if (isdigit(word[0])) {
                        // Get the number of cores and increase count
                        int core_count = stoi(word);
                        cores += core_count;

                        // No longer need to inquire about cores, 
                        // not until a new physical id is found
                        inquire_cores = false;
                        break;
                    }
                }
            }

        } else {
            // Requisite line found
            if (line.find("physical id") != string::npos) {
                // Read words in line until we reach numeric value
                std::istringstream word_reader(line);

                // String to hold each word in line
                string word{};

                // Read each word in line
                while (word_reader >> word) {
                    // If a digit is encountered, we found the physical id
                    if (isdigit(word[0])) {
                        // Retrieve the physical id
                        int id = stoi(word);

                        // If the found id is not yet encountered, we found a new multi core chip
                        if (physical_ids.find(id) == physical_ids.end()) {
                            // So, increase quantity of chips, update current physical id
                            ++chip_quantity;
                            physical_ids.insert(id);

                            // Now that we found a new multi-core chip, we must inquire about its number of cores, 
                            // and add that number to the sum of cores. Note that the information about cores is after the 
                            // information about the physical id

                            inquire_cores = true;
                            break;
                        }
                    }
                }

            }
        }
    }

    // Close file
    input.close();

    // Return found value
    return std::make_pair(chip_quantity, cores);

}

// Gets the uptime of the system
double get_uptime() {
    // ret
    string str_uptime_seconds = "";
    // string str_idletime_seconds = 0;

    // Open uptime for reading
    std::ifstream input("/proc/uptime");

    input >> str_uptime_seconds; 

    // Close file
    input.close();

    // Return uptime in seconds
    return std::stof(str_uptime_seconds);
}

// Formats the uptime of the system as days, hours, minutes, seconds
string format_uptime(float seconds) {
    // Days, hours, minutes, seconds

    // Find the number of days
    int days = seconds / (SECONDS_IN_DAY);
    seconds -= (days * SECONDS_IN_DAY); 

    // Find the number of remaining hours
    int hours = seconds / (SECONDS_IN_HOUR);
    seconds -= (hours * SECONDS_IN_HOUR);

    // Find the number of remaining minutes
    int minutes = seconds / (SECONDS_IN_MIN);
    seconds -= (minutes * SECONDS_IN_MIN);

    // Remaining seconds
    float remaining = seconds;

    return (std::to_string(days) + " days, " 
            + std::to_string(hours) + " hours, " 
            + std::to_string(minutes) + " minutes, " 
            + std::to_string(remaining) + " seconds");
}

// Get requested information about proc0
void proc0info_out() {
    // These hold the info we need to find
    string proc0_vendor{}, proc0_model_name{}, 
           proc0_physical_addr_size{}, proc0_virtual_addr_size{};


    // Open file for reading
    std::ifstream input("/proc/cpuinfo");

    // String for each line
    string line;

    // Current processor while reading file
    int curr_proc = -1;

    bool done = false;
    while (getline(input, line) && !done) {
        // On the requite block
        if (curr_proc == 0) {

            // Found vendor id
            if (line.find("vendor_id") != string::npos) {
                proc0_vendor = grab_after_colon(line);
            // Found model name
            } else if (line.find("model name") != string::npos) {
                proc0_model_name = grab_after_colon(line);
            // Found address sizes
            } else if (line.find("address sizes") != string::npos) {
                std::pair<string, string> addr_sizes = separate_addr_sizes(grab_after_colon(line));
                proc0_physical_addr_size = addr_sizes.first, proc0_virtual_addr_size = addr_sizes.second;
            }
            
        } else {
            // Find processor zero
            if (line.find("processor") != string::npos) {
                // Find the proc number
                int proc_number = stoi(grab_after_colon(line));

                // If we already processed processor zero, we are done
                if (curr_proc == 0) done = true;

                // Otherwise, set the current processor number
                curr_proc = proc_number;
            }
        }
    }

    // Close file
    input.close();

    // Output requite information
    cout << "C. Regarding processor 0:" << endl;
    cout << "1. The Vendor is: " << proc0_vendor << endl
        << "2. The Model is: " << proc0_model_name << endl
        << "3. The physical addr size is: " << proc0_physical_addr_size  << endl
        << "4. The virtual addr size is: " << proc0_virtual_addr_size << endl << endl;
}

// Parse uptime amounts for a CPU number
std::vector<int> get_cpuN_uptime_amounts(const string& amounts) {
    // Jiffy duration in seconds
    float jiffy_duration_seconds = 1.f/JIFFY;

    // Return vector housing times
    std::vector<int> vec_amounts;

    // Find first instance of space, don't need stuff before it
    int start = amounts.find(" ");

    // Current number in string form, easy to build as string
    string curr_number{};

    // Run through input string
    for (int i=start+1; i<amounts.size(); ++i) {
        // If we encounter a space, number is complete, add to vector
        if (amounts[i] == ' ') {
            // Add to vector and reset current number string
            vec_amounts.push_back(stof(curr_number) * jiffy_duration_seconds);
            curr_number = "";
        // Otherwise, build number
        } else {
            curr_number += amounts[i];
        }

    }
    vec_amounts.push_back(stof(curr_number));

    // Return amounts
    return vec_amounts;
}

// Get time info about processor 5 from /proc/stat
void proc5info_out() {
    // Note: Vector entries are
    //      0. User mode
    //      1. Low-priority user mode,
    //      2. System mode
    //      3. Idle
    //      ...
    // Further note: Vector entries are in seconds
    
    // We must read until we get to cpu5, then we get info from it
    std::ifstream input("/proc/stat");
    
    // String to hold each line
    string line{};

    // Vector to hold times for cpu5
    std::vector<int> amounts;
    while (getline(input, line)) {
        // Found cpu5
        if (line.find("cpu5") != string::npos) {
            // Get amount vector
            amounts = get_cpuN_uptime_amounts(line);
        }
    }

    // proc5 does not exist
    if (amounts.empty()) {
        cout << "No information on cpu5, probably because it doesn't exist" << endl;
        return;
    }

    // Output information about proc5, if it exists
    cout << "D. Questions about processor 5" << endl;
    cout << "1. Time spent in user mode is " << amounts[0] << " seconds" << endl
         << "2. Time spent in system mode is " << amounts[2] << " seconds" << endl
         << "3. Time spent in idle mode is " << amounts[3] << " seconds" << endl 
         << "4. Formatted time spent in idle mode is " << format_uptime(amounts[3]) << endl << endl;

    // Close input
    input.close();
}

// Parse line containing swap partition, returns swap size in MB
float parse_swapsize(const string& info) {
    // String to hold size
    string str_size{};

    // Starting position
    int start = info.find("partition");

    // Move to start of size
    while (!isdigit(info[start])) ++start;


    // Extract digits up until space
    for (int i=start; i<(int)info.size(); ++i) {
        str_size+=info[i];
        if (!isdigit(info[i])) break;
    }

    // Return size in MB
    return stof(str_size) / KB_PER_MB;
}

// Reads /proc/swaps and returns size in MB
float get_swap_size_mb() {
    // Open file for reading
    std::ifstream input("/proc/swaps");
    
    // String to hold each line
    string line{};

    // The found size in mb
    float size = 0;

    // Run through each line
    while (getline(input, line)) {
        // Find line with swap partition info
        if (line.find("partition") != string::npos) {
            size = parse_swapsize(line);
            break;
        }
    }

    // Close input
    input.close();         

    // Return the size
    return size;
}

// Entry
int main(int argc, const char* argv[]) {

    // This is be useful
    string hostname = get_hostname();

    // A. Output the information about the OS
    osinfo_out();

    // B. Output the number of multi-core chips exist
    cout << "B: Questions about " << hostname << "'s processor:" << endl;
    cout << "1. The number of multi-core chips existing on " << hostname << " is " << get_chip_quantity_and_cores().first << endl;
    cout << "2. The number of processors (cores) existing on " << hostname << " is " << get_chip_quantity_and_cores().second << endl;
    cout << "3. " << hostname << " has been up for " << get_uptime() << " seconds" << endl;
    cout << "4. This time is given by " << format_uptime(get_uptime()) << endl << endl;

    // C.
    proc0info_out();

    // D.
    proc5info_out();

    // E. 
    cout << "1. The size of " << hostname << "'s " << "swap device in MB is " << get_swap_size_mb() << " MB" << endl;

    return EXIT_SUCCESS;
}
