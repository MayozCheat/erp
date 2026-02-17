#ifndef SERVICE_AUTH_SERVICE_H
#define SERVICE_AUTH_SERVICE_H

#include "../domain/models.h"
#include "../repository/user_repository.h"

#include <string>

// 认证服务：负责登录、改密、权限校验
class AuthService {
public:
    explicit AuthService(UserRepository &userRepository);

    bool login(const std::string &username, const std::string &password, User &outUser, std::string &errorMessage) const;
    bool changePassword(int userId, const std::string &newPassword, std::string &errorMessage);

    bool checkCompanyReadPermission(int userId, int companyId, std::string &errorMessage) const;
    bool checkCompanyWritePermission(int userId, int companyId, std::string &errorMessage) const;

private:
    UserRepository &userRepository;
};

#endif
