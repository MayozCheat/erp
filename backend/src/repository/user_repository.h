#ifndef REPOSITORY_USER_REPOSITORY_H
#define REPOSITORY_USER_REPOSITORY_H

#include "../domain/models.h"

#include <optional>
#include <vector>

// 用户仓储：负责用户与权限数据读取（演示内存实现）
class UserRepository {
public:
    UserRepository();

    std::optional<User> findByUsername(const std::string &username) const;
    bool updatePassword(int userId, const std::string &newHash);
    bool hasCompanyReadPermission(int userId, int companyId) const;
    bool hasCompanyWritePermission(int userId, int companyId) const;

private:
    std::vector<User> users;
    std::vector<UserCompanyPermission> permissions;
};

#endif
