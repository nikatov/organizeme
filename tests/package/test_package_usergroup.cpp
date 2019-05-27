#include <vector>
#include <memory>
#include <cassert>

#include "package/package.h"

bool testPackageUserGroup(ChangeUserGroup &userGroup){
    BinaryData encoded = encodeUserGroup(userGroup);
    UserGroupData userGroupData = decodeUserGroup(encoded.data);
    return (userGroup.getId() == userGroupData.userGroup->getId() &&
            userGroup.getGroupName() == userGroupData.userGroup->getGroupName() &&
            userGroup.getIsLocal() == userGroupData.userGroup->getIsLocal());
}

int main(){
    ChangeUserGroup userGroup(0, "User1", true);
    ChangeUserGroup userGroup1(3, "", true);
    ChangeUserGroup userGroup2(3, "User1", false);
    assert(testPackageUserGroup(userGroup));
    assert(testPackageUserGroup(userGroup1));
    assert(testPackageUserGroup(userGroup2));
    return 0;
}