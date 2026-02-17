#include "user_repository.h"

#include "../utils/password_hasher.h"

UserRepository::UserRepository() {
    users.push_back({1, "admin", PasswordHasher::hashPassword("admin123"), true});
    users.push_back({2, "finance_a", PasswordHasher::hashPassword("finance123"), false});

    permissions.push_back({2, 1001, CompanyPermissionLevel::READ_WRITE});
    permissions.push_back({2, 1002, CompanyPermissionLevel::READ_ONLY});
}

std::optional<User> UserRepository::findByUsername(const std::string &username) const {
    for (const auto &u : users) {
        if (u.username == username) {
            return u;
        }
    }
    return std::nullopt;
}

bool UserRepository::updatePassword(int userId, const std::string &newHash) {
    for (auto &u : users) {
        if (u.userId == userId) {
            u.passwordHash = newHash;
            return true;
        }
    }
    return false;
}

bool UserRepository::hasCompanyReadPermission(int userId, int companyId) const {
    for (const auto &u : users) {
        if (u.userId == userId && u.isAdmin) {
            return true;
        }
    }

    for (const auto &p : permissions) {
        if (p.userId == userId && p.companyId == companyId) {
            return true;
        }
    }
    return false;
}

bool UserRepository::hasCompanyWritePermission(int userId, int companyId) const {
    for (const auto &u : users) {
        if (u.userId == userId && u.isAdmin) {
            return true;
        }
    }

    for (const auto &p : permissions) {
        if (p.userId == userId && p.companyId == companyId && p.level == CompanyPermissionLevel::READ_WRITE) {
            return true;
        }
    }
    return false;
}
