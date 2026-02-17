#include "auth_service.h"

#include "../utils/password_hasher.h"

AuthService::AuthService(UserRepository &userRepository) : userRepository(userRepository) {}

bool AuthService::login(const std::string &username, const std::string &password, User &outUser, std::string &errorMessage) const {
    auto userOptional = userRepository.findByUsername(username);
    if (!userOptional.has_value()) {
        errorMessage = "用户不存在";
        return false;
    }

    if (!PasswordHasher::verifyPassword(password, userOptional->passwordHash)) {
        errorMessage = "密码错误";
        return false;
    }

    outUser = userOptional.value();
    return true;
}

bool AuthService::changePassword(int userId, const std::string &newPassword, std::string &errorMessage) {
    if (newPassword.size() < 8) {
        errorMessage = "新密码长度不能少于8位";
        return false;
    }

    bool ok = userRepository.updatePassword(userId, PasswordHasher::hashPassword(newPassword));
    if (!ok) {
        errorMessage = "用户不存在，修改密码失败";
        return false;
    }
    return true;
}

bool AuthService::checkCompanyReadPermission(int userId, int companyId, std::string &errorMessage) const {
    if (!userRepository.hasCompanyReadPermission(userId, companyId)) {
        errorMessage = "权限不足：没有该公司读取权限";
        return false;
    }
    return true;
}

bool AuthService::checkCompanyWritePermission(int userId, int companyId, std::string &errorMessage) const {
    if (!userRepository.hasCompanyWritePermission(userId, companyId)) {
        errorMessage = "权限不足：没有该公司写入权限";
        return false;
    }
    return true;
}
