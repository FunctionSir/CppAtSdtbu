/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-04-03 14:04:30
 * @LastEditTime: 2025-04-03 20:42:31
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /2-Contacts-Better/entries.hpp
 */
#ifndef __ENTRIES_HPP_INCLUDED__
#define __ENTRIES_HPP_INCLUDED__
#include <string>
using namespace std;
namespace entries {
using namespace std;
class Entry {
  public:
    string FirstName, LastName;
    string Phone, Tel, Email;
    string Group, Note;

    // Set attributes directly.
    void set_attributes(string firstName = "", string lastName = "", string phone = "", string tel = "",
                        string email = "", string note = "");
    // Build entry from cin, interactive.
    void from_cin_interactive(void);
    // Build entry from USSV line.
    void from_ussv(string &ussv);
    // Get English-style full name.
    string get_en_full_name(void) const;
    // Get Asian-style full name.
    string get_asian_full_name(void) const;
    // Convert to USSV string.
    string to_ussv(string end = "");
    // Convert to CSV string.
    string to_csv(bool useFullName = false, bool asianStyleName = false, string separator = ",", string end = "") const;
    // Get the header of CSV.
    static string get_csv_header(bool useFullName = false, bool asianStyleName = false, string separator = ",",
                                 string end = "");

  private:
    enum Part { PartFirstName, PartLastName, PartPhone, PartTel, PartEmail, PartGroup, PartNote };
    void set_attribute_by_part_id(Part part, string &data);
};
} // namespace entries
#endif
