//
// Created by Simon Raul on 5/20/2025.
//

#ifndef IREPO_H
#define IREPO_H
#include <utility>
#include <string>

using namespace std;

template <typename Derived, typename Entity>
class IRepo {
public:
    virtual ~IRepo() = default;

    template<typename... Args>
    shared_ptr<Entity> create(Args&&... args) {
        return static_cast<Derived*>(this)->create(forward<Args>(args)...);
    }

    template<typename... Args>
    bool update(Args&&... args) {
        return static_cast<Derived*>(this)->update(forward<Args>(args)...);
    }

    virtual vector<shared_ptr<Entity>> list() = 0;
    virtual bool remove(int arg) = 0;
    virtual Entity find_by_email(const string& arg) = 0;
};



#endif //IREPO_H
