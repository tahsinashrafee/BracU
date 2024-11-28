#include "scope_table.h"

#include <fstream>
extern std::ofstream outlog;

class symbol_table
{
private:
    scope_table *current_scope;
    int bucket_count;
    int current_scope_id;

public:
    symbol_table(int bucket_count): current_scope_id(-1) {
        current_scope = new scope_table(bucket_count, ++current_scope_id, nullptr);
    }
    ~symbol_table(){
        while (current_scope != nullptr) {
            exit_scope(outlog);
        }
    }
    void enter_scope(ofstream& outlog){
        scope_table* new_scope = new scope_table(bucket_count, ++current_scope_id, current_scope);
        current_scope = new_scope;
        outlog << "New ScopeTable with ID " << current_scope->get_unique_id() << " created" << std::endl;
    }
    void exit_scope(ofstream& outlog){
        if (current_scope != nullptr) {
            outlog << "ScopeTable with ID " << current_scope->get_unique_id() << " removed" << std::endl;
            scope_table* temp = current_scope;
            current_scope = current_scope->get_parent_scope();
            delete temp;
        }
    }
    bool insert(symbol_info* symbol){
        if (current_scope != nullptr) {
            return current_scope->insert_in_scope(symbol);
        }
        return false;

    }
    symbol_info* lookup(symbol_info* symbol){
        scope_table* scope = current_scope;
        while (scope != nullptr) {
            symbol_info* found = scope->lookup_in_scope(symbol);
            if (found != nullptr) {
                return found;
            }
            scope = scope->get_parent_scope();
        }
        return nullptr;
    }
    void print_current_scope(ofstream& outlog){
        if (current_scope != nullptr) {
            current_scope->print_scope_table(outlog);
        }
    }
    void print_all_scopes(ofstream& outlog);

    // you can add more methods if you need

    int getCurrentScopeID() const {
        
        return current_scope_id;  
        
    } 
};

// complete the methods of symbol_table class


void symbol_table::print_all_scopes(ofstream& outlog)
{
    outlog<<"################################"<<endl<<endl;
    scope_table *temp = current_scope;
    while (temp != NULL)
    {
        temp->print_scope_table(outlog);
        temp = temp->get_parent_scope();
    }
    outlog<<"################################"<<endl<<endl;
}