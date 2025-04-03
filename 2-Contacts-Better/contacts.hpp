#ifndef __CONTACTS_HPP_INCLUDED__
#define __CONTACTS_HPP_INCLUDED__
#include "entries.hpp"
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>
namespace contacts {
using namespace std;
class Contacts { // Class Contacts
  public:
    // Will set loaded flag as false.
    Contacts();
    // Load from a USSV file.
    Contacts(string filePath);
    // Will flush before object destroyed.
    ~Contacts();
    // Flush changes to disk.
    bool flush();
    // Load from USSV file.
    bool load_from_file(string filePath);
    // Is loaded or not.
    bool is_loaded() const;
    // Return used USSV file path.
    string file_path() const;
    // List all entries to stdout.
    void list_to_cout(char sortBy, bool desc, bool asianStyle) const;
    // Export to CSV.
    void export_to_csv(bool useFullName, bool asianStyle, string separator, ofstream &outStream);
    // Save as.
    void save_as(ofstream &outStream);
    // Add new entry from cin, interactive.
    void new_from_cin_interactive();
    // Find by full text. Map accelerated.
    set<size_t> find_full(char by, string &target);
    // Find by part of text.
    set<size_t> find_part(char by, string &target) const;
    // Find by regex matched or not.
    set<size_t> find_regex(char by, string &target) const;
    // Print result set to stdout.
    void cout_by_res_set(set<size_t> &res, bool asianStyle);
    // Delete an entry.
    void delete_entry(size_t index);
    // Get const ref of a entry.
    const entries::Entry &get_entry_const_ref(size_t index) const;
    // Get const ref of the entries vec.
    const vector<entries::Entry> &get_entries_vec_const_ref(void) const;
    // Modify an entry.
    bool mod_entry(size_t index, char part, string &data);
    // Get contacts size (count of entries).
    size_t size(void) const;
    // Get index of which will be operated.
    size_t get_index_by_full_name_interactive(bool asianStyle) const;

  private:
    string FilePath;
    bool Loaded;
    vector<entries::Entry> Entries;
    map<string, set<size_t>> ByFirstName;
    map<string, set<size_t>> ByLastName;
    map<string, set<size_t>> ByPhone;
    map<string, set<size_t>> ByTel;
    map<string, set<size_t>> ByEmail;
    map<string, set<size_t>> ByGroup;
    void add_new_entry(entries::Entry &newEntry);
    void load_from_ifstream(ifstream &fileStream);
};
} // namespace contacts
#endif
