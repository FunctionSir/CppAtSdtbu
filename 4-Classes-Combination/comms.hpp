/*
 * @Author: FunctionSir
 * @License: AGPLv3
 * @Date: 2025-05-14 21:51:36
 * @LastEditTime: 2025-05-15 15:25:11
 * @LastEditors: FunctionSir
 * @Description: -
 * @FilePath: /4-Classes-Combination/comms.hpp
 */
#ifndef __COMMS_INCLUDED__
#define __COMMS_INCLUDED__

#include "commentry.hpp"
#include <cstddef>
#include <string>

class Comms {
  public:
    enum FindBy { Name, Number };                    // Find methods
    Comms();                                         // Default constructor
    Comms(size_t cnt);                               // Constructor for pre-reserving some space
    Comms(string path);                              // Constructor for loading from file
    Comms(const Comms &origin);                      // Copy constructor
    Comms &operator=(const Comms &origin);           // Operator =
    ~Comms();                                        // Destructor
    void push_back(const CommEntry &entry);          // Add new entry at the end of comms, auto resize if needed
    size_t find(string target, FindBy findBy) const; // Find entry, get index
    const CommEntry &get(size_t pos) const;          // Get inmut ref
    CommEntry &get_mut(size_t pos);                  // Get mut ref
    void shrink(void);                               // Shrink to fit the entries count
    size_t size(void);                               // Get entries count
    size_t capacity(void);                           // Get max capacity
    void reserve(size_t cap);                        // Set reserved capacity, aka max count
    void erase(size_t pos);                          // Delete an entry
    void order(bool desc = false);                   // Order the entries by name
    void load(string path);                          // Load from file on disk
    void save(string path);                          // Save to file on disk

  private:
    CommEntry *m_entries; // Comm entries
    size_t m_max_count;   // Max entries count
    size_t m_count;       // Current entries count

    static void comms_copy(CommEntry *dst, CommEntry *src, size_t cnt);
    static bool cmp_asc(const CommEntry &a, const CommEntry &b);
    static bool cmp_desc(const CommEntry &a, const CommEntry &b);
    static void comms_obj_copy(Comms *dest, const Comms &origin);
};

#endif
