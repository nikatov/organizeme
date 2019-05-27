#include <vector>
#include <memory>
#include <cassert>

#include "package/package.h"

bool testPackageUser(ChangeUser &user){
    BinaryData encoded = encodeUser(user);
    UserData userData = decodeUser(encoded.data);
    return (user.getId() == userData.user->getId() && user.getUsername() == userData.user->getUsername() &&
            user.getLastName() == userData.user->getLastName() && user.getFirstName() == userData.user->getFirstName() &&
            user.getPatronymic() == userData.user->getPatronymic() && user.getPassword() == userData.user->getPassword());
}

int main(){
    ChangeUser user(0, "User1", "Polokov", "Ivan", "Ivanovich", "qwerty");
    ChangeUser user1(3, "", "Polokov", "Ivan", "Ivanovich", "qwerty");
    ChangeUser user2(3, "User1", "", "Ivan", "Ivanovich", "qwerty");
    ChangeUser user3(3, "User1", "Polokov", "", "Ivanovich", "qwerty");
    ChangeUser user4(3, "User1", "Polokov", "Ivan", "", "qwerty");
    ChangeUser user5(3, "User1", "Polokov", "Ivan", "Ivanovich", "");
    assert(testPackageUser(user));
    assert(testPackageUser(user1));
    assert(testPackageUser(user2));
    assert(testPackageUser(user3));
    assert(testPackageUser(user4));
    assert(testPackageUser(user5));
    return 0;
}