#include <iostream>

class HashLPTable {
   public:
    HashLPTable() { table = std::vector<HashedObj>(4); }

    void insertItem(int value) {
        if (elements_count() >= (int)table.size() / 2) {
            rehash();
        }
        int index = hash_(value);
        while (table[index].is_value) {
            index = (index + 1) % table.size();
        }
        table[index] = HashedObj(value, hash_(value));
        ++size_;
    }

    void erase(int value) {
        // deleteItem(hash_(value));
        eraseItem(value);
    }

    bool find(int value) {
        int index = hash_(value);
        while (table[index].is_value && table[index].value != value) {
            index = (index + 1) % table.size();
        }
        return value == table[index].value;
    }

    void print() {
        for (int i = 0; i < size(); i++) {
            if (table[i].is_value) {
                std::cout << table[i].value << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }

    size_t size() { return table.size(); }
    int elements_count() { return size_; }

   private:
    struct HashedObj {
        bool is_value = false;
        int value;
        int key;
        HashedObj(int v, int k) : value(v), key(k), is_value(true) {}
        HashedObj() {}
    };

    std::vector<HashedObj> table{};

    int size_ = 0;

    int hash_(int key) { return key % table.size(); }

    void eraseItem(int value) {
        int index = hash_(value);
        while (table[index].value != value) {
            if (!table[index].is_value) {
                return;
            }
            index = (index + 1) % table.size();
        }
        table[index].is_value = false;
        --size_;
        int jndex = index + 1;
        while (table[jndex].is_value) {
            if (table[jndex].key == jndex) {
                jndex = (jndex + 1) % table.size();
            } else {
                table[index] = table[jndex];
                index = jndex;
                table[jndex].is_value = false;
                jndex = (jndex + 1) % table.size();
            }
        }
    }

    // void deleteItem(int index) {
    //     int jndex = (index + 1) % table.size();
    //     while (!table[jndex].is_value || table[jndex].key !=
    //     table[index].key) {
    //         if (!table[jndex].is_value) {
    //             table[index].is_value = false;
    //             --size_;
    //             return;
    //         }
    //         jndex = (jndex + 1) % table.size();
    //     }
    //     table[index] = table[jndex];
    //     deleteItem(jndex);
    // }

    void rehash() {
        std::vector<HashedObj> new_table(size() * 2);
        for (int i = 0; i < size(); i++) {
            if (table[i].is_value) {
                int key = table[i].value;
                int index = key % new_table.size();
                new_table[index] = HashedObj(key, index);
            }
        }
        table = new_table;
    }
};

int main() {
    HashLPTable table;
    table.insertItem(1);
    table.print();
    table.insertItem(1);
    table.print();
    table.insertItem(1);
    table.print();
    table.insertItem(1);
    table.print();
    table.erase(1);
    table.print();
    table.erase(1);
    table.print();
    table.erase(1);
    table.print();
    table.erase(1);
    table.print();
    table.erase(1);
    table.print();
    table.insertItem(1);
    table.print();
    table.insertItem(1);
    table.print();

    std::cout << "\n-------\n\n";

    HashLPTable table2;
    for (int i = 0; i < 10; ++i) {
        table2.insertItem(i);
    }
    table2.print();

    std::cout << "\n-------\n\n";

    HashLPTable table3;
    table3.insertItem(3);
    table3.insertItem(3);
    std::cout << table3.find(3) << ' ' << table3.find(2) << '\n';
    table3.print();

    std::cout << "\n-------\n\n";

    HashLPTable table4;
    table4.insertItem(3);
    table4.insertItem(4);
    table4.insertItem(3);
    table4.print();
    table4.erase(3);
    table4.print();
    table4.insertItem(3);
    table4.erase(4);
    table4.print();
}